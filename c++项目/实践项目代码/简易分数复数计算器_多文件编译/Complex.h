/*
 * @Description: 复数相关内容的头文件
 * @Autor: jhl
 * @Date: 2021-12-07 14:38:34
 * @LastEditors: jjkhl
 * @LastEditTime: 2021-12-08 10:00:27
 */
#ifndef COMPLEX_H
#define COMPLEX_H
#include<iostream>
using namespace std;
class Complex{
    public:
    Complex():realPart(0),imaginaryPart(0){}
    Complex(double real,double image):realPart(real),imaginaryPart(image){}

    //输入输出重载
    friend ostream &operator<<(ostream &out,const Complex &complex);
    friend istream &operator>>(istream &in,Complex &complex);

    friend Complex operator+(Complex &complex1,Complex &complex2);
    friend Complex operator+(double number,Complex &complex);
    friend Complex operator+(Complex &complex,double number);
    
    friend Complex operator-(Complex &complex1,Complex &complex2);
    friend Complex operator-(double number,Complex &complex);
    friend Complex operator-(Complex &complex,double number);

    friend Complex operator*(Complex &complex1,Complex &complex2);
    friend Complex operator*(double number,Complex &complex);
    friend Complex operator*(Complex &complex,double number);

    friend Complex operator/(Complex &complex1,Complex &complex2);
    friend Complex operator/(double number,Complex &complex);
    friend Complex operator/(Complex &complex,double number);

    void setRealPart(double real);
    double getRealPart() const;
    void setImaginaryPart(double imaginary);
    double getImaginaryPart() const;
    void display();
    
    private:
     double realPart;
     double imaginaryPart;
};
#endif