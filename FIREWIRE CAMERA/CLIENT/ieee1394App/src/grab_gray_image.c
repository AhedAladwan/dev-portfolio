
#include <stdio.h>
#include <libraw1394/raw1394.h>
#include <libdc1394/dc1394_control.h>
#include <stdlib.h>

#define IMAGE_FILE_NAME "Image.pgm"

/****************************************************************************/
/*              TIMING                                                      */
/****************************************************************************/
float calc(struct timeval *one, struct timeval *two){
	return( ((two->tv_sec - one->tv_sec) * 1000 ) +  ((two->tv_usec -one->tv_usec)/1000) ) ;
}


int main(int argc, char *argv[]) 
{
  FILE* imagefile;
  dc1394_cameracapture camera;
  int numNodes;
  int numCameras;
  raw1394handle_t handle;
  nodeid_t * camera_nodes;
  dc1394_feature_set features;
  struct timeval  startime,endtime;
  dc1394_miscinfo camera_misc_info;
  long i;
  unsigned char *ptr;


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
  /*
  dc1394_free_camera_nodes(camera_nodes);
  */
  
  /* set trigger mode */
    /*
  if( dc1394_set_trigger_mode(handle, camera.node, TRIGGER_MODE_0)
      != DC1394_SUCCESS)
  {
    fprintf( stderr, "unable to set camera trigger mode\n");
    #if 0
    dc1394_release_camera(handle,&camera);
    dc1394_destroy_handle(handle);
    exit(1);
    #endif
  }
  */
  

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
   printf("before capture frame\n");
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
  printf("that took me %fms\n",calc(&startime,&endtime));

   printf("after capture frame\n");

  /*-----------------------------------------------------------------------
   *  Stop data transmission
   *-----------------------------------------------------------------------*/
   /*
  if (dc1394_stop_iso_transmission(handle,camera.node)!=DC1394_SUCCESS) 
  {
    printf("couldn't stop the camera?\n");
  }
  */

  /*-----------------------------------------------------------------------
   *  save image as 'Image.pgm'
   *-----------------------------------------------------------------------*/
  imagefile=fopen(IMAGE_FILE_NAME, "w");

  if( imagefile == NULL)
  {
    perror( "Can't create '" IMAGE_FILE_NAME "'");
    dc1394_release_camera(handle,&camera);
    dc1394_destroy_handle(handle);
    exit( 1);
  }
  
  ptr = (unsigned char *)camera.capture_buffer;
    
  fprintf(imagefile,"P5\n%u %u 255\n", camera.frame_width,camera.frame_height);
  for (i=0;i<camera.frame_height*camera.frame_width;i++){
  	fprintf(imagefile,"%c", (int)ptr[i]);
  }
  /*
  fwrite((const char *)camera.capture_buffer, 1,
         camera.frame_height*camera.frame_width, imagefile);
  */
  fclose(imagefile);
  printf("wrote: " IMAGE_FILE_NAME "\n");

  /*-----------------------------------------------------------------------
   *  Close camera
   *-----------------------------------------------------------------------*/
  dc1394_release_camera(handle,&camera);
  dc1394_destroy_handle(handle);
  return 0;
}
