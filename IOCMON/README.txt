/*
	add the following to devSup.ascii:

	"ai"  INST_IO    "devAiStats"   "VX stats"
	"ao"  INST_IO    "devAoStats"   "VX stats"

	--------------------------------------------------------------------
	Add FD and CA connection information before release.
	Add ability to adjust the rate of everything through ao records

	sample db file to use all data available:
	Note that the valid values for the parm field of the link
	information are:

	ai:
		free_bytes	 - number of bytes in IOC not allocated
		allocated_bytes  - number of bytes allocated
		max_free	 - size of largest free block
		cpu		 - estimated percent CPU usage by tasks
		fd		 - number of file descriptors currently in use
		ca_clients	 - number of current CA clients
		ca_connections	 - number of current CA connections
	ao:
		memoryScanRate	 - max rate at which new memory stats can be read
		fdScanRate	- max rate at which file descriptors can be counted
		cpuScanRate	 - max rate at which cpu load can be calculated
		caConnScanRate	 - max rate at which CA connections can be calculated

	* scan rates are all in seconds

	default rates:
		10 - memory scan rate
		20 - cpu scan rate
		10 - fd scan rate
		15 - CA scan rate

        stringin:

                Some values displayed by the string records are
	 	longer than the 40 char string record length, so multiple 
		records must be used to display them.

		The supported stringin devices are all static; the record only
		needs to be processed once, for which PINI is convenient.

		startup_script_[12]	-path of startup script (2 records)
		bootline_[1-6]		-vxWorks bootline (6 records)
 		bsp_rev			-vxWorks board support package revision
		kernel_ver		-vxWorks kernel build version
		epics_ver		-EPICS base version

	# sample database using all the different types of statistics
	record(ai,"$(PRE):freeBytes")
	{
		field(DTYP,"VX stats")
		field(SCAN,"I/O Intr")
		field(INP,"@free_bytes")
	}
	record(ai,"$(PRE):allocatedBytes")
	{
		field(DTYP,"VX stats")
		field(SCAN,"I/O Intr")
		field(INP,"@allocated_bytes")
	}
	record(ai,"$(PRE):maxFree")
	{
		field(DTYP,"VX stats")
		field(SCAN,"I/O Intr")
		field(INP,"@max_free")
	}
	record(ai,"$(PRE):cpu")
	{
		field(DTYP,"VX stats")
		field(SCAN,"I/O Intr")
		field(INP,"@cpu")
		field(PREC,"3")
	}
	record(ai,"$(PRE):fd")
	{
		field(DTYP,"VX stats")
		field(SCAN,"I/O Intr")
		field(INP,"@fd")
	}
	record(ai,"$(PRE):caClients")
	{
		field(DTYP,"VX stats")
		field(SCAN,"I/O Intr")
		field(INP,"@ca_clients")
	}
	record(ai,"$(PRE):caConnections")
	{
		field(DTYP,"VX stats")
		field(SCAN,"I/O Intr")
		field(INP,"@ca_connections")
	}
	record(ao,"$(PRE):memoryScanRate")
	{
		field(DTYP,"VX stats")
		field(OUT,"@memory_scan_rate")
	}
	record(ao,"$(PRE):fdScanRate")
	{
		field(DTYP,"VX stats")
		field(OUT,"@fd_scan_rate")
	}
	record(ao,"$(PRE):caConnScanRate")
	{
		field(DTYP,"VX stats")
		field(OUT,"@ca_scan_rate")
	}
	record(ao,"$(PRE):cpuScanRate")
	{
		field(DTYP,"VX stats")
		field(OUT,"@cpu_scan_rate")
	}
        record(stringin,"$(PRE):StartupScript1")
        {
		field(DTYP,"VX stats")
                field(INP,"@startup_script_1")
           	field(PINI, "Yes")
        }
        record(stringin,"$(PRE):StartupScript2")
        {
		field(DTYP,"VX stats")
                field(INP,"@startup_script_2")
           	field(PINI, "Yes")
        }
        record(stringin,"$(PRE):Bootline1")
        {
		field(DTYP,"VX stats")
                field(INP,"@bootline_1")
           	field(PINI, "Yes")
        }
        record(stringin,"$(PRE):Bootline2")
        {
		field(DTYP,"VX stats")
                field(INP,"@bootline_2")
           	field(PINI, "Yes")
        }
        record(stringin,"$(PRE):Bootline3")
        {
		field(DTYP,"VX stats")
                field(INP,"@bootline_3")
           	field(PINI, "Yes")
        }
        record(stringin,"$(PRE):Bootline4")
        {
		field(DTYP,"VX stats")
                field(INP,"@bootline_4")
           	field(PINI, "Yes")
        }
        record(stringin,"$(PRE):Bootline5")
        {
		field(DTYP,"VX stats")
                field(INP,"@bootline_5")
           	field(PINI, "Yes")
        }
        record(stringin,"$(PRE):Bootline6")
        {
		field(DTYP,"VX stats")
                field(INP,"@bootline_6")
           	field(PINI, "Yes")
        }
        record(stringin,"$(PRE):BSPRev")
        {
		field(DTYP,"VX stats")
                field(INP,"@bsp_rev")
           	field(PINI, "Yes")
        }
        record(stringin,"$(PRE):KernelVer")
        {
		field(DTYP,"VX stats")
                field(INP,"@kernel_ver")
           	field(PINI, "Yes")
        }
        record(stringin,"$(PRE):EPICSVer")
        {
		field(DTYP,"VX stats")
                field(INP,"@epics_ver")
           	field(PINI, "Yes")
        }

