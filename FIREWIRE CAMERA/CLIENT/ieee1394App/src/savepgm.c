/**************************************************************************/
/*            savepgm.c  - an Epics ca client to save                     */
/*            pgm images from a firewire camera                           */
/**************************************************************************/


#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <cadef.h>
#include <envDefs.h>

/************************************************************************/
/*                            main program                              */
/************************************************************************/

int main(int argc, char *argv[]) {
    FILE    *pgmfile;
    chid    mychid;
    chid    mychid1;
    chid    mychid2;
    char    filename[80];
    char    datarecord[29];
    char    widthrecord[29];
    char    heightrecord[29];
    int     size, width, height;
    unsigned char   *data;
    char    arraysize[64];
	
    if (argc <  2) {
        fprintf(stderr,"usage: %s camera-name [filename] \n",argv[0]);
        exit(1);
    }

    if (argc ==  3) {
        sprintf(filename,"%s",argv[2]);
    } else {
        sprintf(filename,"%s.pgm",argv[1]);
    }
     
        sprintf(widthrecord,"%s:width",argv[1]);
        sprintf(heightrecord,"%s:height",argv[1]);
        sprintf(datarecord,"%s:data",argv[1]);
/*	
        fprintf(stderr,"DEBUG: width=%s height=%s \n",widthrecord,heightrecord);
 */
	SEVCHK(ca_task_initialize(),"ca_task_initialize");
	SEVCHK(ca_search(widthrecord,&mychid1),"ca_search failure");
	SEVCHK(ca_pend_io(5.0),"ca_pend_io failure");
	SEVCHK(ca_get(DBR_LONG,mychid1,&width),"ca_get failure");
	SEVCHK(ca_pend_io(5.0),"ca_pend_io failure");
	SEVCHK(ca_search(heightrecord,&mychid2),"ca_search failure");
	SEVCHK(ca_pend_io(5.0),"ca_pend_io failure");
	SEVCHK(ca_get(DBR_LONG,mychid2,&height),"ca_get failure");
	SEVCHK(ca_pend_io(5.0),"ca_pend_io failure");
	SEVCHK(ca_task_exit(),"ca_task_exit failure");

	size = width*height;
        sprintf(arraysize, "%d", size);
        epicsEnvSet ( "EPICS_CA_MAX_ARRAY_BYTES", arraysize );
        
	data = (char *)malloc(size);
/*	
        fprintf(stderr,"DEBUG: width=%d height=%d size=%d EPICS_CA_MAX_ARRAY_BYTES=%s\n",
            width,height,size,arraysize);
            
        EPICS_CA_MAX_ARRAY_BYTES needs to be set before ca_task_initialize
*/
        
	SEVCHK(ca_task_initialize(),"ca_task_initialize");
        
	SEVCHK(ca_search(datarecord,&mychid),"ca_search failure");
	SEVCHK(ca_pend_io(5.0),"ca_pend_io failure");
	SEVCHK(ca_array_get(DBF_CHAR,size,mychid,(void *)data),"ca_array_get failure");
	SEVCHK(ca_pend_io(5.0),"ca_pend_io failure");

	SEVCHK(ca_task_exit(),"ca_task_exit failure");


	if((pgmfile = fopen(filename,"w"))==NULL){
		perror( "Can't create pgm file");
		return 0;
	}

	fprintf(pgmfile,"P5\n%u %u 255\n", width,height);
	fwrite(data, 1, size, pgmfile);
	fclose(pgmfile);

	printf("written image width=%d height=%d size=%d to file %s \n",width, height,size,filename);
        
        return 0;
}
