# Chrono库的使用
参考网站：https://www.eet-china.com/mp/a74844.html
基本使用方式：
```c++
//新纪元时间1970年1月1日8点
//代码运行时间
#include<iostream>
#include<chrono>
using namespace std;
int main()
{
    chrono::system_clock::time_point start=chrono::system_clock::now();
    //函数运行
    chrono::system_clock::time_point end=chrono::system_clock::now();
    chrono::microseconds dt=chrono::duration_cast<chrono::microseconds>(end - start);
    //auto dt_nanosecs=end-start;
    cout << "总共耗时: " << dt.count() << "微妙" << endl;
}

//格式化输出当前时间
#include <chrono>
#include <iostream>
#include<iomanip>
using namespace std;
using namespace std::chrono;
int main()
{
    system_clock::time_point epoch;
    time_t tm=system_clock::to_time_t(epoch);
    cout<<"新纪元时间为："<<put_time(localtime(&tm),"%Y-%m-%d %H.%M.%S")<<endl;
    system("pause");
}
```
## 基本库
头文件：`<chrono>`
```c++
template<
    class Rep,
    class Period = std::ratio<1>
> class duration;
```
* `ratio类`表示每个时钟周期的秒数，其中第一个模板参数`Rep`表示分子，`Period`表示分母，默认为1s。
示例：
ratio<2>表示一个时钟周期是2s
ratio<1,1000>表示1ms
> 为了方便使用，标准库定义了一些常用给的时间间隔

| 类型 | 定义 |
|:----:|:----:|
|纳秒|std::chrono::nanoseconds|
|微秒|std::chrono::microseconds|
|毫秒|std::chrono::milliseconds|
|秒|std::chrono::seconds|
|分钟|std::chrono::minutes|
|小时|std::chrono::hours|

## `duration类`
```c++
// 1. 拷贝构造函数
duration( const duration& ) = default;
// 2. 通过指定时钟周期的类型来构造对象
template< class Rep2 >
constexpr explicit duration( const Rep2& r );
// 3. 通过指定时钟周期类型，和时钟周期长度来构造对象
template< class Rep2, class Period2 >
constexpr duration( const duration<Rep2,Period2>& d );
```
|操作符的重载|描述|
|:---:|:---:|
|operator=|赋值内容(公开成员函数)|
|operator- operator+|赋值内容(公开成员函数)|
|operator++ operator--|递增或递减周期计数(公开成员函数)|
|operator+= operato-= operator*= operator/=|实现两个时长间的复合赋值(公开成员函数)|

示例：
```c++
#include <chrono>
#include <iostream>
using namespace std;
int main()
{
    chrono::hours h(1);                          // 一小时
    chrono::milliseconds ms{ 3 };                // 3 毫秒
    chrono::duration<int, ratio<1000>> ks(3);    // 3000 秒

    // chrono::duration<int, ratio<1000>> d3(3.5);  // error
    chrono::duration<double> dd(6.6);               // 6.6 秒

    // 使用小数表示时钟周期的次数
    chrono::duration<double, std::ratio<1, 30>> hz(3.5);

     std::chrono::milliseconds ms{3};         // 3 毫秒
    std::chrono::microseconds us = 2*ms;     // 6000 微秒
    // 时间间隔周期为 1/30 秒
    std::chrono::duration<double, std::ratio<1, 30>> hz(3.5);
 
    std::cout <<  "3 ms duration has " << ms.count() << " ticks\n"
              <<  "6000 us duration has " << us.count() << " ticks\n"
              <<  "3.5 hz duration has " << hz.count() << " ticks\n";  
}
```
## `duration类`的`count`的使用
```c++
#include <iostream>
#include <chrono>
using namespace std;

int main()
{
    chrono::minutes t1(10);
    chrono::seconds t2(60);
    chrono::seconds t3 = t1 - t2;
    cout << t3.count() << " second" << endl;
}
```

## 时间点(time point)和时钟类`system_clock`
```c++
template<
    class Clock,
    class Duration = typename Clock::duration
>class time_point;
```
duration：时间间隔为 rep*period 纳秒 chrono::duration<rep, period>

time_point：时间点通过系统时钟做了初始化 chrono::time_point<system_clock>，里面记录了新纪元时间点

比如，我们要获取当前的系统时间，并且需要将其以能够识别的方式打印出来，示例代码如下：
```c++
#include <chrono>
#include <iostream>
using namespace std;
using namespace std::chrono;
int main()
{
    // 新纪元1970.1.1时间
    system_clock::time_point epoch;

    duration<int, ratio<60*60*24>> day(1);
    // 新纪元1970.1.1时间 + 1天
    system_clock::time_point ppt(day);

    using dday = duration<int, ratio<60 * 60 * 24>>;
    // 新纪元1970.1.1时间 + 10天
    time_point<system_clock, dday> t(dday(10));

    // 系统当前时间
    system_clock::time_point today = system_clock::now();
    
    // 转换为time_t时间类型
    time_t tm = system_clock::to_time_t(today);
    cout << "今天的日期是:    " << ctime(&tm);

    time_t tm1 = system_clock::to_time_t(today+day);
    cout << "明天的日期是:    " << ctime(&tm1);

    time_t tm2 = system_clock::to_time_t(epoch);
    cout << "新纪元时间:      " << ctime(&tm2);

    time_t tm3 = system_clock::to_time_t(ppt);
    cout << "新纪元时间+1天:  " << ctime(&tm3);

    time_t tm4 = system_clock::to_time_t(t);
    cout << "新纪元时间+10天: " << ctime(&tm4);
}
```
## steady_clock
在 C++11 中提供的时钟类 steady_clock 相当于秒表，只要启动就会进行时间的累加，并且不能被修改，非常适合于进行耗时的统计。
```c++
struct steady_clock { // wraps QueryPerformanceCounter
    using rep                       = long long;
    using period                    = nano;
    using duration                  = nanoseconds;
    using time_point                = chrono::time_point<steady_clock>;
    static constexpr bool is_steady = true;

    // get current time
    _NODISCARD static time_point now() noexcept 
    { 
        // doesn't change after system boot
        const long long _Freq = _Query_perf_frequency(); 
        const long long _Ctr  = _Query_perf_counter();
        static_assert(period::num == 1, "This assumes period::num == 1.");
        const long long _Whole = (_Ctr / _Freq) * period::den;
        const long long _Part  = (_Ctr % _Freq) * period::den / _Freq;
        return time_point(duration(_Whole + _Part));
    }
};
```
假设要测试某一段程序的执行效率，可以计算它执行期间消耗的总时长，示例代码如下：
```c++
#include <chrono>
#include <iostream>
using namespace std;
using namespace std::chrono;
int main()
{
    // 获取开始时间点
    steady_clock::time_point start = steady_clock::now();
    // 执行业务流程
    cout << "print 1000 stars ...." << endl;
    for (int i = 0; i < 1000; ++i)
    {
        cout << "*";
    }
    cout << endl;
    // 获取结束时间点
    steady_clock::time_point last = steady_clock::now();
    // 计算差值
    auto dt = last - start;
    cout << "总共耗时: " << dt.count() << "纳秒" << endl;
}
```
## high_resolution_clock
high_resolution_clock 提供的时钟精度比 system_clock 要高，它也是不可以修改的。在底层源码中，这个类其实是 steady_clock 类的别名。
使用方法与steady_clock一样。

## duration_cast
在源周期能准确地为目标周期所整除的场合（例如小时到分钟），浮点时长和整数时长间转型能隐式进行无需使用 duration_cast ，其他情况下都需要通过函数进行转换。
```c++
#include <iostream>
#include <chrono>
using namespace std;
using namespace std::chrono;

void f()
{
    cout << "print 1000 stars ...." << endl;
    for (int i = 0; i < 1000; ++i)
    {
        cout << "*";
    }
    cout << endl;
}

int main()
{
    auto t1 = steady_clock::now();
    f();
    auto t2 = steady_clock::now();

    // 整数时长：要求 duration_cast
    auto int_ms = duration_cast<chrono::milliseconds>(t2 - t1);

    // 小数时长：不要求 duration_cast
    duration<double, ratio<1, 1000>> fp_ms = t2 - t1;

    cout << "f() took " << fp_ms.count() << " ms, "
        << "or " << int_ms.count() << " whole milliseconds\n";
}
```
# 文件流(fstream)
[c++文件流](https://blog.csdn.net/seadplus/article/details/7802346)
```c++
//ifstream是指从硬盘到内存，输入读取文件；ostream是指从内存到硬盘，属于写入文件
fstream //文件输出流
ifstream //输入文件流
oftream //输出文件流
```

## 文件打开方式选项
```c++
ios::in　　　　= 0x01,　//供读，文件不存在则创建(ifstream默认的打开方 式)
ios::out　　　 = 0x02,　//供写，文件不存在则创 建，若文件已存在则清空原内容(ofstream默认的打开方式)
ios::ate　　　 = 0x04,　//文件打开时，指针在文件最后。可改变指针的位置，常和in、out联合使用
ios::app　　　 = 0x08,　//供写，文件不存在则创建，若文件已存在则在原文件内容后写入 新的内容，指针位置总在最后
ios::trunc　　 = 0x10,　// 在读写前先将文件长度截断为0（默认）
ios::nocreate　= 0x20,　//文件不存在时产生错误，常和in或app联合使用
ios::noreplace = 0x40,　//文件存在时产生错误，常和out联合使用
ios::binary　　= 0x80　 //二进制格式文件
```

## 打开文件的方式
```c++
//方式一：调用构造函数时指定文件名和打开模式
fstream f("1.txt",ios::in|ios::out|ios::binary); //以读/写/二进制的方式打开文件
//方式二：open成员函数
fstream f;
f.open("1.txt",ios::out);
```

## 字符串读取方式
```c++
fstream fp("1.txt",ios::out)
string a;
getline(fp,a);
getline(fp,a);//再次调用，读取第二行
```

## 文件位置指针
```c++

// 定位到 fileObject 的第 n 个字节（假设是 ios::beg）
fileObject.seekg( n );
 
// 把文件的读指针从 fileObject 当前位置向后移 n 个字节
fileObject.seekg( n, ios::cur );
 
// 把文件的读指针从 fileObject 末尾往回移 n 个字节
fileObject.seekg( n, ios::end );
 
// 定位到 fileObject 的末尾
fileObject.seekg( 0, ios::end );
```

## 示例：
```c++

#include <fstream>
#include <iostream>
using namespace std;
 
int main ()
{
    
   char data[100];
 
   // 以写模式打开文件
   ofstream outfile;
   outfile.open("afile.dat");
 
   cout << "Writing to the file" << endl;
   cout << "Enter your name: "; 
   cin.getline(data, 100);
 
   // 向文件写入用户输入的数据
   outfile << data << endl;
 
   cout << "Enter your age: "; 
   cin >> data;
   cin.ignore();
   
   // 再次向文件写入用户输入的数据
   outfile << data << endl;
 
   // 关闭打开的文件
   outfile.close();
 
   // 以读模式打开文件
   ifstream infile; 
   infile.open("afile.dat"); 
 
   cout << "Reading from the file" << endl; 
   infile >> data; 
 
   // 在屏幕上写入数据
   cout << data << endl;
   
   // 再次从文件读取数据，并显示它
   infile >> data; 
   cout << data << endl; 
 
   // 关闭打开的文件
   infile.close();
 
   return 0;
}
```
# 文件指针(FILE)
参考网址:https://blog.csdn.net/qq_44757034/article/details/104696262
## 基本格式
```c++
//头文件
#include<stdio.h>
FILE *fp;
//打开文件
fopen("1.txt",r);
fclose(fp);
```
## 打开方式选项
|符号|含义|
|:---:|:---|
|r|只读,文件不存在则失败|
|r+|允许读写,文件不存在则失败|
|w|只写覆盖,文件不存在就新建文件|
|w+|允许读写,文件不存在就新建文件|
|a|追加,文件不存在就新建文件|
|rb|只读方式打开二进制文件|

## 对文件操作的函数

