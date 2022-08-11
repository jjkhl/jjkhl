# Shell脚本

```shell
# 新建文本hello.sh
#! /bin/bash
echo 'hello world!'

#注释方式1
#注释方法2可以将!变换为任意符号如EOF
:<<!
注释方式二
!

:`
注释方式三
`
```

运行方式

```shell
# 方法1
sh hello.sh

# 方法二，使脚本具有执行权限
chmod +x hello.sh
./hello.sh
```

# Shell变量

```shell
# 设定变量
your_name="jjkhl"
#设定只读
readonly your_name
#删除变量
unset your_name
#输出变量
echo $your_name
echo ${your_name}
```

# Shell字符串

```shell
your_name="runoob"
# 使用双引号拼接
greeting="hello, "$your_name" !"
greeting_1="hello, ${your_name} !"
echo $greeting  $greeting_1

# 使用单引号拼接
greeting_2='hello, '$your_name' !'
greeting_3='hello, ${your_name} !'
echo $greeting_2  $greeting_3

#获取字符串长度
string="abcd"
echo ${#string}   # 输出 4

#提取子字符串
string="runoob is a great site"
echo ${string:1:4} # 输出 unoo

#查找字符串，示例位查找i或o第一个出现的位置
string="runoob is a great site"
echo `expr index "$string" io`  # 输出 4
```

# Shell数组

只支持一维数组

```shell
#一般形式
数组名=(值1 值2 ... 值n)

# 取得数组元素的个数，@表示所有元素
length=${#array_name[@]}
# 或者
length=${#array_name[*]}
# 取得数组单个元素的长度
lengthn=${#array_name[n]}

#关联数组
declare -A site=(["google"]="www.google.com", ["runoob"]="www.runoob.com", ["taobao"]="www.taobao.com")
echo ${site["runoob"]}

#获取所有元素
echo "数组的元素为: ${my_array[*]}"
echo "数组的元素为: ${my_array[@]}"

#获取所有键——!
echo "数组的键为: ${!site[*]}"
echo "数组的键为: ${!site[@]}"

```

# Shell传递参数

| 参数处理 | 说明                                                         |
| -------- | ------------------------------------------------------------ |
| $#       | 传递到脚本的参数个数                                         |
| $*       | 以一个单字符串显示所有向脚本传递的参数。  如"$*"用「"」括起来的情况、以"$1 $2 … $n"的形式输出所有参数。 |
| $$       | 脚本运行的当前进程ID号                                       |
| $!       | 后台运行的最后一个进程的ID号                                 |
| $@       | 与$*相同，但是使用时加引号，并在引号中返回每个参数。  如"$@"用「"」括起来的情况、以"$1" "$2" … "$n" 的形式输出所有参数。 |
| $-       | 显示Shell使用的当前选项，与[set命令](https://www.runoob.com/linux/linux-comm-set.html)功能相同。 |
| $?       | 显示最后命令的退出状态。0表示没有错误，其他任何值表明有错误。 |

# Shell基本运算符

```shell
#!/bin/bash
val=`expr 2 + 2`
echo "两数之和为 : $val"

# *号需要加反斜杠
val=`expr $a \* $b`
echo "a * b : $val"

if [ $a == $b ]
then
   echo "a 等于 b"
fi
if [ $a != $b ]
then
   echo "a 不等于 b"
fi

if [[ $a -lt 100 && $b -gt 100 ]]
then
   echo "返回 true"
else
   echo "返回 false"
fi
```

## 字符串运算符

| 运算符 |                     说明                     |           举例           |
| :----: | :------------------------------------------: | :----------------------: |
|   =    |   检测两个字符串是否相等，相等返回 true。    | [ $a = $b ] 返回 false。 |
|   !=   | 检测两个字符串是否不相等，不相等返回 true。  | [ $a != $b ] 返回 true。 |
|   -z   |    检测字符串长度是否为0，为0返回 true。     |  [ -z $a ] 返回 false。  |
|   -n   | 检测字符串长度是否不为 0，不为 0 返回 true。 | [ -n "$a" ] 返回 true。  |
|   $    |   检测字符串是否不为空，不为空返回 true。    |    [ $a ] 返回 true。    |

## 文件属性测试运算符
| 运算符 |                     说明                     |           举例           |
| :----: | :------------------------------------------: | :----------------------: |
| -b | 检测文件是否是块设备文件，如果是，则返回 true。              | [ -b $file ] 返回 false。 |
| -c | 检测文件是否是字符设备文件，如果是，则返回 true。            | [ -c $file ] 返回 false。 |
| -d| 检测文件是否是目录，如果是，则返回 true。                    | [ -d $file ] 返回 false。 |
| -f | 检测文件是否是普通文件（既不是目录，也不是设备文件），如果是，则返回 true。 | [ -f $file ] 返回 true。  |
| -g | 检测文件是否设置了 SGID 位，如果是，则返回 true。            | [ -g $file ] 返回 false。 |
| -k| 检测文件是否设置了粘着位(Sticky Bit)，如果是，则返回 true。  | [ -k $file ] 返回 false。 |
| -p| 检测文件是否是有名管道，如果是，则返回 true。                | [ -p $file ] 返回 false。 |
| -u| 检测文件是否设置了 SUID 位，如果是，则返回 true。            | [ -u $file ] 返回 false。 |
| -r| 检测文件是否可读，如果是，则返回 true。                      | [ -r $file ] 返回 true。  |
| -w | 检测文件是否可写，如果是，则返回 true。                      | [ -w $file ] 返回 true。  |
| -x | 检测文件是否可执行，如果是，则返回 true。                    | [ -x $file ] 返回 true。  |
| -s|检测文件是否为空（文件大小是否大于0），不为空返回 true。     | [ -s $file ] 返回 true。  |
| -e| 检测文件（包括目录）是否存在，如果是，则返回 true。          | [ -e $file ] 返回 true。  |

# echo命令

```shell
echo "It is a test"
#It is a test
echo "\"It is a test\""
#"It is a test"

read name 
echo "$name It is a test"
#从标准输入中读取一行，然后把输入行的每个字段的值指定给name变量

echo "OK! \c"
echo "It is a test"
#OK!It is a test

echo "It is a test" > test.txt

echo '$name"'
#单引号输出原样字符串：$name"
```

| 输入命令               | 输出内容                                      | 解 释                                                        |
| ---------------------- | --------------------------------------------- | ------------------------------------------------------------ |
| echo '$USER * $(date)' | $USER * $(date)                               | 单引号无视所有特殊字符，所有字符在它眼里 都是普通字符，都是芸芸众生 |
| echo "$USER * $(date)" | root * Thu Feb 25 12:03:48 CST 2016           | 双引号会无视文件通配符，但“$”、“\”、 会起作用，我管它们叫“美金”、“砍刀”、 “硫酸雨” |
| echo $USER * $(date)   | root book others Thu Feb 25 12:03:48 CST 2016 | $USER 被翻译了 root, * 被翻译了 book, others  是我当前目录下的目录结构 |

单引号将所有字符都看成普通字符，双引号会解释`$`、`\`和```这三种特殊字符，不加引号的话则会解释所有特殊字符。

```shell
echo -e "\033[41;36m Hello world \033[0m"
-e：开启反斜杠转义
\033：转义序列开始，\033表示Esc符号，也可以使用\E或\e代替
41;36：前景色;背景色
m：转义终止符
Hello world：要显示的文字内容
\033[0m：恢复之前的配色，0表示之前的配色方案
```

| 色彩   | 黑   | 红   | 绿   | 黄   | 蓝   | 洋红 | 青   | 白   |
| ------ | ---- | ---- | ---- | ---- | ---- | ---- | ---- | ---- |
| 前景色 | 30   | 31   | 32   | 33   | 34   | 35   | 36   | 37   |
| 背景色 | 40   | 41   | 42   | 43   | 44   | 45   | 46   | 47   |

**tput使用**

| 数值 | 0    | 1    | 2    | 3    | 4    | 5      | 6    | 7    |
| ---- | ---- | ---- | ---- | ---- | ---- | ------ | ---- | ---- |
| 颜色 | 黑色 | 红色 | 绿色 | 黄色 | 蓝色 | 洋红色 | 黄色 | 白色 |

```shell
RED=$(tput setaf 1)
GREEN=$(tput setaf 2)
RESET=$(tput sgr0)
echo "${RED}red text ${GREEN}green text${RESET}"
```

# printf

```shell
printf "%-10s %-8s %-4s\n" 姓名 性别 体重kg  
printf "%-10s %-8s %-4.2f\n" 郭靖 男 66.1234
printf "%-10s %-8s %-4.2f\n" 杨过 男 48.6543
printf "%-10s %-8s %-4.2f\n" 郭芙 女 47.9876
:<<!
姓名     性别   体重kg
郭靖     男      66.12
杨过     男      48.65
郭芙     女      47.99
!
```

%-10s 指一个宽度为 10 个字符（**-** 表示左对齐，没有则表示右对齐），任何字符都会被显示在 10 个字符宽的字符内，如果不足则自动以空格填充，超过也会将内容全部显示出来。

%-4.2f 指格式化为小数，其中 **.2** 指保留2位小数。

| \a    | 警告字符，通常为ASCII的BEL字符                               |
| ----- | ------------------------------------------------------------ |
| \b    | 后退                                                         |
| \c    | 抑制（不显示）输出结果中任何结尾的换行字符（只在%b格式指示符控制下的参数字符串中有效），而且，任何留在参数里的字符、任何接下来的参数以及任何留在格式字符串中的字符，都被忽略 |
| \f    | 换页（formfeed）                                             |
| \n    | 换行                                                         |
| \r    | 回车（Carriage return）                                      |
| \t    | 水平制表符                                                   |
| \v    | 垂直制表符                                                   |
| \\    | 一个字面上的反斜杠字符                                       |
| \ddd  | 表示1到3位数八进制值的字符。仅在格式字符串中有效             |
| \0ddd | 表示1到3位的八进制值字符                                     |

# test命令

| -eq  | 等于则为真     |
| :--: | -------------- |
| -ne  | 不等于则为真   |
| -gt  | 大于则为真     |
| -ge  | 大于等于则为真 |
| -lt  | 小于则为真     |
| -le  | 小于等于则为真 |

```shell
num1=100
num2=100
if test $[num1] -eq $[num2]
then
    echo '两个数相等！'
else
    echo '两个数不相等！'
fi
```

代码中的 [] 执行基本的算数运算，如：

```shell
a=5
b=6
result=$[a+b] # 注意等号两边不能有空格
echo "result 为： $result"
```

## 字符串测试

|     =     | 等于则为真               |
| :-------: | ------------------------ |
|    !=     | 不相等则为真             |
| -z 字符串 | 字符串的长度为零则为真   |
| -n 字符串 | 字符串的长度不为零则为真 |

```shell
num1="ru1noob"
num2="runoob"
if test $num1 = $num2
then
    echo '两个字符串相等!'
else
    echo '两个字符串不相等!'
fi
```

## 文件测试

| -e 文件名 | 如果文件存在则为真                   |
| :-------: | ------------------------------------ |
| -r 文件名 | 如果文件存在且可读则为真             |
| -w 文件名 | 如果文件存在且可写则为真             |
| -x 文件名 | 如果文件存在且可执行则为真           |
| -s 文件名 | 如果文件存在且至少有一个字符则为真   |
| -d 文件名 | 如果文件存在且为目录则为真           |
| -f 文件名 | 如果文件存在且为普通文件则为真       |
| -c 文件名 | 如果文件存在且为字符型特殊文件则为真 |
| -b 文件名 | 如果文件存在且为块特殊文件则为真     |

优先级：非(!)>与(-a)>或(-o)

```shell
if test -e ./notFile -o -e ./bash
then
    echo '至少有一个文件存在!'
else
    echo '两个文件都不存在'
fi
```

# 流程控制

## IF判断

```shell
a=10
b=20
if [ $a == $b ]
then
   echo "a 等于 b"
elif [ $a -gt $b ]
then
   echo "a 大于 b"
elif [ $a -lt $b ]
then
   echo "a 小于 b"
else
   echo "没有符合的条件"
fi
```

```shell
a=10
b=20
if (( $a == $b ))
then
   echo "a 等于 b"
elif (( $a > $b ))
then
   echo "a 大于 b"
elif (( $a < $b ))
then
   echo "a 小于 b"
else
   echo "没有符合的条件"
fi
```

```shell
num1=$[2*3]
num2=$[1+5]
if test $[num1] -eq $[num2]
then
    echo '两个数字相等!'
else
    echo '两个数字不相等!'
fi
```

## for循环

```shell
for loop in 1 2 3 4 5
do
    echo "The value is: $loop"
done
```

```shell
for str in This is a string
do
    echo $str
done
:<<!
This
is
a
string
!
```

## while循环

```shell
int=1
while(( $int<=5 ))
do
    echo $int
    let "int++"
done
```

```shell
while true
do
    command
done

for (( ; ; ))

while :
do
    command
done
```

## until循环

```shell
a=0

until [ $a -gt 10 ]
do
   echo $a
   a=`expr $a + 1`
done
```

## case…esac

```shell
echo '输入 1 到 4 之间的数字:'
echo '你输入的数字为:'
read aNum
case $aNum in
    1)  echo '你选择了 1'
    ;;
    2)  echo '你选择了 2'
    ;;
    3)  echo '你选择了 3'
    ;;
    4)  echo '你选择了 4'
    ;;
    *)  echo '你没有输入 1 到 4 之间的数字'
    ;;
esac
```

```shell
while :
do
    echo -n "输入 1 到 5 之间的数字:"
    read aNum
    case $aNum in
        1|2|3|4|5) echo "你输入的数字为 $aNum!"
        ;;
        *) echo "你输入的数字不是 1 到 5 之间的! 游戏结束"
            break
        ;;
    esac
done
```

# Shell函数

```shell
[ function ] funname [()]
{
    action;
    [return int;]
}
```

```shell
demoFun(){
    echo "这是我的第一个 shell 函数!"
}
echo "-----函数开始执行-----"
demoFun
echo "-----函数执行完毕-----"
```

## 函数参数

```shell
funWithParam(){
    echo "第一个参数为 $1 !"
    echo "第二个参数为 $2 !"
    echo "第十个参数为 $10 !"
    echo "第十个参数为 ${10} !"
    echo "第十一个参数为 ${11} !"
    echo "参数总数有 $# 个!"
    echo "作为一个字符串输出所有参数 $* !"
}
funWithParam 1 2 3 4 5 6 7 8 9 34 73
```

|  $#  | 传递到脚本或函数的参数个数                                   |
| :--: | ------------------------------------------------------------ |
|  $*  | 以一个单字符串显示所有向脚本传递的参数                       |
|  $$  | 脚本运行的当前进程ID号                                       |
|  $!  | 后台运行的最后一个进程的ID号                                 |
|  $@  | 与$*相同，但是使用时加引号，并在引号中返回每个参数。         |
|  $-  | 显示Shell使用的当前选项，与set命令功能相同。                 |
|  $?  | 显示最后命令的退出状态。0表示没有错误，其他任何值表明有错误。 |

# 输入/输出重定向

| command > file  | 将输出重定向到 file。                              |
| --------------- | -------------------------------------------------- |
| command < file  | 将输入重定向到 file。                              |
| command >> file | 将输出以追加的方式重定向到 file。                  |
| n > file        | 将文件描述符为 n 的文件重定向到 file。             |
| n >> file       | 将文件描述符为 n 的文件以追加的方式重定向到 file。 |
| n >& m          | 将输出文件 m 和 n 合并。                           |
| n <& m          | 将输入文件 m 和 n 合并。                           |
| << tag          | 将开始标记 tag 和结束标记 tag 之间的内容作为输入。 |

```shell
cat << EOF
欢迎来到
菜鸟教程
www.runoob.com
EOF
```

