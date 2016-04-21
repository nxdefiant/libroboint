# -*- coding: utf-8 -*-

# Form implementation generated from reading ui file 'open.ui'
#
# Created by: PyQt4 UI code generator 4.11.4
#
# WARNING! All changes made in this file will be lost!

from PyQt4 import QtCore, QtGui

try:
    _fromUtf8 = QtCore.QString.fromUtf8
except AttributeError:
    def _fromUtf8(s):
        return s

try:
    _encoding = QtGui.QApplication.UnicodeUTF8
    def _translate(context, text, disambig):
        return QtGui.QApplication.translate(context, text, disambig, _encoding)
except AttributeError:
    def _translate(context, text, disambig):
        return QtGui.QApplication.translate(context, text, disambig)

class Ui_Dialog(object):
    def setupUi(self, Dialog):
        Dialog.setObjectName(_fromUtf8("Dialog"))
        Dialog.resize(600, 300)
        sizePolicy = QtGui.QSizePolicy(QtGui.QSizePolicy.Fixed, QtGui.QSizePolicy.Fixed)
        sizePolicy.setHorizontalStretch(0)
        sizePolicy.setVerticalStretch(0)
        sizePolicy.setHeightForWidth(Dialog.sizePolicy().hasHeightForWidth())
        Dialog.setSizePolicy(sizePolicy)
        Dialog.setMinimumSize(QtCore.QSize(600, 300))
        Dialog.setMaximumSize(QtCore.QSize(600, 300))
        self.radioButton_Serial = QtGui.QRadioButton(Dialog)
        self.radioButton_Serial.setGeometry(QtCore.QRect(20, 80, 211, 31))
        self.radioButton_Serial.setObjectName(_fromUtf8("radioButton_Serial"))
        self.radioButton_USB = QtGui.QRadioButton(Dialog)
        self.radioButton_USB.setGeometry(QtCore.QRect(20, 20, 121, 25))
        self.radioButton_USB.setChecked(True)
        self.radioButton_USB.setObjectName(_fromUtf8("radioButton_USB"))
        self.comboBox = QtGui.QComboBox(Dialog)
        self.comboBox.setGeometry(QtCore.QRect(150, 20, 421, 31))
        self.comboBox.setObjectName(_fromUtf8("comboBox"))
        self.buttonBox = QtGui.QDialogButtonBox(Dialog)
        self.buttonBox.setGeometry(QtCore.QRect(210, 220, 177, 29))
        self.buttonBox.setStandardButtons(QtGui.QDialogButtonBox.Cancel|QtGui.QDialogButtonBox.Ok)
        self.buttonBox.setObjectName(_fromUtf8("buttonBox"))
        self.lineEdit = QtGui.QLineEdit(Dialog)
        self.lineEdit.setGeometry(QtCore.QRect(400, 140, 171, 30))
        self.lineEdit.setObjectName(_fromUtf8("lineEdit"))
        self.radioButton_Serial_II = QtGui.QRadioButton(Dialog)
        self.radioButton_Serial_II.setGeometry(QtCore.QRect(20, 110, 241, 25))
        self.radioButton_Serial_II.setObjectName(_fromUtf8("radioButton_Serial_II"))
        self.radioButton_Serial_II_Slave = QtGui.QRadioButton(Dialog)
        self.radioButton_Serial_II_Slave.setGeometry(QtCore.QRect(20, 140, 331, 25))
        self.radioButton_Serial_II_Slave.setObjectName(_fromUtf8("radioButton_Serial_II_Slave"))
        self.label = QtGui.QLabel(Dialog)
        self.label.setGeometry(QtCore.QRect(400, 120, 111, 18))
        self.label.setObjectName(_fromUtf8("label"))
        self.checkBox = QtGui.QCheckBox(Dialog)
        self.checkBox.setGeometry(QtCore.QRect(340, 60, 231, 31))
        self.checkBox.setObjectName(_fromUtf8("checkBox"))

        self.retranslateUi(Dialog)
        QtCore.QMetaObject.connectSlotsByName(Dialog)

    def retranslateUi(self, Dialog):
        Dialog.setWindowTitle(_translate("Dialog", "Dialog", None))
        self.radioButton_Serial.setText(_translate("Dialog", "Serial Robo Interface", None))
        self.radioButton_USB.setText(_translate("Dialog", "USB Device", None))
        self.lineEdit.setText(_translate("Dialog", "/dev/ttyS0", None))
        self.radioButton_Serial_II.setText(_translate("Dialog", "Serial Intelligent Interface", None))
        self.radioButton_Serial_II_Slave.setText(_translate("Dialog", "Serial Intelligent Interface with Slave", None))
        self.label.setText(_translate("Dialog", "Serial Device:", None))
        self.checkBox.setText(_translate("Dialog", "D1/D2 in distance mode", None))

