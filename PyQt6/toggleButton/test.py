'''
Description: 
Version: 2.0
Autor: jjkhl
Date: 2021-10-19 23:06:15
LastEditors: jjkhl
LastEditTime: 2021-10-21 22:11:33
'''
import sys
from ui import Ui_MainWindow
from PySide6 import QtCore, QtWidgets,QtGui

class Mywin(QtWidgets.QMainWindow,Ui_MainWindow):
    def __init__(self):
        super().__init__()
        self.setupUi(self)
        self.pushButton.toggled.connect(self.hello)

    def hello(self):
        if self.pushButton.isChecked():
            print("按钮已按下")
        else:
            print("按钮弹起")

if __name__=="__main__":
    app=QtWidgets.QApplication(sys.argv)
    window=Mywin()
    window.show()
    sys.exit(app.exec())
