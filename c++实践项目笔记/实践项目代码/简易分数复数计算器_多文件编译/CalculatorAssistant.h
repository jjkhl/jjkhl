/*
 * @Description: �����������ڵ�ͷ�ļ�
 * @Autor: jhl
 * @Date: 2021-12-07 14:29:57
 * @LastEditors: jjkhl
 * @LastEditTime: 2021-12-07 14:53:38
 */
#ifndef CALCULATOR_H
#define CALCULATOR_H
#include<iostream>
#include<iomanip>
#include"Complex.h"
#include"Fraction.h"
class CalculatorAssistant
{
    public:
    void showMenu();
    void fractionCompute();//��������
    void complexCompute();//��������
    void run();
    private:
        Complex complex;
        Fraction fraction;
};
#endif// !CALCULATOR_H
