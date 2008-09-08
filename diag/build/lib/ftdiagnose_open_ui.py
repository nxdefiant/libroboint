# -*- coding: utf-8 -*-

# Form implementation generated from reading ui file 'open.ui'
#
# Created: Sun Aug 24 15:00:54 2008
#      by: PyQt4 UI code generator 4.4.2
#
# WARNING! All changes made in this file will be lost!

from PyQt4 import QtCore, QtGui

class Ui_Dialog(object):
    def setupUi(self, Dialog):
        Dialog.setObjectName("Dialog")
        Dialog.resize(600,300)
        sizePolicy = QtGui.QSizePolicy(QtGui.QSizePolicy.Fixed,QtGui.QSizePolicy.Fixed)
        sizePolicy.setHorizontalStretch(0)
        sizePolicy.setVerticalStretch(0)
        sizePolicy.setHeightForWidth(Dialog.sizePolicy().hasHeightForWidth())
        Dialog.setSizePolicy(sizePolicy)
        Dialog.setMinimumSize(QtCore.QSize(600,300))
        Dialog.setMaximumSize(QtCore.QSize(600,300))
        self.radioButton_Serial = QtGui.QRadioButton(Dialog)
        self.radioButton_Serial.setGeometry(QtCore.QRect(20,80,211,31))
        self.radioButton_Serial.setObjectName("radioButton_Serial")
        self.radioButton_USB = QtGui.QRadioButton(Dialog)
        self.radioButton_USB.setGeometry(QtCore.QRect(20,20,121,25))
        self.radioButton_USB.setChecked(True)
        self.radioButton_USB.setObjectName("radioButton_USB")
        self.comboBox = QtGui.QComboBox(Dialog)
        self.comboBox.setGeometry(QtCore.QRect(150,20,421,31))
        self.comboBox.setObjectName("comboBox")
        self.buttonBox = QtGui.QDialogButtonBox(Dialog)
        self.buttonBox.setGeometry(QtCore.QRect(210,220,177,29))
        self.buttonBox.setStandardButtons(QtGui.QDialogButtonBox.Cancel|QtGui.QDialogButtonBox.Ok)
        self.buttonBox.setObjectName("buttonBox")
        self.lineEdit = QtGui.QLineEdit(Dialog)
        self.lineEdit.setGeometry(QtCore.QRect(400,140,171,30))
        self.lineEdit.setObjectName("lineEdit")
        self.radioButton_Serial_II = QtGui.QRadioButton(Dialog)
        self.radioButton_Serial_II.setGeometry(QtCore.QRect(20,110,241,25))
        self.radioButton_Serial_II.setObjectName("radioButton_Serial_II")
        self.radioButton_Serial_II_Slave = QtGui.QRadioButton(Dialog)
        self.radioButton_Serial_II_Slave.setGeometry(QtCore.QRect(20,140,331,25))
        self.radioButton_Serial_II_Slave.setObjectName("radioButton_Serial_II_Slave")
        self.label = QtGui.QLabel(Dialog)
        self.label.setGeometry(QtCore.QRect(400,120,111,18))
        self.label.setObjectName("label")
        self.checkBox = QtGui.QCheckBox(Dialog)
        self.checkBox.setGeometry(QtCore.QRect(340,60,231,31))
        self.checkBox.setObjectName("checkBox")

        self.retranslateUi(Dialog)
        QtCore.QMetaObject.connectSlotsByName(Dialog)

    def retranslateUi(self, Dialog):
        Dialog.setWindowTitle(QtGui.QApplication.translate("Dialog", "Dialog", None, QtGui.QApplication.UnicodeUTF8))
        self.radioButton_Serial.setText(QtGui.QApplication.translate("Dialog", "Serial Robo Interface", None, QtGui.QApplication.UnicodeUTF8))
        self.radioButton_USB.setText(QtGui.QApplication.translate("Dialog", "USB Device", None, QtGui.QApplication.UnicodeUTF8))
        self.lineEdit.setText(QtGui.QApplication.translate("Dialog", "/dev/ttyS0", None, QtGui.QApplication.UnicodeUTF8))
        self.radioButton_Serial_II.setText(QtGui.QApplication.translate("Dialog", "Serial Intelligent Interface", None, QtGui.QApplication.UnicodeUTF8))
        self.radioButton_Serial_II_Slave.setText(QtGui.QApplication.translate("Dialog", "Serial Intelligent Interface with Slave", None, QtGui.QApplication.UnicodeUTF8))
        self.label.setText(QtGui.QApplication.translate("Dialog", "Serial Device:", None, QtGui.QApplication.UnicodeUTF8))
        self.checkBox.setText(QtGui.QApplication.translate("Dialog", "D1/D2 in distance mode", None, QtGui.QApplication.UnicodeUTF8))

