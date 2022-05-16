'''
Description: 
Version: 2.0
Autor: jjkhl
Date: 2021-10-29 23:53:45
LastEditors: jjkhl
LastEditTime: 2021-10-31 23:46:46
'''
import sys
from PySide6.QtWidgets import (QLineEdit, QMainWindow, QPushButton, QApplication,
    QVBoxLayout, QDialog)
from ui import Ui_MainWindow

class Form(QMainWindow,Ui_MainWindow):

    def __init__(self, parent=None):
        super(Form, self).__init__(parent)
        self.setupUi(self)
        # 创建组件
        self.pushButton.toggled.connect(self.changestate)

    # 向用户打招呼
    def changestate(self):
        if self.pushButton.isChecked():
            self.pushButton.setText("按钮按下")
        else:
            self.pushButton.setText("按钮弹起")

if __name__ == '__main__':
    # 创建Qt应用程序
    app = QApplication(sys.argv)
    # 创建并显示Form
    form = Form()
    form.show()
    # 运行Qt主循环
    sys.exit(app.exec())