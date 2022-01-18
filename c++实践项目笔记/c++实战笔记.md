**实战笔记基于书籍《C++实战笔记_罗剑锋》**
# 变量命名方式
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
void hello(){
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
|__FILE__|源文件名字|
|__LINE__|源文件行号|
|__DATE__|预处理时的日期|
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
