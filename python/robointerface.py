#!/usr/bin/python
"""Open Source Library for the fischertechnik ROBO Interface.

Copyright (C) 2007 Erik Andresen erik@vontaene.de
License: LGPL
"""


# won't show in pydoc:
"""
This library is free software; you can redistribute it and/or
modify it under the terms of the GNU Lesser General Public
License as published by the Free Software Foundation; either
version 2.1 of the License, or (at your option) any later version.

This library is distributed in the hope that it will be useful,
but WITHOUT ANY WARRANTY; without even the implied warranty of
MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU
Lesser General Public License for more details.

You should have received a copy of the GNU Lesser General Public
License along with this library; if not, write to the Free Software
Foundation, Inc., 51 Franklin Street, Fifth Floor, Boston, MA  02110-1301  USA
 
"""

import sys
import ctypes.util
from ctypes import *

class _FT_TRANSFER_AREA(Structure):
	"""Python wrapper for the ftlib transfer area"""
	_fields_ = [
		("E_Main", c_ubyte),
		("E_Sub1", c_ubyte),
		("E_Sub2", c_ubyte),
		("E_Sub3", c_ubyte),
		("rsvd1", c_ubyte*8),
		("Distance", c_ubyte),
		("rsvd2", c_ubyte),
		("IRKeys", c_ubyte),
		("res_1", c_ubyte),
		("AX", c_ushort),
		("AY", c_ushort),
		("A1", c_ushort),
		("A2", c_ushort),
		("AZ", c_ushort),
		("AV", c_ushort),
		("D1", c_ushort),
		("D2", c_ushort),
		("AXS1", c_ushort),
		("AXS2", c_ushort),
		("AXS3", c_ushort),
		("DS1", c_ushort),
		("DS2", c_ushort),
		("ZE", c_ushort),
		("rsvd3", c_ubyte*4),
		("Timer1ms", c_ushort),
		("Timer10ms", c_ushort),
		("Timer100ms", c_ushort),
		("Timer1s", c_ushort),
		("Timer10s", c_ushort),
		("Timer1min", c_ushort),
		("res_bF", c_ushort),
		("res_bT", c_ubyte),
		("resvd4", c_ubyte*1),
		("M_Main", c_ubyte),
		("M_Sub1", c_ubyte),
		("M_Sub2", c_ubyte),
		("M_Sub3", c_ubyte),
		("rsvd5", c_ubyte*4),
		("MES_Main", c_ubyte),
		("MES_Sub1", c_ubyte),
		("MES_Sub2", c_ubyte),
		("MES_Sub3", c_ubyte),
		("rsvd6", c_ubyte*1),
		("reserverd_l1", c_ubyte),
		("reserverd_l2", c_ubyte),
		("reserverd_l3", c_ubyte),
		("MPWM_Main", c_ubyte*8),
		("MPWM_Sub1", c_ubyte*8),
		("MPWM_Sub2", c_ubyte*8),
		("MPWM_Sub3", c_ubyte*8),
		("rsvd7", c_ubyte*32),
		("A1S1", c_ushort),
		("A1S2", c_ushort),
		("A1S3", c_ushort),
		("AVS1", c_ushort),
		("AVS2", c_ushort),
		("AVS3", c_ushort),
		("rsvd8", c_ubyte*4),
		("AX_R", c_ushort),
		("AY_R", c_ushort),
		("AXS1_R", c_ushort),
		("AXS2_R", c_ushort),
		("AXS3_R", c_ushort),
		("rsvd10", c_ubyte*54),
		("Mode", c_ubyte),
		("MPWM_Update", c_ubyte),
		("TransferAktiv", c_ubyte),
		("rsvd11", c_ubyte*3),
		("BudModules", c_ubyte),
		("SlotModule1", c_ubyte),
		("SlotModule2", c_ubyte),
		("rsvd12", c_ubyte*7),
		("ChangeEg", c_ubyte),
		("ChangeAn", c_ubyte),
		("ChangeIr", c_ubyte),
		("rsvd13", c_ubyte*13),
		("E16_Main", c_ubyte*8),
		("E16_Sub1", c_ubyte*8),
		("E16_Sub2", c_ubyte*8),
		("E16_Sub3", c_ubyte*8),
		("Distance16", c_ushort*2),
		("rsvd14", c_ubyte*12),
		("IRKeys16", c_ushort*11),
		("rsvd15", c_ubyte*15),
		("IRKeys16Code1", c_ushort*11),
		("rsvd16", c_ubyte*10),
		("IRKeys16Code2", c_ushort*11),
		("rsvd17", c_ubyte*10),
		("RfStatus", c_ushort),
		("RfPower", c_ushort),
		("RfError", c_ushort),
		("MsgNumInBuffer", c_ushort),
		("RfModulNr", c_ushort),
		("rsvd19", c_ubyte*2),
		("dwTc", c_long),
		("rsvd20", c_ubyte*64),
	]	


def GetNumFtUsbDevices():
	"""Get the count of found ft Interfaces over USB.

	If we find a Robo RF Data Link we will count the devices attached to it instead
	
	Warning:
	Do not call this function while an USB Interface is active!
	If you call this function it should be the first you do.
	However if you need to call this function in the middle of the program,
	close all open Interfaces first.

	Returns Number of ft Interface devices on the USB bus found.
	"""
	sLibName = ctypes.util.find_library("roboint")
	if not sLibName:
		print >> sys.stderr, "Error: Can't find Library libroboint"
	else:
		lib = cdll.LoadLibrary(sLibName)
		lib.InitFtUsbDeviceList()
		return lib.GetNumFtUsbDevice()
	return 0


class RoboInterface:
	"""class for access to the Interface

	This is a wrapper class.
	The real action will be done in the C-lib below us.


	Example usage:
	
	from robointerface import *
	from time import sleep

	ri = RoboInterface() # Open the first ft USB device

	ri.SetMotor(1, 'r', 4) # Motor 1 slow right
	sleep(1)
	ri.SetMotor(1, 'l') # Motor 1 left with max speed

	while not ri.Digital(1): # wait until endpoint at digital
		time.sleep(0.001)		# input 1 is reached

	ri.SetMotor(1, 's') # Motor 1 stop

	ri.close()


	Public module constants:

	FT_INTELLIGENT_IF	-- intelligent interface
	FT_INTELLIGENT_IF_SLAVE	-- intelligent interface with slave
	FT_ROBO_IF_IIM		-- Robo Interface in intelligent interface mode
	FT_ROBO_IF_USB		-- Robo Interface over USB
	FT_ROBO_IF_COM		-- Robo Interface over serial
	FT_ROBO_IF_OVER_RF	-- Robo Interface over RF Module
	FT_ROBO_IO_EXTENSION	-- Robo IO Extension
	FT_ROBO_RF_DATA_LINK	-- Robo RF Data Link

	Public module variables:

	kTolerance		-- Range of tolerance for distance sensors D1 and D2.
	kLevel			-- Threshold for distance sensors D1 and D2.
	kRepeat			-- Repition value for distance sensors D1 and D2.

	"""

	FT_AUTO_TYPE                =   1
	FT_INTELLIGENT_IF           =  10
	FT_INTELLIGENT_IF_SLAVE     =  20
	FT_ROBO_IF_IIM              =  50
	FT_ROBO_IF_USB              =  60
	FT_ROBO_IF_COM              =  70
	FT_ROBO_IF_OVER_RF          =  80
	FT_ROBO_IO_EXTENSION        =  90
	FT_ROBO_LT_CONTROLLER       =  91
	FT_ROBO_RF_DATA_LINK	    = 110
	ROBO_CONNECT_BOX	    = 200

	# Distance Input settings
	kTolerance = (20, 20)
	kLevel = (100, 100)
	kRepeat = (3, 3)

	def __init__(self, iDevice=0, serialDevice=None, SerialType=FT_ROBO_IF_COM, bEnableDist=False, bStartTransferArea=True, iUSBSerial=0):
		"""Constructor

		In USB mode it will initiate and scan the USB bus,
		in serial mode it will configure the serial.

		It both modes, the desired device will be opened and the
		communication Thread will be started.

		Keyword arguments:
		iDevice		-- USB Device to use. 0 will be the first
				   Interface found.
		iUSBSerial	-- Open the USB Device with this serial number
		serialDevice	-- Use a serial device: Don't use USB.
				   Can be "/dev/ttyS0" for example.
		SerialType 	-- Type of device at serial port, either
				   FT_INTELLIGENT_IF, FT_INTELLIGENT_IF_SLAVE
				   or FT_ROBO_IF_COM.
		bEnableDist	-- Enable D1 and D2 for use with the ft distance sensor
		bStartTransferArea -- Start the transfer area. Usually you want that.
		"""
		self.transfer_area = None
		sLibName = ctypes.util.find_library("roboint")
		if not sLibName:
			print >> sys.stderr, "Error: Can't find Library libroboint"
		else:
			self.lib = cdll.LoadLibrary(sLibName)

			# rs232
			if serialDevice:
				self.fthandle_p = self.lib.OpenFtCommDevice(serialDevice, SerialType, 10)
			# usb
			else:
				self.lib.InitFtUsbDeviceList()
				# by serial
				if iUSBSerial:
					self.fthandle_p = self.lib.GetFtUsbDeviceHandleSerialNr(iUSBSerial, self.FT_AUTO_TYPE)
				# by id
				else:
					self.fthandle_p = self.lib.GetFtUsbDeviceHandle(iDevice)
				self.lib.OpenFtUsbDevice(self.fthandle_p)

			# distance sensors
			if bEnableDist:
				self.lib.SetFtDistanceSensorMode(self.fthandle_p, 1, self.kTolerance[0], self.kTolerance[1], self.kLevel[0], self.kLevel[1], self.kRepeat[0], self.kRepeat[1])
			else:
				self.lib.SetFtDistanceSensorMode(self.fthandle_p, 0, self.kTolerance[0], self.kTolerance[1], self.kLevel[0], self.kLevel[1], self.kRepeat[0], self.kRepeat[1])

			self.transfer_area = None
			if bStartTransferArea:
				self.lib.StartFtTransferArea(self.fthandle_p, None)
				transfer_area_p = self.lib.GetFtTransferAreaAddress(self.fthandle_p)
				if transfer_area_p:
					self.transfer_area = cast(transfer_area_p, POINTER(_FT_TRANSFER_AREA)).contents
				else:
					print >> sys.stderr, "Error: I was unable to open the Interface"


	def hasInterface(self):
		"""Tells if we have a connection to the Interface

		Useful to call after the constructor., e.g:
		ri = RoboInterface()
		if ri.hasInterface():
			# do something here
		else:
			# sorry, failed to establish interface connection

		Returns a boolean value
		"""
		if self.transfer_area:
			return True
		return False


	def close(self):
		"""Close the connection

		Will close the connection to the Interface, kill the communication
		Thread and free the allocated memory.
		"""
		if hasattr(self, "lib"):
			if self.transfer_area:
				self.lib.StopFtTransferArea(self.fthandle_p)
			if self.fthandle_p:
				self.lib.CloseFtDevice(self.fthandle_p)
				self.fthandle_p = None


	def exit(self):
		"""Same as close
		"""
		return self.close()

	
	def SetMotor(self, iMotor, cDirection='', iSpeed=7):
		"""Set a Motor speed and direction

		Example Usage:
		SetMotor(1, 'r', 4) # slow right
		SetMotor(1, 'l') # left with max speed

		SetMotor(1, iSpeed=3) # slow left
		SetMotor(1, iSpeed=-5) # faster right

		Arguments:
		iMotor:		-- Motor to change 1..Max (1..4 for Master, 4..8 for Slave 1 etc)
		Keyword arguments:
		cDirection 	-- Either l (left), r (right) or s (stop)
		iSpeed 		-- Speed to use, defaults to max.
		"""
	
		if iMotor < 0 or iMotor > 16:
			print >> sys.stderr, "Warning: Bad Motor number!"

		if iSpeed > 7:
			print >> sys.stderr, "Warning: Bad speed value for Motor!"
			iSpeed = 7
		elif iSpeed < -7:
			print >> sys.stderr, "Warning: Bad speed value for Motor!"
			iSpeed = -7

		iDirection = 0x0
		if cDirection:
			switch = {
				'l': 0x1,
				'r': 0x2,
				's': 0x0
			}
			if switch.has_key(cDirection):
				iDirection = switch[cDirection]
			else:
				print >> sys.stderr, "Warning: Unknown Direction for Motor!"
		else:
			if iSpeed < 0:
				iDirection = 0x1
			elif iSpeed > 0:
				iDirection = 0x2
		iSpeed = abs(iSpeed)

		if self.transfer_area:
			if iMotor <= 4:
				self.transfer_area.M_Main &= ~(3<<(iMotor-1)*2)
				self.transfer_area.M_Main |= iDirection<<(iMotor-1)*2
				self.transfer_area.MPWM_Main[(iMotor-1)*2] = iSpeed
				self.transfer_area.MPWM_Main[(iMotor-1)*2 + 1] = iSpeed
			elif iMotor <= 8:
				iMotor -= 4
				self.transfer_area.M_Sub1 &= ~(3<<(iMotor-1)*2)
				self.transfer_area.M_Sub1 |= iDirection<<(iMotor-1)*2
				self.transfer_area.MPWM_Sub1[(iMotor-1)*2] = iSpeed
				self.transfer_area.MPWM_Sub1[(iMotor-1)*2 + 1] = iSpeed
			elif iMotor <= 12:
				iMotor -= 8
				self.transfer_area.M_Sub2 &= ~(3<<(iMotor-1)*2)
				self.transfer_area.M_Sub2 |= iDirection<<(iMotor-1)*2
				self.transfer_area.MPWM_Sub2[(iMotor-1)*2] = iSpeed
				self.transfer_area.MPWM_Sub2[(iMotor-1)*2 + 1] = iSpeed
			elif iMotor <= 16:
				iMotor -= 12
				self.transfer_area.M_Sub3 &= ~(3<<(iMotor-1)*2)
				self.transfer_area.M_Sub3 |= iDirection<<(iMotor-1)*2
				self.transfer_area.MPWM_Sub3[(iMotor-1)*2] = iSpeed
				self.transfer_area.MPWM_Sub3[(iMotor-1)*2 + 1] = iSpeed


	def SetOutput(self, iOutput, iSpeed=7):
		"""Set an output with speed

		Arguments:
		iOutput:	-- Motor to change 1..Max
		Keyword arguments:
		iSpeed 		-- Speed to use, defaults to max.
		"""
		
		if iOutput < 0 or iOutput > 32:
			print >> sys.stderr, "Warning: Bad Output number!"
		
		if iSpeed > 7:
			print >> sys.stderr, "Warning: Bad speed value for Output!"
			iSpeed = 7
		elif iSpeed < 0:
			print >> sys.stderr, "Warning: Bad speed value for Output!"
			iSpeed = 0

		iSpeed = abs(iSpeed)

		if self.transfer_area:
			if iOutput <= 8:
				if iSpeed == 0:
					self.transfer_area.M_Main &= ~(1<<iOutput-1)
				else:
					self.transfer_area.M_Main |= (1<<iOutput-1)
				self.transfer_area.MPWM_Main[iOutput-1] = iSpeed
			elif iOutput <= 16:
				iOutput -= 8
				if iSpeed == 0:
					self.transfer_area.M_Sub1 &= ~(1<<iOutput-1)
				else:
					self.transfer_area.M_Sub1 |= (1<<iOutput-1)
				self.transfer_area.MPWM_Sub1[iOutput-1] = iSpeed
			elif iOutput <= 24:
				iOutput -= 16
				if iSpeed == 0:
					self.transfer_area.M_Sub2 &= ~(1<<iOutput-1)
				else:
					self.transfer_area.M_Sub2 |= (1<<iOutput-1)
				self.transfer_area.MPWM_Sub2[iOutput-1] = iSpeed
			elif iOutput <= 32:
				iOutput -= 24
				if iSpeed == 0:
					self.transfer_area.M_Sub3 &= ~(1<<iOutput-1)
				else:
					self.transfer_area.M_Sub3 |= (1<<iOutput-1)
				self.transfer_area.MPWM_Sub3[iOutput-1] = iSpeed


	def Digital(self, iNum):
		"""Same as GetInput()

		see GetInput()
		"""
		return self.GetInput(iNum)


	def GetInput(self, iNum):
		"""Gets the state of a digital input

		Arguments:
		iNum -- Digital Input to read 1..Max

		Will return 1 or 0
		"""
		if self.transfer_area:
			if iNum <= 8:
				return (self.transfer_area.E_Main & (1<<(iNum-1))) >> (iNum-1)
			elif iNum <= 16:
				iNum -= 8
				return (self.transfer_area.E_Sub1 & (1<<(iNum-1))) >> (iNum-1)
			elif iNum <= 24:
				iNum -= 16
				return (self.transfer_area.E_Sub3 & (1<<(iNum-1))) >> (iNum-1)
			elif iNum <= 32:
				iNum -= 24
				return (self.transfer_area.E_Sub3 & (1<<(iNum-1))) >> (iNum-1)

		return 0

	
	def GetAX(self):
		"""Get the value of AX (Analog resistor input)

		Will return a number between 0 and 1024
		"""
		if self.transfer_area:
			return self.transfer_area.AX
		return 0

	
	def GetAY(self):
		"""Get the value of AY (Analog resistor input)

		Will return a number between 0 and 1024
		"""
		if self.transfer_area:
			return self.transfer_area.AY
		return 0

	
	def GetAZ(self):
		"""Get the value of AZ (Analog resistor input)

		Will return a number between 0 and 1024
		"""
		if self.transfer_area:
			return self.transfer_area.AZ
		return 0

	
	def GetA1(self):
		"""Get the value of A1 (Analog voltage input)

		Will return a number between 0 and 1024
		"""
		if self.transfer_area:
			return self.transfer_area.A1
		return 0
	
	
	def GetA2(self):
		"""Get the value of A2 (Analog voltage input)

		Will return a number between 0 and 1024
		"""
		if self.transfer_area:
			return self.transfer_area.A2
		return 0
	
	
	def GetD1(self):
		"""Get the value of D1 (Analog voltage or distance input)

		Will return a number between 0 and 1024
		"""
		if self.transfer_area:
			return self.transfer_area.D1
		return 0
	
	
	def GetD2(self):
		"""Get the value of D2 (Analog voltage or distance input)

		Will return a number between 0 and 1024
		"""
		if self.transfer_area:
			return self.transfer_area.D2
		return 0

	def av_to_v(self, av):
		"""Converts analog value 0..1023 in voltage
		"""
		if self.GetDeviceType() in [self.FT_ROBO_IO_EXTENSION, self.FT_ROBO_LT_CONTROLLER]:
			return 0.03*av

		return 8.63*av-1775
	
	def GetAV(self):
		"""Get the value of AV (power supply)

		Will return a number between 0 and 1024
		"""
		if self.transfer_area:
			return self.av_to_v(self.transfer_area.AV)
		return 0
	
	
	def GetAV_Slave1(self):
		"""Get the value of AV of Slave 1 (power supply)

		Will return a number between 0 and 1024
		"""
		if self.transfer_area:
			return self.av_to_v(self.transfer_area.AVS1)
		return 0


	def GetAV_Slave2(self):
		"""Get the value of AV of Slave 2 (power supply)

		Will return a number between 0 and 1024
		"""
		if self.transfer_area:
			return self.av_to_v(self.transfer_area.AVS2)
		return 0


	def GetAV_Slave3(self):
		"""Get the value of AV of Slave 3 (power supply)

		Will return a number between 0 and 1024
		"""
		if self.transfer_area:
			return self.av_to_v(self.transfer_area.AVS3)
		return 0

	
	def GetAX_Slave1(self):
		"""Get the value of AX of Slave 1 (analog resistor input)

		Will return a number between 0 and 1024
		"""
		if self.transfer_area:
			return self.transfer_area.AXS1
		return 0

	
	def GetAX_Slave2(self):
		"""Get the value of AX of Slave 2 (analog resistor input)

		Will return a number between 0 and 1024
		"""
		if self.transfer_area:
			return self.transfer_area.AXS2
		return 0
	
	
	def GetAX_Slave3(self):
		"""Get the value of AX of Slave 3 (analog resistor input)

		Will return a number between 0 and 1024
		"""
		if self.transfer_area:
			return self.transfer_area.AXS3
		return 0

	
	def GetIR(self):
		"""Get the last pressed IR key

		Will return last pressed IR key
		"""
		if self.transfer_area:
			return self.transfer_area.IRKeys
		return 0


	def GetDeviceType(self):
		"""Returns type of the interface

		This function will return the type of the interface,
		which is one of
		NO_FT_DEVICE, FT_INTELLIGENT_IF, FT_INTELLIGENT_IF_SLAVE,
		FT_ROBO_IF_COM, FT_ROBO_IF_USB, FT_ROBO_IF_IIM, FT_ROBO_IF_OVER_RF, 
		FT_ROBO_IO_EXTENSION or FT_ROBO_RF_DATA_LINK
		"""
		return self.lib.GetFtDeviceTyp(self.fthandle_p)


	def GetDeviceTypeString(self):
		"""Returns a string that identifies this interface with human words

		This function will return a human readable string like "Robo Interface"
		you can work with.
		"""
		s = create_string_buffer('\0' * 128)
		self.lib.GetFtDeviceTypeString(self.fthandle_p, s, 128)
		return s.value


	def __del__(self):
		self.close()


	def GetNumDevices(self):
		"""Get the number of attached devices to the Interface

		Will return the number of attached devices.
		"""
		return self.transfer_area.BusModules


	def IsConnected(self):
		"""Tells if we successfuly got a connection to the Interface

		Will return 0 if the interface is not responding
		"""
		return self.lib.IsFtInterfaceConnected(self.fthandle_p)

