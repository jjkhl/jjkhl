/*
 * @Description: 
 * @Autor: jhl
 * @Date: 2021-12-07 14:50:35
 * @LastEditors: jjkhl
 * @LastEditTime: 2021-12-08 10:03:45
 */
#ifndef FRACTION_H
#define FRACTION_H
#include<iostream>
#include<iomanip>
using namespace std;
class Fraction
{
    public:
    Fraction(int nume=0,int denom=1):numerator(nume),denominator(denom){}
    void simplify();

    friend ostream &operator<<(ostream &out, const Fraction &fraction);
    friend istream &operator>>(istream &in,Fraction &fraction);

    //�Ӽ��˳�
    friend Fraction operator+(const Fraction &left,const Fraction &right);
    friend Fraction operator-(const Fraction &left,const Fraction &right);
    friend Fraction operator*(const Fraction &left,const Fraction &right);
    friend Fraction operator/(const Fraction &left,const Fraction &right);

    //��ϵ�����
    friend bool operator>(const Fraction &left,const Fraction &right);
    friend bool operator<(const Fraction &left,const Fraction &right);
    friend bool operator>=(const Fraction &left,const Fraction &right);
    friend bool operator<=(const Fraction &left,const Fraction &right);
    friend bool operator==(const Fraction &left,const Fraction &right);
    friend bool operator!=(const Fraction &left,const Fraction &right);

    //ȡ+��-һĿ�����
    Fraction operator +();
    Fraction operator -();
    void setNumerator(int nume);
    int getNumerator() const;
    void setDenominator(int denom);
    int getDenominator() const;

    private:
    int numerator;
    int denominator;
};
#endif