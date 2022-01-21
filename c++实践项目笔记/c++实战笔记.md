<h5 align="center">实战笔记基于书籍《C++实战笔记_罗剑锋》</h5>
# 第一章c++开发综述
## 变量命名方式
* 变量、函数名和命名空间用snake_case方式，全局变量加“g_”前缀
* 自定义类名用驼峰式(CamelCase)风格，成员函数用snake_case,成员变量加“m_”前缀
* 宏和常量全部大写，单词之间使用下划线连接
* 不要将下划线作为变量的前缀或者后缀
**示例：**
```c++
#define MAX_PATH_LEN 256//常量全部大写
int g_sys_flag;//全局变量
namespace linux_sys{//命名空间，全部小写
    void get_rlimit_core();
}
class FilePath final//类名，首字母大写
{
    public:
        void set_path(const string& str);//函数，全小写
    private:
        string m_path;
        int m_level;//成员变量添加前缀
};
```
# 预处理阶段
## include
作用是包含任意文件，可以编写一些代码片段，存进`*.inc`文件里，然后再预处理阶段有选择地加载。
示例：
```c++
//calc_values.inc
static unit32_t calc_table[] = {
    ...
};
//使用方式
#include "calc_values.inc"
static unit32_t* calc_table1={
    calc_table
};
```
## define
宏的展开、替换发生在预处理阶段，不涉及函数调用、参数传递、指针寻址，没有任何运行期的效率损失，所以对于调用一些频繁的小代码片段来说，用宏封装的效果比使用inline关键字要好。
但是，宏定义没有作用域概念，永远是全局生效，所以对于一些用来简化代码、起临时作用的宏，最后用完需要用`#undef`取消定义。
**示例：**
```c++
//方式一
#define CUBE(a) (a)*(a)*(a)
cout<<CUBE(10)<<endl;
#undef CUBE
//方式二
#ifdef AUTH_PWD
#undef AUTH_PWD
#endif
#define AUTH_PWD "xxx"
```
**文本替换示例**
```c++
#include<iostream>
#define BEGIN(x) namespace x {//使用BEGIN(X)替换了namespace {
#define END(x)  }//使用END(X)
BEGIN(x)
void hello(*-+){
    std::cout<<"hello x"<<std::endl;
}
END(x)
using namespace std;
int main(int argc,char *argv[])
{
    x::hello();
    system("pause");
    return 0;
}
```
## 预定宏编译
|变量名|含义|
|:--:|:--:|
|__cpluscplus|c++语言的版本号|
|`__FILE__`|源文件名字|
|`__LINE__`|源文件行号|
|`__DATE__`|预处理时的日期|
|__has_include|是否存在某个可包含文件|
|__cpp_modules|是否支持模块机制|
|__cpp_decltype|是否支持decltype特性|
|__cpp_decltyoe_auto|是否支持decltype(auto)特性|
|__cpp_lib_make_unique|是否提供函数make_unique()|
## 编译阶段的属性介绍
属性使用两对方括号的形式表示，即`[[...]]`
|变量名|含义|
|:--:|:--:|
|noreturn|显示声明函数不返回任何值|
|nodiscard|显示声明不允许忽略函数返回值|
|deprecated|允许当不建议使用(会出现警告)|
|maybe_unused|显示标记某段代码暂时不用，但保留|
|gnu::const|标记函数时无副作用的常量函数，让编译器积极优化|
|gnu::constructor|函数会在main()之前执行，效果类似于全局对象的构造函数|
|gnu::destructor|函数会在main()之后执行，效果类似于全局对象的析构函数|
|gnu::always_inline|要求编译器强制内联函数，效果比inline关键字强|
|gnu::hot|标记"热点"函数，要求编译器更积极优化|
## 静态断言和动态断言
### 动态断言
含义：程序运行时检查断言
头文件：<cassert>
宏：`assert`
示例：assert(p=227)
效果：断言一个表达式必定为真，如果判断为假，则会输出错误消息，然后调用函数abort()终止程序的运行。
### 静态断言
含义：程序编译时检查断言
宏：`static_assert`
示例：
```c++
static_assert(sizeof(long)>=8,"must run on x64")
```
效果：编译阶段如果表达式的值是false就会报错，导致编译失败。
检查范围：只能检查编译时的阐述和类型，无法检测运行时的变量、指针、内存数据等。

### 模板元函数
```c++
//c++17模板元函数，类似于is_xxx<T>::value
static_assert(is_integral_V<T>);//断言T是整数类型
static_assert(is_pointer_V<T>);//断言T是指针类型
static_assert(is_default_constructible_V<T>);//断言T是有默认构造函数
```
# C++核心语言特性
## 编码准则
### final标识符
```c++
class DemoClass final//静止任何人继承
{...};

class Interface
{
    virtual void f()=0;
};

class Abstract: public Interface{
    virtual void f() final //虚函数，有final，禁止子类继承
    {...}
};

class Implement final: public Abstract//实现类，final禁止其被继承
{
    ...
};
```

### default/delete函数
* 类的六大基本函数
构造函数、析构函数、复制构造函数、复制赋值函数、转移构造函数、转移赋值函数
* default
对于比较重要德构造函数和析构函数，使用`=default`形式能明确地告诉编译器进行默认实现。
```c++
class DemoClass final
{
    public:
        DemoClass()=default;//明确告诉编译器，使用默认实现
        ~DemoClass()=default;//明确告诉编译器，使用默认实现
}
```
* delete
对于任何函数形式，明确禁止该形式的使用
```c++
class DemoClass final
{
    public:
        DemoClass(const DemoClass&) = delete;//禁止复制构造函数
        DemoClass & operator=(const DemoClass&) = delete;//禁止复制赋值函数
};
//编译时代码报错
DemoClass obj1;
DemoClass obj2=obj1;//错误，不可复制
```
### explicit函数
explicit关键字只能用于类内部的构造函数声明上，而不能用在类外部的函数定义(函数实现)上，它的作用是不能进行隐式转换；explicit关键字作用于单个参数的构造函数，如果构造函数有多个参数，但是从第二个参数开始，如果各参数均有默认赋值，也可以应用explicit关键字
```c++
class DemoClass final
{
    public:
        explicit DemoClass(const string_type& str);//显式单参数构造函数
        explicit operator bool();//显式转型为bool
};
//错误方式
DemoClass obj = "stint ctor";
bool b=obj;
//正确方式
DemoClass obj = (DemoClass) "sting ctor";
bool b = static_cast<bool>(obj);
```
## [委托构造函数](https://cloud.tencent.com/developer/article/1187765#:~:text=%E5%A7%94%E6%89%98%E6%9E%84%E9%80%A0%E5%87%BD%E6%95%B0%EF%BC%88Delegating,Constructor%EF%BC%89%E7%94%B1C%2B%2B11%E5%BC%95%E5%85%A5%EF%BC%8C%E6%98%AF%E5%AF%B9C%2B%2B%E6%9E%84%E9%80%A0%E5%87%BD%E6%95%B0%E7%9A%84%E6%94%B9%E8%BF%9B%EF%BC%8C%E5%85%81%E8%AE%B8%E6%9E%84%E9%80%A0%E5%87%BD%E6%95%B0%E9%80%9A%E8%BF%87%E5%88%9D%E5%A7%8B%E5%8C%96%E5%88%97%E8%A1%A8%E8%B0%83%E7%94%A8%E5%90%8C%E4%B8%80%E4%B8%AA%E7%B1%BB%E7%9A%84%E5%85%B6%E4%BB%96%E6%9E%84%E9%80%A0%E5%87%BD%E6%95%B0%EF%BC%8C%E7%9B%AE%E7%9A%84%E6%98%AF%E7%AE%80%E5%8C%96%E6%9E%84%E9%80%A0%E5%87%BD%E6%95%B0%E7%9A%84%E4%B9%A6%E5%86%99%EF%BC%8C%E6%8F%90%E9%AB%98%E4%BB%A3%E7%A0%81%E7%9A%84%E5%8F%AF%E7%BB%B4%E6%8A%A4%E6%80%A7%EF%BC%8C%E9%81%BF%E5%85%8D%E4%BB%A3%E7%A0%81%E5%86%97%E4%BD%99%E8%86%A8%E8%83%80%E3%80%82)
委托构造函数（Delegating Constructor）由C++11引入，是对C++构造函数的改进，允许构造函数通过初始化列表调用同一个类的其他构造函数，目的是简化构造函数的书写，提高代码的可维护性，避免代码冗余膨胀。
```c++
//不使用之前
class Foo
{
public:
    Foo() :type(4), name('x') {initRest();}
    Foo(int i) : type(i), name('x') {initRest();}
    Foo(char c) :type(4), name(c) {initRest();}

private:
    void initRest() {/* init othre members */}
    int type;
    char name;
    //...
};
//使用委托构造函数织构
class Foo
{
public:
    Foo() {initRest(); }
    Foo(int i) : Foo() {type = i;}
    Foo(char e) : Foo() {name = e;}
private:
    void initRest() { /* init othre members */}
    int type{1};
    char name{'a'};
};
```
## 成员变量初始化
在类里声明变量的同时给它赋值，实现初始化。
## 静态成员变量初始化
const的静态成员变量，可以在声明的时候初始化。
非const的静态成员变量，必须在实现文件"*.cpp"里初始化，因为需要分配唯一的存储空间。
内联变量可以保证无论头文件被包含多少次，静态成员变量也只有唯一一个全局实例。
**示例：**
```c++
class DemoInit final
{
    public:
        static const int x = 0;//静态常量可以直接初始化
        static string prefix = "xx";//无法通过编译
};
string DemoInit::prefix= "xx";//需要在类外实现初始化

//c++17解决类成员变量初始化形式的不一致问题
//内联变量
class DemoInit final
{
public:
    inline static string prefix = "xx";//c++17中编译正常
};
```
## 类型别名
```c++
using unit_t = unsigned int;
typedef unsigned int unint_t;
```
## 自动类型推导(auto、decltype)
### auto
* auto默认推导值类型
* auto只适用于初始化的场合
```c++
auto str = "hello";//自动推到为const char [6]类型
auto str = "hello"s;//c++14以后能推导出string类型
auto x= 10L;//auto推导出long，x是long
auto& x1=x;//auto推导出long，x1是long&
auto* x2=&x;//auto推导出long,x2是long*
const auto& x3=x;//auto推导出long，x3是const long&
auto x4=&x3;//auto推导出const long*,x4是const long*
auto&& x5=x;//总是推导出引用类型，auto推导出long,x5是long&

auto get_a_set(){
    std::set<int> a={1,2,3};
    return a;
}//c++14之后自动推导函数返回值
```
### decltype
```c++
int x=0;
decltype(x) x1;//推导为int，x1是int
decltype(x)& x2=x;//推导为int，x2是int&，引用必须赋值
decltype(x)* x3;//推导为int，x3是int*
decltype(&x) x4;//推导为int*，x4是int*
decltype(&x)* x5;//推导为int*，x5是int**
```
### 综合使用
```c++
int x=0;
decltype(auto) x1=(x);//推导为int&
decltype(auto) x2=&x;//推导为int*
decltype(auto) x3=x1；//推导为int&，x3和x1推导一致
```