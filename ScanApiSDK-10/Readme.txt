================================================================================

                      ScanAPI SDK Version 10.2.227


                            Socket Mobile, Inc.
                           www.socketmobile.com

               © Copyright 2015 all rights reserved worldwide
================================================================================


Content
1) Quick install notes
2) Sample code
3) Introduction
4) Content description
5) ScanAPI usage
6) SoftScan since iOS 7.0
7) Developers Warranty Extension Program
Appendix A. Changes log

1. Quick install notes
----------------------

In this release of the SDK we moved away from the drag and drop
installation and fully embraced the dependency management offered by CocoaPods.

Since ScanAPI SDK is still a download from our developer portal, a few things
are required in order to install this ScanAPI CocoaPods in your machine and
project.

First, you need to install CocoaPods on your machine by following the
instructions found here: https://guides.cocoapods.org/using/getting-started.html

Then you need to create a file named Podfile' in the same folder as your Xcode
project is located.
The content of this file should be something like:
        xcodeproj 'myProject.xcodeproj'
         pod 'ScanAPI', :path => '../ScanApiSDK-10.2.195'

The path for pod 'ScanAPI' should be where you have extracted the zip file.
Once you have saved this file, from the terminal command prompt, type the
command 'pod install' and make sure your current directory is where the Podfile
is.

This creates a workspace file. If you have Xcode open on your project, you need
to close it, and open your project workspace file.

From there you should be able to compile without error.

Now you're ready to add #import 'ScanApiHelper.h' in your main controller, and
make it derive from <ScanApiHelperDelegate>.
Go to the ScanApiHelperDelegate source and copy paste the delegate you want to
override, at minimum the onDecodedDataResult delegate in order to be able to
receive the barcode decoded data in your application.

Last but not least, make sure to add the string 'com.socketmobile.chs' in the
'Supported external accessory protocols' through the project Info properties.

IMPORTANT NOTES ABOUT THIS RELEASE:
1- the API has changed a little since our last release. We have replaced the
protocol objects by an interface. So if your code has some reference to them
they should be replaced as follows:
<ISktScanObject>      =>   ISktScanObject*
<ISktScanProperty>    =>   ISktScanProperty*
<ISktScanDevice>      =>   ISktScanDevice*
<ISktScanSymbology>   =>   ISktScanSymbology*
<ISktScanDecodedData> =>   ISktScanDecodedData*

2- If the application used only libScanApi.a, this library has been renamed
to libScanApiCore.a. So the header files, and the library is still accessible if
you wish to not use CocoaPods at all.

2. Sample code
--------------
Sample code can be found on GitHub / SocketMobile.

3. Introduction
---------------

This SDK is designed for using all of the Socket CHS 7 and 8 Series Scanners
on the iOS platforms. The intended usage is to develop a native iOS application
that includes built in support for the Socket CHS 7/8 canners. As the
application developer this SDK will give you full programmatic access to a
connected CHS scanner to customize the scanner Symbology, data support and
manage scanner feedback messages and functions.  The API document for the SDK
can be found on the Socket Developer portal at:
http://www.socketmobile.com/developers/welcome
Click the login, the on the right side click on the downloads link and the
API document is the first one in the list.


The following are Socket CHS models/revisions that are compatible with
SocketScan 10 SDK for iOS:

		 CHS 7Xi: 8550-00059, Revisions A, B and C
		 CHS 7XiRx: 8550-00060, Revisions A, B and C
		 CHS 7Ci: All
		 CHS 7Pi: All
		 CHS 7Mi: All
		 CHS 7Qi: All
		 CHS 8Ci: All
		 CHS 8Qi: All

Note: The CRS Series 9 Ring Scanner is NOT supported.


The CHS scanners are shipped by default in HID profile mode and will display the
following friendly name on iOS platform devices in the Bluetooth manager:
For the 7Xi and 7Qi:
Socket 7Xi [xxxxxx] (where x’s are the last 6 digits of the BD address of the
scanner)
OR for the 7Ci/7Mi/7Pi, 8Ci, 8Qi:
Socket CHS [xxxxxx]
In this mode the scanner will function as a standard HID keyboard device and you
can test with the scanner in this mode utilizing the HID keyboard mode.

***Please note that if you discover and test with the scanner in HID mode that
it may cause conflicts with discovering and using the scanner in iOS mode due to
the fact that the iOS device will cache the name and service information of the
device. If you setup the scanner in HID mode Socket recommends that you remove
the pairing information stored in the iOS device by removing the HID discovered
device in the Bluetooth settings by selecting “forget this device” AND
completely closing out the settings applet by returning to your home screen and
shut down the settings applet using the iOS multi-task panel.***


To setup the scanner in iOS mode and be able to communicate with an application
using our ScanAPI functions the scanner will need to scan an iOS programming
barcode. This barcode is included in the last page of the included quick start
guide or you can create your own physical DataMatrix barcode for the 7Xi or Code
128 1D linear barcode for the 7Ci with the following data:
For the 7Xi/Qi: #FNC IOS ACCEPTOR 000000000000#
For all others (1D scanners and 8Qi): #FNB00F40002#

The 2D barcode is also in the source of the ScannerSettings app and can be
reused in your developer application. As the developer you must define the best
method on how to present this setup barcode for the user.
Once the scanner has been programmed in iOS mode the scanner will display the
following friendly name on iOS platform devices in the Bluetooth manager:
For the 7Xi and 7Qi:
Socket 7Xi [xxxxxx]
For the all of the 1D scanners and 8Qi, the name will follow this friendly name
convention at all times:
Socket CHS [xxxxxx]

The scanner LED will blink 1 time a second to indicate it is discoverable and
ready to be paired. After 2 mins the scanner will emit a long beep tone to
indicate that it is no longer discoverable. You can re-enable the scanner to be
discoverable by simply pressing the Scan or Power button on the scanner for the
7Xi/Qi. For the 1D scanners (7Ci/Mi/Pi,8Ci, 8Qi) you will need to power cycle
the scanner to initiate the 2 minute discovery period.

Once you have setup the scanner you can discover and pair to the CHS scanner
using the Bluetooth manager in the iOS device by tapping on the
settings--General--Bluetooth.

Verify that Bluetooth is on. Wait for the device to discover the scanner and
verify the correct friendly name. Once the scanner appears tap on the device to
complete the pairing process. Once the pairing is complete the iOS device will
automatically initiate a connection and the scanner will remain permanently
paired and connected to the iOS device as an available Bluetooth IAP accessory
to communicate with in your app.  The scanner Led will blink 1 time every 3
seconds to indicate a connection to the iOS device.

If you need to clear the pairing information in order to connect with another
iOS device you will need to manually clear the pairing from BOTH the scanner and
the connected iOS device.

From the scanner verify the scanner is powered on and connected and hold down
the large trigger button while powering off the scanner. You will hear a 3 tone
sequence to let you know the pairing information has been cleared.

From the iOS device select the Socket 7Xi or Socket CHS device and tap on
“Forget this device” to remove the pairing. You are now free to use the scanner
with another device or setup the same connection to the existing device.


SUMMARY

For ALL user scenarios with the CHS scanners and any sample app or developed
application with ScanAPI support these steps MUST occur in order to be able to
connect and communicate with the scanner:

1. Setup the CHS scanner in iOS mode
2. Discover the CHS scanner in the Bluetooth manager of the iOS device
3. Pair with the CHS scanner in the Bluetooth manager of the iOS device
4. Verify Bluetooth connected state between the iOS device and 7Xi or 7Ci
scanner

4. Content description
----------------------

This SDK is release as a simple zip file with the version,
ie: ScanApiSDK-10.2.195.zip.

The content at the root of the SDK contains the source file for ScanApiHelper,
a wav file for SoftScan feature, the podspec file descriptor, the license file,
and this Readme file.
There are 2 sub-folders: include and lib. Include folder contains all the header
files of ScanAPI, and the lib folder contains the libScanApiCore.a file which is
the main ScanAPI library.

5. ScanAPI usage
----------------

The ScanAPI is described in greater detail in the ScanAPI.pdf document.
A brief description follows.

The recommended way of using ScanAPI is by using ScanApiHelper.

ScanApiHelper can be instantiated in one of your application controllers.
The chosen controller must implement the ScanApiHelperDelegate protocol in order
to receive the various ScanAPI asynchronous events.

A timer or a thread should be created in order to receive these asynchronous
event by simply calling ScanApiHelper doScanApiReceive.

NOTE: A shared feature is available in ScanApiHelper allowing to instantiate the
main instance in the main controller of the application, and have a reference to
it in any sub-view controller by maintaining a stack of ScanApiHelper delegates.
The main controller has a timer set to consume periodically the events coming
from ScanApi.
When a sub-view requiring barcode scanning becomes active, it push its delegate
reference. Then that view receive a device arrival indicating the presence of a
scanner connected on the host. It receives the decoded data directly through the
usual onResultDecodedData delegate of this view. That view does not need to open
or close ScanApiHelper since it is already done in the application main
controller and it does not need to setup a timer as it is already done in the
main controller. When the view becomes inactive, then the popDelegate remove the
view delegate and the previous delegate in the stack becomes active. Whatever
view that is, it receives the device arrival notification.

Summary for Integrating ScanAPI in Xcode application is now a simple 9 steps
process after drag and drop of the ScanAPI folder into your Xcode project:

1. Add "com.socketmobile.chs" in Supported external accessory protocols in your
application info.plist

2. Add 'pod "ScanAPI", ":path => <path where the ScanAPI CocoaPods has been extracted>"'
in the file Podfile located at the same level than the application .xcproj file.
Make sure this file first line is giving the name of the application .xcproj
file:
'xcodeproj "myProject.xcproj" '

3. Install ScanAPI CocoaPods in the project by using the terminal and typing the
following command: 'pod install' in the project's directory. Once the
installation completes, use the application workspace in order to compile it
with ScanAPI.

4. Import "ScanApiHelper.h" in your application main controller

5. Add ScanApiHelper and a ScanApi Consumer NSTimer properties in the same
controller

6. Derive your application main controller from the ScanApiHelperDelegate
protocol

7. In the appropriate controller function initializes ScanApiHelper, by using
the setDelegate to specify your controller reference, by calling ScanApiHelper
open method to start initializing ScanAPI and by starting your NSTimer ScanApi
consumer.

8. The onTimer of ScanApi consumer calls ScanApiHelper doScanApiReceive method.

9. Add the implementation of the ScanApiDelegate protocol from which the
controller derived to handle the various ScanAPI asynchronous events.


ScanApiHelper makes the application aware of a new scanner connection by
invoking the onDeviceArrival of the protocol and in the same way when a scanner
disconnects, the onDeviceRemoval is invoked.

If the scanner triggers a scan, the decoded data can be retrieve in the protocol
function onResultDecodedData.

The application can retrieve or modify the scanner properties by calling the
various ScanApiHelper postGetxxx or postSetxxx method. By example there is a
method to retrieve the scanner friendly name: postGetFriendlyName.

If a property in not accessible through the available ScanApiHelper methods, it
is very easy to add new ones, by copy and paste a similar postGetxxx or
postSetxxx method and change the property settings inside the new method.

Each postGetxx or postSetxxx has a selector parameter that can be used to
display a specific error message if an error occurs, or to refresh the UI with
the property value retrieved.

6. SoftScan since iOS7.0
------------------------

SoftScan feature is the capability of using the phone's camera in order to scan
a barcode.
The SoftScan feature is implemented using the built-in SoftScan of iOS since
iOS7.
The main purpose of integrating this feature in ScanAPI is to provide a
consistent interface to barcode readers. Whatever it is a Socket Cordless
Handled Scanner, or simply the phone's camera, the application relies on the
same interface.

The application using the SoftScan feature needs to do 2 things differently than
that Socket Handled Scanners don't require.

The first thing is to register the application main UI view to ScanAPI so the
camera overlay view can be displayed correctly by passing the UI application
reference to the overlay property (kSktScanPropIdOverlayViewDevice).

The second thing is to provide a trigger logic that starts the SoftScan scanning
operation. The trigger is a ScanAPI property (kSktScanPropIdTriggerDevice) that
exists since the first version of ScanAPI, whereas the overlay view property has
been added to support SoftScan feature.

A third property (kSktScanPropIdSoftScanStatus) allows to enable or disable the
SoftScan feature. This is a ScanAPI property that is persistent across the life
cycle of the application using it.

If the SoftScan feature is enabled, ScanAPI will send a device arrival
notification to the application referencing a SoftScan device the application
can control.
Once the application trigger a scan, the decoded data arrives the same way with
the same information than as any other scanners supported by ScanAPI.

To integrate ScanAPI with SoftScan feature in an application, just Drag and Drop
the "ScanAPI" folder of the SDK into the application Xcode project. Only this
folder is needed.

The application must be linked with the following frameworks:
ExternalAccessory.framework
UIKit.framework
Foundation.framework
AVFoundation.framework
AudioToolbox.framework

NOTE: The SoftScan feature is only supported on iOS7.0 and higher. If the
application is running on older version than iOS7.0 and tries to turn on
SoftScan by using the property kSktScanPropIdSoftScanStatus, an
ESKT_NOTSUPPORTED error is returned.

7. Developers Warranty Extension Program
----------------------------------

Socket offers an optional program where developers can integrate a scanner
registration component in their application that will track the registration of
purchased scanner that are used with their application. These registrations are
tracked by Socket which then rewards the END USER with a 1 year extension to
their existing warranty. More information can be found on our website here:

http://www.socketmobile.com/docs/default-source/software-development-kits-(sdks)/socketscan-developer-program-info-packet.pdf

The DCP registration requirements can also be found in the sdk doc folder.

Appendix A. Changes log
-----------------------
Change from the version 10.2.223
* compiled against iOS 9.1 SDK

Change from the version 10.2.221
* fix the SoftScan scanner version

Change from the version 10.2.119
* fix a crash detected while turning Guard Malloc on
* fix a crash when using shared ScanApiHelper feature and not providing
a device Arrival delegate

Change from the version 10.1.12647
* move ScanAPI to CocoaPods
* compile against the iOS8.4 SDK
* Remove protocol objects to be replaced by interface to provide better
  support for Xamarin.

Change from the version 10.1.12604
* add an error code ESKT_CANCEL used when end user cancels SoftScan
* add iOS ScanApiHelper onDecodedDataResult that has a Result field
that might be set to ESKT_CANCEL when the end-user cancels SoftScan

Change from the version 10.1.12451
* add workaround for a External Accessory deadlock occurring in iOS7.1.2

Change from the version 10.0.10.12120
* better handling of iOS sleep while scanner connected
* device cache for faster reconnection especially for 7Ci series

Change from the version 10.0.10.12018
* Combine all processor and SoftScan in one ScanAPI supporting version iOS6 and
up.
(SoftScan status returns "not supported" on iOS version lower than 7.0)

Change from the version 10.0.10.11437
* Replace RedLaser SoftScan by native iOS7.0 SoftScan
* New Warranty Checker in SDK Sample applications
* Added support for 7Qi
* Remove (deprecate) ScannerRegistrationLib
* Replace beep.wav by softScanBeep.wav in the SDK
* Added Socket Scanner Registration API.pdf document
* Add GetDeviceInfoFromHandle method in ScanApiHelper
* Add SktProfile.h was missing in the previous release of the SDK
* Add error ESKT_OVERLAYVIEWNOTSET error if overlay view is not set prior
triggering Soft Scanner
* Add SoftScan in the SDK Sample App SingleEntry
* Clean up Symbology name mapping
* Update data editing so special xml chars can be in data values
* Fix data editing to allow empty profile
* Fix crash in data editing for setprofile property
* Fix 8Ci so correct statistics data is mapped


Change from the version 10.0.10.11241
* Fix a memory leak

Change from the version 10.0.10.11228
* Fix 2 warnings in ScanApiHelper code when compiling for arm64.
* Fix the Scanner Registration library 64 build that was missing in the
architecture setting.
* Fix the ScanAPI 64 build that was missing a generic transport class.

Change from the version 10.0.10.11663
* Compiled with the official release of Xcode 5
* Separate the ARM64 SDK from the Normal SDK
* ARM64 SDK for iOS7 and higher
* Normal SDK for iOS6.0 and higher

Change from the version 10.0.10.10997
* Add iOS7 support
* Temporary removal of RedLaser support for SoftScan
* Fix a Lock not working correctly by using a Recursive Mutex

Changes from the version 10.0.9.10686
* Add Data Editing (version 10.0.10 and higher).
* Add new device type for the 8Ci scanner.
* Change in ScanApiHelper to set the flag connected before onDeviceArrival is
invoked.
* Fix mapping of Sound and Rumble Config. Data Confirmation is now consistent
across scanners models.

Changes from the version 10.0.9.10547
* Remove the Debug messages from the release build. (They weren't
displayed but they took some code space for nothing.)
* Fix a crash occurring when the scanner (7Ci or 7Xi) can't be initialized
because it is too busy decoding data.
* Add a force Accessory Monitor check connected accessories list in case
the monitor doesn't receive the External Accessory notification callback.

Changes from the version 10.0.9.10132
* Fix the documentation about the Trigger lockout timer
* Fix a minor memory leaks in some properties

Changes from the version 10.0.9.10094
* Fix the error -21 occurring too often
	- Bluetooth Helper data member not initialized correctly
	- Packet Repeat detection, that are now discarded correctly

Changes from the version 10.0.9.10029
* Increase the number of connection retries from 2 to 20.

Changes from the version 10.0.9.9996
* Improvements in External Accessory detections
* Full support of multi bluetooth scanners.

Changes from the version 10.0.9.9606
* Add support for iOS6.0
* Project settings updated to support 4.3 emulator

Changes from the version 10.0.9.9388
* Add the armv7s settings of ScanAPI RedLaser
* Add the Factory Reset barcodes for 1D scanner and 2D scanner
* Add the iOS Mode for 1D scanner

Changes from the version 10.0.9.9380
* Add the Default launch images for ScannerSettings.
* Fix the Project settings for ScannerSettings for compiling for iOS4.3 or
higher.

Changes from the version 10.0.9.9339
* Add iOS6 support to compile with Xcode 4.5.
* Fix a bug in the platform name reported during the Scanner Registration.
* SoftScan Version reported correctly using RedLaser Version API.
* Updated RedLaser SDK version 3.3.1

Changes from the version 10.0.9.8985
* Bug fixes regarding SoftScan scanner.

Changes from the version 10.0.8.8064
* Adding SoftScan feature using RedLaser SDK version 3.3.0.154 2012/04/12.

Changes from the version 10.0.8.8002
* Fix the Device Specific (pass-through) for 7Xi, the length returned was short
of 2 bytes preventing to read the response value of a scanner specific
parameter.

Changes from the version 10.0.8.7841
* Add a small (500ms) delay before sending the initialization commands to the
scanner when it connects. This corrected an issue where the 7Ci and 7Xi scanner
would reconnect too quickly to the iOS device before the scanner was ready to
send or receive data.

* Add the Data Store support for 7Ci. See section 12.3 Property
kSktScanPropIdDeviceSpecific for more details.

* Updates to the ScanAPI document

Changes from the version 10.0.8.7683
* Fix a missing Scan event, when rapidly scans occurs.

Changes from the version 10.0.4.7534
* Add support for 1D Scanner 7Ci which is version 10.0.8 of ScanAPI.

Changes from the version 10.0.4.7492
* Fix the first scan (after 3mins or more of inactivity) of a multi frames
barcode, where it got discarded because of a retry of the first frame that
removed the current state.
This issue concerns mostly barcode bigger than173 characters.

Changes from the version 10.0.4.7240
* Fix the 174 characters barcode that was silently discarded.
* Add the SingleEntry sample App

Changes from the version 10.0.4.7225
* Add a new ScanAPI folder for an easier integration
in an Xcode project by doing just a Drag and Drop

Changes from the version 10.0.4.7200
* fix the build script to build ScanAPI and ScannerRegistration for all
the supported architecture

Changes from the version 10.0.4.7092
* add the preprocessor #if for compiling ScanApiHelper either
in ARC project or in no ARC project.
* rename the ScanApiHelper implementation file to ScanApiHelper.mm from
ScanApiHelper.m
* fix few compiler errors while compiling with an ARC mode project.

Changes from the version 10.0.4.7088
* fix the revision number in ScanAPI version that wasn't always updated
correctly.

Changes from the version 10.0.4.7054
* fix the 100% CPU utilization when no scanner connected, by adding
a timer to the current loop.

Changes from the version 10.0.4.7043
* Drain the auto release memory pool used in the listener thread
to avoid increasing memory usage while ScanAPI is open.

Changes from the version 10.0.4.6868
* Fix some warnings and update to Xcode 4.2

* Fix a memory leaks appearing only when closing ScanAPI

* Fix a crash when the scanner disconnects after closing ScanAPI

Changes from the version 10.0.4.6429

* Fix progress bar issue in ScannerSettings that was
broken when writting the settings to the scanner

* Add the Scanner Registration library with source code

* Add the Scanner Registration documentation
