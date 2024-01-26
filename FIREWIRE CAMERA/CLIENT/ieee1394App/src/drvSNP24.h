/* $Author: dach $ */ 
/* $Date: 2005/08/26 09:03:33 $ */ 
/* $Id: drvSNP24.h,v 1.1 2005/08/26 09:03:33 dach Exp $ */  
/* $Name:  $ */ 
/* $Revision: 1.1 $ */ 
/* Revision 1.4  2000/02/28 10:08:39  dach
* higher thread priorites
*/
/* Revision 1.3  1999/12/01 08:35:26  dach
 * driver fully tested with 12 cameras
 *
 * Revision 1.2  1999/10/18 08:39:58  dach
 * Double buffering implemented, Mux for 12 CCDs
 *
 * Revision 1.1  1999/09/16 07:24:04  dach
 * driver for snp24 grabber to support 12 cameras
 * */ 

/* SNP24 is an EPICS driver for the DataCell snp24 frame grabber  */
/* The code was written in Paul Scherer Institute by Miroslaw Dach*/
/* in case of problems please send me an e-mail to the address:   */
/* dach@psi.ch                                                    */

#define WF_DEV_SUP devWfSNP24

#define Ok 0
#define ERR -1
#define EOS '\0'

#define STATIC static
#define SP24_RGB_CHAN_NR 3  /* number of RGB video channels */
#define SP24_MUX_CHAN_NR 4  /* number of muliplex channels per R , G , B channel */
#define SP24_CAMERA_1    0
#define SP24_CAMERA_2    1
#define SP24_CAMERA_3    2
#define SP24_CAMERA_4    3
#define SP24_SEM_LOCKED    0
#define SP24_SEM_UNLOCKED  1

#define SP24_PARM_GET_IMAGE_ADDR "address"
#define SP24_PARM_LOCK_IMAGE     "lock"
#define SP24_PARM_UNLOCK_IMAGE   "unlock"
#define SP24_PARM_NOTHING         NULL


/* macros copied form the make file */
#ifndef _VXWORKS
#define _VXWORKS
#endif
#ifndef _FPGA_INTERNAL
#define _FPGA_INTERNAL
#endif
#ifndef _SNP24
#define _SNP24
#endif
#ifndef _GNU_TOOL
#define _GNU_TOOL
#endif

int Snp24_read(
        unsigned short card,
        unsigned short channel,
        unsigned int *val
);




/************************************************************************/
/*
 * Xycom DRV driver error codes
 */
#define M_drvSnp24Lib (1003<<16U)

#define drvSnp24Error(CODE) (M_drvSnp24Lib | (CODE))

#define S_drvSnp24_OK 0 /* success */
#define S_drvSnp24_badParam drvSnp24Error(1) /*Snp24 driver: bad parameter*/
#define S_drvSnp24_noMemory drvSnp24Error(2) /*Snp24 driver: no memory*/
#define S_drvSnp24_noDevice drvSnp24Error(3) /*Snp24 driver: device not configured*/
#define S_drvSnp24_invSigMode drvSnp24Error(4)/*Snp24 driver: signal mode conflicts with device config*/
#define S_drvSnp24_cbackChg drvSnp24Error(5) /*Snp24 driver: specified callback differs from previous config*/
#define S_drvSnp24_alreadyQd drvSnp24Error(6)/*SSI driver: a read request is already queued for the channel*/
