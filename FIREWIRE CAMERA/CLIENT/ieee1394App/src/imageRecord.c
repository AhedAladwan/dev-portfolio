/* imageRecord.c - */
/*
 *      Author:  Ned Arnold
 *      Date:    10-07-97
 *
 *      Experimental Physics and Industrial Control System (EPICS)
 *
 *      Copyright 1991, the Regents of the University of California,
 *      and the University of Chicago Board of Governors.
 *
 *      This software was produced under  U.S. Government contracts:
 *      (W-7405-ENG-36) at the Los Alamos National Laboratory,
 *      and (W-31-109-ENG-38) at Argonne National Laboratory.
 *
 *      Initial development by:
 *              The Controls and Automation Group (AT-8)
 *              Ground Test Accelerator
 *              Accelerator Technology Division
 *              Los Alamos National Laboratory
 *
 *      Co-developed with
 *              The Controls and Computing Group
 *              Accelerator Systems Division
 *              Advanced Photon Source
 *              Argonne National Laboratory
 *
 *****************************************************************************
 *
 * GENERAL DESCRIPTION
 * The image record is intended to be used to transfer a digitized image over
 * channel access. In order to circumvent the "16KByte Channel Access Limit",
 * the image record handles the image on a 'scan line' basis. The record  
 * contains 1024 scan line fields (.L0 thru .L1023). Each is a pointer
 * to an array of pixel data representing one scan line of the image.
 * The length of each array is defined using .XRES (pixels per scan line)
 * and the number of actual scan lines in the image is specified in .YRES.
 * 
 * The image record does NOT make a copy or move image data around. Given a
 * vxWorks symbol name that points to the image (.VXNM), the length of each 
 * scan line (.XRES), and the number of bytes per pixel (.SIZE), it calculates
 * pointers to the beginning of each scan line. When a caGet is performed
 * on a particular scan line field (.Lxxx), that scan line data is returned.
 *
 * REGION OF INTEREST
 * Maintaining this scan line orientation within the record makes it very
 * convenient for a CA Client to read only a portion of the image. The 
 * image record allows for a Region Of Interest (ROI) to be defined such
 * that a client can access only a portion of the image. The fields 
 * associated with the ROI are described below :
 *    
 *    RXST - Roi X STart - Specifies the starting pixel within the scan line
 *                         for a Region of Interest
 *    RXSZ - Roi X SiZe  - Specifies the number of pixels in each scan line
 *                         of the ROI 
 *    RYST - Roi Y STart - Specifies the starting scan line of the ROI
 *    RYSZ - Roi Y SiZe  - Specifies the number of scan lines in the ROI
 * 
 * If .RXSZ is non-zero, the array returned when a scan line is read is a
 * sub-array of the full length scan line. The sub-array is of size .RXSZ and
 * the offset used for the first pixel returned is .RXST. If .RXSZ is 0, the
 * entire scan line array (size = .XRES) is returned.
 * 
 * The ROI fields associated with the Y direction (.RYST and .RYSZ) are
 * not used by the image record. They are intended as a place holder for
 * fully defining the ROI. It is expected that a client interested in 
 * reading only ROI data will read these fields to decide which scan line
 * fields to fetch.
 *
 * RECORD PROCESSING
 * The only thing that occurs when an image record is processed is that the
 * .VAL field is incremented. If the database is configured such that the
 * image record is processed when a new image is available, simply monitoring
 * the .VAL field will inform the client when new data is available. The
 * value of the .VAL field can be used to keep track of how many images have 
 * been aquired.
 *
 * NO 'MONITOR' SUPPORT FOR SCAN LINES
 * The scan line fields (L0 thru L1023) do not 'post monitors'. The arrays
 * that these fields point to must be fetched using a caGet. There are 
 * <at least> two reasons for this. First, the array size may change if the
 * .RXSZ field is changed (ROI). When the size of an array changes from
 * one 'monitor' to the next, most clients are significantly affected. If
 * a client must perform a caGet, a well written client will check the 
 * length of an array and plan accordingly. Second, the amount of data 
 * transmitted may be very LARGE. It seems more appropriate to ask clients
 * to come get it rather than sending it to many clients who do not REALLY
 * NEED it every time.
 *
 *
 *****************************************************************************
 * Modification Log:
 * -----------------
 * 1.00  10-14-97  nda   VERSION 1.0 functional
 * 1.00  11-20-97  nda   added ENAB and RATE field (still 1.00)
 * 1.01  06-30-98  nda   changed scan line arrays from CHAR to UCHAR 
 */


#define VERSION 1.01


#include	<vxWorks.h>
#include	<types.h>
#include	<stdioLib.h>
#include	<lstLib.h>
#include        <sysSymTbl.h>
#include	<stdlib.h>
#include	<string.h>
#include        <tickLib.h>

#include	<alarm.h>
#include	<dbDefs.h>
#include	<dbAccess.h>
#include	<dbEvent.h>
#include	<dbFldTypes.h>
#include	<dbScan.h>
#include	<devSup.h>
#include	<errMdef.h>
#include	<recSup.h>
/*
  Because EPICS base is not in the standard include locations, I 
  modified the include line to get dbRecDes.h from the std
  place (and copied the header there)
 
#include        <../src/cvtDctsdr/dbRecDes.h>
*/

#include        <dbRecDes.h>

#include        <drvSNP24.h>
#define GEN_SIZE_OFFSET
#include	<imageRecord.h>
#undef  GEN_SIZE_OFFSET
/* Create RSET - Record Support Entry Table*/
#define report NULL
#define initialize NULL
static long init_record();
static long process();
#define special NULL
#define get_value NULL
static long cvt_dbaddr();
static long get_array_info();
static long put_array_info();
static long get_units();
static long get_precision();
#define get_enum_str NULL
#define get_enum_strs NULL
#define put_enum_str NULL
static long get_graphic_double();
static long get_control_double();
#define get_alarm_double NULL
struct rset imageRSET={
	RSETNUMBER,
	report,
	initialize,
	init_record,
	process,
	special,
	get_value,
	cvt_dbaddr,
	get_array_info,
	put_array_info,
	get_units,
	get_precision,
	get_enum_str,
	get_enum_strs,
	put_enum_str,
	get_graphic_double,
	get_control_double,
	get_alarm_double };


struct imagedeset{ /* image dset */
  long        number;
  DEVSUPFUN   dev_report;
  DEVSUPFUN   init;
  DEVSUPFUN   init_record;
  DEVSUPFUN   get_ioint_info;
  DEVSUPFUN   read_img;
};

static void monitor();
static long readValue();
extern SEM_ID pictureSemaphore;

static long init_record(pim,pass)
    struct imageRecord	*pim;
    int pass;
{
    SYM_TYPE stype;
    int *pLxxx;
    short i;
    struct vmeio  *pvmeio = (struct vmeio *)&(pim->inp.value);
    struct imagedeset *pdset=(struct imagedeset *) (pim->dset);

    /* printf("init_record pass = %d\n",pass); */

    if (pass==0){
        pim->vers = VERSION;
	pvmeio->parm = SP24_PARM_GET_IMAGE_ADDR;
	/* memory for image storage is alocated in the config func */
	/* in driver support */
	(*pdset->read_img)(pim); /* fetch the pointer to the image */
	
        pLxxx = (int *)&pim->l0;
        for(i=0;i<1024;i++, pLxxx++) {
          *pLxxx = (int)((char *)pim->l0 + (i * (pim->size+1) * pim->xres));
	  } 
	pvmeio->parm = SP24_PARM_NOTHING;
	return(0);
    }

    return(0);
}

static long process(pim)
	struct imageRecord	*pim;
{
	unsigned char    pact=pim->pact;
        unsigned long    currentTick;

	/* printf("process pact = %d\n",pact);
	printf("call dev support routine read_image\n");
	printf("status => %d\n",(int) (*pdset->read_img)(pim)); */
	if (pact) return(0);

	/* read the new value, <NOT CURRENTLY NECESSARY> 
	status=readValue(pim); 
        */

        /* Only increment and post .val if ENAB is 1 AND 
           .rate has not been exceeded */

        currentTick = tickGet();
        if (pim->enab && ((currentTick - pim->pmtk)/(float)sysClkRateGet() >= pim->rate)) {
            pim->val++;
            pim->pact = TRUE;

	    pim->udf=FALSE;

	    monitor(pim);
            pim->pmtk = currentTick;
        }

	recGblGetTimeStamp(pim);
        /* process the forward scan link record */
        recGblFwdLink(pim);

        pim->pact=FALSE;
        return(0);
}

static long cvt_dbaddr(paddr)
    struct dbAddr *paddr;
{
    struct imageRecord *pim=(struct imageRecord *)paddr->precord;
    int *pLine = paddr->pfield;

    /* printf("cvt_dbaddr \n"); */
 
    if(!pim->rxsz) {
        paddr->pfield = (void *)*pLine;
        paddr->no_elements = pim->xres;
    }
    else {
        /* If .RXSZ != 0, index to the correct place in the scan line */
        paddr->pfield = (void *)((char *)*pLine + (pim->rxst*(pim->size+1)));
        paddr->no_elements = pim->rxsz;
    }

    if(pim->size == 0) {
        paddr->field_type = DBF_UCHAR;
        paddr->field_size = 1;
        paddr->dbr_field_type = DBF_UCHAR;
    } 
    else {
        paddr->field_type = DBF_SHORT;
        paddr->field_size = 2;
        paddr->dbr_field_type = DBF_SHORT;
    } 
    return(0);
}

static long get_array_info(paddr,no_elements,offset)
    struct dbAddr *paddr;
    long	  *no_elements;
    long	  *offset;
{  
    struct imageRecord	*pim    = (struct imageRecord *) paddr->precord;
    struct vmeio        *pvmeio = (struct vmeio *)     &(pim->inp.value);
    struct imagedeset   *pdset  = (struct imagedeset *) (pim->dset);

    int *pLine = paddr->pfield;
    /* printf("get_array_info %d\n",(int) pim->yres); */
 
    if ((&pim->l0)[(pim->yres)-1] == pLine)
      {
	pvmeio->parm = SP24_PARM_LOCK_IMAGE;
	(*pdset->read_img)(pim);
	pvmeio->parm = SP24_PARM_NOTHING ;
      }
    else if (pim->l0 == pLine)
      {
	pvmeio->parm = SP24_PARM_UNLOCK_IMAGE;
	(*pdset->read_img)(pim);
	pvmeio->parm = SP24_PARM_NOTHING ;
      }

    *no_elements =  pim->xres;
    *offset = 0;
    return(0);
}

static long put_array_info(paddr,nNew)
    struct dbAddr *paddr;
    long	  nNew;
{
    return(0);
}

static long get_units(paddr,units)
    struct dbAddr *paddr;
    char	  *units;
{

    strncpy(units,"",DB_UNITS_SIZE);
    return(0);
}

static long get_precision(paddr,precision)
    struct dbAddr *paddr;
    long	  *precision;
{
    struct imageRecord	*pim=(struct imageRecord *)paddr->precord;
    /* printf("get_precision\n"); */
    *precision = 0;
    if(paddr->pfield==(void *)&pim->val) return(0);
    if(paddr->pfield==(void *)&pim->rate) {
        *precision = 2;
        return(0);
    }
    recGblGetPrec(paddr,precision);
    return(0);
}

static long get_graphic_double(paddr,pgd)
    struct dbAddr *paddr;
    struct dbr_grDouble *pgd;
{
    recGblGetGraphicDouble(paddr,pgd);
    return(0);
}
static long get_control_double(paddr,pcd)
    struct dbAddr *paddr;
    struct dbr_ctrlDouble *pcd;
{
    recGblGetControlDouble(paddr,pcd);
    return(0);
}

static void monitor(pim)
    struct imageRecord	*pim;
{
	unsigned short	monitor_mask;

        monitor_mask = recGblResetAlarms(pim);
	monitor_mask |= (DBE_LOG|DBE_VALUE);
        if(monitor_mask) db_post_events(pim,&pim->val,monitor_mask);
	return;

}

static long readValue(pim)
        struct imageRecord *pim;
{
        long            status;
	/* printf("readValue\n"); */
        status=0;

        /* Pointers to data, no reading required */
        return(status);
}
