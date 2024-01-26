include /ioc/tools/driver.makefile
USR_INCLUDES += -I$(EPICS_BASE)/src/rsrv
USR_INCLUDES += -I$(EPICS_BASE)/src/ca
USR_INCLUDES += -I$(EPICS_BASE)/src/db
DBDS = devStats.dbd timestampRecord.dbd
SOURCES += devVxStats.c
SOURCES += read_ca_stats.c
SOURCES += timestampRecord.c ioccar.c
SOURCES += netIFShow.c
EXCLUDE_VERSIONS = 3.14
PROJECT = iocmon

ifeq ($(EPICSVERSION),3.13.2)
SOURCES += tsSubr.c
endif
