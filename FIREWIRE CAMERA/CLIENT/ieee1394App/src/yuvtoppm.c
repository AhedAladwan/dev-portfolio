/* yuvtoppm.c - convert Abekas YUV bytes into a portable pixmap
**
** by Marc Boucher
** Internet: marc@PostImage.COM
** 
** Based on Example Conversion Program, A60/A64 Digital Video Interface
** Manual, page 69
**
** Uses integer arithmetic rather than floating point for better performance
**
** Copyright (C) 1991 by DHD PostImage Inc.
** Copyright (C) 1987 by Abekas Video Systems Inc.
** Copyright (C) 1991 by Jef Poskanzer.
**
** Permission to use, copy, modify, and distribute this software and its
** documentation for any purpose and without fee is hereby granted, provided
** that the above copyright notice appear in all copies and that both that
** copyright notice and this permission notice appear in supporting
** documentation.  This software is provided "as is" without express or
** implied warranty.
*/

/*
#include "ppm.h"
#include "mallocvar.h"
*/
#include "stdlib.h"
#include "stdio.h"

/* x must be signed for the following to work correctly */
#define limit(x) ((((x)>0xffffff)?0xff0000:(((x)<=0xffff)?0:(x)&0xff0000))>>16)

typedef unsigned char pixel;

/****************************************************************************/
/*              TIMING                                                      */
/****************************************************************************/
float calc(struct timeval *one, struct timeval *two){
	        return( ((two->tv_sec - one->tv_sec) * 1000 ) +  ((two->tv_usec -one->tv_usec)/1000) ) ;
}

int
main(argc, argv) 
   char          **argv; {

   FILE           *ifp;
   FILE           *imagefile;
   unsigned char  *pixrow;
   int             argn, rows, cols, row;
   const char     * const usage = "<width> <height> [yuvfile]";
   struct yuv {
	unsigned char u;
	unsigned char y1;
	unsigned char v;
	unsigned char y2;
   } *yuvbuf;
   struct timeval  startime,endtime;

   cols = 640;
   rows = 480;

   if((ifp  = fopen("Image.rgb","r")) == NULL){
	fprintf(stderr,"unable to open file for reading\n");
	exit(1);
   }
   if((imagefile  = fopen("Image2.ppm","w"))==NULL){
	fprintf(stderr,"unable to open Imagefile2.ppm for writing\n");
	exit(1);
   }

   fprintf(stderr,"rows %d cols %d \n",rows,cols);

   fprintf(imagefile,"P6\n%u %u 255\n",cols, rows);

   pixrow = malloc(cols*3);
   yuvbuf=malloc(cols+1);
   if (yuvbuf == NULL) {
	printf("Unable to allocate YUV buffer for %d columns.", cols);
   }

   gettimeofday(&startime,NULL);

   for (row = 0; row < rows; ++row) {
	int    col;

	/*
	fread(yuvbuf, cols * 2, 1, ifp);
	*/

	for (col = 0; col < cols; col += 2) {
		int y1, u, v, y2, r, g, b;

		u = yuvbuf[col/2].u-128;
		y1 = yuvbuf[col/2].y1 - 16;
		if (y1 < 0) y1 = 0;
		v = yuvbuf[col/2].v - 128;
		y2 = yuvbuf[col/2].y2 - 16;
		if (y2 < 0) y2 = 0;
		r = 104635 * v;
		g = -25690 * u + -53294 * v;
		b = 132278 * u;
		y1*=76310; y2*=76310;

		pixrow[(col*3)+0]= limit(r+y1);
		pixrow[(col*3)+1]= limit(g+y1);
		pixrow[(col*3)+2]= limit(b+y1);
		pixrow[(col*3)+3]= (r+y2);
		pixrow[(col*3)+4]= (g+y2);
		pixrow[(col*3)+5]= (b+y2);

		/*
		pixrow[(col*3)+0]= limit(r+y1);
		pixrow[(col*3)+1]= limit(g+y1);
		pixrow[(col*3)+2]= limit(b+y1);
		*/
		/*
		PPM_ASSIGN(pixrow[col], limit(r+y1), limit(g+y1), limit(b+y1));
		PPM_ASSIGN(pixrow[col+1], limit(r+y2), limit(g+y2), limit(b+y2));
		*/
	}

	/*
	fwrite(pixrow, 1, 640*3, imagefile);
	*/
   }
   gettimeofday(&endtime,NULL);
   fprintf(stderr,"calc took %fms\n",calc(&startime,&endtime));

   free(yuvbuf);
   free(pixrow);
   close(ifp);
   close(stdout);

   exit(0);
}
