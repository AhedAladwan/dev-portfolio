/***********************************************************************************/
/**                         yuv2ppm                                             ****/
/**                  reads yuv file and creates ppm file                        ****/
/***********************************************************************************/

#include <stdio.h>
#include <stdlib.h>

#define PPM_FILE_NAME "Image.ppm"
#define YUV_FILE_NAME "Image.yuv"
#define W 640
#define H 480

int main(int argc, char *argv[]) 
{
   FILE* ppmfile;
   FILE* yuvfile;
   long i;
   unsigned char  *yuv,*rgb,*rgb_p;
   unsigned int size;
   double y1,y2,u,v;
   double r1,g1,b1,r2,g2,b2;


   yuv  = (unsigned char *)malloc(W*H*2);
   rgb  = (unsigned char *)malloc(W*H*3);
   rgb_p = rgb;

   if((yuvfile=fopen(YUV_FILE_NAME, "r"))==NULL){
 	perror( "Can't open '" YUV_FILE_NAME "'");
	exit( 1);
   }

   if((size=fread(yuv,1,W*H*2,yuvfile))<W*H*2) {
	fprintf(stderr,"can't read data\n");
	exit( 1);
   }

   fclose(yuvfile);

   /**************************************************************************/
   /*      read each group of four elements and set y, u and v               */
   /**************************************************************************/
    size = W*H/2;
    rgb = malloc(size*6);
    rgb_p = rgb;

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



   if((ppmfile=fopen(PPM_FILE_NAME, "w"))==NULL){
	perror( "Can't create '" PPM_FILE_NAME "'");
	exit( 1);
   }

   fprintf(ppmfile,"P6\n%u %u 255\n", W,H);

   fwrite(rgb, 1, H*W*3, ppmfile);

   fclose(ppmfile);

   printf("wrote: " PPM_FILE_NAME "\n");


   return 0;
}
