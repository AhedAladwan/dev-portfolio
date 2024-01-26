TOP=../..
include $(TOP)/configure/CONFIG
#----------------------------------------
#  ADD MACRO DEFINITIONS AFTER THIS LINE
#=============================

USR_INCLUDES_WIN32 += -I../include/

LIB_INSTALLS_WIN32 += ../lib/os/win32-x86/td_telnet.lib ../lib/os/win32-x86/td_wget.lib 
BIN_INSTALLS_WIN32 += ../lib/os/win32-x86/td_telnet.dll ../lib/os/win32-x86/td_wget.dll


LIBRARY_IOC_WIN32 += argus
LIB_SRCS += argus.cpp
LIB_LIBS += td_telnet td_wget

PROD_IOC_WIN32 += argusApp

# <name>.dbd will be created from <name>Include.dbd
DBD += argusApp.dbd
DBD += argusSupport.dbd

# <name>_registerRecordDeviceDriver.cpp will be created from <name>.dbd
PROD_SRCS += argusApp_registerRecordDeviceDriver.cpp argusAppMain.cpp

# Add locally compiled object code
PROD_LIBS += argus
PROD_LIBS += td_telnet td_wget

include $(AREA_DETECTOR)/ADApp/commonDriverMakefile

#=============================

include $(TOP)/configure/RULES
#----------------------------------------
#  ADD RULES AFTER THIS LINE
