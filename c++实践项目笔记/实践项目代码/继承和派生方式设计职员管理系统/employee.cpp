/*
 * @Description: 
 * @Autor: jhl
 * @Date: 2021-12-09 14:12:18
 * @LastEditors: jjkhl
 * @LastEditTime: 2021-12-10 21:35:24
 */
#include<iostream>
#include<string.h>
#include"employee.h"
using namespace std;
int number=1;
employee::employee()
{
    cout<<"1-销售；2-技术人员；3-销售经理；4-技术经理；5-总经理"<<endl;
    cout<<"请输入您的职位[1-5]：";
    int position=0;
    cin>>position;
    switch(position)
    {
        case 1:
            cout<<"销售人员你好，";
            break;
        case 2:
            cout<<"技术人员你好，";
            break;
        case 3:
            cout<<"销售经理你好，";
            break;
        case 4:
            cout<<"技术经理你好，";
            break;
        case 5:
            cout<<"总经理你好，";
            break;
    }
    char namestr[50];
    cout<<"请输入你的姓名：";
    cin>>namestr;
    name=new char[strlen(namestr+1)];
    strcpy(name,namestr);
    individual_number=number++;
    grade=1;
    paycheck=0.0;
}
employee::~employee()
{
    delete name;
}

void employee::prompt(int increment)
{
    grade+=increment;
}

//technical类

technician::technician()
{
    bonus=10;
    jixiao=0;
}

void technician::pay()
{
    cout<<"请输入技术人员"<<name<<"本月的绩效考核分数：";
    cin>>jixiao;
    paycheck=3000+bonus*jixiao;
}

void technician::displayStatus()
{
    cout<<"技术人员"<<name<<"编号"<<individual_number
    <<"级别为"<<grade<<"级，已付本月工资："<<paycheck<<endl;
}

//salesman类函数定义
salesman::salesman()
{
    rate_bonus=0.01;
}

void salesman::pay()
{
    cout<<"请输入销售人员"<<name<<"本月销售额：";
    cin>>sales;
    paycheck=sales*rate_bonus;
}

void salesman::displayStatus()
{
    cout<<"销售人员"<<name<<"编号"<<individual_number
    <<"级别为"<<grade<<"级，已付本月工资："<<paycheck<<endl;
}

//manager类函数定义
manager::manager()
{
    monthlypay=10000;
}

void manager::pay()
{
    paycheck=monthlypay;
}

void manager::displayStatus()
{
    cout<<"总经理"<<name<<"编号"<<individual_number
    <<"级别为"<<grade<<"级，已付本月工资："<<paycheck<<endl;
}

//salesmanager类定义函数
salesmanager::salesmanager()
{
    monthlypay=4000;
    rate_bonus=0.005;
}

void salesmanager::pay()
{
    cout<<"请输入销售经理"<<name<<"销售部本月销售总额：";
    cin>>sales;
    paycheck=monthlypay+rate_bonus*sales;
}

void salesmanager::displayStatus()
{
    cout<<"销售经理"<<name<<"编号"<<individual_number
    <<"级别为"<<grade<<"级，已付本月工资："<<paycheck<<endl;
}

//techmanager类定义函数
techmanager::techmanager()
{
    monthlypay=5000;
}

void techmanager::pay()
{
    cout<<"请输入技术经理"<<name<<"本月的绩效考核分数：";
    cin>>jixiao;
    paycheck=monthlypay+bonus*jixiao;
}

void techmanager::displayStatus()
{
    cout<<"技术经理"<<name<<"编号"<<individual_number
    <<"级别为"<<grade<<"级，已付本月工资"<<paycheck<<endl;
}


