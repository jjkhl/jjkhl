# Makefile
文件名：`Makefile`

**变量：**

预定义变量：

AR：默认值ar

CC：c编译器

CXX：c++编译器

获取变量的值：

`$@`：目标的完整名称

`$<`：第一个依赖文件的名称

`$^`：所有依赖文件

**模式匹配：**

`%.o:%.c`

`%`：匹配一个字符串

`:=`	表示覆盖之前的值

```shell
x=foo
y=$(x) bar
x=xyz
# y=xyz bar

x:=foo
y:=$(x) bar
x:=xyz
# y=foo bar
```

`?=` 	如果没有被赋值过就赋予等号后面的值

`+=`	增加等号后面的值

**函数：**

* wildcard PATTERN...
  * 功能：获取指定目录下指定类型的文件列表
  * PATTERN：某个或多个目录对应的某种类型的文件，一般空格间隔
  * 返回：得到若干个文件的文件列表，文件名之间使用空格间隔
  * 实例：
  ```
  #(wildcard *.c ./sub/*.c)
  返回格式：a.c b.c c.c
  ```

* `$(patsubst <pattern>,<replacement>,<text>)`

  * 功能：查找`<text>`中的单词(以空格、tal或回车、换行分隔)是否符合模式`<pattern>`，如果匹配，则以`<replacement>`替换
  * `'\'`进行转义，`\%`表示真正的`%`字符
  * 返回：函数返回被替换后的字符串
  * 实例：
  ```shell
  $(patsubst %.c,%.o,x.c bar.c)
  返回值格式：x.o bar.o
  ```

* subst( from, to, text)

    * 功能：将text中的from字符串替换为to字符串，返回替换后的text

* notdir和dir

  * 功能：取出文件名中的路径信息/取出目录部分

  ```shell
  src=$(notdir ./src/a.cpp)
  # src=a.cpp
  src=$(dir b.cpp ./src/a.cpp)
  # src=./ ./src/
  ```

* $(strip text)

    * 功能：去掉text开头和结尾的空字符，并将字符串中多个连续空字符合并为一个空字符

    ```shell
    SRCS = a.c b.c c.c
    OBJS = $(subst .c,.o,$(SRCS))
    # OBJS=a.o b.o c.o
    ```

* $(filter PATTERN, TEXT)

    * 功能：保留TEXT中符合PATTERN模式的字符串

    ```shell
    SRCS = a.c b.c a.h b.h c.so
    RST = $(filter %.c, $(SRCS))
    # RST=a.c b.c
    ```

    

* $(filter-out PATTERN, TEXT)

    * 功能反过滤函数，保留不符合PATTERN模式的字符串

    ```shell
    SRCS = a.c b.c a.h b.h c.so
    RST = $(filter-out %.c, $(SRCS))
    # RST=a.h b.h c.so
    ```

* 包含头文件路径

  ```shell
  includes= -I ./include
  ```

* $(addsuffix suffix, names)

  * 功能：往每一个names中加入后缀suffix

  ```shell
  $(addsuffix .c,foo bar)
  # 返回foo.c bar.c
  ```

* 包含另外一个文件：include

    ```shell
    include file.dep
    ```

* $(foreach var, list,text)

    * 功能：把参数list中的单词逐个取出放到参数var指定的变量中，然后再执行text所包含的表达式

    ```shell
    names := a b c d
    files := $(foreach n, $(names), $(n).o)
    #files值为a.o b.o c.o d.o
    ```

    

同一目录下：

```shell
总体写法：
目标文件:使用文件列表
        shell命令
//如果使用了@shell命令，则终端上不会显示shell指令
写法一：
app:sub.c add.c mult.c div.c main.c
        gcc sub.c add.c mult.c div.c main.c -o app
写法二：
app:sub.o add.o mult.o div.o main.o
        gcc sub.o add.o mult.o div.o main.o -o app1
sub.o:sub.c
        gcc -c sub.c -o sub.o
add.o:add.c
        gcc -c add.c -o add.o
mult.o:mult.c
        gcc -c mult.c -o mult.o
div.o:div.c
        gcc -c div.c -o div.o
main.o:main.c
        gcc -c main.c -o main.o 
写法三（变量法）：
#定义变量
src=sub.o add.o mult.o div.o main.o
target=app3
$(target):$(src)
        $(CC) $^ -o  $(target)
sub.o:sub.c
        gcc -c sub.c -o sub.o
add.o:add.c
        gcc -c add.c -o add.o
mult.o:mult.c
        gcc -c mult.c -o mult.o
div.o:div.c
        gcc -c div.c -o div.o
main.o:main.c
        gcc -c main.c -o main.o 

写法六：模式匹配
src=sub.o add.o mult.o div.o main.o
target=app3
$(target):$(src)
        $(CC) $^ -o  $(target)
%.o:%.c
        gcc -c $< -o $@

写法五：函数
1. wildcard
src=$(wildcard ./*.c)
target=app1
$(target):$(src)
        $(CC) $^ -o  $(target)
%.o:%.c
        gcc -c $< -o $@

2. patsubst
src=$(wildcard ./*.c)
objs=$(patsubst %.c,%.o,$(src))
target=app1
$(target):$(objs)
        $(CC) $(objs) -o  $(target)
%.o:%.c
        gcc -c $< -o $@

#定义为伪目标，不会对clean进行更新检查
.PHONY:clean
clean:
    rm $(objs) -f#删除生成的.o文件

手动clean命令行：`make clean`

如果需要同时执行，可以定义一个all
all:$(target) clean
```

