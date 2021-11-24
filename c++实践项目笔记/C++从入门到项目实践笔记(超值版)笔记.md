<h1 align="center">C++从入门到项目实践(超值版)笔记</h1>

1. 全局变量x和局部变量x同时出现，使用`::x`表示全局变量
2. 多重继承的构造函数写法`MyClass_D::MyClass_D(int a, int b, int c, int d, int e) : MyClass_A(a, b), MyClass_B(c, d), m_e(e)`
3. 虚函数的使用方式：在基类定义的一个成员函数前加上`virtual`，定义一个指向基类对象的指针变量`Base *p=&b`，通过该指针变量调用不同类中的同名函数

