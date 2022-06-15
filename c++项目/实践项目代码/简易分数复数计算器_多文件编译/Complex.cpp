/*
 * @Description: 
 * @Autor: jhl
 * @Date: 2021-12-07 16:31:48
 * @LastEditors: jjkhl
 * @LastEditTime: 2021-12-08 10:07:16
 */
#include<iostream>
#include<iomanip>
#include"Complex.h"
using namespace std;
void Complex::setRealPart(double real)
{
    realPart=real;
}

double Complex::getRealPart() const
{
    return realPart;
}

void Complex::setImaginaryPart(double imaginary)
{
    imaginaryPart=imaginary;
}

//输出重载
ostream &operator<<(ostream &out, const Complex &complex)
{
    out<<'('<<complex.realPart<<','<<complex.imaginaryPart<<')';
    return out;
}

//输入重载
istream &operator>>(istream &in,Complex &complex)
{
    char left;
    char comma;
    char right;
    char tempChar;
    in>>left>>complex.realPart>>comma>>complex.imaginaryPart>>right;
    while(true)
    {
        while((tempChar=getchar())!='\n')
        {
            continue;
        }
        if((left!='(')||(comma!=',')||(right!=')'))
        {
            cerr<<"格式错误！[例如(m,n)],请重新输入："<<endl;
            in.clear();
        in>>left>>complex.realPart>>comma>>complex.imaginaryPart>>right;
            
        }
        else
        {
            break;
        }
    }
    return in;
}

//复数相加
Complex operator+(Complex &complex1,Complex &complex2)
{
    Complex res;
    res.realPart=complex1.realPart+complex2.realPart;
    res.imaginaryPart=complex1.imaginaryPart+complex2.imaginaryPart;
    return res;
}
Complex operator+(double number,Complex &complex)
{
    Complex res(number,0);
    return res+complex;
}
Complex operator+(Complex &complex, double number)
{
    Complex res(number,0);
    return res+complex;
}


//复数相减
Complex operator-(Complex &complex1,Complex &complex2)
{
    Complex res;
    res.realPart=complex1.realPart-complex2.realPart;
    res.imaginaryPart=complex1.imaginaryPart-complex2.imaginaryPart;
    return res;
}
Complex operator-(double number,Complex &complex)
{
    Complex res(number,0);
    return res-complex;
}
Complex operator-(Complex &complex, double number)
{
    Complex res(number,0);
    return complex-res;
}

//复数相乘
//(a+bi)(c+di)=(ac-bd)+(bc+ad)i
Complex operator*(Complex &complex1,Complex &complex2)
{
    Complex res;
    res.realPart=complex1.realPart*complex2.realPart-complex1.imaginaryPart*complex2.imaginaryPart;
    res.imaginaryPart=complex1.imaginaryPart*complex2.realPart+complex1.realPart*complex2.imaginaryPart;
    return res;
}
Complex operator*(double number,Complex &complex)
{
    Complex res(number,0);
    return res*complex;
}
Complex operator*(Complex &complex, double number)
{
    Complex res(number,0);
    return res*complex;
}

//复数相除
//(a+bi)(c+di)=(ac+bd)/(c^2+d^2)+(bc-ad)/(c^2+d^2)i
Complex operator/(Complex &complex1,Complex &complex2)
{
    Complex res;
    double divided=complex2.realPart*complex2.realPart+complex2.imaginaryPart*complex2.imaginaryPart;
    res.realPart=(complex1.realPart*complex2.realPart+complex1.imaginaryPart*complex2.imaginaryPart)/divided;
    res.imaginaryPart=(complex1.imaginaryPart*complex2.realPart-complex1.realPart*complex2.imaginaryPart)/divided;
    return res;
}
Complex operator/(double number,Complex &complex)
{
    Complex res(number,0);
    return res/complex;
}
Complex operator/(Complex &complex, double number)
{
    Complex res(number,0);
    return complex/res;
}

void Complex::display()
{
    cout<<"("<<realPart<<","<<imaginaryPart<<"i)"<<endl;
}