'''
Description: 
Version: 2.0
Autor: jjkhl
Date: 2021-10-05 23:33:25
LastEditors: jjkhl
LastEditTime: 2021-10-05 23:58:43
'''
from test import Ui_MainWindow
from PyQt5.QtCore import *
from PyQt5.QtWidgets import *
import sys
from tab1 import Tab1
class MyMainForm(QMainWindow,Ui_MainWindow):
    def __init__(self,parent=None):
        super(MyMainForm, self).__init__(parent)
        self.setupUi(self)
        #将tab1.py文件中的父类定位到MyMainForm
        self.tab1=Tab1(self)
        
#设置主线程
if __name__=="__main__":
	app=QApplication(sys.argv)
	myWin=MyMainForm()#类的初始化定义
	myWin.show()
	sys.exit(app.exec_())