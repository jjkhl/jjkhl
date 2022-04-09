<h1 align = "center">CPlusPlus笔记</h1>

## const

### 与`#define`宏定义常量的区别：

* const常量具有数据类型，编译器可以进行安全检查；`#define`宏定义没有护具类型，知识简单的字符串替换，不能进行安全检查。
* const定义的变量只有类型位<strong style="color:red">整数或枚举</strong>，且以常量表达式初始化才能作为常量表达式
* 其它情况下它只是const限定的变量，不要将常量混淆
* const定义常量从汇编的角度来看，只是给出了对应的内存地址，而不是想`#define`一样给出的是立即数
* const定义的常量在程序运行过程中只有一份拷贝，而`#define`定义的常量在内存中有多个拷贝

### const对象默认位文件局部变量

非const变量默认为extern。要让const变量能够在其他文件中访问，必须在文件中显式地指定为extern。

<strong style="color:red">未被const修饰的变量不需要extern显式声明</strong>！而<strong style="color:red">const常量需要显式声明extern</strong>，并且需要做初始化！因为常量在定义后就不能被修改，所以定义时必须初始化。

```c++
//未被const变量修饰的变量在不同文件的访问
// file1.cpp
int ext
// file2.cpp
#include<iostream>

extern int ext;
int main(){
    std::cout<<(ext+10)<<std::endl;
}

//const常量在不同文件的访问
//extern_file1.cpp
extern const int ext=12;
//extern_file2.cpp
#include<iostream>
extern const int ext;
int main(){
    std::cout<<ext<<std::endl;
}
```

### 指针与const

#### 指针常量——指向值，地址不可变，必须进行初始化

`int *const p`：const修饰的是p，p是指针，p指向的地址不可以改变，但是*p可以修改

> <strong style="color:red">引用也是指针常量</strong>，是一个对象的别名，且一定不为空。可以增加效率同时放置修改，不需要产生临时对象，但是有可能改变原有值(解决方式：`void func(const A &x)`，但是基本数据类型的输入参数<strong style="color:red">不需要</strong>该解决方法，比如`void func(const int &x)`)。

#### 常量指针（常指针）——指向地址，值不可变(可读属性)

`int const *p`

`const int *p`：const修饰的`*p`，即`*p`的内容不可以通过p改变，但是p

#### 函数中使用const

* 指针指向内容不变：const int* func2();
* 指针本身不可变：int *const func2();

#### 类中使用const

* 类中的const成员变量必须通过初始化列表进行初始化
* const对象只能访问const成员函数(函数名称后加const)，而非const对象可以访问任意的成员函数，包括const成员函数

## 静态变量——static

### 函数中的静态变量

当变量声明为static时，空间将在<strong style="color:red">程序的生命周期</strong>内分配。即使多次调用该函数，静态变量的空间也**只分配一次**。

### 类中的静态变量

* 不能使用构造函数初始化：声明为static的变量只能被初始化一次，因为它们在单独的静态存储中分配了空间，因此类中的静态变量`**`由对象共享。`**`对于不同的对象，不能有相同静态变量的多个副本

### 类中静态函数

允许静态成员函数仅访问静态数据成员或其它静态成员函数，无法访问类的非静态成员或成员函数。

## this指针

this被编译器解析为`A *const`， 值可变但是指针地址不可变。

## inline内联函数

内联函数一般是与类一起使用。如果一个函数是内联的，那么编译时，编译器会把该函数的代码副本放置在每个调用的位置，对内联函数进行任何修改，都需要重新编译函数的所有客户端，因为编译器需要重新更换一次所有的代码，否则将会继续使用旧的函数。

> 在类定义中的定义的函数都是内联函数，即使没有使用 `inline` 说明符。

内联能提高函数效率，但并不是所有的函数都定义成内联函数！内联是以代码膨胀(复制)为代价，仅仅省去了函数调用的开销，从而提高函数的执行效率。

- 如果执行函数体内代码的时间相比于函数调用的开销较大，那么效率的收货会更少！

- 另一方面，每一处内联函数的调用都要复制代码，将使程序的总代码量增大，消耗更多的内存空间。

以下情况不宜用内联：

  （1）如果函数体内的代码比较长，使得内联将导致内存消耗代价比较高。

  （2）如果函数体内出现循环，那么执行函数体内代码的时间要比函数调用的开销大。

### 虚函数与内联函数的关系

- 虚函数可以是内联函数，内联是可以修饰虚函数的，但是当虚函数表现多态性的时候不能内联。
- 内联是在编译期建议编译器内联，而虚函数的多态性在运行期，编译器无法知道运行期调用哪个代码，因此<strong style="color:red">虚函数表现为多态性时（运行期）不可以内联。</strong>
- `inline virtual` 唯一可以内联的时候是：编译器知道所调用的对象是哪个类（如 `Base::who()`），这只有在编译器具有实际对象而不是对象的指针或引用时才会发生。

## sizeof的使用

字节对齐方式:https://blog.csdn.net/sweetfather/article/details/78487563

- 空类的大小为1字节
- 一个类中，虚函数本身、成员函数（包括静态与非静态）和静态数据成员都是不占用类对象的存储空间。

```c++
//字节对齐作用
struct MyStruct 
{ 
char dda;//偏移量为0，满足对齐方式，dda占用1个字节； 
double dda1;//下一个可用的地址的偏移量为1，不是sizeof(double)=8的倍数，需要补足7个字节才能使偏移量变为8（满足对齐方式），因此VC自动填充7个字节，dda1存放在偏移量为8的地址上，它占用8个字节。 
int type;//下一个可用的地址的偏移量为16，是sizeof(int)=4的倍数，满足int的对齐方式，所以不需要VC自动填充，type存放在偏移量为16的地址上，它占用4个字节。 
}；　　　　　　　　　　　　　　　　　
//所有成员变量都分配了空间，空间总的大小为1+7+8+4=20，不是结构的节边界数（即结构中占用最大空间的类型所占用的字节数sizeof(double)=8）的倍数，所以需要填充4个字节，以满足结构的大小为sizeof(double)=8的倍数。 

struct S1{
char a;
long b;
};
struct S2 {
char c;
struct S1 d;
long long e;
};
//S1有8字节.在S2中c按照S1中最大对齐参数(long=4)对齐,所以为4字节.然后c和d共占用12字节,e为8字节,按照字节对齐原则,S2一共占用12+4+8=24字节
    
class A1
{
    public:
        virtual void fun() {};
};//A1有8个字节
class B1
{
    public:
        virtual void fun() {};
        virtual void fun2(){};
};//B1有8个字节
   class A2
{
    public:
        char b;
       static int c;
}; //A2有1字节
class A3
{
    public:
    char b;
    virtual void fun(){};
};//A3有16字节
```

- 对于包含虚函数的类，不管有多少个虚函数，只有一个虚指针vptr的大小。
- 普通继承，派生类继承了所有基类的函数与成员，要按照字节对齐来计算大小，然后根据基类最大对齐参数进行分配。
- 虚函数继承，不管是单继承还是多继承，都是继承了基类的vptr。(<strong style="color:red">32位操作系统4字节，64位操作系统 8字节</strong>)！
- 虚继承,继承基类的vptr。

```c++
class A
{
    virtual void fun() {}
};
class B
{
    virtual void fun2() {}
};
class C : virtual public  A, virtual public B
{
    public:
        virtual void fun3() {}
};

int main()
{
    /**
     * @brief 8 8 16  派生类虚继承多个虚函数，会继承所有虚函数的vptr
     */
    cout<<sizeof(A)<<" "<<sizeof(B)<<" "<<sizeof(C);

    return 0;
}
```

## 纯虚函数和抽象类

#### 纯虚函数的定义

C++中的纯虚函数(或抽象函数)是我们没有实现的虚函数！我们只需声明它! 通过声明中赋值0来声明纯虚函数！` virtual void show() = 0; `。定义一个函数为虚函数是为了允许使用基类的指针来调用子类的函数，定义一个函数为虚函数是为了实现一个接口，起到规范作用，规范继承这个类的程序员必须实现这个函数。

#### 抽象类的实现

```c++
// A为抽象类
class A {
public:
    virtual void f() = 0;  // 纯虚函数
    void g(){ this->f(); }
    A(){}  // 构造函数
};

class B : public A{
public:
    void f(){ cout<<"B:f()"<<endl;}  // 实现了抽象类的纯虚函数
};
```

#### 重点

* 纯虚函数使一个类变成抽象类
* 抽象类类型的指针和引用

```c++
// 抽象类至少包含一个纯虚函数
class Base{
public: 
    virtual void show() = 0; // 纯虚函数
    int getX() { return x; } // 普通成员函数

private:
     int x; 
}; 
class Derived : public Base { 
public: 
    void show() { cout << "In Derived \n"; } // 实现抽象类的纯虚函数
    Derived(){} // 构造函数
}; 

int main(void) 
{ 
    //Base b;  // error! 不能创建抽象类的对象
    //Base *b = new Base(); error!
    
    Base *bp = new Derived(); // 抽象类的指针和引用 -> 由抽象类派生出来的类的对象
    bp->show();
    return 0; 
}
```

* 如果我们不在派生类中覆盖纯虚函数，那么派生类也会变成抽象类
* 抽象类可以有构造函数
* 构造函数不能使虚函数，而析构函数可以是虚析构函数

## virtual的使用

* 默认参数是静态绑定的，虚函数是动态绑定的。 默认参数的使用需要看指针或者引用本身的类型，而不是对象的类型。

```c++
#include <iostream> 
using namespace std; 
class Base 
{ 
    public: 
        virtual void fun ( int x = 10 ) 
        { 
            cout << "Base::fun(), x = " << x << endl; 
        } 
}; 

class Derived : public Base 
{ 
    public: 
        virtual void fun ( int x=20 ) 
        { 
            cout << "Derived::fun(), x = " << x << endl; 
        } 
}; 
int main() 
{ 
    Derived d1; 
    Base *bp = &d1; 
    bp->fun();  // 10
    return 0; 
} 
```

## friend的使用

* 友元函数：普通函数对一个访问某个类中的私有或保护成员
* 友元类：类A中的成员函数访问类B中的私有或保护成员

友元的声明都在该类的声明，实现在类外。

没有继承性 假如类B是类A的友元，类C继承于类A，那么友元类B是没办法直接访问类C的私有或保护成员。

不存在传递性，即类B是类A的友元，类C是类B的友元，那么友元类C是没办法直接访问类A的私有或保护成员，也就是<strong style="color:red">不存在“友元的友元”</strong>这种关系。

## enum的使用

为了解决作用域不受限带来的命名冲突问题，可以使用命名空间。

```c++
struct Color1
{
    enum Type
    {
        RED=102,
        YELLOW,
        BLUE
    };
};
```

