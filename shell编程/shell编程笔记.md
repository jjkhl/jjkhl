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