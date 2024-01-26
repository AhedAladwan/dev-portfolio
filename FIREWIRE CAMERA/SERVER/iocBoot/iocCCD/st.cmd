#!../../bin/linux-x86/ieee1394

## You may have to change ieee1394 to something else
## everywhere it appears in this file

< envPaths

cd ${TOP}

## Register all support components
dbLoadDatabase("dbd/ieee1394.dbd",0,0)
ieee1394_registerRecordDeviceDriver(pdbbase)

## Load record instances
dbLoadRecords("db/1394.db","CAM=GTEST-PC-CCD")
dbLoadRecords("db/save_restoreStatus.db","P=GTEST-CCD-AS:")

save_restoreSet_Debug(0)
set_requestfile_path("./req")
set_savefile_path("./save")
save_restoreSet_status_prefix("GTEST-CCD-AS:")
set_pass0_restoreFile "auto_settings.sav"
set_pass1_restoreFile "auto_settings.sav"


cd ${TOP}/iocBoot/${IOC}
iocInit()

create_monitor_set("auto_settings.req", 5)

