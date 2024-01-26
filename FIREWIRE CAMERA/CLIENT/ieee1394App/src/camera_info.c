
#include <stdio.h>
#include <libraw1394/raw1394.h>
#include <libdc1394/dc1394_control.h>
#include <stdlib.h>

#define IMAGE_FILE_NAME "Image.pgm"

int main(int argc, char *argv[]) 
{
  FILE* imagefile;
  dc1394_cameracapture camera;
  raw1394handle_t handle;
  nodeid_t * camera_nodes;
  dc1394_feature_set camera_features;
  dc1394_camerainfo camera_info;
  dc1394_miscinfo camera_misc_info;
  int numNodes;
  int numCameras;
  int capture_size;
  int trigger_mode;
  int trigger_polarity;
  int trigger_on_off;
  quadlet_t formats;
  quadlet_t modes;

  char *rawversion;

  rawversion = raw1394_get_libversion();

  printf("libraw version = %s\n",rawversion);

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
/*
  trigger_mode=raw1394_reset_bus(handle);
  trigger_mode=raw1394_reset_bus_new(handle,RAW1394_LONG_RESET);
*/
  if(trigger_mode != 0)
    printf("BUS RESET FAILED\n");
  else
    printf("BUS RESET OK\n");
  
  /*-----------------------------------------------------------------------
   *  get the camera nodes and describe them as we find them
   *-----------------------------------------------------------------------*/
  numNodes = raw1394_get_nodecount(handle);
  printf("nodes=%d\n",numNodes);
  camera_nodes = dc1394_get_camera_nodes(handle,&numCameras,1);
  fflush(stdout);
  if (numCameras<1)
  {
    fprintf( stderr, "no cameras found :(\n");
    dc1394_destroy_handle(handle);
    exit(1);
  }
  printf("working with the first camera on the bus\n");
  printf("camera node is %d\n",camera_nodes[0]);
  
  /*-----------------------------------------------------------------------
   *  to prevent the iso-transfer bug from raw1394 system, check if
   *  camera is highest node. For details see 
   *  http://linux1394.sourceforge.net/faq.html#DCbusmgmt
   *  and
   *  http://sourceforge.net/tracker/index.php?func=detail&aid=435107&group_id=8157&atid=108157
   *-----------------------------------------------------------------------*/
  if( camera_nodes[0] == numNodes-1)
  {
    fprintf( stderr, "\n"
             "Sorry, your camera is the highest numbered node\n"
             "of the bus, and has therefore become the root node.\n"
             "The root node is responsible for maintaining \n"
             "the timing of isochronous transactions on the IEEE \n"
             "1394 bus.  However, if the root node is not cycle master \n"
             "capable (it doesn't have to be), then isochronous \n"
             "transactions will not work.  The host controller card is \n"
             "cycle master capable, however, most cameras are not.\n"
             "\n"
             "The quick solution is to add the parameter \n"
             "attempt_root=1 when loading the OHCI driver as a \n"
             "module.  So please do (as root):\n"
             "\n"
             "   rmmod ohci1394\n"
             "   insmod ohci1394 attempt_root=1\n"
             "\n"
             "for more information see the FAQ at \n"
             "http://linux1394.sourceforge.net/faq.html#DCbusmgmt\n"
             "\n");
    dc1394_destroy_handle(handle);
    /*
    dc1394_free_camera_nodes(camera_nodes);
    */
    exit( 1);
  }
  
  /**************************************************************************/
  /*                     get camera features                                */
  /**************************************************************************/

  if(dc1394_get_camera_feature_set(handle,camera_nodes[0],&camera_features)!=DC1394_SUCCESS) {
	  printf("error getting feature set \n");
	  exit(1);
  }
  dc1394_print_feature_set(&camera_features);


  /**************************************************************************/
  /*                     get camera info                                    */
  /**************************************************************************/
  if(dc1394_get_camera_info(handle,camera_nodes[0],&camera_info)!=DC1394_SUCCESS) {
	  printf("error getting info set \n");
	  exit(1);
  }
  dc1394_print_camera_info(&camera_info);
  printf("id = %d\n",camera_info.id);
  printf("model = %s\n",camera_info.model);
  printf("vendor = %s\n",camera_info.vendor);

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

  /**************************************************************************/
  /*                     get camera capture buffer size                     */
  /**************************************************************************/
  if(dc1394_get_capture_size(handle,camera_nodes[0],&capture_size)!=DC1394_SUCCESS) {
          printf("error getting capture_size \n");
          exit(1);
  }
  printf("capture_size = %d\n",capture_size);

  /**************************************************************************/
  /*                     get camera trigger_mode                            */
  /**************************************************************************/
  if(dc1394_get_trigger_mode(handle,camera_nodes[0],&trigger_mode)!=DC1394_SUCCESS) {
          printf("error getting trigger_mode \n");
          exit(1);
  }
  printf("trigger_mode = %d\n",trigger_mode);

  /**************************************************************************/
  /*                     get camera trigger_polarity                            */
  /**************************************************************************/
  if(dc1394_get_trigger_polarity(handle,camera_nodes[0],&trigger_polarity)!=DC1394_SUCCESS) {
          printf("error getting trigger_polarity \n");
          exit(1);
  }
  printf("trigger_polarity = %d\n",trigger_polarity);

  /**************************************************************************/
  /*                     get camera trigger_on_off                            */
  /**************************************************************************/
  if(dc1394_get_trigger_on_off(handle,camera_nodes[0],&trigger_on_off)!=DC1394_SUCCESS) {
          printf("error getting trigger_on_off \n");
          exit(1);
  }
  printf("trigger_on_off = %d\n",trigger_on_off);

  /**************************************************************************/
  /*                     get camera formats and modes                         */
  /**************************************************************************/
  if(dc1394_query_supported_formats(handle,camera_nodes[0],&formats)!=DC1394_SUCCESS) {
          printf("error getting query_supported_formats \n");
          exit(1);
  }
  printf("formats supported = %X\n",(unsigned int)formats);

  if (formats & (0x1 <<31 )) {
	printf("format 0 supported\n");
  }

  if (formats & (0x1 <<30 )) {
	printf("format 1 supported\n");
	if(dc1394_query_supported_modes(handle,camera_nodes[0],FORMAT_SVGA_NONCOMPRESSED_1,&modes)!=DC1394_SUCCESS) {
		printf("error getting supported_modes \n");
		exit(1);
	}
  	printf("format 1 modes supported = %X\n",(unsigned int)modes);
	printf("MIN=%X MAX=%X\n",MODE_FORMAT1_MIN,MODE_FORMAT1_MAX);
	if (modes & (0x1 << 31)){ printf("MODE_800x600_YUV422  supported\n");}
	if (modes & (0x1 << 30)){ printf("MODE_800x600_RGB     supported\n");}
	if (modes & (0x1 << 29)){ printf("MODE_800x600_MONO    supported\n");}
	if (modes & (0x1 << 28)){ printf("MODE_1024x768_YUV422 supported\n");}
	if (modes & (0x1 << 27)){ printf("MODE_1024x768_RGB    supported\n");}
	if (modes & (0x1 << 26)){ printf("MODE_1024x768_MONO   supported\n");}
	if (modes & (0x1 << 25)){ printf("MODE_800x600_MONO16  supported\n");}
	if (modes & (0x1 << 24)){ printf("MODE_1024x768_MONO16 supported\n");}
  }

  if (formats & (0x1 <<29 )) {
	printf("format 2 supported\n");
  }
  if (formats & (0x1 <<25 )) {
	printf("format 6 supported\n");
  }
  if (formats & (0x1 <<24 )) {
	printf("format 7 supported\n");
  }

  

  return 0;
}
