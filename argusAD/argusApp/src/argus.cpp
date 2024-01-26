/* argus.cpp
 *
 * This is a driver for Argus Detector (Argus API)
 * Author: Ahed Aladwan
 *         Australian Synchrotron, IMBL
 *
 * Created: 26.11.2012
 *
 * ARGUS API doesn't support direct memory access to acquired image, rather save it to file system, Magick lib was used to create a "buffered" version of the image that was written back to NDArray 
 * data, in case of the ARGUS this has no speed overhead as the acquistion is already very slow, it takes usually around 20 sec to acquire a full size image.
 */

// Standard Lib headers
#include <stddef.h>
#include <stdlib.h>
#include <stdarg.h>
#include <math.h>
#include <stdio.h>
#include <string.h>
#include <ctype.h>
#include <fstream>
#include <iostream>
#include <sstream>
using namespace std;

// EPICS headers
#include <epicsTime.h>
#include <epicsThread.h>
#include <epicsEvent.h>
#include <epicsString.h>
#include <epicsStdio.h>
#include <epicsMutex.h>
#include <cantProceed.h>
#include <osiSock.h>
#include <iocsh.h>
#include <epicsExport.h>
#include <epicsExit.h>
#include "ADDriver.h"
static const char *driverName = "argus";

// Argus headers
#include "stdafx.h"
#include <windows.h>
#include "ArgusAPI.h"

#include <Magick++.h>
using namespace Magick;

// Argus global constants

#define					INIT_STR_LEN				20						/*	Length limit for user entry to dll									*/
#define					DLL_MSG_LEN					CAM_RESP_LEN			/*	Camera resonse, MUST be greater or equal to dll buffer size	CAM_RESP_LEN	*/
#define					CAM_RESP_LEN				(8160 * 16665)				//	Camera response maximum length, must be greater than RXBUF_LEN 
#define					CMD_LEN						CAM_TX_BUF_LEN			/*	Command string length	*/
#define					CAM_TX_BUF_LEN				30						/*	string length limit of the camera command							*/
#define					TELNET_PORT					23						/*	standard telnet port number											*/
#define					INIT_STR_LEN				20						/*	Length limit for user entry to dll									*/
#define					MAX_WIDTH					4080
#define					MAX_HEIGHT					16665

// Argus Detector Devie Information

	char				ARGUSdetectorSerial[10] = "14013722";

	static int			ArgusMaxImageHeightRangesY[] = {
						5555,  // 2x2 binning
						8332,  // 3x3 binning
						11100, // 4x4 binning
						13887, // 5x5 binning
						16665  // 6x6 binning
	};


	static int			ArgusMaxImageHeightRangesX[] = {
						4080,  // 2x2 binning
						2720,  // 3x3 binning
						2040, // 4x4 binning
						1632, // 5x5 binning
						1360  // 6x6 binning
	};

	typedef struct
	{
	char				Login[INIT_STR_LEN];
	char				Password[INIT_STR_LEN];
	char				CameraIP[INIT_STR_LEN];
	char				CameraResp[DLL_MSG_LEN];
	int					WSAStatus;
	int					TARGET_PORT;
	} _CAM_INFO;

	static				_CAM_INFO _cam_info = {0};

	char				*pDL;
	char				dPath[MAX_FILENAME_LEN];
	char				imagePath[MAX_FILENAME_LEN];
	char				logPath[MAX_FILENAME_LEN];
	char				URLString[MAX_FILENAME_LEN];
	char				logUrl[MAX_FILENAME_LEN];

	char				Cmd[CMD_LEN] = {0};
	int					CmdTimeout = 20000;			/*	Must be greater or equal to CAM_MIN_WAIT in millisecond	*/
	int					CamConnectTimout = 60000;	/*	Timeout value for _camera_conect()	*/

	int					get_image_argc;

#define					NUM_ARG_PARAMS (10)


/** Driver-specific parameters for the ARGUS driver */

#define					ARGUSoffsetAllString		"ARGUS_OFFSET_ALL"     /* (asynInt32,    r/w) Both Tabs Offset */
#define					ARGUSlineRateString			"ARGUS_LINERATE"     /* (asynInt32,    r/w Line Rate */
#define					ARGUSrestorString			"ARGUS_RESTOR"     /* (asynInt32,    r/o Restor */
#define					ARGUSactiveSignalString     "ARGUS_ACTIVE_SIGNAL"     /* (asynInt32,    r/o Restor */

/** Driver for Argus cameras using their Argus Camera API */
class argus : public ADDriver {
public:
    argus(const char *portName, const char *cameraId, int maxBuffers, size_t maxMemory,
              int priority, int stackSize, int maxPvAPIFrames);

   /* These are the methods that we override from ADDriver */
    virtual asynStatus	writeInt32(asynUser *pasynUser, epicsInt32 value); // The standard writeInt32 that is used to "put" camera paramters and accessed via asyn records
    virtual asynStatus	writeFloat64(asynUser *pasynUser, epicsFloat64 value);
    void				shutdown(); //This is called by epicsAtExit
	void				ArgusTask(); /**< Should be private, but gets called from C, so must be public */
	
                 
protected:
	int					frameRate;
	int					ARGUSoffsetAll;
	int					ARGUSlineRate;
	int					ARGUSactiveSignal;
	int					ARGUSrestor;
	int					ARGUSbinningVal;
	double				ARGUSgainAll;
	int					offsetAll;
	int					ARGUStriggerMode;
	double				ARGUSexpTime;
	int					ARGUSimageHeight;

private:                                        
    /* These are the methods that are new to this class */
    asynStatus			connectCamera();
    asynStatus			disconnectCamera();
	asynStatus			readParameters();
	asynStatus			argusStart();
	asynStatus			argusStop();
	virtual asynStatus	readImage();
	Image				image;
	char				*cameraId;
    epicsEventId		startEventId;
    epicsEventId		stopEventId;
};


static void c_shutdown(void* arg) {
    argus *p = (argus*)arg;
    p->shutdown();
}

void argus::shutdown() {

	int status = asynSuccess;;
	const char *functionName = "shutdown";

	status = disconnectCamera();

	if (!status) 
		asynPrint(this->pasynUserSelf, ASYN_TRACE_ERROR, 
			"%s: %s: Detector Disconnected\n", driverName, functionName);
} 

asynStatus argus::disconnectCamera()
{
	int status = asynSuccess;
	static const char *functionName = "disconnectCamera";


	/*	Close Camera operation	*/
	printf( "Disconnecting device\n" );
	status = _camera_disconnect( &_cam_info.WSAStatus, _cam_info.CameraResp, CmdTimeout );
	if(status)
	{
		asynPrint(this->pasynUserSelf, ASYN_TRACE_ERROR,
			"%s: %s: Can't close the camera ... \n", driverName, functionName);
		return(asynError);
	}

	return(asynSuccess);
}

asynStatus argus::connectCamera()
{

		int status = asynSuccess;
		std::string cmdBuffer;
		static const char *functionName = "connectCamera";

		memset( &_cam_info, 0, sizeof(_cam_info) );

		/*	Argus Camera Login	*/
		
		strcpy_s( _cam_info.CameraIP, this->cameraId);
		strcpy_s( _cam_info.Login, "root" );
		strcpy_s( _cam_info.Password, "root" );
		_cam_info.TARGET_PORT = TELNET_PORT;						/*	use IPPORT_TELNET is include <winsock.h>	*/
		_cam_info.WSAStatus = 0;

		// Set Argus default ADDriver parameters
		status = setStringParam(ADManufacturer, "Argus");
		status = setStringParam(ADModel, ARGUSdetectorSerial);
		status = setIntegerParam(ADMaxSizeX, MAX_WIDTH);
		status = setIntegerParam(ADMaxSizeY, MAX_HEIGHT);

		/*	Connect to Camera	*/
		/*	must define long enough timeout	*/
		/*	telnet connect default is 60sec, CmdTimeout doesn't affect telnet connect	*/
		status = _camera_connect( _cam_info.CameraIP, _cam_info.TARGET_PORT, &_cam_info.WSAStatus,
							_cam_info.CameraResp, _cam_info.Login, _cam_info.Password, CamConnectTimout );
		if(status) 
		{
			asynPrint(this->pasynUserSelf, ASYN_TRACE_ERROR,
				"%s: %s: _camera_connect failure ... \n", driverName, functionName);
			disconnectCamera();
			return(asynError);
		}

    pasynManager->exceptionConnect(this->pasynUserSelf);
    return((asynStatus)status);
}

asynStatus argus::argusStart()
{
	static const char *functionName = "argusStart";

	printf("\n----------------------------------------------\n");
	printf("Start Acqusition\n");
	printf("----------------------------------------------\n");

	return asynSuccess;
}


asynStatus argus::argusStop()
{
	static const char *functionName = "argusStop";

	printf("\n----------------------------------------------\n");
	printf("Stop Acqusition\n");
	printf("----------------------------------------------\n");

	return asynSuccess;
}

asynStatus argus::readParameters()
{

	static const char *functionName = "readParameters";
	
	asynStatus status = asynSuccess;
	int adstatus;
	int counter = 0;

	// Read Binning
	sprintf_s(Cmd, "gbm");
	adstatus = _camera_cmd( Cmd, _cam_info.CameraResp, CmdTimeout );
	if(!adstatus) {
		status = setIntegerParam(ADBinX, atoi(&_cam_info.CameraResp[38]));
		counter += 1;
	}
	// Read Size
	sprintf_s(Cmd, "gih");
	adstatus = _camera_cmd( Cmd, _cam_info.CameraResp, CmdTimeout );
	if(!adstatus) {
		status = setIntegerParam(ADSizeY, atoi(&_cam_info.CameraResp[38]));
		counter += 1;
	}
	// Read Trigger Mode
	sprintf_s(Cmd, "gim");
	adstatus = _camera_cmd( Cmd, _cam_info.CameraResp, CmdTimeout );
	if(!adstatus) {
		status = setIntegerParam(ADTriggerMode, atoi(&_cam_info.CameraResp[38]));
		counter += 1;
	}
	// Read Offset
	sprintf_s(Cmd, "gao 0");
	adstatus = _camera_cmd( Cmd, _cam_info.CameraResp, CmdTimeout );
	if(!adstatus) {
		status = setIntegerParam(ARGUSoffsetAll, atoi(&_cam_info.CameraResp[38]));
		counter += 1;
	}
	// Read Line Rate
	sprintf_s(Cmd, "glr");
	adstatus = _camera_cmd( Cmd, _cam_info.CameraResp, CmdTimeout );
	if(!adstatus) {
		setIntegerParam(ARGUSlineRate, atoi(&_cam_info.CameraResp[38]));
		counter += 1;
	}

	// Read Gain
	sprintf_s(Cmd, "gag 0");
	adstatus = _camera_cmd( Cmd, _cam_info.CameraResp, CmdTimeout );
	if(!adstatus) {
		status = setDoubleParam(ADGain, atoi(&_cam_info.CameraResp[38]));
		counter += 1;
	}
	
	// Read Active Signal
	sprintf_s(Cmd, "gad");
	adstatus = _camera_cmd( Cmd, _cam_info.CameraResp, CmdTimeout );
	if(!adstatus) {
		status = setIntegerParam(ARGUSactiveSignal, atoi(&_cam_info.CameraResp[38]));
		counter += 1;
	}

	if (counter == 7) setStringParam(ADStatusMessage, "Ok");
	if (counter < 7) setStringParam(ADStatusMessage, "Failed to read parameters");

    /* Do callbacks so higher layers see any changes */
    callParamCallbacks();

	if(status) {
		asynPrint(this->pasynUserSelf, ASYN_TRACE_ERROR,
			"%s: %s: read parameters error ... \n", driverName, functionName);
		return(asynError);
	}

	return((asynStatus)status);	
}

/** Called when asyn clients call pasynInt32->write().
  * This function performs actions for some parameters, including ADAcquire, ADBinX, etc.
  * For all parameters it sets the value in the parameter library and calls any registered callbacks..
  * \param[in] pasynUser pasynUser structure that encodes the reason and address.
  * \param[in] value Value to write. */
asynStatus argus::writeInt32(asynUser *pasynUser, epicsInt32 value)
{
    int function = pasynUser->reason;
    asynStatus status = asynSuccess;
	int adstatus;
	int offset;
	int linerate;
	int activeSignal;
	epicsInt32 oldValue;

    static const char *functionName = "writeInt32";
	
    /* Set the parameter and readback in the parameter library.  This may be overwritten when we read back the
     * status at the end, but that's OK */
	status = getIntegerParam(function, &oldValue);
    status = setIntegerParam(function, value);

    if (function == ADAcquire) {
		status = getIntegerParam(ADStatus, &adstatus);
        if (value && (adstatus == ADStatusIdle)) {
            /* Send an event to wake up the acquisition task.
             * It won't actually start generating new images until we release the lock below */
			status = argusStart();
			if(!status)
				epicsEventSignal(this->startEventId);
        }
        if (!value && (adstatus != ADStatusIdle)) {
            /* This was a command to stop acquisition */
            /* Send the stop event */
            epicsEventSignal(this->stopEventId);
			status = argusStop();
        }
	} else if(function == ADBinX) {
		status = getIntegerParam(ADBinX, &ARGUSbinningVal);
		status = getIntegerParam(ADTriggerMode, &ARGUStriggerMode);
		if(ARGUStriggerMode != 2) {
			sprintf_s(Cmd, "sbm %d", ARGUSbinningVal);
			adstatus = _camera_cmd( Cmd, _cam_info.CameraResp, CmdTimeout );		// Set the device to the binning value
			if(!adstatus) {
				status = setIntegerParam(ADBinX, atoi(&_cam_info.CameraResp[4]));
				status = setIntegerParam(ADBinY, atoi(&_cam_info.CameraResp[4]));
				switch(ARGUSbinningVal){
					case 2:
						status = setIntegerParam(ADSizeX, ArgusMaxImageHeightRangesX[0]);
						break;
					case 3:
						status = setIntegerParam(ADSizeX, ArgusMaxImageHeightRangesX[1]);
						break;
					case 4:
						status = setIntegerParam(ADSizeX, ArgusMaxImageHeightRangesX[2]);
						break;
					case 5:
						status = setIntegerParam(ADSizeX, ArgusMaxImageHeightRangesX[3]);
						break;
					case 6:
						status = setIntegerParam(ADSizeX, ArgusMaxImageHeightRangesX[4]);
						break;
				}
				status = setStringParam(ADStatusMessage, "Ok");
			} else {
				status = setStringParam(ADStatusMessage, "Binning illegal value: must be between 2-6");
				status = setIntegerParam(function, oldValue);
			}
		} else {
				status = setStringParam(ADStatusMessage, "Binning deafults to 2 in Area Mode");
				status = setIntegerParam(function, oldValue);
		}
	} else if(function == ADSizeY) {
		status = getIntegerParam(ADSizeY, &ARGUSimageHeight);
		status = getIntegerParam(ADBinX, &ARGUSbinningVal);
		switch(ARGUSbinningVal){
			case 2:
				if(ARGUSimageHeight > ArgusMaxImageHeightRangesY[0])
					status = setIntegerParam(ADSizeY, ArgusMaxImageHeightRangesY[0]);
				else
					status = setIntegerParam(ADSizeY, ARGUSimageHeight);
				break;
			case 3:
				if(ARGUSimageHeight > ArgusMaxImageHeightRangesY[1])
					status = setIntegerParam(ADSizeY, ArgusMaxImageHeightRangesY[1]);
				else
					status = setIntegerParam(ADSizeY, ARGUSimageHeight);
				break;
			case 4:
				if(ARGUSimageHeight > ArgusMaxImageHeightRangesY[2])
					status = setIntegerParam(ADSizeY, ArgusMaxImageHeightRangesY[2]);
				else
					status = setIntegerParam(ADSizeY, ARGUSimageHeight);
				break;
			case 5:
				if(ARGUSimageHeight > ArgusMaxImageHeightRangesY[3])
					status = setIntegerParam(ADSizeY, ArgusMaxImageHeightRangesY[3]);
				else
					status = setIntegerParam(ADSizeY, ARGUSimageHeight);
				break;
			case 6:
				if(ARGUSimageHeight > ArgusMaxImageHeightRangesY[4])
					status = setIntegerParam(ADSizeY, ArgusMaxImageHeightRangesY[4]);
				else
					status = setIntegerParam(ADSizeY, ARGUSimageHeight);
				break;
		}
		status = getIntegerParam(ADSizeY, &ARGUSimageHeight);
		sprintf_s(Cmd, "sih %d", ARGUSimageHeight);
		adstatus = _camera_cmd( Cmd, _cam_info.CameraResp, CmdTimeout );		// Set the image height command
		if(!adstatus) {
			status = setIntegerParam(ADSizeY, atoi(&_cam_info.CameraResp[4]));
			status = setStringParam(ADStatusMessage, "Ok");
		} 
		else {
			status = setStringParam(ADStatusMessage, "Size illegal value: min 20, max based on binning");
			status = setIntegerParam(function, oldValue);
		}
	} 
	else if(function == ADTriggerMode) {
		getIntegerParam(ADTriggerMode, &ARGUStriggerMode);
		if(ARGUStriggerMode == 0) {
			sprintf_s(Cmd, "sim %d", 0); // TDI_EXTERNAL
			adstatus = _camera_cmd( Cmd, _cam_info.CameraResp, CmdTimeout );
		}
		if(ARGUStriggerMode == 1) {
			sprintf_s(Cmd, "sim %d", 1); // TDI_INTERNAL
			adstatus = _camera_cmd( Cmd, _cam_info.CameraResp, CmdTimeout );
		}
		if(ARGUStriggerMode == 2) {
			sprintf_s(Cmd, "sim %d", 2); // AREA_INTERNAL
			adstatus = _camera_cmd( Cmd, _cam_info.CameraResp, CmdTimeout );
		}
		if(!adstatus) {
			status = setStringParam(ADStatusMessage, "Ok");
			status = setIntegerParam(ADBinX, 2); // Binning is automatically set to 2 by the detecotor on this mode, this to reflect that on EPICS
			sprintf_s(Cmd, "sbm %d", 2);
			adstatus = _camera_cmd( Cmd, _cam_info.CameraResp, CmdTimeout );		// Set the device to the binning value
			if(!adstatus) setStringParam(ADStatusMessage, "Ok");
			else status = setStringParam(ADStatusMessage, "Failed to set bin to 2 in Area Mode");
		} 
		else {
			status = setStringParam(ADStatusMessage, "Failed to set trigger value");
			status = setIntegerParam(function, oldValue);
		}
	}
	else if(function == ARGUSoffsetAll) {
		status = getIntegerParam(ARGUSoffsetAll, &offset);
		sprintf_s(Cmd, "sao 0 %d", offset); // Offset All Tabs
		adstatus = _camera_cmd( Cmd, _cam_info.CameraResp, CmdTimeout );
		if(!adstatus) {
			status = setStringParam(ADStatusMessage, "Ok");
		} 
		else {
			status = setStringParam(ADStatusMessage, "illegal value: offset range (0-511)");
			status = setIntegerParam(function, oldValue);
		}
	}
	else if(function == ARGUSlineRate) {
		status  = getIntegerParam(ARGUSlineRate, &linerate);
		sprintf_s(Cmd, "slr %d", linerate); // Line Rate
		adstatus = _camera_cmd( Cmd, _cam_info.CameraResp, CmdTimeout );
		if(!adstatus) {
			status = setStringParam(ADStatusMessage, "Ok");
		} 
		else {
			status = setStringParam(ADStatusMessage, "illegal value: LineRate range (50-2000)");
			status = setIntegerParam(function, oldValue);
		}
	}
	else if(function == ARGUSrestor) {
		sprintf_s(Cmd, "rfs"); // Restore Factory Settings
		adstatus = _camera_cmd( Cmd, _cam_info.CameraResp, CmdTimeout );
		if(!adstatus) {
			status = setStringParam(ADStatusMessage, "Restore Detector to Factory Settings");
			status = readParameters();
		} 
		else {
			status = setStringParam(ADStatusMessage, "Failed to restore detector to factory settings");
			status = setIntegerParam(function, oldValue);
		}
	}
	else if(function == ARGUSactiveSignal) {
		status = getIntegerParam(ARGUSactiveSignal, &activeSignal);
		sprintf_s(Cmd, "sad %d", activeSignal); // Restore Factory Settings
		adstatus = _camera_cmd( Cmd, _cam_info.CameraResp, CmdTimeout );
		if(!adstatus) {
			status = setStringParam(ADStatusMessage, "Ok");
		} 
		else {
			status = setStringParam(ADStatusMessage, "Failed to set active signal");
			status = setIntegerParam(function, oldValue);
		}
	}	
	else {
        /* If this parameter belongs to a base class call its method */
        status = ADDriver::writeInt32(pasynUser, value);
    }

    /* Do callbacks so higher layers see any changes */
    callParamCallbacks();

    if (status)
        asynPrint(pasynUser, ASYN_TRACE_ERROR,
              "%s:writeInt32 error, status=%d function=%d, value=%d\n",
              driverName, status, function, value);
    else
        asynPrint(pasynUser, ASYN_TRACEIO_DRIVER,
              "%s:writeInt32: function=%d, value=%d\n",
              driverName, function, value);

    return((asynStatus)status);
}

/** Called when asyn clients call pasynFloat64->write().
  * This function performs actions for some parameters, including ADAcquireTime, ADGain, etc.
  * For all parameters it sets the value in the parameter library and calls any registered callbacks..
  * \param[in] pasynUser pasynUser structure that encodes the reason and address.
  * \param[in] value Value to write. */
asynStatus argus::writeFloat64(asynUser *pasynUser, epicsFloat64 value)
{
    int function = pasynUser->reason;
    int status = asynSuccess;
    const char *paramName;
	int adstatus;
	epicsFloat64 oldValue;
    static const char *functionName = "writeFloat64";

    /* Set the parameter and readback in the parameter library.  This may be overwritten when we read back the
     * status at the end, but that's OK */
	status = getDoubleParam(function, &oldValue);

    status = getParamName(function, &paramName);
    /* Set the parameter and readback in the parameter library.  This may be overwritten when we read back the
     * status at the end, but that's OK */
    status = setDoubleParam(function, value);

    if (function == ADAcquireTime) {
		status = getDoubleParam(ADAcquireTime, &ARGUSexpTime);
		status = getIntegerParam(ADTriggerMode, &ARGUStriggerMode);
		if(ARGUStriggerMode == 2){
			sprintf_s(Cmd, "set %d", (int) ARGUSexpTime);
			adstatus = _camera_cmd( Cmd, _cam_info.CameraResp, CmdTimeout );
			if(!adstatus) {
				status = setStringParam(ADStatusMessage, "Ok");
			} 
			else {
				status = setStringParam(ADStatusMessage, "iLlegal Value: Expousre range 1-8191 ms");
				status = setDoubleParam(function, oldValue);
			}
		} else {
				status = setStringParam(ADStatusMessage, "Trigger should be on Area mode");
		}
	} else if(function == ADGain) {
		status = getDoubleParam(ADGain, &ARGUSgainAll);
		sprintf_s(Cmd, "sag 0 %d", (int) ARGUSgainAll);
		adstatus = _camera_cmd( Cmd, _cam_info.CameraResp, CmdTimeout );
		if(!adstatus) {
			status = setStringParam(ADStatusMessage, "Ok");
		} 
		else {
			status = setStringParam(ADStatusMessage, "iLlegal Value: Gain range 0-63");
			status = setDoubleParam(function, oldValue);
		}
	} else if(function == ADTemperature) {
		sprintf_s(Cmd, "vt"); // Restore Factory Settings
		adstatus = _camera_cmd( Cmd, _cam_info.CameraResp, CmdTimeout );
		if(!adstatus) {
			status = setDoubleParam(ADTemperature, atoi(&_cam_info.CameraResp[37]));
		} 
		else {
			status = setStringParam(ADStatusMessage, "Failed to read temp");
			status = setDoubleParam(function, oldValue);
		}	
	} else {
        /* If this is not a parameter we have handled call the base class */
        status = ADDriver::writeFloat64(pasynUser, value);
    }

    /* Do callbacks so higher layers see any changes */
    callParamCallbacks();
    if (status)
        asynPrint(pasynUser, ASYN_TRACE_ERROR,
              "%s:writeInt32 error, status=%d function=%d, value=%d\n",
              driverName, status, function, value);
    else
        asynPrint(pasynUser, ASYN_TRACEIO_DRIVER,
              "%s:writeInt32: function=%d, value=%d\n",
              driverName, function, value);

    return((asynStatus)status);
}

asynStatus argus::readImage()
{
    int dims[3];
    int ndims;
    int nrows, ncols;
    ImageType imageType;
    StorageType storageType;
    NDDataType_t dataType;
    NDColorMode_t colorMode;
    NDArrayInfo_t arrayInfo;
    NDArray *pImage = this->pArrays[0];
	int status = asynSuccess;
    int depth;
    const char *map;
	epicsTimeStamp startTime;
    static const char *functionName = "readImage";

	char *get_image_argv[] = {
		"_camera_get_image",
		"-w",		//wait for 2 second, value from original .bat file
		"2",		
		"-T",		//timeout 15 second, value from original .bat file
		"15",				
		"-O",		//output file name, can use absolute path to it, but have to use Linux path divider "/"
		imagePath,
		"-o",		//use log file, supress dll output to stdout, caller crashes if stdout is not handled
		logPath,				/*	please create a folder to keep the log file	*/
		logUrl,
	};
    
	memset( &arrayInfo, 0, sizeof(arrayInfo) );

	get_image_argc = (sizeof(get_image_argv) / sizeof(get_image_argv[0]));
	/*	grab image 	*/
	epicsTimeGetCurrent(&startTime);
	printf("\nAcquiring image ... \n");
	strcpy_s( Cmd, "acq" );
	status = _camera_cmd( Cmd, _cam_info.CameraResp, INFINITE);
	if(status) {
		asynPrint(pasynUserSelf, ASYN_TRACE_ERROR, 
			"%s:%s: time out ... \n", 
                driverName, functionName);
		return(asynError);
	}
	printf("Downloading image from Argus ... \n");
	status = _camera_get_image( get_image_argc, get_image_argv, _cam_info.CameraResp);
	epicsTimeGetCurrent(&startTime);
    if (strlen(URLString) == 0) return(asynError);
    try {
        image.read(URLString);
        imageType = image.type();
        depth = image.depth();
        nrows = image.rows();
        ncols = image.columns();
		switch(imageType) {
		case GrayscaleType:
            ndims = 2;
            dims[0] = ncols;
            dims[1] = nrows;
            dims[2] = 0;
            map = "R";
            colorMode = NDColorModeMono;
            break;
        case TrueColorType:
            ndims = 3;
            dims[0] = 3;
            dims[1] = ncols;
            dims[2] = nrows;
            map = "RGB";
            colorMode = NDColorModeRGB1;
            break;
        default:
            asynPrint(pasynUserSelf, ASYN_TRACE_ERROR, 
                "%s:%s: unknown ImageType=%d\n", 
                driverName, functionName, imageType);
            return(asynError);
            break;
        }
        switch(depth) {
        case 1:
        case 8:
            dataType = NDUInt8;
            storageType = CharPixel;
            break;
        case 16:
            dataType = NDUInt16;
            storageType = ShortPixel;
            break;
        case 32:
            dataType = NDUInt32;
            storageType = IntegerPixel;
            break;
        default:
            asynPrint(pasynUserSelf, ASYN_TRACE_ERROR, 
                "%s:%s: unsupported depth=%d\n", 
                driverName, functionName, depth);
            return(asynError);
            break;
        }
        if (pImage) pImage->release();
        this->pArrays[0] = this->pNDArrayPool->alloc(ndims, dims, dataType, 0, NULL);
        pImage = this->pArrays[0];

        asynPrint(this->pasynUserSelf, ASYN_TRACEIO_DRIVER,
            "%s:%s: reading URL=%s, dimensions=[%d,%d,%d], ImageType=%d, depth=%d\n",
            driverName, functionName, URLString, dims[0], dims[1], dims[2], imageType, depth);

        image.write(0, 0, ncols, nrows, map, storageType, pImage->pData);
		epicsTimeGetCurrent(&startTime);
        pImage->pAttributeList->add("ColorMode", "Color mode", NDAttrInt32, &colorMode);
        setIntegerParam(ADSizeX, ncols);
        setIntegerParam(NDArraySizeX, ncols);
        setIntegerParam(ADSizeY, nrows);
        setIntegerParam(NDArraySizeY, nrows);
        pImage->getInfo(&arrayInfo);
        setIntegerParam(NDArraySize,  arrayInfo.totalBytes);
        setIntegerParam(NDDataType, dataType);
        setIntegerParam(NDColorMode, colorMode);
    }
    catch(std::exception &error)
    {
        asynPrint(this->pasynUserSelf, ASYN_TRACE_ERROR, 
            "%s:%s: error reading URL=%s\n", 
            driverName, functionName, error.what());
        return(asynError);
    }
         
    return(asynSuccess);
}

static void ArgusTaskC(void *drvPvt)
{
    argus *pPvt = (argus *)drvPvt;

    pPvt->ArgusTask();
}

/** This thread calls computeImage to compute new image data and does the callbacks to send it to higher layers.
  * It implements the logic for single, multiple or continuous acquisition. */
void argus::ArgusTask()
{
    int status = asynSuccess;
    asynStatus imageStatus;
    int imageCounter;
    int numImages, numImagesCounter;
    int imageMode;
    int arrayCallbacks;
    int acquire;
    NDArray *pImage;
    double acquirePeriod, delay;
    epicsTimeStamp startTime, endTime;
    double elapsedTime;
    const char *functionName = "ArgusTask";

    this->lock();
    /* Loop forever */
    while (1) {
        /* Is acquisition active? */
		this->unlock();
		callParamCallbacks();
        status = getIntegerParam(ADAcquire, &acquire);
        this->lock();
        /* If we are not acquiring then wait for a semaphore that is given when acquisition is started */
        if (!acquire) {
            status = setIntegerParam(ADStatus, ADStatusIdle);
            callParamCallbacks();
            /* Release the lock while we wait for an event that says acquire has started, then lock again */
            asynPrint(this->pasynUserSelf, ASYN_TRACE_FLOW,
                "%s:%s: waiting for acquire to start\n", driverName, functionName);
            this->unlock();
            status = epicsEventWait(this->startEventId);
            this->lock();
            status = setIntegerParam(ADNumImagesCounter, 0);
        }

        /* We are acquiring. */
        /* Get the current time */
        status = epicsTimeGetCurrent(&startTime);

        /* Get the exposure parameters */
        status = getDoubleParam(ADAcquirePeriod, &acquirePeriod);

        status = setIntegerParam(ADStatus, ADStatusAcquire);

        /* Open the shutter */
        setShutter(ADShutterOpen);

        /* Call the callbacks to update any changes */
        callParamCallbacks();

        /* Read the image */
        imageStatus = readImage();

        /* Close the shutter */
        setShutter(ADShutterClosed);
        /* Call the callbacks to update any changes */
        callParamCallbacks();

        if (imageStatus == asynSuccess) {
            pImage = this->pArrays[0];

            /* Get the current parameters */
            status = getIntegerParam(NDArrayCounter, &imageCounter);
            status = getIntegerParam(ADNumImages, &numImages);
            status = getIntegerParam(ADNumImagesCounter, &numImagesCounter);
            status = getIntegerParam(ADImageMode, &imageMode);
            status = getIntegerParam(NDArrayCallbacks, &arrayCallbacks);
            imageCounter++;
            numImagesCounter++;
            status = setIntegerParam(NDArrayCounter, imageCounter);
            status = setIntegerParam(ADNumImagesCounter, numImagesCounter);

            /* Put the frame number and time stamp into the buffer */
            pImage->uniqueId = imageCounter;
            pImage->timeStamp = startTime.secPastEpoch + startTime.nsec / 1.e9;

            /* Get any attributes that have been defined for this driver */
            this->getAttributes(pImage->pAttributeList);

            if (arrayCallbacks) {
                /* Call the NDArray callback */
                /* Must release the lock here, or we can get into a deadlock, because we can
                 * block on the plugin lock, and the plugin can be calling us */
                this->unlock();
                asynPrint(this->pasynUserSelf, ASYN_TRACE_FLOW,
                     "%s:%s: calling imageData callback\n", driverName, functionName);
                doCallbacksGenericPointer(pImage, NDArrayData, 0);
                this->lock();
            }
        }

        /* See if acquisition is done */

        if (imageStatus != asynSuccess)
			status = setStringParam(ADStatusMessage, "Error");

        if ((imageMode == ADImageSingle) ||
            ((imageMode == ADImageMultiple) &&
             (numImagesCounter >= numImages))) {
            status = setIntegerParam(ADAcquire, 0);
			status = argusStop();
            asynPrint(this->pasynUserSelf, ASYN_TRACE_FLOW,
                  "%s:%s: acquisition completed\n", driverName, functionName);
        }

        /* Call the callbacks to update any changes */
        callParamCallbacks();
        status = getIntegerParam(ADAcquire, &acquire);

        /* If we are acquiring then sleep for the acquire period minus elapsed time. */
        if (acquire) {
            epicsTimeGetCurrent(&endTime);
            elapsedTime = epicsTimeDiffInSeconds(&endTime, &startTime);
            delay = acquirePeriod - elapsedTime;
            asynPrint(this->pasynUserSelf, ASYN_TRACE_FLOW,
                     "%s:%s: delay=%f\n",
                      driverName, functionName, delay);
            if (delay >= 0.0) {
                /* We set the status to readOut to indicate we are in the period delay */
                status = setIntegerParam(ADStatus, ADStatusWaiting);
                callParamCallbacks();
                this->unlock();
                status = epicsEventWaitWithTimeout(this->stopEventId, delay);
                this->lock();
            }
        }
    }
}

extern "C" int argusConfig(char *portName, /* Port name */
                               const char *cameraId,   /* Unique ID #, or IP address or IP name of this camera. */
                               int maxBuffers, size_t maxMemory,
                               int priority, int stackSize, int maxPvAPIFrames)
{
    new argus(portName, cameraId, maxBuffers, maxMemory, priority, stackSize, maxPvAPIFrames);
    return(asynSuccess);
}   


/** Constructor for Argus driver; most parameters are simply passed to ADDriver::ADDriver.
  * After calling the base class constructor this method creates a thread to collect the detector data, 
  * and sets reasonable default values for the parameters defined in this class, asynNDArrayDriver and ADDriver.
  * \param[in] portName The name of the asyn port driver to be created.
  * \param[in] cameraId The uniqueId, IP address or IP DNS name  of the camera to be connected to this driver.
  * \param[in] maxBuffers The maximum number of NDArray buffers that the NDArrayPool for this driver is 
  *            allowed to allocate. Set this to -1 to allow an unlimited number of buffers.
  * \param[in] maxMemory The maximum amount of memory that the NDArrayPool for this driver is 
  *            allowed to allocate. Set this to -1 to allow an unlimited amount of memory.
  * \param[in] priority The thread priority for the asyn port driver thread if ASYN_CANBLOCK is set in asynFlags.
  * \param[in] stackSize The stack size for the asyn port driver thread if ASYN_CANBLOCK is set in asynFlags.
  * \param[in] maxPvAPIFrames The number of frame buffers to use in the PvAPI library driver. Default=MAX_PVAPI_FRAMES=2.
  */
argus::argus(const char *portName, const char *cameraId, int maxBuffers, size_t maxMemory,
                     int priority, int stackSize, int maxPvAPIFrames)
    : ADDriver(portName, 1, NUM_ARG_PARAMS, maxBuffers, maxMemory, 
               0, 0,               /* No interfaces beyond those set in ADDriver.cpp */
               ASYN_CANBLOCK, 1,   /* ASYN_CANBLOCK=1, ASYN_MULTIDEVICE=0, autoConnect=1 */
               priority, stackSize)  

{
    int status = asynSuccess;

    static const char *functionName = "argus";

	this->cameraId = epicsStrDup(cameraId);

	printf("Read System Drive env var\n");

	pDL = getenv("SystemDrive");

	if (pDL){
		sprintf(dPath, "%s\\argustmp", pDL);
		sprintf(imagePath, "%s/argustmp/image.tiff", pDL);
		sprintf(logPath, "%s/argustmp/_camera_get_image.log", pDL);
		sprintf(URLString,"%s\\argustmp\\image.tiff", pDL);
		sprintf(logUrl, "http://%s/images/tp.tiff", this->cameraId);
		printf("The argus tmp directory is = %s\n", dPath);
	}
	else {
		printf("SystemDrive env var is not set\n");
		return;
	}
	if(ERROR_ALREADY_EXISTS == GetLastError()) 
		printf("Argus tmp dir exist\n");
	else{
		CreateDirectory(dPath, NULL);
		printf("Create Argus tmp dir\n");
	}

	//if (CreateDirectory("c:\tmp\argus", NULL) ||
	//	ERROR_ALREADY_EXISTS == GetLastError())
	//	printf("Create tmp dir for Argus\n");
	//else
	//	printf("Argus tmp dir exist\n");

	createParam(ARGUSoffsetAllString,		asynParamInt32,		&ARGUSoffsetAll);
	createParam(ARGUSlineRateString,		asynParamInt32,		&ARGUSlineRate);
	createParam(ARGUSrestorString,			asynParamInt32,		&ARGUSrestor);
	createParam(ARGUSactiveSignalString,	asynParamInt32,		&ARGUSactiveSignal);

     /* It is not a fatal error if we cannot now, the camera may be off or owned by
     * someone else.  It may connect later. */
	printf("%s: Camera ID = %s\n", functionName, this->cameraId);

	/* Initialize GraphicsMagick */
    InitializeMagick(NULL);

    status = connectCamera();
	// Sleep a little bit for camera to connect
	//epicsThreadSleep(0.5);
    if (status) {
        printf("%s:%s: cannot connect to camera %s, manually connect when available.\n", 
               driverName, functionName, cameraId);
        return;
    }
    
    /* Create the epicsEvents for signaling to the acquisition task when acquisition starts and stops */
    this->startEventId = epicsEventCreate(epicsEventEmpty);
    if (!this->startEventId) {
        printf("%s:%s epicsEventCreate failure for start event\n",
            driverName, functionName);
        return;
    }
    this->stopEventId = epicsEventCreate(epicsEventEmpty);
    if (!this->stopEventId) {
        printf("%s:%s epicsEventCreate failure for stop event\n",
            driverName, functionName);
        return;
    }

    /* Create the thread that updates the images */
    status = (epicsThreadCreate("ArgusDriverTask",
                                epicsThreadPriorityMedium,
                                epicsThreadGetStackSize(epicsThreadStackMedium),
                                (EPICSTHREADFUNC)ArgusTaskC,
                                this) == NULL);
    if (status) {
        printf("%s:%s epicsThreadCreate failure for image read task\n",
            driverName, functionName);
        return;
    }

    /* Register the shutdown function for epicsAtExit */
    epicsAtExit(c_shutdown, (void*)this);

}
/* Code for iocsh registration */
static const iocshArg argusConfigArg0 = {"Port name", iocshArgString};
static const iocshArg argusConfigArg1 = {"Camera Id (unique ID, IP address, or IP name", iocshArgString};
static const iocshArg argusConfigArg2 = {"maxBuffers", iocshArgInt};
static const iocshArg argusConfigArg3 = {"maxMemory", iocshArgInt};
static const iocshArg argusConfigArg4 = {"priority", iocshArgInt};
static const iocshArg argusConfigArg5 = {"stackSize", iocshArgInt};
static const iocshArg argusConfigArg6 = {"maxPvAPIFrames", iocshArgInt};
static const iocshArg * const argusConfigArgs[] = {&argusConfigArg0,
                                                       &argusConfigArg1,
                                                       &argusConfigArg2,
                                                       &argusConfigArg3,
                                                       &argusConfigArg4,
                                                       &argusConfigArg5,
                                                       &argusConfigArg6};
static const iocshFuncDef configargus = {"argusConfig", 7, argusConfigArgs};
static void configargusCallFunc(const iocshArgBuf *args)
{
    argusConfig(args[0].sval, args[1].sval, args[2].ival, 
                    args[3].ival, args[4].ival, args[5].ival, args[6].ival);
}


static void argusRegister(void)
{

    iocshRegister(&configargus, configargusCallFunc);
}

extern "C" {
epicsExportRegistrar(argusRegister);
}
