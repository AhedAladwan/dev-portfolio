TOP=../..

include $(TOP)/configure/CONFIG
#----------------------------------------
#  ADD MACRO DEFINITIONS AFTER THIS LINE
#=============================

#=============================
# build an ioc application

PROD_HOST += savepgm firewire
PROD_LIBS += ca

firewire_INCLUDES += -I /usr/X11R6/include
firewire_LDFLAGS += -L /usr/X11R6/lib
firewire_SYS_LIBS += Xm

#The following builds sncExample as a standalone application
#PROD_HOST += sncExample
#sncExample_SNCFLAGS += +m
#sncExample_SRCS += sncExample.stt
#sncExample_LIBS += seq pv
#sncExample_LIBS += $(EPICS_BASE_HOST_LIBS)

PROD_IOC = ieee1394

# <name>.dbd will be created from <name>Include.dbd
ieee1394_DBD += ieee1394.dbd

#ieee1394_CFLAGS+= -I 
ieee1394_LDFLAGS+=  -lraw1394 -ldc1394_control

ieee1394_SRCS += dev1394.c
#ieee1394_SRCS += imageRecord.c

# <name>_registerRecordDeviceDriver.cpp will be created from <name>.dbd
ieee1394_SRCS += ieee1394_registerRecordDeviceDriver.cpp
ieee1394_SRCS_DEFAULT += ieee1394Main.cpp
ieee1394_SRCS_vxWorks += -nil-

#The following adds support from base/src/vxWorks
ieee1394_OBJS_vxWorks += $(EPICS_BASE_BIN)/vxComLibrary

#add a definition for each support application used by this application
#ieee1394_LIBS += xxx

#NOTES:
#      1)It is not possible to build sncExample both as a component of ieee1394
#        and standalone. You must choose only one.
#      2)To build sncExample SNCSEQ must be defined in <top>/configure/RELEASE

#The following builds sncExample as a component of ieee1394
#ieee1394_SRCS += sncExample.stt
#ieee1394_LIBS += seq pv

ieee1394_LIBS += $(EPICS_BASE_IOC_LIBS)

#===========================

include $(TOP)/configure/RULES
#----------------------------------------
#  ADD RULES AFTER THIS LINE

