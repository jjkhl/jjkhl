<h1 align="center">PyQt5</h1>

## 环境安装

`pip install PyQt5 -i https:://pypi.douban.com/simple`

`pip install PyQt5-tools -i https://pypi.douban.com/simple`

系统Path添加`./Lib/site-packages/pyqt5-tools`

**vscode安装PyQt5**:https://zhuanlan.zhihu.com/p/66758263

## Matplotlib

安装：  `pip install matplotlib -i https://pypi.tuna.tsinghua.edu.cn/simple/ `

```python	
#头文件导入
import matplotlib.pyplot as plt
#画图
# 如果只传入一个数组作为参数， matplotlib 认为是 Y 轴的坐标
# 并自动产生 从 0 开始的 对应 X 轴坐标： 0、1、2、3 ...
plt.plot([2, 4, 6, 8])
plt.plot([0,1,2,3],[2,4,6,8])
plt.show()
#matplotlib的缺省字体不支持中文，我们可以指定一个支持中文的字体
import matplotlib.pyplot as plt

plt.rcParams['font.family'] = 'sans-serif'
# 设定字体为微软雅黑
plt.rcParams['font.sans-serif']=['Microsoft Yahei']

plt.plot([1, 2, 3, 4])
plt.xlabel('times 次数')
plt.show()

#原文链接：https://blog.csdn.net/hopyGreat/article/details/81389144
import matplotlib.pyplot as plt
import numpy as np
import matplotlib
 
plt.rcParams['font.sans-serif'] = ['SimHei']    # 用来正常显示中文字符
plt.rcParams['axes.unicode_minus'] = False      # 用来正常显示正负号
 
# 这行可以显示matplotlib的配置文件的位置
print(matplotlib.matplotlib_fname())
 
x = np.linspace(1,4,100)
y = x**x
plt.plot(x,y, '+',label='y=x**x函数图像',color='black')
 
plt.xlabel('这是x坐标')
plt.ylabel('这是y坐标')
plt.title('这是y=x**x的函数图像')
plt.legend()
plt.show()
#
```

### 样式设置

```python
#'r.'表示红色点图，-线图。参考：  https://matplotlib.org/stable/api/_as_gen/matplotlib.pyplot.plot.html 
import matplotlib.pyplot as plt
plt.plot([1, 2, 3, 4], [1, 4, 9, 16], 'r.')
plt.show()
#指定宽度：linewidth
import matplotlib.pyplot as plt
plt.plot(range(10), range(10), linewidth=0.5)
plt.show()
#指定点的大小：markersize
plt.plot(range(10), range(10), 'r.', markersize=2.5)

#numpy数组
#matplotlib 内部都是把作图数据转化为 numpy 的 ndarray 数组类型进行处理的。
#所以可以直接使用numpy数组作为画图数据
import matplotlib.pyplot as plt
import numpy as np
# arange 就像 Python中的range
# 从 0 到 5 步长为 0.2
t = np.arange(0, 5, 0.2)
# 使用 numpy 的ndarray 作为数据
plt.plot(t, t**2, 'b.')
plt.show()

#柱状图：bar
import matplotlib.pyplot as plt
names = ['2016', '2017', '2018']
values = [1, 10, 100]
plt.bar(names, values)
plt.show()

#饼状图：pie
import matplotlib.pyplot as plt

# 指定饼图的每个切片名称
labels = 'Frogs', 'Hogs', 'Dogs', 'Logs'

# 指定每个切片的数值，从而决定了百分比
sizes = [15, 30, 45, 10]
explode = (0, 0.1, 0, 0)  # only "explode" the 2nd slice (i.e. 'Hogs')

fig1, ax1 = plt.subplots()
ax1.pie(sizes, explode=explode, labels=labels, autopct='%1.1f%%',
        shadow=True, startangle=90)
ax1.axis('equal')  # Equal aspect ratio ensures that pie is drawn as a circle.

plt.show()

#多个子图：subplot
import matplotlib.pyplot as plt
import numpy as np

# arange 就像 Python中的range
# 从 0 到 5 步长为 0.2
t = np.arange(0, 5, 0.2)

# 指定2行，1列，共两个axe，当前使用第1个绘图块
plt.subplot(2,1,1)   
plt.plot(t, t**2, 'b.')

# 当前使用第2个绘图块
plt.subplot(2,1,2)   
plt.plot(t, t**2, 'r-')
plt.show()

#使用多个Figure
import matplotlib.pyplot as plt
plt.figure(1)                # the first figure
plt.subplot(211)             # the first subplot in the first figure
plt.plot([1, 2, 3])
plt.subplot(212)             # the second subplot in the first figure
plt.plot([4, 5, 6])


plt.figure(2)                # a second figure
plt.plot([4, 5, 6])          # creates a subplot(111) by default

plt.figure(1)                # figure 1 current; subplot(212) still current
plt.subplot(211)             # make subplot(211) in figure1 current
plt.title('Easy as 1, 2, 3') # subplot 211 title

plt.show()

#在图形中插入文字
import matplotlib.pyplot as plt
import numpy as np

mu, sigma = 100, 15
x = mu + sigma * np.random.randn(10000)

n, bins, patches = plt.hist(x, 50, density=1, facecolor='g', alpha=0.75)

# x轴标题
plt.xlabel('Smarts')
# y轴标题
plt.ylabel('Probability')
# 子图标题
plt.title('Histogram of IQ')
# 指定坐标处添加文本
plt.text(60, .025, r'$\mu=100,\ \sigma=15$')
plt.axis([40, 160, 0, 0.03])
plt.grid(True)
plt.show()

#x轴刻度文字垂直
import matplotlib.pyplot as plt
# 设定字体为微软雅黑
plt.rcParams['font.family'] = 'Microsoft Yahei'

# x刻度垂直，否则字会重叠
plt.xticks(rotation=-90)

# 加长底部空间，否则文字显示不全
plt.subplots_adjust(bottom=0.45)
```



## PyQt5

中文教程：https://www.cnblogs.com/linyfeng/p/11294173.html

### 基本格式：

```python
#前面是UI文件生成的py函数，导入即可
#设置测试类初始化
import sys
from PyQt5.QtWidgets import QApplication, QWidget
from PyQt5.QtGui import QIcon

class MyMainForm(QMainWindow, Ui_Form):
    def __init__(self, parent=None):
        super(MyMainForm, self).__init__(parent)
        self.setWindowTitle("test")
        self.setupUi(self)
        self.okButton.clicked.connect(self.checkCheckBox)#定义信号连接的槽函数
    def checkCheckBox(self):
            #函数定义
#设置主线程
if __name__=="__main__":
	app=QApplication(sys.argv)
	myWin=MyMainForm()#类的初始化定义
	myWin.show()
	sys.exit(app.exec_())
```
### 程序图标

```python
#添加主窗口图标
from PySide2.QtGui import QIcon

app=QApplication([])
#加载icon
app.setWindowIcon(QIcon('logo.png'))
#制作应用程序图标
pyinstaller -F 目标文件 --icon="logo.ico"#一定要是ico文件
```



### 样式更改

```python
#文本框提示文字：
QTextEdit——placeholderText
#更改按钮的样式：MainWindow对象styleSheet属性添加样式表
QPushButton { 
    color: red ;
    font-size:15px;
    width:50px;#宽度
    height:20px;#高度
}
```

**选择器的常见用法**：https://doc.qt.io/qt-5/stylesheet-syntax.html

| Selector            | 示例                      | 说明                                              |
| ------------------- | ------------------------- | ------------------------------------------------- |
| Universal Selector  | *                         | 星号匹配所有界面元素                              |
| Type Selector       | QPushButton               | 选择所有QPushButton类型(包括其子类)               |
| Class Selector      | .QPushButton              | 选择所有QPushButton类型，但是不包括子类           |
| ID Selector         | QPushButton#okButton      | 选择所有对象名为okButton的QPushButton类型         |
| Property Selector   | QPushButton[flat=“false”] | 选择所有 flat 属性值为 false 的 QPushButton类型。 |
| Descendant Selector | QDialog QPushButton       | 选择所有 QDialog  `内部`  QPushButton类型         |
| Child Selector      | QDialog > QPushButton     | 择所有 QDialog  `直接子节点`  QPushButton类型     |

```python
#设置tabWidget下所有控件
#tabWidget *{
	color:red;
}
#鼠标悬浮在控件上时显示的样式
QPushButton:hover{color:red}
#指定控件disable状态下显示的样式    
QpushButton:disabled{color:red}
#指定控件鼠标悬浮加上处于勾选状态下的显示样式
QCheckBox:hover:checked { color: white }
#优先级选择：
#如果一个元素的显示样式被多层指定了， 越靠近元素本身 的选择指定，优先级越高
#指定边框
*{border:1px solid red;}
#1px是边框宽度，solid是实线，dashed为虚线，dotted为点，none为无边框
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

### 文件不存在退出以及文件保存

```python
#文件不存在问题
import os
if os.path.isfile("data.xlsx")==False:
            msg_box=QMessageBox.warning(self,'警告','文件不存在')
            app = QApplication(sys.argv)
            time.sleep(1)
            app.exit(msg_box.exec_())
            
#文件保存问题
from PyQt5.QtWidgets import *
from PyQt5.QtCore import *
 Now=QDateTime.currentDateTime().toString("yyyyMMdd_HHmmss")
 workbook.save(f'output_{Now}.xlsx')
 
#excel中插入图片
from openpyxl.drawing.image import Image
workbook = openpyxl.load_workbook('data.xlsx')
sheet=workbook['Sheet1']
img=Image('pic.jpg')
sheet.add_image(img,'F1')
```

### 使用布局后如何改变空间大小

`QWidget——sizePolicy`

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



### 异常

```python
#处理结构
try:
    可能会出现错误的代码段
except 错误类型:
    处理异常代码
#处理所有异常
except:
except Exception as e:#e为所有异常类型的别名
	处理异常代码
	print(traceback.format_exc())#查找错误的位置并打印

#抛出异常
raise 异常名称
```

### 调用外部程序

```python
#方法1：os库的system函数
import os
cmd=r'd:\tools\wget http:///mirrors.sohu.com/ngnix/nginx-1.13.9.zip'
os.system(cmd)
#打开非可执行程序文件
os.startfile('hello.txt')
#方法2：subprocess库
from subprocess import PIPE, Popen
# 返回的是 Popen 实例对象
proc = Popen(
    'fsutil volume diskfree c:',
    stdin  = None,
    stdout = PIPE,
    stderr = PIPE,
    shell=True
# communicate 方法返回 输出到 标准输出 和 标准错误 的字节串内容
# 标准输出设备和 标准错误设备 当前都是本终端设备
outinfo, errinfo = proc.communicate()
# 注意返回的内容是bytes 不是 str ，我的是中文windows，所以用gbk解码
outinfo = outinfo.decode('gbk')
errinfo = errinfo.decode('gbk')
print (outinfo)
print ('-------------')
print (errinfo)

outputList = outinfo.splitlines()

# 剩余量
free  = int(outputList[0].split(':')[1].strip())

# 总空间
total = int(outputList[1].split(':')[1].strip())

if (free/total < 0.1):
    print('!! 剩余空间告急！！')
else:
    print('剩余空间足够')
```

### 装饰器

```python
#在原来函数的基础上，不去修改原来的函数而使用装饰器
#原函数
import time
def getXXXTime():
    print()
    return time.strftime('%Y_%m_%d %H:%M:%S',time.localtime())
#装饰器
import time

# 定义一个装饰器函数
def sayLocal(func):
    def wrapper():
        curTime = func()#未执行func函数
        return f'当地时间： {curTime}'
    return wrapper

def getXXXTime():
    return time.strftime('%Y_%m_%d %H:%M:%S',time.localtime())

# 装饰 getXXXTime
getXXXTime = sayLocal(getXXXTime)

print (getXXXTime())  
```

### JSON格式转换

**序列化**：把程序的各种类型数据对象变成表示该数据对象的字节串的过程`json.dumps(数据对象)`

**反序列化**：把字节串转化为程序中的数据对象的过程`json.loads(目标字符串)`

```python
historyTransactions = [

    {
        'time'   : '20170101070311',  # 交易时间
        'amount' : '3088',            # 交易金额
        'productid' : '45454455555',  # 货号
        'productname' : 'iphone7'     # 货名
    },
    {
        'time'   : '20170101050311',  # 交易时间
        'amount' : '18',              # 交易金额
        'productid' : '453455772955', # 货号
        'productname' : '奥妙洗衣液'   # 货名
    },
]
import json
jsonStr=json.dumps(historyTransactions,ensure_ascii=False)
print(jsonStr)
```

### 日期与实践

#### 获取当前时间对应的数字

```python
import time
before=time.time()#从1970年1月1日0点(epoch时间点)到当前时间经过的秒数（秒数时间）
#得到当前时间对应的字符串
from datetime import datetime
str(datetime.now())#2021-09-02 20:23:57.021582
datetime.now().strftime('%Y-%m-%d %H:%M:%S')#2021-09-02 20:27:50
time.strftime('%Y-%m-%d %H:%M:%S',time.localtime())#2021-09-02 20:27:50
#将字符串指定时间转换为秒数时间
int(time.mktime(time.strptime('2015-08-01 23:59:59', '%Y-%m-%d %H:%M:%S')))
```



## 多线程

```python
#Python3调用线程
print('主线程执行代码') 

# 从 threading 库中导入Thread类
from threading import Thread
from time import sleep

# 定义一个函数，作为新线程执行的入口函数
def threadFunc(arg1,arg2):
    print('子线程 开始')
    print(f'线程函数参数是：{arg1}, {arg2}')
    sleep(5)
    print('子线程 结束')


# 创建 Thread 类的实例对象
thread = Thread(
    # target 参数 指定 新线程要执行的函数
    # 注意，这里指定的函数对象只能写一个名字，不能后面加括号，
    # 如果加括号就是直接在当前线程调用执行，而不是在新线程中执行了
    target=threadFunc, 

    # 如果 新线程函数需要参数，在 args里面填入参数
    # 注意参数是元组， 如果只有一个参数，后面要有逗号，像这样 args=('参数1',)
    args=('参数1', '参数2')
)

# 执行start 方法，就会创建新线程，
# 并且新线程会去执行入口函数里面的代码。
# 这时候 这个进程 有两个线程了。
thread.start()

# 主线程的代码执行 子线程对象的join方法，
# 就会等待子线程结束，才继续执行下面的代码
thread.join()
print('主线程结束')

#Lock保护共享数据
from threading import Thread,Lock
from time import sleep

bank = {
    'byhy' : 0
}

bankLock = Lock()

# 定义一个函数，作为新线程执行的入口函数
def deposit(theadidx,amount):
    # 操作共享数据前，申请获取锁
    bankLock.acquire()
    
    balance =  bank['byhy']
    # 执行一些任务，耗费了0.1秒
    sleep(0.1)
    bank['byhy']  = balance + amount
    print(f'子线程 {theadidx} 结束')
    
    # 操作完共享数据后，申请释放锁
    bankLock.release()

theadlist = []
for idx in range(10):
    thread = Thread(target = deposit,
                    args = (idx,1)
                    )
    thread.start()
    # 把线程对象都存储到 threadlist中
    theadlist.append(thread)

for thread in theadlist:
    thread.join()

print('主线程结束')
print(f'最后我们的账号余额为 {bank["byhy"]}')
```

### 定时器(QTimer)

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

### Asyncio并发库

网址：http://c.biancheng.net/view/5557.html

[实现多个客户端数据收发](###多客户端服务器)

概念：一个主线程，进行多个不同任务(future对象)，这些不同的任务被事件循环(Event Loop)的对象控制。

> 事件循环：主线程每次将执行序列中的任务清空后，就去事件队列中检查是否有等待执行的任务，如果有则每次取出一个推到执行序列中执行，这个过程时循环往复的。
>
> Asyncio的任务在运行时不会被外部的一些因素打断，因此Asyncio内的操作不会出现竞争资源(多个线程同时使用同一资源)的情况，也就不需要担心线程安全的问题。

```python
    import asyncio
    import aiohttp
    import time
    async def download_one(url):
        async with aiohttp.ClientSession() as session:
            async with session.get(url) as resp:
                print('Read {} from {}'.format(resp.content_length, url))
    async def download_all(sites):
        tasks = [asyncio.ensure_future(download_one(site)) for site in sites]
        await asyncio.gather(*tasks)
    def main():
        sites = [
            'http://c.biancheng.net',
            'http://c.biancheng.net/c',
            'http://c.biancheng.net/python'
        ]
        start_time = time.perf_counter()
       
        loop = asyncio.get_event_loop()
        try:
            loop.run_until_complete(download_all(sites))
        finally:
            loop.close()
        end_time = time.perf_counter()
        print('Download {} sites in {} seconds'.format(len(sites), end_time - start_time))
       
    if __name__ == '__main__':
        main()
```



## socket编程

tcp进行通讯的双方，分为服务端和客户端。

![白月黑羽Python3教程](http://cdn1.python3.vip/imgs/socket1.png)

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

#socket编程：http://www.byhy.net/tut/py/etc/socket/
#服务端代码
#  === TCP 服务端程序 server.py ===

# 导入socket 库
from socket import *

# 主机地址为空字符串，表示绑定本机所有网络接口ip地址
# 等待客户端来连接
IP = ''
# 端口号
PORT = 50000
# 定义一次从socket缓冲区最多读入512个字节数据
BUFLEN = 512

# 实例化一个socket对象
# 参数 AF_INET 表示该socket网络层使用IP协议
# 参数 SOCK_STREAM 表示该socket传输层使用tcp协议
listenSocket = socket(AF_INET, SOCK_STREAM)

# socket绑定地址和端口
listenSocket.bind((IP, PORT))


# 使socket处于监听状态，等待客户端的连接请求
# 参数 8 表示 最多接受多少个等待连接的客户端
listenSocket.listen(8)
print(f'服务端启动成功，在{PORT}端口等待客户端连接...')

dataSocket, addr = listenSocket.accept()
print('接受一个客户端连接:', addr)

while True:
    # 尝试读取对方发送的消息
    # BUFLEN 指定从接收缓冲里最多读取多少字节
    recved = dataSocket.recv(BUFLEN)

    # 如果返回空bytes，表示对方关闭了连接
    # 退出循环，结束消息收发
    if not recved:
        break

    # 读取的字节数据是bytes类型，需要解码为字符串
    info = recved.decode()
    print(f'收到对方信息： {info}')

    # 发送的数据类型必须是bytes，所以要编码
    dataSocket.send(f'服务端接收到了信息 {info}'.encode())

# 服务端也调用close()关闭socket
dataSocket.close()
listenSocket.close()

#客户端代码
#  === TCP 客户端程序 client.py ===

from socket import *

IP = '127.0.0.1'
SERVER_PORT = 50000
BUFLEN = 1024

# 实例化一个socket对象，指明协议
dataSocket = socket(AF_INET, SOCK_STREAM)

# 连接服务端socket
dataSocket.connect((IP, SERVER_PORT))

while True:
    # 从终端读入用户输入的字符串
    toSend = input('>>> ')
    if  toSend =='exit':
        break
    # 发送消息，也要编码为 bytes
    dataSocket.send(toSend.encode())

    # 等待接收服务端的消息
    recved = dataSocket.recv(BUFLEN)
    # 如果返回空bytes，表示对方关闭了连接
    if not recved:
        break
    # 打印读取的信息
    print(recved.decode())

dataSocket.close()
```

Windows查看IP地址端口：`netstat -an|find /i "端口号"`

### 应用消息格式

TCP协议传输的是字节流，需要明确定义<strong style="color:red">消息边界</strong>

指定消息边界的两种方式：

* 用特殊字节作为消息的结尾符号

使用消息内容中不可能出现的字符串，比如`FFFF`，作为消息的结尾字符

* 在消息开头的某个位置，直接指定消息的长度

> UDP协议通常不需要指定消息边界，因为UDP是数据包协议，应用程序从socket接收到的必定是发送方发送的完整消息

### 多客户端服务器

缺省下创建的`socke`t和`recv`都是阻塞的。所以一个线程里面，没法不断调用监听socket的`accept`方法,同时还能负责多个数据传输socket消息的收发

```python
#  === TCP 服务端程序 server.py ， 支持多客户端 ===IO bound程序
#缺点：主要时间都是花费在IO上面，时间都用来等待连接请求了
# 导入socket 库
from socket import *
from threading import Thread

IP = ''
PORT = 50000
BUFLEN = 512

# 这是新线程执行的函数，每个线程负责和一个客户端进行通信
def clientHandler(dataSocket,addr):
    while True:
        recved = dataSocket.recv(BUFLEN)
        # 当对方关闭连接的时候，返回空字符串
        if not recved:
            print(f'客户端{addr} 关闭了连接' )
            break

        # 读取的字节数据是bytes类型，需要解码为字符串
        info = recved.decode()
        print(f'收到{addr}信息： {info}')

        dataSocket.send(f'服务端接收到了信息 {info}'.encode())

    dataSocket.close()

# 实例化一个socket对象 用来监听客户端连接请求
listenSocket = socket(AF_INET, SOCK_STREAM)

# socket绑定地址和端口
listenSocket.bind((IP, PORT))

listenSocket.listen(8)
print(f'服务端启动成功，在{PORT}端口等待客户端连接...')

while True:
   # 在循环中，一直接受新的连接请求
   dataSocket, addr = listenSocket.accept()     # Establish connection with client.
   addr = str(addr)
   print(f'一个客户端 {addr} 连接成功' )

   # 创建新线程处理和这个客户端的消息收发
   th = Thread(target=clientHandler,args=(dataSocket,addr))
   th.start()

listenSocket.close()

#异步IO：存在一个线程很好的分配时间，在有连接请求到来时，执行处理连接请求代码，有消息到达socket缓冲时，执行读取处理消息的代码
#python3的asyncio库同时处理多个客户端数据的收发
#  === TCP 服务端程序 server.py 异步支持多客户端 ===
import asyncio, socket
IP = ''
PORT = 50000
BUFLEN = 512

# 定义处理数据收发的回调
async def handle_echo(reader, writer):
    addr = writer.get_extra_info('peername')
    while True:
        data = await reader.read(100)
        if not data:
            print(f'客户端{addr}关闭了连接')
            writer.close()
            break

        message = data.decode()
        print(f'收到{addr}信息： {message}')

        writer.write(data)

loop = asyncio.get_event_loop()
coro = asyncio.start_server(handle_echo, IP, PORT, loop=loop)
server = loop.run_until_complete(coro)

# Serve requests until Ctrl+C is pressed
print('服务端启动成功，在{}端口等待客户端连接...'.format(server.sockets[0].getsockname()[1]))
try:
    loop.run_forever()
except KeyboardInterrupt:
    pass

# Close the server
server.close()
loop.run_until_complete(server.wait_closed())
loop.close()
```



