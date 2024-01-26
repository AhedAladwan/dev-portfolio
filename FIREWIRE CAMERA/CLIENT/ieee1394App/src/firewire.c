	/**************************************************************************/
	/*            firewire.c - an Epics ca client to display                  */
	/*                  images from a firewire camera                         */
	/*                                                                        */
	/*      TODO:                                                             */
	/*          1. Mono 16 bit display                                        */
	/*                                                                        */
	/*      DONE:                                                             */
	/*          1. Mono 8 bit display                                         */
	/*          2. YUV422 display                                             */
	/*          3. RGB display                                                */
	/*                                                                        */
	/**************************************************************************/

#include <X11/Intrinsic.h>
#include <X11/Xutil.h>
#include <Xm/Xm.h>
#include <Xm/DrawingA.h>
#include <Xm/PushB.h>
#include <Xm/BulletinB.h>
/* #include "conversions.h" */

/* enumeration from dc1394_conversions.h */
enum {
  DC1394_BAYER_METHOD_NEAREST=0,
  DC1394_BAYER_METHOD_SIMPLE,
  DC1394_BAYER_METHOD_BILINEAR,
  DC1394_BAYER_METHOD_HQLINEAR,
  DC1394_BAYER_METHOD_DOWNSAMPLE,
  DC1394_BAYER_METHOD_EDGESENSE
};

/* enumeration from dc1394_control.h */
enum {
  DC1394_COLOR_FILTER_RGGB = 512,
  DC1394_COLOR_FILTER_GBRG,
  DC1394_COLOR_FILTER_GRBG,
  DC1394_COLOR_FILTER_BGGR
};

#define BAYER_FILTER_BW 0    /* this is not in any include file */


/* #include "dc1394_conversions.h" */

#include <fdmgr.h>
#include <cadef.h>
#include <tsDefs.h>
#include <alarm.h>             
#include <alarmString.h>
#include "dbDefs.h"

#define mycolor 16

#define PPM_FILE_NAME "Image.ppm"
#define PGM_FILE_NAME "Image.pgm"
#define YUV_FILE_NAME "Image.yuv"
#define D 1

#define MAX_PV 1000
#define MAX_PV_NAME_LEN 40
GC gc; 
Widget bb,drawing_area,button1; 
Widget toplevel;
XGCValues vals;
XImage *ximage = NULL;
Visual *visual;
unsigned char   *data;
unsigned char   *yuv;
struct timeval  startime,endtime,counttime;
unsigned int size,oldsize,nsize;
unsigned int imagesize=0;
unsigned int width,oldwidth = 0;
unsigned int height,oldheight = 0;
unsigned int save,oldsave;
unsigned char *rgbn=NULL,*rgbn_p=NULL,*rgbCamera=NULL,*rgbCamera_p=NULL;
unsigned int  bpp;
unsigned int  code;
unsigned int  iBayerConversion=0,iBayerConversion_old=1; 
unsigned int  iBayerMethod=0;
unsigned int  iColorFilter=0,iColorFilter_old=1;
unsigned int  iBayerFilter=0;


char mybuffer[80];

/***  epics stuff  ***/
int         status;
chid        mychid;
long        st,en;
int         i;
int         asize = 10;
int         dsize;
int         *myarg;
char	    camera[80];

#define FDMGR_SEC_TIMEOUT        10              /* seconds       */
#define FDMGR_USEC_TIMEOUT       0               /* micro-seconds */
#define CA_PEND_EVENT_TIME      0.001
#define TRUE            1
#define FALSE           0
int DEBUG;
int mycount;

Arg al[10];

/*
typedef struct{
	char                value[20];
	chid                mychid;
	evid                myevid;
} MYNODE;
*/

char *mystrcat(char *str1, char *str2){
	strcpy(mybuffer,str1);
	strcat(mybuffer,str2);
	return(mybuffer);
}

/************************************************************************/
/*     writeppmfile - function to write data to file                      */
/**************************************************************************/
/*
void writeppmfile (){
   FILE *ppmfile;

   printf("writeppmfile");

  if((ppmfile=fopen(PPM_FILE_NAME, "w"))==NULL){;
	perror( "Can't create '" PPM_FILE_NAME "'");
	return;
   }

   fprintf(ppmfile,"P6\n%u %u 255\n", width,height);
   fwrite(rgb, 1, height*width*3, ppmfile);
   fclose(ppmfile);
}
*/

/************************************************************************/
/*     writepgmfile - function to write data to file                      */
/**************************************************************************/
void writepgmfile (){
   FILE *pgmfile;

   printf("writepgmfile");

  if((pgmfile=fopen(PGM_FILE_NAME, "w"))==NULL){;
	perror( "Can't create '" PGM_FILE_NAME "'");
	return;
   }

   fprintf(pgmfile,"P5\n%u %u 255\n", width,height);
   fwrite(data, 1, height*width, pgmfile);
   fclose(pgmfile);
}


/************************************************************************/
/*     calc - function to calculate time in ms between two times          */
/**************************************************************************/
int calc(struct timeval *one, struct timeval *two){
	  return( ((two->tv_sec - one->tv_sec) * 1000 ) +  ((two->tv_usec -one->tv_usec)/1000) ) ;
}


/************************************************************************/
/*     displayme - displays the image in the drawing area                 */
/**************************************************************************/
void displayme() {
	Display *display=XtDisplay(drawing_area);
	int x,y,i;
	double y1,y2,u,v;
	double r1,g1,b1,r2,g2,b2;
	unsigned char uR,uG,uB;
	/*************************************************************************/
	/*            Check if width of height changed                           */
	/**************************************************************************/
	if (width!=oldwidth | height!=oldheight){
                imagesize = 0;
                if (ximage) XDestroyImage(ximage);
        
		size = height * width * bpp;
		printf("H or W changed size=%d\n",size);
		XClearArea(XtDisplay(drawing_area), XtWindow(drawing_area), 0,0,0,0, True);

		XtSetArg(al[0],XmNheight,height+40);
		XtSetArg(al[1],XmNwidth,width+40);
		XtSetValues(toplevel,al,2);
		       
		XtSetArg(al[0], XmNheight,height);
		XtSetArg(al[1], XmNwidth,width);
		XtSetArg(al[2],XmNx,20);
		XtSetArg(al[3],XmNy,20);
		XtSetValues(bb,al,4);

		XtSetArg(al[0], XmNheight,height);
		XtSetArg(al[1], XmNwidth,width);
		XtSetArg(al[2],XmNx,0);
		XtSetArg(al[3],XmNy,0);
		XtSetValues(drawing_area,al,4);
		if(rgbn) free(rgbn);
		if(rgbCamera) free(rgbCamera);
                rgbn = (unsigned char *) malloc(size*4);
		rgbCamera = (unsigned char *) malloc(size*3);
                imagesize = size;
		ximage=XCreateImage(display,visual,24,2,0,rgbn,width,height,16,width*4);
                
		oldwidth=width;
		oldheight=height;
	}
        if (size>imagesize) size=imagesize;

	/******************************************************/
	/* Check if the Bayer conversion function was changed */
	/******************************************************/
	if(iBayerConversion != iBayerConversion_old){
	  switch (iBayerConversion) {
	  case 0:
	    iBayerMethod=DC1394_BAYER_METHOD_NEAREST;
	    break;
	  case 1:
	    iBayerMethod=DC1394_BAYER_METHOD_SIMPLE;
	    break;
	  case 2:
	    iBayerMethod=DC1394_BAYER_METHOD_BILINEAR;
	    break;
	  case 3:
	    iBayerMethod=DC1394_BAYER_METHOD_HQLINEAR;
	    break;
	  case 4:
	    iBayerMethod=DC1394_BAYER_METHOD_DOWNSAMPLE;
	    break;
	  case 5:
	    iBayerMethod=DC1394_BAYER_METHOD_EDGESENSE;
	    break;
	  }
	  iBayerConversion_old = iBayerConversion;
	}

	/******************************************************/
	/* Check if the Bayer filter */
	/******************************************************/
	if(iColorFilter != iColorFilter_old){
	  switch (iColorFilter) {
	  case 0:
	    iBayerFilter=BAYER_FILTER_BW;
	    break;
	  case 1:
	    iBayerFilter=DC1394_COLOR_FILTER_BGGR;
	    break;
	  case 2:
	    iBayerFilter=DC1394_COLOR_FILTER_GRBG;
	    break;
	  case 3:
	    iBayerFilter=DC1394_COLOR_FILTER_RGGB;
	    break;
	  case 4:
	    iBayerFilter=DC1394_COLOR_FILTER_GBRG;
	    break;
	  }
	  iColorFilter_old = iColorFilter;
	}

	

	/*************************************************************************/
	/*            Display 8 bit monochrome data on a  24 bit display         */
	/**************************************************************************/
	if (bpp == 1 && code == 1) {
		rgbn_p = rgbn;
		
		if(iBayerFilter != BAYER_FILTER_BW){
		  rgbCamera_p=rgbCamera;
		  printf("Bayer mode 8 bits Bayer filter %d size %d\n", iBayerFilter, size);
		  dc1394_bayer_decoding_8bit(data, rgbCamera, width, height, iBayerFilter,iBayerMethod );
		  
		  for (i=0;i<size;i++){
		    uR=*rgbCamera_p++;
		    uG=*rgbCamera_p++;
		    uB=*rgbCamera_p++;
		    *rgbn_p++ = uB;
		    *rgbn_p++ = uG;
		    *rgbn_p++ = uR;
		    *rgbn_p++ = 0;
		  }
		}
		else{ /* black and white mode */
		  for (i=0;i<size;i++){
                        *rgbn_p++ = data[i];
                        *rgbn_p++ = data[i];
                        *rgbn_p++ = data[i];
                        *rgbn_p++ = 0;
		  }
		}/* end of else */
		  

		XPutImage(display,XtWindow(drawing_area),gc,ximage,0,0,0,0, width,height);
	}
	
	/*************************************************************************/
	/*           Display 16 bit monochrome data on a  24 bit display         */
	/**************************************************************************/
	if (bpp == 2 && code == 1) {
		rgbn_p = rgbn;
		if(iBayerFilter != BAYER_FILTER_BW){
		  rgbCamera_p=rgbCamera;
		  printf("Bayer mode 16 bits colour %d size %d\n", iBayerFilter,size);
		  dc1394_bayer_decoding_16bit(data, rgbCamera, width, height, iBayerFilter,iBayerMethod );
		  
		  for (i=0;i<size;i++){
		    uR=*rgbCamera_p++;
		    *rgbCamera_p++;
		    uG=*rgbCamera_p++;
		    *rgbCamera_p++;
		    uB=*rgbCamera_p++;
		    *rgbCamera_p++;
		    *rgbn_p++ = uB;
		    *rgbn_p++ = uG;
		    *rgbn_p++ = uR;
		    *rgbn_p++ = 0;
		  }
		}
		else{ /* black and white mode */
		  for (i=0;i<size;i++){
                        *rgbn_p++ = data[i];
                        *rgbn_p++ = data[i];
                        *rgbn_p++ = data[i];
                        *rgbn_p++ = 0;
		  }
		}/* end of else */


		for (i=0;i<size;i++){
			*rgbn_p++ = data[i*2];
			*rgbn_p++ = data[i*2];
			*rgbn_p++ = data[i*2];
			*rgbn_p++ = 0;
		}
		XPutImage(display,XtWindow(drawing_area),gc,ximage,0,0,0,0, width,height);
	}
	
	/*************************************************************************/
	/*            Display 8 bit monochrome data on a  16 bit display         */
	/**************************************************************************/
	/*
	for(i=0;i<width*height;i++) {
		data4[i]=data[i]/8;
		data3[i] = (unsigned short)(2113*data4[i]);
	}
	ximage=XCreateImage(display,visual,16,2,0,(unsigned char*)data3,width,height,16,width*2);
	XPutImage(display,XtWindow(drawing_area),gc,ximage,0,0,0,0, width,height);
	*/

	/*************************************************************************/
	/*            Display 16 bit YUV422 data on a 24 bit display             */
	/**************************************************************************/
	if (bpp == 2 && code == 2) {
		yuv = (unsigned char *)data;
		nsize = width*height/2;
		rgbn_p = rgbn;

		for (i=0;i<nsize;i++){

			u  = yuv[(i*4)+0]-128;
			y1 = yuv[(i*4)+1];
			v  = yuv[(i*4)+2]-128;
			y2 = yuv[(i*4)+3];
		
			r1=y1-0.0009267*u+1.4016868*v;
			g1=y1-0.3436954*u-0.7141690*v;
			b1=y1+1.7721604*u+0.0009902*v;
			
			r2=y2-0.0009267*u+1.4016868*v;
			g2=y2-0.3436954*u-0.7141690*v;
			b2=y2+1.7721604*u+0.0009902*v;

			*rgbn_p++ = b1;
			*rgbn_p++ = g1;
			*rgbn_p++ = r1;
			*rgbn_p++ = 0;
			*rgbn_p++ = b2;
			*rgbn_p++ = g2;
			*rgbn_p++ = r2;
			*rgbn_p++ = 0;
    		}
		XPutImage(display,XtWindow(drawing_area),gc,ximage,0,0,0,0, width,height);
	}

	/*************************************************************************/
	/*            Display 24 bit RGB    data on a 24 bit display             */
	/**************************************************************************/
	if (bpp == 3 && code == 3) {
		rgbn_p = rgbn;

		for (i=0;i<height*width;i++){
			*rgbn_p++ = data[i*3+2]; 
			*rgbn_p++ = data[i*3+1];
			*rgbn_p++ = data[i*3+0];
			*rgbn_p++ = 0;
    		}
		XPutImage(display,XtWindow(drawing_area),gc,ximage,0,0,0,0, width,height);
	}
}


/************************************************************************/
/*     printChidInfo - print out status on error in epics                 */
/**************************************************************************/
static void printChidInfo(chid chid, char *message)
{
	printf("\n%s\n",message);
	printf("pv: %s  type(%d) nelements(%ld) host(%s)",
	ca_name(chid),ca_field_type(chid),ca_element_count(chid),
	ca_host_name(chid));
	printf(" read(%d) write(%d) state(%d)\n",
	ca_read_access(chid),ca_write_access(chid),ca_state(chid));
}

/************************************************************************/
/*     epics exception callback                                           */
/**************************************************************************/
static void exceptionCallback(struct exception_handler_args args)
{
	chid        chid = args.chid;
	long        stat = args.stat; /* Channel access status code*/
	const char  *channel;
	static char *noname = "unknown";

	channel = (chid ? ca_name(chid) : noname);

	if(chid) printChidInfo(chid,"exceptionCallback");
		printf("exceptionCallback stat %s channel %s\n",
	ca_message(stat),channel);
}

/************************************************************************/
/*                  epics connection callback                             */
/**************************************************************************/
static void connectionCallback(struct connection_handler_args args)
{
	chid        chid = args.chid;

	printChidInfo(chid,"connectionCallback");
}

/************************************************************************/
/*                  epics rights changed callback                         */
/**************************************************************************/
static void accessRightsCallback(struct access_rights_handler_args args)
{
	chid        chid = args.chid;
		
	printChidInfo(chid,"accessRightsCallback");
}

/************************************************************************/
/*            Event callback is called when a value changes               */
/**************************************************************************/
static void eventCallback(struct event_handler_args eha)
{
	chid        chid = eha.chid;
	double	fs,seconds;
	/*
	MYNODE  *node;
	*/
	unsigned int *ndata;

	if(eha.status!=ECA_NORMAL) {
		printChidInfo(chid,"eventCallback error");
		return;
	} 

	/************************************************************************/
	/*            check if if the image aray has been sent                    */
	/*            if so call displayme to display image                       */
	/**************************************************************************/
	if(!strcmp(ca_name(chid),mystrcat(camera,":data"))){
		data = (unsigned char *)eha.dbr;
		mycount++;
		size=eha.count;
		gettimeofday(&startime,NULL);
		displayme();
		gettimeofday(&endtime,NULL);
		seconds = calc(&startime,&endtime)/1000.0;
		if(mycount%100==0){
			printf("size=%d, ",size);
			printf("count=%d, ",mycount);
			printf("display took %f seconds, ",seconds);
			seconds = calc(&counttime,&endtime)/1000.0;
			printf("framerate=%f frames/second\n",100.0/seconds);
			gettimeofday(&counttime,NULL);
		}
		return;
	}

	/************************************************************************/
	/*            check if if the image width has been sent                   */
	/**************************************************************************/
	if(!strcmp(ca_name(chid),mystrcat(camera,":width"))){
		width = *(unsigned int *)eha.dbr;
		printf("width=%d\n",width);
		return;
	}

	/************************************************************************/
	/*            check if if the image Height has been sent                  */
	/**************************************************************************/
	if(!strcmp(ca_name(chid),mystrcat(camera,":height"))){
		height = *(unsigned int *)eha.dbr;
		printf("height=%d\n",height);
		return;
	}

	/************************************************************************/
	/*            check if bytes per pixel has been sent                      */
	/**************************************************************************/
	if(!strcmp(ca_name(chid),mystrcat(camera,":bayerConv"))){
		iBayerConversion = *(unsigned int *)eha.dbr;
		printf("iBayerConversion=%d\n",iBayerConversion);
		return;
	}

	/************************************************************************/
	/*            check if bytes per pixel has been sent                      */
	/**************************************************************************/
	if(!strcmp(ca_name(chid),mystrcat(camera,":colorFilter"))){
		iColorFilter = *(unsigned int *)eha.dbr;
		printf("iColorFilter=%d\n",iColorFilter);
		return;
	}

	/************************************************************************/
	/*            check if bytes per pixel has been sent                      */
	/**************************************************************************/
	if(!strcmp(ca_name(chid),mystrcat(camera,":code"))){
		code = *(unsigned int *)eha.dbr;
		printf("code=%d\n",code);
		return;
	}

	/************************************************************************/
	/*            check if bytes per pixel has been sent                      */
	/**************************************************************************/
	if(!strcmp(ca_name(chid),mystrcat(camera,":bpp"))){
		bpp = *(unsigned int *)eha.dbr;
		printf("bpp=%d\n",bpp);
		return;
	}
}


/************************************************************************/
/*            UpdateEpics is called by hte x display loop every 100ms     */
/*            it just has to call ca_poll to read buffers                 */
/**************************************************************************/
void UpdateEpics(Widget w, XtIntervalId *id) {
	int result ;
	XtIntervalId timerid ;

	result = ca_poll();
	timerid = XtAddTimeOut(10, (XtTimerCallbackProc) UpdateEpics, w);
}

/************************************************************************/
/*                            main program                                */
/**************************************************************************/

main(int argc, char *argv[]) {
	int foreground,background;
	int ac;
	int x,i;
	int         npv = 1;
	/*
	MYNODE      *pmynode[10];
	*/
	char        *pname[10];
	XtIntervalId timerid;
	evid 	myevid;
	evid 	data_evid;
	chid    mychid;
	chid    mychid1;
	chid    mychid2;
	chid    mychid3;
	chid    mychid4;
	chid    mychid5;
	chid    mychid6;
	chid    data_chid;
	chid    width_chid;
	chid    height_chid;

	printf("firewire \n");
	strcpy(camera,"camera1"); /* default camera name */

	if (argc > 1){
		printf("camera = %s\n",argv[1]);
		strcpy(camera,argv[1]);
	}

	/*************************************************************************/
	/*            Initialize Epics - read width and height                    */
	/**************************************************************************/
	SEVCHK(ca_task_initialize(),"ca_task_initialize");
	SEVCHK(ca_search(mystrcat(camera,":width"),&mychid1),"ca_search failure");
	SEVCHK(ca_search(mystrcat(camera,":height"),&mychid2),"ca_search failure");
	SEVCHK(ca_search(mystrcat(camera,":bpp"),&mychid3),"ca_search failure");
	SEVCHK(ca_search(mystrcat(camera,":code"),&mychid4),"ca_search failure");
	SEVCHK(ca_search(mystrcat(camera,":bayerConv"),&mychid5),"ca_search failure");
	SEVCHK(ca_search(mystrcat(camera,":colorFilter"),&mychid6),"ca_search failure");
	SEVCHK(ca_pend_io(10.0),"ca_pend_io failure");
	SEVCHK(ca_get(DBR_INT,mychid1,&width),"ca_get failure");
	SEVCHK(ca_get(DBR_INT,mychid2,&height),"ca_get failure");
	SEVCHK(ca_get(DBR_INT,mychid3,&bpp),"ca_get failure");
	SEVCHK(ca_get(DBR_INT,mychid4,&code),"ca_get failure");
	SEVCHK(ca_get(DBR_INT,mychid5,&iBayerConversion),"ca_get failure");
	SEVCHK(ca_get(DBR_INT,mychid6,&iColorFilter),"ca_get failure");
	SEVCHK(ca_pend_io(10.0),"ca_pend_io failure");
	SEVCHK(ca_clear_channel(mychid1),"ca_clear_channel failure");
	SEVCHK(ca_clear_channel(mychid2),"ca_clear_channel failure");
	SEVCHK(ca_clear_channel(mychid3),"ca_clear_channel failure");
	SEVCHK(ca_clear_channel(mychid4),"ca_clear_channel failure");
	SEVCHK(ca_clear_channel(mychid5),"ca_clear_channel failure");
	SEVCHK(ca_clear_channel(mychid6),"ca_clear_channel failure");
	SEVCHK(ca_task_exit(),"ca_task_exit failure");

	printf("width=%d =height%d\n",width, height);

/*
	oldwidth=width;
	oldheight=height;
*/

	/*************************************************************************/
	/*            define the toplevel window                                  */
	/**************************************************************************/
	toplevel=XtInitialize(argv[0],"",NULL,0,&argc,argv);

	/**************************************************************************/
	/*            define the buletin board - a container widget               */
	/**************************************************************************/
	XtSetArg( al[0], XmNheight,height+40);
	XtSetArg( al[1], XmNwidth,width+40);
	bb=XtCreateManagedWidget("bb",xmBulletinBoardWidgetClass,toplevel,al,2);

	/**************************************************************************/
	/*            define the drawing area widget - and put in buletin board   */
	/**************************************************************************/
	XtSetArg(al[0], XmNheight,height);
	XtSetArg(al[1], XmNwidth,width);
	XtSetArg(al[2],XmNx,20);
	XtSetArg(al[3],XmNy,20);
	drawing_area=XtCreateManagedWidget("drawing_area", xmDrawingAreaWidgetClass, bb,al,4);

	/**************************************************************************/
	/*            display widgets                                             */
	/**************************************************************************/
	XtManageChild(drawing_area);
	XtManageChild(bb);
	XtRealizeWidget(toplevel);

	/**************************************************************************/
	/*            Create the Graphics Context (GC)                            */
	/**************************************************************************/
	gc= XCreateGC(XtDisplay(drawing_area),XtWindow(drawing_area), GCForeground | GCBackground , &vals);

	/*************************************************************************/
	/*         Setup the Epics callbacks to get data                          */
	/**************************************************************************/
	SEVCHK(ca_create_channel(
		mystrcat(camera,":data"),
		connectionCallback,
		NULL,
		20,
		&mychid),
		"ca_create_channel");
	SEVCHK(ca_create_subscription(
		DBF_CHAR,
		height*width*bpp,
		mychid,
		DBE_VALUE,
		eventCallback,
		NULL,
		&myevid),
		"ca_create_subscription");

	/*************************************************************************/
	/*         Setup the Epics callbacks to get width                         */
	/**************************************************************************/
	SEVCHK(ca_create_channel(
		mystrcat(camera,":width"),
		connectionCallback,
		NULL,
		20,
		&mychid),
		"ca_create_channel");
	SEVCHK(ca_create_subscription(
		DBF_INT,
		1,
		mychid,
		DBE_VALUE,
		eventCallback,
		NULL,
		&myevid),
		"ca_create_subscription");

	/************************************************************************/
	/*         Setup the Epics callbacks to get height                        */
	/**************************************************************************/
	SEVCHK(ca_create_channel(
		mystrcat(camera,":height"),
		connectionCallback,
		NULL,
		20,
		&mychid),
		"ca_create_channel");
	SEVCHK(ca_create_subscription(
		DBF_INT,
		1,
		mychid,
		DBE_VALUE,
		eventCallback,
		NULL,
		&myevid),
		"ca_create_subscription");

	/************************************************************************/
	/*         Setup the Epics callbacks to get bytes per pixel               */
	/**************************************************************************/
	SEVCHK(ca_create_channel(
		mystrcat(camera,":bpp"),
		connectionCallback,
		NULL,
		20,
		&mychid),
		"ca_create_channel");
	SEVCHK(ca_create_subscription(
		DBF_INT,
		1,
		mychid,
		DBE_VALUE,
		eventCallback,
		NULL,
		&myevid),
		"ca_create_subscription");

	/************************************************************************/
	/*         Setup the Epics callbacks to get pixel coding                  */
	/**************************************************************************/
	SEVCHK(ca_create_channel(
		mystrcat(camera,":code"),
		connectionCallback,
		NULL,
		20,
		&mychid),
		"ca_create_channel");
	SEVCHK(ca_create_subscription(
		DBF_INT,
		1,
		mychid,
		DBE_VALUE,
		eventCallback,
		NULL,
		&myevid),
		"ca_create_subscription");


	gettimeofday(&startime,NULL);

	/*************************************************************************/
	/*         Setup the Epics callbacks to get width                         */
	/**************************************************************************/
	SEVCHK(ca_create_channel(
		mystrcat(camera,":bayerConv"),
		connectionCallback,
		NULL,
		20,
		&mychid),
		"ca_create_channel");
	SEVCHK(ca_create_subscription(
		DBF_INT,
		1,
		mychid,
		DBE_VALUE,
		eventCallback,
		NULL,
		&myevid),
		"ca_create_subscription");

	/*************************************************************************/
	/*         Setup the Epics callbacks to get width                         */
	/**************************************************************************/
	SEVCHK(ca_create_channel(
		mystrcat(camera,":colorFilter"),
		connectionCallback,
		NULL,
		20,
		&mychid),
		"ca_create_channel");
	SEVCHK(ca_create_subscription(
		DBF_INT,
		1,
		mychid,
		DBE_VALUE,
		eventCallback,
		NULL,
		&myevid),
		"ca_create_subscription");


	/********************************************************************/
	/*            start x loop                                            */
	/**********************************************************************/
	timerid=XtAddTimeOut(10,(XtTimerCallbackProc)UpdateEpics,toplevel);
	XtMainLoop();
}
