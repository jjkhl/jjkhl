# 学习资料

1. [最新QT从入门到实战完整版|传智教育](https://www.bilibili.com/video/BV1g4411H78N/?vd_source=8b01e16d821495c639dbc02ca4104dce)
2. 《QT5开发及实例》

# QT基础

## 默认文件含义

### qmake文件(*.pro)

```c++
QT       += core gui #QT包含的模块
greaterThan(QT_MAJOR_VERSION, 4): QT += widgets#大于4版本以上，包含widgetmo'ku'a
CONFIG += c++11
TARGET=main #生成的可执行文件名称
TEMPLATE=app #应用程序模板，Application
SOURCES += \
    main.cpp \
    widget.cpp
HEADERS += \
    widget.h
FORMS += \
    widget.ui
```

### main.cpp

```c++
#include "widget.h"
#include <QApplication>
int main(int argc, char *argv[])
{
    QApplication a(argc, argv);//应用对象a，在qt中有且只有一个
    MainWindow w;//窗口对象，继承于QWidget
    w.show();//窗口对象默认不显示，必须调用show方法
    return a.exec();//让应用对象进入消息循环，阻塞在该行
}
```

### widget.cpp

```c++
#include "widget.h"
#include "ui_widget.h"

Widget::Widget(QWidget *parent)
    : QWidget(parent)
    , ui(new Ui::Widget)
{
    ui->setupUi(this);//更改ui的部分，可以自定义添加一些按钮
}

Widget::~Widget()
{
    delete ui;
}
```

### widget.h

```c++
#ifndef WIDGET_H
#define WIDGET_H
#include <QWidget>

QT_BEGIN_NAMESPACE
namespace Ui { class Widget; }
QT_END_NAMESPACE

class Widget : public QWidget
{
    Q_OBJECT //Q_OBJECT宏，允许类中使用信号和槽机制
public:
    Widget(QWidget *parent = nullptr);
    ~Widget();
private:
    Ui::Widget *ui;
};
#endif // WIDGET_H
```

## 按钮

头文件`QPushButton`

```c++
Widget::Widget(QWidget *parent)
    : QWidget(parent)
    , ui(new Ui::Widget)
{
    ui->setupUi(this);
    QPushButton *btn=new QPushButton("第二个按钮",this);
    btn->setParent(this);//设置父类
    btn->setText("hello");//设置按钮文字
    btn->move(100,100);//移动位置
    setWindowTitle("hello");//设置窗口标题
    setFixedSize(600,400);//设置固定窗口大小
}
```

## 信号与槽

[连接函数](https://blog.csdn.net/ljsant/article/details/118827657)：`connect(信号发送方，发送的信号，信号接收方，信号的处理槽)`

```qt
等效写法：
connect(ui->pushButton,&QPushButton::clicked, this, &Qwidget::close);
connect(ui->pushButton,SIGNAL(clicked, this, SLOT(close);
connect(ui->pushButton_2,QOverload<bool>::of(&QPushButton::clicked),[=](){
        std::cout<<"good"<<std::endl;});
        
connect(btn, &QPushButton::clicked, /* this, */ [&]() {
        this->close();
    });
```

### 自定义信号与槽

下课后，教师饿了，学生请吃饭

```c++
//teacher.h
#ifndef TEACHER_H
#define TEACHER_H

#include <QObject>

class Teacher : public QObject
{
    Q_OBJECT
public:
    explicit Teacher(QObject *parent = nullptr);

signals:
    void hungry();//只需要声明信号，不需要任何定义
	void hungry(QString foog);//函数重载
};

#endif // TEACHER_H

//teacher.cpp
#include "teacher.h"

Teacher::Teacher(QObject *parent) : QObject(parent)
{

}

```

```c++
//student.h
#ifndef STUDENT_H
#define STUDENT_H

#include <QObject>

class Student : public QObject
{
    Q_OBJECT
public:
    explicit Student(QObject *parent = nullptr);
    void treat();
    void treat(QString food);
signals:

};

#endif // STUDENT_H

//student.cpp
#include "student.h"
#include<QDebug>
Student::Student(QObject *parent) : QObject(parent)
{

}
void Student::treat()
{
    qDebug()<<"请老师吃饭";
}
void Student::treat(QString food)
{
    qDebug()<<"请老师吃"<<food;//输出带引号的food；解决方式：food.toUtf8().data();
}
```

```c++
//widget.h
#ifndef WIDGET_H
#define WIDGET_H
#include"teacher.h"
#include"student.h"
#include <QWidget>

QT_BEGIN_NAMESPACE
namespace Ui { class Widget; }
QT_END_NAMESPACE

class Widget : public QWidget
{
    Q_OBJECT

public:
    Widget(QWidget *parent = nullptr);
    ~Widget();

private:
    Ui::Widget *ui;
    Teacher *zt;
    Student *st;

    void classIsOver()
    {
        emit zt->hungry("宫保鸡丁");
    }
};
#endif // WIDGET_H
//widget.cpp
#include "widget.h"
#include "./ui_widget.h"

Widget::Widget(QWidget *parent)
    : QWidget(parent)
    , ui(new Ui::Widget)
{
    ui->setupUi(this);
    //创建一个老师和学生对象
    this->zt=new Teacher(this);
    this->st=new Student(this);
	/*
    connect(zt,&Teacher::hungry,st,&Student::treat);//无函数重载的连接版本
    this->classIsOver();
    */
    //函数重载的解决办法——函数指针：函数返回值 (*变量名) (参数列表)=&函数地址
    void(Teacher::*teacherSignal) (QString)=&Teacher::hungry;
    void(Student::*studentSlot) (QString)=&Student::treat;
    connect(zt,teacherSignal,st,studentSlot);
    /* 断开连接
    disconnect(zt,teacherSigbal,st,studentSlot);
    */
}

Widget::~Widget()
{
    delete ui;
}
```

## 菜单栏和工具栏

```c++
#include "mainwindow.h"
#include "./ui_mainwindow.h"
#include<QMenuBar>
#include<QToolBar>
#include<QPushButton>
MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    QMenuBar *bar=menuBar();
    //QMenuBar *bar=new QMenuBar();
    setMenuBar(bar);//设置到ui界面
    //创建菜单
    QMenu *fileMenu=bar->addMenu("文件");
//    QMenu *editMenu=bar->addMenu("编辑");
    // 创建菜单项
    fileMenu->addAction("新建");
    //添加分割线
    fileMenu->addSeparator();
    fileMenu->addAction("打开");

    //工具栏，可以有多个
    QToolBar *toolBar=new QToolBar(this);
    addToolBar(Qt::LeftToolBarArea,toolBar);

    //只允许左右停靠
    toolBar->setAllowedAreas(Qt::LeftToolBarArea|Qt::RightToolBarArea);

    //设置不允许浮动
    toolBar->setFloatable(false);
    //设置不允许移动
    toolBar->setMovable(false);
    //工具栏中设置内容
    toolBar->addAction("新建");
    toolBar->addSeparator();
    toolBar->addAction("打开");

    //工具栏设置按钮
    QPushButton *btn=new QPushButton("aa",this);
    toolBar->addWidget(btn);
}

MainWindow::~MainWindow()
{
    delete ui;
}
```

