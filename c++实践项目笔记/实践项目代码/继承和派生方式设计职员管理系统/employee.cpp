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
    cout<<"1-���ۣ�2-������Ա��3-���۾���4-��������5-�ܾ���"<<endl;
    cout<<"����������ְλ[1-5]��";
    int position=0;
    cin>>position;
    switch(position)
    {
        case 1:
            cout<<"������Ա��ã�";
            break;
        case 2:
            cout<<"������Ա��ã�";
            break;
        case 3:
            cout<<"���۾�����ã�";
            break;
        case 4:
            cout<<"����������ã�";
            break;
        case 5:
            cout<<"�ܾ�����ã�";
            break;
    }
    char namestr[50];
    cout<<"���������������";
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

//technical��

technician::technician()
{
    bonus=10;
    jixiao=0;
}

void technician::pay()
{
    cout<<"�����뼼����Ա"<<name<<"���µļ�Ч���˷�����";
    cin>>jixiao;
    paycheck=3000+bonus*jixiao;
}

void technician::displayStatus()
{
    cout<<"������Ա"<<name<<"���"<<individual_number
    <<"����Ϊ"<<grade<<"�����Ѹ����¹��ʣ�"<<paycheck<<endl;
}

//salesman�ຯ������
salesman::salesman()
{
    rate_bonus=0.01;
}

void salesman::pay()
{
    cout<<"������������Ա"<<name<<"�������۶";
    cin>>sales;
    paycheck=sales*rate_bonus;
}

void salesman::displayStatus()
{
    cout<<"������Ա"<<name<<"���"<<individual_number
    <<"����Ϊ"<<grade<<"�����Ѹ����¹��ʣ�"<<paycheck<<endl;
}

//manager�ຯ������
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
    cout<<"�ܾ���"<<name<<"���"<<individual_number
    <<"����Ϊ"<<grade<<"�����Ѹ����¹��ʣ�"<<paycheck<<endl;
}

//salesmanager�ඨ�庯��
salesmanager::salesmanager()
{
    monthlypay=4000;
    rate_bonus=0.005;
}

void salesmanager::pay()
{
    cout<<"���������۾���"<<name<<"���۲����������ܶ";
    cin>>sales;
    paycheck=monthlypay+rate_bonus*sales;
}

void salesmanager::displayStatus()
{
    cout<<"���۾���"<<name<<"���"<<individual_number
    <<"����Ϊ"<<grade<<"�����Ѹ����¹��ʣ�"<<paycheck<<endl;
}

//techmanager�ඨ�庯��
techmanager::techmanager()
{
    monthlypay=5000;
}

void techmanager::pay()
{
    cout<<"�����뼼������"<<name<<"���µļ�Ч���˷�����";
    cin>>jixiao;
    paycheck=monthlypay+bonus*jixiao;
}

void techmanager::displayStatus()
{
    cout<<"��������"<<name<<"���"<<individual_number
    <<"����Ϊ"<<grade<<"�����Ѹ����¹���"<<paycheck<<endl;
}


