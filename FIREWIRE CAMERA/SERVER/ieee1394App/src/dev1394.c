/*****************************************************************************/
/*    dev1394.c - IEEE1394 'firewire' device support for Epics               */
/*                                                                           */
/*                                                                           */
/*    TODO:                                                                  */
/*                                                                           */
/*       1. Option to return only evey 2nd pixel - to reduce image size      */
/*       8. Use latest buffer                                                */
/*       9. Find reason for message in /var/log/messages                     */
/*      14. Update width and Height fields when mode changes                 */
/*      15. Display software revision                                        */
/*                                                                           */
/*    DONE:                                                                  */
/*       2. More than one camera                                             */
/*       3. Support YUV422 as well as monochrome                             */
/*       4. Suspend transmission                                             */
/*       5. Add threshold for calculating width                              */
/*       6. Support format 1 mode 0 800x600 YUV422                           */
/*       7. Support 1024x768 mono 16 for flea                                */
/*      10. Set available formats                                            */
/*      11. Set available modes                                              */
/*      12. Set available framerates                                         */
/*      13. Display Iso Status                                               */
/*      16. Display IIDC     version                                         */
/*                                                                           */
/*                                                                           */
/*                                                                           */
/*                                                                           */
/*****************************************************************************/
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <math.h>
#include <sys/time.h>
#include <fcntl.h>

#include "alarm.h"
#include "cvtTable.h"
#include "dbDefs.h"
#include "dbAccess.h"
#include "recGbl.h"
#include "recSup.h"
#include "devSup.h"
#include "link.h"
#include "aiRecord.h"
#include "aoRecord.h"
#include <stringinRecord.h>
#include <waveformRecord.h>
#include <mbbiRecord.h>
#include <mbboRecord.h>

#include <libraw1394/raw1394.h>
#include <libdc1394/dc1394_control.h>
#include <epicsExport.h>

#define CSIG1 1.5
#define CSIG2 0.5

#define BAYER_PATTERN_REG	0x1040

#define ABS_VAL_GAIN_MIN	0x920
#define ABS_VAL_GAIN_MAX	0x924
#define ABS_VAL_GAIN		0x928

#define ABS_VAL_SHUTTER_MIN	0x910
#define ABS_VAL_SHUTTER_MAX	0x914
#define ABS_VAL_SHUTTER		0x918


static long init_ai();
static long init_record_ai();
static long read_ai();

static long init_ao();
static long init_record_ao();
static long write_ao();
static long linconv_ao();

static long init_record_stringin();
static long read_stringin();

static long init_waveform();
static long init_record_waveform();
static long read_waveform();

static long init_mbbi();
static long init_record_mbbi();
static long read_mbbi();

static long init_mbbo();
static long init_record_mbbo();
static long write_mbbo();

struct{
        long            number;
        DEVSUPFUN       report;
        DEVSUPFUN       init;
        DEVSUPFUN       init_record;
        DEVSUPFUN       get_ioint_info;
        DEVSUPFUN       read_ai;
        DEVSUPFUN       special_linconv;
}devAi1394={
        6,
        NULL,
        init_ai,
        init_record_ai,
        NULL,
        read_ai,
        NULL
};

struct {
        long            number;
        DEVSUPFUN       report;
        DEVSUPFUN       init;
        DEVSUPFUN       init_record;
        DEVSUPFUN       get_ioint_info;
        DEVSUPFUN       write_ao;
        DEVSUPFUN       special_linconv;
}devAo1394={
        6,
        NULL,
        init_ao,
        init_record_ao,
        NULL,
        write_ao,
	linconv_ao
};

struct {
        long            number;
        DEVSUPFUN       report;
        DEVSUPFUN       init;
        DEVSUPFUN       init_record;
        DEVSUPFUN       get_ioint_info;
        DEVSUPFUN       write_mbbo;
}devMbbo1394={
        5,
        NULL,
        init_mbbo,
        init_record_mbbo,
        NULL,
        write_mbbo
};

struct {
        long            number;
        DEVSUPFUN       report;
        DEVSUPFUN       init;
        DEVSUPFUN       init_record;
        DEVSUPFUN       get_ioint_info;
        DEVSUPFUN       read_mbbi;
}devMbbi1394={
        5,
        NULL,
        init_mbbi,
        init_record_mbbi,
        NULL,
        read_mbbi
};

struct {
        long            number;
        DEVSUPFUN       report;
        DEVSUPFUN       init;
        DEVSUPFUN       init_record;
        DEVSUPFUN       get_ioint_info;
        DEVSUPFUN       read_stringin;
}devStringin1394={
        5,
        NULL,
        NULL,
        init_record_stringin,
        NULL,
        read_stringin
};

struct {
        long            number;
        DEVSUPFUN       report;
        DEVSUPFUN       init;
        DEVSUPFUN       init_record;
        DEVSUPFUN       get_ioint_info;
        DEVSUPFUN       read_waveform;
}devWaveform1394={
        5,
        NULL,
        init_waveform,
        init_record_waveform,
        NULL,
        read_waveform
};

epicsExportAddress(dset,devAi1394);
epicsExportAddress(dset,devAo1394);
epicsExportAddress(dset,devStringin1394);
epicsExportAddress(dset,devWaveform1394);
epicsExportAddress(dset,devMbbi1394);
epicsExportAddress(dset,devMbbo1394);

/*
  FILE* imagefile;
*/
  dc1394_cameracapture camera[10];
  dc1394_camerainfo info;
  int numNodes;
  int numCameras;
  raw1394handle_t handle;
  nodeid_t * camera_nodes;
  dc1394_feature_set features;
  quadlet_t qValue;

  float  absGain;
  float  absGainMax;
  float  absGainMin;
  float  absShutter;
  float  absShutterMax;
  float  absShutterMin;

  int  init_done = 0;
  int  init_camera_done[10];
  dc1394_miscinfo camera_misc_info[10];

  unsigned int mode[10];
  int width[10];
  int maxwidth[10];
  int woffset[10];
  int height[10];
  int maxheight[10];
  int hoffset[10];
  int size[10];
  int dropped_frames[10];
  int stopstart;
  double threshold[10];
  double low_thresh[10];
  double xavg[10];
  double yavg[10];

  float xw[10];
  float xp[10];
  float xsn[10];

  float yw[10];
  float yp[10];
  float ysn[10];
  
  int trigger_mode;
  int set_trigger_mode;
  int iso_status;
  dc1394bool_t trigger_on_off;
  int set_trigger_on_off;
  int framerate;
  int set_framerate;
  dc1394bool_t trigger_polarity;
  int set_trigger_polarity;
  int format;
  int set_format;
  int	gain;
  int	shutter;
  int	brightness;
  int	exposure;
  int sw_version;

  char vendor[80];
  char model[80];
  int ret=0;
  int pattern = 0;

  int  bpp[10] ;  /* Bytes per pixel */
  int  code[10] ;  /* encoding - 1=mono, 2=YUV422, 3=RGB */
  quadlet_t formats[10];
  quadlet_t modes[10];
  int num_formats[10];
  int format_code[10][10];
  char format_string[10][10][80];
  int num_modes[10];
  int mode_code[10][10];
  char mode_string[10][10][80];
/* Define max + background substraction variables(AA) */
  int max[10];
  int maxCol[10];
  int maxLine[10];
  int xdistMaxSum[10];
  int ydistMaxSum[10];
  int xdistMaxCol[10];
  int ydistMaxLine[10];
  int bgs[10];
  int man_auto[10];
  float xFWHM[10];
  float xWindow[10];
  int sCol[10];
  int eCol[10];
  int sLine[10];
  int eLine[10];
  int ext_sCol[10];
  int ext_eCol[10];
  int ext_sLine[10];
  int ext_eLine[10];  
  float yFWHM[10];
  float yWindow[10];
  float sigmaX[10];
  float sigmaY[10];
  float sumTot[10];
  unsigned long *dest_ref;
  unsigned char data[1600*1200];
  unsigned char data_array_ref[1600*1200];
  unsigned char data_array_diff[1600*1200];
  int counter = 0;
  struct timeval start, end;
  float afps[10];




/****************************************************************************/
/*              TIMING                                                      */
/****************************************************************************/
float calc(struct timeval *one, struct timeval *two){
return( ((two->tv_sec - one->tv_sec) * 1000 ) +  ((two->tv_usec -one->tv_usec)/1000) ) ;
}


/****************************************************************************/
/*              CAMERA INITIALISATION                                       */
/****************************************************************************/

static long init_handle() {
	if (init_done == 0) {
		handle = dc1394_create_handle(0);
		if (handle==NULL) {
			printf("error creating handle\n");
       			return(1);
		}
   		numNodes = raw1394_get_nodecount(handle);
		camera_nodes = dc1394_get_camera_nodes(handle,&numCameras,0);
	}
	init_done=1;
	return(0);
}

/**********************************************************************/
/*             Check available modes in current format                */
/**********************************************************************/
long check_available_modes(int cam){
	int current_format=camera_misc_info[cam].format;
	printf("current_format = %d\n",current_format);

	if (dc1394_query_supported_modes(handle, camera[cam].node,current_format, &modes[cam]) != DC1394_SUCCESS) {
		fprintf( stderr, "unable to get camera formats\n");
       		return(S_db_badField);
	}

	num_formats[cam] = 0;
	/**********************************************************************/
	/*             check if format 0                                      */
	/**********************************************************************/
	if(camera_misc_info[cam].format==FORMAT_VGA_NONCOMPRESSED){
		if (modes[cam] & (0x1 << 31)){ 
			printf("MODE_160x120_YUV444  supported\n"); 
			mode_code[cam][num_modes[cam]]= MODE_160x120_YUV444;
			strcpy(mode_string[cam][num_modes[cam]],"MODE_160x120_YUV444");
			num_modes[cam]++;
		}
		if (modes[cam] & (0x1 << 30)){ 
			printf("MODE_320x240_YUV422  supported\n"); 
			mode_code[cam][num_modes[cam]]= MODE_320x240_YUV422;
			strcpy(mode_string[cam][num_modes[cam]],"MODE_320x240_YUV422");
			num_modes[cam]++;
		}
		if (modes[cam] & (0x1 << 29)){ 
			printf("MODE_640x480_YUV411  supported\n"); 
			mode_code[cam][num_modes[cam]]= MODE_640x480_YUV411;
			strcpy(mode_string[cam][num_modes[cam]],"MODE_640x480_YUV411");
			num_modes[cam]++;
		}
		if (modes[cam] & (0x1 << 28)){ 
			printf("MODE_640x480_YUV422  supported\n"); 
			mode_code[cam][num_modes[cam]]=MODE_640x480_YUV422;
			strcpy(mode_string[cam][num_modes[cam]],"MODE_640x480_YUV422");
			num_modes[cam]++;
		}
		if (modes[cam] & (0x1 << 27)){ 
			printf("MODE_640x480_RGB supported\n"); 
			mode_code[cam][num_modes[cam]]= MODE_640x480_RGB ;
			strcpy(mode_string[cam][num_modes[cam]],"MODE_640x480_RGB");
			num_modes[cam]++;
		}
		if (modes[cam] & (0x1 << 26)){ 
			printf("MODE_640x480_MONO supported\n"); 
			mode_code[cam][num_modes[cam]]= MODE_640x480_MONO ;
			strcpy(mode_string[cam][num_modes[cam]],"MODE_640x480_MONO");
			num_modes[cam]++;
		}
		if (modes[cam] & (0x1 << 25)){ 
			printf("MODE_640x480_MONO16 supported\n"); 
			mode_code[cam][num_modes[cam]]= MODE_640x480_MONO16 ;
			strcpy(mode_string[cam][num_modes[cam]],"MODE_640x480_MONO16");
			num_modes[cam]++;
		}
	}

	/**********************************************************************/
	/*             check if format 1                                      */
	/**********************************************************************/
	if(camera_misc_info[cam].format==FORMAT_SVGA_NONCOMPRESSED_1){
		if (modes[cam] & (0x1 << 31)){ 
			printf("MODE_800x600_YUV422 supported\n");
			mode_code[cam][num_modes[cam]]= MODE_800x600_YUV422 ;
			strcpy(mode_string[cam][num_modes[cam]],"MODE_800x600_YUV422");
			num_modes[cam]++;
		}
		if (modes[cam] & (0x1 << 30)){ 
			printf("MODE_800x600_RGB supported\n");
			mode_code[cam][num_modes[cam]]= MODE_800x600_RGB ;
			strcpy(mode_string[cam][num_modes[cam]],"MODE_800x600_RGB");
			num_modes[cam]++;
		}
		if (modes[cam] & (0x1 << 29)){ 
			printf("MODE_800x600_MONO supported\n");
			mode_code[cam][num_modes[cam]]= MODE_800x600_MONO;
			strcpy(mode_string[cam][num_modes[cam]],"MODE_800x600_MONO");
			num_modes[cam]++;
		}
		if (modes[cam] & (0x1 << 28)){ 
			printf("MODE_1024x768_YUV422 supported\n");
			mode_code[cam][num_modes[cam]]= MODE_1024x768_YUV422 ;
			strcpy(mode_string[cam][num_modes[cam]],"MODE_1024x768_YUV422");
			num_modes[cam]++;
		}
		if (modes[cam] & (0x1 << 27)){ 
			printf("MODE_1024x768_RGB supported\n");
			mode_code[cam][num_modes[cam]]= MODE_1024x768_RGB ;
			strcpy(mode_string[cam][num_modes[cam]],"MODE_1024x768_RGB");
			num_modes[cam]++;
		}
		if (modes[cam] & (0x1 << 26)){ 
			printf("MODE_1024x768_MONO supported\n");
			mode_code[cam][num_modes[cam]]= MODE_1024x768_MONO;
			strcpy(mode_string[cam][num_modes[cam]],"MODE_1024x768_MONO");
			num_modes[cam]++;
		}
		if (modes[cam] & (0x1 << 25)){ 
			printf("MODE_800x600_MONO16 supported\n");
			mode_code[cam][num_modes[cam]]=MODE_800x600_MONO16  ;
			strcpy(mode_string[cam][num_modes[cam]],"MODE_800x600_MONO16");
			num_modes[cam]++;
		}
		if (modes[cam] & (0x1 << 24)){ 
			printf("MODE_1024x768_MONO16 supported\n");
			mode_code[cam][num_modes[cam]]= MODE_1024x768_MONO16 ;
			strcpy(mode_string[cam][num_modes[cam]],"MODE_1024x768_MONO16");
			num_modes[cam]++;
		}
	}

	/**********************************************************************/
	/*             check if format 2                                      */
	/**********************************************************************/
	if(camera_misc_info[cam].format==FORMAT_SVGA_NONCOMPRESSED_2){
		if (modes[cam] & (0x1 << 31)){ 
			printf("MODE_1280x960_YUV422 supported\n");
			mode_code[cam][num_modes[cam]]= MODE_1280x960_YUV422 ;
			strcpy(mode_string[cam][num_modes[cam]],"MODE_1280x960_YUV422");
			num_modes[cam]++;
		}
		if (modes[cam] & (0x1 << 30)){ 
			printf("MODE_1280x960_RGB supported\n");
			mode_code[cam][num_modes[cam]]= MODE_1280x960_RGB ;
			strcpy(mode_string[cam][num_modes[cam]],"MODE_1280x960_RGB");
			num_modes[cam]++;
		}
		if (modes[cam] & (0x1 << 29)){ 
			printf("MODE_1280x960_MONO supported\n");
			mode_code[cam][num_modes[cam]]=MODE_1280x960_MONO  ;
			strcpy(mode_string[cam][num_modes[cam]],"MODE_1280x960_MONO");
			num_modes[cam]++;
		}
		if (modes[cam] & (0x1 << 28)){ 
			printf("MODE_1600x1200_YUV422 supported\n");
			mode_code[cam][num_modes[cam]]= MODE_1600x1200_YUV422 ;
			strcpy(mode_string[cam][num_modes[cam]],"MODE_1600x1200_YUV422");
			num_modes[cam]++;
		}
		if (modes[cam] & (0x1 << 27)){ 
			printf("MODE_1600x1200_RGB supported\n");
			mode_code[cam][num_modes[cam]]= MODE_1600x1200_RGB ;
			strcpy(mode_string[cam][num_modes[cam]],"MODE_1600x1200_RGB");
			num_modes[cam]++;
		}
		if (modes[cam] & (0x1 << 26)){ 
			printf("MODE_1600x1200_MONO supported\n");
			mode_code[cam][num_modes[cam]]= MODE_1600x1200_MONO;
			strcpy(mode_string[cam][num_modes[cam]],"MODE_1600x1200_MONO");
			num_modes[cam]++;
		}
		if (modes[cam] & (0x1 << 25)){ 
			printf("MODE_1280x960_MONO16 supported\n");
			mode_code[cam][num_modes[cam]]= MODE_1280x960_MONO16;
			strcpy(mode_string[cam][num_modes[cam]],"MODE_1280x960_MONO16");
			num_modes[cam]++;
		}
		if (modes[cam] & (0x1 << 24)){ 
			printf("MODE_1600x1200_MONO16 supported\n");
			mode_code[cam][num_modes[cam]]= MODE_1600x1200_MONO16 ;
			strcpy(mode_string[cam][num_modes[cam]],"MODE_1600x1200_MONO16");
			num_modes[cam]++;
		}
	}
	/**********************************************************************/
	/*             check if format 6                                      */
	/**********************************************************************/
	if(camera_misc_info[cam].format==FORMAT_STILL_IMAGE){
		if (modes[cam] & (0x1 << 31)){ 
			printf("MODE_EXIF supported\n");
			mode_code[cam][num_modes[cam]]= MODE_EXIF ;
			strcpy(mode_string[cam][num_modes[cam]],"MODE_EXIF");
			num_modes[cam]++;
		}
	}
	/**********************************************************************/
	/*             check if format 7                                      */
	/**********************************************************************/
	if(camera_misc_info[cam].format==FORMAT_SCALABLE_IMAGE_SIZE){
		if (modes[cam] & (0x1 << 31)){ 
			printf("MODE_FORMAT7_0 supported\n");
			mode_code[cam][num_modes[cam]]=MODE_FORMAT7_0  ;
			strcpy(mode_string[cam][num_modes[cam]],"MODE_FORMAT7_0");
			num_modes[cam]++;
		}
		if (modes[cam] & (0x1 << 30)){ 
			printf("MODE_FORMAT7_1 supported\n");
			mode_code[cam][num_modes[cam]]= MODE_FORMAT7_1 ;
			strcpy(mode_string[cam][num_modes[cam]],"MODE_FORMAT7_1");
			num_modes[cam]++;
		}
		if (modes[cam] & (0x1 << 29)){ 
			printf("MODE_FORMAT7_2 supported\n");
			mode_code[cam][num_modes[cam]]= MODE_FORMAT7_2 ;
			strcpy(mode_string[cam][num_modes[cam]],"MODE_FORMAT7_2");
			num_modes[cam]++;
		}
		if (modes[cam] & (0x1 << 28)){ 
			printf("MODE_FORMAT7_3 supported\n");
			mode_code[cam][num_modes[cam]]= MODE_FORMAT7_3 ;
			strcpy(mode_string[cam][num_modes[cam]],"MODE_FORMAT7_3");
			num_modes[cam]++;
		}
		if (modes[cam] & (0x1 << 27)){ 
			printf("MODE_FORMAT7_4 supported\n");
			mode_code[cam][num_modes[cam]]= MODE_FORMAT7_4 ;
			strcpy(mode_string[cam][num_modes[cam]],"MODE_FORMAT7_4");
			num_modes[cam]++;
		}
		if (modes[cam] & (0x1 << 26)){ 
			printf("MODE_FORMAT7_5 supported\n");
			mode_code[cam][num_modes[cam]]= MODE_FORMAT7_5 ;
			strcpy(mode_string[cam][num_modes[cam]],"MODE_FORMAT7_5");
			num_modes[cam]++;
		}
		if (modes[cam] & (0x1 << 25)){ 
			printf("MODE_FORMAT7_6 supported\n");
			mode_code[cam][num_modes[cam]]= MODE_FORMAT7_6 ;
			strcpy(mode_string[cam][num_modes[cam]],"MODE_FORMAT7_6");
			num_modes[cam]++;
		}
		if (modes[cam] & (0x1 << 24)){ 
			printf("MODE_FORMAT7_7 supported\n");
			mode_code[cam][num_modes[cam]]= MODE_FORMAT7_7 ;
			strcpy(mode_string[cam][num_modes[cam]],"MODE_FORMAT7_7");
			num_modes[cam]++;
		}
	}
	return(0);
}

/**********************************************************************/
/*             Check available formats                                */
/**********************************************************************/
int check_available_formats(int cam) {

	/**********************************************************************/
	/*               Get camera supported formats                         */
	/**********************************************************************/
	if (dc1394_query_supported_formats(handle, camera[cam].node, &formats[cam]) != DC1394_SUCCESS) {
		fprintf( stderr, "unable to get camera formats\n");
       		return(S_db_badField);
	}

	num_formats[cam] = 0;
	if (formats[cam] & (0x1 <<31)) {
		printf("Format 0 (VGA_NONCOMPRESSED) supported\n");
		format_code[cam][num_formats[cam]]= FORMAT_VGA_NONCOMPRESSED;
		strcpy(format_string[cam][num_formats[cam]],"VGA_NONCOMPRESSED");
		num_formats[cam]++;
	}

	if (formats[cam] & (0x1 << 30)) {
		printf("Format 1 supported\n");
		format_code[cam][num_formats[cam]]= FORMAT_SVGA_NONCOMPRESSED_1;
		strcpy(format_string[cam][num_formats[cam]],"SVGA_NONCOMPRESSED_1");
		num_formats[cam]++;
	}

	if (formats[cam] & (0x1 << 29)) {
		printf("Format 2 supported\n");
		format_code[cam][num_formats[cam]]= FORMAT_SVGA_NONCOMPRESSED_2;
		strcpy(format_string[cam][num_formats[cam]],"SVGA_NONCOMPRESSED_2");
		num_formats[cam]++;
	}

	if (formats[cam] & (0x1 << 25)) {
		printf("Format 6 supported\n");
		num_formats[cam]++;
	}

	if (formats[cam] & (0x1 << 24)) {
		printf("Format 7 supported\n");
		format_code[cam][num_formats[cam]]= FORMAT_SCALABLE_IMAGE_SIZE;
		strcpy(format_string[cam][num_formats[cam]],"SCALABLE_IMAGE_SIZE");
		num_formats[cam]++;
	}
	return(0);
}

static long init_camera(int cam) {

    unsigned int ch,sp;
    char camstring[80];

   if (init_camera_done[cam] == 0){
	printf("init_camera\n");

	threshold[cam] = 1.0;
	low_thresh[cam] = 0;
	if(dc1394_get_camera_misc_info(handle,camera_nodes[cam],&camera_misc_info[cam])!=DC1394_SUCCESS) {
		printf("error getting info set \n");
	}
	printf("format = %d\n",camera_misc_info[cam].format);
	printf("mode = %d\n",camera_misc_info[cam].mode);
	printf("framerate = %d\n",camera_misc_info[cam].framerate);

	sprintf(camstring,"/dev/video1394/%d",cam);

	printf("camstring= %s\n",camstring);


	if (dc1394_dma_setup_capture(\
		handle,\
		camera_nodes[cam], \
		cam, \
		camera_misc_info[cam].format, \
		camera_misc_info[cam].mode, \
		SPEED_400, \
		36, \
		10, \
		/*0, \*/
		0, \
		camstring, \
		&camera[cam])!=DC1394_SUCCESS) {
	    	fprintf( stderr,"unable to setup camera-\n");
	        return(S_db_badField);
	}

   	if (dc1394_get_iso_channel_and_speed(handle, camera[cam].node, &ch,&sp) != DC1394_SUCCESS) {
		fprintf( stderr, "unable to get iso chan and speed\n");
        	return(S_db_badField);
   	}
	printf("speed=%d\n",sp);
/*      ######################################
        Here I force the filedescriptor to close upon calling exec*/
        int flags;
        flags = fcntl(camera[cam].dma_fd, F_GETFD);
        if (flags == -1)
        {
                fprintf(stderr, "Shit, can't get FD\n");
        }
        flags = FD_CLOEXEC;
        if (fcntl(camera[cam].dma_fd, F_SETFD, flags) == -1)
        {
                fprintf(stderr, "Shit, can't set FD to FD_CLOEXEC\n");
        }

	/**********************************************************************/
	/*               Get camera Video Mode                                */
	/**********************************************************************/
   	if (dc1394_get_video_mode(handle, camera[cam].node, &mode[cam]) != DC1394_SUCCESS) {
		fprintf( stderr, "unable to get video mode\n");
        	return(S_db_badField);
   	}

	printf("format = %d \n",camera_misc_info[cam].format);

	/**********************************************************************/
	/*             check if format 0                                      */
	/**********************************************************************/
	if(camera_misc_info[cam].format==FORMAT_VGA_NONCOMPRESSED){
		switch (camera_misc_info[cam].mode) {
			case MODE_160x120_YUV444 : {
				width[cam]=160;
				height[cam]=120;
				bpp[cam] = 2;
				code[cam]=2;
				break;
			}
			case MODE_320x240_YUV422 : {
				width[cam]=320;
				height[cam]=240;
				bpp[cam] = 2;
				code[cam]=2;
				break;
			}
			case MODE_640x480_YUV411 : {
				width[cam]=640;
				height[cam]=480;
				bpp[cam] = 2;
				code[cam]=2;
				break;
			}
			case MODE_640x480_YUV422 : {
				width[cam]=640;
				height[cam]=480;
				bpp[cam] = 2;
				code[cam]=2;
				break;
			}
			case MODE_640x480_RGB : {
				width[cam]=640;
				height[cam]=480;
				bpp[cam] = 3;
				code[cam]=3;
				printf("mode 640_480_RGB bpp=%d\n",bpp[cam]);
				break;
			}
			case MODE_640x480_MONO : {
				width[cam]=640;
				height[cam]=480;
				bpp[cam] = 1;
				code[cam]=1;
				printf("mode 640_480_MONO bpp=%d\n",bpp[cam]);
				break;
			}
			case MODE_640x480_MONO16 : {
				width[cam]=640;
				height[cam]=480;
				bpp[cam] = 2;
				code[cam]=1;
				printf("mode 640_480_MONO16 bpp=%d\n",bpp[cam]);
				break;
			}
		}
		size[cam]= width[cam]*height[cam];
		maxwidth[cam]=width[cam];
		maxheight[cam]=height[cam];
		printf("format 0 : size=%d\n",size[cam]);
	}

	/**********************************************************************/
	/*             check if format 1                                      */
	/**********************************************************************/
	if(camera_misc_info[cam].format==FORMAT_SVGA_NONCOMPRESSED_1){
		switch (camera_misc_info[cam].mode) {
			case MODE_800x600_YUV422 : {
				width[cam]=800;
				height[cam]=600;
				bpp[cam] = 2;
				code[cam]=2;
				break;
			}
			case MODE_800x600_RGB : {
				width[cam]=800;
				height[cam]=600;
				bpp[cam] = 3;
				code[cam]=3;
				break;
			}
			case MODE_800x600_MONO : {
				width[cam]=800;
				height[cam]=600;
				bpp[cam] = 1;
				code[cam]=1;
				break;
			}
			case MODE_1024x768_YUV422 : {
				width[cam]=1024;
				height[cam]=768;
				bpp[cam] = 2;
				code[cam]=2;
				break;
			}
			case MODE_1024x768_RGB : {
				width[cam]=1024;
				height[cam]=768;
				bpp[cam] = 3;
				code[cam]=3;
				break;
			}
			case MODE_1024x768_MONO : {
				width[cam]=1024;
				height[cam]=768;
				bpp[cam] = 1;
				code[cam]=1;
				break;
			}
			case MODE_800x600_MONO16 : {
				width[cam]=800;
				height[cam]=600;
				bpp[cam] = 2;
				code[cam]=1;
				break;
			}
			case MODE_1024x768_MONO16 : {
				width[cam]=1024;
				height[cam]=768;
				bpp[cam] = 2;
				code[cam]=1;
				break;
			}
		}
		size[cam]= width[cam]*height[cam];
		maxwidth[cam]=width[cam];
		maxheight[cam]=height[cam];
		printf("format 1 : size=%d\n",size[cam]);
	}

	/**********************************************************************/
	/*             check if format 2                                      */
	/**********************************************************************/
	if(camera_misc_info[cam].format==FORMAT_SVGA_NONCOMPRESSED_2){
		switch (camera_misc_info[cam].mode) {
			case MODE_1280x960_YUV422 : {
				width[cam]=1280;
				height[cam]=960;
				bpp[cam] = 2;
				code[cam]=2;
				break;
			}
		}
		size[cam]= width[cam]*height[cam];
		maxwidth[cam]=width[cam];
		maxheight[cam]=height[cam];
		printf("format 2 : size=%d\n",size[cam]);
	}

	/**********************************************************************/
	/*             check if format 7 (scalable)                           */
	/**********************************************************************/
	if(camera_misc_info[cam].format==FORMAT_SCALABLE_IMAGE_SIZE){
		printf("format 7\n");
		dc1394_query_format7_max_image_size(handle,camera_nodes[cam],camera_misc_info[cam].mode,&width[cam],&height[cam]);
		switch (camera_misc_info[cam].mode) {
			case  MODE_FORMAT7_0 : {
				/*
				bpp[cam] = 1;
				*/
				bpp[cam] = 2;
				code[cam]=2;
				printf("mode 7_0 bpp=%d\n",bpp[cam]);
				break;
			}
			case  MODE_FORMAT7_1 : {
				bpp[cam] = 2;
				code[cam]=2;
				printf("mode 7_1 bpp=%d\n",bpp[cam]);
				break;
			}
			case  MODE_FORMAT7_2 : {
				bpp[cam] = 2;
				code[cam]=2;
				printf("mode 7_2 bpp=%d\n",bpp[cam]);
				break;
			}
			case  MODE_FORMAT7_3 : {
				bpp[cam] = 2;
				code[cam]=2;
				printf("mode 7_3 bpp=%d\n",bpp[cam]);
				break;
			}
			case  MODE_FORMAT7_4 : {
				bpp[cam] = 2;
				code[cam]=2;
				printf("mode 7_4 bpp=%d\n",bpp[cam]);
				break;
			}
			case  MODE_FORMAT7_5 : {
				bpp[cam] = 2;
				code[cam]=2;
				printf("mode 7_5 bpp=%d\n",bpp[cam]);
				break;
			}
			case  MODE_FORMAT7_6 : {
				bpp[cam] = 2;
				code[cam]=2;
				printf("mode 7_6 bpp=%d\n",bpp[cam]);
				break;
			}
			case  MODE_FORMAT7_7 : {
				bpp[cam] = 2;
				code[cam]=2;
				printf("mode 7_7 bpp=%d\n",bpp[cam]);
				break;
			}
		}
		size[cam]= width[cam]*height[cam];
		maxwidth[cam]=width[cam];
		maxheight[cam]=height[cam];
		printf("mode=%d hsize=%d, vsize=%d bytes_per_pixel=%d\n",camera_misc_info[cam].mode,width[cam],height[cam],bpp[cam]);
	}


	/**********************************************************************/
	/*               Get camera trigger_on_off                          */
	/**********************************************************************/
   	if (dc1394_get_trigger_on_off(handle, camera[cam].node, &trigger_on_off) != DC1394_SUCCESS) {
		fprintf( stderr, "unable to get trigger_on_off\n");
   	}
	printf("trigger_on_off=%d\n",trigger_on_off);

	/**********************************************************************/
	/*               Get camera trigger_polarity                          */
	/**********************************************************************/
   	if (dc1394_get_trigger_polarity(handle, camera[cam].node, &trigger_polarity) != DC1394_SUCCESS) {
		fprintf( stderr, "unable to get trigger_polarity\n");
   	}
	printf("trigger_polarity=%d\n",trigger_polarity);

	/**********************************************************************/
	/*               Get camera trigger_mode                              */
	/**********************************************************************/
   	if (dc1394_get_trigger_mode(handle, camera[cam].node, &trigger_mode) != DC1394_SUCCESS) {
		fprintf( stderr, "unable to get video trigger_mode\n");
   	}
	printf("trigger_mode=%d\n",trigger_mode);

	/**********************************************************************/
	/*               Get camera framerate                                 */
	/**********************************************************************/
   	if (dc1394_get_video_framerate(handle, camera[cam].node, &framerate) != DC1394_SUCCESS) {
		fprintf( stderr, "unable to get video framerate\n");
   	}

	/**********************************************************************/
	/*               Get camera format                                    */
	/**********************************************************************/
	if (dc1394_get_video_format(handle, camera[cam].node, &format) != DC1394_SUCCESS) {
		fprintf( stderr, "unable to get video format\n");
       		return(S_db_badField);
   	}

	/**********************************************************************/
	/*               Get camera gain                                      */
	/**********************************************************************/
   	if (dc1394_get_gain(handle, camera[cam].node, &gain) != DC1394_SUCCESS) {
		fprintf( stderr, "unable to get gain\n");
        	return(S_db_badField);
   	}

        /**********************************************************************/
        /*               Get camera shutter (AA)                              */
        /**********************************************************************/
        if (dc1394_get_shutter(handle, camera[cam].node, &shutter) != DC1394_SUCCESS) {
                fprintf( stderr, "unable to get shutter\n");
                return(S_db_badField);
        }


	/**********************************************************************/
	/*               Get camera Brightness                                */
	/**********************************************************************/
   	if (dc1394_get_brightness(handle, camera[cam].node, &brightness) != DC1394_SUCCESS) {
		fprintf( stderr, "unable to get brightness\n");
        	return(S_db_badField);
   	}

	/*--------------------------------------------------------------------- */
	/*  query the camera to determine the Bayer pattern			*/
   
	/*----------------------------------------------------------------------*/
	if(!(ret=GetCameraControlRegister(handle, camera[cam].node, BAYER_PATTERN_REG, &qValue ))) {
	
   		switch( qValue ) {
			case 0x42474752:  /* BGGR */
				pattern = 1;
				break;
			case 0x47524247:  /* GRBG */
				pattern = 2;
        			break;
     			case 0x52474742:  /* RGGB */
        			pattern = 3;
        			break;
      			case 0x47425247:  /* GBRG */
         			pattern = 4;
         			break;
      			case 0x59595959:  /* BW */
         			pattern = 0;                
         			break;
		}
	}
	else {

		fprintf( stderr, "unable to get Bayer pattern\n");
		return(S_db_badField);
	}

	/**********************************************************************/
	/*               Get camera Exposure                                  */
	/**********************************************************************/
   	if (dc1394_get_exposure(handle, camera[cam].node, &exposure) != DC1394_SUCCESS) {
		fprintf( stderr, "unable to get exposure\n");
        	return(S_db_badField);
   	}

	/**********************************************************************/
	/*               Get camera Vendor and Model strings                  */
	/**********************************************************************/
	if (dc1394_get_camera_info(handle, camera[cam].node, &info) != DC1394_SUCCESS) {
		fprintf( stderr, "unable to get camera info\n");
       		return(S_db_badField);
   	}
	strcpy(vendor, info.vendor);
	strcpy(model, info.model);

	/*-------------------------------------------------------------------
	*  have the camera start sending us data
	*---------------------------------------------------------------------*/
	printf("will send data\n");
	if (dc1394_start_iso_transmission(handle,camera[cam].node) !=DC1394_SUCCESS){
		fprintf( stderr, "unable to start camera iso transmission\n");
		dc1394_release_camera(handle,&camera[cam]);
	        return(S_db_badField);
	}

	init_camera_done[cam]=1;
   }
   return(0);
}
/****************************************************************************/
/*                      AO                                                  */
/****************************************************************************/

static long init_ao()
{
	init_handle();
	return(0);
}

static long init_record_ao(aoRecord *pao)
{
	int cam;
	struct vmeio *pvmeio;
	pvmeio = (struct vmeio *)&(pao->out.value);
	cam = pvmeio->card;

	init_camera(cam);

	pao->eslo = 1.0;
	pao->roff = 0.0;

	return(2);
}

static long write_ao(aoRecord *pao)
{

	int cam;
	struct vmeio *pvmeio;
	pvmeio = (struct vmeio *)&(pao->out.value);
	cam = pvmeio->card;

	if(strstr(pvmeio->parm,"gain")){
		gain = (unsigned int)pao->rval;
   		if (dc1394_set_gain(handle, camera[cam].node, gain) != DC1394_SUCCESS) {
			fprintf( stderr, "unable to set gain\n");
        		return(S_db_badField);
   		}
	}
/*		Add shutter control (AA)		*/		
        if(strstr(pvmeio->parm,"shutter")){
                shutter = (unsigned int)pao->rval;
                if (dc1394_set_shutter(handle, camera[cam].node, shutter) != DC1394_SUCCESS) {
                        fprintf( stderr, "unable to set shutter\n");
                        return(S_db_badField);
                }
        }

        if(strstr(pvmeio->parm,"ext_sCol")){
		pao->hopr = width[cam];
                ext_sCol[cam] = pao->val;
        }

        if(strstr(pvmeio->parm,"ext_eCol")){
		 pao->hopr = width[cam];
                ext_eCol[cam] = pao->val;
        }

        if(strstr(pvmeio->parm,"ext_sLine")){
		 pao->hopr = height[cam];
                ext_sLine[cam] = pao->val;
        }

        if(strstr(pvmeio->parm,"ext_eLine")){
		 pao->hopr = height[cam];
                ext_eLine[cam] = pao->val;
        }

	if(strstr(pvmeio->parm,"threshold")){
		threshold[cam] = pao->val;
	}

	if(strstr(pvmeio->parm,"low_thresh")){
		low_thresh[cam] = pao->val;
	}

	if(strstr(pvmeio->parm,"exposure")){
		exposure = (unsigned int)pao->rval;
   		if (dc1394_set_exposure(handle, camera[cam].node, exposure) != DC1394_SUCCESS) {
			fprintf( stderr, "unable to set exposure\n");
        		return(S_db_badField);
   		}
	}

	if(strstr(pvmeio->parm,"width")){
		width[cam] = (unsigned int)pao->rval;
		size[cam] = width[cam] * height[cam];
	}

	if(strstr(pvmeio->parm,"height")){
		height[cam] = (unsigned int)pao->rval;
		size[cam] = width[cam] * height[cam];
	}

	if(strstr(pvmeio->parm,"woffset")){
		pao->hopr=maxwidth[cam]-width[cam];
		if(pao->rval < maxwidth[cam]-width[cam]){
			woffset[cam] = (unsigned int)pao->rval;
		}
	}

	if(strstr(pvmeio->parm,"hoffset")){
		if(pao->rval < maxheight[cam]-height[cam]){
			hoffset[cam] = (unsigned int)pao->rval;
		}
	}

	return(0);
}

static long linconv_ao( aoRecord *pao, int after) {
   if (!after)
        return(0);
   pao->eslo = 1.0;
   pao->roff = 0.0;
   return(0);
}




/****************************************************************************/
/*                      MBBO                                                */
/****************************************************************************/

static long init_mbbo()
{
	init_handle();
	return(0);
}

static long init_record_mbbo(mbboRecord *pmbbo)
{
	int cam;
	struct vmeio *pvmeio;
	pvmeio = (struct vmeio *)&(pmbbo->out.value);
	cam = pvmeio->card;

	init_camera(cam);

	if(strstr(pvmeio->parm,"trigger_on_off")){
		pmbbo->nobt = 16;
		pmbbo->zrvl = 0;
		pmbbo->onvl = 1;
		strcpy(pmbbo->zrst,"off");
		strcpy(pmbbo->onst,"on");
	}

        if(strstr(pvmeio->parm,"bgs")){
                pmbbo->nobt = 8;
                pmbbo->zrvl = 0;
                pmbbo->onvl = 1;
                strcpy(pmbbo->zrst,"BGS OFF");
                strcpy(pmbbo->onst,"BGS ON");
        }

        if(strstr(pvmeio->parm,"man_auto")){
                pmbbo->nobt = 8;
                pmbbo->zrvl = 0;
                pmbbo->onvl = 1;
                strcpy(pmbbo->zrst,"AUTO");
                strcpy(pmbbo->onst,"MANU");
        }

	if(strstr(pvmeio->parm,"trigger_polarity")){
		pmbbo->nobt = 16;
		pmbbo->zrvl = 0;
		pmbbo->onvl = 1;
		strcpy(pmbbo->zrst,"positive");
		strcpy(pmbbo->onst,"negative");
	}

	if(strstr(pvmeio->parm,"trigger_mod")){
		pmbbo->nobt = 16;
		pmbbo->zrvl = 352;
		pmbbo->onvl = 353;
		pmbbo->twvl = 354;
		pmbbo->thvl = 355;
		strcpy(pmbbo->zrst,"TRIGGER_MODE_0");
		strcpy(pmbbo->onst,"TRIGGER_MODE_1");
		strcpy(pmbbo->twst,"TRIGGER_MODE_2");
		strcpy(pmbbo->thst,"TRIGGER_MODE_3");
	}

	if(strstr(pvmeio->parm,"stopstart")){
		pmbbo->nobt = 1;
		pmbbo->zrvl = 0;
		pmbbo->onvl = 1;
		strcpy(pmbbo->zrst,"stop");
		strcpy(pmbbo->onst,"start");
	}

	if(strstr(pvmeio->parm,"framerate")){
		pmbbo->nobt = 8;
		pmbbo->zrvl = 32;
		pmbbo->onvl = 33;
		pmbbo->twvl = 34;
		pmbbo->thvl = 35;
		pmbbo->frvl = 36;
		pmbbo->fvvl = 37;
		strcpy(pmbbo->zrst,"1.875");
		strcpy(pmbbo->onst,"3.75");
		strcpy(pmbbo->twst,"7.5");
		strcpy(pmbbo->thst,"15");
		strcpy(pmbbo->frst,"30");	
		strcpy(pmbbo->fvst,"60");
		
	}
                                                                               
	/**********************************************************************/
	/*                             Formats                                */
	/**********************************************************************/
	if(strstr(pvmeio->parm,"format")){
		check_available_formats(cam);
		printf("number of supported formats=%d\n",num_formats[cam]);
		pmbbo->nobt = 16;
		if(num_formats[cam] >= 1) {
			pmbbo->zrvl = format_code[cam][0];
			strncpy(pmbbo->zrst,format_string[cam][0],16);
		}
		if(num_formats[cam] >= 2) {
			pmbbo->onvl = format_code[cam][1];
			strncpy(pmbbo->onst,format_string[cam][1],16);
		}
		if(num_formats[cam] >= 3) {
			pmbbo->twvl = format_code[cam][2];
			strncpy(pmbbo->twst,format_string[cam][2],16);
		}
		if(num_formats[cam] >= 4) {
			pmbbo->frvl = format_code[cam][3];
			strncpy(pmbbo->frst,format_string[cam][3],16);
		}
		if(num_formats[cam] >= 5) {
			pmbbo->fvvl = format_code[cam][4];
			strncpy(pmbbo->fvst,format_string[cam][4],16);
		}
		if(num_formats[cam] >= 6) {
			pmbbo->sxvl = format_code[cam][5];
			strncpy(pmbbo->sxst,format_string[cam][5],16);
		}
	}

	/**********************************************************************/
	/*                             Modes                                  */
	/**********************************************************************/
	if(strstr(pvmeio->parm,"mode")){
		check_available_modes(cam);
		printf("number of supported modes=%d\n",num_modes[cam]);
		pmbbo->nobt = 16;
		if(num_modes[cam] >= 1) {
			pmbbo->zrvl = mode_code[cam][0];
			strncpy(pmbbo->zrst,mode_string[cam][0],16);
		}
		if(num_modes[cam] >= 2) {
			pmbbo->onvl = mode_code[cam][1];
			strncpy(pmbbo->onst,mode_string[cam][1],16);
		}
		if(num_modes[cam] >= 3) {
			pmbbo->twvl = mode_code[cam][2];
			strncpy(pmbbo->twst,mode_string[cam][2],16);
		}
		if(num_modes[cam] >= 4) {
			pmbbo->frvl = mode_code[cam][3];
			strncpy(pmbbo->frst,mode_string[cam][3],16);
		}
		if(num_modes[cam] >= 5) {
			pmbbo->fvvl = mode_code[cam][4];
			strncpy(pmbbo->fvst,mode_string[cam][4],16);
		}
		if(num_modes[cam] >= 6) {
			pmbbo->sxvl = mode_code[cam][5];
			strncpy(pmbbo->sxst,mode_string[cam][5],16);
		}
	}
	return(0);
}

static long write_mbbo(mbboRecord *pmbbo)
{
	/*int 	framerate;*/
	/*int 	format=0;*/
	int 	set_mode;
	int     cam;
	struct vmeio *pvmeio;
	pvmeio = (struct vmeio *)&(pmbbo->out.value);
	cam = pvmeio->card;

	if(strstr(pvmeio->parm,"trigger_polarity")){
		set_trigger_polarity = (int)pmbbo->rval;
   		if (dc1394_set_trigger_polarity(handle, camera[cam].node, set_trigger_polarity) != DC1394_SUCCESS) {
			fprintf( stderr, "unable to set trigger_polarity\n");
		}
   	}

        if(strstr(pvmeio->parm,"bgs")){
                bgs[cam] = (int)pmbbo->rval;
        }

        if(strstr(pvmeio->parm,"man_auto")){
                man_auto[cam] = (int)pmbbo->rval;
        }

	if(strstr(pvmeio->parm,"trigger_mod")){
		set_trigger_mode = (int)pmbbo->rval;
   		if (dc1394_set_trigger_mode(handle, camera[cam].node, set_trigger_mode) != DC1394_SUCCESS) {
			fprintf( stderr, "unable to set trigger_mode\n");
		}
   	}

	if(strstr(pvmeio->parm,"trigger_on_off")){
		set_trigger_on_off = (int)pmbbo->rval;
   		if (dc1394_set_trigger_on_off(handle, camera[cam].node, set_trigger_on_off) != DC1394_SUCCESS) {
			fprintf( stderr, "unable to set trigger_on_off\n");
		}
   	}

	if(strstr(pvmeio->parm,"stopstart")){
		printf("stopstart=%d",(int)pmbbo->rval);
		stopstart = (int)pmbbo->rval;
		if (stopstart == 0){
   			if (dc1394_stop_iso_transmission(handle, camera[cam].node) != DC1394_SUCCESS) {
				fprintf( stderr, "unable to stop iso transmission\n");
        			return(S_db_badField);
			} 
   		}
		if (stopstart == 1){
   			if (dc1394_start_iso_transmission(handle, camera[cam].node) != DC1394_SUCCESS) {
				fprintf( stderr, "unable to start iso transmission\n");
        			return(S_db_badField);
			} 
			init_camera(cam);
   		}
	}

	if(strstr(pvmeio->parm,"framerate")){
		set_framerate = (int)pmbbo->rval;
   		if (dc1394_set_video_framerate(handle, camera[cam].node, set_framerate) != DC1394_SUCCESS) {
			fprintf( stderr, "unable to set video framerate\n");
        		return(S_db_badField);
   		}
	}

	if(strstr(pvmeio->parm,"format")){
		set_format = (int)pmbbo->rval;
   		if (dc1394_set_video_format(handle, camera[cam].node, set_format) != DC1394_SUCCESS) {
			fprintf( stderr, "unable to set video format\n");
        		return(S_db_badField);
   		}
	}

	if(strstr(pvmeio->parm,"mode")){
		printf("\nchange mode to %d\n",(int)pmbbo->rval);
		set_mode = (int)pmbbo->rval;

   		if (dc1394_set_video_mode(handle, camera[cam].node, set_mode) != DC1394_SUCCESS) {
			fprintf( stderr, "unable to set video mode\n");
        		return(S_db_badField);
   		}
	}
	return(0);
}

/****************************************************************************/
/*                      MBBI                                                */
/****************************************************************************/

static long init_mbbi()
{
	init_handle();
	return(0);
}

static long init_record_mbbi(mbbiRecord *pmbbi)
{
	int cam;
	struct vmeio *pvmeio;
	pvmeio = (struct vmeio *)&(pmbbi->inp.value);
	cam = pvmeio->card;

	init_camera(cam);

	if(strstr(pvmeio->parm,"iso_status")){
		pmbbi->nobt = 16;
		pmbbi->zrvl = 0;
		pmbbi->onvl = 1;
		strcpy(pmbbi->zrst,"off");
		strcpy(pmbbi->onst,"on");
	}

	if(strstr(pvmeio->parm,"trigger_on_off")){
		pmbbi->nobt = 16;
		pmbbi->zrvl = 0;
		pmbbi->onvl = 1;
		strcpy(pmbbi->zrst,"off");
		strcpy(pmbbi->onst,"on");
	}

	if(strstr(pvmeio->parm,"trigger_polarity")){
		pmbbi->nobt = 16;
		pmbbi->zrvl = 0;
		pmbbi->onvl = 1;
		strcpy(pmbbi->zrst,"positive");
		strcpy(pmbbi->onst,"negative");
	}

	if(strstr(pvmeio->parm,"trigger_mod")){
		pmbbi->nobt = 16;
		pmbbi->zrvl = 352;
		pmbbi->onvl = 353;
		pmbbi->twvl = 354;
		pmbbi->thvl = 355;
		strcpy(pmbbi->zrst,"TRIGGER_MODE_0");
		strcpy(pmbbi->onst,"TRIGGER_MODE_1");
		strcpy(pmbbi->twst,"TRIGGER_MODE_2");
		strcpy(pmbbi->thst,"TRIGGER_MODE_3");
	}

	if(strstr(pvmeio->parm,"framerate")){
		pmbbi->nobt = 8;
		pmbbi->zrvl = 32;
		pmbbi->onvl = 33;
		pmbbi->twvl = 34;
		pmbbi->thvl = 35;
		pmbbi->frvl = 36;
		pmbbi->fvvl = 37;
		strcpy(pmbbi->zrst,"1.875");
		strcpy(pmbbi->onst,"3.75");
		strcpy(pmbbi->twst,"7.5");
		strcpy(pmbbi->thst,"15");
		strcpy(pmbbi->frst,"30");
		strcpy(pmbbi->fvst,"60");
	}

        if(strstr(pvmeio->parm,"pattern")){
                pmbbi->nobt = 8;
                pmbbi->zrvl = 0;
                pmbbi->onvl = 1;
                pmbbi->twvl = 2;
                pmbbi->thvl = 3;
                pmbbi->frvl = 4;
                strcpy(pmbbi->zrst,"BW");
                strcpy(pmbbi->onst,"BGGR");
                strcpy(pmbbi->twst,"GRBG");
                strcpy(pmbbi->thst,"RGGB");
                strcpy(pmbbi->frst,"GBRG");
        }

	if(strstr(pvmeio->parm,"format")){
		pmbbi->nobt = 16;
		pmbbi->zrvl = 0;
		pmbbi->onvl = 384;
		pmbbi->twvl = 385;
		pmbbi->thvl = 386;
		pmbbi->frvl = 387;
		pmbbi->fvvl = 388;
		pmbbi->sxvl = 389;
		pmbbi->svvl = 390;
		pmbbi->eivl = 391;
		strcpy(pmbbi->zrst,"Error");
		strcpy(pmbbi->onst,"VGA_NONCOMPRESSED");
		strcpy(pmbbi->twst,"SVGA_NONCOMPRESSED_1");
		strcpy(pmbbi->thst,"SVGA_NONCOMPLRESSED_2");
		strcpy(pmbbi->frst,"reserved1");
		strcpy(pmbbi->fvst,"reserved1");
		strcpy(pmbbi->sxst,"reserved1");
		strcpy(pmbbi->svst,"STILL_IMAGE");
		strcpy(pmbbi->eist,"SCALABLE_IMAGE_SIZE");
	}
	if(strstr(pvmeio->parm,"mode")){
		if(camera_misc_info[cam].format==FORMAT_SCALABLE_IMAGE_SIZE){
			pmbbi->nobt = 16;
			pmbbi->zrvl = MODE_FORMAT7_0;
			pmbbi->onvl = MODE_FORMAT7_1;
			pmbbi->twvl = MODE_FORMAT7_2;
			pmbbi->thvl = MODE_FORMAT7_3;
			pmbbi->frvl = MODE_FORMAT7_4;
			pmbbi->fvvl = MODE_FORMAT7_5;
			pmbbi->sxvl = MODE_FORMAT7_6;
			pmbbi->svvl = MODE_FORMAT7_7;
			strcpy(pmbbi->zrst,"MODE_FORMAT7_0");
			strcpy(pmbbi->onst,"MODE_FORMAT7_1");
			strcpy(pmbbi->twst,"MODE_FORMAT7_2");
			strcpy(pmbbi->thst,"MODE_FORMAT7_3");
			strcpy(pmbbi->frst,"MODE_FORMAT7_4");
			strcpy(pmbbi->fvst,"MODE_FORMAT7_5");
			strcpy(pmbbi->sxst,"MODE_FORMAT7_6");
			strcpy(pmbbi->svst,"MODE_FORMAT7_7");
		}
		if(camera_misc_info[cam].format==FORMAT_VGA_NONCOMPRESSED){
			pmbbi->nobt = 16;
			pmbbi->zrvl = 0;
			pmbbi->onvl = 64;
			pmbbi->twvl = 65;
			pmbbi->thvl = 66;
			pmbbi->frvl = 67;
			pmbbi->fvvl = 68;
			pmbbi->sxvl = 69;
			pmbbi->svvl = 70;
			strcpy(pmbbi->zrst,"Error");
			strcpy(pmbbi->onst,"160x120_YUV444");
			strcpy(pmbbi->twst,"320x240_YUV422");
			strcpy(pmbbi->thst,"640x480_YUV411");
			strcpy(pmbbi->frst,"640x480_YUV422");
			strcpy(pmbbi->fvst,"640x480_RGB");
			strcpy(pmbbi->sxst,"640x480_MONO");
			strcpy(pmbbi->svst,"640x480_MONO16");
		}
		if(camera_misc_info[cam].format==FORMAT_SVGA_NONCOMPRESSED_1){
			pmbbi->nobt = 16;
			pmbbi->zrvl = 0;
			pmbbi->onvl = 96;
			pmbbi->twvl = 97;
			pmbbi->thvl = 98;
			pmbbi->frvl = 99;
			pmbbi->fvvl = 100;
			pmbbi->sxvl = 101;
			pmbbi->svvl = 102;
			pmbbi->eivl = 103;
			strcpy(pmbbi->zrst,"Error");
			strcpy(pmbbi->onst,"800x600_YUV422");
			strcpy(pmbbi->twst,"800x600_RGB");
			strcpy(pmbbi->thst,"800x600_MONO");
			strcpy(pmbbi->frst,"1024x768_YUV422");
			strcpy(pmbbi->fvst,"1024x768_RGB");
			strcpy(pmbbi->sxst,"1024x768_MONO");
			strcpy(pmbbi->svst,"800x600_MONO16");
			strcpy(pmbbi->eist,"1024x768_MONO16");
		}
	}
	return(0);
}

static long read_mbbi(mbbiRecord *pmbbi)
{
	int cam;
	struct vmeio *pvmeio;
	pvmeio = (struct vmeio *)&(pmbbi->inp.value);
	cam = pvmeio->card;

	if(strstr(pvmeio->parm,"iso_status")){
   		if (dc1394_get_iso_status(handle, camera[cam].node, (dc1394bool_t *)&iso_status) != DC1394_SUCCESS) {
			fprintf( stderr, "unable to get iso_status\n");
   		}
    		pmbbi->rval=iso_status;
    	}

        if(strstr(pvmeio->parm,"pattern")){
                pmbbi->rval=pattern;
        }	

	if(strstr(pvmeio->parm,"trigger_on_off")){
   		if (dc1394_get_trigger_on_off(handle, camera[cam].node, (dc1394bool_t *)&trigger_on_off) != DC1394_SUCCESS) {
			fprintf( stderr, "unable to get trigger_on_off\n");
   		}
    		pmbbi->rval=trigger_on_off;
    	}

	if(strstr(pvmeio->parm,"trigger_polarity")){
   		if (dc1394_get_trigger_polarity(handle, camera[cam].node, (dc1394bool_t *)&trigger_polarity) != DC1394_SUCCESS) {
			fprintf( stderr, "unable to get trigger_polarity\n");
   		}
    		pmbbi->rval=trigger_polarity;
    	}

	if(strstr(pvmeio->parm,"trigger_mod")){
   		if (dc1394_get_trigger_mode(handle, camera[cam].node, &trigger_mode) != DC1394_SUCCESS) {
			fprintf( stderr, "unable to get trigger_mode\n");
   		}
    		pmbbi->rval=trigger_mode;
    	}

	if(strstr(pvmeio->parm,"framerate")){
   		if (dc1394_get_video_framerate(handle, camera[cam].node, &framerate) != DC1394_SUCCESS) {
			fprintf( stderr, "unable to get video framerate\n");
        		return(S_db_badField);
   		}
    		pmbbi->rval=framerate;
    	}

	if(strstr(pvmeio->parm,"format")){
   		if (dc1394_get_video_format(handle, camera[cam].node, &format) != DC1394_SUCCESS) {
			fprintf( stderr, "unable to get video format\n");
        		return(S_db_badField);
   		}
    		pmbbi->rval=format;
    	}

	if(strstr(pvmeio->parm,"mode")){
   		if (dc1394_get_video_mode(handle, camera[cam].node, &mode[cam]) != DC1394_SUCCESS) {
			fprintf( stderr, "unable to get video mode\n");
        		return(S_db_badField);
   		}
    		pmbbi->rval=mode[cam];
    	}
	return(0);
}


/****************************************************************************/
/*              WAVEFORMS                                                   */
/****************************************************************************/

static long init_waveform()
{
	init_handle();
	return(0);
}

static long init_record_waveform(waveformRecord *pwf) {
	int cam;
	struct vmeio *pvmeio;
	pvmeio = (struct vmeio *)&(pwf->inp.value);
	cam = pvmeio->card;

	init_camera(cam);
	pwf->nelm = size[cam]*bpp[cam];	
	return(0);
}

static long read_waveform(waveformRecord *pwf)
{
	int cam;
	struct vmeio *pvmeio;

	int line = 0,col = 0;
	unsigned char *src;
	unsigned char *dest;
        unsigned char *tot_src;
        unsigned char *tot_dest;
	int 	lastbuf;
	int framesize;

	pvmeio = (struct vmeio *)&(pwf->inp.value);
	pwf->nord = 0;	
	cam = pvmeio->card;
	pwf->nelm = size[cam]*bpp[cam];

	if (counter == 0) 
		gettimeofday( &start, NULL );
	
	/**********************************************************/
	/*                get the image array                     */
	/**********************************************************/
	if(strstr(pvmeio->parm,"data")){
                int e = dc1394_dma_single_capture_poll(&camera[cam]);
		camera[cam].drop_frames = 1;

                if (e == DC1394_SUCCESS) {
                        dc1394_dma_done_with_buffer(&camera[cam]);
/*                        printf("Got the frame\n");*/
                        counter += 1;

                }

                if (e == DC1394_FAILURE) {
			fprintf( stderr, "Can't capture a frame\n");
                        dc1394_release_camera(handle,&camera[cam]);
                        return(S_db_badField);
                }

                if (e == DC1394_NO_FRAME) {
/*                        printf("There is no ready frame at the Buffer\n");*/
			dropped_frames[cam] = 0;
                }

/* Timing 10 captured farmes */
                if (counter == 11){

                        gettimeofday( &end, NULL );
                        int endms = end.tv_sec*1000 + end.tv_usec/1000;
                        int startms = start.tv_sec*1000 + start.tv_usec/1000;
                        int ms = endms - startms;
                        afps[cam] = (10.0*1000.0/(float)ms);
                        counter = 0;
                }

                if(camera[cam].num_dma_buffers_behind > 0) {
                        dropped_frames[cam] = camera[cam].num_dma_buffers_behind;
                }
			
		lastbuf = camera[cam].dma_last_buffer;
		lastbuf--;
		if (lastbuf == -1) lastbuf = 9;

		pwf->nelm=size[cam]*bpp[cam];
		src = (unsigned char *)camera[cam].dma_ring_buffer;

		framesize=camera[cam].dma_frame_size;

		src+=framesize*lastbuf;
		dest = (unsigned char *)pwf->bptr;	
		for (line = 0;line <height[cam];line++){
			tot_dest = dest+(line*width[cam]*bpp[cam]);
			tot_src = src+((line+hoffset[cam])*maxwidth[cam]*bpp[cam])+(woffset[cam]*bpp[cam]);
 			memcpy(tot_dest,tot_src,(size_t)width[cam]*bpp[cam]);
		}
		pwf->nord = pwf->nelm;	
/*		dc1394_dma_done_with_buffer(&camera[cam]);*/
	}

        /*****************************************************************/
        /*get the X distribution of the Refernce waveform, width and pos (AA) */
        /*****************************************************************/
        if(strstr(pvmeio->parm,"xdist_ref")){
                unsigned char *src = (unsigned char *)camera[cam].capture_buffer;
                dest_ref = (unsigned long *)pwf->bptr;
                int    bytes = bpp[cam];
                int    coding = code[cam];	

                /*****************************************************************/
                /*                                                               */
                /*      calculate the start point in the camera buffer           */
                /*      Zero the waveform array                                  */
                /*      Set nelm, hopr and lopr                                  */
                /*                                                               */
                /*****************************************************************/
                src+=((hoffset[cam]*maxwidth[cam]*bpp[cam])+woffset[cam]*bpp[cam]);
                for(col=0;col<width[cam];col++){
                        dest_ref[col] = 0;
                }
                pwf->nelm=width[cam];
                pwf->lopr=0;
                pwf->hopr=256*maxheight[cam];
                pwf->nord = pwf->nelm;

                /*****************************************************************/
                /*       Total the values in each column                         */
                /*****************************************************************/
                if (bytes == 1 && coding == 1){ /* Monochrome 8 bit */
                        for (line = 0;line<height[cam];line++){
                                for(col=0;col<width[cam];col++){
                                        if (src[col*bytes] > low_thresh[cam] ){
                                                dest_ref[col] += src[col*bytes];
						data_array_ref[line*width[cam]+col] = src[col*bytes];	
                                        }
					else
						data_array_ref[line*width[cam]+col] = 0;
                                }
                                src+=maxwidth[cam]*bytes;
                        }
                }
                if (bytes == 2 && coding == 1){ /* Monochrome 16 bit */
                        for (line = 0;line<height[cam];line++){
                                for(col=0;col<width[cam];col++){
                                        if (src[col*bytes] > low_thresh[cam] ){
                                                dest_ref[col] += src[col*bytes];
						data_array_ref[line*width[cam]+col] = src[col*bytes];
                                        }
					else
						data_array_ref[line*width[cam]+col] = 0;
                                }
                                src+=maxwidth[cam]*bytes;
                        }
                }

                if (bytes == 2 && coding == 2){  /* YUV  */
                        for (line = 0;line<height[cam];line++){
                                for(col=0;col<width[cam];col++){
                                        if (src[col*bytes+1] > low_thresh[cam] ){
                                                dest_ref[col] += src[col*bytes+1];
						data_array_ref[line*width[cam]+col] = src[col*bytes+1];
                                        }
					else
						data_array_ref[line*width[cam]+col] = 0;
                                }
                                src+=maxwidth[cam]*bytes;
                        }
                }
                if (bytes == 3 && coding == 3){  /* RGB */
                        for (line = 0;line<height[cam];line++){
                                for(col=0;col<width[cam];col++){
                                        dest_ref[col] += src[col*bytes+0];
                                        dest_ref[col] += src[col*bytes+1];
                                        dest_ref[col] += src[col*bytes+2];
                                }
                                src+=maxwidth[cam]*bytes;
                        }
                }
         }
	/**********************************************************/
	/*               get the X distribution, width and pos    */
	/**********************************************************/
	if(strstr(pvmeio->parm,"xdist")){
  		double sum=0;
		double noisesum;
		unsigned char *src = (unsigned char *)camera[cam].capture_buffer;
		unsigned long *dest = (unsigned long *)pwf->bptr;
		int    bytes = bpp[cam];
		int    coding = code[cam];
		int sIndex = 0;
		int tmp    = 0;
		max[cam] = 0;
		maxCol[cam] = 0;
		maxLine[cam] = 0;

		/*****************************************************************/
		/*                                                               */
		/*      calculate the start point in the camera buffer           */
		/*      Zero the waveform array                                  */
		/*      Set nelm, hopr and lopr                                  */
		/*                                                               */
		/*****************************************************************/
		src+=((hoffset[cam]*maxwidth[cam]*bpp[cam])+woffset[cam]*bpp[cam]);
		for(col=0;col<width[cam];col++){
 			dest[col] = 0;  
		}
		pwf->nelm=width[cam];
		pwf->lopr=0;
		pwf->hopr=256*maxheight[cam];
		pwf->nord = pwf->nelm;	
		/*****************************************************************/
		/*       Total the values in each column                         */
		/*****************************************************************/
		if (bytes == 1 && coding == 1){ /* Monochrome 8 bit */
			for (line = 0;line<height[cam];line++){
				for(col=0;col<width[cam];col++){
					if (src[col*bytes] > low_thresh[cam] ){
						data[line*width[cam]+col] = src[col*bytes];
/*                                              Check for background substraction (AA)   */
						if (bgs[cam] == 1){
							if ((data[line*width[cam]+col] - data_array_ref[line*width[cam]+col]) > 0){
								data_array_diff[line*width[cam]+col] = (data[line*width[cam]+col] - data_array_ref[line*width[cam]+col]);
								dest[col] += data_array_diff[line*width[cam]+col];
							}
							else{
								dest[col] += 0;
								data_array_diff[line*width[cam]+col] = 0;
							}
						}
						else 
	 						dest[col] += data[line*width[cam]+col];
/*                                              Find the maximum pixel intensity (AA)   */
                                                if (data[line*width[cam]+col] > max[cam]){
                                                        max[cam] = data[line*width[cam]+col];
                                                        maxCol[cam] = col;
                                                        maxLine[cam] = line;
						}
					}
				}
				src+=maxwidth[cam]*bytes;
			}
		}

		if (bytes == 2 && coding == 1){ /* Monochrome 16 bit */
			for (line = 0;line<height[cam];line++){
				for(col=0;col<width[cam];col++){
					if (src[col*bytes] > low_thresh[cam] ){
						data[line*width[cam]+col] = src[col*bytes];
/*                                              Check for background substraction (AA)   */
                                                if (bgs[cam] == 1){
                                                        if ((data[line*width[cam]+col] - data_array_ref[line*width[cam]+col]) > 0){
                                                                data_array_diff[line*width[cam]+col] = (data[line*width[cam]+col] - data_array_ref[line*width[cam]+col]);
								dest[col] +=  data_array_diff[line*width[cam]+col];
                                                }        
						else{
                                                                dest[col] += 0;
								data_array_diff[line*width[cam]+col] = 0;
						}
						}
                                                else
                                                        dest[col] += data[line*width[cam]+col];
/*						Find the maximum pixel intensity (AA)	*/ 
						if (data[line*width[cam]+col] > max[cam]){
							max[cam] = data[line*width[cam]+col];
							maxCol[cam] = col;
							maxLine[cam] = line;
						}
					}
				}
				src+=maxwidth[cam]*bytes;
			}
		}

		if (bytes == 2 && coding == 2){  /* YUV  */
			for (line = 0;line<height[cam];line++){
				for(col=0;col<width[cam];col++){
					if (src[col*bytes+1] > low_thresh[cam] ){
                                                data[line*width[cam]+col] = src[col*bytes+1];
/*                                              Check for background substraction (AA)   */
                                                if (bgs[cam] == 1){
                                                        if ((data[line*width[cam]+col] - data_array_ref[line*width[cam]+col]) > 0){
                                                                data_array_diff[line*width[cam]+col] = (data[line*width[cam]+col] - data_array_ref[line*width[cam]+col]);
                                                                dest[col] +=  data_array_diff[line*width[cam]+col];
                                                }
                                                else{
                                                                dest[col] += 0;
                                                                data_array_diff[line*width[cam]+col] = 0;
                                                }
                                                }
                                                else
                                                        dest[col] += data[line*width[cam]+col];
/*                                              Find the maximum pixel intensity (AA)   */
                                                if (data[line*width[cam]+col] > max[cam]){
                                                        max[cam] = data[line*width[cam]+col];
                                                        maxCol[cam] = col;
                                                        maxLine[cam] = line;
                                                }
                                        }
                                }
                                src+=maxwidth[cam]*bytes;
                        }
                }

		if (bytes == 3 && coding == 3){  /* RGB */
			for (line = 0;line<height[cam];line++){
				for(col=0;col<width[cam];col++){
					printf("src = %d\n", src[col*bytes+0]);
					if (src[col*bytes+0] > low_thresh[cam] )
	 					dest[col] += src[col*bytes+0];  
					if (src[col*bytes+1] > low_thresh[cam] )
 						dest[col] += src[col*bytes+1];  
					if (src[col*bytes+2] > low_thresh[cam] )
	 					dest[col] += src[col*bytes+2];  
				}
				src+=maxwidth[cam]*bytes;
		}
	}



		/*****************************************************************/
		/*       Calculate the averge pixel value                        */
		/*****************************************************************/
/*			 Find the maximum xdist intensity (Value + Location) (AA)   */
		xdistMaxSum[cam] = 0;
		xdistMaxCol[cam] = 0;
		for (col=0;col<width[cam];col++){
			sum+=dest[col];			
			if (dest[col] > xdistMaxSum[cam]){
				xdistMaxSum[cam] = dest[col];
				xdistMaxCol[cam] = col;
			}
		}
		sumTot[cam] = sum;
		xavg[cam]=sum/width[cam];
		xFWHM[cam] = xdistMaxSum[cam]/2;
		xWindow[cam] = xdistMaxSum[cam] * 0.135;   /*  86.5 % window */
		/*****************************************************************/
		/*       Calculate the width                                     */
		/*****************************************************************/
                xw[cam]=0;
		if (man_auto[cam] == 0){
/*                       Find the xdist FWHM (AA)   */
			for (col=0;col<width[cam];col++){
	                	if(dest[col] > xFWHM[cam]){
					xw[cam]++;
				}
			}
		/*****************************************************************/
		/*       Calculate the position and s/n                          */
		/*****************************************************************/
/*			Find the  xdist 86.5 % window boundaries(AA) */
			noisesum = 0;
	                for (col=0;col<width[cam];col++){
	                        if(dest[col] > xWindow[cam]) {
					if (sIndex == 0)
						sCol[cam] = col;
					sIndex += 1;
					eCol[cam] = col;
	                        } else {
        	                        noisesum+=dest[col];
                	        }
	                }
/*                      Define a new window based on the previous one (AA) */	
			tmp = sCol[cam];
			sCol[cam] = ((CSIG1*sCol[cam]) - (CSIG2*eCol[cam]));	
			eCol[cam] = ((CSIG1*eCol[cam]) - (CSIG2*tmp));
			if (sCol[cam] < 0)
				sCol[cam] = 0;
	                if (sCol[cam] > width[cam])
	                        sCol[cam] = width[cam];
	                if (eCol[cam] < 0)
	                        eCol[cam] = 0;
	                if (eCol[cam] > width[cam])
	                        eCol[cam] = width[cam];		
		} else {
			sCol[cam] = ext_sCol[cam];
			eCol[cam] = ext_eCol[cam];
/*                       Find the maximum xdist intensity (Value + Location) (AA)   */
	                xdistMaxSum[cam] = 0;
	                xdistMaxCol[cam] = 0;
	                for (col=sCol[cam];col<=eCol[cam];col++){
	                        if (dest[col] > xdistMaxSum[cam]){
        	                        xdistMaxSum[cam] = dest[col];
                	                xdistMaxCol[cam] = col;
                        	}
			}
/*                      Find the xdist FWHM (AA)   */
                        for (col=sCol[cam];col<=eCol[cam];col++){
                                if(dest[col] > xFWHM[cam])
                                        xw[cam]++;
			}
		}
			
	}

	/**********************************************************/
	/*       get the Y distribution, width and position       */
	/**********************************************************/
	if(strstr(pvmeio->parm,"ydist")){
  		double sum=0;
		unsigned char *src = (unsigned char *)camera[cam].capture_buffer;
		unsigned long *dest = (unsigned long *)pwf->bptr;
		double noisesum=0;
		int    bytes = bpp[cam];
		int    coding = code[cam];
                int sIndex = 0;
                int tmp    = 0;


		/*****************************************************************/
		/*                                                               */
		/*      calculate the start point in the camera buffer           */
		/*      Zero the waveform array                                  */
		/*      Set nelm, hopr and lopr                                  */
		/*                                                               */
		/*****************************************************************/
		src+=((hoffset[cam]*maxwidth[cam]*bpp[cam])+woffset[cam]*bpp[cam]);
		for(line=0;line<height[cam];line++){
 			dest[line] = 0;  
		}
		pwf->nelm=height[cam];
		pwf->lopr=0;
		pwf->hopr=256*maxwidth[cam];
		pwf->nord = pwf->nelm;	

		/*****************************************************************/
		/*       Total the values in each row                            */
		/*****************************************************************/
		if (coding == 1){
			for (line = 0;line<height[cam];line++){
				for(col=0;col<width[cam];col++){
					if (src[col*bytes] > low_thresh[cam] ){
/*                                              Check for background substraction (AA) Begin  */
                                                if (bgs[cam] == 1)
                                                	dest[line] += data_array_diff[line*width[cam]+col];
                                                else
							dest[line] += data[line*width[cam]+col]; 
					}
				}
				src+=maxwidth[cam]*bytes;
			}
		}
		if (bytes == 2 && coding == 2){
			for (line = 0;line<height[cam];line++){
				for(col=0;col<width[cam];col++){
					if (src[col*bytes+1] > low_thresh[cam] ){
/*                                              Check for background substraction (AA) Begin  */
                                                if (bgs[cam] == 1)
                                                	dest[line] += data_array_diff[line*width[cam]+col];
						else 
							dest[line] += data[line*width[cam]+col];
					}

				}
				src+=maxwidth[cam]*bytes;
			}
		}
		if (bytes == 3 && coding == 3){
			for (line = 0;line<height[cam];line++){
				for(col=0;col<width[cam];col++){
                                	if (src[col*bytes+0] > low_thresh[cam] )
                                                dest[line] += src[col*bytes+0];
                                        if (src[col*bytes+1] > low_thresh[cam] )
                                                dest[line] += src[col*bytes+1];
                                        if (src[col*bytes+2] > low_thresh[cam] )
                                                dest[line] += src[col*bytes+2]; 
				}
				src+=maxwidth[cam]*bytes;
			}
		}


		/*****************************************************************/
		/*       Calculate the averge pixel value                        */
		/*****************************************************************/
/*                       Find the maximum ydist intensity (Value + Location) (AA)   */
 		ydistMaxSum[cam] = 0;
  		ydistMaxLine[cam] = 0;
		for (line=0;line<height[cam];line++){
			sum+=dest[line];
                        if (dest[line] > ydistMaxSum[cam]){
                                ydistMaxSum[cam] = dest[line];
                                ydistMaxLine[cam] = line;
                        }
                }
		yavg[cam]=sum/height[cam];
                yFWHM[cam] = ydistMaxSum[cam]/2;
                yWindow[cam] = ydistMaxSum[cam] * 0.135;   /*  86.5 % window */

		/*****************************************************************/
		/*       Calculate the width                                     */
		/*****************************************************************/
/*                       Find the ydist FWHM (AA)   */
                yw[cam]=0;
		if (man_auto[cam] == 0){
	                for (line=0;line<height[cam];line++){
        	                if(dest[line] > yFWHM[cam])
                	                yw[cam]++;
	                }

		/*****************************************************************/
		/*       Calculate the position and s/n                          */
		/*****************************************************************/
/*                      Find the  ydist 86.5 % window boundaries(AA) */
	                sIndex = 0;
	                for (line=0;line<height[cam];line++){
        	                if(dest[line] > yWindow[cam]) {
                	                if (sIndex == 0)
                        	                sLine[cam] = line;
	                               	sIndex += 1;
        	                        eLine[cam] = line;
                	        	} 
					else
                                		noisesum+=dest[line];
	                }
/*                      Define a new window based on the previous one (AA) */
	                tmp = sLine[cam];
	                sLine[cam] = ((CSIG1*sLine[cam]) - (CSIG2*eLine[cam]));
	                eLine[cam] = ((CSIG1*eLine[cam]) - (CSIG2*tmp));
	                if (sLine[cam] < 0)
	                        sLine[cam] = 0;
	                if (sLine[cam] > height[cam])
        	                sLine[cam] = height[cam];
	                if (eLine[cam] < 0)
        	                eLine[cam] = 0;
	                if (eLine[cam] > height[cam])
        	                eLine[cam] = height[cam];		
		} else {
                        sLine[cam] = ext_sLine[cam];
                        eLine[cam] = ext_eLine[cam];
	                ydistMaxSum[cam] = 0;
	                ydistMaxLine[cam] = 0;
	                for (line=sLine[cam];line<eLine[cam];line++){
	                        if (dest[line] > ydistMaxSum[cam]){
	                                ydistMaxSum[cam] = dest[line];
	                                ydistMaxLine[cam] = line;
	                        }
	                }
	                yFWHM[cam] = ydistMaxSum[cam]/2;
/*                      Find the ydist FWHM (AA)   */
	                for (line=sLine[cam];line<=eLine[cam];line++){
	                	if(dest[line] > yFWHM[cam])
	                 	yw[cam]++;	
			}
		}
	}

	return(0);
}

/****************************************************************************/
/*                      STRINGIN                                            */
/****************************************************************************/

static long init_record_stringin(stringinRecord *psi)
{
	int cam;
	struct vmeio *pvmeio;

	pvmeio = (struct vmeio *)&(psi->inp.value);
	cam = pvmeio->card;

    	init_camera(cam);
	return(0);
}

static long read_stringin(stringinRecord *psi)
{
	struct vmeio *pvmeio;
	pvmeio = (struct vmeio *)&(psi->inp.value);

	if(strstr(pvmeio->parm,"vendor")){
		strcpy(psi->val, vendor);
	}

	if(strstr(pvmeio->parm,"model")){
		strcpy(psi->val, model);
	}

	return(0);
}

/****************************************************************************/
/*                      AI                                                  */
/****************************************************************************/

static long init_ai()
{
    	init_handle();
	return(0);
}


static long init_record_ai(aiRecord *pai)
{
    int cam;
    struct vmeio *pvmeio;

    pvmeio = (struct vmeio *)&(pai->inp.value);
    cam = pvmeio->card;

    /* set slope of engineering unit conversion  assume 16 bits  */
    pai->eslo = (pai->eguf - pai->egul) / 65535.0;

    init_camera(cam);

   if(strstr(pvmeio->parm,"xp")){
    	pai->hopr=width[cam];
    }

   if(strstr(pvmeio->parm,"sCol")){
        pai->hopr=width[cam];
    }

   if(strstr(pvmeio->parm,"eCol")){
        pai->hopr=width[cam];
    }

   if(strstr(pvmeio->parm,"yp")){
    	pai->hopr=height[cam];
    }

   if(strstr(pvmeio->parm,"sLine")){
        pai->hopr=height[cam];
    }

   if(strstr(pvmeio->parm,"eLine")){
        pai->hopr=height[cam];
    }

    return(0);
}

static long read_ai(aiRecord *pai)
{
    int cam;
    struct vmeio *pvmeio;

   pvmeio = (struct vmeio *)&(pai->inp.value);
   cam = pvmeio->card;

   if(strstr(pvmeio->parm,"version")){
   	if (dc1394_get_sw_version(handle, camera[cam].node, &sw_version) != DC1394_SUCCESS) {
		fprintf( stderr, "unable to get sw_version \n");
        	return(S_db_badField);
   	}
    	pai->val=sw_version;
    	return(2);
   }


   if(strstr(pvmeio->parm,"xavg")){
    	pai->val=xavg[cam];
    	return(2);
   }

   if(strstr(pvmeio->parm,"yavg")){
    	pai->val=yavg[cam];
    	return(2);
   }

   if(strstr(pvmeio->parm,"threshold")){
    	pai->val=threshold[cam];
    	return(2);
   }

   if(strstr(pvmeio->parm,"low_thresh")){
    	pai->val=low_thresh[cam];
    	return(2);
   }

   if(strstr(pvmeio->parm,"bpp")){
    	pai->rval=bpp[cam];
    	return(0);
   }

   if(strstr(pvmeio->parm,"code")){
    	pai->rval=code[cam];
    	return(0);
   }

   if(strstr(pvmeio->parm,"numNodes")){
    	pai->rval=numNodes;
   }

   if(strstr(pvmeio->parm,"numCameras")){
    	pai->rval=numCameras;
   }

   if(strstr(pvmeio->parm,"format")){
    	pai->rval=format;
   }

   if(strstr(pvmeio->parm,"mode")){
    	pai->rval=mode[cam];
   }

   if(strstr(pvmeio->parm,"framerate")){
    	pai->rval=framerate;
    }

   if(strstr(pvmeio->parm,"dropFrame")){
        pai->rval=dropped_frames[cam];
    }

   if(strstr(pvmeio->parm,"brightness")){
    	pai->rval=brightness;
    }
/*		Activate gain and shutter reading (AA)		*/


   if(strstr(pvmeio->parm,"gainMin")){

        if(!(ret=GetCameraControlRegister(handle, camera[cam].node, ABS_VAL_GAIN_MIN, (quadlet_t *) &absGainMin ))) {
                pai->val=absGainMin;
        }
        else {
                fprintf( stderr, "unable to get ABS_VAL_GAIN_MIN\n");
                return(S_db_badField);
        }
        return(2);

    }

   if(strstr(pvmeio->parm,"gainMax")){

        if(!(ret=GetCameraControlRegister(handle, camera[cam].node, ABS_VAL_GAIN_MAX, (quadlet_t *) &absGainMax ))) {
                pai->val=absGainMax;
        }
        else {
                fprintf( stderr, "unable to get ABS_VAL_GAIN_MAX\n");
                return(S_db_badField);
        }
        return(2);

    }

   if(strstr(pvmeio->parm,"gain")){
	
        if(!(ret=GetCameraControlRegister(handle, camera[cam].node, ABS_VAL_GAIN, (quadlet_t *) &absGain ))) {
		pai->val=absGain;
        }
        else {
                fprintf( stderr, "unable to get ABS_VAL_GAIN\n");
                return(S_db_badField);
        }
	return(2);

    }

   if(strstr(pvmeio->parm,"shutterMin")){

        if(!(ret=GetCameraControlRegister(handle, camera[cam].node, ABS_VAL_SHUTTER_MIN, (quadlet_t *) &absShutterMin ))) {
                pai->val=absShutterMin;
        }
        else {
                fprintf( stderr, "unable to get ABS_VAL_SHUTTER\n");
                return(S_db_badField);
        }
        return(2);
    }

   if(strstr(pvmeio->parm,"shutterMax")){

        if(!(ret=GetCameraControlRegister(handle, camera[cam].node, ABS_VAL_SHUTTER_MAX, (quadlet_t *) &absShutterMax ))) {
                pai->val=absShutterMax;
        }
        else {
                fprintf( stderr, "unable to get ABS_VAL_SHUTTER\n");
                return(S_db_badField);
        }
        return(2);
    }

   if(strstr(pvmeio->parm,"shutter")){

        if(!(ret=GetCameraControlRegister(handle, camera[cam].node, ABS_VAL_SHUTTER, (quadlet_t *) &absShutter ))) {
                pai->val=absShutter;
        }
        else {
                fprintf( stderr, "unable to get ABS_VAL_SHUTTER\n");
                return(S_db_badField);
        }
	return(2);
    }

   if(strstr(pvmeio->parm,"woffset")){
    	pai->rval=woffset[cam];
    }

   if(strstr(pvmeio->parm,"hoffset")){
    	pai->rval=hoffset[cam];
    }

   if(strstr(pvmeio->parm,"width")){
    	pai->rval=width[cam];
    }

   if(strstr(pvmeio->parm,"height")){
    	pai->rval=height[cam];
    }

   if(strstr(pvmeio->parm,"size")){
    	pai->rval=size[cam];
    }

   if(strstr(pvmeio->parm,"xw")){
    	pai->rval=xw[cam];
    }

   if(strstr(pvmeio->parm,"xp")){
/*	Calculate the centroid		*/
	int line = 0, col = 0;
	double sumCol[width[cam]];
	double sum = 0;
        double sig = 0,noise = 0;
        double sigsum = 0;
        double noisesum = 0;

/*	Intilaize array elemnets	*/	
	for (col=0;col < width[cam];col++)
		sumCol[col] = 0;
	
        for(col=sCol[cam];col <= eCol[cam];col++){
	        for (line = sLine[cam];line <= eLine[cam];line++){
			if (bgs[cam] == 1){
				sumCol[col] += data_array_diff[line*width[cam]+col];
				sigsum += data_array_diff[line*width[cam]+col];
			}
			else {
				sumCol[col] += data[line*width[cam]+col];
				sigsum += data[line*width[cam]+col];
			}	
		}
		sum += col * sumCol[col];
	}		 
	xp[cam] = (sum/sigsum);   /*new centroid algorithm (AA) */
	sig = sigsum/xw[cam];
	noise = noisesum/(width[cam]-xw[cam]);
	xsn[cam] = 20*log(sig/noise);
    	pai->val= xp[cam];
	
	sum = 0;
/*	Calculate SigmaX		*/
	for(col=sCol[cam];col <= eCol[cam];col++){
			
                        sum += pow(( col - xp[cam]), 2) * sumCol[col];
			
                        }
	sigmaX[cam] = sqrt((sum/sigsum));
	return(2);
    }

   if(strstr(pvmeio->parm,"xsn")){
    	pai->rval=xsn[cam];
    }

   if(strstr(pvmeio->parm,"yw")){
    	pai->rval=yw[cam];
    }

   if(strstr(pvmeio->parm,"yp")){
        int line = 0, col = 0;
	double sumLine[height[cam]];	
        double sum = 0;
        double sig = 0,noise = 0;
        double sigsum = 0;
        double noisesum = 0;

        for (line=0;line < height[cam];line++)
                sumLine[line] = 0;

        for(line=sLine[cam]; line < eLine[cam];line++){
                for (col = sCol[cam];col < eCol[cam];col++){
                        if (bgs[cam] == 1){
                                sumLine[line] += data_array_diff[line*width[cam]+col];
                                sigsum += data_array_diff[line*width[cam]+col];
                        }
                        else {
                                sumLine[line] += data[line*width[cam]+col];
                                sigsum += data[line*width[cam]+col];
                        }
                }
		sum += line * sumLine[line];
        }
        yp[cam] = (sum/sigsum);   /*new centroid algorithm (AA) */
        sig = sigsum/yw[cam];
        noise = noisesum/(width[cam]-yw[cam]);
        ysn[cam] = 20*log(sig/noise);
    	pai->val=yp[cam];

        sum = 0;
/*      Calculate SigmaY                */
        for(line=sLine[cam];line <= eLine[cam];line++){

                        sum += pow(( line - yp[cam]), 2) * sumLine[line];
                        }
        sigmaY[cam] = sqrt((sum/sigsum));
	return(2);
    }

   if(strstr(pvmeio->parm,"ysn")){
    	pai->rval=ysn[cam];
    }
/*		New AI channels (AA)		*/

   if(strstr(pvmeio->parm,"max")){
        pai->rval=max[cam];
    }

   if(strstr(pvmeio->parm,"afps")){
        pai->val=afps[cam];	
	return(2);
    }


   if(strstr(pvmeio->parm,"maxCol")){
        pai->rval=maxCol[cam];
    }

   if(strstr(pvmeio->parm,"maxLine")){
        pai->rval=maxLine[cam];
    }

   if(strstr(pvmeio->parm,"xdistMaxSum")){
        pai->rval=xdistMaxSum[cam];
    }

   if(strstr(pvmeio->parm,"ydistMaxSum")){
        pai->rval=ydistMaxSum[cam];
    }

   if(strstr(pvmeio->parm,"xdistMaxCol")){
        pai->rval=xdistMaxCol[cam];
    }

   if(strstr(pvmeio->parm,"ydistMaxLine")){
        pai->rval=ydistMaxLine[cam];
    }

   if(strstr(pvmeio->parm,"sCol")){
        pai->rval=sCol[cam];
    }

   if(strstr(pvmeio->parm,"eCol")){
        pai->rval=eCol[cam];
    }

   if(strstr(pvmeio->parm,"sLine")){
        pai->rval=sLine[cam];
    }

   if(strstr(pvmeio->parm,"eLine")){
        pai->rval=eLine[cam];
    }

   if(strstr(pvmeio->parm,"sigmaX")){
        pai->val=sigmaX[cam];
	return(2);
    }

   if(strstr(pvmeio->parm,"sigmaY")){
        pai->val=sigmaY[cam];
	return(2);
    }

   if(strstr(pvmeio->parm,"sumTot")){
        pai->val=sumTot[cam];
        return(2);
    }



    return(0);
}
            
