
#include <stdio.h>
#include <libraw1394/raw1394.h>
#include <libdc1394/dc1394_control.h>
#include <stdlib.h>

#define IMAGE_FILE_NAME "Image.ppm"

int main(int argc, char *argv[]) 
{
  FILE* imagefile;
  long i;
  unsigned char *ptr;


  imagefile=fopen(IMAGE_FILE_NAME, "w");

  if( imagefile == NULL)
  {
    perror( "Can't create '" IMAGE_FILE_NAME "'");
    exit( 1);
  }
  
    
  fprintf(imagefile,"P6\n%u %u 255\n", 640,480);
  for (i=0;i<640*480;i++){
  	fprintf(imagefile,"%c%c%c", 128,0,0);
  }
  fclose(imagefile);
  printf("wrote: " IMAGE_FILE_NAME "\n");

  return 0;
}
