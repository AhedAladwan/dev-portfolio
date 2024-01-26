errlogInit(20000)

< envPaths

dbLoadDatabase("../../dbd/argusApp.dbd")

argusApp_registerRecordDeviceDriver(pdbbase) 

epicsEnvSet("PREFIX", "ARGUS:")
epicsEnvSet("PORT",   "argusTel")
epicsEnvSet("IPADDRS", "169.254.144.100")
epicsEnvSet("TELPORT", "23")
epicsEnvSet("QSIZE",  "20")
epicsEnvSet("XSIZE",  "4080")
epicsEnvSet("YSIZE",  "16655")
epicsEnvSet("NCHANS", "2048")

# argusConfig(portName,    # The name of the asyn port to be created
#                 cameraId,    # Unique ID, IP address, or IP name of the camera
#                 maxBuffers,  # Maximum number of NDArray buffers driver can allocate. 0=unlimited
#                 maxMemory,   # Maximum memory bytes driver can allocate. 0=unlimited
#                 priority,    # EPICS thread priority for asyn port driver 0=default
#                 stackSize,   # EPICS thread stack size for asyn port driver 0=default
#                 maxPvAPIFrames) # Number of frames to allocate in PvAPI driver. Default=2.

argusConfig("$(PORT)", "$(IPADDRS)", 50, 0)

#asynSetTraceIOMask("$(PORT)",0,2)
#asynSetTraceMask("$(PORT)",0,255)

dbLoadRecords("$(AREA_DETECTOR)/ADApp/Db/ADBase.template",   "P=$(PREFIX),R=cam1:,PORT=$(PORT),ADDR=0,TIMEOUT=1")
dbLoadRecords("$(AREA_DETECTOR)/ADApp/Db/NDFile.template",   "P=$(PREFIX),R=cam1:,PORT=$(PORT),ADDR=0,TIMEOUT=1")
dbLoadRecords("../../db/argus.template","P=$(PREFIX),R=cam1:,PORT=$(PORT),ADDR=0,TIMEOUT=1")

# Create a standard arrays plugin.
NDStdArraysConfigure("Image1", 5, 0, "$(PORT)", 0, 0)
dbLoadRecords("$(AREA_DETECTOR)/ADApp/Db/NDPluginBase.template","P=$(PREFIX),R=image1:,PORT=Image1,ADDR=0,TIMEOUT=1,NDARRAY_PORT=$(PORT),NDARRAY_ADDR=0")
dbLoadRecords("$(AREA_DETECTOR)/ADApp/Db/NDStdArrays.template", "P=$(PREFIX),R=image1:,PORT=Image1,ADDR=0,TIMEOUT=1,TYPE=Int16,FTVL=SHORT,NELEMENTS=22664400")

# Load all other plugins using commonPlugins.cmd
< ../commonPlugins.cmd

#asynSetTraceMask("$(PORT)",0,255)

iocInit()

# save things every thirty seconds
create_monitor_set("auto_settings.req", 30,"P=$(PREFIX),D=cam1:")
