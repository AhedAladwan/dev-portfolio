/* recTimestamp.c */
/* recTimestamp.c - Record Support Routines for Timestamp records */
/*
 *      Original Author:  Susumu Yoshida
 *      Current Author: 
 *      Date:            10-12-98
 *
 * Modification Log:
 * -----------------
 *      2-Jun-2000 rpc - Use tsStampToLocal to get daylight savings time
 *                       (involves changes to tsSubr.c and tsDefs.h)
 *                       Remove superfluous subroutines
 *                       Add more formats (see also timestampRecord.dbd)
 */

#include	<vxWorks.h>
#include	<types.h>
#include	<stdioLib.h>
#include	<lstLib.h>
#include	<string.h>

#include        <tsDefs.h> 
#include	<dbDefs.h>
#include	<dbAccess.h>
#include	<dbFldTypes.h>
#include	<devSup.h>
#include	<recSup.h>
#include        <dbEvent.h>    /* for db_post_events() */

#define GEN_SIZE_OFFSET
#include	<timestampRecord.h>
#undef  GEN_SIZE_OFFSET

/* Create RSET - Record Support Entry Table*/
#define report NULL
#define initialize NULL
#define init_record NULL
static long process();
static void monitor();
#define special NULL
#define cvt_dbaddr NULL
#define get_array_info NULL
#define put_array_info NULL
#define get_units NULL
#define get_precision NULL
#define get_enum_str NULL
#define get_enum_strs NULL
#define put_enum_str NULL
#define get_graphic_double NULL
#define get_control_double NULL
#define get_alarm_double NULL

struct rset timestampRSET={
	RSETNUMBER,
	report,
	initialize,
	init_record,
	process,
	special,
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

char MONTH[12][4]=
 {"JAN","FEB","MAR","APR","MAY","JUN","JUL","AUG","SEP","OCT","NOV","DEC"};

static long process(struct timestampRecord *ptimestamp){

  struct tsDetail time_s;
  
  ptimestamp->udf  = FALSE;
  ptimestamp->pact = TRUE;

  recGblGetTimeStamp(ptimestamp);
  tsStampToLocal(ptimestamp->time, &time_s);
  
  switch(ptimestamp->tst) {
  case timestampTST_YY_MM_DD_HH_MM_SS:
    sprintf(ptimestamp->val,"%.2d/%.2d/%.2d %.2d:%.2d:%.2d"
	    ,time_s.year,time_s.monthNum+1,time_s.dayMonth+1
	    ,time_s.hours,time_s.minutes,time_s.seconds);
    break;
  case timestampTST_MM_DD_YY_HH_MM_SS:
    sprintf(ptimestamp->val,"%.2d/%.2d/%.2d %.2d:%.2d:%.2d"
	    ,time_s.monthNum+1,time_s.dayMonth+1,time_s.year
	    ,time_s.hours,time_s.minutes,time_s.seconds);
    break;
  case timestampTST_MM_DD_HH_MM_SS_YY:
    sprintf(ptimestamp->val,"%s %.2d %.2d:%.2d:%.2d %.2d"
	    ,MONTH[time_s.monthNum],time_s.dayMonth+1
	    ,time_s.hours,time_s.minutes,time_s.seconds,time_s.year);
    break;
  case timestampTST_MM_DD_HH_MM_SS:
    sprintf(ptimestamp->val,"%s %.2d %.2d:%.2d:%.2d"
	    ,MONTH[time_s.monthNum],time_s.dayMonth+1
	    ,time_s.hours,time_s.minutes,time_s.seconds);
    break;
  case timestampTST_HH_MM_SS:
    sprintf(ptimestamp->val,"%.2d:%.2d:%.2d"
	    ,time_s.hours,time_s.minutes,time_s.seconds);
    break;
  case timestampTST_HH_MM:
    sprintf(ptimestamp->val,"%.2d:%.2d"
	    ,time_s.hours,time_s.minutes);
    break;
  case timestampTST_DD_MM_YY_HH_MM_SS:
    sprintf(ptimestamp->val,"%.2d/%.2d/%.2d %.2d:%.2d:%.2d"
	    ,time_s.dayMonth+1,time_s.monthNum+1,time_s.year
	    ,time_s.hours,time_s.minutes,time_s.seconds);
    break;
  case timestampTST_DD_MM_HH_MM_SS_YY:
    sprintf(ptimestamp->val,"%.2d %s %.2d:%.2d:%.2d %.2d"
	    ,time_s.dayMonth+1,MONTH[time_s.monthNum]
	    ,time_s.hours,time_s.minutes,time_s.seconds,time_s.year);
    break;
  case timestampTST_VMS:
    sprintf(ptimestamp->val,"%.2d-%s-%.4d %.2d:%.2d:%.2d"
	    ,time_s.dayMonth+1,MONTH[time_s.monthNum],time_s.year
	    ,time_s.hours,time_s.minutes,time_s.seconds);
    break;
  case timestampTST_MM_DD_YYYY:
    sprintf(ptimestamp->val,"%s %.2d, %.4d %.2d:%.2d:%.2d"
	    ,MONTH[time_s.monthNum],time_s.dayMonth+1
	    ,time_s.year,time_s.hours,time_s.minutes,time_s.seconds);
    break;
  case timestampTST_MM_DD_YY:
    sprintf(ptimestamp->val,"%.2d/%.2d/%.2d %.2d:%.2d:%.2d"
	    ,time_s.monthNum+1,time_s.dayMonth+1,time_s.year
	    ,time_s.hours,time_s.minutes,time_s.seconds);
    break;
  default :  /* YY/MM/DD HH:MM:SS */
    sprintf(ptimestamp->val,"%.2d/%.2d/%.2d %.2d:%.2d:%.2d"
            ,time_s.year,time_s.monthNum+1,time_s.dayMonth+1
            ,time_s.hours,time_s.minutes,time_s.seconds);
    break;
  }
  /* check event list */
  monitor(ptimestamp);

  /* process the forward scan link record */
  recGblFwdLink(ptimestamp);
  ptimestamp->pact=FALSE;
  return(0);
}


static void monitor(ptimestamp)
     struct timestampRecord             *ptimestamp;
{
  unsigned short  monitor_mask;
  
  monitor_mask = recGblResetAlarms(ptimestamp);
  monitor_mask |=DBE_VALUE|DBE_LOG;
  if(strncmp(ptimestamp->oval,ptimestamp->val,sizeof(ptimestamp->val))) {
    db_post_events(ptimestamp,&(ptimestamp->val[0]), monitor_mask);
    db_post_events(ptimestamp,&ptimestamp->rval,monitor_mask);
    strncpy(ptimestamp->oval,ptimestamp->val,sizeof(ptimestamp->val));
  }
  return;
}
