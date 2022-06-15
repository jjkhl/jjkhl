/*
 * @Description: 
 * @Autor: jhl
 * @Date: 2021-12-07 16:54:07
 * @LastEditors: jjkhl
 * @LastEditTime: 2021-12-07 21:35:44
 */
#include<iostream>
#include<iomanip>
#include"Fraction.h"
using namespace std;
void Fraction::setNumerator(int nume)
{
    numerator=(nume==0)?0:nume;
}

int Fraction::getNumerator() const
{
    return numerator;
}

void Fraction::setDenominator(int denom)
{
    if(denom==0)
    cerr<<"��ĸ����Ϊ0��"<<endl;

    denominator=(denom!=0)?denominator:NULL;
}

int Fraction::getDenominator() const
{
    return denominator;
}

void Fraction::simplify()
{
    int num1=numerator;
    int num2=denominator;
    /*�������򣬹ؼ��������ĸ�ͷ��ӵ����������
  ������á�շת����������������������������
  շת������� ����ŷ������㷨��Euclidean algorithm�����������Լ����һ�ַ�����
  ���ľ��������ǣ��ýϴ������Խ�С�������ó��ֵ���������һ������ȥ�����������ó��ֵ��������ڶ�������ȥ����һ������
  ��˷�����ֱ�����������0Ϊֹ��������������������Լ������ô���ĳ��������������������Լ����
    */
    while(num2)
    {
        int tmp=num2;
        num2=num1%num2;
        num1=tmp;
    }
    numerator/=num1;
    denominator/=num1;
    if(denominator<0)
    {
        denominator=-denominator;
        numerator=-numerator;
    }
}

ostream &operator<<(ostream &out, const Fraction &fraction)
{
    out<<fraction.numerator<<'/'<<fraction.denominator;
    return out;
}

istream &operator>>(istream &in,Fraction &fraction)
{
    char ch;
    char tempChar;
    in>>fraction.numerator>>ch>>fraction.denominator;
    while(true)
    {
        while((tempChar=getchar())!='\n')
        {
            continue;
        }
        if(fraction.denominator==0)
        {
            cerr<<"��ĸΪ0�����������룺"<<endl;
            in.clear();
            in>>fraction.numerator>>ch>>fraction.denominator;
        }
        else if(ch!='/')
        {
            cerr<<"��ʽ����(ʾ����m/n)!���������룺";
            in.clear();
            in>>fraction.numerator>>ch>>fraction.denominator;
        }
        else
        {
            break;
        }
    }
    return in;
}

Fraction operator+(const Fraction &left,const Fraction &right)
{
    Fraction res;
    res.numerator=left.numerator*right.denominator+left.denominator*right.numerator;
    res.denominator=left.denominator*right.denominator;
    res.simplify();
    return res;
}

Fraction operator-(const Fraction &left,const Fraction &right)
{
    Fraction res;
    res.numerator=left.numerator*right.denominator-left.denominator*right.numerator;
    res.denominator=left.denominator*right.denominator;
    res.simplify();
    return res;
}

Fraction operator*(const Fraction &left,const Fraction &right)
{
    Fraction res;
    res.numerator=left.numerator*right.numerator;
    res.denominator=left.denominator*right.denominator;
    res.simplify();
    return res;
}

Fraction operator/(const Fraction &left,const Fraction &right)
{
    Fraction res;
    res.numerator=left.numerator/right.numerator;
    res.denominator=left.denominator/right.denominator;
    res.simplify();
    return res;
}

Fraction Fraction::operator+()
{
    simplify();
    if(numerator<0)
    {
        numerator=-numerator;
    }
    return *this;
}

Fraction Fraction::operator-()
{
    simplify();
    numerator=-numerator;
    return *this;
}

bool operator>(const Fraction &left,const Fraction &right)
{
    int left_num=left.numerator*right.denominator;
    int right_num=left.denominator*right.numerator;
    int common_deominator=left.denominator*right.denominator;
    if((left_num-right_num)*common_deominator>0)
        return true;
    else
        return false;
}

bool operator<(const Fraction &left,const Fraction &right)
{
    // int left_num=left.numerator*right.denominator;
    // int right_num=left.denominator*right.numerator;
    // int common_deominator=left.denominator*right.denominator;
    // if((left_num-right_num)*common_deominator<0)
    //     return true;
    // else
    //     return false;
    return !(left>right);
}

bool operator==(const Fraction &left,const Fraction &right)
{
    //TODO:����û�м򻯣����ܵ�������
    if(left.numerator==right.numerator&&right.denominator==left.denominator)
        return true;
    else
        return false;
}

bool operator!=(const Fraction &left,const Fraction &right)
{
    return !(left==right);
}

bool operator>=(const Fraction &left,const Fraction &right)
{
    if(left<right)
    {
        return false;
    }
    return true;
}

bool operator<=(const Fraction &left,const Fraction &right)
{
    if(left>right)
    {
        return false;
    }
    else
    return true;

}


