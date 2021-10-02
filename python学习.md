<h1 align="center">Python学习</h1>

网址推荐：https://docs.python.org/zh-cn/3/tutorial/classes.html

​				  http://www.byhy.net/tut/py/basic/01/

​				  https://www.runoob.com/python3/python3-tutorial.html

## 字符串

```python
name="Aka"
name='Aka'
print(name.title)#首字母大写
name.upper()#字母大写
name.lower()#字母小写

#在字符串中使用变量
full_name=f"{first_name}{last_name}“

#删除空白
rstrip()#原变量没有发生改变，删除末尾空白
lstrip()#删除开头空白

#乘方运算
3**2=9

#初始化
x,y,z=0,1,2

#全大写设置为常量
MAX_CONNECTION=100
```

## 列表

```python
#访问元素
test=['a','b','c']
#访问最后一个元素
test[2]
test[-1]

#列表末尾添加元素
test.append('d')
test.insert(2,'d')

#删除末尾元素
del test[2]
test.pop()
test.remove('c')#只删除第一个发现的值

#对列表永久逆排序
test.sort(reverse=True)
#对列表暂时逆排序
print(sorted(test,reverse=True))

#获取列表长度
len(test)
```

## 遍历

```python	
#基本格式
for test in test_list：
#没缩进表示结束，缩进表示在for循环中

#创建数值列表
for value in range(1,5):#只打印1-4
for value in range(6):#打印0-5

numbers=list(range(1,6))#numbers=[1,2,3,4,5]
even_num=list(range(2,11,3))#even_num=[2,5,8]——3表示步长

#列表解析
squares=[val**2 for val in range(1,11)]

#切片
test[0:2:2]#等价于test[0]
test[:1]#自动从列表开头开始，等价于test[0]
test[-1:]#test的最后一项

#复制列表
test1=test[:]

#元组
demension=(200,50)#不能修改任何数据

#修改元组变量
dimension=(200,30)#将新元组覆盖旧元组
```

## IF语句

```python	
#基本结构
if a==True:

#多条件检查
if a==True and b==True:
if a==True or b==True:

#检查特定值
'a' in test

if 'd' not in test:

#if-else
if a==True:
else:

#if-elif-else
if a==True
elif a==False
else:
```

## 字典

```python
test={'color':'green','points':5}
#添加键配对
test['size']=2

#删除键配对
del test['size']

#使用get()访问：以防出现键值错误
temp=test.get('size','There is no size')

#遍历字典
for k,v in test.items():#字典中所有元素
test.keys()#字典中所有键值
test.values()#字典中所有值
for k in sort(test.keys()):

#遍历剔除重复元素
for temp in set(test.values()):

#在字典中存储列表
pizza={
	'toppings': ['mushroom','cheese'],
}
for top in pizza['toppings']:
```

## 用户输入和while循环

```python	
#输入文本
message=input("输入：")

#转换为数值输入
int()

#求模——获得余数
4%3#输出1

#while循环
while temp <= 5:
	break
	continue
```

## 函数

```python	
def hello():
    
#传递任意数量的实参
def make_pizza(size,*toppings)
#*表示创建一个topping的空元组，将收到的所有值都封装到这个元组中。
make_pizza(20,'mushroom','green peppers','cheese')

#使用任意数量的关键字实参
#**user_info：创建一个字典，并将收到的所有名称值对都放到字典中
def build(first,last,**user_info)

#多文件操作
import pizza#导入pizza.py文件
#导入特定函数
from pizza make_pizza as mp#只导入pizza.py文件中的make_pizza函数，重命名为mp

#导入所有函数
from pizza import *
```

## 类

类的说明：https://docs.python.org/zh-cn/3/tutorial/classes.html

实例属性用于区分不同的实例，类属性是每个实例共有属性。

> 实例属性每个实例都各自拥有，互相独立；而类属性有且只有一份，是共有属性。
>
> 实例属性的访问优先级比类属性高。
>
> 千万不要在实例上修改类属性，它实际上并没有修改类属性，而是给实例绑定了一个实例属性。

```python	
class Circle(object):
   pi = 3.14  # 类属性

   def __init__(self, r):
       self.r = r

circle1 = Circle(1)
circle2 = Circle(2)
print('----未修改前-----')
print('pi=\t', Circle.pi)
print('circle1.pi=\t', circle1.pi)  #  3.14
print('circle2.pi=\t', circle2.pi)  #  3.14

print('----通过类名修改后-----')
Circle.pi = 3.14159  # 通过类名修改类属性，所有实例的类属性被改变
print('pi=\t', Circle.pi)   #  3.14159
print('circle1.pi=\t', circle1.pi)   #  3.14159
print('circle2.pi=\t', circle2.pi)   #  3.14159

print('----通过circle1实例名修改后-----')
circle1.pi=3.14111   # 实际上这里是给circle1创建了一个与类属性同名的实例属性
print('pi=\t', Circle.pi)     #  3.14159
print('circle1.pi=\t', circle1.pi)  # 实例属性的访问优先级比类属性高，所以是3.14111   
print('circle2.pi=\t', circle2.pi)  #  3.14159

print('----删除circle1实例属性pi-----')
del circle1.pi
print('pi=\t', Circle.pi)
print('circle1.pi=\t', circle1.pi)
print('circle2.pi=\t', circle2.pi)
```

## 文件和异常

```python	
#pi_digit.txt
3.1415926535 
  8979323846 
  2643383279
  
#file_reader.py调用pi_digit.txt
filename = 'pi_digits.txt'
with open(filename) as file_object:
#with open('D:\\testfile\\pi_digit.txt') as file_object:
    for line in file_object:
    	print(line.rstrip())#rstrip()消除换行符

#写入文件
with open('test.txt','w') as file:
#w——写入；r——只读；r+——读写；a——附加模式
	file.write("hello")
	
#异常处理
try:
	print(5/0)
except ZeroDivisionError:
#pass——用作跳过
	print("You can't divide by zero")
else:
	print(answer)

#json文件存储和读取数据
import json
json.dump(要存储的数据，文件对象)
json.load(文件)


```





