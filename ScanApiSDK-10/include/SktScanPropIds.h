/*
SktScanPropIds.h
Property ID definitions for Socket ScanAPI
(c) Socket Mobile, Inc.
*/

/*
NOTES: 
IF ANY MODIFICATION IS MADE IN THIS FILE THE SCANAPI INTERFACE VERSION
WILL NEED TO BE UPDATED TO IDENTIFY THIS CHANGE.
THE SCANAPI INTERFACE VERSION IS DEFINED IN SktScanAPI.h
THE MODIFICATION MUST BE DESCRIBED IN ScanAPI.doc
*/

/*
Definition of a Socket Scan Prop ID

  31  30  29  28  27  26  25  24  23  22  21  20  19  18  17  16  15  14  13  12  11  10  9   8   7   6   5   4   3   2   1   0 
---------------------------------------------------------------------------------------------------------------------------------
|   |   |   |   |   |   |   |   |   |   |   |   |   |   |   |   |   |   |   |   |   |   |   |   |   |   |   |   |   |   |   |   |
---------------------------------------------------------------------------------------------------------------------------------
  |	  |                       |   |           |   |           |   |           |   |           |    |                           |  
  |   \=======================/   \===========/   \===========/   \===========/   \===========/    \===========================/
  |               |                     |               |              |               |                         |
  |               |                     |               |              |               | Group ID                \------------------>Property ID
  |               |                     |               |              | Reserved      \-------------------------------------------->Group ID
  |               |                     |               | Set Type     \------------------------------------------------------------>Reserved must be 0
  |               |                     | Get Type      \--------------------------------------------------------------------------->Set Type (type of the property during a Set operation)
  |               | Reserved            \------------------------------------------------------------------------------------------->Get Type (type of the property during a Get operation)
  |  ScanAPI      \----------------------------------------------------------------------------------------------------------------->Reserved must be 0
  \--------------------------------------------------------------------------------------------------------------------------------->ScanAPI Prop ID (property only for ScanAPI)

*/
#ifndef _SktScanPropIds_h
#define _SktScanPropIds_h

#define SKTPROPIDSCANAPI(scanApi)		(scanApi<<31)
#define SKTGETTYPE(type)				(type<<20)
#define SKTSETTYPE(type)				(type<<16)
#define SKTSETGROUPID(groupId)			(groupId<<8)
#define SKTSETPROPID(propId)			(propId)
#define SKTISSCANAPI(propId)			(propId>>31)
#define SKTRETRIEVEID(propId)			(propId&0x000000ff)
#define SKTRETRIEVESETTYPE(propId)		((propId>>16)&0x0000000f)
#define SKTRETRIEVEGETTYPE(propId)		((propId>>20)&0x0000000f)
#define SKTRETRIEVEGROUPID(groupId)		((groupId>>8)&0x0000000f)

// group IDs for properties
enum
{
	kSktScanGroupGeneral,
	kSktScanGroupLocalFunctions
};

// properties for the ScanAPI General Group
enum
{
	kSktScanIdAbort,
	kSktScanIdVersion,
	kSktScanIdInterfaceVersion,
	kSktScanIdConfiguration,
	kSktScanIdDataConfirmationMode,
	kSktScanIdDataConfirmationAction,
	kSktScanIdMonitorMode,				// new
	kSktScanIdSoftScanStatus,			// new
	kSktScanIdSymbologyInfo,			// newer
	kSktScanIdDataEditingProfile,		// new
	kSktScanIdDataEditingCurrentProfile,
	kSktScanIdDataEditingTriggerSymbologies,
	kSktScanIdDataEditingTriggerMinLength,
	kSktScanIdDataEditingTriggerMaxLength,
	kSktScanIdDataEditingTriggerStartsBy,
	kSktScanIdDataEditingTriggerEndsWith,
	kSktScanIdDataEditingTriggerContains,
	kSktScanIdDataEditingOperation,
	kSktScanIdDataEditingImportExport,
	kSktScanLastGeneralGroup
};

// properties for the device General Group
enum
{
	kSktScanIdDeviceVersion,
	kSktScanIdDeviceInterfaceVersion,
	kSktScanIdDeviceType,
	kSktScanIdDeviceSpecific,
	kSktScanIdDeviceSymbology,
	kSktScanIdDeviceTrigger,
	kSktScanIdDeviceApplyConfig,
	kSktScanIdDevicePreamble,
	kSktScanIdDevicePostamble,
	kSktScanIdDeviceCapabilities,
	kSktScanIdDeviceChangeId,
	kSktScanIdDeviceDataFormat,
	kSktScanLastDeviceGeneralGroup
};

// properties for the Local Functions Group
enum
{
	kSktScanIdDeviceFriendlyName,
	kSktScanIdDeviceSecurityMode,
	kSktScanIdDevicePinCode,
	kSktScanIdDeviceDeletePairingBonding,
	kSktScanIdDeviceRestoreFactoryDefaults,
	kSktScanIdDeviceSetPowerOff,
	kSktScanIdDeviceButtonsStatus,
	kSktScanIdDeviceSoundConfig,
	kSktScanIdDeviceTimers,
	kSktScanIdDeviceLocalAcknowledgement,
	kSktScanIdDeviceDataConfirmation,
	kSktScanIdDeviceBatteryLevel,
	kSktScanIdDeviceLocalDecodeAction,
	kSktScanIdDeviceBluetoothAddress,
	kSktScanIdDeviceStatisticCounters,
	kSktScanIdDeviceRumbleConfig,
	kSktScanIdDeviceProfileConfig,
	kSktScanIdDeviceDisconnect,
	kSktScanIdDeviceDataStore,
	kSktScanIdDeviceNotifications,
	kSktScanIdDeviceConnectReason,
	kSktScanIdDevicePowerState,			
	kSktScanIdDeviceStartUpRoleSPP,
	kSktScanIdDeviceConnectionBeepConfig,
	kSktScanIdDeviceFlash,		
	kSktScanIdDeviceOverlayView,			
	kSktScanIdDeviceStandConfig,					// new
	kSktScanLastDeviceLocalFunctions
};

// ScanAPI configuration
#define kSktScanConfigSerialComPort "SerialPorts"	// indicates which com port ScanAPI listens
#define kSktScanConfigPath			"ConfigPath"	// indicates where ScanAPI config file is located

// Monitor Debug -only available on build with traces turned on-
#define kSktScanConfigMonitorDbgLevel			"MonitorDbgLevel"			// indicates what ScanAPI monitor Debug Level should be used
#define kSktScanConfigMonitorDbgFileLineLevel	"MonitorDbgFileLineLevel"	// indicates what ScanAPI monitor Debug File Line level should be used
#define kSktScanConfigMonitorDbgChannel			"MonitorDbgChannel"			// indicates what ScanAPI monitor Debug Channel should be used


// Data Confirmation Mode indicates what is
// expected to the send the Data ACK back to the scanner
enum ESktScanDataConfirmationMode
{
	kSktScanDataConfirmationModeOff,			// use the device configuration (Local Confirmation or App)
	kSktScanDataConfirmationModeDevice,			// the device confirms the decoded data locally
	kSktScanDataConfirmationModeScanAPI,		// ScanAPI confirms the decoded data as it receives them and there is one app
	kSktScanDataConfirmationModeApp				// the Application confirms the decoded data as it receives them
};

// Device Data Acknowledgment mode
enum ESktScanDeviceDataAcknowledgment
{
	kSktScanDeviceDataAcknowledgmentOff,	// the device won't locally acknowledge decoded data
	kSktScanDeviceDataAcknowledgmentOn		// the device will locally acknowledge decoded data
};

// Security Mode
enum ESktScanSecurityMode
{
	kSktScanSecurityModeNone,
	kSktScanSecurityModeAuthentication,
	kSktScanSecurityModeAuthenticationEncryption
};

// Trigger parameter
enum
{
    kSktScanTriggerStart=1,          // start a scan
    kSktScanTriggerStop,             // stop a scan
    kSktScanTriggerEnable,           // enable the trigger
    kSktScanTriggerDisable,          // disable the trigger
    kSktScanTriggerContinuousScan    // start a scan in continuous mode (SoftScan scanner only, ESKT_NOTSUPPORTED returned when used with other scanner)
};

// Delete Pairing Parameter
enum
{
	kSktScanDeletePairingCurrent=0,
	kSktScanDeletePairingAll=1
};


// Sound configuration parameters
// sound configuration Action Type
enum
{
	kSktScanSoundActionTypeGoodScan,
	kSktScanSoundActionTypeGoodScanLocal,
	kSktScanSoundActionTypeBadScan,
	kSktScanSoundActionTypeBadScanLocal
};

// sound configuration frequency
enum
{
	kSktScanSoundFrequencyNone=0,
	kSktScanSoundFrequencyLow,
	kSktScanSoundFrequencyMedium,
	kSktScanSoundFrequencyHigh,
	kSktScanSoundFrequencyLast		// max count, not an actual frequency
};

// Rumble configuration parameters
// Rumble configuration Action Type
enum
{
	kSktScanRumbleActionTypeGoodScan,
	kSktScanRumbleActionTypeGoodScanLocal,
	kSktScanRumbleActionTypeBadScan,
	kSktScanRumbleActionTypeBadScanLocal
};


// configuration for the Local Decode Action
enum
{
	kSktScanLocalDecodeActionNone=0,
	kSktScanLocalDecodeActionBeep=1,
	kSktScanLocalDecodeActionFlash=2,
	kSktScanLocalDecodeActionRumble=4
};

// configuration for the Data Confirmation property
enum
{
	kSktScanDataConfirmationLedNone=0,
	kSktScanDataConfirmationLedGreen=1,
	kSktScanDataConfirmationLedRed=2,
};
enum
{
	kSktScanDataConfirmationBeepNone=0,
	kSktScanDataConfirmationBeepGood=1,
	kSktScanDataConfirmationBeepBad=2,
};
enum
{
	kSktScanDataConfirmationRumbleNone=0,
	kSktScanDataConfirmationRumbleGood=1,
	kSktScanDataConfirmationRumbleBad=2
};
enum
{
	kSktScanFlashOff=0,
	kSktScanFlashOn=1
};
enum
{
	kSktScanEnableSoftScan=0,
	kSktScanDisableSoftScan=1,
    kSktScanSoftScanNotSupported=2,// make the SoftScan feature not supported (Set Property only)
    kSktScanSoftScanSupported=3// make the SoftScan feature supported (Set property only)
};

// Macros to build a Data Confirmation or to extract fields
// from the Data Confirmation. Note: reserved should be set to 0.
#define SKTDATACONFIRMATION(reserved,rumble,beep,led) ((reserved<<6)|(rumble<<4)|(beep<<2)|led)
#define SKTDATACONFIRMATION_LED(dataConfirmation) (dataConfirmation&0x03)
#define SKTDATACONFIRMATION_BEEP(dataConfirmation) ((dataConfirmation>>2)&0x03)
#define SKTDATACONFIRMATION_RUMBLE(dataConfirmation) ((dataConfirmation>>4)&0x03)


// Macros to retrieve the Buttons status
#define SKTBUTTON_ISLEFTPRESSED(buttonsStatus)	((buttonsStatus&0x01)==0x01)
#define SKTBUTTON_ISRIGHTPRESSED(buttonsStatus)	((buttonsStatus&0x02)==0x02)
#define SKTBUTTON_ISMIDDLEPRESSED(buttonsStatus)((buttonsStatus&0x04)==0x04)
#define SKTBUTTON_ISPOWERPRESSED(buttonsStatus)	((buttonsStatus&0x08)==0x08)
#define SKTBUTTON_ISRINGDETACHED(buttonsStatus)	((buttonsStatus&0x10)==0x10)

#define SKTBUTTON_LEFTPRESSED(pressed)			(pressed&0x01)
#define SKTBUTTON_RIGHTPRESSED(pressed)			((pressed<<1)&0x02)
#define SKTBUTTON_MIDDLEPRESSED(pressed)		((pressed<<2)&0x04)
#define SKTBUTTON_POWERPRESSED(pressed)			((pressed<<3)&0x08)
#define SKTBUTTON_RINGDETACHED(detached)		((detached<<4)&0x10)

// Power State
enum
{
	kSktScanPowerStatusUnknown=		0x00,
	kSktScanPowerStatusOnBattery=	0x01,
	kSktScanPowerStatusOnCradle=	0x02,
	kSktScanPowerStatusOnAc=		0x04
};

// Macros to retrieve the Power status
#define SKTPOWER_GETSTATE(powerStatus)		(unsigned char)(powerStatus&0x000000FF)
#define SKTPOWER_SETSTATE(powerStatus)		(powerStatus&0x000000FF)

// Macro to retrieve the Battery Level
#define SKTBATTERY_GETMINLEVEL(powerStatus)	(unsigned char)(powerStatus>>16)
#define SKTBATTERY_GETMAXLEVEL(powerStatus)	(unsigned char)(powerStatus>>24)
#define SKTBATTERY_GETCURLEVEL(powerStatus)	(unsigned char)(powerStatus>>8)
#define SKTBATTERY_SETMINLEVEL(powerStatus)	((powerStatus&0x000000FF)<<16)
#define SKTBATTERY_SETMAXLEVEL(powerStatus)	((powerStatus&0x000000FF)<<24)
#define SKTBATTERY_SETCURLEVEL(powerStatus)	((powerStatus&0x000000FF)<<8)


//Monitor property
enum
{
	kSktScanMonitorDbgLevel=1,
	kSktScanMonitorDbgChannel,
	kSktScanMonitorDbgFileLineLevel,
	kSktScanMonitorLast
};


// Capability Groups
enum
{
	kSktScanCapabilityGeneral=1,		// Capabilities supported by all devices
	kSktScanCapabilityLocalFunctions=2	// Capabilities for devices supporting Local Function
};

// General Capabilities
enum
{
	kSktScanCapabilityGeneralLocalFunctions=0x00000001	// when this bit is on the device has the Local Functions capability
};

// Local Functions Capabilities
enum
{
	kSktScanCapabilityLocalFunctionRumble	=0x00000001,	// when this bit is on the device has the Rumble feature
	kSktScanCapabilityLocalFunctionChangeID	=0x00000002		// when this bit is on the device has the Change ID feature
};


// statistic Counter identifiers
enum
{
	kSktScanCounterUnknown=0,
	kSktScanCounterConnect=1,
	kSktScanCounterDisconnect=2,
	kSktScanCounterUnbond=3,
	kSktScanCounterFactoryReset=4,
	kSktScanCounterScans=5,
	kSktScanCounterScanButtonUp=6,
	kSktScanCounterScanButtonDown=7,
	kSktScanCounterPowerButtonUp=8,
	kSktScanCounterPowerButtonDown=9,
	kSktScanCounterPowerOnACTimeInMinutes=10,
	kSktScanCounterPowerOnBatTimeInMinutes=11,
// SSI only
	kSktScanCounterRfcommSend=12,
	kSktScanCounterRfcommReceive=13,
	kSktScanCounterRfcommReceiveDiscarded=14,
	kSktScanCounterUartSend=15,
	kSktScanCounterUartReceive=16,
	kSktScanCounterUartReceiveDiscarded=17,
// Specific to CRS
	kSktScanCounterButtonLeftPress=18,
    kSktScanCounterButtonLeftRelease=19,
    kSktScanCounterButtonRightPress=20,
    kSktScanCounterButtonRightRelease=21,
    kSktScanCounterRingUnitDetachEvents=22,
    kSktScanCounterRingUnitAttachEvents=23,

// 7X only (ISCI)
	kSktScanCounterDecodedBytes=24,
	kSktScanCounterAbnormalShutDowns=25,
	kSktScanCounterBatteryChargeCycles=26,
	kSktScanCounterBatteryChangeCount=27,

// Only on 8Ci
	kSktScanCounterPowerOn=28,
	kSktScanCounterPowerOff=29,

// 7X/Q only 7630 and higher
kSktScanStandModeChange = 30,

	kSktScanCounterLast // this is not a counter, just the last index
};

// disconnect parameter
enum
{
	kSktScanDisconnectStartProfile=0, // disconnect and then start the selected profile
	kSktScanDisconnectDisableRadio=1  // disconnect and disable radio (low power)
};

// profile select parameter
enum
{
	kSktScanProfileSelectNone=0,
	kSktScanProfileSelectSpp=1,
	kSktScanProfileSelectHid=2
};

// profile Config Role parameter
enum
{
	kSktScanProfileConfigNone=0,
	kSktScanProfileConfigAcceptor=1,
	kSktScanProfileConfigInitiator=2
};

// notifications masks
enum
{
    kSktScanNotificationsScanButtonPress      = 1 << 0,       // Enable scan button press notifications       
    kSktScanNotificationsScanButtonRelease    = 1 << 1,       // Enable scan button release notifications     
    kSktScanNotificationsPowerButtonPress     = 1 << 2,       // Enable power button release notifications    
    kSktScanNotificationsPowerButtonRelease   = 1 << 3,       // Enable power button release notifications    
    kSktScanNotificationsPowerState           = 1 << 4,       // Enable power state change notifications      
    kSktScanNotificationsBatteryLevelChange   = 1 << 5        // Enable battery level change notifications    
};

// timer identifications
enum
{
    kSktScanTimerTriggerAutoLockTimeout = 1,   // Trigger lock selected
    kSktScanTimerPowerOffDisconnected   = 2,   // Disconnected state timeout
    kSktScanTimerPowerOffConnected      = 4,   // Connected state timeout
};

// Data format
enum
{
	kSktScanDataFormatRaw	=0,
	kSktScanDataFormatPacket=1
};

// Trigger Mode
enum
{
	kSktScanTriggerModeLocalOnly		=1, // Normal trigger on the device
	kSktScanTriggerModeRemoteAndLocal	=2, // Normal trigger on the device or trigger from host
	kSktScanTriggerModeAutoLock			=3, // Auto Trigger Lock waiting for the host to unlock
	kSktScanTriggerModeNormalLock		=4, // the trigger is locked and unlocked locally
	kSktScanTriggerModePresentation		=5
};

// Connect Reason
enum
{
	kSktScanConnectReasonUnknown	=0, // unknown reason
	kSktScanConnectReasonPowerOn	=1, // the device has connected because it powers on
	kSktScanConnectReasonBarcode	=2,	// the device has connected because it scans a connect barcode
	kSktScanConnectReasonUserAction =3, // the device has connected because the user press the power button or the trigger button
	kSktScanConnectReasonHostChange	=4, // the device has connected because the host has changed
	kSktScanConnectReasonRetry		=5	// the device has connected because it is back in range
};

// Start Up Role SPP
enum
{
	kSktScanStartUpRoleSPPAcceptor	=0, // the SPP Role will always be Acceptor
	kSktScanStartUpRoleSPPLastRole	=1	// the SPP Role will always be what was the last SPP Role config
};

// Connect Beep Config
enum
{
	kSktScanConnectBeepConfigNoBeep	=0,	// don't beep when a connection is established
	kSktScanConnectBeepConfigBeep	=1	// Beep when a connection is established
};

// Stand Config
// 0 - Mobile mode Works like today existing firmware Engine is always in 
//     trigger mode Engine hibernate enabled
// 1 - Stand mode Engine always in presentation mode Engine hibernate 
//     disabled Scanner turns on immediately Power timers disabled Connection 
//     retries forever
// 2 - Detect mode On stand engine in presentation mode On stand engine 
//     hibernate disabled On stand charging led state not show On stand 
//     scanner turns on immediately On stand power timers disabled On stand 
//     connection retries forever Off stand engine in level mode Off stand 
//     battery led state reported Off stand engine hibernate enabled Off stand 
//     power off timers running Off stand connection retries halt after max 
//     count
// 3 - Auto mode On stand engine in presentation mode On stand engine hibernate 
//     disabled On stand charging led state not show On stand scanner turns on 
//     immediately On stand power timers disabled On stand connection retries 
//     forever Off stand does nothing, engine remains in presentation mode Off 
//     stand trigger press causes engine to enter level mode Engine in level 
//     mode battery led state reported Engine in level mode hibernate enabled 
//     Engine in level mode power off timers running Engine in level mode 
//     connection retries halt after max count
enum
{
	kSktScanStandConfigMobileMode=0,
	kSktScanStandConfigStandMode=1,
	kSktScanStandConfigDetectMode=2,
	kSktScanStandConfigAutoMode=3
};

//==========================================================================================================================================================================================================================================================
//			Property ID									ScanAPI?			Data Type for Get							Data Type for Set							Group ID										Internal Prop ID
//==========================================================================================================================================================================================================================================================
// ScanAPI General Properties
#define kSktScanPropIdAbort							(SKTPROPIDSCANAPI(1)|SKTGETTYPE(kSktScanPropTypeNotApplicable)	|SKTSETTYPE(kSktScanPropTypeNone)			|SKTSETGROUPID(kSktScanGroupGeneral)			|SKTSETPROPID(kSktScanIdAbort))
#define kSktScanPropIdVersion						(SKTPROPIDSCANAPI(1)|SKTGETTYPE(kSktScanPropTypeNone)			|SKTSETTYPE(kSktScanPropTypeNotApplicable)	|SKTSETGROUPID(kSktScanGroupGeneral)			|SKTSETPROPID(kSktScanIdVersion))
#define kSktScanPropIdInterfaceVersion				(SKTPROPIDSCANAPI(1)|SKTGETTYPE(kSktScanPropTypeNone)			|SKTSETTYPE(kSktScanPropTypeNotApplicable)	|SKTSETGROUPID(kSktScanGroupGeneral)			|SKTSETPROPID(kSktScanIdInterfaceVersion))
#define kSktScanPropIdConfiguration					(SKTPROPIDSCANAPI(1)|SKTGETTYPE(kSktScanPropTypeString)			|SKTSETTYPE(kSktScanPropTypeString)			|SKTSETGROUPID(kSktScanGroupGeneral)			|SKTSETPROPID(kSktScanIdConfiguration))
#define kSktScanPropIdDataConfirmationMode			(SKTPROPIDSCANAPI(1)|SKTGETTYPE(kSktScanPropTypeNone)			|SKTSETTYPE(kSktScanPropTypeByte)			|SKTSETGROUPID(kSktScanGroupGeneral)			|SKTSETPROPID(kSktScanIdDataConfirmationMode))
#define kSktScanPropIdDataConfirmationAction		(SKTPROPIDSCANAPI(1)|SKTGETTYPE(kSktScanPropTypeNone)			|SKTSETTYPE(kSktScanPropTypeUlong)			|SKTSETGROUPID(kSktScanGroupGeneral)			|SKTSETPROPID(kSktScanIdDataConfirmationAction))
#define kSktScanPropIdMonitorMode					(SKTPROPIDSCANAPI(1)|SKTGETTYPE(kSktScanPropTypeByte)			|SKTSETTYPE(kSktScanPropTypeArray)			|SKTSETGROUPID(kSktScanGroupGeneral)			|SKTSETPROPID(kSktScanIdMonitorMode))
#define kSktScanPropIdSoftScanStatus				(SKTPROPIDSCANAPI(1)|SKTGETTYPE(kSktScanPropTypeNone)			|SKTSETTYPE(kSktScanPropTypeByte)			|SKTSETGROUPID(kSktScanGroupGeneral)			|SKTSETPROPID(kSktScanIdSoftScanStatus))

// ScanAPI Data Editing Properties
#define kSktScanPropIdDataEditingProfile			(SKTPROPIDSCANAPI(1)|SKTGETTYPE(kSktScanPropTypeNone)			|SKTSETTYPE(kSktScanPropTypeString)			|SKTSETGROUPID(kSktScanGroupGeneral)			|SKTSETPROPID(kSktScanIdDataEditingProfile))
#define kSktScanPropIdDataEditingCurrentProfile		(SKTPROPIDSCANAPI(1)|SKTGETTYPE(kSktScanPropTypeNone)			|SKTSETTYPE(kSktScanPropTypeString)			|SKTSETGROUPID(kSktScanGroupGeneral)			|SKTSETPROPID(kSktScanIdDataEditingCurrentProfile))
#define kSktScanPropIdDataEditingTriggerSymbologies	(SKTPROPIDSCANAPI(1)|SKTGETTYPE(kSktScanPropTypeString)			|SKTSETTYPE(kSktScanPropTypeString)			|SKTSETGROUPID(kSktScanGroupGeneral)			|SKTSETPROPID(kSktScanIdDataEditingTriggerSymbologies))
#define kSktScanPropIdDataEditingTriggerMinLength	(SKTPROPIDSCANAPI(1)|SKTGETTYPE(kSktScanPropTypeString)			|SKTSETTYPE(kSktScanPropTypeString)			|SKTSETGROUPID(kSktScanGroupGeneral)			|SKTSETPROPID(kSktScanIdDataEditingTriggerMinLength))
#define kSktScanPropIdDataEditingTriggerMaxLength	(SKTPROPIDSCANAPI(1)|SKTGETTYPE(kSktScanPropTypeString)			|SKTSETTYPE(kSktScanPropTypeString)			|SKTSETGROUPID(kSktScanGroupGeneral)			|SKTSETPROPID(kSktScanIdDataEditingTriggerMaxLength))
#define kSktScanPropIdDataEditingTriggerStartsBy	(SKTPROPIDSCANAPI(1)|SKTGETTYPE(kSktScanPropTypeString)			|SKTSETTYPE(kSktScanPropTypeString)			|SKTSETGROUPID(kSktScanGroupGeneral)			|SKTSETPROPID(kSktScanIdDataEditingTriggerStartsBy))
#define kSktScanPropIdDataEditingTriggerEndsWith	(SKTPROPIDSCANAPI(1)|SKTGETTYPE(kSktScanPropTypeString)			|SKTSETTYPE(kSktScanPropTypeString)			|SKTSETGROUPID(kSktScanGroupGeneral)			|SKTSETPROPID(kSktScanIdDataEditingTriggerEndsWith))
#define kSktScanPropIdDataEditingTriggerContains	(SKTPROPIDSCANAPI(1)|SKTGETTYPE(kSktScanPropTypeString)			|SKTSETTYPE(kSktScanPropTypeString)			|SKTSETGROUPID(kSktScanGroupGeneral)			|SKTSETPROPID(kSktScanIdDataEditingTriggerContains))
#define kSktScanPropIdDataEditingOperation			(SKTPROPIDSCANAPI(1)|SKTGETTYPE(kSktScanPropTypeString)			|SKTSETTYPE(kSktScanPropTypeString)			|SKTSETGROUPID(kSktScanGroupGeneral)			|SKTSETPROPID(kSktScanIdDataEditingOperation))
#define kSktScanPropIdDataEditingImportExport		(SKTPROPIDSCANAPI(1)|SKTGETTYPE(kSktScanPropTypeString)			|SKTSETTYPE(kSktScanPropTypeString)			|SKTSETGROUPID(kSktScanGroupGeneral)			|SKTSETPROPID(kSktScanIdDataEditingImportExport))

// Device General Properties
#define kSktScanPropIdVersionDevice					(SKTPROPIDSCANAPI(0)|SKTGETTYPE(kSktScanPropTypeNone)			|SKTSETTYPE(kSktScanPropTypeNotApplicable)	|SKTSETGROUPID(kSktScanGroupGeneral)			|SKTSETPROPID(kSktScanIdDeviceVersion))
#define kSktScanPropIdDeviceType					(SKTPROPIDSCANAPI(0)|SKTGETTYPE(kSktScanPropTypeNone)			|SKTSETTYPE(kSktScanPropTypeNotApplicable)	|SKTSETGROUPID(kSktScanGroupGeneral)			|SKTSETPROPID(kSktScanIdDeviceType))
#define kSktScanPropIdDeviceSpecific				(SKTPROPIDSCANAPI(0)|SKTGETTYPE(kSktScanPropTypeArray)			|SKTSETTYPE(kSktScanPropTypeArray)			|SKTSETGROUPID(kSktScanGroupGeneral)			|SKTSETPROPID(kSktScanIdDeviceSpecific))
#define kSktScanPropIdSymbologyDevice				(SKTPROPIDSCANAPI(0)|SKTGETTYPE(kSktScanPropTypeSymbology)		|SKTSETTYPE(kSktScanPropTypeSymbology)		|SKTSETGROUPID(kSktScanGroupGeneral)			|SKTSETPROPID(kSktScanIdDeviceSymbology))
#define kSktScanPropIdTriggerDevice					(SKTPROPIDSCANAPI(0)|SKTGETTYPE(kSktScanPropTypeNotApplicable)	|SKTSETTYPE(kSktScanPropTypeByte)			|SKTSETGROUPID(kSktScanGroupGeneral)			|SKTSETPROPID(kSktScanIdDeviceTrigger))
#define kSktScanPropIdApplyConfigDevice				(SKTPROPIDSCANAPI(0)|SKTGETTYPE(kSktScanPropTypeNotApplicable)	|SKTSETTYPE(kSktScanPropTypeNone)			|SKTSETGROUPID(kSktScanGroupGeneral)			|SKTSETPROPID(kSktScanIdDeviceApplyConfig))
#define kSktScanPropIdPreambleDevice				(SKTPROPIDSCANAPI(0)|SKTGETTYPE(kSktScanPropTypeNone)			|SKTSETTYPE(kSktScanPropTypeString)			|SKTSETGROUPID(kSktScanGroupGeneral)			|SKTSETPROPID(kSktScanIdDevicePreamble))
#define kSktScanPropIdPostambleDevice				(SKTPROPIDSCANAPI(0)|SKTGETTYPE(kSktScanPropTypeNone)			|SKTSETTYPE(kSktScanPropTypeString)			|SKTSETGROUPID(kSktScanGroupGeneral)			|SKTSETPROPID(kSktScanIdDevicePostamble))
#define kSktScanPropIdCapabilitiesDevice			(SKTPROPIDSCANAPI(0)|SKTGETTYPE(kSktScanPropTypeByte)			|SKTSETTYPE(kSktScanPropTypeNotApplicable)	|SKTSETGROUPID(kSktScanGroupGeneral)			|SKTSETPROPID(kSktScanIdDeviceCapabilities))
#define kSktScanPropIdChangeIdDevice				(SKTPROPIDSCANAPI(0)|SKTGETTYPE(kSktScanPropTypeNone)			|SKTSETTYPE(kSktScanPropTypeNotApplicable)	|SKTSETGROUPID(kSktScanGroupGeneral)			|SKTSETPROPID(kSktScanIdDeviceChangeId))
#define kSktScanPropIdDataFormatDevice				(SKTPROPIDSCANAPI(0)|SKTGETTYPE(kSktScanPropTypeNone)			|SKTSETTYPE(kSktScanPropTypeByte)			|SKTSETGROUPID(kSktScanGroupGeneral)			|SKTSETPROPID(kSktScanIdDeviceDataFormat))

// Device Local Function Properties
#define kSktScanPropIdFriendlyNameDevice			(SKTPROPIDSCANAPI(0)|SKTGETTYPE(kSktScanPropTypeNone)			|SKTSETTYPE(kSktScanPropTypeString)			|SKTSETGROUPID(kSktScanGroupLocalFunctions)		|SKTSETPROPID(kSktScanIdDeviceFriendlyName))
#define kSktScanPropIdSecurityModeDevice			(SKTPROPIDSCANAPI(0)|SKTGETTYPE(kSktScanPropTypeNone)			|SKTSETTYPE(kSktScanPropTypeByte)			|SKTSETGROUPID(kSktScanGroupLocalFunctions)		|SKTSETPROPID(kSktScanIdDeviceSecurityMode))
#define kSktScanPropIdPinCodeDevice					(SKTPROPIDSCANAPI(0)|SKTGETTYPE(kSktScanPropTypeNotApplicable)	|SKTSETTYPE(kSktScanPropTypeString)			|SKTSETGROUPID(kSktScanGroupLocalFunctions)		|SKTSETPROPID(kSktScanIdDevicePinCode))
#define kSktScanPropIdDeletePairingBondingDevice	(SKTPROPIDSCANAPI(0)|SKTGETTYPE(kSktScanPropTypeNotApplicable)	|SKTSETTYPE(kSktScanPropTypeByte)			|SKTSETGROUPID(kSktScanGroupLocalFunctions)		|SKTSETPROPID(kSktScanIdDeviceDeletePairingBonding))
#define kSktScanPropIdRestoreFactoryDefaultsDevice	(SKTPROPIDSCANAPI(0)|SKTGETTYPE(kSktScanPropTypeNotApplicable)	|SKTSETTYPE(kSktScanPropTypeNone)			|SKTSETGROUPID(kSktScanGroupLocalFunctions)		|SKTSETPROPID(kSktScanIdDeviceRestoreFactoryDefaults))
#define kSktScanPropIdSetPowerOffDevice				(SKTPROPIDSCANAPI(0)|SKTGETTYPE(kSktScanPropTypeNotApplicable)	|SKTSETTYPE(kSktScanPropTypeNone)			|SKTSETGROUPID(kSktScanGroupLocalFunctions)		|SKTSETPROPID(kSktScanIdDeviceSetPowerOff))
#define kSktScanPropIdButtonsStatusDevice			(SKTPROPIDSCANAPI(0)|SKTGETTYPE(kSktScanPropTypeNone)			|SKTSETTYPE(kSktScanPropTypeNotApplicable)	|SKTSETGROUPID(kSktScanGroupLocalFunctions)		|SKTSETPROPID(kSktScanIdDeviceButtonsStatus))
#define kSktScanPropIdSoundConfigDevice				(SKTPROPIDSCANAPI(0)|SKTGETTYPE(kSktScanPropTypeByte)			|SKTSETTYPE(kSktScanPropTypeArray)			|SKTSETGROUPID(kSktScanGroupLocalFunctions)		|SKTSETPROPID(kSktScanIdDeviceSoundConfig))
#define kSktScanPropIdTimersDevice					(SKTPROPIDSCANAPI(0)|SKTGETTYPE(kSktScanPropTypeNone)			|SKTSETTYPE(kSktScanPropTypeArray)			|SKTSETGROUPID(kSktScanGroupLocalFunctions)		|SKTSETPROPID(kSktScanIdDeviceTimers))
#define kSktScanPropIdLocalAcknowledgmentDevice		(SKTPROPIDSCANAPI(0)|SKTGETTYPE(kSktScanPropTypeNone)			|SKTSETTYPE(kSktScanPropTypeByte)			|SKTSETGROUPID(kSktScanGroupLocalFunctions)		|SKTSETPROPID(kSktScanIdDeviceLocalAcknowledgement))
#define kSktScanPropIdDataConfirmationDevice		(SKTPROPIDSCANAPI(0)|SKTGETTYPE(kSktScanPropTypeNotApplicable)	|SKTSETTYPE(kSktScanPropTypeUlong)			|SKTSETGROUPID(kSktScanGroupLocalFunctions)		|SKTSETPROPID(kSktScanIdDeviceDataConfirmation))
#define kSktScanPropIdBatteryLevelDevice			(SKTPROPIDSCANAPI(0)|SKTGETTYPE(kSktScanPropTypeNone)			|SKTSETTYPE(kSktScanPropTypeNotApplicable)	|SKTSETGROUPID(kSktScanGroupLocalFunctions)		|SKTSETPROPID(kSktScanIdDeviceBatteryLevel))
#define kSktScanPropIdLocalDecodeActionDevice		(SKTPROPIDSCANAPI(0)|SKTGETTYPE(kSktScanPropTypeNone)			|SKTSETTYPE(kSktScanPropTypeByte)			|SKTSETGROUPID(kSktScanGroupLocalFunctions)		|SKTSETPROPID(kSktScanIdDeviceLocalDecodeAction))
#define kSktScanPropIdBluetoothAddressDevice		(SKTPROPIDSCANAPI(0)|SKTGETTYPE(kSktScanPropTypeNone)			|SKTSETTYPE(kSktScanPropTypeNotApplicable)	|SKTSETGROUPID(kSktScanGroupLocalFunctions)		|SKTSETPROPID(kSktScanIdDeviceBluetoothAddress))
#define kSktScanPropIdStatisticCountersDevice		(SKTPROPIDSCANAPI(0)|SKTGETTYPE(kSktScanPropTypeNone)			|SKTSETTYPE(kSktScanPropTypeNotApplicable)	|SKTSETGROUPID(kSktScanGroupLocalFunctions)		|SKTSETPROPID(kSktScanIdDeviceStatisticCounters))
#define kSktScanPropIdRumbleConfigDevice			(SKTPROPIDSCANAPI(0)|SKTGETTYPE(kSktScanPropTypeByte)			|SKTSETTYPE(kSktScanPropTypeArray)			|SKTSETGROUPID(kSktScanGroupLocalFunctions)		|SKTSETPROPID(kSktScanIdDeviceRumbleConfig))
#define kSktScanPropIdProfileConfigDevice			(SKTPROPIDSCANAPI(0)|SKTGETTYPE(kSktScanPropTypeNone)			|SKTSETTYPE(kSktScanPropTypeArray)			|SKTSETGROUPID(kSktScanGroupLocalFunctions)		|SKTSETPROPID(kSktScanIdDeviceProfileConfig))
#define kSktScanPropIdDisconnectDevice				(SKTPROPIDSCANAPI(0)|SKTGETTYPE(kSktScanPropTypeNotApplicable)	|SKTSETTYPE(kSktScanPropTypeByte)			|SKTSETGROUPID(kSktScanGroupLocalFunctions)		|SKTSETPROPID(kSktScanIdDeviceDisconnect))
#define kSktScanPropIdDataStoreDevice				(SKTPROPIDSCANAPI(0)|SKTGETTYPE(kSktScanPropTypeArray)			|SKTSETTYPE(kSktScanPropTypeArray)			|SKTSETGROUPID(kSktScanGroupLocalFunctions)		|SKTSETPROPID(kSktScanIdDeviceDataStore))
#define kSktScanPropIdNotificationsDevice			(SKTPROPIDSCANAPI(0)|SKTGETTYPE(kSktScanPropTypeNone)			|SKTSETTYPE(kSktScanPropTypeUlong)			|SKTSETGROUPID(kSktScanGroupLocalFunctions)		|SKTSETPROPID(kSktScanIdDeviceNotifications))
#define kSktScanPropIdConnectReasonDevice			(SKTPROPIDSCANAPI(0)|SKTGETTYPE(kSktScanPropTypeNone)			|SKTSETTYPE(kSktScanPropTypeNotApplicable)	|SKTSETGROUPID(kSktScanGroupLocalFunctions)		|SKTSETPROPID(kSktScanIdDeviceConnectReason))
#define kSktScanPropIdPowerStateDevice				(SKTPROPIDSCANAPI(0)|SKTGETTYPE(kSktScanPropTypeNone)			|SKTSETTYPE(kSktScanPropTypeNotApplicable)	|SKTSETGROUPID(kSktScanGroupLocalFunctions)		|SKTSETPROPID(kSktScanIdDevicePowerState))
#define kSktScanPropIdStartUpRoleSPPDevice			(SKTPROPIDSCANAPI(0)|SKTGETTYPE(kSktScanPropTypeNone)			|SKTSETTYPE(kSktScanPropTypeByte)			|SKTSETGROUPID(kSktScanGroupLocalFunctions)		|SKTSETPROPID(kSktScanIdDeviceStartUpRoleSPP))
#define kSktScanPropIdConnectionBeepConfigDevice	(SKTPROPIDSCANAPI(0)|SKTGETTYPE(kSktScanPropTypeNone)			|SKTSETTYPE(kSktScanPropTypeByte)			|SKTSETGROUPID(kSktScanGroupLocalFunctions)		|SKTSETPROPID(kSktScanIdDeviceConnectionBeepConfig))
#define kSktScanPropIdFlashDevice					(SKTPROPIDSCANAPI(0)|SKTGETTYPE(kSktScanPropTypeNone)			|SKTSETTYPE(kSktScanPropTypeByte)			|SKTSETGROUPID(kSktScanGroupLocalFunctions)		|SKTSETPROPID(kSktScanIdDeviceFlash))
#define kSktScanPropIdOverlayViewDevice				(SKTPROPIDSCANAPI(0)|SKTGETTYPE(kSktScanPropTypeNone)			|SKTSETTYPE(kSktScanPropTypeObject)			|SKTSETGROUPID(kSktScanGroupLocalFunctions)		|SKTSETPROPID(kSktScanIdDeviceOverlayView))
#define kSktScanPropIdStandConfigDevice				(SKTPROPIDSCANAPI(0)|SKTGETTYPE(kSktScanPropTypeNone)			|SKTSETTYPE(kSktScanPropTypeUlong)			|SKTSETGROUPID(kSktScanGroupLocalFunctions)		|SKTSETPROPID(kSktScanIdDeviceStandConfig))


#endif //_SktScanPropIds_h
