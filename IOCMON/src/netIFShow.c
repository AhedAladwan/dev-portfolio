/* This program reports on the N/W Interface statistics */
 
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include <stdio.h>

#include <vxWorks.h>
#include <version.h>

#include <ifLib.h>
#include <etherLib.h>
#include <net/if.h>
#include <net/mbuf.h>


#ifdef RUNTIME_VERSION

	#include "net/if.h"
	#include <end.h>
	#include <endLib.h>
	#include <netBufLib.h>

extern int m2If64BitCounters;

#endif

/******************************************************************************
 * *
 * * vxSnoop - Show number of times packets were dropped because interface send
 * *                was full.
 * *
 * * ifname
 * *     Expects the interface name plus the unit number: dc0, fei0 which is resolved by using the ifname function from the * *	    caller
 * * 
 * */

long vxSnoop(char *ifname,int *PPsent,int *PPrcv, int *Pierror, int *Poerror, int *Pcollis, int *Pdrop)
{

#ifdef RUNTIME_VERSION

	struct ifnet *ifp;
	END_OBJ	*pEnd = NULL;
        int nameLen;
        BOOL found;
        found = FALSE;

        /*get the information*/
        ifp = ifnet;

        for (ifp = ifnet; ifp != NULL; ifp = ifp->if_next)
        {
                nameLen = strlen (ifp->if_name);

                if (ifname != NULL) /* if a name was specified */
                {
                        if (strncmp (ifname, ifp->if_name, nameLen) ==0)
                        {
                                found = TRUE;
                                break;
                        }

                }
                else break;
        }

        if (!found)
        {
                printf("no network device found!\n");
                return 1;
        }
	
        pEnd = endFindByName(ifp->if_name, ifp->if_unit);
        if ((NULL != pEnd) && (pEnd->flags & END_MIB_2233)) {
	

                  *PPrcv   = pEnd->pMib2Tbl->m2Data.mibIfTbl.ifInOctets +
		             pEnd->pMib2Tbl->m2Data.mibIfTbl.ifInUcastPkts +
	                     pEnd->pMib2Tbl->m2Data.mibIfTbl.ifInNUcastPkts +
	                     pEnd->pMib2Tbl->m2Data.mibXIfTbl.ifInMulticastPkts + 
	                     pEnd->pMib2Tbl->m2Data.mibXIfTbl.ifInBroadcastPkts;
		  
		  
                  *PPsent  = pEnd->pMib2Tbl->m2Data.mibIfTbl.ifOutOctets + 
	                     pEnd->pMib2Tbl->m2Data.mibIfTbl.ifOutNUcastPkts +
           	             pEnd->pMib2Tbl->m2Data.mibXIfTbl.ifOutMulticastPkts +
	                     pEnd->pMib2Tbl->m2Data.mibXIfTbl.ifOutBroadcastPkts;		  




                  *Pdrop   = pEnd->pMib2Tbl->m2Data.mibIfTbl.ifInDiscards + 
           	             pEnd->pMib2Tbl->m2Data.mibIfTbl.ifOutDiscards;
		  
                  *Pierror = pEnd->pMib2Tbl->m2Data.mibIfTbl.ifInErrors;
                  *Poerror = pEnd->pMib2Tbl->m2Data.mibIfTbl.ifOutErrors;
		  *Pcollis = -1;
        }
        else {
	
        	  *PPsent  = ifp->if_data.ifi_opackets;

          	  *PPrcv   = ifp->if_data.ifi_ipackets;

          	  *Pierror = ifp->if_data.ifi_ierrors;

          	  *Poerror  = ifp->if_data.ifi_oerrors;

          	  *Pcollis  = ifp->if_data.ifi_collisions;

          	  *Pdrop    = ifp->if_data.ifi_iqdrops;		  
	}
	
#else					/*Tornado 1*/
	struct ifnet *ifp;
	ifp = ifunit(ifname);
	if (ifp == NULL)
	{
		printf("IOCMON:vxSnoop:Could not find %s interface\n", ifname);
	}

        *PPsent  = ifp->if_opackets;
        *PPrcv   = ifp->if_ipackets;
        *Pierror = ifp->if_ierrors;
        *Poerror = ifp->if_oerrors;
        *Pcollis = ifp->if_collisions;
        *Pdrop   = ifp->if_snd.ifq_drops;

#endif
	
	return(0);
}

/* bufInfoShow: show infromation about the buffer
 *
 */ 

long bufInfoShow (char *ifname, int *bufDrops, int *bufWait, int *bufDrain)
{

#ifndef RUNTIME_VERSION			/*Tornado 1*/

	*bufDrops  = (int) mbstat.m_drops;
	*bufWait   = (int) mbstat.m_wait;
	*bufDrain  = (int) mbstat.m_drain;

#else                                   /*Tornado 2*/
	
    END_OBJ   *   pEnd;
    NET_POOL *pNetPool = ( NET_POOL *) _pNetDpool ; /*data mbuf pool */
    int           unit;
    char          device [8];
    int           devLen;

        /* Take a private copy to modify */

    strcpy (device, ifname);

        /* The unit number here is assumed to be just a single
        * digit; this assumption should be OK for most people.
        */

    devLen = strlen (ifname) - 1;

    if (isdigit ((unsigned char)device[devLen]))
       {
                unit   = atoi (&ifname[devLen]);

                /* Remove the number now */

                device [devLen] = '\0';
        }
     else
        {
                /* Assume unit number is 0 if none specified */

                unit = 0;
        }

    if ((pEnd = endFindByName (device, unit)) != NULL)
        {
                *bufDrops  = (int) pNetPool->pPoolStat->mDrops;
                *bufWait   = (int) pNetPool->pPoolStat->mWait;
                *bufDrain  = (int) pNetPool->pPoolStat->mDrain;
        }
    else
    {
                printf ("IOCMON:bufInfoShow:Could not find device %s\n", ifname);
    }
#endif	
    return(0);
}

