<h1 align="center">PyQt5</h1>

## 环境安装

`pip install PyQt5 -i https:://pypi.douban.com/simple`

`pip install PyQt5-tools -i https://pypi.douban.com/simple`

系统Path添加`./Lib/site-packages/pyqt5-tools`

**vscode安装PyQt5**:https://zhuanlan.zhihu.com/p/66758263

## PyQt5

中文教程：https://www.cnblogs.com/linyfeng/p/11294173.html

### 基本格式：

```python
#前面是UI文件生成的py函数，导入即可
#设置测试类初始化
import sys
from PyQt5.QtWidgets import QApplication, QMainWindow
class MyMainForm(QMainWindow,Ui_MainWindow):
    def __init__(self,parent=None):
        super(MyMainForm, self).__init__(parent)
        self.setupUi(self)
        self.pushButton.clicked.connect(self.hello)
    def hello(self):
        print("hello")
        
#设置主线程
if __name__=="__main__":
	app=QApplication(sys.argv)
	myWin=MyMainForm()#类的初始化定义
	myWin.show()
	sys.exit(app.exec_())
```

### 运行展示一个小窗口

```python
#头文件导入
import sys
from PyQt5.QtWidgets import QApplication, QMainWindow
if __name__ == '__main__':
#QApplication包含基本组件
    app = QApplication(sys.argv)
#QWidge空间提供基本的应用构造器，默认情况下为没有父级的构造器，即窗口
    w = QWidget()
#resize()改变控件大小
    w.resize(250, 150)
#移动窗口位置到(300,300)
    w.move(300, 300)
#设置窗口名称
    w.setWindowTitle('Simple')
#在桌面显示
    w.show()
#退出程序
    sys.exit(app.exec_())
```

### 带窗口标题

```python	
import sys
from PyQt5.QtWidgets import QApplication, QWidget
from PyQt5.QtGui import QIcon
class Example(QWidget):

    def __init__(self):
        super().__init__()
        self.initUI()
    def initUI(self):
        self.setGeometry(300, 300, 300, 220)
#setGeometry()：把窗口放到屏幕上并且设置窗口大小。参数分别代表屏幕坐标的x、y和窗口大小的宽、高
        self.setWindowTitle('Icon')
        self.setWindowIcon(QIcon('web.png'))#放置绝对路径的图片        
        self.show()
   if __name__ == '__main__':

    app = QApplication(sys.argv)
    ex = Example()
    sys.exit(app.exec_())
```

### 提示框

```python	
import sys
from PyQt5.QtWidgets import (QWidget, QToolTip, 
    QPushButton, QApplication)
from PyQt5.QtGui import QFont    


class Example(QWidget):

    def __init__(self):
        super().__init__()

        self.initUI()


    def initUI(self):

        QToolTip.setFont(QFont('SansSerif', 10))

        self.setToolTip('This is a <b>QWidget</b> widget')

        btn = QPushButton('Button', self)
        btn.setToolTip('This is a <b>QPushButton</b> widget')
        btn.resize(btn.sizeHint())
        btn.move(50, 50)       

        self.setGeometry(300, 300, 300, 200)
        self.setWindowTitle('Tooltips')    
        self.show()


if __name__ == '__main__':

    app = QApplication(sys.argv)
    ex = Example()
    sys.exit(app.exec_())
```

### 基本控件的使用

单选框、多选框、下拉框、文本框：https://www.cnblogs.com/linyfeng/p/11294173.html

```python
#单选框框架
self.单选框名字.clicked.connect(self.checkCheck自定义函数名称)
def checkCheck(self):
    if self.radioButton.isChecked():
        QMessageBox.information(self,"消息框标题","我RadioButton按钮被选中啦！",QMessageBox.Yes | QMessageBox.No)
#QMessageBox.information(self, "Title", "Content", QMessageBox.Yes | QMessageBox.No, QMessageBox.Yes);——(父控件指针，标题，内容，按钮数量，默认按钮)

#多选框框架
class MyMainForm(QMainWindow, Ui_Form):
    def __init__(self, parent=None):
        super(MyMainForm, self).__init__(parent)
        self.setupUi(self)
        self.okButton.clicked.connect(self.checkCheckBox)

    def checkCheckBox(self):
        if self.freshcheckBox.isChecked() and self.bearcheckBox.isChecked():
            QMessageBox.information(self,"消息框标题","鱼和熊掌我要兼得！",QMessageBox.Yes | QMessageBox.No)
            
#下拉列表框
class MyWin(QMainWindow,Ui_test.Ui_Form):
    def __init__(self,parent=None):
        super(MyWin,self).__init__(parent)
        self.setupUi(self)
        self.pushButton.clicked.connect(self.hello)
    def hello(self):
        s_val=self.comboBox.currentText()
        QMessageBox.information(self,"提示框","你要学%s，为什么？"% (s_val),QMessageBox.Yes|QMessageBox.No)

#单行文本框：
setText()：设置单行文本框内容。
 Text():返回文本框内容
 clear()：清除文本框内容
#多行文本框：
setPlainText()：设置多行文本框的文本内容。
 toPlainText()：获取多行文本框的文本内容。
 clear()：清除多行文本框的内容
```
### 消息弹出、用户输入、文件/目录选择对话框

```python
#常用格式
information(QWdiget parent,title,text,buttons,defaultButton)：弹出消息对话框。
question(QWidget parent,title,text,buttons,defaultButton)：弹出问答对话框
warning(QWidget parent,title,text,buttons,defaultButton)：弹出警告对话框
critical(QWidget parent,title,text,buttons,defaultButton)：弹出严重错误对话框
about(QWidget parent,title,text)：弹出关于对话
setTitle()：设置标题
setText()：设置正文消息
setIcon()：设置弹出对话框图片

#标准按键
QMessage.Ok 同意操作、QMessage.Cancel  取消操作、QMessage.Yes  同意操作、QMessage.No 取消操作、QMessage.Abort  终止操作、QMessage.Retry 重试操作、QMessage.Ignore  忽略操作
# 对于提问对话框，需要根据用户选择Yes或者No进行下一步判断，可以获取按钮点击的返回值进行判断，选择NO的返回值为65536，选择Yes的返回值为其他

#获取用户输入
getint()：从输入控件中获得标准整数输入
getDouble()：从输入控件中获得标准浮点数输入
getText()：从输入控件中获得标准字符串的输入
getItem() ：从输入控件中获得列表里的选项输入
#输入提示框
class MyWin(QMainWindow,Ui_test.Ui_Form):
    def __init__(self, parent=None):
        super(MyWin, self).__init__(parent)
        self.setupUi(self)
        self.pushButton.clicked.connect(self.getint)
        self.pushButton_2.clicked.connect(self.getStr)
        self.pushButton_3.clicked.connect(self.getList)
    def getint(self):
        num,ok=QInputDialog.getInt(self,'整数输入','请输入整数：')
        if ok and num:
            self.lineEdit.setText(str(num))
    def getStr(self):
        text,ok=QInputDialog.getText(self,'Text Input','姓名：')
        if ok and text:
            self.lineEdit_2.setText(str(text))
    def getList(self):
        items=('C', 'C++', 'C#', 'JAva', 'Python')#下拉列表
        list,ok=QInputDialog.getItem(self,"Select input dialog",'语言列表',items,0,False)
        if ok and list:
            self.lineEdit_3.setText(str(list))

#QFileDialog文件/目录选择对话框
#打开和保存文件：
#https://www.cnblogs.com/linyfeng/p/11223711.html
QFileDialog.getOpenFileName()：获取单个文件路径
QFileDialog.getOpenFileNames()：获取多个文件路径
QFileDialog.getExistingDirectory()：获取文件夹路径

#示例
class MyMainForm(QMainWindow, Ui_Form):
    def __init__(self, parent=None):
        super(MyMainForm, self).__init__(parent)
        self.setupUi(self)
        self.openFileButton.clicked.connect(self.openFile)

    def openFile(self):
        get_directory_path = QFileDialog.getExistingDirectory(self,
                                    "选取指定文件夹",
                                    "C:/")
        self.filePathlineEdit.setText(str(get_directory_path))

        get_filename_path, ok = QFileDialog.getOpenFileName(self,
                                    "选取单个文件",
                                   "C:/",
                                    "All Files (*);;Text Files (*.txt)")
        if ok:
            self.filePathlineEdit.setText(str(get_filename_path))
#格式问题：https://www.cnblogs.com/linyfeng/p/11223711.html
        get_filenames_path, ok = QFileDialog.getOpenFileNames(self,
                                    "选取多个文件",
                                   "C:/",
                                    "All Files (*);;Text Files (*.txt)")
        if ok:
            self.filePathlineEdit.setText(str(' '.join(get_filenames_path)))
```

## 信号与槽

### 为控件创建信号

`pyqtSignal()`

```python	
#为自定义控件WinForm创建了一个btnClickedSignal信号
from PyQt5.QtCore import pyqtSignal
from PyQt5.QtWidgets import QMainWindow
class WinForm(QMainWindow):
    btnClickedSignal=pyqtSignal()
```

### 信号与槽函数

**绑定**：`connect()`

**解除**：`disconnect()`

**发射信号**：`emit()`

**左键点击并释放触发信号：**`Clicked()`

**左键按下触发信号：**`Pressed()`

**左键释放触发信号：**`Released()`

**控件标记状态发生改变时触发信号：**`Toggled()`

### 基本控件使用

`isChecked()`

## 信号与槽的入门应用

**步骤**：

1. 导入头文件：`import PyQt5.QtCore`    `import PyQt5.QtWiddgets`

2. 声明信号：`signal=pyqtSignal()`

3. 将信号连接到指定槽函数：`self.signal.connect(self.signalCall)`

4. 定义槽函数：

```python
def signalCall(self):
	print("signal emit")
```

5. 发射信号：`self.signal.emit()`

### 内置信号与槽的使用

```python
#单击"测试点击按钮"会出先信息提示框
from PyQt5.QtWidgets import  QPushButton ,  QApplication, QWidget 
from  PyQt5.QtWidgets import QMessageBox  
import sys 
   
app =  QApplication(sys.argv)
widget =  QWidget()

def showMsg():
     QMessageBox.information(widget, "信息提示框", "ok，弹出测试信息")
     
btn = QPushButton( "测试点击按钮", widget)
btn.clicked.connect( showMsg)
widget.show()
sys.exit(app.exec_())
```

### 内置信号与槽函数

```python
from PyQt5.QtWidgets import *
import sys

class Winform(QWidget):
	def __init__(self,parent=None):#parent=None表示不使用父类，可以和下面的super().__init__(parent)一起省略
		super().__init__(parent)#使用父类QWidget的初始化函数__init__
		self.setWindowTitle('内置的信号/槽示例')
		self.resize(330,  50 ) 
		btn = QPushButton('关闭', self)
		btn.clicked.connect(self.close) #内置槽函数close
         
if __name__ == '__main__':#主函数main()
	app = QApplication(sys.argv)#表明程序开始
	win = Winform()#win初始化为Winform类
	win.show()#展示win初始化得到的GUI界面
	sys.exit(app.exec_())#退出程序
```

### 使用自定义参数

**问题**：信号发出的参数个数小于槽函数接收的参数个数

**解决方式**：lambda表达式

```python
from PyQt5.QtWidgets import QMainWindow, QPushButton , QWidget , QMessageBox, QApplication, QHBoxLayout
import sys 

class WinForm(QMainWindow):  
	def __init__(self, parent=None):  
		super(WinForm, self).__init__(parent)  
		self.setWindowTitle("信号和槽传递额外参数例子")
		button1 = QPushButton('Button 1')  
		button2 = QPushButton('Button 2')  
        
		button1.clicked.connect(lambda: self.onButtonClick(1)) #lambda表达式解决
		button2.clicked.connect(lambda: self.onButtonClick(2)) 		

		layout = QHBoxLayout()  
		layout.addWidget(button1)  
		layout.addWidget(button2)  
  
		main_frame = QWidget()  
		main_frame.setLayout(layout)       
		self.setCentralWidget(main_frame)  
  
	def onButtonClick(self, n):  
		print('Button {0} 被按下了'.format(n))  
		QMessageBox.information(self, "信息提示框", 'Button {0} clicked'.format(n))            
  
if __name__ == "__main__":  
	app = QApplication(sys.argv)  
	form = WinForm()  
	form.show()  
	sys.exit(app.exec_())
```
### 装饰器信号与槽

使用方法：

```python
  @QtCore.pyqtSlot()    
  def on_hello_clicked(self):#自定义槽函数名称
      print( "点击了OK按钮")
```



自定义槽函数规则：on+使用`setObjectName`设置的名称+信号名称

```python	
from PyQt5 import QtCore 
from PyQt5.QtWidgets import QApplication ,QWidget ,QHBoxLayout , QPushButton
import sys    
    
class CustWidget( QWidget ):
    
    def __init__(self, parent=None):
        super(CustWidget, self).__init__(parent)
        
        self.okButton = QPushButton("OK", self)
        #使用setObjectName设置对象名称
        self.okButton.setObjectName("hello")        
        layout =  QHBoxLayout()
        layout.addWidget(self.okButton)
        self.setLayout(layout)                
        QtCore.QMetaObject.connectSlotsByName(self)
        
    @QtCore.pyqtSlot()    
    def on_hello_clicked(self):#自定义槽函数名称
        print( "点击了OK按钮")
        
if __name__ == "__main__":        
    app =  QApplication(sys.argv)
    win = CustWidget()
    win.show()
    sys.exit(app.exec_())
```

 `QtCore.QMetaObject.connectSlotsByName(self)`作用：

```python	
@QtCore.pyqtSlot()    
    def on_hello_clicked(self):#自定义槽函数名称
        print( "点击了OK按钮")
 #变成
def __init__(self,parent=None):
    self.hello.clicked.conntet(self.hello_clicked)
def hello_clicked(self):
	print("点击了OK按钮")
```

### 多线程

#### 定时器(QTimer)

```python
#头文件
from PyQt5.QtCore import QTimer
#初始化一个定时器
self.timer=QTimer(self)#使用self.timer作为变量
#设置时间间隔并启动定时器
#timeout：当定时器超时时发送信号    #singleShot：在给定的时间间隔后调用一个槽函数时发射此信号
self.timer.timeout.connect(self.自定义函数)#自定义函数不能加()
self.timer.start(2000)#设置2000ms

#示例：显示当前时间
self.timer=Qtimer(self)
self.timer.timeout.connect(self.showTime)

def showTime(self):
    #获取系统目前时间
    time=QDateTime.currentDateTime()
    #设置系统时间显示格式
    timeDisplay=time.toString("yyyy-MM-DD hh:mm:ss dddd");
    #在标签上显示时间
    self.label.setText(timeD)
    
#线程锁和信号：https://zhuanlan.zhihu.com/p/62988456
from PyQt5.Qt import (QApplication, QWidget, QPushButton,
                      QThread,QMutex,pyqtSignal)
import sys
import time

qmut_1 = QMutex() # 创建线程锁
qmut_2 = QMutex()
# 继承QThread
class Thread_1(QThread):  # 线程1
    def __init__(self):
        super().__init__()

    def run(self):
        qmut_1.lock() # 加锁
        values = [1, 2, 3, 4, 5]
        for i in values:
            print(i)
            time.sleep(0.5)  # 休眠
        qmut_1.unlock() # 解锁


class Thread_2(QThread):  # 线程2
    _signal =pyqtSignal()
    def __init__(self):
        super().__init__()

    def run(self):
        # qmut_2.lock()  # 加锁
        values = ["a", "b", "c", "d", "e"]
        for i in values:
            print(i)
            time.sleep(0.5)
        # qmut_2.unlock()  # 解锁
        self._signal.emit()


class MyWin(QWidget):
    def __init__(self):
        super().__init__()
        # 按钮初始化
        self.btn_1 = QPushButton('按钮1', self)
        self.btn_1.move(120, 80)
        self.btn_1.clicked.connect(self.click_1)  # 绑定槽函数

        self.btn_2 = QPushButton('按钮2', self)
        self.btn_2.move(120, 120)
        self.btn_2.clicked.connect(self.click_2)  # 绑定槽函数

    def click_1(self):
        self.thread_1 = Thread_1()  # 创建线程
        self.thread_1.start()  # 开始线程

    def click_2(self):
        self.btn_2.setEnabled(False)#按钮不可点击
        self.thread_2 = Thread_2()#创建线程
        self.thread_2._signal.connect(self.set_btn)#连接结束信号
        self.thread_2.start()#线程启动

    def set_btn(self):
        self.btn_2.setEnabled(True)


if __name__ == "__main__":
    app = QApplication(sys.argv)
    myshow = MyWin()
    myshow.show()
    sys.exit(app.exec_())
```

### socket编程

```python
#创建一个socket进程
socket1=socket.socket(socket.AF_INET,socket.SOCK_STREAM)
socket1.settimeout(1)
#需要在调用socket的connect方法之前设置settimeout(time)方法，另外在设置之后要将再次调用settimeout(None)来设置socket进入阻塞模式。https://www.cnblogs.com/shengulong/p/7202458.html
#进行测试
try:
    socket.connect(IP地址,端口号)
    socket1.recv(1024)#每次调用时会使用settimeout将计时器重置为1
except Exception:#其余情况
    
time.sleep(.1)#进程暂停100ms
socket.send(string)#执行一次，但是不一定能发送完给定的数据
socket.sendall(string)#发送完整的TCP数据，成功返回None，失败p
#ipv4协议，TCP协议
sock=socket.socket(socket.AF_INET,socket.SOCK_STREAM)
#SOCK_STREM表示tcp
check_socket.settimeout(3)#阻塞线程3s，然后自动退出
```
