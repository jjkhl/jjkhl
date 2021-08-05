<h1 align="center">GDB调试</h1>

## 安装gdb、gcc、g++、cmake

### centos

1. yum install gdb

2. yum install gcc

3. yum install g++

4. yum install cmake

   [安装教程](https://blog.csdn.net/dream_1996/article/details/69397089)

### ubuntu

sudo apt update

1. sudo apt install build-essential gdb
2. sudo apt install cmake

$\textcolor{red}{检测是否安装成功}$

```shell
gcc --version
g++ --version
gdb --version
```

## 安装GCC编译器

### 前言

  VScode是通过调用GCC编译器来完成对c++的编译

### 过程

:set ts=4：按下tab键实现4个空格(默认8个空格)

1. 预处理(Pre)——.i文件
    -E选项指示编译器只对输入文件进行预处理
```c++
  g++ -E test.cpp-o test.i
```
2. 编译(Compiling)——.s文件

   -S 选项告诉g++在为C++代码产生了汇编语言文件后停止编译

 ```c++
   g++ -S test.i -o test.s
 ```

   

3. 汇编(Assembling)——.o文件

   -c选项告诉g++只把源代码编译为机器语言的目标代码

```c++
   g++ -c test.i -o test.o
```

   

4. 链接(Linking)——bin文件

   -o 选项来为将产生的可执行文件命名

```c++
   g++ test.o -o test
```

5. 直接运行：./test

   查看运行时间：time ./test

### g++重要编译参数

```bash
1. 编译带调试信息的可执行文件：-g
    产生带调试信息的可执行文件：g++ -g test.cpp -o test
2. 优化源代码：-O[n]
    定义：比如省略代码中从未使用的变量、直接将常量表达式用结果值代替等，这些操作会缩减目标文件所包含的代码量，提高最终生成的可执行文件的运行效率
    -O：同时减小代码的长度和执行时间，效果等价于-O1
    -O0：不做优化
    -O1：默认
    -O2：除完成-O1的优化外，还进行一些额外的调整工作，如指令调整等
    -O3：包括循环展开和其它一些与处理特性相关的优化工作
    示例：使用-O2优化源代码，并输出可执行文件：g++ -O2 test.cpp -o test
3. 指定库文件|指定库文件路径：-l(L的小写)  |  -L
    -l默认路径：/lib      /usr/lib       usr/local/lib
    链接glog库：g++ -lglog test.cpp
    链接mytest库，libmytest.so在/home/bing/mytestlibfolder目录下：
    g++ -L/home/bing/mytestlibfolder -lmytest test.cpp
4. 指定头文件搜索目录：-I(i的大写)
    /usr/include目录一般不用指定，如果头文件放在/myinclude里面：g++ -I/myinclude test.cpp
5. 打印警告信息：-Wall
    g++ -Wall test.cpp
6. 关闭警告信息：-w
    g++ -w test.cpp
7. 设置编译标准：g++ -std=c++11
8. 输出指定文件名test01：g++ test.cpp -o test01
   默认输出a.out
9. 定义宏：-D
   打开   
```
实战演练
```bash
直接运行：g++ main.cpp src/swap.cpp -Iinclude

增加参数编译运行：g++ main.cpp src/swap.cpp -Iinclude -std=c++11 -o2 -Wall -o b.out

```

### 生成库文件并编译

#### 链接静态库生成可执行文件①：

```bash
# 汇编，生成swap.o文件
g++ swap.cpp -c -I../include
#生成静态库libswap.a
ar rs libswap.a swap.o
#链接，生成可执行文件staticmain
g++ main.cpp -Iinclude -Lsrc -lswap -o staticmain
#执行
./staticmain
```

#### 链接动态库生成可执行文件②：(内存占用小)

```bash
#生成东陶库libswap.so
g++ swap.cpp -I../include -fPIC -shared -o libswap.so
#-fPIC：与路径无关    -shared：生成动态库文件
#等价于gcc swap.cpp -I../include -c -fPIC
#gcc -shared -o libswap.so swap.o

#链接生成可执行文件sharemain
g++ main.cpp -Iinclude -Lsrc -lswap -o sharemain
#-l指定库文件名
#运行,指定动态库的搜索路径
LD_LIBRARY_PATH=src ./sharemain
```

## GDB调试器

vscode是通过调用GDB调试器来实现c/c++调试工作

### 常用调试命令参数

格式：gdb [exefilename]，exefilemane为要调试的可执行文件名

**编译程序时需要加上-g，才能使用gdb调试：gcc -g main.c -o main**

**回车键：直接重复上一个命令**

```bash
#以下命令后括号内为命令的简化使用，比如run(r)，直接输入r就代表run
$(gdb)help(h)
$(gdb)run(r)			#重新开始运行文件(run-text：加载文本文件，run-bin：加载二进制文件)
$(gdb)start				#单步执行
$(gdb)list(l)			#查看源代码(list-n，第n行开始查看代码。list+函数名：查看具体函数)
$(gdb)set 				#设置变量的值
$(gdb)next(n)			#单步调试(逐过程，函数直接执行)
$(gdb)step(s)			#单步调试(逐语句，跳入自定义函数内部执行)
$(gdb)backtrace(bt)		#查看函数的调用的栈帧和层级关系
$(gdb)frame(f)			#切换函数的栈帧
$(gdb)info(i)			#查看函数内部局部变量的数值
$(gdb)finish			#结束当前函数，返回到函数调用点
$(gdb)continue(c)		#继续运行
$(gdb)print(p)			#打印值及地址(一次性)
$(gdb)quit(q)			#退出gdb
```

```bash
$(gdb)break num						#在第num行设置断点
$(gdb)info breakpoints				#查看当前设置的所有断点
$(gdb)delete breakpoints num(d)		#删除第num个断点
$(gdb)dispaly						#追踪查看具体变量(一直追踪)
$(gdb)undisplay						#取消追踪具体变量
$(gdb)watch							#被设置的观察点的变量发生修改时，打印显示
$(gdb)i watch						#显示观察点
$(gdb)enable breakpoints			#启用断点
$(gdb)disable breakpoints			#禁用断点
$(gdb)x								#查看内存x/20xw：显示20个单元，16进制，4字节每单元
$(gdb)run argv[1] argv[2]			#调试时命令行传参
$(gdb)set follow-fork-mode child	#Makefile项目管理：选择跟踪父子进程
```

### 实战

vim中显示行号：:set nu

进入到gdb调试后，ctrl+x然后ctrl+a进入tui模式

## VScode使用

### 安装

```bash
sudo snap install --classic code
```

或

```bash
#以 sudo 用户身份运行下面的命令，更新软件包索引，并且安装依赖软件
sudo apt update
sudo apt install software-properties-common apt-transport-https wget
#使用 wget 命令插入 Microsoft GPG key 
wget -q https://packages.microsoft.com/keys/microsoft.asc -O- | sudo apt-key add -
#启用 Visual Studio Code 源仓库
sudo add-apt-repository "deb [arch=amd64] https://packages.microsoft.com/repos/vscode stable main"
#安装
sudo apt install code
#更新
sudo apt update
sudo apt upgrade
```

### 常用快捷键

| 转到文件/其它常用操作 | ctrl+p       | 关闭当前文件     | ctrl+w  |
| --------------------- | ------------ | ---------------- | ------- |
| 打开命令面板          | ctrl+shift+p | 当前行上/下移动  | alt+↑/↓ |
| 打开终端              | ctrl+`       | 白能量统一重命名 | F2      |
| 关闭侧边栏            | ctrl+b       | 转到定义出       | F12     |
| 复制文本              | ctrl+c       | 粘贴文本         | ctrl+v  |
| 保存文本              | ctrl+s       | 撤销操作         | ctrl+z  |

1. **在ctrl+p窗口下还可以：**
  * 直接输入文件名，直接跳转到文件
  * 列出当前可执行操作：？
  * 显示Errors或Warnings：！或ctrl+shift+m
  * 跳转到行数：:或ctrl+g
  * 跳转到symbol(搜索变量或函数)：@或ctrl+shift+o
  * 根据名字查找symbol：#或ctrl+t

2. **代码行编辑快捷键**：

  * 代码行缩进：ctrl+[  或  ctrl+]
  * 代码格式标准化：shift+alt+f  或 ctrl+shift+p后输入format code
  * 向下或向上复制一行：alt+shift+↓     alt+shift+↑
  * 在当前行下面插入一行：ctrl+enter
  * 在当前行上面插入一行：ctrl+shift+enter 
  * 删除光标右侧所有字：ctrl+delete
  * 多行编辑(列编辑)：alt+shift+鼠标左键  或   alt+shift+up/down

## cmake的使用

cmake是一个**跨平台**的安装编译工具，可以用简单的语句来描述所有平台的安装过程

[单文件和多文件的调试](https://blog.csdn.net/qq_42429142/article/details/113274450)

[json的配置](JSON的配置使用.md)

* 基本语法格式：指令(参数1 参数2…)
  * 参数使用括弧括起
  * 参数之间用空格或分号分开
* 指令大小写无关，参数和变量大小写相关
```bash
set(HELLO hello.cpp)
add_executable(hello main.cpp hello.cpp)
ADD_EXECUYABLE(hello main.cpp ${HELLO}) 
#变量使用${}方式取值，但是在IF控制语句中直接使用变量名
```

### <span id="jump1">重要指令和CMake常用变量</span>

```cmake
#指定CMake最小版本要求位2.8.3
cmake_minimm_required(VERSION 2.8.3)

#指定工作名为HELLO
project(HELLO)

#定义SRC变量，其值为main.cpp hello.cpp
set(SRC main.cpp hello.cpp)

#将/usr/include/myincludefolder和./include添加到头文件搜索路径
include_directories(/usr/include/myincludefolder ./include)
等价于g++ -Iinclude

#将/usr/lib/mylib和./lib添加到库文件搜索路径
link_directories(/usr/lib/mylib ./lib)

#通过变量SRC生成hello.so共享库   SHRED-动态库  STATIC-动态库 
add_library(hello SHARED ${SRC})

#添加编译参数 -Wall -std=c++11
add_compile_options(-Wall -std=c++11)

#编译main.cpp生成可执行文件main
add_executable(main main.cpp)
等价于g++ main.cpp -o main

#将hello动态库文件连接到可执行文件main
target_link_libraries(main hello)

#向当前过程添加存放源文件的子目录，并可以指定中间二进制和目标二进制存放的位置
#添加src子目录，src中需要有一个CMakeLists.txt
add_subdirectory(src)

#发现一个目录下所有的源代码文件并将列表存储在一个变量中，aux_source_directory被临时用来自动构建源文件列表
#定义SRC变量，其值为当前目录下所有源代码文件
aux_source_directory(. SRC)
#编译SRC变量所代表的源代码文件，生成main可执行文件
add_executable(main ${SRC})
```

* [动态库和静态库](###生成库文件并编译)

```cmake
#CMAKE_C_FLAG  gcc编译选项
#CMAKE_CXX_FLAG编译选项
#在CMAKE_CXX_FLAG编译选项后追加-std=c++11
set( CMAKE_CXX_FLAG "${CMAKE_CXX_FLAGS} -std=c++11")

#设定编译类型为debug，调试时需要选择debug
set(CMAKE_BUILD_TYPE Debug)
#设定编译类型为release，发布时需要选择release
set(CMAKE_BUILD_TYPE Release)

可执行文件的存放路径：EXECUTABLE_OUTPUT_PATH
库文件输出的存放路径：LIBRAY_OUTPUT_PATH
```

### Cmake编译工程

Cmake目录结构：项目主目录存在一个CMakeLists.txt文件

**两种方式设置编译规则：**

1. 包含源文件的子文件夹包含CMakeLists.txt，主目录的CMakeLists.txt通过addsubdirectory添加子目录

2. 包含源文件的子文件夹不包含CMakeLists.txt，子目录编译规则体现在主目录的CMakeLists.txt中

#### 编译流程

**在Linux下使用CMake构建C/C++过程流程：**

* 手动编写CMakeLists.txt
* 执行命令cmake PATH生成Makefile(PATH是顶层CMakeLists.txt所在目录)
* 执行命令make进行编译

| .    | 当前目录 |
| ---- | -------- |
| ./   | 当前目录 |
| ..   | 上级目录 |
| ../  | 上级目录 |

推荐的外部构建：

```cmake
#1.在当前目录下，创建build文件夹
mkdir build
#2.进入build文件夹
cd build
#3.编译上级目录的CMakeLists。txt，生成Makefile和其他文件
#如果电脑上有vs，使用一次(cmake -G "MinGW Makefiles" ..)代替cmake 
#或者直接F1输入cmake，选择GNU
cmake ..
#4.执行make目录，生成target
make
```

具体可以查看[JSON的配置使用](JSON的配置使用.md)

