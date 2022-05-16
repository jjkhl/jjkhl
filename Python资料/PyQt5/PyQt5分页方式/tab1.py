'''
Description: 
Version: 2.0
Autor: jjkhl
Date: 2021-10-05 23:36:56
LastEditors: jjkhl
LastEditTime: 2021-10-06 00:33:40
'''
from PyQt5.QtCore import *

class Tab1:
    def __init__(self,mainwindow):
      mainwindow.pushButton.clicked.connect(self.push)
      self.mainwindow=mainwindow
    def push(self):
        # self.lineEdit.setText("按钮按下")
        # window_object.lineEdit("按钮按下")
        # print("按钮按下")
        self.mainwindow.lineEdit.setText("按钮按下")