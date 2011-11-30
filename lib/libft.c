/** @file
 *
 * Copyright (C) 2007 Erik Andresen erik@vontaene.de
 *
 * Open Source version of the fischertechnik ROBO Interface Library for Unix like systems
 *
 * Communication is done through a "transfer area" this is constantly updated.
 *
 * This library is free software; you can redistribute it and/or
 * modify it under the terms of the GNU Lesser General Public
 * License as published by the Free Software Foundation; either
 * version 2.1 of the License, or (at your option) any later version.
 *
 * This library is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU
 * Lesser General Public License for more details.
 *
 * You should have received a copy of the GNU Lesser General Public
 * License along with this library; if not, write to the Free Software
 * Foundation, Inc., 51 Franklin Street, Fifth Floor, Boston, MA  02110-1301  USA
 *
 */

/**
 * \example example.c
 *
 * \mainpage libft Index Page
 *
 * \section intro_sec Introduction
 *
 * libft is an Open Source version of the fischertechnik ROBO Interface Library for Unix like systems
 *
 * The goal is to create a library that is fully compatible with the ftlib by knobloch eletronic.
 * 
 * This library should work on any systems supported by libusb, like Linux, BSD and Mac OS X and is released
 * under the GNU Lesser General Public License (LGPL)
 * 
 * Included is the helper program "ftuploader" which allows you to upload programs to the Robo Interface.\n
 * Running ftuploader --help should give you an idea how to use it.\n
 * Also included is an Interface Diagnose utility. See section Interface Diagnose
 *
 * \section dl_sec Download
 * Current Version: 0.4.4
 *
 * See http://defiant.homedns.org/~erik/ft/libft/files/ \n
 * Download Latest version: http://defiant.homedns.org/~erik/ft/libft/files/libft-current.tar.gz
 *
 * \section req_sec Requirements
 * - libusb - http://libusb.sourceforge.net/
 * - cmake at least version 2.4 - http://cmake.org
 * - pthreads (Should be included with every modern posix compatible OS)
 *
 *
 * \section apidoc_sec API Documentation
 * \see libft.c
 *
 * \section install_sec Installation
 *
 * \subsection step1 Step 1: Compiling
 *
 * Type
 * - cmake .
 * - make
 * \subsection step2 Step 2: Installation
 * Type
 * - make install
 *
 * After installing you should run
 * - ldconfig
 *
 * to make the library known to your system. Make sure that /etc/ld.so.conf is configured to include /usr/local/li
 *
 * To install the diagnose utility type
 * - make diag
 * 
 * Debian packages are available. Please read http://vontaene.de/apt/README.txt\n
 * You can install them with apt-get install libft0 libft-doc libft-python libft-diag
 *
 * \subsection step3 Step 3: udev
 * When running udev you might want to copy the file fischertechnik.rules from the udev folder to /etc/udev/rules.d/ to get the correct permissions.\n
 * Udev then needs a reload with
 * - udevcontrol reload_rules
 *
 * You will now need to replug your device.
 *
 * \subsection step4 Step 4: Create Documentation\n
 * Type\n
 * - make doc\n
 * to create the html API documentation.
 *
 * \subsection step5 Step 5: Python
 * A Python interface to this library is available, see the python folder for details.\n
 * Type\n
 * make python\n
 *
 * in the python/ -folder to install the python module.
 * Use pydoc to read its documentation:
 * - pydoc robointerface in the shell
 * - help(robointerface) from the python interpreter
 *
 * \section diag_sec Interface Diagnose 
 * You can find it in the folder diag/.\n
 * It requires the python module (see above) and PyQT4. You can launch it by running "python ftdiagnose"
 * \image html diag1.png
 *
 * \section author_sec Author
 * Erik Andresen - erik@vontaene.de
 * 
 * Please contact me for bugs or any suggestions
 *
 * Homepage of libft: http://defiant.homedns.org/~erik/ft/libft/
 *
 *
 * \section changes_sec Changes
 * 
 * - 0.4.4:	- Some Bug fixes, fixes to work with Fedora 14
 * - 0.4.3:	- Bug fix: Extension digital inputs at RoboRF
 *		- ftdiagnose: Display connection status
 *		- Added functions: (not in Knobloch lib):
 *			- IsFtInterfaceConnected()
 *		- Python added functions:
 *			- IsConnected()
 * - 0.4.2:	- Python support to open the interface by serial
 *		- Some Bug fixes
 * 		- Added functions: (not in Knobloch lib)
 *	 		- SetRealSerial()
 * - 0.4.1:
 *   		- Added support to change the RF address.
 * 		- Added functions: (not in Knobloch lib)
 *	 		- SetRFMode()
 * 			- GetRFMode()
 * 		- Added support for functions:
 * 			- GetFtManufacturerStrg()
 * 			- GetFtShortNameStrg()
 * 			- GetFtLongNameStrg()
 * 			- GetFtLibErrorString()
 *	 	- Some minor Bug fixes
 * - 0.4:
 *   		- Hopefully support for more then one Robo Interface attached to an RF Link.
 * 			- InitFtUsbDeviceList() will now also count the number of Robo Interfaces attached to an RF Link
 * 		- Added support for the ft distance sensor
 * 		- Added functions:
 * 			- GetFtDeviceTypeString() (not in Knobloch lib)
 * 		- Added support for functions:
 * 			- SetFtDistanceSensorMode()
 * 		- Python added functions:
 * 			- GetNumFtUsbDevices()
 * 			- RoboInterface.GetDeviceTypeString()
 * 			- GetD1()
 * 			- GetD2()
 * 		- Added ft Diagnose utility.
 * - 0.3:	
 *   		- added (overwrite) --target option to the ftuploader
 * 		- included some documentation
 * 		- minor fixes
 * 		- enhanced python layer
 * 		- support for RF Module
 * - 0.2.1:	
 *   		- fixed Analog/Voltage Sensor calculations
 * - 0.2:	
 *   		- added udev file
 * 		- experimental support for uploading to the interface (usb only)
 * 		- included program ftuploader
 * 		- add support for functions:
 * 			- DownloadFtProgram()
 * 			- StartFtProgram()   
 * 			- StopFtProgram()    
 * 			- DeleteFtProgram()  
 * 			- SetFtProgramActiv()
 * 			- GetFtProgramName() 
 * 			- GetFtStatus()      
 * 			- GetFtFirmware()    
 * 			- GetFtFirmwareStrg()
 * 			- GetFtSerialNr()    
 * 			- GetFtSerialNrStrg()
 * 
 *
 * \section porting_sec Porting your program from the Knobloch Windows Library
 * When porting your program from the Knobloch Library for Microsoft Windows operation systems please note the following:
 * - The name of this library is libft, not ftlib (the Knobloch original) to follow the UNIX naming scheme
 * - Types like DWORD are replaced with their logical ANSI-C counterparts, like
 *   -# DWORD - long int
 *   -# LPCSTR - char *
 *   -# LPVOID - void *
 *   -# BYTE - unsigned char
 *   -# USHORT - unsigned short int
 *   -# UINT - unsigned int
 *   -# UCHAR - unsigned char
 * - The Windows Notifications stuff will probably never be supported.
 * - Some return codes might be different, so if something is going wrong, check this manual.
 *  
 */

#include <stdio.h>
#include <string.h>
#include <pthread.h>
#include <semaphore.h>
#include <termios.h>
#include <fcntl.h>
#include <usb.h>
#include "crc.h"
#include "ftlib.h"

/** \cond doxygen ignore start */
#define VERSION_MAJOR LIBFT_VERSION_MAJOR
#define VERSION_MINOR LIBFT_VERSION_MINOR
#define VERSION_PATCH LIBFT_VERSION_PATCH
#define FT_VENDOR_ID 0x146a
#define ROBO_IF_PRODUCT_ID 0x1
#define EXT_IF_PRODUCT_ID 0x2
#define RF_DATA_LINK_PRODUCT_ID 0x3
#define ABF_IF_COMPLETE 0x8b // 0xf2
#define ABF_IF_COMPLETE_NUM_WRITE 32
#define ABF_IF_COMPLETE_NUM_READ 42
#define INTERFACE_QUERY_TIME 10000 // µs == 5ms
#define INTERFACE_QUERY_TIME_SERIAL 10000
#define FT_ENDPOINT_INTERRUPT_IN 0x81
#define FT_ENDPOINT_INTERRUPT_OUT 0x1
#define FT_ENDPOINT_BULK_IN 0x82
#define FT_ENDPOINT_BULK_OUT 0x2
#define FT_RF_ENDPOINT_INTERRUPT_IN 0x82
#define FT_RF_ENDPOINT_INTERRUPT_OUT 0x2
#define FT_USB_TIMEOUT 1000
#define FT_USB_TIMEOUT_LONG 10000
#define BAUDRATE_II B9600
#define BAUDRATE_RI B38400
#define PROGRAM_UPLOAD_PACKET_SIZE 128

#ifndef MIN
	#define MIN(a, b) ( (a)<=(b) ? (a) : (b) )
#endif
/** \endcond doxygen ignore end */


/**
 * \brief Returns lib version
 *
 *  Returns the library version.
 *
 *  @return version as Major Minor Patch
 */
long int GetLibVersion()
{
	return VERSION_MAJOR<<16 | VERSION_MINOR<<8 | VERSION_PATCH;
}


/**
 * \brief Returns lib version
 *
 * Returns the library version.
 * The allocated space should be freed with free() later.
 *
 * @return Pointer to a string with the serial
 */
char *GetLibVersionStrg()
{
	long int ver = GetLibVersion();
	char *s = (char *)malloc(16);
	int byte1 = ver & 0xff;
	int byte2 = (ver & 0xff00) >> 8;
	int byte3 = (ver & 0xff0000) >> 16;

	snprintf(s, 16, "%d.%02d.%02d", byte3, byte2, byte1);

	return s;
}


/**
 * \brief Library initialization (dummy)
 *
 * Dummy for compatibility. Only used in original library.
 * @return Always FTLIB_ERR_SUCCESS
 */
long int InitFtLib()
{
	return FTLIB_ERR_SUCCESS;
}


/**
 * \brief Initiates and scans the USB bus
 *
 * This function has to be called before any other USB action.
 * It will set up USB basic variables and then scan the USB bus.
 *
 * @return Always FTLIB_ERR_SUCCESS. Not able to fail.
 */
long int InitFtUsbDeviceList()
{
	usb_init();
    	usb_find_busses();
    	usb_find_devices();

	return FTLIB_ERR_SUCCESS;	
}


/** \cond doxygen ignore start */
static unsigned int GetNumFtDevicesFromRF(struct usb_device *dev)
{
	unsigned int iNum = 0;
	usb_dev_handle *device;
	int ret;
	unsigned char buffer[35] = { 0 };
	int i;
					
	device = usb_open(dev);

	for(i=1; i<9; i++) {
		ret = usb_control_msg(device, 0xc0, 0x52, i<<8 | 0x05, 0, buffer, 35, FT_USB_TIMEOUT);
		if (ret < 0) fprintf(stderr, "Error sending control msg 0xC0 0x52\n");
		else if (buffer[0] == 0xfa && buffer[1] == 0) iNum++; // buffer[1] == 0xff => no device
	}

	usb_close(device);

	return iNum;
}


static unsigned int GetNthFtDeviceFromRF(struct usb_device *dev, int iNum)
{
	usb_dev_handle *device;
	int ret=0;
	unsigned char buffer[35] = { 0 };
	int i;
					
	device = usb_open(dev);

	for(i=1; i<9, iNum>0; i++) {
		ret = usb_control_msg(device, 0xc0, 0x52, i<<8 | 0x05, 0, buffer, 35, FT_USB_TIMEOUT);
		if (ret < 0) fprintf(stderr, "Error sending control msg 0xC0 0x52\n");
		else if (buffer[0] == 0xfa && buffer[1] == 0) iNum--; // buffer[1] == 0xff => no device

		ret = i;
	}

	usb_close(device);

	return ret;
}


static int GetFtDeviceFromRFWithSerial(struct usb_device *dev, long int dwSN)
{
	usb_dev_handle *device;
	int ret;
	unsigned char buffer[35] = { 0 };
	int i;
	long int serial;
					
	device = usb_open(dev);

	for(i=1; i<9; i++) {
		ret = usb_control_msg(device, 0xc0, 0x52, i<<8 | 0x05, 0, buffer, 35, FT_USB_TIMEOUT);
		if (ret < 0) fprintf(stderr, "Error sending control msg 0xC0 0x52\n");
		else if (buffer[0] == 0xfa && buffer[1] == 0) { // buffer[1] == 0xff => no device
			serial = buffer[6]<<24 | buffer[5]<<16 | buffer[4]<<8 | buffer[3];
			
			if (serial == dwSN) {
				return i;
			}
		}
	}

	usb_close(device);

	return 0;
}
/** \endcond doxygen ignore end */


/**
 * \brief Get the count of found ft Interfaces over USB.
 *
 * If we find a Robo RF Data Link we will count the devices attached to it instead
 *
 * @return Number of ft Interface devices on the USB bus found.
 */
unsigned int GetNumFtUsbDevice()
{
	struct usb_device *dev;
	struct usb_bus *busses;
	struct usb_bus *bus;
	unsigned int iNum = 0;

	busses = usb_get_busses();
	
	for (bus = busses; bus; bus = bus->next) {
		for (dev = bus->devices; dev; dev = dev->next) {
			if (dev->descriptor.idVendor == FT_VENDOR_ID) {
				if (dev->descriptor.idProduct == RF_DATA_LINK_PRODUCT_ID) {
					iNum+=GetNumFtDevicesFromRF(dev);
				}
				iNum++;
			}
		}
	}	

	return iNum;
}


/** \cond doxygen ignore start */
static int FtproductIDToInterfaceID(int iProductID)
{
	switch(iProductID) {
		case ROBO_IF_PRODUCT_ID:
			return FT_ROBO_IF_USB;
		case EXT_IF_PRODUCT_ID:
			return FT_ROBO_IO_EXTENSION;
		case RF_DATA_LINK_PRODUCT_ID:
			return FT_ROBO_RF_DATA_LINK;
	}

	return 0;
}


static int FtInterfaceIDToProductID(int InterfaceID)
{
	switch(InterfaceID) {
		case FT_ROBO_IF_USB:
			return ROBO_IF_PRODUCT_ID;
		case FT_ROBO_IO_EXTENSION:
			return EXT_IF_PRODUCT_ID;
		case FT_ROBO_RF_DATA_LINK:
			return RF_DATA_LINK_PRODUCT_ID;
	}

	return 0;
}
/** \endcond doxygen ignore end */


/**
 * \brief Gets the handle to a ft USB device.
 *
 * Get the handle for the ft USB device with this number.
 * Passing just 0 as argument will use the first device found.
 *
 * Count the interfaces with GetNumFtUsbDevice()
 *
 * @see GetNumFtUsbDevice()
 * @param Num selected Interface. If unsure try 0.
 * @return The ft device or NULL if error
 */
FT_HANDLE GetFtUsbDeviceHandle(unsigned char Num)
{
	struct usb_device *dev;
	struct usb_bus *busses;
	struct usb_bus *bus;
	int i=0;
	FT_HANDLE ret;
	int count_ri_at_rf;

	busses = usb_get_busses();
	
	for (bus = busses; bus; bus = bus->next) {
		for (dev = bus->devices; dev; dev = dev->next) {
			if (dev->descriptor.idVendor == FT_VENDOR_ID) {
				//if (dev->descriptor.idProduct == 0x2) {
				//	// test: fake Product ID
				//	dev->descriptor.idProduct = 0x6;
				//}
				if (dev->descriptor.idProduct == RF_DATA_LINK_PRODUCT_ID) {
					count_ri_at_rf = GetNumFtDevicesFromRF(dev);
					i+=count_ri_at_rf;
				}
				if (i >= Num) { // '>=' because any RF will add more then 1 to the count
					ret = (FT_HANDLE) malloc (sizeof(struct ft_handle_devices));
					if (ret == NULL) {
						perror("GetFtUsbDeviceHandle malloc");
						return NULL;
					}
					ret->device = NULL;
					ret->dev = dev;
					ret->sdev = 0;
					ret->type = FtproductIDToInterfaceID(dev->descriptor.idProduct);
					sem_init(&ret->lock, 0, 1);
					memset(&ret->transfer_area, 0, sizeof(struct _FT_TRANSFER_AREA));
					ret->transfer_area.TransferAktiv = 0;
					ret->query_time = INTERFACE_QUERY_TIME;
					ret->transfer_area.RfModulNr = -1;
					ret->interface_connected = 0;

					if (dev->descriptor.idProduct == RF_DATA_LINK_PRODUCT_ID) {
						ret->transfer_area.RfModulNr = GetNthFtDeviceFromRF(dev, Num);
						if (ret->transfer_area.RfModulNr == 0) // user has chosen the RF Modul, so choose the first Interface at RF for the user
							ret->transfer_area.RfModulNr = GetNthFtDeviceFromRF(dev, 1);
						else 
							ret->type = FT_ROBO_IF_OVER_RF;
					}

					return ret;
				}
				i++;
			}
		}
	}

	return NULL;
}


/**
 * \brief Gets the handle to a ft USB device with a specific serial number.
 *
 * Get the handle for the ft USB device with this number.
 * Serial is 1 for most devices, unless explicitly changed in the device.
 * Second argument can be FT_AUTO_TYPE.
 *
 * @param dwSN Serial of the USB Device
 * @param dwTyp Type of the USB Device: FT_AUTO_TYPE, FT_ROBO_IF_USB, FT_ROBO_IO_EXTENSION, FT_ROBO_IF_OVER_RF or FT_ROBO_RF_DATA_LINK
 * @return The ft device or NULL on error
 */
FT_HANDLE GetFtUsbDeviceHandleSerialNr(long int dwSN, long int dwTyp)
{
	int i;
	FT_HANDLE ret;

	for(i=0; i < GetNumFtUsbDevice(); i++) {
		ret = GetFtUsbDeviceHandle(i);
		if (OpenFtUsbDevice(ret) != 0) {
			fprintf(stderr, "Skipping device: already open\n");
			continue;
		}
	
		if ((dwTyp == FT_AUTO_TYPE || ret->type == dwTyp) && GetFtSerialNr(ret) == dwSN) {
			CloseFtDevice(ret);
			return GetFtUsbDeviceHandle(i); // CloseFtDevice() frees memory, so we have to reallocate it
		}
		
		CloseFtDevice(ret);
	}

	return NULL;
}


/**
 * \brief Gets the handle to a ft serial device.
 *
 * Get the handle for the ft Serial device at the selected serial port.
 *
 * @param sDevice filename of your serial device, like /dev/ttyS0.
 * @param dwTyp Interface type. FT_INTELLIGENT_IF, FT_INTELLIGENT_IF_SLAVE or FT_ROBO_IF_COM.
 * @param dwZyklus Cycle to retrieve analog values (only II). Try 10.
 * @return The ft device or NULL if error.
 */
FT_HANDLE OpenFtCommDevice(char *sDevice, long int dwTyp, long int dwZyklus)
{
	long int dev;
	FT_HANDLE ret;
	unsigned char in[5];
	unsigned char on[] = " ft-Robo-ON-V1";
	on[0] = 0xA1;

	if ((dev = open(sDevice, O_RDWR | O_NOCTTY)) < 0) {
		perror("OpenFtCommDevice open");
		return NULL;
	}

	if ((ret = (FT_HANDLE) malloc (sizeof(struct ft_handle_devices))) == NULL) {
		perror("GetFtUsbDeviceHandle malloc");
		return NULL;
	}
	ret->device = NULL;
	ret->dev = NULL;
	ret->type = dwTyp;
	sem_init(&ret->lock, 0, 1);
	memset(&ret->transfer_area, 0, sizeof(struct _FT_TRANSFER_AREA));
	ret->transfer_area.TransferAktiv = 0;
	ret->analogcycle = dwZyklus/2.0+0.5;
	ret->query_time = INTERFACE_QUERY_TIME_SERIAL;
	ret->transfer_area.RfModulNr = -1;
	ret->interface_connected = 0;

	tcgetattr(dev, &ret->saveioset); /* save current modem settings */
	bzero(&ret->newioset, sizeof(struct termios));
	ret->newioset.c_cflag = CS8 | CLOCAL | CREAD; 
	if (dwTyp == FT_INTELLIGENT_IF || dwTyp == FT_INTELLIGENT_IF_SLAVE || dwTyp == FT_ROBO_IF_IIM)
		ret->newioset.c_cflag |= BAUDRATE_II;
	else // dwTyp == FT_ROBO_IF_COM
		ret->newioset.c_cflag |= BAUDRATE_RI;
        ret->newioset.c_oflag = 0;
        ret->newioset.c_lflag = 0;
        ret->newioset.c_cc[VTIME] = 1;
        ret->newioset.c_cc[VMIN] = 0;
	tcflush(dev, TCIFLUSH);
	tcsetattr(dev, TCSANOW, &ret->newioset);
	ret->sdev = dev;
	if (dwTyp == FT_INTELLIGENT_IF) ret->transfer_area.BusModules = 1;
	else if (dwTyp == FT_INTELLIGENT_IF_SLAVE) ret->transfer_area.BusModules = 2;

	if (dwTyp == FT_ROBO_IF_COM && ((write(dev, &on, 14)) != 14 || (read(dev, &in, 5)) != 5 || in[0] != 0x5E)) {
		fprintf(stderr, "OpenFtCommDevice: Error communicating with serial\n");
		free(ret);
		return NULL;
	}
	
	return ret;
}


/**
 * \brief Returns type of the interface
 *
 * This function will return the type of the interface that is behind the handle.
 *
 * @param hFt Handle of the device
 * @return NO_FT_DEVICE, FT_INTELLIGENT_IF, FT_INTELLIGENT_IF_SLAVE, FT_ROBO_IF_COM, FT_ROBO_IF_USB, FT_ROBO_IF_IIM, FT_ROBO_IF_OVER_RF, FT_ROBO_IO_EXTENSION or FT_ROBO_RF_DATA_LINK
 */
long int GetFtDeviceTyp(FT_HANDLE hFt)
{
	if (hFt == NULL) {
		fprintf(stderr, "GetFtDeviceTyp: No such device\n");
		return NO_FT_DEVICE;
	}

	return hFt->type;
}


/**
 * \brief Returns a string that identifies the interface with human words
 *
 * This function will give you a human readable string like "Robo Interface" you can work with.
 *
 * @param hFt Handle of the device
 * @param dest Buffer we can write the string to
 * @param len Maximum length of this buffer
 * @return FTLIB_ERR_SUCCESS or a failure
 */
long int GetFtDeviceTypeString(FT_HANDLE hFt, char *dest, int len)
{
	// Todo: Maybe let usb query the string from the device?
	if (hFt == NULL) {
		fprintf(stderr, "GetFtDeviceTyp: No such device\n");
		return NO_FT_DEVICE;
	}

	switch(GetFtDeviceTyp(hFt)) {
		case FT_INTELLIGENT_IF:
			strncpy(dest, "Intelligent Interface", len);
			break;
		case FT_INTELLIGENT_IF_SLAVE:
			strncpy(dest, "Intelligent Interface with slave", len);
			break;
		case FT_ROBO_IF_IIM:
			strncpy(dest, "Robo Interface II mode", len);
			break;
		case FT_ROBO_IF_COM:
			strncpy(dest, "Robo Interface over serial", len);
			break;
		case FT_ROBO_IF_USB:
			strncpy(dest, "Robo Interface over USB", len);
			break;
		case FT_ROBO_IO_EXTENSION:
			strncpy(dest, "Robo IO Extension", len);
			break;
		case FT_ROBO_RF_DATA_LINK:
			strncpy(dest, "Robo RF Datalink", len);
			break;
		case FT_ROBO_IF_OVER_RF:
			strncpy(dest, "Robo Interface over RF Datalink", len);
			break;
		default:
			strncpy(dest, "Unknown", len);
	}

	return FTLIB_ERR_SUCCESS;
}



/**
 * \brief Opens this USB device.
 *
 * This function will try to open the ft USB device that belongs to the ft handle hFt.
 * You can get the ft handle with GetFtUsbDeviceHandle() or GetFtUsbDeviceHandleSerialNr().
 *
 * @see GetFtUsbDeviceHandle()
 * @see GetFtUsbDeviceHandleSerialNr()
 * @param hFt ft USB Device to open
 * @return Number >= 0 on success, < 0 on error
 */
long int OpenFtUsbDevice(FT_HANDLE hFt)
{
	long int ret;

	if (hFt == NULL) {
		fprintf(stderr, "OpenFtUsbDevice: No such device\n");
		return  FTLIB_ERR_PORT_NUMBER_IS_NULL;
	}
	hFt->device = usb_open(hFt->dev);
	ret = usb_claim_interface(hFt->device, 0);
	if (ret < 0) perror("usb_claim_interface");

	return ret;
}


/**
 * \brief Close the ft Device
 *
 * This function will close the ft Device and free its memory.
 * Warning: CloseFtDevice() will also free() the allocated memory for this device!
 * Meaning, that you should not call OpenFtUsbDevice() after CloseFtDevice().
 *
 * @param hFt Handle of the Device to close.
 * @return A number < 0 on error.
 */
long int CloseFtDevice(FT_HANDLE hFt)
{
	int ret = 0;
	char off = 0xA2;
	unsigned char in[1];
	unsigned char buf[1];
	
	if (hFt == NULL) {
		fprintf(stderr, "CloseFtDevice: No such device\n");
		return  FTLIB_ERR_PORT_NUMBER_IS_NULL;
	}

	while(hFt->transfer_area.TransferAktiv != 0) {
		fprintf(stderr, "Transfer area still active\n");
		sleep(1);
	}

	switch(hFt->type) {
		// usb
		case FT_ROBO_RF_DATA_LINK:
		case FT_ROBO_IF_OVER_RF:
		case FT_ROBO_IF_USB:
		case FT_ROBO_IO_EXTENSION:
		default:
			ret = usb_release_interface(hFt->device, 0);
			if (ret < 0) {
				fprintf(stderr, "CloseFtDevice(): Error in usb_release_interface()\n");
				break;
			}
			ret = usb_close(hFt->device);
			break;
		// serial
		case FT_ROBO_IF_COM:
			if ((write(hFt->sdev, &off, 1)) != 1 || (read(hFt->sdev, &in, 1)) != 1 || in[0] != 0x5D) {
				fprintf(stderr, "CloseFtDevice: Error communicating with serial\n");
			}
		case FT_ROBO_IF_IIM:
		case FT_INTELLIGENT_IF:
		case FT_INTELLIGENT_IF_SLAVE:
			tcsetattr(hFt->sdev, TCSANOW, &hFt->saveioset);
			ret = close(hFt->sdev);
			break;
	}

	free(hFt);
	hFt = NULL;
	return ret;
}


/**
 * \brief Library deinitialization (dummy)
 *
 * Dummy for compatibility. Only used in original library.
 * @return Always FTLIB_ERR_SUCCESS
 */
long int CloseFtLib()
{
	return FTLIB_ERR_SUCCESS;
}


/**
 * \brief Check for Library initialization (dummy)
 *
 * Dummy for compatibility. Only used in original library.
 * @return Always FTLIB_ERR_LIB_IS_INITIALIZED since initialization is ignored in this version
 */
long int IsFtLibInit()
{
	return FTLIB_ERR_LIB_IS_INITIALIZED;
}


/** \cond doxygen ignore start */
static void *FtThread(FT_HANDLE hFt)
{
	FT_TRANSFER_AREA *area = &hFt->transfer_area;
	int ret;
	unsigned char out[ABF_IF_COMPLETE_NUM_WRITE]; //= {ABF_IF_COMPLETE,1,0x07,0,0,0,0,0,0,0,0,0,0,0,0,0,0};
	unsigned char in[ABF_IF_COMPLETE_NUM_READ];
	int num_write = ABF_IF_COMPLETE_NUM_WRITE;
	int num_read = ABF_IF_COMPLETE_NUM_READ;
	int usb_endpoint_write = FT_ENDPOINT_INTERRUPT_OUT;
	int usb_endpoint_read = FT_ENDPOINT_INTERRUPT_IN;
	int i=0;
	int ii_speed = 0;

	out[0] = ABF_IF_COMPLETE;
	area->TransferAktiv = 1;

	switch(hFt->type) {
		case FT_ROBO_IF_USB: // old firmware can not handle the new command, so stick with the old for now
		case FT_ROBO_IF_COM:
		default:
			out[0] = 0xf2;
			num_write = 17;
			num_read = 21;
			break;
		case FT_ROBO_IO_EXTENSION:
			out[0] = 0xf2;
			num_write = 6;
			num_read = 6;
			break;
		case FT_INTELLIGENT_IF:
			num_write = 2;
			break;
		case FT_INTELLIGENT_IF_SLAVE:
			num_write = 3;
			break;
		case FT_ROBO_IF_OVER_RF:
		case FT_ROBO_RF_DATA_LINK:
			usb_endpoint_write = FT_RF_ENDPOINT_INTERRUPT_OUT;
			usb_endpoint_read = FT_RF_ENDPOINT_INTERRUPT_IN;

			// init RF
			// 0x102 == first RF
			// 0x202 == 2nd RF
			// ...
			//ret = usb_control_msg(hFt->device, 0xc0, 0xfb, 0x102, 0x1, in, 2, FT_USB_TIMEOUT);
			ret = usb_control_msg(hFt->device, 0xc0, 0xfb, hFt->transfer_area.RfModulNr << 8 | 0x02, 0x1, in, 2, FT_USB_TIMEOUT);
			if (ret != 2) {
				fprintf(stderr, "%d FtThread: Error initiating RF Module!\n");
				area->TransferAktiv = 0;
			}
			break;
		}

	while(area->TransferAktiv == 1) {
		sem_wait(&hFt->lock);
		out[1] = area->M_Main;
		out[2] = (area->MPWM_Main[0] & 0x7) | (area->MPWM_Main[1]<<3 & 0x38) | (area->MPWM_Main[2]<<6 & 0xC0);
		out[3] = (area->MPWM_Main[2] & 0x1) | (area->MPWM_Main[3]<<1 & 0xE) | (area->MPWM_Main[4]<<4 & 0x70) | (area->MPWM_Main[5]<<7 & 0x80);
		out[4] = (area->MPWM_Main[5] & 0x3) | (area->MPWM_Main[6]<<2 & 0x1C) | (area->MPWM_Main[7]<<5 & 0xE0);
		out[5] = area->M_Sub1;
		out[6] = (area->MPWM_Sub1[0] & 0x7) | (area->MPWM_Sub1[1]<<3 & 0x38) | (area->MPWM_Sub1[2]<<6 & 0xC0);
		out[7] = (area->MPWM_Sub1[2] & 0x1) | (area->MPWM_Sub1[3]<<1 & 0xE) | (area->MPWM_Sub1[4]<<4 & 0x70) | (area->MPWM_Sub1[5]<<7 & 0x80);
		out[8] = (area->MPWM_Sub1[5] & 0x3) | (area->MPWM_Sub1[6]<<2 & 0x1C) | (area->MPWM_Sub1[7]<<5 & 0xE0);
		out[9] = area->M_Sub2;
		out[10] = (area->MPWM_Sub2[0] & 0x7) | (area->MPWM_Sub2[1]<<3 & 0x38) | (area->MPWM_Sub2[2]<<6 & 0xC0);
		out[11] = (area->MPWM_Sub2[2] & 0x1) | (area->MPWM_Sub2[3]<<1 & 0xE) | (area->MPWM_Sub2[4]<<4 & 0x70) | (area->MPWM_Sub2[5]<<7 & 0x80);
		out[12] = (area->MPWM_Sub2[5] & 0x3) | (area->MPWM_Sub2[6]<<2 & 0x1C) | (area->MPWM_Sub2[7]<<5 & 0xE0);
		out[13] = area->M_Sub3;
		out[14] = (area->MPWM_Sub3[0] & 0x7) | (area->MPWM_Sub3[1]<<3 & 0x38) | (area->MPWM_Sub3[2]<<6 & 0xC0);
		out[15] = (area->MPWM_Sub3[2] & 0x1) | (area->MPWM_Sub3[3]<<1 & 0xE) | (area->MPWM_Sub3[4]<<4 & 0x70) | (area->MPWM_Sub3[5]<<7 & 0x80);
		out[16] = (area->MPWM_Sub3[5] & 0x3) | (area->MPWM_Sub3[6]<<2 & 0x1C) | (area->MPWM_Sub3[7]<<5 & 0xE0);
		out[17]	= 0;
		out[18]	= 0;
		out[19]	= 0;
		out[20]	= 0;
		out[21]	= 0;
		out[22]	= 0;
		out[23]	= 0;
		out[24]	= 0;
		out[25]	= 0;
		out[26]	= 0;
		out[27]	= 0;
		out[28]	= 0;
		out[29]	= 0;
		out[30]	= 0;
		out[31]	= 0;
		
		// For the II we need to simulate different speeds here
		if (hFt->type == FT_INTELLIGENT_IF || hFt->type == FT_INTELLIGENT_IF_SLAVE) {
			int iCurMotor;
			for (iCurMotor = 0; iCurMotor < 8; iCurMotor++) {
				if (area->MPWM_Main[iCurMotor] < ii_speed) out[1] &= ~(1 << iCurMotor);
				if (area->MPWM_Sub1[iCurMotor] < ii_speed) out[5] &= ~(1 << iCurMotor);
			}

			ii_speed++;
			if (ii_speed > 7) ii_speed = 0;
		}

		if (hFt->type == FT_INTELLIGENT_IF) {
			i++;
			num_read = 1;
			out[0] = 0xC1;
			if (i % 20) { // EX
				out[0] = 0xC5;
				num_read = 3;
			} else if (i % 10) { // EY
				out[0] = 0xC9;
				num_read = 3;
			}
		} else if (hFt->type == FT_INTELLIGENT_IF_SLAVE) {
			i++;
			num_read = 2;
			out[0] = 0xC2;
			out[2] = out[5];
			if (i % 20) { // EX
				out[0] = 0xC6;
				num_read = 4;
			} else if (i % 10) { // EY
				out[0] = 0xCA;
				num_read = 4;
			}
		}
		sem_post(&hFt->lock);

		ret = 0;
		switch(hFt->type) {
			case FT_ROBO_IF_USB:
			case FT_ROBO_IO_EXTENSION:
			case FT_ROBO_IF_OVER_RF:
			case FT_ROBO_RF_DATA_LINK:
			default:
				ret = usb_interrupt_write(hFt->device, usb_endpoint_write, out, num_write, FT_USB_TIMEOUT);
				break;
			case FT_ROBO_IF_COM:
			case FT_INTELLIGENT_IF:
			case FT_INTELLIGENT_IF_SLAVE:
				ret = write(hFt->sdev, &out, num_write);
				break;
		}
		if (ret != num_write) {
			hFt->interface_connected = 0;
			fprintf(stderr, "FtThread: Error writing to the Interface...exiting!\n");
			break;
		}

		ret = 0;
		switch (hFt->type) {
			case FT_ROBO_IF_USB:
			case FT_ROBO_IO_EXTENSION:
			case FT_ROBO_IF_OVER_RF:
			case FT_ROBO_RF_DATA_LINK:
			default:
				ret = usb_interrupt_read(hFt->device, usb_endpoint_read, in, num_read, FT_USB_TIMEOUT);
				break;
			case FT_ROBO_IF_COM:
			case FT_INTELLIGENT_IF:
			case FT_INTELLIGENT_IF_SLAVE:
				ret = read(hFt->sdev, &in, num_read);
				break;
		}
		if (ret != num_read) {
			hFt->interface_connected = 0;
			fprintf(stderr, "FtThread: Error reading from the Interface\n");
			usleep(hFt->query_time);
			continue;
		}

		sem_wait(&hFt->lock);
		area->E_Main = in[0];
		area->E_Sub1 = in[1];
		area->E_Sub2 = in[2];
		area->E_Sub3 = in[3];
		if (hFt->type != FT_INTELLIGENT_IF && hFt->type != FT_INTELLIGENT_IF_SLAVE) {
			area->AX = in[4];
			area->AY = in[5];
		}
		area->A1 = in[6];
		area->A2 = in[7];
		if (hFt->type != FT_INTELLIGENT_IF && hFt->type != FT_INTELLIGENT_IF_SLAVE) {
			area->AX |= (in[8] & 0x3) << 8;
			area->AY |= (in[8] & 0xC) << 6;
		}
		area->A1 |= (in[8] & 0x30) << 4;
		area->A2 |= (in[8] & 0xC0) << 2;
		area->AZ = in[9];
		area->D1 = in[10];
		area->D2 = in[11];
		area->AV = in[12];
		area->AZ |= (in[13] & 0x3) << 8;
		area->D1 |= (in[13] & 0xC) << 6;
		area->D2 |= (in[13] & 0x30) << 4;
		area->AV |= (in[13] & 0xC0) << 2;
		area->IRKeys = in[14];
		area->BusModules = in[15];
		// 16
		area->AXS1 = in[17];
		area->AXS2 = in[18];
		area->AXS3 = in[19];
		area->AXS1 |= (in[20] & 0x3) << 8;
		area->AXS2 |= (in[20] & 0xC) << 6;
		area->AXS3 |= (in[20] & 0x30) << 4;
		// 21
		area->AVS1 = in[22];
		area->AVS2 = in[23];
		area->AVS3 = in[24];
		area->AVS1 |= (in[25] & 0x3) << 8;
		area->AVS2 |= (in[25] & 0xC) << 6;
		area->AVS3 |= (in[25] & 0x30) << 4;
		// 26...42
		if (hFt->type == FT_INTELLIGENT_IF || hFt->type == FT_INTELLIGENT_IF_SLAVE) {
			if (i % hFt->analogcycle) { // EX
				area->AX = in[1] & (8<<in[2]);
			} else if (i % (2*hFt->analogcycle)) { // EY
				area->AY = in[1] & (8<<in[2]);
			}
		}
		sem_post(&hFt->lock);

		hFt->interface_connected = 1;

		usleep(hFt->query_time);
	}
	if (hFt->type == FT_ROBO_IF_OVER_RF || hFt->type == FT_ROBO_RF_DATA_LINK) {
		ret = usb_control_msg(hFt->device, 0xc0, 0x21, hFt->transfer_area.RfModulNr << 8, 0, in, 1, FT_USB_TIMEOUT);
		if (ret != 1 || in[0] != 0xd7) {
			fprintf(stderr, "Error uninitiating RF Module!\n");
		}
	}

	hFt->transfer_area.TransferAktiv = 0;
	pthread_exit((void *) 0);
}
/** \endcond doxygen ignore end */


/**
 * \brief reset outputs
 *
 * Will clear all outputs.
 *
 * @return Always FTLIB_ERR_SUCCESS
 */
long int ResetFtTransfer(FT_HANDLE hFt) {
	FT_TRANSFER_AREA *area = &hFt->transfer_area;

	area->M_Main = 0;
	area->M_Sub1 = 0;
	area->M_Sub2 = 0;
	area->M_Sub3 = 0;

	return FTLIB_ERR_SUCCESS;
}


/**
 * \brief Starts the communication thread.
 *
 * This function is needed to start the communication with the interface in passive mode.
 * Get the handle with GetFtUsbDeviceHandle(), GetFtUsbDeviceHandleSerialNr() or OpenFtCommDevice().
 *
 * @see GetFtUsbDeviceHandle()
 * @see GetFtUsbDeviceHandleSerialNr()
 * @see OpenFtCommDevice()
 * @param hFt Handle of the interface.
 * @param ignored The second argument is ignored in this version.
 * @return Everything except FTLIB_ERR_SUCCESS indicates an error.
 */
long int StartFtTransferArea(FT_HANDLE hFt, NOTIFICATION_EVENTS* ignored)
{
	int ret;
	
	if (hFt == NULL) {
		fprintf(stderr, "StartFtTransferArea: No such device\n");
		return NO_FT_DEVICE;
	}

	ret = pthread_create(&hFt->t, NULL, (void *)FtThread, hFt);
	usleep(INTERFACE_QUERY_TIME*10);

	if(ret != 0) {
		perror("StartFtTransferArea pthread_create");
		return ret;
	}

	return FTLIB_ERR_SUCCESS;
}


/**
 * \brief Starts the communication thread.
 *
 * Since notification are ignored in this version, will just call StartFtTransferArea().
 *
 * @see StartFtTransferArea()
 */
long int StartFtTransferAreaWithCommunication(FT_HANDLE hFt, NOTIFICATION_EVENTS* ignored) {
	return StartFtTransferArea(hFt, ignored);
}


/**
 * \brief Get the transfer area
 *
 * This function will return a pointer to the transfer area of the given handle.
 *
 * @param hFt Handle of the device.
 * @return transfer area or NULL on error.
 */
FT_TRANSFER_AREA* GetFtTransferAreaAddress(FT_HANDLE hFt)
{
	if (hFt == NULL) {
		fprintf(stderr, "GetFtTransferAreaAddress: No such device\n");
		return NULL;
	}
	return &hFt->transfer_area;
}


/**
 * \brief Stops the communication thread.
 * \warning Will block a few microseconds until thread stopped.
 *
 * This function will stop the communication thread.
 *
 * @see StartFtTransferArea()
 * @param hFt Handle of the Interface.
 * @return Everything except FTLIB_ERR_SUCCESS indicates an error.
 */
long int StopFtTransferArea(FT_HANDLE hFt) {
	int ret;

	if (hFt == NULL) {
		fprintf(stderr, "StopFtTransferArea: No such device\n");
		return NO_FT_DEVICE;
	}

	usleep(INTERFACE_QUERY_TIME*10); // wait to make sure the last command is send to the interface
	if (hFt->transfer_area.TransferAktiv == 1) {
		hFt->transfer_area.TransferAktiv = 2; // cleaner then pthread_cancel()
	}
	if ((ret = pthread_join(hFt->t, NULL)) != 0) return ret;

	return FTLIB_ERR_SUCCESS;
}


/**
 * \brief check if transfer is active. 
 *
 * Check if we are currently communicating with the device.
 *
 * @param hFt Handle of the Interface.
 * @return FTLIB_ERR_THREAD_IS_RUNNING or FTLIB_ERR_THREAD_NOT_RUNNING
 */
long int IsFtTransferActiv(FT_HANDLE hFt) {
	if (hFt == NULL) {
		fprintf(stderr, "StopFtTransferArea: No such device\n");
		return NO_FT_DEVICE;
	}
	
	if (hFt->transfer_area.TransferAktiv) return FTLIB_ERR_THREAD_IS_RUNNING;

	return FTLIB_ERR_THREAD_NOT_RUNNING;
}


/**
 * \brief Upload a program to the interface
 *
 * Upload (download from the perspective of the interface) a program to the interface.
 *
 * @param hFt Handle of the Interface
 * @param dwMemBlock Destination 0 (Flash 1), 1 (Flash 2) or 2 (Ram)
 * @param pbArray Pointer to the program to upload
 * @param dwSize Size of the program to upload
 * @param dwParameter 1 to Autostart this program, else 0.
 * @param pbName Name of the program to upload
 * @param dwNameLen Length of the name
 * @return FTLIB_ERR_SUCCESS if you got lucky
 */
long int DownloadFtProgram(FT_HANDLE hFt, long int dwMemBlock, unsigned char *pbArray, long int dwSize, long int dwParameter, unsigned char *pbName, long int dwNameLen) {
	int ret;
	unsigned char buffer[128];
	long int i;
	crc_t crc;
	int memblockarg;

	if (hFt == NULL) {
		fprintf(stderr, "DownloadFtProgram: No such device\n");
		return  FTLIB_ERR_PORT_NUMBER_IS_NULL;
	} else if (hFt->type != FT_ROBO_IF_USB) {
		fprintf(stderr, "DownloadFtProgram: Sorry, I can only handle the Robo Interface over USB at this time.\n");
		return FTLIB_ERR_NOT_SUPPORTED;
	}

	switch(dwMemBlock) {
		case 0x0:	// flash 1
				memblockarg = 0x100;
				if (dwParameter == 1) memblockarg += 0x100;
				break;
		case 0x1:	// flash 2
				memblockarg = 0x101;
				if (dwParameter == 1) fprintf(stderr, "Warning: Autostart for flash 2 not supported\n");
				break;
		case 0x2:	// ram
				memblockarg = 0x102;
				if (dwParameter == 1) fprintf(stderr, "Warning: Autostart for RAM not supported\n");
				break;
		case 0xf0:	// firmware A
				memblockarg = 0xf200;
				break;
		case 0xf1:	// firmware B
				memblockarg = 0xf201;
				break;
		default:
				fprintf(stderr, "Unknown Memblock Target\n");
				return FTLIB_ERR_DOWNLOAD_WRONG_MEM_BLOCK;
	}

	// init upload
	ret = usb_control_msg(hFt->device, 0xc0, 0xf0, 0x20, 0, buffer, 1, FT_USB_TIMEOUT_LONG);
	if (ret < 0) {
		fprintf(stderr, "Error sending control msg 0xC0 0xF0\n");
		return ret;
	}
	if (buffer[0] != 1) {
		fprintf(stderr, "Error uploading Program: Return value for 0xC0 0xF0 is 0x%x\n", buffer[0]);
		return FTLIB_ERR_DOWNLOAD;
	}

	// write name
	memset(buffer, 0, 128); // clean buffer
	if (pbName != NULL)
		strncpy(buffer, pbName, MIN(dwNameLen, 80)); // copy to buffer, so we not change the original content
	ret = usb_control_msg(hFt->device, 0x40, 0x10, memblockarg, dwSize/PROGRAM_UPLOAD_PACKET_SIZE, buffer, 80, FT_USB_TIMEOUT_LONG);
	if (ret < 0) {
		fprintf(stderr, "Error sending control msg 0x40 0x10\n");
		return ret;
	}

	// check
	ret = usb_control_msg(hFt->device, 0xC0, 0x20, 0x0, 0x0, buffer, 1, FT_USB_TIMEOUT_LONG);
	if (ret < 0) {
		fprintf(stderr, "Error sending control ms 0xC0 0x20g\n");
		return ret;
	}
	if (buffer[0] != dwMemBlock || (buffer[0] == 0 && memblockarg == 0xf200) || (buffer[0] == 1 && memblockarg == 0xf201)) {
		fprintf(stderr, "Upload Error: Target mismatch\n");
	}

	// write the data
	for(i=0; dwSize >= PROGRAM_UPLOAD_PACKET_SIZE; i++, dwSize -= PROGRAM_UPLOAD_PACKET_SIZE) {
		memset(buffer, 0, 128); // clean buffer
		memcpy(buffer, pbArray + (i*PROGRAM_UPLOAD_PACKET_SIZE), MIN(dwSize, PROGRAM_UPLOAD_PACKET_SIZE)); // make sure we not change the original content
		
		crc = crc_init();
		crc = crc_update(crc, buffer, PROGRAM_UPLOAD_PACKET_SIZE);
		crc = crc_finalize(crc);

		// write 128 byte
		/*printf("CRC: 0x%x\n", crc);
		printf("Paket: 0x%x\n", i+1);
		for(k=0; k<128; k++) {
			printf("0x%x ", buffer[k]);
			if ((k+1) % 16 == 0 && k != 0) printf("\n");
		}
		printf("\n");*/
		ret = usb_control_msg(hFt->device, 0x40, 0x11, i+1, crc, buffer, PROGRAM_UPLOAD_PACKET_SIZE, FT_USB_TIMEOUT_LONG);
		if (ret < 0) {
			fprintf(stderr, "Error sending control msg 0x40 0x11 0x%x\n", i+1);
			return ret;
		}

		// check
		ret = usb_control_msg(hFt->device, 0xC0, 0x20, 0x0, 0x0, buffer, 1, FT_USB_TIMEOUT_LONG);
		if (ret < 0) {
			fprintf(stderr, "Error sending control msg 0xC0 0x20\n");
			return ret;
		}
		if (buffer[0] != 1) {
			fprintf(stderr, "Error uploading Program: Return value for 0xC0, 0x20 is 0x%x\n", buffer[0]);
			return FTLIB_ERR_DOWNLOAD;
		}
	}

	return FTLIB_ERR_SUCCESS;
}


/**
 * \brief Start a program
 *
 * Will start a program that has been Successfully uploaded to the interface.
 *
 * @param hFt Handle of the Interface
 * @param dwMemBlock Destination 0 (Flash 1), 1 (Flash 2) or 2 (Ram)
 * @return FTLIB_ERR_SUCCESS or FTLIB_ERR_IF_NO_PROGRAM
 */
long int StartFtProgram(FT_HANDLE hFt, long int dwMemBlock) {
	int ret;
	unsigned char buffer[2];

	if (hFt == NULL) {
		fprintf(stderr, "StartFtProgram: No such device\n");
		return  FTLIB_ERR_PORT_NUMBER_IS_NULL;
	}

	switch (hFt->type) {
		case FT_ROBO_IF_USB:
			// note: serial documentation says 0xf4 here, sniffer says 0x12
			ret = usb_control_msg(hFt->device, 0xc0, 0x12, dwMemBlock, 0, buffer, 1, FT_USB_TIMEOUT_LONG);
			if (ret < 0) {
				fprintf(stderr, "Error sending control msg 0xC0 0xF4\n");
				return ret;
			}
			if ((buffer[0]) == 0x1) return FTLIB_ERR_SUCCESS;
			else return FTLIB_ERR_IF_NO_PROGRAM;
			break;
		case FT_ROBO_IF_COM:
			buffer[0] = 0xf4;
			buffer[1] = dwMemBlock;
			if ((write(hFt->sdev, &buffer, 2)) != 2 || (read(hFt->sdev, &buffer, 1)) != 1) {
				return FTLIB_ERR_IF_NO_PROGRAM;
			}
			if ((buffer[0]) == 0x1) return FTLIB_ERR_SUCCESS;
			else return FTLIB_ERR_IF_NO_PROGRAM;
			break;
	}

	return FTLIB_ERR_NOT_SUPPORTED;
}


/**
 * \brief Stop a program
 *
 * Will stop the current running program that has been uploaded to the interface.
 *
 * @param hFt Handle of the Interface
 * @return FTLIB_ERR_SUCCESS or FTLIB_ERR_IF_NO_PROGRAM
 */
long int StopFtProgram(FT_HANDLE hFt) {
	int ret;
	unsigned char buffer[1];

	if (hFt == NULL) {
		fprintf(stderr, "StopFtProgram: No such device\n");
		return  FTLIB_ERR_PORT_NUMBER_IS_NULL;
	}

	switch (hFt->type) {
		case FT_ROBO_IF_USB:
			// note: serial documentation says 0xf8 here, sniffer says 0x13
			ret = usb_control_msg(hFt->device, 0xc0, 0x13, 0, 0, buffer, 1, FT_USB_TIMEOUT_LONG);
			if (ret < 0) {
				fprintf(stderr, "Error sending control msg 0xC0 0x13\n");
				return ret;
			}

			if ((buffer[0]) == 0x1) return FTLIB_ERR_SUCCESS;
			else return FTLIB_ERR_IF_NO_PROGRAM;
			break;
		case FT_ROBO_IF_COM:
			buffer[0] = 0xf8;
			if ((write(hFt->sdev, &buffer, 1)) != 1 || (read(hFt->sdev, &buffer, 1)) != 1) {
				return FTLIB_ERR_IF_NO_PROGRAM;
			}
			if ((buffer[0]) == 0x1) return FTLIB_ERR_SUCCESS;
			else return FTLIB_ERR_IF_NO_PROGRAM;
			break;
	}

	return FTLIB_ERR_NOT_SUPPORTED;
}


/**
 * \brief Delete a program
 *
 * Will delete a program that has been uploaded to the interface.
 *
 * @param hFt Handle of the Interface
 * @param dwMemBlock Destination 0 (Flash 1), 1 (Flash 2) or 2 (Ram)
 * @return FTLIB_ERR_SUCCESS or FTLIB_ERR_IF_NO_PROGRAM
 */
long int DeleteFtProgram(FT_HANDLE hFt, long int dwMemBlock) {
	int ret;
	unsigned char buffer[2];
	
	if (hFt == NULL) {
		fprintf(stderr, "DeleteFtProgram: No such device\n");
		return  FTLIB_ERR_PORT_NUMBER_IS_NULL;
	}

	switch (hFt->type) {
		case FT_ROBO_IF_USB:
			ret = usb_control_msg(hFt->device, 0xc0, 0xf5, dwMemBlock, 0, buffer, 1, FT_USB_TIMEOUT_LONG);
			if (ret < 0) {
				fprintf(stderr, "Error sending control msg 0xC0 0xF5\n");
				return ret;
			}

			if ((buffer[0]) == 0x1) return FTLIB_ERR_SUCCESS;
			else return FTLIB_ERR_IF_NO_PROGRAM;
			break;
		case FT_ROBO_IF_COM:
			buffer[0] = 0xf5;
			buffer[1] = dwMemBlock;
			if ((write(hFt->sdev, &buffer, 2)) != 2 || (read(hFt->sdev, &buffer, 1)) != 1) {
				return FTLIB_ERR_IF_NO_PROGRAM;
			}
			if ((buffer[0]) == 0x1) return FTLIB_ERR_SUCCESS;
			else return FTLIB_ERR_IF_NO_PROGRAM;
			break;
	}

	return FTLIB_ERR_NOT_SUPPORTED;
}


/**
 * \brief Activate a program
 *
 * Will activate a program that has been uploaded to the interface.
 *
 * @param hFt Handle of the Interface
 * @param dwMemBlock Destination 0 (Flash 1) or 1 (Flash 2)
 * @return FTLIB_ERR_SUCCESS or FTLIB_ERR_IF_NO_PROGRAM
 */
long int SetFtProgramActiv(FT_HANDLE hFt, long int dwMemBlock) {
	int ret;
	unsigned char buffer[1];

	if (hFt == NULL) {
		fprintf(stderr, "SetFtProgramActiv: No such device\n");
		return  FTLIB_ERR_PORT_NUMBER_IS_NULL;
	}

	switch (hFt->type) {
		case FT_ROBO_IF_USB:
			ret = usb_control_msg(hFt->device, 0xc0, 0xf9, dwMemBlock, 0, buffer, 1, FT_USB_TIMEOUT_LONG);
			if (ret < 0) {
				fprintf(stderr, "Error sending control msg 0xC0 0xf9\n");
				return ret;
			}

			if ((buffer[0]) == 0x1) return FTLIB_ERR_SUCCESS;
			else return FTLIB_ERR_IF_NO_PROGRAM;
			break;
		case FT_ROBO_IF_COM:
			buffer[0] = 0xf9;
			buffer[1] = dwMemBlock;
			if ((write(hFt->sdev, &buffer, 2)) != 2 || (read(hFt->sdev, &buffer, 1)) != 1) {
				return FTLIB_ERR_IF_NO_PROGRAM;
			}
			if ((buffer[0]) == 0x1) return FTLIB_ERR_SUCCESS;
			else return FTLIB_ERR_IF_NO_PROGRAM;
			break;
	}

	return FTLIB_ERR_NOT_SUPPORTED;
}


/**
 * \brief Get the name of a program
 *
 * Will write the name of a program that has been uploaded to the interface to a given area.
 *
 * @param hFt Handle of the Interface
 * @param dwMemBlock Destination 0 (Flash 1), 1 (Flash 2) or 2 (Ram)
 * @param pName Pointer to the area where we can store the name
 * @param dwSize Size of the area to store the name to
 * @return FTLIB_ERR_SUCCESS or FTLIB_ERR_IF_NO_PROGRAM
 */
long int GetFtProgramName(FT_HANDLE hFt, long int dwMemBlock, long int dwSize, void *pName) {
	int ret;
	unsigned char buffer[dwSize+1];

	if (hFt == NULL) {
		fprintf(stderr, "GetFtProgramName: No such device\n");
		return  FTLIB_ERR_PORT_NUMBER_IS_NULL;
	}

	switch (hFt->type) {
		case FT_ROBO_IF_USB:
			ret = usb_control_msg(hFt->device, 0xc0, 0xfa, dwMemBlock, 0, buffer, dwSize + 1, FT_USB_TIMEOUT_LONG);
			if (ret < 0) {
				fprintf(stderr, "Error sending control msg 0xC0 0xFA\n");
				return ret;
			}
			memcpy(pName, buffer+1, ret-1);

			if (buffer[0] == 0x1) return FTLIB_ERR_SUCCESS;
			if (buffer[0] == 0xf3) return FTLIB_ERR_IF_NO_PROGRAM;
			return buffer[1];
			break;
		case FT_ROBO_IF_COM:
			buffer[0] = 0xfa;
			buffer[1] = dwMemBlock;
			if ((write(hFt->sdev, &buffer, 2)) != 2 || (ret = read(hFt->sdev, &buffer, dwSize+1)) < 0 || buffer[0] != 0x01) {
				return FTLIB_ERR_IF_NO_PROGRAM;
			}
			memcpy(pName, buffer+1, ret-1);
			if (buffer[0] == 0x1) return FTLIB_ERR_SUCCESS;
			break;
	}

	return FTLIB_ERR_NOT_SUPPORTED;
}


/**
 * \brief Checks if a program is running
 *
 * Checks if a program is currently running.
 *
 * @param hFt Handle of the Interface
 * @param num Area where we can store the number of the running program.
 * @return 1 if a program is running, else 0
 */
int GetFtStatus(FT_HANDLE hFt, int *num) {
	int ret;
	unsigned char buffer[3];

	if (hFt == NULL) {
		fprintf(stderr, "GetFtStatus: No such device\n");
		return  FTLIB_ERR_PORT_NUMBER_IS_NULL;
	}

	switch (hFt->type) {
		case FT_ROBO_IF_USB:
			// test replace 0xf0 with 0x50
			ret = usb_control_msg(hFt->device, 0xc0, 0xf0, 0x3, 0, buffer, 3, FT_USB_TIMEOUT);
			if (ret < 0) {
				fprintf(stderr, "Error sending control msg 0xC0 0xF0\n");
				return ret;
			}
			ret = buffer[1];
			*num = buffer[2];
			break;
		case FT_ROBO_IF_COM:
			buffer[0] = 0xf0;
			buffer[1] = 0x3;
			if ((write(hFt->sdev, &buffer, 2)) != 2 || (ret = read(hFt->sdev, &buffer, 3)) < 0 || buffer[0] != 0xfc) {
				return ret;
			}
			ret = buffer[1];
			*num = buffer[2];
			break;
		default:
			return FTLIB_ERR_NOT_SUPPORTED;
	}

	return ret;
}


/**
 * \brief Get the firmware number of this interface.
 *
 * Returns the firmware number of the interface squashed into a single int.
 *
 * @param hFt Handle of the Interface
 * @return Firmware number as int byte4 | byte3 | byte2 | byte1, 0 on error.
 */
long int GetFtFirmware(FT_HANDLE hFt) {
	int ret;
	unsigned char buffer[35] = { 0 };
	long int firmware = 0;

	if (hFt == NULL) {
		fprintf(stderr, "GetFtFirmware: No such device\n");
		return  FTLIB_ERR_PORT_NUMBER_IS_NULL;
	}


	switch (hFt->type) {
		case FT_INTELLIGENT_IF:
		case FT_INTELLIGENT_IF_SLAVE:
			return 0;
			break;
		case FT_ROBO_IF_USB:
		case FT_ROBO_IO_EXTENSION:
		case FT_ROBO_RF_DATA_LINK:
			ret = usb_control_msg(hFt->device, 0xc0, 0xf0, 0x1, 0, buffer, 5, FT_USB_TIMEOUT);
			if (ret < 0) {
				fprintf(stderr, "Error sending control msg 0xC0 0xF0\n");
				return 0;
			}
			firmware = buffer[1] | buffer[2]<<8 | buffer[3]<<16 | buffer[4]<<24;
			break;
		case FT_ROBO_IF_OVER_RF:
			ret = usb_control_msg(hFt->device, 0xc0, 0x52, hFt->transfer_area.RfModulNr<<8 | 0x05, 0, buffer, 35, FT_USB_TIMEOUT);
			if (ret < 0) {
				fprintf(stderr, "Error sending control msg 0xC0 0x52\n");
				return 0;
			}
			if (buffer[0] == 0xfa && buffer[1] == 0) { // buffer[1] == 0xff => no device
				firmware = buffer[23]<<24 | buffer[22]<<16 | buffer[21]<<8 | buffer[20];
			}
			break;
		case FT_ROBO_IF_COM:
			buffer[0] = 0xf0;
			buffer[1] = 0x01;
			ret = write(hFt->sdev, &buffer, 2);
			if (ret != 2) {
				fprintf(stderr, "Error writing msg 0xF0 0x01\n");
				return 0;
			}
			ret = read(hFt->sdev, &buffer, 5);
			if (ret != 5) {
				fprintf(stderr, "Error reading msg 0xF0 0x01\n");
				return 0;
			}
			firmware = buffer[1] | buffer[2]<<8 | buffer[3]<<16 | buffer[4]<<24;
			break;
		default:
			return FTLIB_ERR_NOT_SUPPORTED;
	}

	return firmware;
}


/**
 * \brief Get the firmware number of this interface.
 *
 * Returns the firmware number of the interface with this handle.
 * The allocated space should be freed with free() later.
 *
 * @param hFt Handle of the Interface
 * @return Pointer to a string with the firmware
 */
char *GetFtFirmwareStrg(FT_HANDLE hFt) {
	long int ifw = GetFtFirmware(hFt);
	char *s = (char *)malloc(16);
	int byte1 = ifw & 0xff;
	int byte2 = (ifw & 0xff00) >> 8;
	int byte3 = (ifw & 0xff0000) >> 16;
	int byte4 = (ifw & 0xff000000) >> 24;

	snprintf(s, 16, "%d.%02d.%02d.%02d", byte4, byte3, byte2, byte1);

	return s;
}


/**
 * \brief Get the serial number of this interface.
 *
 * Returns the serial number of the interface squashed into a single int.
 *
 * @param hFt Handle of the Interface
 * @return Serial number as int byte4 | byte3 | byte2 | byte1, 0 on error.
 */
long int GetFtSerialNr(FT_HANDLE hFt) {
	int ret;
	unsigned char buffer[35] = { 0 };
	long int serial = 0;

	if (hFt == NULL) {
		fprintf(stderr, "GetFtSerialNr: No such device\n");
		return  FTLIB_ERR_PORT_NUMBER_IS_NULL;
	}


	switch (hFt->type) {
		case FT_INTELLIGENT_IF:
		case FT_INTELLIGENT_IF_SLAVE:
			return 0;
			break;
		case FT_ROBO_IF_USB:
			ret = usb_control_msg(hFt->device, 0xc0, 0xf0, 0x2, 0, buffer, 5, FT_USB_TIMEOUT);
			if (ret < 0) {
				fprintf(stderr, "Error sending control msg 0xC0 0xF0\n");
				return 0;
			}
			serial = buffer[1] + buffer[2]*100 + buffer[3]*10000 + buffer[4]*1000000;
			break;
		case FT_ROBO_IO_EXTENSION:
			ret = usb_control_msg(hFt->device, 0xc0, 0xf0, 0x2, 0, buffer, 14, FT_USB_TIMEOUT);
			if (ret < 0) {
				fprintf(stderr, "Error sending control msg 0xC0 0xF0\n");
				return 0;
			}
			serial = buffer[1] + buffer[2]*100 + buffer[3]*10000 + buffer[4]*1000000;
			break;
		case FT_ROBO_RF_DATA_LINK:
			ret = usb_control_msg(hFt->device, 0xc0, 0xf0, 0x2, 0, buffer, 14, FT_USB_TIMEOUT);
			if (ret < 0) {
				fprintf(stderr, "Error sending control msg 0xC0 0x52\n");
				return 0;
			}
			serial = buffer[1] + buffer[2]*100 + buffer[3]*10000 + buffer[4]*1000000;
			break;
		case FT_ROBO_IF_OVER_RF:
			ret = usb_control_msg(hFt->device, 0xc0, 0x52, hFt->transfer_area.RfModulNr<<8 | 0x05, 0, buffer, 35, FT_USB_TIMEOUT);
			if (ret < 0) {
				fprintf(stderr, "Error sending control msg 0xC0 0x52\n");
				return 0;
			}
			if (buffer[0] == 0xfa && buffer[1] == 0) { // buffer[1] == 0xff => no device
				serial = buffer[6]*1000000 + buffer[5]*10000 + buffer[4]*100 + buffer[3];
			}
			break;
		case FT_ROBO_IF_COM:
			buffer[0] = 0xf0;
			buffer[1] = 0x02;
			ret = write(hFt->sdev, &buffer, 2);
			if (ret != 2) {
				fprintf(stderr, "Error writing msg 0xF0 0x02\n");
				return 0;
			}
			ret = read(hFt->sdev, &buffer, 5);
			if (ret != 5) {
				fprintf(stderr, "Error reading msg 0xF0 0x02\n");
				return 0;
			}
			serial = buffer[1] + buffer[2]*100 + buffer[3]*10000 + buffer[4]*1000000;
			break;
		default:
			return FTLIB_ERR_NOT_SUPPORTED;
	}

	return serial;
}


/**
 * \brief Get the serial number of this interface.
 *
 * Returns the serial number of the interface with this handle.
 * The allocated space should be freed with free() later.
 *
 * @param hFt Handle of the Interface
 * @return Pointer to a string with the serial
 */
char *GetFtSerialNrStrg(FT_HANDLE hFt) {
	long int ifw = GetFtSerialNr(hFt);
	char *s = (char *)malloc(16);
	int byte1, byte2, byte3, byte4;

	byte1 = ifw % 100;
	ifw /= 100;
	byte2 = ifw % 100;
	ifw /= 100;
	byte3 = ifw % 100;
	ifw /= 100;
	byte4 = ifw % 100;
	ifw /= 100;

	snprintf(s, 16, "%d.%02d.%02d.%02d", byte4, byte3, byte2, byte1);

	return s;
}


/**
 * \brief Close all ft devices
 *
 * Dummy. Can't be supported. Only used in original library.
 *
 * @return Always FTLIB_ERR_NOT_SUPPORTED
 */
long int CloseAllFtDevices() {
	return FTLIB_ERR_NOT_SUPPORTED;
}


/**
 * \brief Set the inputs D1 and D2 to distance oder voltage measuring
 *
 * This function allows to enable the inputs D1 and D2 to measure distances.
 * Must be called before StartFtTransferArea() 
 *
 * Note by Hardware Vendor:
 * "Since the operating mode of the D1 / D2 inputs can be set by means of software, we recommend that no
 * voltage be supplied 'directly' to these connections in order to avoid damage to the interface during software
 * errors. Since the inputs are highly resistive, a resistance of approximately 200 Ohm - 470 Ohm should be
 * directly connected to the D1 / D2 socket (series connection). We recommend to connect the voltage range to
 * be measured 'behind' it."
 *
 * @param hFt Handle of the Interface
 * @param dwMode Set mode to IF_DS_INPUT_VOLTAGE (measure voltage) or IF_DS_INPUT_DISTANCE (measure distance)
 * @param dwTol1 Range of tolerance for D1. Try IF_DS_INPUT_TOL_STD (20).
 * @param dwTol2 Range of tolerance for D2. Try IF_DS_INPUT_TOL_STD (20).
 * @param dwLevel1 Threshold for D1. Try 100.
 * @param dwLevel2 Threshold for D2. Try 100.
 * @param dwRepeat1 Repition value for D1. Try IF_DS_INPUT_REP_STD (3).
 * @param dwRepeat2 Repition value for D2. Try IF_DS_INPUT_REP_STD (3).
 * @return FTLIB_ERR_SUCCESS on success
 */
long int SetFtDistanceSensorMode(FT_HANDLE hFt, long int dwMode, long int dwTol1, long int dwTol2, long int dwLevel1, long int dwLevel2, long int dwRepeat1, long int dwRepeat2) {
	int ret;
	unsigned char buffer[] =  {1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0}; // 34
	int i;

	buffer[1] = dwTol1;
	buffer[2] = dwTol2;
	buffer[3] = dwLevel1;
	buffer[4] = dwLevel1>>8;
	buffer[5] = dwLevel2;
	buffer[6] = dwLevel2>>8;
	buffer[7] = dwRepeat1;
	buffer[8] = dwRepeat2;
	
	if (hFt == NULL) {
		fprintf(stderr, "GetFtFirmware: No such device\n");
		return FTLIB_ERR_PORT_NUMBER_IS_NULL;
	}

	switch (hFt->type) {
		case FT_ROBO_IF_USB:
			ret = usb_control_msg(hFt->device, 0x40, 0xf1, 0x1, dwMode, buffer+1, 8, FT_USB_TIMEOUT);
			if (ret != 8) {
				fprintf(stderr, "Error sending control msg 0x40 0xf1\n");
				return ret;
			}
			break;
		case FT_ROBO_RF_DATA_LINK:
		case FT_ROBO_IF_OVER_RF:
			ret = usb_control_msg(hFt->device, 0x40, 0x53, hFt->transfer_area.RfModulNr<<8 | 0x01, 0, buffer, 34, FT_USB_TIMEOUT);
			if (ret != 34) {
				fprintf(stderr, "Error sending control msg 0x40 0x53\n");
				return ret;
			}
			break;
		case FT_ROBO_IF_COM:
			// move data in array for two bytes
			for(i=10; i>=3; i--) {
				buffer[i] = buffer[i-2];
			}
			buffer[0] = 0xf1;
			buffer[1] = 0x01;
			buffer[2] = dwMode;
			if ((write(hFt->sdev, &buffer, 11)) != 11 || (read(hFt->sdev, &buffer, 1)) != 1 || buffer[0] != 0x01) {
				fprintf(stderr, "SetFtDistanceSensorMode: Error communicating with serial\n");
				return buffer[0];
			}
			break;
		default:
			return FTLIB_ERR_NOT_SUPPORTED;
	}

	usleep(100000); // wait before continue, else it doesn't always work

	return FTLIB_ERR_SUCCESS;
}


/**
 * \brief Sets the frequency and call sign for a Robo Interface or RF Data Link.
 *
 * Sets the frequency and call sign which allows to control multiple Interfaces at one RF Data Link.
 * The value won't be lost on power failure.
 *
 * @param hFt Handle of the Interface
 * @param frequency to use. May be between 2 and 80.
 * @param callSign call sign for this Interface. May be between 1 and 8. (ignored for the RF Data Link)
 * @return FTLIB_ERR_SUCCESS on success
 */
long int SetRFMode(FT_HANDLE hFt, long int frequency, long int callSign) {
	int ret;
	unsigned char buffer[5];
	
	if (hFt == NULL) {
		fprintf(stderr, "GetFtFirmware: No such device\n");
		return FTLIB_ERR_PORT_NUMBER_IS_NULL;
	} else if (frequency < 2 || frequency > 80) {
		return FTLIB_ERR_INVALID_PARAM;
	} else if (callSign > 8) {
		return FTLIB_ERR_INVALID_PARAM;
	}

	switch (hFt->type) {
		case FT_ROBO_RF_DATA_LINK:
			ret = usb_control_msg(hFt->device, 0xc0, 0xfb, 1, frequency, buffer, 2, FT_USB_TIMEOUT);
			if (ret != 2 || buffer[0] != 0xfe || buffer[1] != 0) {
				fprintf(stderr, "Error sending control msg 0xc0 0xfb\n");
				return ret;
			}
			break;
		case FT_ROBO_IF_USB:
			// not or-ing 1 to frequency seems to disable the modul
			ret = usb_control_msg(hFt->device, 0xc0, 0xfb, (callSign<<8) | 1, (1<<8) | frequency, buffer, 2, FT_USB_TIMEOUT);
			if (ret != 2 || buffer[0] != 0xfe || buffer[1] != 0) {
				fprintf(stderr, "Error sending control msg 0xc0 0xfb\n");
				return ret;
			}
			break;
		case FT_ROBO_IF_COM:
			buffer[0] = 0xfb;
			buffer[1] = 0x1;
			buffer[2] = 0x7f;
			buffer[3] = frequency;
			buffer[4] = callSign;
			if ((write(hFt->sdev, &buffer, 5)) != 5 || (ret = read(hFt->sdev, &buffer, 2)) != 2 || buffer[0] != 0xfe) {
				fprintf(stderr, "SetRFMode: Error communicating with serial\n");
				return ret;
			}
			break;
		default:
			return FTLIB_ERR_NOT_SUPPORTED;
	}
 
	return FTLIB_ERR_SUCCESS;
}


/**
 * \brief Gets the frequency and call sign of a Robo Interface or RF Data Link.
 *
 * Sets the frequency and call sign which allows to control multiple Interfaces at one RF Data Link.
 *
 * @param hFt Handle of the Interface
 * @param frequency Points to a place to store the frequency.
 * @param callSign Points to a place to store the callSign. (Value will be 0 for the RF Data Link)
 * @return FTLIB_ERR_SUCCESS on success
 */
long int GetRFMode(FT_HANDLE hFt, long int *frequency, long int *callSign) {
	int ret;
	unsigned char buffer[8];
	
	if (hFt == NULL) {
		fprintf(stderr, "GetFtFirmware: No such device\n");
		return FTLIB_ERR_PORT_NUMBER_IS_NULL;
	}

	switch (hFt->type) {
		case FT_ROBO_IF_USB:
		case FT_ROBO_RF_DATA_LINK:
			ret = usb_control_msg(hFt->device, 0xc0, 0xfb, 0x81, 0, buffer, 8, FT_USB_TIMEOUT);
			if (ret != 8) {
				fprintf(stderr, "Error sending control msg 0xc0 0xfb\n");
				return ret;
			}
			*frequency = buffer[6];
			*callSign = buffer[7];
			break;
		case FT_ROBO_IF_COM:
			buffer[0] = 0xfb;
			buffer[1] = 0x81;
			if ((write(hFt->sdev, &buffer, 2)) != 2 || (ret = read(hFt->sdev, &buffer, 8)) != 8 || buffer[0] != 0x7e) {
				fprintf(stderr, "GetRFMode: Error communicating with serial\n");
				return ret;
			}
			*frequency = buffer[6];
			*callSign = buffer[7];
			break;
		default:
			return FTLIB_ERR_NOT_SUPPORTED;
	}
 
	return FTLIB_ERR_SUCCESS;
}


/**
 * \brief Switches between the real serial and 0001 of a device.
 *
 * Every ft Interface is shipped with 0001 as serial.
 * Nevertheless each has its own serial which can be activated.
 *
 * @param hFt Handle of the Interface
 * @param bOn 0 to use 0001, else the real serial
 * @return FTLIB_ERR_SUCCESS on success
 */
long int SetRealSerial(FT_HANDLE hFt, unsigned char bOn) {
	int ret;
	// on: 2 0xd2 0x3a
	// off: 1 0x81 0x6f
	// RF: 2 d8 77 vs 1 8b 22
	// Whats the number?
	// SetSerial(hFt, 5386);
	unsigned char buffer[16] = {0xaf, 0x83, 0x55, 0xa1, 1, 0, 0, 0, 1, 0x81, 0x6f, 0, 0, 0, 0, 0};

	if (hFt == NULL) {
		fprintf(stderr, "GetFtFirmware: No such device\n");
		return FTLIB_ERR_PORT_NUMBER_IS_NULL;
	}

	switch (hFt->type) {
		case FT_ROBO_IF_USB:
			if (bOn) {
				buffer[8] = 2;
				buffer[9] = 0xd2;
				buffer[10] = 0x3a;
			} else {
				buffer[8] = 1;
				buffer[9] = 0x81;
				buffer[10] = 0x6f;
			}
			ret = usb_control_msg(hFt->device, 0x40, 0xaf, 0x83, 0, buffer, 16, 200000);
			if (ret != 16) {
				fprintf(stderr, "Error sending control msg 0x40 0xaf\n");
				return ret;
			}
			break;
		case FT_ROBO_IF_OVER_RF:
			if (bOn) {
				buffer[8] = 2;
				buffer[9] = 0xd8;
				buffer[10] = 0x77;
			} else {
				buffer[8] = 1;
				buffer[9] = 0x8b;
				buffer[10] = 0x22;
			}
			ret = usb_control_msg(hFt->device, 0x40, 0xaf, 0x83, 0, buffer, 16, 200000);
			if (ret != 16) {
				fprintf(stderr, "Error sending control msg 0x40 0xaf\n");
				return ret;
			}
			break;
		case FT_ROBO_IO_EXTENSION:
			if (bOn) {
				buffer[8] = 2;
				buffer[9] = 0x5f;
				buffer[10] = 0x28;
			} else {
				buffer[8] = 1;
				buffer[9] = 0x0c;
				buffer[10] = 0x7d;
			}
			ret = usb_control_msg(hFt->device, 0x40, 0xaf, 0x83, 0, buffer, 16, 200000);
			if (ret != 16) {
				fprintf(stderr, "Error sending control msg 0x40 0xaf\n");
				return ret;
			}
			break;
		case FT_ROBO_IF_COM:
			if ((write(hFt->sdev, &buffer, 16)) != 16 || (ret = read(hFt->sdev, &buffer, 2)) != 2 || buffer[0] != 0x7c) {
				fprintf(stderr, "SetRealSerial: Error communicating with serial\n");
				return ret;
			}
			break;
		default:
			return FTLIB_ERR_NOT_SUPPORTED;
	}
 
	return FTLIB_ERR_SUCCESS;
}



/**
 * @brief Gets the Manufacturer of the Interface
 *
 * Will return the Manufacturer of a fischertechnik USB device.
 * The allocated space should be freed with free() later.
 *
 * @param hFt Handle of the Interface
 * @return Pointer to the string with the name
 */
char *GetFtManufacturerStrg(FT_HANDLE hFt) {
	char *buffer = (char *)malloc(128);
	memset(buffer, '\0', 128);

	if (hFt == NULL) {
		fprintf(stderr, "GetFtFirmware: No such device\n");
	}

	switch (hFt->type) {
		case FT_ROBO_IF_USB:
		case FT_ROBO_RF_DATA_LINK:
		case FT_ROBO_IF_OVER_RF:
			usb_get_string_simple(hFt->device, 1, buffer, 128);
		break;
	}

	return buffer;
}


/**
 * @brief Gets the short name of the Interface
 *
 * Will return the short name of a fischertechnik USB device.
 * The allocated space should be freed with free() later.
 *
 * @param hFt Handle of the Interface
 * @return Pointer to the string with the name
 */
char *GetFtShortNameStrg(FT_HANDLE hFt) {
	char *buffer = (char *)malloc(128);
	memset(buffer, '\0', 128);

	if (hFt == NULL) {
		fprintf(stderr, "GetFtFirmware: No such device\n");
	}

	switch (hFt->type) {
		case FT_ROBO_IF_USB:
		case FT_ROBO_RF_DATA_LINK:
		case FT_ROBO_IF_OVER_RF:
			usb_get_string_simple(hFt->device, 5, buffer, 128);
			break;
	}

	return buffer;
}


/**
 * @brief Gets the long name of the Interface
 *
 * Will return the long name of a fischertechnik USB device.
 * The allocated space should be freed with free() later.
 *
 * @param hFt Handle of the Interface
 * @return Pointer to the string with the name
 */
char *GetFtLongNameStrg(FT_HANDLE hFt) {
	char *buffer = (char *)malloc(128);
	memset(buffer, '\0', 128);

	if (hFt == NULL) {
		fprintf(stderr, "GetFtFirmware: No such device\n");
	}
	
	switch (hFt->type) {
		case FT_ROBO_IF_USB:
		case FT_ROBO_RF_DATA_LINK:
		case FT_ROBO_IF_OVER_RF:
			usb_get_string_simple(hFt->device, 2, buffer, 128);
			break;
	}

	return buffer;
}


/**
 * @brief Tells if we successfuly got a connection to the Interface
 *
 * @param hFt Handle of the Interface
 * @return 0 if the Interface is not connected
 */
char IsFtInterfaceConnected(FT_HANDLE hFt) {
	return hFt->interface_connected;
}


/**
 * @brief Gets the description of an error
 *
 * Will return a description of an error.
 * The allocated space should be freed with free() later.
 *
 * The return value is the constant as string if parameter dwTyp is 0,
 * else a verbose description of the error.
 *
 * @param dwErrorCode Error Code
 * @param dwTyp Type of the return value (see description) 
 * @return Pointer to a string (see description)
 */
char *GetFtLibErrorString(long int dwErrorCode, long int dwTyp) {
	char *buffer = (char *)malloc(128);

	switch(dwErrorCode) {
		case FTLIB_ERR_IF_NO_PROGRAM:
			if (dwTyp) strncpy(buffer, "There is no program stored to work with", 128);
			else strncpy(buffer, "FTLIB_ERR_IF_NO_PROGRAM", 128);
			break;
		case FTLIB_ERR_SUCCESS:
			if (dwTyp) strncpy(buffer, "Everything is fine", 128);
			else strncpy(buffer, "FTLIB_ERR_SUCCESS", 128);
			break;
		case FTLIB_ERR_THREAD_IS_RUNNING:
			if (dwTyp) strncpy(buffer, "Thread has been started successfully", 128);
			else strncpy(buffer, "FTLIB_ERR_THREAD_IS_RUNNING", 128);
			break;
		case FTLIB_ERR_DOWNLOAD:
			if (dwTyp) strncpy(buffer, "Failed to upload the program", 128);
			else strncpy(buffer, "FTLIB_ERR_DOWNLOAD", 128);
			break;
		case FTLIB_ERR_DOWNLOAD_WRONG_MEM_BLOCK:
			if (dwTyp) strncpy(buffer, "Bad target to upload the program to", 128);
			else strncpy(buffer, "FTLIB_ERR_DOWNLOAD_WRONG_MEM_BLOCK", 128);
			break;
		case FTLIB_ERR_INVALID_PARAM:
			if (dwTyp) strncpy(buffer, "A parameter specified has a wrong value", 128);
			else strncpy(buffer, "FTLIB_ERR_INVALID_PARAM", 128);
			break;
		case FTLIB_ERR_LIB_IS_INITIALIZED:
			if (dwTyp) strncpy(buffer, "This library has been initialized", 128);
			else strncpy(buffer, "FTLIB_ERR_LIB_IS_INITIALIZED", 128);
			break;
		case FTLIB_ERR_NOT_SUPPORTED:
			if (dwTyp) strncpy(buffer, "The requested action is not supported", 128);
			else strncpy(buffer, "FTLIB_ERR_NOT_SUPPORTED", 128);
			break;
		case FTLIB_ERR_PORT_NUMBER_IS_NULL:
			if (dwTyp) strncpy(buffer, "No handle given", 128);
			else strncpy(buffer, "FTLIB_ERR_PORT_NUMBER_IS_NULL", 128);
			break;
		case FTLIB_ERR_THREAD_NOT_RUNNING:
			if (dwTyp) strncpy(buffer, "Unable to start the thread", 128);
			else strncpy(buffer, "FTLIB_ERR_THREAD_NOT_RUNNING", 128);
			break;
		default:
			strncpy(buffer, "Unknown", 128);
	}

	return buffer;
}


/** \cond doxygen ignore start */
//! \todo
long int SetFtDeviceCommMode(FT_HANDLE hFt, long int dwMode, long int dwParameter, unsigned short *puiValue) {
	return 0;
}


//! \todo
long int GetFtDeviceSetting(FT_HANDLE hFt, FT_SETTING *pSet) {
	return 0;
}


//! \todo
long int SetFtDeviceSetting(FT_HANDLE hFt, FT_SETTING *pSet) {
	return 0;
}


//! \todo
long int SendFtMessage(FT_HANDLE hFt, unsigned char bHwId, unsigned char bSubId, long int dwMessage, long int dwWaitTime, long int dwOption) {
	return 0;
}


//! \todo
long int ClearFtMessageBuffer(FT_HANDLE hFt) {
	return 0;
}


//! \todo
long int GetFtMemoryLayout(FT_HANDLE hFt, unsigned char* pbArray, long int dwSize) {
	return 0;
}


//! \todo
long int GetFtMemoryData(FT_HANDLE hFt, unsigned char * pbArray, long int dwSize, long int dwAddress) {
	return 0;
}


//! \todo
long int WriteFtMemoryData(FT_HANDLE hFt, long int dwData, long int dwAddress) {
	return 0;
}
/** \endcond doxygen ignore end */

