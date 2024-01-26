TOP=../..

include $(TOP)/configure/CONFIG
#----------------------------------------
#  ADD MACRO DEFINITIONS AFTER THIS LINE
#=============================

#=============================
# build an ioc application

#STATIC_BUILD=YES

PROD_HOST += setup_camera
PROD_LIBS += ca

setup_camera_LDFLAGS += -ldc1394_control -lraw1394

#============================

PROD_IOC = ieee1394

# <name>.dbd will be created from <name>Include.dbd
DBD += ieee1394.dbd

#ieee1394_CFLAGS+= -I 
ieee1394_LDFLAGS+=  -ldc1394_control -lraw1394
CFLAGS+= -fno-strict-aliasing

ieee1394_SRCS += dev1394.c
#ieee1394_SRCS += imageRecord.c

# <name>_registerRecordDeviceDriver.cpp will be created from <name>.dbd
ieee1394_SRCS += ieee1394_registerRecordDeviceDriver.cpp
ieee1394_SRCS_DEFAULT += ieee1394Main.cpp
ieee1394_SRCS_vxWorks += -nil-

#The following adds support from base/src/vxWorks
ieee1394_OBJS_vxWorks += $(EPICS_BASE_BIN)/vxComLibrary

ieee1394_LIBS += autosave
ieee1394_LIBS += $(EPICS_BASE_IOC_LIBS)

#===========================

include $(TOP)/configure/RULES
#----------------------------------------
#  ADD RULES AFTER THIS LINE

