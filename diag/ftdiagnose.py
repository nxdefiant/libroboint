#!/usr/bin/python


import sys
from PyQt4 import QtCore, QtGui

from ftdiagnose_ui import Ui_diag
from ftdiagnose_open_ui import Ui_Dialog

from robointerface import *
from time import sleep
from threading import Thread


"""
TODO:
-check if we can do most stuff here with a loop instead of this long source
"""


class OpenForm(QtGui.QDialog):
	def __init__(self, parent=None):
		self.parentForm = parent
		QtGui.QWidget.__init__(self, parent)
		self.ui = Ui_Dialog()
		self.ui.setupUi(self)

		QtCore.QObject.connect(self.ui.buttonBox,QtCore.SIGNAL("accepted()"), self.pressed_ok)
		QtCore.QObject.connect(self.ui.buttonBox,QtCore.SIGNAL("rejected()"), self.pressed_cancel)
		QtCore.QObject.connect(self.ui.radioButton_USB,QtCore.SIGNAL("clicked()"), self.radio_usb)
		QtCore.QObject.connect(self.ui.radioButton_Serial,QtCore.SIGNAL("clicked()"), self.radio_serial)
		QtCore.QObject.connect(self.ui.radioButton_Serial_II,QtCore.SIGNAL("clicked()"), self.radio_serial_ii)
		QtCore.QObject.connect(self.ui.radioButton_Serial_II_Slave,QtCore.SIGNAL("clicked()"), self.radio_serial_ii_slave)
		QtCore.QObject.connect(self.ui.lineEdit,QtCore.SIGNAL("textChanged(QString)"), self.serial_select)
		QtCore.QObject.connect(self.ui.comboBox,QtCore.SIGNAL("currentIndexChanged(int)"), self.usb_select)
		QtCore.QObject.connect(self.ui.checkBox,QtCore.SIGNAL("toggled(bool)"), self.toggle_dist)

		for i in range(GetNumFtUsbDevices()):
			pCurInterface = RoboInterface(i, bStartTransferArea=False)
			s = pCurInterface.GetDeviceTypeString()
			self.ui.comboBox.addItem("%d - %s" % (i, s))
			pCurInterface.close()
			sleep(0.1) # sleep, else usb will fail
		
	def pressed_ok(self):
		self.parentForm.open_device_selected()
		self.close()
	def pressed_cancel(self):
		self.close()
	def radio_usb(self):
		self.parentForm.selectDeviceType = 0
	def radio_serial(self):
		self.parentForm.selectDeviceType = 1
	def radio_serial_ii(self):
		self.parentForm.selectDeviceType = 2
	def radio_serial_ii_slave(self):
		self.parentForm.selectDeviceType = 3
	def serial_select(self, s):
		self.parentForm.sSerialDevice = s
	def usb_select(self, i):
		self.parentForm.iUSBDevice = i
	def toggle_dist(self, b):
		self.parentForm.bEnableDist = b


class DiagForm(QtGui.QMainWindow, Thread):
	def __init__(self, parent=None):
		QtGui.QWidget.__init__(self, parent)
		self.ui = Ui_diag()
		self.ui.setupUi(self)
		
		# init stuff
		self.pInterface = None
		self.bRunThread = 0
		self.sSerialDevice = "/dev/ttyS0"
		self.iUSBDevice = 0
		self.selectDeviceType = 0 # 0 = USB, 1 = Robo Serial, 2 = II, 3 = II+Slave
		self.bEnableDist = False
		self.ui.tabWidget.setTabEnabled(0, 0)
		self.ui.tabWidget.setTabEnabled(1, 0)
		self.ui.tabWidget.setTabEnabled(2, 0)
		self.ui.tabWidget.setTabEnabled(3, 0)

		# here we connect signals with our slots
		QtCore.QObject.connect(self.ui.actionOpen,QtCore.SIGNAL("triggered()"), self.action_open)
		QtCore.QObject.connect(self.ui.actionClose_Interface,QtCore.SIGNAL("triggered()"), self.action_close)
		QtCore.QObject.connect(self,QtCore.SIGNAL("SetAnalogSignal()"), self.set_AnalogValues)
		QtCore.QObject.connect(self.ui.pushButton_Stop,QtCore.SIGNAL("clicked()"), self.emerg_stop)
		QtCore.QObject.connect(self.ui.pushButton_Stop_2,QtCore.SIGNAL("clicked()"), self.emerg_stop)
		QtCore.QObject.connect(self.ui.pushButton_Stop_3,QtCore.SIGNAL("clicked()"), self.emerg_stop)
		QtCore.QObject.connect(self.ui.pushButton_Stop_4,QtCore.SIGNAL("clicked()"), self.emerg_stop)

		# Outputs Main
		QtCore.QObject.connect(self.ui.dial_MainBoth_1,QtCore.SIGNAL("valueChanged(int)"), self.set_engineBoth_1)
		QtCore.QObject.connect(self.ui.dial_MainLeft_1,QtCore.SIGNAL("valueChanged(int)"), self.set_engineLeft_1)
		QtCore.QObject.connect(self.ui.dial_MainRight_1,QtCore.SIGNAL("valueChanged(int)"), self.set_engineRight_1)
		QtCore.QObject.connect(self.ui.dial_MainBoth_2,QtCore.SIGNAL("valueChanged(int)"), self.set_engineBoth_2)
		QtCore.QObject.connect(self.ui.dial_MainLeft_2,QtCore.SIGNAL("valueChanged(int)"), self.set_engineLeft_2)
		QtCore.QObject.connect(self.ui.dial_MainRight_2,QtCore.SIGNAL("valueChanged(int)"), self.set_engineRight_2)
		QtCore.QObject.connect(self.ui.dial_MainBoth_3,QtCore.SIGNAL("valueChanged(int)"), self.set_engineBoth_3)
		QtCore.QObject.connect(self.ui.dial_MainLeft_3,QtCore.SIGNAL("valueChanged(int)"), self.set_engineLeft_3)
		QtCore.QObject.connect(self.ui.dial_MainRight_3,QtCore.SIGNAL("valueChanged(int)"), self.set_engineRight_3)
		QtCore.QObject.connect(self.ui.dial_MainBoth_4,QtCore.SIGNAL("valueChanged(int)"), self.set_engineBoth_4)
		QtCore.QObject.connect(self.ui.dial_MainLeft_4,QtCore.SIGNAL("valueChanged(int)"), self.set_engineLeft_4)
		QtCore.QObject.connect(self.ui.dial_MainRight_4,QtCore.SIGNAL("valueChanged(int)"), self.set_engineRight_4)

		QtCore.QObject.connect(self.ui.dial_Slave1Both_1,QtCore.SIGNAL("valueChanged(int)"), self.set_engineBoth_5)
		QtCore.QObject.connect(self.ui.dial_Slave1Left_1,QtCore.SIGNAL("valueChanged(int)"), self.set_engineLeft_5)
		QtCore.QObject.connect(self.ui.dial_Slave1Right_1,QtCore.SIGNAL("valueChanged(int)"), self.set_engineRight_5)
		QtCore.QObject.connect(self.ui.dial_Slave1Both_2,QtCore.SIGNAL("valueChanged(int)"), self.set_engineBoth_6)
		QtCore.QObject.connect(self.ui.dial_Slave1Left_2,QtCore.SIGNAL("valueChanged(int)"), self.set_engineLeft_6)
		QtCore.QObject.connect(self.ui.dial_Slave1Right_2,QtCore.SIGNAL("valueChanged(int)"), self.set_engineRight_6)
		QtCore.QObject.connect(self.ui.dial_Slave1Both_3,QtCore.SIGNAL("valueChanged(int)"), self.set_engineBoth_7)
		QtCore.QObject.connect(self.ui.dial_Slave1Left_3,QtCore.SIGNAL("valueChanged(int)"), self.set_engineLeft_7)
		QtCore.QObject.connect(self.ui.dial_Slave1Right_3,QtCore.SIGNAL("valueChanged(int)"), self.set_engineRight_7)
		QtCore.QObject.connect(self.ui.dial_Slave1Both_4,QtCore.SIGNAL("valueChanged(int)"), self.set_engineBoth_8)
		QtCore.QObject.connect(self.ui.dial_Slave1Left_4,QtCore.SIGNAL("valueChanged(int)"), self.set_engineLeft_8)
		QtCore.QObject.connect(self.ui.dial_Slave1Right_4,QtCore.SIGNAL("valueChanged(int)"), self.set_engineRight_8)
		
		QtCore.QObject.connect(self.ui.dial_Slave2Both_1,QtCore.SIGNAL("valueChanged(int)"), self.set_engineBoth_9)
		QtCore.QObject.connect(self.ui.dial_Slave2Left_1,QtCore.SIGNAL("valueChanged(int)"), self.set_engineLeft_9)
		QtCore.QObject.connect(self.ui.dial_Slave2Right_1,QtCore.SIGNAL("valueChanged(int)"), self.set_engineRight_9)
		QtCore.QObject.connect(self.ui.dial_Slave2Both_2,QtCore.SIGNAL("valueChanged(int)"), self.set_engineBoth_10)
		QtCore.QObject.connect(self.ui.dial_Slave2Left_2,QtCore.SIGNAL("valueChanged(int)"), self.set_engineLeft_10)
		QtCore.QObject.connect(self.ui.dial_Slave2Right_2,QtCore.SIGNAL("valueChanged(int)"), self.set_engineRight_10)
		QtCore.QObject.connect(self.ui.dial_Slave2Both_3,QtCore.SIGNAL("valueChanged(int)"), self.set_engineBoth_11)
		QtCore.QObject.connect(self.ui.dial_Slave2Left_3,QtCore.SIGNAL("valueChanged(int)"), self.set_engineLeft_11)
		QtCore.QObject.connect(self.ui.dial_Slave2Right_3,QtCore.SIGNAL("valueChanged(int)"), self.set_engineRight_11)
		QtCore.QObject.connect(self.ui.dial_Slave2Both_4,QtCore.SIGNAL("valueChanged(int)"), self.set_engineBoth_12)
		QtCore.QObject.connect(self.ui.dial_Slave2Left_4,QtCore.SIGNAL("valueChanged(int)"), self.set_engineLeft_12)
		QtCore.QObject.connect(self.ui.dial_Slave2Right_4,QtCore.SIGNAL("valueChanged(int)"), self.set_engineRight_12)

		QtCore.QObject.connect(self.ui.dial_Slave3Both_1,QtCore.SIGNAL("valueChanged(int)"), self.set_engineBoth_13)
		QtCore.QObject.connect(self.ui.dial_Slave3Left_1,QtCore.SIGNAL("valueChanged(int)"), self.set_engineLeft_13)
		QtCore.QObject.connect(self.ui.dial_Slave3Right_1,QtCore.SIGNAL("valueChanged(int)"), self.set_engineRight_13)
		QtCore.QObject.connect(self.ui.dial_Slave3Both_2,QtCore.SIGNAL("valueChanged(int)"), self.set_engineBoth_14)
		QtCore.QObject.connect(self.ui.dial_Slave3Left_2,QtCore.SIGNAL("valueChanged(int)"), self.set_engineLeft_14)
		QtCore.QObject.connect(self.ui.dial_Slave3Right_2,QtCore.SIGNAL("valueChanged(int)"), self.set_engineRight_14)
		QtCore.QObject.connect(self.ui.dial_Slave3Both_3,QtCore.SIGNAL("valueChanged(int)"), self.set_engineBoth_15)
		QtCore.QObject.connect(self.ui.dial_Slave3Left_3,QtCore.SIGNAL("valueChanged(int)"), self.set_engineLeft_15)
		QtCore.QObject.connect(self.ui.dial_Slave3Right_3,QtCore.SIGNAL("valueChanged(int)"), self.set_engineRight_15)
		QtCore.QObject.connect(self.ui.dial_Slave3Both_4,QtCore.SIGNAL("valueChanged(int)"), self.set_engineBoth_16)
		QtCore.QObject.connect(self.ui.dial_Slave3Left_4,QtCore.SIGNAL("valueChanged(int)"), self.set_engineLeft_16)
		QtCore.QObject.connect(self.ui.dial_Slave3Right_4,QtCore.SIGNAL("valueChanged(int)"), self.set_engineRight_16)

	def emerg_stop(self):
		self.pInterface.SetMotor(1, iSpeed=0)
		self.ui.dial_MainLeft_1.setSliderPosition(0)
		self.ui.dial_MainRight_1.setSliderPosition(0)
		self.ui.dial_MainBoth_1.setSliderPosition(0)
		self.pInterface.SetMotor(2, iSpeed=0)
		self.ui.dial_MainLeft_2.setSliderPosition(0)
		self.ui.dial_MainRight_2.setSliderPosition(0)
		self.ui.dial_MainBoth_2.setSliderPosition(0)
		self.pInterface.SetMotor(3, iSpeed=0)
		self.ui.dial_MainLeft_3.setSliderPosition(0)
		self.ui.dial_MainRight_3.setSliderPosition(0)
		self.ui.dial_MainBoth_3.setSliderPosition(0)
		self.pInterface.SetMotor(4, iSpeed=0)
		self.ui.dial_MainLeft_4.setSliderPosition(0)
		self.ui.dial_MainRight_4.setSliderPosition(0)
		self.ui.dial_MainBoth_4.setSliderPosition(0)

		self.pInterface.SetMotor(5, iSpeed=0)
		self.ui.dial_Slave1Left_1.setSliderPosition(0)
		self.ui.dial_Slave1Right_1.setSliderPosition(0)
		self.ui.dial_Slave1Both_1.setSliderPosition(0)
		self.pInterface.SetMotor(6, iSpeed=0)
		self.ui.dial_Slave1Left_2.setSliderPosition(0)
		self.ui.dial_Slave1Right_2.setSliderPosition(0)
		self.ui.dial_Slave1Both_2.setSliderPosition(0)
		self.pInterface.SetMotor(7, iSpeed=0)
		self.ui.dial_Slave1Left_3.setSliderPosition(0)
		self.ui.dial_Slave1Right_3.setSliderPosition(0)
		self.ui.dial_Slave1Both_3.setSliderPosition(0)
		self.pInterface.SetMotor(8, iSpeed=0)
		self.ui.dial_Slave1Left_4.setSliderPosition(0)
		self.ui.dial_Slave1Right_4.setSliderPosition(0)
		self.ui.dial_Slave1Both_4.setSliderPosition(0)

		self.pInterface.SetMotor(9, iSpeed=0)
		self.ui.dial_Slave2Left_1.setSliderPosition(0)
		self.ui.dial_Slave2Right_1.setSliderPosition(0)
		self.ui.dial_Slave2Both_1.setSliderPosition(0)
		self.pInterface.SetMotor(10, iSpeed=0)
		self.ui.dial_Slave2Left_2.setSliderPosition(0)
		self.ui.dial_Slave2Right_2.setSliderPosition(0)
		self.ui.dial_Slave2Both_2.setSliderPosition(0)
		self.pInterface.SetMotor(11, iSpeed=0)
		self.ui.dial_Slave2Left_3.setSliderPosition(0)
		self.ui.dial_Slave2Right_3.setSliderPosition(0)
		self.ui.dial_Slave2Both_3.setSliderPosition(0)
		self.pInterface.SetMotor(12, iSpeed=0)
		self.ui.dial_Slave2Left_4.setSliderPosition(0)
		self.ui.dial_Slave2Right_4.setSliderPosition(0)
		self.ui.dial_Slave2Both_4.setSliderPosition(0)

		self.pInterface.SetMotor(13, iSpeed=0)
		self.ui.dial_Slave3Left_1.setSliderPosition(0)
		self.ui.dial_Slave3Right_1.setSliderPosition(0)
		self.ui.dial_Slave3Both_1.setSliderPosition(0)
		self.pInterface.SetMotor(14, iSpeed=0)
		self.ui.dial_Slave3Left_2.setSliderPosition(0)
		self.ui.dial_Slave3Right_2.setSliderPosition(0)
		self.ui.dial_Slave3Both_2.setSliderPosition(0)
		self.pInterface.SetMotor(15, iSpeed=0)
		self.ui.dial_Slave3Left_3.setSliderPosition(0)
		self.ui.dial_Slave3Right_3.setSliderPosition(0)
		self.ui.dial_Slave3Both_3.setSliderPosition(0)
		self.pInterface.SetMotor(16, iSpeed=0)
		self.ui.dial_Slave3Left_4.setSliderPosition(0)
		self.ui.dial_Slave3Right_4.setSliderPosition(0)
		self.ui.dial_Slave3Both_4.setSliderPosition(0)

	def __del__(self):
		self.bRunThread = 0
		if self.pInterface:
			self.pInterface.close()
			self.pInterface = None

	def run(self):
		while(self.bRunThread and self.isVisible()):
			self.CheckDigitalInputs()
			self.CheckAnalogValues()
			sleep(0.1)
		self.ui.tabWidget.setEnabled(0)

	def action_open(self):
		self.action_close()
		self.openapp = OpenForm(parent=self)
		self.openapp.show()

	def open_device_selected(self):
		sSerialDevice = str(self.sSerialDevice)
		if self.selectDeviceType == 1:
			self.pInterface = RoboInterface(serialDevice=sSerialDevice, SerialType = RoboInterface.FT_ROBO_IF_COM)
		elif self.selectDeviceType == 2:
			self.pInterface = RoboInterface(serialDevice=sSerialDevice, SerialType = RoboInterface.FT_INTELLIGENT_IF)
		elif self.selectDeviceType == 3:
			self.pInterface = RoboInterface(serialDevice=sSerialDevice, SerialType = RoboInterface.FT_INTELLIGENT_IF_SLAVE)
		else:
			self.pInterface = RoboInterface(self.iUSBDevice, bEnableDist = self.bEnableDist)
		if not self.pInterface.transfer_area:
			self.pErrorBox = QtGui.QMessageBox.critical(None, "Error", "Unable to open selected Interface")
		else:
			self.ui.tabWidget.setEnabled(1)
			self.ui.tabWidget.setTabEnabled(0, 1)
			
			typ = self.pInterface.GetDeviceType()
			if typ == RoboInterface.FT_INTELLIGENT_IF_SLAVE:
				self.ui.tabWidget.setTabEnabled(1, 1)
			elif typ in [RoboInterface.FT_ROBO_IF_USB, RoboInterface.FT_ROBO_IF_OVER_RF, RoboInterface.FT_ROBO_RF_DATA_LINK]:
				self.ui.tabWidget.setTabEnabled(1, 1)
				self.ui.tabWidget.setTabEnabled(2, 1)
				self.ui.tabWidget.setTabEnabled(3, 1)
			Thread.__init__(self)
			self.bRunThread = 1
			self.start()
	
	def action_close(self):
		self.bRunThread = 0
		if self.pInterface:
			self.pInterface.close()
			self.pInterface = None
		self.ui.tabWidget.setTabEnabled(0, 0)
		self.ui.tabWidget.setTabEnabled(1, 0)
		self.ui.tabWidget.setTabEnabled(2, 0)
		self.ui.tabWidget.setTabEnabled(3, 0)
		self.ui.tabWidget.setEnabled(0)

	def set_AnalogValues(self):
		if self.pInterface:
			self.ui.progressBar_Voltage.setValue(self.pInterface.GetAV())
			self.ui.progressBar_Voltage_Slave1.setValue(self.pInterface.GetAV_Slave1())
			self.ui.progressBar_Voltage_Slave2.setValue(self.pInterface.GetAV_Slave2())
			self.ui.progressBar_Voltage_Slave3.setValue(self.pInterface.GetAV_Slave3())
			self.ui.lcdNumber_AX.display(self.pInterface.GetAX())
			self.ui.lcdNumber_AY.display(self.pInterface.GetAY())
			self.ui.lcdNumber_AZ.display(self.pInterface.GetAZ())
			self.ui.lcdNumber_A1.display(self.pInterface.GetA1())
			self.ui.lcdNumber_A2.display(self.pInterface.GetA2())
			self.ui.lcdNumber_D1.display(self.pInterface.GetD1())
			self.ui.lcdNumber_D2.display(self.pInterface.GetD2())
			self.ui.lcdNumber_IR.display(self.pInterface.GetIR())
			self.ui.lcdNumber_AX_Slave1.display(self.pInterface.GetAX_Slave1())
			self.ui.lcdNumber_AX_Slave2.display(self.pInterface.GetAX_Slave2())
			self.ui.lcdNumber_AX_Slave3.display(self.pInterface.GetAX_Slave3())

	def CheckAnalogValues(self):
		if self.pInterface:
			self.emit(QtCore.SIGNAL('SetAnalogSignal()'))

	def CheckDigitalInputs(self):
		if self.pInterface:
			if self.pInterface.IsConnected():
				self.ui.checkBoxConnection_Main.setCheckable(1)
				self.ui.checkBoxConnection_Main.setChecked(1)
				self.ui.checkBoxConnection_Slave1.setCheckable(1)
				self.ui.checkBoxConnection_Slave1.setChecked(1)
				self.ui.checkBoxConnection_Slave2.setCheckable(1)
				self.ui.checkBoxConnection_Slave2.setChecked(1)
				self.ui.checkBoxConnection_Slave3.setCheckable(1)
				self.ui.checkBoxConnection_Slave3.setChecked(1)
			else:
				self.ui.checkBoxConnection_Main.setChecked(0)
				self.ui.checkBoxConnection_Main.setCheckable(0)
				self.ui.checkBoxConnection_Slave1.setChecked(0)
				self.ui.checkBoxConnection_Slave1.setCheckable(0)
				self.ui.checkBoxConnection_Slave2.setChecked(0)
				self.ui.checkBoxConnection_Slave2.setCheckable(0)
				self.ui.checkBoxConnection_Slave3.setChecked(0)
				self.ui.checkBoxConnection_Slave3.setCheckable(0)

			if self.pInterface.Digital(1) and not self.ui.radioButton_MainDigital_1.isChecked():
				self.ui.radioButton_MainDigital_1.setCheckable(1)
				self.ui.radioButton_MainDigital_1.setChecked(1)
			elif not self.pInterface.Digital(1) and self.ui.radioButton_MainDigital_1.isChecked():
				self.ui.radioButton_MainDigital_1.setChecked(0)
				self.ui.radioButton_MainDigital_1.setCheckable(0)
			if self.pInterface.Digital(2) and not self.ui.radioButton_MainDigital_2.isChecked():
				self.ui.radioButton_MainDigital_2.setCheckable(1)
				self.ui.radioButton_MainDigital_2.setChecked(1)
			elif not self.pInterface.Digital(2) and self.ui.radioButton_MainDigital_2.isChecked():
				self.ui.radioButton_MainDigital_2.setChecked(0)
				self.ui.radioButton_MainDigital_2.setCheckable(0)
			if self.pInterface.Digital(3) and not self.ui.radioButton_MainDigital_3.isChecked():
				self.ui.radioButton_MainDigital_3.setCheckable(1)
				self.ui.radioButton_MainDigital_3.setChecked(1)
			elif not self.pInterface.Digital(3) and self.ui.radioButton_MainDigital_3.isChecked():
				self.ui.radioButton_MainDigital_3.setChecked(0)
				self.ui.radioButton_MainDigital_3.setCheckable(0)
			if self.pInterface.Digital(4) and not self.ui.radioButton_MainDigital_4.isChecked():
				self.ui.radioButton_MainDigital_4.setCheckable(1)
				self.ui.radioButton_MainDigital_4.setChecked(1)
			elif not self.pInterface.Digital(4) and self.ui.radioButton_MainDigital_4.isChecked():
				self.ui.radioButton_MainDigital_4.setChecked(0)
				self.ui.radioButton_MainDigital_4.setCheckable(0)
			if self.pInterface.Digital(5) and not self.ui.radioButton_MainDigital_5.isChecked():
				self.ui.radioButton_MainDigital_5.setCheckable(1)
				self.ui.radioButton_MainDigital_5.setChecked(1)
			elif not self.pInterface.Digital(5) and self.ui.radioButton_MainDigital_5.isChecked():
				self.ui.radioButton_MainDigital_5.setChecked(0)
				self.ui.radioButton_MainDigital_5.setCheckable(0)
			if self.pInterface.Digital(6) and not self.ui.radioButton_MainDigital_6.isChecked():
				self.ui.radioButton_MainDigital_6.setCheckable(1)
				self.ui.radioButton_MainDigital_6.setChecked(1)
			elif not self.pInterface.Digital(6) and self.ui.radioButton_MainDigital_6.isChecked():
				self.ui.radioButton_MainDigital_6.setChecked(0)
				self.ui.radioButton_MainDigital_6.setCheckable(0)
			if self.pInterface.Digital(7) and not self.ui.radioButton_MainDigital_7.isChecked():
				self.ui.radioButton_MainDigital_7.setCheckable(1)
				self.ui.radioButton_MainDigital_7.setChecked(1)
			elif not self.pInterface.Digital(7) and self.ui.radioButton_MainDigital_7.isChecked():
				self.ui.radioButton_MainDigital_7.setChecked(0)
				self.ui.radioButton_MainDigital_7.setCheckable(0)
			if self.pInterface.Digital(8) and not self.ui.radioButton_MainDigital_8.isChecked():
				self.ui.radioButton_MainDigital_8.setCheckable(1)
				self.ui.radioButton_MainDigital_8.setChecked(1)
			elif not self.pInterface.Digital(8) and self.ui.radioButton_MainDigital_8.isChecked():
				self.ui.radioButton_MainDigital_8.setChecked(0)
				self.ui.radioButton_MainDigital_8.setCheckable(0)

			if self.pInterface.Digital(9) and not self.ui.radioButton_Slave1Digital_1.isChecked():
				self.ui.radioButton_Slave1Digital_1.setCheckable(1)
				self.ui.radioButton_Slave1Digital_1.setChecked(1)
			elif not self.pInterface.Digital(9) and self.ui.radioButton_Slave1Digital_1.isChecked():
				self.ui.radioButton_Slave1Digital_1.setChecked(0)
				self.ui.radioButton_Slave1Digital_1.setCheckable(0)
			if self.pInterface.Digital(10) and not self.ui.radioButton_Slave1Digital_2.isChecked():
				self.ui.radioButton_Slave1Digital_2.setCheckable(1)
				self.ui.radioButton_Slave1Digital_2.setChecked(1)
			elif not self.pInterface.Digital(10) and self.ui.radioButton_Slave1Digital_2.isChecked():
				self.ui.radioButton_Slave1Digital_2.setChecked(0)
				self.ui.radioButton_Slave1Digital_2.setCheckable(0)
			if self.pInterface.Digital(11) and not self.ui.radioButton_Slave1Digital_3.isChecked():
				self.ui.radioButton_Slave1Digital_3.setCheckable(1)
				self.ui.radioButton_Slave1Digital_3.setChecked(1)
			elif not self.pInterface.Digital(11) and self.ui.radioButton_Slave1Digital_3.isChecked():
				self.ui.radioButton_Slave1Digital_3.setChecked(0)
				self.ui.radioButton_Slave1Digital_3.setCheckable(0)
			if self.pInterface.Digital(12) and not self.ui.radioButton_Slave1Digital_4.isChecked():
				self.ui.radioButton_Slave1Digital_4.setCheckable(1)
				self.ui.radioButton_Slave1Digital_4.setChecked(1)
			elif not self.pInterface.Digital(12) and self.ui.radioButton_Slave1Digital_4.isChecked():
				self.ui.radioButton_Slave1Digital_4.setChecked(0)
				self.ui.radioButton_Slave1Digital_4.setCheckable(0)
			if self.pInterface.Digital(13) and not self.ui.radioButton_Slave1Digital_5.isChecked():
				self.ui.radioButton_Slave1Digital_5.setCheckable(1)
				self.ui.radioButton_Slave1Digital_5.setChecked(1)
			elif not self.pInterface.Digital(13) and self.ui.radioButton_Slave1Digital_5.isChecked():
				self.ui.radioButton_Slave1Digital_5.setChecked(0)
				self.ui.radioButton_Slave1Digital_5.setCheckable(0)
			if self.pInterface.Digital(14) and not self.ui.radioButton_Slave1Digital_6.isChecked():
				self.ui.radioButton_Slave1Digital_6.setCheckable(1)
				self.ui.radioButton_Slave1Digital_6.setChecked(1)
			elif not self.pInterface.Digital(14) and self.ui.radioButton_Slave1Digital_6.isChecked():
				self.ui.radioButton_Slave1Digital_6.setChecked(0)
				self.ui.radioButton_Slave1Digital_6.setCheckable(0)
			if self.pInterface.Digital(15) and not self.ui.radioButton_Slave1Digital_7.isChecked():
				self.ui.radioButton_Slave1Digital_7.setCheckable(1)
				self.ui.radioButton_Slave1Digital_7.setChecked(1)
			elif not self.pInterface.Digital(15) and self.ui.radioButton_Slave1Digital_7.isChecked():
				self.ui.radioButton_Slave1Digital_7.setChecked(0)
				self.ui.radioButton_Slave1Digital_7.setCheckable(0)
			if self.pInterface.Digital(16) and not self.ui.radioButton_Slave1Digital_8.isChecked():
				self.ui.radioButton_Slave1Digital_8.setCheckable(1)
				self.ui.radioButton_Slave1Digital_8.setChecked(1)
			elif not self.pInterface.Digital(16) and self.ui.radioButton_Slave1Digital_8.isChecked():
				self.ui.radioButton_Slave1Digital_8.setChecked(0)
				self.ui.radioButton_Slave1Digital_8.setCheckable(0)

			if self.pInterface.Digital(17) and not self.ui.radioButton_Slave2Digital_1.isChecked():
				self.ui.radioButton_Slave2Digital_1.setCheckable(1)
				self.ui.radioButton_Slave2Digital_1.setChecked(1)
			elif not self.pInterface.Digital(17) and self.ui.radioButton_Slave2Digital_1.isChecked():
				self.ui.radioButton_Slave2Digital_1.setChecked(0)
				self.ui.radioButton_Slave2Digital_1.setCheckable(0)
			if self.pInterface.Digital(18) and not self.ui.radioButton_Slave2Digital_2.isChecked():
				self.ui.radioButton_Slave2Digital_2.setCheckable(1)
				self.ui.radioButton_Slave2Digital_2.setChecked(1)
			elif not self.pInterface.Digital(18) and self.ui.radioButton_Slave2Digital_2.isChecked():
				self.ui.radioButton_Slave2Digital_2.setChecked(0)
				self.ui.radioButton_Slave2Digital_2.setCheckable(0)
			if self.pInterface.Digital(19) and not self.ui.radioButton_Slave2Digital_3.isChecked():
				self.ui.radioButton_Slave2Digital_3.setCheckable(1)
				self.ui.radioButton_Slave2Digital_3.setChecked(1)
			elif not self.pInterface.Digital(19) and self.ui.radioButton_Slave2Digital_3.isChecked():
				self.ui.radioButton_Slave2Digital_3.setChecked(0)
				self.ui.radioButton_Slave2Digital_3.setCheckable(0)
			if self.pInterface.Digital(20) and not self.ui.radioButton_Slave2Digital_4.isChecked():
				self.ui.radioButton_Slave2Digital_4.setCheckable(1)
				self.ui.radioButton_Slave2Digital_4.setChecked(1)
			elif not self.pInterface.Digital(20) and self.ui.radioButton_Slave2Digital_4.isChecked():
				self.ui.radioButton_Slave2Digital_4.setChecked(0)
				self.ui.radioButton_Slave2Digital_4.setCheckable(0)
			if self.pInterface.Digital(21) and not self.ui.radioButton_Slave2Digital_5.isChecked():
				self.ui.radioButton_Slave2Digital_5.setCheckable(1)
				self.ui.radioButton_Slave2Digital_5.setChecked(1)
			elif not self.pInterface.Digital(21) and self.ui.radioButton_Slave2Digital_5.isChecked():
				self.ui.radioButton_Slave2Digital_5.setChecked(0)
				self.ui.radioButton_Slave2Digital_5.setCheckable(0)
			if self.pInterface.Digital(22) and not self.ui.radioButton_Slave2Digital_6.isChecked():
				self.ui.radioButton_Slave2Digital_6.setCheckable(1)
				self.ui.radioButton_Slave2Digital_6.setChecked(1)
			elif not self.pInterface.Digital(22) and self.ui.radioButton_Slave2Digital_6.isChecked():
				self.ui.radioButton_Slave2Digital_6.setChecked(0)
				self.ui.radioButton_Slave2Digital_6.setCheckable(0)
			if self.pInterface.Digital(23) and not self.ui.radioButton_Slave2Digital_7.isChecked():
				self.ui.radioButton_Slave2Digital_7.setCheckable(1)
				self.ui.radioButton_Slave2Digital_7.setChecked(1)
			elif not self.pInterface.Digital(23) and self.ui.radioButton_Slave2Digital_7.isChecked():
				self.ui.radioButton_Slave2Digital_7.setChecked(0)
				self.ui.radioButton_Slave2Digital_7.setCheckable(0)
			if self.pInterface.Digital(24) and not self.ui.radioButton_Slave2Digital_8.isChecked():
				self.ui.radioButton_Slave2Digital_8.setCheckable(1)
				self.ui.radioButton_Slave2Digital_8.setChecked(1)
			elif not self.pInterface.Digital(24) and self.ui.radioButton_Slave2Digital_8.isChecked():
				self.ui.radioButton_Slave2Digital_8.setChecked(0)
				self.ui.radioButton_Slave2Digital_8.setCheckable(0)

			if self.pInterface.Digital(25) and not self.ui.radioButton_Slave3Digital_1.isChecked():
				self.ui.radioButton_Slave3Digital_1.setCheckable(1)
				self.ui.radioButton_Slave3Digital_1.setChecked(1)
			elif not self.pInterface.Digital(25) and self.ui.radioButton_Slave3Digital_1.isChecked():
				self.ui.radioButton_Slave3Digital_1.setChecked(0)
				self.ui.radioButton_Slave3Digital_1.setCheckable(0)
			if self.pInterface.Digital(26) and not self.ui.radioButton_Slave3Digital_2.isChecked():
				self.ui.radioButton_Slave3Digital_2.setCheckable(1)
				self.ui.radioButton_Slave3Digital_2.setChecked(1)
			elif not self.pInterface.Digital(26) and self.ui.radioButton_Slave3Digital_2.isChecked():
				self.ui.radioButton_Slave3Digital_2.setChecked(0)
				self.ui.radioButton_Slave3Digital_2.setCheckable(0)
			if self.pInterface.Digital(27) and not self.ui.radioButton_Slave3Digital_3.isChecked():
				self.ui.radioButton_Slave3Digital_3.setCheckable(1)
				self.ui.radioButton_Slave3Digital_3.setChecked(1)
			elif not self.pInterface.Digital(27) and self.ui.radioButton_Slave3Digital_3.isChecked():
				self.ui.radioButton_Slave3Digital_3.setChecked(0)
				self.ui.radioButton_Slave3Digital_3.setCheckable(0)
			if self.pInterface.Digital(28) and not self.ui.radioButton_Slave3Digital_4.isChecked():
				self.ui.radioButton_Slave3Digital_4.setCheckable(1)
				self.ui.radioButton_Slave3Digital_4.setChecked(1)
			elif not self.pInterface.Digital(28) and self.ui.radioButton_Slave3Digital_4.isChecked():
				self.ui.radioButton_Slave3Digital_4.setChecked(0)
				self.ui.radioButton_Slave3Digital_4.setCheckable(0)
			if self.pInterface.Digital(29) and not self.ui.radioButton_Slave3Digital_5.isChecked():
				self.ui.radioButton_Slave3Digital_5.setCheckable(1)
				self.ui.radioButton_Slave3Digital_5.setChecked(1)
			elif not self.pInterface.Digital(29) and self.ui.radioButton_Slave3Digital_5.isChecked():
				self.ui.radioButton_Slave3Digital_5.setChecked(0)
				self.ui.radioButton_Slave3Digital_5.setCheckable(0)
			if self.pInterface.Digital(30) and not self.ui.radioButton_Slave3Digital_6.isChecked():
				self.ui.radioButton_Slave3Digital_6.setCheckable(1)
				self.ui.radioButton_Slave3Digital_6.setChecked(1)
			elif not self.pInterface.Digital(30) and self.ui.radioButton_Slave3Digital_6.isChecked():
				self.ui.radioButton_Slave3Digital_6.setChecked(0)
				self.ui.radioButton_Slave3Digital_6.setCheckable(0)
			if self.pInterface.Digital(31) and not self.ui.radioButton_Slave3Digital_7.isChecked():
				self.ui.radioButton_Slave3Digital_7.setCheckable(1)
				self.ui.radioButton_Slave3Digital_7.setChecked(1)
			elif not self.pInterface.Digital(31) and self.ui.radioButton_Slave3Digital_7.isChecked():
				self.ui.radioButton_Slave3Digital_7.setChecked(0)
				self.ui.radioButton_Slave3Digital_7.setCheckable(0)
			if self.pInterface.Digital(32) and not self.ui.radioButton_Slave3Digital_8.isChecked():
				self.ui.radioButton_Slave3Digital_8.setCheckable(1)
				self.ui.radioButton_Slave3Digital_8.setChecked(1)
			elif not self.pInterface.Digital(32) and self.ui.radioButton_Slave3Digital_8.isChecked():
				self.ui.radioButton_Slave3Digital_8.setChecked(0)
				self.ui.radioButton_Slave3Digital_8.setCheckable(0)

	def set_engineBoth_1(self, val):
		if self.pInterface:
			self.pInterface.SetMotor(1, iSpeed=val)
			self.ui.dial_MainLeft_1.setSliderPosition(0)
			self.ui.dial_MainRight_1.setSliderPosition(0)
	def set_engineLeft_1(self, val):
		if self.pInterface:
			self.pInterface.SetOutput(1, val)
			self.ui.dial_MainBoth_1.setSliderPosition(0)
	def set_engineRight_1(self, val):
		if self.pInterface:
			self.pInterface.SetOutput(2, val)
			self.ui.dial_MainBoth_1.setSliderPosition(0)
	def set_engineBoth_2(self, val):
		if self.pInterface:
			self.pInterface.SetMotor(2, iSpeed=val)
			self.ui.dial_MainLeft_2.setSliderPosition(0)
			self.ui.dial_MainRight_2.setSliderPosition(0)
	def set_engineLeft_2(self, val):
		if self.pInterface:
			self.pInterface.SetOutput(3, val)
			self.ui.dial_MainBoth_2.setSliderPosition(0)
	def set_engineRight_2(self, val):
		if self.pInterface:
			self.pInterface.SetOutput(4, val)
			self.ui.dial_MainBoth_2.setSliderPosition(0)
	def set_engineBoth_3(self, val):
		if self.pInterface:
			self.pInterface.SetMotor(3, iSpeed=val)
			self.ui.dial_MainLeft_3.setSliderPosition(0)
			self.ui.dial_MainRight_3.setSliderPosition(0)
	def set_engineLeft_3(self, val):
		if self.pInterface:
			self.pInterface.SetOutput(5, val)
			self.ui.dial_MainBoth_3.setSliderPosition(0)
	def set_engineRight_3(self, val):
		if self.pInterface:
			self.pInterface.SetOutput(6, val)
			self.ui.dial_MainBoth_3.setSliderPosition(0)
	def set_engineBoth_4(self, val):
		if self.pInterface:
			self.pInterface.SetMotor(4, iSpeed=val)
			self.ui.dial_MainLeft_4.setSliderPosition(0)
			self.ui.dial_MainRight_4.setSliderPosition(0)
	def set_engineLeft_4(self, val):
		if self.pInterface:
			self.pInterface.SetOutput(7, val)
			self.ui.dial_MainBoth_4.setSliderPosition(0)
	def set_engineRight_4(self, val):
		if self.pInterface:
			self.pInterface.SetOutput(8, val)
			self.ui.dial_MainBoth_4.setSliderPosition(0)

	def set_engineBoth_5(self, val):
		if self.pInterface:
			self.pInterface.SetMotor(5, iSpeed=val)
			self.ui.dial_Slave1Left_1.setSliderPosition(0)
			self.ui.dial_Slave1Right_1.setSliderPosition(0)
	def set_engineLeft_5(self, val):
		if self.pInterface:
			self.pInterface.SetOutput(9, val)
			self.ui.dial_Slave1Both_1.setSliderPosition(0)
	def set_engineRight_5(self, val):
		if self.pInterface:
			self.pInterface.SetOutput(10, val)
			self.ui.dial_Slave1Both_1.setSliderPosition(0)
	def set_engineBoth_6(self, val):
		if self.pInterface:
			self.pInterface.SetMotor(6, iSpeed=val)
			self.ui.dial_Slave1Left_2.setSliderPosition(0)
			self.ui.dial_Slave1Right_2.setSliderPosition(0)
	def set_engineLeft_6(self, val):
		if self.pInterface:
			self.pInterface.SetOutput(11, val)
			self.ui.dial_Slave1Both_2.setSliderPosition(0)
	def set_engineRight_6(self, val):
		if self.pInterface:
			self.pInterface.SetOutput(12, val)
			self.ui.dial_Slave1Both_2.setSliderPosition(0)
	def set_engineBoth_7(self, val):
		if self.pInterface:
			self.pInterface.SetMotor(7, iSpeed=val)
			self.ui.dial_Slave1Left_3.setSliderPosition(0)
			self.ui.dial_Slave1Right_3.setSliderPosition(0)
	def set_engineLeft_7(self, val):
		if self.pInterface:
			self.pInterface.SetOutput(13, val)
			self.ui.dial_Slave1Both_3.setSliderPosition(0)
	def set_engineRight_7(self, val):
		if self.pInterface:
			self.pInterface.SetOutput(14, val)
			self.ui.dial_Slave1Both_3.setSliderPosition(0)
	def set_engineBoth_8(self, val):
		if self.pInterface:
			self.pInterface.SetMotor(8, iSpeed=val)
			self.ui.dial_Slave1Left_4.setSliderPosition(0)
			self.ui.dial_Slave1Right_4.setSliderPosition(0)
	def set_engineLeft_8(self, val):
		if self.pInterface:
			self.pInterface.SetOutput(15, val)
			self.ui.dial_Slave1Both_4.setSliderPosition(0)
	def set_engineRight_8(self, val):
		if self.pInterface:
			self.pInterface.SetOutput(16, val)
			self.ui.dial_Slave1Both_4.setSliderPosition(0)

	def set_engineBoth_9(self, val):
		if self.pInterface:
			self.pInterface.SetMotor(9, iSpeed=val)
			self.ui.dial_Slave2Left_1.setSliderPosition(0)
			self.ui.dial_Slave2Right_1.setSliderPosition(0)
	def set_engineLeft_9(self, val):
		if self.pInterface:
			self.pInterface.SetOutput(17, val)
			self.ui.dial_Slave2Both_1.setSliderPosition(0)
	def set_engineRight_9(self, val):
		if self.pInterface:
			self.pInterface.SetOutput(18, val)
			self.ui.dial_Slave2Both_1.setSliderPosition(0)
	def set_engineBoth_10(self, val):
		if self.pInterface:
			self.pInterface.SetMotor(10, iSpeed=val)
			self.ui.dial_Slave2Left_2.setSliderPosition(0)
			self.ui.dial_Slave2Right_2.setSliderPosition(0)
	def set_engineLeft_10(self, val):
		if self.pInterface:
			self.pInterface.SetOutput(19, val)
			self.ui.dial_Slave2Both_2.setSliderPosition(0)
	def set_engineRight_10(self, val):
		if self.pInterface:
			self.pInterface.SetOutput(20, val)
			self.ui.dial_Slave2Both_2.setSliderPosition(0)
	def set_engineBoth_11(self, val):
		if self.pInterface:
			self.pInterface.SetMotor(11, iSpeed=val)
			self.ui.dial_Slave2Left_3.setSliderPosition(0)
			self.ui.dial_Slave2Right_3.setSliderPosition(0)
	def set_engineLeft_11(self, val):
		if self.pInterface:
			self.pInterface.SetOutput(21, val)
			self.ui.dial_Slave2Both_3.setSliderPosition(0)
	def set_engineRight_11(self, val):
		if self.pInterface:
			self.pInterface.SetOutput(22, val)
			self.ui.dial_Slave2Both_3.setSliderPosition(0)
	def set_engineBoth_12(self, val):
		if self.pInterface:
			self.pInterface.SetMotor(12, iSpeed=val)
			self.ui.dial_Slave2Left_4.setSliderPosition(0)
			self.ui.dial_Slave2Right_4.setSliderPosition(0)
	def set_engineLeft_12(self, val):
		if self.pInterface:
			self.pInterface.SetOutput(23, val)
			self.ui.dial_Slave2Both_4.setSliderPosition(0)
	def set_engineRight_12(self, val):
		if self.pInterface:
			self.pInterface.SetOutput(24, val)
			self.ui.dial_Slave2Both_4.setSliderPosition(0)

	def set_engineBoth_13(self, val):
		if self.pInterface:
			self.pInterface.SetMotor(13, iSpeed=val)
			self.ui.dial_Slave3Left_1.setSliderPosition(0)
			self.ui.dial_Slave3Right_1.setSliderPosition(0)
	def set_engineLeft_13(self, val):
		if self.pInterface:
			self.pInterface.SetOutput(25, val)
			self.ui.dial_Slave3Both_1.setSliderPosition(0)
	def set_engineRight_13(self, val):
		if self.pInterface:
			self.pInterface.SetOutput(26, val)
			self.ui.dial_Slave3Both_1.setSliderPosition(0)
	def set_engineBoth_14(self, val):
		if self.pInterface:
			self.pInterface.SetMotor(14, iSpeed=val)
			self.ui.dial_Slave3Left_2.setSliderPosition(0)
			self.ui.dial_Slave3Right_2.setSliderPosition(0)
	def set_engineLeft_14(self, val):
		if self.pInterface:
			self.pInterface.SetOutput(27, val)
			self.ui.dial_Slave3Both_2.setSliderPosition(0)
	def set_engineRight_14(self, val):
		if self.pInterface:
			self.pInterface.SetOutput(28, val)
			self.ui.dial_Slave3Both_2.setSliderPosition(0)
	def set_engineBoth_15(self, val):
		if self.pInterface:
			self.pInterface.SetMotor(15, iSpeed=val)
			self.ui.dial_Slave3Left_3.setSliderPosition(0)
			self.ui.dial_Slave3Right_3.setSliderPosition(0)
	def set_engineLeft_15(self, val):
		if self.pInterface:
			self.pInterface.SetOutput(29, val)
			self.ui.dial_Slave3Both_3.setSliderPosition(0)
	def set_engineRight_15(self, val):
		if self.pInterface:
			self.pInterface.SetOutput(30, val)
			self.ui.dial_Slave3Both_3.setSliderPosition(0)
	def set_engineBoth_16(self, val):
		if self.pInterface:
			self.pInterface.SetMotor(16, iSpeed=val)
			self.ui.dial_Slave3Left_4.setSliderPosition(0)
			self.ui.dial_Slave3Right_4.setSliderPosition(0)
	def set_engineLeft_16(self, val):
		if self.pInterface:
			self.pInterface.SetOutput(31, val)
			self.ui.dial_Slave3Both_4.setSliderPosition(0)
	def set_engineRight_16(self, val):
		if self.pInterface:
			self.pInterface.SetOutput(32, val)
			self.ui.dial_Slave3Both_4.setSliderPosition(0)

def run():
	app = QtGui.QApplication(sys.argv)
	myapp = DiagForm()
	myapp.show()

	sys.exit(app.exec_())

if __name__ == "__main__":
	run()

