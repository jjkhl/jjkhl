/*
 * @Description: 
 * @Autor: jhl
 * @Date: 2021-12-10 21:03:32
 * @LastEditors: jjkhl
 * @LastEditTime: 2021-12-10 21:40:16
 */
#include<iostream>
#include"employee.h"
int main()
{

    salesman s1;
    system("cls");
    technician t1;
    system("cls");
    salesmanager sm1;
    system("cls");
    techmanager tm1;
    system("cls");
    manager m1;
    system("cls");

    m1.prompt(4);
    m1.pay();
    m1.displayStatus();

    t1.prompt(2);
    t1.pay();
    t1.displayStatus();

    sm1.prompt(3);
    sm1.pay();
    sm1.displayStatus();

    s1.prompt(1);
    s1.pay();
    s1.displayStatus();

    tm1.prompt(3);
    tm1.pay();
    tm1.displayStatus();
    
    system("pause");
    return 0;
}