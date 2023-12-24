# 学习资料

1. [最新QT从入门到实战完整版|传智教育](https://www.bilibili.com/video/BV1g4411H78N/?vd_source=8b01e16d821495c639dbc02ca4104dce)
2. 《QT5开发及实例第四版》

# QT基础

## [基础类型](https://subingwen.cn/qt/qt-basetype/)

### QByteArray

可以看作`char*`的升级版本，通过构造函数申请一块动态内存，用于存储需要处理的字符串数据。

```c++
构造函数
// 构造空对象, 里边没有数据
QByteArray::QByteArray();
// 将data中的size个字符进行构造, 得到一个字节数组对象
// 如果 size==-1 函数内部自动计算字符串长度, 计算方式为: strlen(data)
QByteArray::QByteArray(const char *data, int size = -1);
// 构造一个长度为size个字节, 并且每个字节值都为ch的字节数组
QByteArray::QByteArray(int size, char ch);

// 在尾部追加数据
// 其他重载的同名函数可参考Qt帮助文档, 此处略
QByteArray &QByteArray::append(const QByteArray &ba);
void QByteArray::push_back(const QByteArray &other);

// 头部添加数据
// 其他重载的同名函数可参考Qt帮助文档, 此处略
QByteArray &QByteArray::prepend(const QByteArray &ba);
void QByteArray::push_front(const QByteArray &other);

// 插入数据, 将ba插入到数组第 i 个字节的位置(从0开始)
// 其他重载的同名函数可参考Qt帮助文档, 此处略
QByteArray &QByteArray::insert(int i, const QByteArray &ba);

// 删除数据
// 从大字符串中删除len个字符, 从第pos个字符的位置开始删除
QByteArray &QByteArray::remove(int pos, int len);
// 从字符数组的尾部删除 n 个字节
void QByteArray::chop(int n);
// 从字节数组的 pos 位置将数组截断 (前边部分留下, 后边部分被删除)
void QByteArray::truncate(int pos);
// 将对象中的数据清空, 使其为null
void QByteArray::clear();

// 字符串替换
// 将字节数组中的 子字符串 before 替换为 after
// 其他重载的同名函数可参考Qt帮助文档, 此处略
QByteArray &QByteArray::replace(const QByteArray &before, const QByteArray &after);

// 判断字节数组中是否包含子字符串 ba, 包含返回true, 否则返回false
bool QByteArray::contains(const QByteArray &ba) const;
bool QByteArray::contains(const char *ba) const;
// 判断字节数组中是否包含子字符 ch, 包含返回true, 否则返回false
bool QByteArray::contains(char ch) const;

// 判断字节数组是否以字符串 ba 开始, 是返回true, 不是返回false
bool QByteArray::startsWith(const QByteArray &ba) const;
bool QByteArray::startsWith(const char *ba) const;
// 判断字节数组是否以字符 ch 开始, 是返回true, 不是返回false
bool QByteArray::startsWith(char ch) const;

// 判断字节数组是否以字符串 ba 结尾, 是返回true, 不是返回false
bool QByteArray::endsWith(const QByteArray &ba) const;
bool QByteArray::endsWith(const char *ba) const;
// 判断字节数组是否以字符 ch 结尾, 是返回true, 不是返回false
bool QByteArray::endsWith(char ch) const;


```

### `QString`

```c++
// 将int, short, long, float, double 转换为 QString 类型
// 其他重载的同名函数可参考Qt帮助文档, 此处略
QString &QString::setNum(int n, int base = 10);
QString &QString::setNum(short n, int base = 10);
QString &QString::setNum(long n, int base = 10);
QString &QString::setNum(float n, char format = 'g', int precision = 6);
QString &QString::setNum(double n, char format = 'g', int precision = 6);
[static] QString QString::number(long n, int base = 10);
[static] QString QString::number(int n, int base = 10);
[static] QString QString::number(double n, char format = 'g', int precision = 6);

// 将 QString 转换为 int, short, long, float, double 类型
int QString::toInt(bool *ok = Q_NULLPTR, int base = 10) const;
short QString::toShort(bool *ok = Q_NULLPTR, int base = 10) const;
long QString::toLong(bool *ok = Q_NULLPTR, int base = 10) const
float QString::toFloat(bool *ok = Q_NULLPTR) const;
double QString::toDouble(bool *ok = Q_NULLPTR) const;

// 将标准C++中的 std::string 类型 转换为 QString 类型
[static] QString QString::fromStdString(const std::string &str);
// 将 QString 转换为 标准C++中的 std::string 类型
std::string QString::toStdString() const;

// QString -> QByteArray
// 转换为本地编码, 跟随操作系统
QByteArray QString::toLocal8Bit() const;
// 转换为 Latin-1 编码的字符串 不支持中文
QByteArray QString::toLatin1() const;
// 转换为 utf8 编码格式的字符串 (常用)
QByteArray QString::toUtf8() const;

// 所有字符转换为大写
QString QString::toUpper() const;
// 所有字符转换为小写
QString QString::toLower() const;

// 其他重载的同名函数可参考Qt帮助文档, 此处略
QString QString::arg(const QString &a, 
          int fieldWidth = 0, 
          QChar fillChar = QLatin1Char( ' ' )) const;
QString QString::arg(int a, int fieldWidth = 0, 
          int base = 10, 
          QChar fillChar = QLatin1Char( ' ' )) const;

// 示例程序
int i;                // 假设该变量表示当前文件的编号
int total;            // 假设该变量表示文件的总个数
QString fileName;     // 假设该变量表示当前文件的名字
// 使用以上三个变量拼接一个动态字符串
QString status = QString("Processing file %1 of %2: %3")
                  .arg(i).arg(total).arg(fileName);
```

### `QVariant`

`QVariant `这个类型充当着最常见的数据类型的联合。`QVariant` 可以保存很多Qt的数据类型，包括`QBrush、QColor、QCursor、QDateTime、QFont、QKeySequence、 QPalette、QPen、QPixmap、QPoint、QRect、QRegion、QSize和QString`，并且还有C++基本类型，如 int、float等。

```c++
QVariant::QVariant(int val);
QVariant::QVariant(bool val);
QVariant::QVariant(double val);
QVariant::QVariant(const char *val);
QVariant::QVariant(const QByteArray &val);
QVariant::QVariant(const QString &val);
// 这里的 T 类型, 就是QVariant支持的类型
void QVariant::setValue(const T &value);
// 该函数行为和 setValue() 函数完全相同
[static] QVariant QVariant::fromValue(const T &value);

// 如果要实现该操作, 可以使用QVariant类提供的 toxxx() 方法, 全部转换可以参考Qt帮助文档
// 在此举列举几个常用函数:
bool QVariant::toBool() const;
QByteArray QVariant::toByteArray() const;
double QVariant::toDouble(bool *ok = Q_NULLPTR) const;
float QVariant::toFloat(bool *ok = Q_NULLPTR) const;
int QVariant::toInt(bool *ok = Q_NULLPTR) const;
QString QVariant::toString() const;
```

自定义类型封装，默认有一个构造函数和一个拷贝构造函数，需要使用`Q_DECLARE_METATYPE`宏

```c++
// *.h
struct MyTest
{
    int id;
    QString name;
};
// 自定义类型注册
Q_DECLARE_METATYPE(MyTest)
    
MyTest t;
t.name = "张三丰";
t.num = 666;
// 值的封装
QVariant vt = QVariant::fromValue(t);

// 值的读取
if(vt.canConvert<MyTest>())
{
    MyTest t = vt.value<MyTest>();
    qDebug() << "name: " << t.name << ", num: " << t.num;
}
```

## 位置和尺寸

### `QPoint`

```c++
// 构造函数
// 构造一个坐标原点, 即(0, 0)
QPoint::QPoint();
// 参数为 x轴坐标, y轴坐标
QPoint::QPoint(int xpos, int ypos);

// 设置x轴坐标
void QPoint::setX(int x);
// 设置y轴坐标
void QPoint::setY(int y);

// 得到x轴坐标
int QPoint::x() const;
// 得到x轴坐标的引用
int &QPoint::rx();
// 得到y轴坐标
int QPoint::y() const;
// 得到y轴坐标的引用
int &QPoint::ry();

// 直接通过坐标对象进行算术运算: 加减乘除
QPoint &QPoint::operator*=(float factor);
QPoint &QPoint::operator*=(double factor);
QPoint &QPoint::operator*=(int factor);
QPoint &QPoint::operator+=(const QPoint &point);
QPoint &QPoint::operator-=(const QPoint &point);
QPoint &QPoint::operator/=(qreal divisor);
```

### `QLine`

```c++
// 构造函数
// 构造一个空对象
QLine::QLine();
// 构造一条直线, 通过两个坐标点
QLine::QLine(const QPoint &p1, const QPoint &p2);
// 从点 (x1, y1) 到 (x2, y2)
QLine::QLine(int x1, int y1, int x2, int y2);

// 给直线对象设置坐标点
void QLine::setPoints(const QPoint &p1, const QPoint &p2);
// 起始点(x1, y1), 终点(x2, y2)
void QLine::setLine(int x1, int y1, int x2, int y2);
// 设置直线的起点坐标
void QLine::setP1(const QPoint &p1);
// 设置直线的终点坐标
void QLine::setP2(const QPoint &p2);

// 返回直线的起始点坐标
QPoint QLine::p1() const;
// 返回直线的终点坐标
QPoint QLine::p2() const;
// 返回值直线的中心点坐标, (p1() + p2()) / 2
QPoint QLine::center() const;

// 返回值直线起点的 x 坐标
int QLine::x1() const;
// 返回值直线终点的 x 坐标
int QLine::x2() const;
// 返回值直线起点的 y 坐标
int QLine::y1() const;
// 返回值直线终点的 y 坐标
int QLine::y2() const;

// 用给定的坐标点平移这条直线
void QLine::translate(const QPoint &offset);
void QLine::translate(int dx, int dy);
// 用给定的坐标点平移这条直线, 返回平移之后的坐标点
QLine QLine::translated(const QPoint &offset) const;
QLine QLine::translated(int dx, int dy) const;

// 直线对象进行比较
bool QLine::operator!=(const QLine &line) const;
bool QLine::operator==(const QLine &line) const;
```

### `QSize`

形容长度和宽度

```c++
// 构造函数
// 构造空对象, 对象中的宽和高都是无效的
QSize::QSize();
// 使用宽和高构造一个有效对象
QSize::QSize(int width, int height);

// 设置宽度
void QSize::setWidth(int width)
// 设置高度
void QSize::setHeight(int height);

// 得到宽度
int QSize::width() const;
// 得到宽度的引用
int &QSize::rwidth();
// 得到高度
int QSize::height() const;
// 得到高度的引用
int &QSize::rheight();

// 交换高度和宽度的值
void QSize::transpose();
// 交换高度和宽度的值, 返回交换之后的尺寸信息
QSize QSize::transposed() const;

// 进行算法运算: 加减乘除
QSize &QSize::operator*=(qreal factor);
QSize &QSize::operator+=(const QSize &size);
QSize &QSize::operator-=(const QSize &size);
QSize &QSize::operator/=(qreal divisor);
```

### `QRect`

```c++
// 构造函数
// 构造一个空对象
QRect::QRect();
// 基于左上角坐标, 和右下角坐标构造一个矩形对象
QRect::QRect(const QPoint &topLeft, const QPoint &bottomRight);
// 基于左上角坐标, 和 宽度, 高度构造一个矩形对象
QRect::QRect(const QPoint &topLeft, const QSize &size);
// 通过 左上角坐标(x, y), 和 矩形尺寸(width, height) 构造一个矩形对象
QRect::QRect(int x, int y, int width, int height);

// 设置矩形的尺寸信息, 左上角坐标不变
void QRect::setSize(const QSize &size);
// 设置矩形左上角坐标为(x,y), 大小为(width, height)
void QRect::setRect(int x, int y, int width, int height);
// 设置矩形宽度
void QRect::setWidth(int width);
// 设置矩形高度
void QRect::setHeight(int height);

// 返回值矩形左上角坐标
QPoint QRect::topLeft() const;
// 返回矩形右上角坐标
// 该坐标点值为: QPoint(left() + width() -1, top())
QPoint QRect::topRight() const;
// 返回矩形左下角坐标
// 该坐标点值为: QPoint(left(), top() + height() - 1)
QPoint QRect::bottomLeft() const;
// 返回矩形右下角坐标
// 该坐标点值为: QPoint(left() + width() -1, top() + height() - 1)
QPoint QRect::bottomRight() const;
// 返回矩形中心点坐标
QPoint QRect::center() const;

// 返回矩形上边缘y轴坐标
int QRect::top() const;
int QRect::y() const;
// 返回值矩形下边缘y轴坐标
int QRect::bottom() const;
// 返回矩形左边缘 x轴坐标
int QRect::x() const;
int QRect::left() const;
// 返回矩形右边缘x轴坐标
int QRect::right() const;

// 返回矩形的高度
int QRect::width() const;
// 返回矩形的宽度
int QRect::height() const;
// 返回矩形的尺寸信息
QSize QRect::size() const;
```

## 日期和时间

### `QDate`

```c++
// 构造函数
QDate::QDate();
QDate::QDate(int y, int m, int d);

// 公共成员函数
// 重新设置日期对象中的日期
bool QDate::setDate(int year, int month, int day);
// 给日期对象添加 ndays 天
QDate QDate::addDays(qint64 ndays) const;
// 给日期对象添加 nmonths 月
QDate QDate::addMonths(int nmonths) const;
// 给日期对象添加 nyears 月
QDate QDate::addYears(int nyears) const;

// 得到日期对象中的年/月/日
int QDate::year() const;
int QDate::month() const;
int QDate::day() const;
void QDate::getDate(int *year, int *month, int *day) const;
QDate::fromString("20000110", "yyyyMMdd");  // January 10, 2000
QDate::fromString("1.30", "M.d");           // January 30 1900
QDate::isValid(2002, 5, 17);  // true
QDate::fromString("20000110", "yyyyMd");    // January 10, 2000

// 日期对象格式化
/*
    d    - The day as a number without a leading zero (1 to 31)
    dd   - The day as a number with a leading zero (01 to 31)
    ddd	 - The abbreviated localized day name (e.g. 'Mon' to 'Sun'). Uses the system locale to localize the name, i.e. QLocale::system().
    dddd - The long localized day name (e.g. 'Monday' to 'Sunday'). Uses the system locale to localize the name, i.e. QLocale::system().
    M    - The month as a number without a leading zero (1 to 12)
    MM   - The month as a number with a leading zero (01 to 12)
    MMM	 - The abbreviated localized month name (e.g. 'Jan' to 'Dec'). Uses the system locale to localize the name, i.e. QLocale::system().
    MMMM - The long localized month name (e.g. 'January' to 'December'). Uses the system locale to localize the name, i.e. QLocale::system().
    yy   - The year as a two digit number (00 to 99)
    yyyy - The year as a four digit number. If the year is negative, a minus sign is prepended, making five characters.
*/
QString QDate::toString(const QString &format) const;

// 操作符重载 ==> 日期比较
bool QDate::operator!=(const QDate &d) const;
bool QDate::operator<(const QDate &d) const;
bool QDate::operator<=(const QDate &d) const;
bool QDate::operator==(const QDate &d) const;
bool QDate::operator>(const QDate &d) const;
bool QDate::operator>=(const QDate &d) const;

// 静态函数 -> 得到本地的当前日期
[static] QDate QDate::currentDate();
```

### `QTime`

```c++
// 构造函数
QTime::QTime();
/*
    h 		==> 取值范围： 0 ~ 23
    m and s 	==> 取值范围： 0 ~ 59
    ms 		==> 取值范围： 0 ~ 999
*/ 
QTime::QTime(int h, int m, int s = 0, int ms = 0);

// 公共成员函数
// Returns true if the set time is valid; otherwise returns false.
bool QTime::setHMS(int h, int m, int s, int ms = 0);
QTime QTime::addSecs(int s) const;
QTime QTime::addMSecs(int ms) const;

// 示例代码
  QTime n(14, 0, 0);                // n == 14:00:00
  QTime t;
  t = n.addSecs(70);                // t == 14:01:10
  t = n.addSecs(-70);               // t == 13:58:50
  t = n.addSecs(10 * 60 * 60 + 5);  // t == 00:00:05
  t = n.addSecs(-15 * 60 * 60);     // t == 23:00:00

// 从时间对象中取出 时/分/秒/毫秒
// Returns the hour part (0 to 23) of the time. Returns -1 if the time is invalid.
int QTime::hour() const;
// Returns the minute part (0 to 59) of the time. Returns -1 if the time is invalid.
int QTime::minute() const;
// Returns the second part (0 to 59) of the time. Returns -1 if the time is invalid.
int QTime::second() const;
// Returns the millisecond part (0 to 999) of the time. Returns -1 if the time is invalid.
int QTime::msec() const;


// 时间格式化
/*
    -- 时 --
    h	==>	The hour without a leading zero (0 to 23 or 1 to 12 if AM/PM display)
    hh	==>	The hour with a leading zero (00 to 23 or 01 to 12 if AM/PM display)
    H	==>	The hour without a leading zero (0 to 23, even with AM/PM display)
    HH	==>	The hour with a leading zero (00 to 23, even with AM/PM display)
    -- 分 --
    m	==>	The minute without a leading zero (0 to 59)
    mm	==>	The minute with a leading zero (00 to 59)
    -- 秒 --
    s	==>	The whole second, without any leading zero (0 to 59)
    ss	==>	The whole second, with a leading zero where applicable (00 to 59)
    -- 毫秒 --
    zzz	==>	The fractional part of the second, to millisecond precision, 
			including trailing zeroes where applicable (000 to 999).
    -- 上午或者下午
    AP or A	==>	使用AM/PM(大写) 描述上下午, 中文系统显示汉字
    ap or a	==>	使用am/pm(小写) 描述上下午, 中文系统显示汉字
*/
QString QTime::toString(const QString &format) const;

// 阶段性计时
// 过时的API函数
// 开始计时
void QTime::start();
// 计时结束
int QTime::elapsed() const;
// 重新计时
int QTime::restart();

// 推荐使用的API函数
// QElapsedTimer 类
void QElapsedTimer::start();
qint64 QElapsedTimer::restart();
qint64 QElapsedTimer::elapsed() const;


// 操作符重载 ==> 时间比较
bool QTime::operator!=(const QTime &t) const;
bool QTime::operator<(const QTime &t) const;
bool QTime::operator<=(const QTime &t) const;
bool QTime::operator==(const QTime &t) const;
bool QTime::operator>(const QTime &t) const;
bool QTime::operator>=(const QTime &t) const;

// 静态函数 -> 得到当前时间
[static] QTime QTime::currentTime();
```

## 定时器类`QTimer`

```c++
// 构造函数
// 如果指定了父对象, 创建的堆内存可以自动析构
QTimer::QTimer(QObject *parent = nullptr);

// 设置定时器时间间隔为 msec 毫秒
// 默认值是0，一旦窗口系统事件队列中的所有事件都已经被处理完，一个时间间隔为0的QTimer就会触发
void QTimer::setInterval(int msec);
// 获取定时器的时间间隔, 返回值单位: 毫秒
int QTimer::interval() const;

// 根据指定的时间间隔启动或者重启定时器, 需要调用 setInterval() 设置时间间隔
[slot] void QTimer::start();
// 启动或重新启动定时器，超时间隔为msec毫秒。
[slot] void QTimer::start(int msec);
// 停止定时器。
[slot] void QTimer::stop();

// 设置定时器精度
/*
参数: 
    - Qt::PreciseTimer -> 精确的精度, 毫秒级
    - Qt::CoarseTimer  -> 粗糙的精度, 和1毫秒的误差在5%的范围内, 默认精度
    - Qt::VeryCoarseTimer -> 非常粗糙的精度, 精度在1秒左右
*/
void QTimer::setTimerType(Qt::TimerType atype);
Qt::TimerType QTimer::timerType() const;	// 获取当前定时器的精度

// 如果定时器正在运行，返回true; 否则返回false。
bool QTimer::isActive() const;

// 判断定时器是否只触发一次
bool QTimer::isSingleShot() const;
// 设置定时器是否只触发一次, 参数为true定时器只触发一次, 为false定时器重复触发, 默认为false
void QTimer::setSingleShot(bool singleShot);

```



## 默认文件含义

### qmake文件(*.pro)

```c++
QT       += core gui #QT包含的模块
greaterThan(QT_MAJOR_VERSION, 4): QT += widgets#大于4版本以上，包含widgetmo'ku'a
CONFIG += c++11
#输出到外部终端
#CONFIG +=c++11 conole
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

## 窗口设置

```c++
// 获取当前窗口的位置信息
void MainWindow::on_positionBtn_clicked()
{
    QRect rect = this->frameGeometry();//得到当前包括边框在内的窗口几何信息
    //const QRect &geometry() const;//得到
    qDebug() << "左上角: " << rect.topLeft()
             << "右上角: " << rect.topRight()
             << "左下角: " << rect.bottomLeft()
             << "右下角: " << rect.bottomRight()
             << "宽度: " << rect.width()
             << "高度: " << rect.height();
}

// 重新设置当前窗口的位置以及宽度, 高度
void MainWindow::on_geometryBtn_clicked()
{
    int x = 100 + rand() % 500;
    int y = 100 + rand() % 500;
    int width = this->width() + 10;
    int height = this->height() + 10;
    setGeometry(x, y, width, height);
}

// 通过 move() 方法移动窗口
void MainWindow::on_moveBtn_clicked()
{
    QRect rect = this->frameGeometry();
    move(rect.topLeft() + QPoint(10, 20));
}

```

## `QDialog`

模态对话框：阻塞同一应用程序中其它窗口的输入

非模态对话框：不会阻塞同一应用程序中其它窗口的输入

```c++
//模态对话框
#include <QDialog>
QDialog dialog;
dialog.setWindowTitle(tr("Hello, dialog!"));
dialog.exec();

//非模态对话框
QDialog *dialog=new QDialog;//堆创建
dialog->setAttribute(Qt::WA_DeleteOnClose);//对话框关闭自动销毁对话框
dialog->setWindowTitle(tr("Hello, dialog!"));
dialog->show();
```

### `QMessageBox`

```c++
// 显示一个模态对话框, 将参数 text 的信息展示到窗口中
[static] void QMessageBox::about(QWidget *parent, const QString &title, const QString &text);

/*
参数:
- parent: 对话框窗口的父窗口
- title: 对话框窗口的标题
- text: 对话框窗口中显示的提示信息
- buttons: 对话框窗口中显示的按钮(一个或多个)
- defaultButton
    1. defaultButton指定按下Enter键时使用的按钮。
    2. defaultButton必须引用在参数 buttons 中给定的按钮。
    3. 如果defaultButton是QMessageBox::NoButton, QMessageBox会自动选择一个合适的默认值。
*/
// 显示一个信息模态对话框
[static] QMessageBox::StandardButton QMessageBox::information(
           QWidget *parent, const QString &title, 
           const QString &text, 
           QMessageBox::StandardButtons buttons = Ok,
           QMessageBox::StandardButton defaultButton = NoButton);

// 显示一个错误模态对话框
[static] QMessageBox::StandardButton QMessageBox::critical(
           QWidget *parent, const QString &title, 
           const QString &text, 
           QMessageBox::StandardButtons buttons = Ok,
           QMessageBox::StandardButton defaultButton = NoButton);

// 显示一个问题模态对话框
[static] QMessageBox::StandardButton QMessageBox::question(
           QWidget *parent, const QString &title, 
           const QString &text, 
           QMessageBox::StandardButtons buttons = StandardButtons(Yes | No), 
           QMessageBox::StandardButton defaultButton = NoButton);

// 显示一个警告模态对话框
[static] QMessageBox::StandardButton QMessageBox::warning(
           QWidget *parent, const QString &title, 
           const QString &text, 
           QMessageBox::StandardButtons buttons = Ok,
           QMessageBox::StandardButton defaultButton = NoButton);
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
    btn->setFixedSize(50,50);//设置a
    setWindowTitle("hello");//设置窗口标题
    setFixedSize(600,400);//设置固定窗口大小
}
```

```c++
    //普通按钮示例
    bt_test = new QPushButton("ok");
    bt_test->setMinimumSize(200, 100);      //设置最小尺寸
    bt_test->setFlat(true);                 //设置无边框
    bt_test->setIconSize(QSize(80, 80));    //设置按钮图标大小
    bt_test->setIcon(QIcon("car.png"));     //设置按钮图标

    //工具按钮示例
    bt_tool = new QToolButton;
    bt_tool->setIcon(QIcon("car.png"));     //设置按钮图标
    bt_tool->setShortcut(QKeySequence(Qt::CTRL + Qt::Key_M));//绑定快捷键

    //单选按钮示例
    bt_radio2 = new QRadioButton("可以左转");
    bt_radio1 = new QRadioButton("可以右转");

    //多选按钮示例
    bt_check1 = new QCheckBox("显示密码");
    bt_check2 = new QCheckBox("自动登录");
```



## 信号与槽

[连接函数](https://blog.csdn.net/ljsant/article/details/118827657)：`connect(信号发送方，发送的信号，信号接收方，信号的处理槽)`

```qt
等效写法：
connect(ui->pushButton,&QPushButton::clicked, this, &Qwidget::close);
connect(ui->pushButton,SIGNAL(clicked), this, SLOT(close);
connect(ui->pushButton_2,QOverload<bool>::of(&QPushButton::clicked),[=](){
        std::cout<<"good"<<std::endl;});
        
connect(btn, &QPushButton::clicked, /* this, */ [&]() {
        this->close();
    });
```

### 绑定多个按钮的一个槽函数调用

```c++
QPushButton *b=qobject_cast<QPushButton *>(sender());
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
        
    //状态栏：最多只有一个
    QStatusBar *stBar=new QStatusBar();
    setStatusBar(stBar);
    //放标签控件
    QLabel *label=new QLabel("提示信息",this);
    stBar->addWidget(label);
    //stBar->addPermanetWidget(label);
    //浮动窗口可以有多个
    
        
}

MainWindow::~MainWindow()
{
    delete ui;
}
```

## 状态栏、浮动窗口、核心窗口

```c++
#include "mainwindow.h"
#include "./ui_mainwindow.h"
#include<QStatusBar>
#include<QLabel>
#include<QDockWidget>
#include<QTextEdit>
MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    //状态栏最多一个
    QStatusBar *stBar=new QStatusBar;
    setStatusBar(stBar);
    QLabel *label=new QLabel("提示信息",this);
    stBar->addWidget(label);
    QLabel *label2=new QLabel("右侧提示信息",this);
    stBar->addPermanentWidget(label2);//设置永久状态栏

    //铆接部件(浮动窗口)可以有多个
    QDockWidget *dw=new QDockWidget("浮动窗口",this);
    addDockWidget(Qt::TopDockWidgetArea,dw);

    //设置后期停靠区域，如只允许上下区域
    dw->setAllowedAreas(Qt::TopDockWidgetArea | Qt::BottomDockWidgetArea);
    //设置核心窗口，只能一个
    QTextEdit *edit=new QTextEdit(this);
    setCentralWidget(edit);

};

MainWindow::~MainWindow()
{
    delete ui;
}
```

# QT进阶

## 文字转语音

```c++
//库链接
//CMakeLists.txt
find_package(Qt5 COMPONENTS Widgets Core Gui TextToSpeech REQUIRED)
target_link_libraries(jjkhl PRIVATE Qt5::Widgets Qt5::Core Qt5::Gui Qt5::TextToSpeech)
//.pro
QT+=core gui texttospeech

//mainwindow.h
#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include<QTextToSpeech>

QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

private slots:
    void on_pushButton_clicked();

private:
    Ui::MainWindow *ui;
    QTextToSpeech *x;
};
#endif // MAINWINDOW_H

//mainwindow.cpp
#include "mainwindow.h"
#include "ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    x=new QTextToSpeech;
}

MainWindow::~MainWindow()
{
    delete ui;
}


void MainWindow::on_pushButton_clicked()
{
    x->say("吃饭了吗");
}


```

