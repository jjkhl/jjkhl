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