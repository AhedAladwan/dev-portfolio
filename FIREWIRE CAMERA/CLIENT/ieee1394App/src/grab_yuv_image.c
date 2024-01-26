
#include <stdio.h>
#include <libraw1394/raw1394.h>
#include <libdc1394/dc1394_control.h>
#include <stdlib.h>

#define PPM_FILE_NAME "Image.ppm"
#define YUV_FILE_NAME "Image.yuv"
#define W 640
#define H 480

/****************************************************************************/
/*              TIMING                                                      */
/****************************************************************************/
float calc(struct timeval *one, struct timeval *two){
	return( ((two->tv_sec - one->tv_sec) * 1000 ) +  ((two->tv_usec -one->tv_usec)/1000) ) ;
}


int main(int argc, char *argv[]) 
{
  FILE* ppmfile;
  FILE* yuvfile;
  dc1394_cameracapture camera;
  int numNodes;
  int numCameras;
  raw1394handle_t handle;
  nodeid_t * camera_nodes;
  dc1394_feature_set features;
  struct timeval  startime,endtime;
  dc1394_miscinfo camera_misc_info;
  long i;
  unsigned char *yuv;  /* pointer to camera memory buffer */
  unsigned char *rgb,*rgb_p;  /* array of rgb vals */
  unsigned int size;
  double y1,y2,u,v;
  double r1,g1,b1,r2,g2,b2;
  float x;


  /*-----------------------------------------------------------------------
   *  Open ohci and asign handle to it
   *-----------------------------------------------------------------------*/
  handle = dc1394_create_handle(0);
  if (handle==NULL)
  {
    fprintf( stderr, "Unable to aquire a raw1394 handle\n\n"
             "Please check \n"
	     "  - if the kernel modules `ieee1394',`raw1394' and `ohci1394' are loaded \n"
	     "  - if you have read/write access to /dev/raw1394\n\n");
    exit(1);
  }

  
  /*-----------------------------------------------------------------------
   *  get the camera nodes and describe them as we find them
   *-----------------------------------------------------------------------*/
   numNodes = raw1394_get_nodecount(handle);
   camera_nodes = dc1394_get_camera_nodes(handle,&numCameras,1);
   fflush(stdout);
   if (numCameras<1) {
	fprintf( stderr, "no cameras found :(\n");
	dc1394_destroy_handle(handle);
	exit(1);
   }
   printf("working with the first camera on the bus\n");
  
  /*-----------------------------------------------------------------------
   *  to prevent the iso-transfer bug from raw1394 system, check if
   *  camera is highest node. For details see 
   *-----------------------------------------------------------------------*/
   if( camera_nodes[0] == numNodes-1) {
	fprintf( stderr, "\n" "Sorry, your camera is the highest numbered node\n");
	dc1394_destroy_handle(handle);
	/*
	dc1394_free_camera_nodes(camera_nodes);
	*/
	exit( 1);
   }
  
   /**************************************************************************/
   /*                     get camera misc info                               */
   /**************************************************************************/
   if(dc1394_get_camera_misc_info(handle,camera_nodes[0],&camera_misc_info)!=DC1394_SUCCESS) {
	printf("error getting info set \n");
	exit(1);
   }
   printf("format = %d\n",camera_misc_info.format);
   printf("mode = %d\n",camera_misc_info.mode);
   printf("framerate = %d\n",camera_misc_info.framerate);

  /*-----------------------------------------------------------------------
   *  setup capture
   *-----------------------------------------------------------------------*/
  if (dc1394_setup_capture(handle,camera_nodes[0],
                           0, 
                           camera_misc_info.format,
                           camera_misc_info.mode,
                           SPEED_400,
                           camera_misc_info.framerate,
                           &camera)!=DC1394_SUCCESS) {
	fprintf( stderr,"unable to setup camera-\n");
	dc1394_release_camera(handle,&camera);
	dc1394_destroy_handle(handle);
	/*
	dc1394_free_camera_nodes(camera_nodes);
	*/
	exit(1);
  }

  /*-----------------------------------------------------------------------
   *  have the camera start sending us data
   *-----------------------------------------------------------------------*/
  if (dc1394_start_iso_transmission(handle,camera.node) !=DC1394_SUCCESS) {
	fprintf( stderr, "unable to start camera iso transmission\n");
	dc1394_release_camera(handle,&camera);
	dc1394_destroy_handle(handle);
	exit(1);
  }

  /*-----------------------------------------------------------------------
   *  capture one frame
   *-----------------------------------------------------------------------*/
   gettimeofday(&startime,NULL);
  if (dc1394_single_capture(handle,&camera)!=DC1394_SUCCESS) {
	fprintf( stderr, "unable to capture a frame\n");
	dc1394_release_camera(handle,&camera);
	dc1394_destroy_handle(handle);
	exit(1);
  }
  if (dc1394_single_capture(handle,&camera)!=DC1394_SUCCESS) {
	fprintf( stderr, "unable to capture a frame\n");
	dc1394_release_camera(handle,&camera);
	dc1394_destroy_handle(handle);
	exit(1);
  }
  gettimeofday(&endtime,NULL);
  printf("capture took %fms\n",calc(&startime,&endtime));

   yuv = (unsigned char *)camera.capture_buffer;

   /**************************************************************************/
   /*             Write the raw yuv data to a file                           */
   /**************************************************************************/

   if((yuvfile=fopen(YUV_FILE_NAME, "w"))==NULL){
	perror( "Can't create '" YUV_FILE_NAME "'");
	dc1394_release_camera(handle,&camera);
	dc1394_destroy_handle(handle);
	exit( 1);
   }
       
   fwrite(yuv, 1, W*H*2, yuvfile);
   fclose(yuvfile);
   printf("wrote: " YUV_FILE_NAME "\n");

  
  yuv = (unsigned char *)camera.capture_buffer;
    

  /* read each group of four elements and set y, u and v   */
  size = camera.frame_width*camera.frame_height/2;
  rgb = malloc(size*6);
  rgb_p = rgb;
  gettimeofday(&startime,NULL);
  for (i=0;i<size;i++){

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

	*rgb_p++ = r1;
	*rgb_p++ = g1;
	*rgb_p++ = b1;
	*rgb_p++ = r2;
	*rgb_p++ = g2;
	*rgb_p++ = b2;
  }
  gettimeofday(&endtime,NULL);
  printf("calc took %fms\n",calc(&startime,&endtime));

  /*-----------------------------------------------------------------------
   *  save image as 'Image.ppm'
   *-----------------------------------------------------------------------*/
  if((ppmfile=fopen(PPM_FILE_NAME, "w"))==NULL){;
    perror( "Can't create '" PPM_FILE_NAME "'");
    dc1394_release_camera(handle,&camera);
    dc1394_destroy_handle(handle);
    exit( 1);
  }
  fprintf(ppmfile,"P6\n%u %u 255\n", camera.frame_width,camera.frame_height);
  fwrite(rgb, 1, size*6, ppmfile);

  printf("width=%d height=%d tot=%d\n",camera.frame_width,camera.frame_height,camera.frame_width*camera.frame_height);
  fclose(ppmfile);
  printf("wrote: " PPM_FILE_NAME "\n");

  /*-----------------------------------------------------------------------
   *  Close camera
   *-----------------------------------------------------------------------*/
  dc1394_release_camera(handle,&camera);
  dc1394_destroy_handle(handle);
  return 0;
}
