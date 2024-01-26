/****************************************************************************/
/*                                                                          */
/*                      setup_camera.c                                      */
/*                                                                          */
/*                 set format, mode, gain, etc for firewire camera          */
/*                                                                          */
/****************************************************************************/


#include <stdio.h>
#include <libraw1394/raw1394.h>
#include <libdc1394/dc1394_control.h>
#include <stdlib.h>
#include <string.h>


int main(int argc, char *argv[]) {
  static char cvsid[]="$Id: setup_camera.c,v 1.2 2005/08/30 10:40:15 adwan Exp $";
/*  dc1394_cameracapture camera;*/
  int numNodes;
  int numCameras;
  raw1394handle_t handle;
  nodeid_t * camera_nodes;
/*  dc1394_feature_set features;*/
/*  dc1394_miscinfo camera_misc_info;*/
/*  long i;*/
/*  unsigned char *ptr;*/
   int feature = 0;
   int value;
   int old_value;
   int min_value;
   int max_value;
/*   dc1394bool_t truefalse;*/
   dc1394bool_t feature_present;
   dc1394bool_t has_manual;
   dc1394bool_t has_auto;
   dc1394bool_t is_auto;
   unsigned int format=0;
   unsigned int mode=0;
   unsigned int framerate=0;
   unsigned int old_format;
   unsigned int old_mode;
   unsigned int old_framerate;
   quadlet_t formats;
   quadlet_t modes;
   quadlet_t framerates;

   if(argc==2){
   	if(!strcmp(argv[1],"--version")){
		printf("%s\n",cvsid);
		exit(1);
   	}
   }

   if(argc!=3){
	printf("\nusage: setup_camera [brightness|exposure|sharpness|white_balance|hue|stauration|gamma|shutter|gain|iris|focus|temperature|trigger|trigger_delay|white_shading|frame_rate auto|manual|value|show] [format|mode|framerate value|show] \n");
	exit(1);
   }


   if (( handle = dc1394_create_handle(0)) ==NULL) {
	fprintf( stderr, "Unable to aquire a raw1394 handle\n");
	exit(1);
   }

  
   numNodes = raw1394_get_nodecount(handle);
   camera_nodes = dc1394_get_camera_nodes(handle,&numCameras,0);
   fflush(stdout);
   if (numCameras<1) {
	fprintf( stderr, "no cameras found :(\n");
	dc1394_destroy_handle(handle);
	exit(1);
   }
  
   if( camera_nodes[0] == numNodes-1) {
	fprintf( stderr, "\n" "Sorry, your camera is the highest node\n");
	dc1394_destroy_handle(handle);
	exit( 1);
   }
  
   if(dc1394_get_video_format(handle,camera_nodes[0],&old_format)!=DC1394_SUCCESS) {
   	printf("error getting format\n");
       	exit(1);
   }

   if(dc1394_get_video_mode(handle,camera_nodes[0],&old_mode)!=DC1394_SUCCESS) {
   	printf("error getting mode\n");
       	exit(1);
   }

   if(dc1394_get_video_framerate(handle,camera_nodes[0],&old_framerate)!=DC1394_SUCCESS) {
   	printf("error getting framerate\n");
       	exit(1);
   }

   if(dc1394_query_supported_formats(handle,camera_nodes[0],&formats)!=DC1394_SUCCESS) {
   	printf("error getting supported formats\n");
       	exit(1);
   }

   if(dc1394_query_supported_modes(handle,camera_nodes[0],old_format,&modes)!=DC1394_SUCCESS) {
   	printf("error getting supported modes\n");
       	exit(1);
   }

   if(dc1394_query_supported_framerates(handle,camera_nodes[0],old_format,old_mode,&framerates)!=DC1394_SUCCESS) {
   	printf("error getting supported framerates\n");
       	exit(1);
   }

   if(!strcmp(argv[1],"format")) { 
   	if(!strcmp(argv[2],"show")) { 
		switch (old_format) {
			case FORMAT_VGA_NONCOMPRESSED :{
				printf("format 0 : FORMAT_VGA_NONCOMPRESSED\n"); 
				exit(0);
			}
			case FORMAT_SVGA_NONCOMPRESSED_1 :{
				printf("format 1 : FORMAT_SVGA_NONCOMPRESSED_1\n"); 
				exit(0);
			}
			case FORMAT_STILL_IMAGE :{
				printf("format 6 : FORMAT_STILL_IMAGE\n"); 
				exit(0);
			}
			case FORMAT_SCALABLE_IMAGE_SIZE :{
				printf("format 7 : FORMAT_SCALABLE_IMAGE_SIZE\n"); 
				exit(0);
			}
		}
		printf("Unknown format \n");
		exit(1);
	}
   	if( (!strcmp(argv[2],"FORMAT_VGA_NONCOMPRESSED")) || (!strcmp(argv[2],"0")) ) { 
		format = FORMAT_VGA_NONCOMPRESSED;
		if (!(formats & (0x1 <<31))) {
			printf("Format 0 (VGA_NONCOMPRESSED) not supported by this camera\n");
			exit(1);
		}
   	}
   	if( (!strcmp(argv[2],"FORMAT_SVGA_NONCOMPRESSED_1"))  || (!strcmp(argv[2],"1")) ){ 
		format = FORMAT_SVGA_NONCOMPRESSED_1;
		if (!(formats & (0x1 <<30))) {
			printf("Format 0 (SVGA_NONCOMPRESSED_1) not supported by this camera\n");
			exit(1);
		}
   	}
   	if( (!strcmp(argv[2],"FORMAT_SVGA_NONCOMPRESSED_2"))  || (!strcmp(argv[2],"2")) ){ 
		format = FORMAT_SVGA_NONCOMPRESSED_2;
		if (!(formats & (0x1 <<29))) {
			printf("Format 0 (SVGA_NONCOMPRESSED_2) not supported by this camera\n");
			exit(1);
		}
   	}
	if(!format) {
		printf("Unknown cmd/value for format \n");
		exit(1);
	}

	if(dc1394_set_video_format(handle,camera_nodes[0],format)!=DC1394_SUCCESS) {
		printf("error setting format\n");
       		exit(1);
   	}
	exit(0);
   }
 
   if(!strcmp(argv[1],"mode")) { 
   	if(!strcmp(argv[2],"show")) { 
		if(old_format==FORMAT_VGA_NONCOMPRESSED){
			switch (old_mode) {
				case MODE_160x120_YUV444 :{
					printf("format 0 mode 0: MODE_160x120_YUV444\n"); 
					exit(0);
				}
				case MODE_320x240_YUV422 :{
					printf("format 0 mode 1: MODE_320x240_YUV422\n"); 
					exit(0);
				}
				case MODE_640x480_YUV411 :{
					printf("format 0 mode 2: MODE_640x480_YUV411\n"); 
					exit(0);
				}
				case MODE_640x480_YUV422 :{
					printf("format 0 mode 3: MODE_640x480_YUV422\n"); 
					exit(0);
				}
				case MODE_640x480_RGB :{
					printf("format 0 mode 4: MODE_640x480_RGB\n"); 
					exit(0);
				}
				case MODE_640x480_MONO :{
					printf("format 0 mode 5: MODE_640x480_MONO\n"); 
					exit(0);
				}
				case MODE_640x480_MONO16 :{
					printf("format 0 mode 5: MODE_640x480_MONO16\n"); 
					exit(0);
				}
			}
			printf("Unknown mode \n");
			exit(1);
		}
		if(old_format==FORMAT_SVGA_NONCOMPRESSED_1){
			switch (old_mode) {
				case MODE_800x600_YUV422 :{
					printf("MODE_800x600_YUV422\n"); 
					exit(0);
				}
				case MODE_800x600_RGB :{
					printf("MODE_800x600_RGB\n"); 
					exit(0);
				}
				case MODE_800x600_MONO :{
					printf("MODE_800x600_MONO\n"); 
					exit(0);
				}
				case MODE_1024x768_YUV422 :{
					printf("MODE_1024x768_YUV422\n"); 
					exit(0);
				}
				case MODE_1024x768_RGB :{
					printf("MODE_1024x768_RGB\n"); 
					exit(0);
				}
				case MODE_1024x768_MONO :{
					printf("MODE_1024x768_MONO\n"); 
					exit(0);
				}
				case MODE_800x600_MONO16 :{
					printf("MODE_800x600_MONO16\n"); 
					exit(0);
				}
				case MODE_1024x768_MONO16 :{
					printf("MODE_1024x768_MONO16\n"); 
					exit(0);
				}
			}
		}
		if(old_format==FORMAT_SVGA_NONCOMPRESSED_2){
			switch (old_mode) {
				case MODE_1280x960_YUV422 :{
					printf("MODE_1280x960_YUV422\n"); 
					exit(0);
				}
				case MODE_1280x960_RGB :{
					printf("MODE_1280x960_RGB\n"); 
					exit(0);
				}
				case MODE_1280x960_MONO :{
					printf("MODE_1280x960_MONO\n"); 
					exit(0);
				}
				case MODE_1600x1200_YUV422 :{
					printf("MODE_1600x1200_YUV422\n"); 
					exit(0);
				}
				case MODE_1600x1200_RGB :{
					printf("MODE_1600x1200_RGB\n"); 
					exit(0);
				}
				case MODE_1600x1200_MONO :{
					printf("MODE_1600x1200_MONO\n"); 
					exit(0);
				}
				case MODE_1280x960_MONO16 :{
					printf("MODE_1280x960_MONO16\n"); 
					exit(0);
				}
				case MODE_1600x1200_MONO16 :{
					printf("MODE_1600x1200_MONO16\n"); 
					exit(0);
				}
			}
		}
		printf("Unknown mode \n");
		exit(1);
	}
	if(old_format==FORMAT_VGA_NONCOMPRESSED){
		if((!strcmp(argv[2],"MODE_160x120_YUV444"))||(!strcmp(argv[2],"0"))) {
			mode = MODE_160x120_YUV444;
		}
		if((!strcmp(argv[2],"MODE_320x240_YUV422"))||(!strcmp(argv[2],"1"))) {
			mode = MODE_320x240_YUV422;
		}
		if((!strcmp(argv[2],"MODE_640x480_YUV411"))||(!strcmp(argv[2],"2"))) {
			mode = MODE_640x480_YUV411;
		}
		if((!strcmp(argv[2],"MODE_640x480_YUV422"))||(!strcmp(argv[2],"3"))) {
			mode = MODE_640x480_YUV422;
		}
		if((!strcmp(argv[2],"MODE_640x480_RGB"))||(!strcmp(argv[2],"4"))) {
			mode = MODE_640x480_RGB;
		}
		if((!strcmp(argv[2],"MODE_640x480_MONO"))||(!strcmp(argv[2],"5"))) {
			mode = MODE_640x480_MONO;
		}
		if((!strcmp(argv[2],"MODE_640x480_MONO16"))||(!strcmp(argv[2],"6"))) {
			mode = MODE_640x480_MONO16;
		}
		if(!mode){
			printf("unknown mode in format 0\n");
       			exit(1);
		}
	}
	if(old_format==FORMAT_SVGA_NONCOMPRESSED_1){
		if((!strcmp(argv[2],"MODE_800x600_YUV422"))||(!strcmp(argv[2],"0"))) {
			mode = MODE_800x600_YUV422;
		}
		if((!strcmp(argv[2],"MODE_800x600_RGB"))||(!strcmp(argv[2],"1"))) {
			mode = MODE_800x600_RGB;
		}
		if((!strcmp(argv[2],"MODE_800x600_MONO"))||(!strcmp(argv[2],"2"))) {
			mode = MODE_800x600_MONO;
		}
		if((!strcmp(argv[2],"MODE_1024x768_YUV422"))||(!strcmp(argv[2],"3"))) {
			mode = MODE_1024x768_YUV422;
		}
		if((!strcmp(argv[2],"MODE_1024x768_RGB"))||(!strcmp(argv[2],"4"))) {
			mode = MODE_1024x768_RGB;
		}
		if((!strcmp(argv[2],"MODE_1024x768_MONO"))||(!strcmp(argv[2],"5"))) {
			mode = MODE_1024x768_MONO;
		}
		if((!strcmp(argv[2],"MODE_800x600_MONO16"))||(!strcmp(argv[2],"6"))) {
			mode = MODE_800x600_MONO16;
		}
		if((!strcmp(argv[2],"MODE_1024x768_MONO16"))||(!strcmp(argv[2],"7"))) {
			mode = MODE_1024x768_MONO16;
		}
		if(!mode){
			printf("unknown mode in format 1\n");
       			exit(1);
		}
	}
	if(old_format==FORMAT_SVGA_NONCOMPRESSED_2){
		if((!strcmp(argv[2],"MODE_1280x960_YUV422"))||(!strcmp(argv[2],"0"))) {
			mode = MODE_1280x960_YUV422;
		}
		if((!strcmp(argv[2],"MODE_1280x960_RGB"))||(!strcmp(argv[2],"1"))) {
			mode = MODE_1280x960_RGB;
		}
		if((!strcmp(argv[2],"MODE_1280x960_MONO"))||(!strcmp(argv[2],"2"))) {
			mode = MODE_1280x960_MONO;
		}
		if((!strcmp(argv[2],"MODE_1600x1200_YUV422"))||(!strcmp(argv[2],"3"))) {
			mode = MODE_1600x1200_YUV422;
		}
		if((!strcmp(argv[2],"MODE_1600x1200_RGB"))||(!strcmp(argv[2],"4"))) {
			mode = MODE_1600x1200_RGB;
		}
		if((!strcmp(argv[2],"MODE_1600x1200_MONO"))||(!strcmp(argv[2],"5"))) {
			mode = MODE_1600x1200_MONO;
		}
		if((!strcmp(argv[2],"MODE_1280x960_MONO16"))||(!strcmp(argv[2],"6"))) {
			mode = MODE_1280x960_MONO16;
		}
		if((!strcmp(argv[2],"MODE_1600x1200_MONO16"))||(!strcmp(argv[2],"7"))) {
			mode = MODE_1600x1200_MONO16;
		}
		if(!mode){
			printf("unknown mode in format 1\n");
       			exit(1);
		}
	}

	if(!mode){
		printf("unknown format/mode\n");
       		exit(1);
	}

	if(dc1394_set_video_mode(handle,camera_nodes[0],mode)!=DC1394_SUCCESS) {
		printf("error setting mode\n");
       		exit(1);
   	}
	exit(0);
   }
 
   if(!strcmp(argv[1],"framerate")) { 
   	if(!strcmp(argv[2],"show")) { 
		switch (old_framerate) {
			case FRAMERATE_1_875 :{
				printf("FRAMERATE_1_875\n"); 
				exit(0);
			}
			case FRAMERATE_3_75 :{
				printf("FRAMERATE_3_75\n"); 
				exit(0);
			}
			case FRAMERATE_7_5 :{
				printf("FRAMERATE_7_5\n"); 
				exit(0);
			}
			case FRAMERATE_15 :{
				printf("FRAMERATE_15\n"); 
				exit(0);
			}
			case FRAMERATE_30 :{
				printf("FRAMERATE_30\n"); 
				exit(0);
			}
			case FRAMERATE_60 :{
				printf("FRAMERATE_60\n"); 
				exit(0);
			}
		}
	}
   	if( (!strcmp(argv[2],"FRAMERATE_1_875")) || (!strcmp(argv[2],"1.875")) ) { 
		framerate = FRAMERATE_1_875;
		if (!(framerates & (0x1 <<31))) {
			printf("framerate 1.875 (FRAMERATE_1_875) not supported by this camera %X\n",framerates);
			exit(1);
		}
   	}
   	if( (!strcmp(argv[2],"FRAMERATE_3_75")) || (!strcmp(argv[2],"3.75")) ) { 
		framerate = FRAMERATE_3_75;
		if (!(framerates & (0x1 <<30))) {
			printf("framerate 3.75 (FRAMERATE_3_75) not supported by this camera %X\n",framerates);
			exit(1);
		}
   	}
   	if( (!strcmp(argv[2],"FRAMERATE_7_5")) || (!strcmp(argv[2],"7.5")) ) { 
		framerate = FRAMERATE_7_5;
		if (!(framerates & (0x1 <<29))) {
			printf("framerate 7.5 (FRAMERATE_7_5) not supported by this camera %X\n",framerates);
			exit(1);
		}
   	}
   	if( (!strcmp(argv[2],"FRAMERATE_15")) || (!strcmp(argv[2],"15")) ) { 
		framerate = FRAMERATE_15;
		if (!(framerates & (0x1 <<28))) {
			printf("framerate 15 (FRAMERATE_15) not supported by this camera %X\n",framerates);
			exit(1);
		}
   	}
   	if( (!strcmp(argv[2],"FRAMERATE_30")) || (!strcmp(argv[2],"30")) ) { 
		framerate = FRAMERATE_30;
		if (!(framerates & (0x1 <<27))) {
			printf("framerate 30 (FRAMERATE_30) not supported by this camera %X\n",framerates);
			exit(1);
		}
   	}
   	if( (!strcmp(argv[2],"FRAMERATE_60")) || (!strcmp(argv[2],"60")) ) { 
		framerate = FRAMERATE_60;
		if (!(framerates & (0x1 <<26))) {
			printf("framerate 60 (FRAMERATE_60) not supported by this camera %X\n",framerates);
			exit(1);
		}
   	}
	if(!framerate) {
		printf("unknown cmd/value for framerate 0\n");
		exit(1);
	}
	if(dc1394_set_video_framerate(handle,camera_nodes[0],framerate)!=DC1394_SUCCESS) {
		printf("error setting framerate\n");
       		exit(1);
   	}
	exit(0);
   }

   if(!strcmp(argv[1],"brightness")) { 
	feature = FEATURE_BRIGHTNESS;
   }
   if(!strcmp(argv[1],"exposure")) { 
	feature = FEATURE_EXPOSURE;
   }
   if(!strcmp(argv[1],"sharpness")) { 
	feature = FEATURE_SHARPNESS;
   } 
   if(!strcmp(argv[1],"white_balance")) { 
	feature = FEATURE_WHITE_BALANCE;
   } 
   if(!strcmp(argv[1],"hue")) { 
	feature = FEATURE_HUE;
   } 
   if(!strcmp(argv[1],"saturation")) { 
	feature = FEATURE_SATURATION;
   } 
   if(!strcmp(argv[1],"gamma")) { 
	feature = FEATURE_GAMMA;
   } 
   if(!strcmp(argv[1],"shutter")) { 
	feature = FEATURE_SHUTTER;
   } 
   if(!strcmp(argv[1],"gain")) { 
	feature = FEATURE_GAIN;
   } 
   if(!strcmp(argv[1],"iris")) { 
	feature = FEATURE_IRIS;
   } 
   if(!strcmp(argv[1],"focus")) { 
	feature = FEATURE_FOCUS;
   } 
   if(!strcmp(argv[1],"temperature")) { 
	feature = FEATURE_TEMPERATURE;
   } 
   if(!strcmp(argv[1],"trigger")) { 
	feature = FEATURE_TRIGGER;
   }  
   if(!feature){
	fprintf( stderr, "\n" "feature not known\n");
	exit(1);
   }

   if(dc1394_is_feature_present(handle,camera_nodes[0],feature,&feature_present)!=DC1394_SUCCESS) {
        printf("error getting feature value \n");
        exit(1);
   }

   if(!feature_present){ 
	printf("feature not present\n"); 
	exit(1);
   }

   if(dc1394_has_manual_mode(handle,camera_nodes[0],feature,&has_manual)!=DC1394_SUCCESS) {
        printf("error querying manual mode \n");
        exit(1);
   }

   if(dc1394_has_auto_mode(handle,camera_nodes[0],feature,&has_auto)!=DC1394_SUCCESS) {
   	printf("error querying auto mode \n");
       	exit(1);
   }

   if(dc1394_is_feature_auto(handle,camera_nodes[0],feature,&is_auto)!=DC1394_SUCCESS) {
        printf("error getting is feature auto \n");
        exit(1);
   }

   if(dc1394_get_feature_value(handle,camera_nodes[0],feature,&old_value)!=DC1394_SUCCESS) {
        printf("error getting old value \n");
        exit(1);
   }

   if(dc1394_get_min_value(handle,camera_nodes[0],feature,&min_value)!=DC1394_SUCCESS) {
        printf("error getting min value \n");
        exit(1);
   }

   if(dc1394_get_max_value(handle,camera_nodes[0],feature,&max_value)!=DC1394_SUCCESS) {
        printf("error getting max value \n");
        exit(1);
   }

   if(!strcmp(argv[2],"auto")) { 

   	if(!has_auto){ 
		printf("no auto mode\n"); 
		exit(1);
   	}

   	if(dc1394_auto_on_off(handle,camera_nodes[0],feature,1)!=DC1394_SUCCESS) {
        	printf("error seting auto on \n");
        	exit(1);
	}

	exit(0);
   }

   if(!strcmp(argv[2],"manual")) { 

   	if(!has_manual){ 
		printf("no manual mode\n"); 
		exit(1);
   	}

   	if(dc1394_auto_on_off(handle,camera_nodes[0],feature,0)!=DC1394_SUCCESS) {
        	printf("error seting manual on \n");
        	exit(1);
	}

	exit(0);
   }

   if(!strcmp(argv[2],"show")) { 
	printf("has manual mode=%d\n",(int)has_manual); 
	printf("has auto mode=%d\n",(int)has_auto); 
	printf("is auto mode=%d\n",(int)is_auto); 
	printf("value is =%d\n",(int)old_value); 
	printf("min value is =%d\n",(int)min_value); 
	printf("max value is =%d\n",(int)max_value); 

	exit(0);
   }

   value = atoi(argv[2]);

   if(dc1394_set_feature_value(handle,camera_nodes[0],feature,value)!=DC1394_SUCCESS) {
        printf("error setting feature value \n");
        exit(1);
   }

/*
  dc1394_release_camera(handle,&camera);
  dc1394_destroy_handle(handle);
*/
  return 0;
}
