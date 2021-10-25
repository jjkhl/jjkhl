<h1 align="center">PySide6笔记</h1>

## 基本格式

```python
#第一种格式
import sys
from PySide6 import QtWidgets
import ui_xxxx # 创建UI的代码,如果有的话

class MyWindow(QtWidgets.QMainWindow):#继承QMainWindow
    def __init__(self):
        super().__init__()
        
        #在此创建窗体上的部件

        #使用UI文件创建部件，如果有的话
        self.ui = ui_xxxx.Ui_MainWindow()
        self.ui.setupUi(self)

if __name__ == "__main__":
    app = QtWidgets.QApplication()

    window = MyWindow() #实例化窗口
    window.show()#显示
    sys.exit(app.exec())
```



```
#第二种格式
import sys
from PySide6.QtWidgets import QApplication
from ui import Ui_Form
from PySide6 import QtWidgets
class MyMainForm(QtWidgets.QMainWindow, Ui_Form):
    def __init__(self, parent=None):
        super(MyMainForm, self).__init__(parent)
        self.setWindowTitle("test")
        self.setupUi(self)
        self.pushButton.clicked.connect(self.pushdown)#定义信号连接的槽函数
    def pushdown(self):
        print("按钮按下")
#设置主线程
if __name__=="__main__":
	app=QApplication(sys.argv)
	myWin=MyMainForm()#类的初始化定义
	myWin.show()
	sys.exit(app.exec())
```

## toggleButton

```python
#按钮checkable属性勾选，表示只有按下和弹起两种状态
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

```

