/*
 * @Description: 计算器函数的定义
 * @Autor: jhl
 * @Date: 2021-12-07 14:54:38
 * @LastEditors: jjkhl
 * @LastEditTime: 2021-12-07 21:58:56
 */
#include"CalculatorAssistant.h"
#include<string>
using namespace std;
void CalculatorAssistant::showMenu()
{
    cout<<"********系统菜单********"<<endl;
    cout<<"*     1.分数计算       *"<<endl;
    cout<<"*     2.复数计算       *"<<endl;
    cout<<"*     3.清除历史       *"<<endl;
    cout<<"*     0.退出系统       *"<<endl;
    cout<<"************************"<<endl;
    cout<<"请输入您的选择[0-3]：";
}
void CalculatorAssistant::run()
{
    int chooseItem;
    char ch;
    while (true)
    {
        showMenu();
        cin>>chooseItem;
        if(chooseItem==1)
        {
            fractionCompute();
            continue;
        }
        else if(chooseItem==2)
        {
            complexCompute();
            continue;
        }
        else if(chooseItem==0)
        {
            return;
        }
        else if(chooseItem==3)
        {
            system("cls");
            continue;
        }
        else
        {
            //消除其它字符的影响
            while((ch=getchar())!='\n')
            {
                continue;
            }
            cout<<"您的输入有误，请重新输入您的选择："<<endl;
            cin.clear();
            cin>>chooseItem;
        }
    }
    
}

void CalculatorAssistant::fractionCompute()
{
    Fraction f1;
    Fraction f2;
    cout<<"****分数计算****"<<endl;
    cout<<"请输入两个分数，[格式为1/4]："<<endl;
    cin>>f1>>f2;
    cout<<"分数1："<<f1<<endl;
    cout<<"分数2："<<f2<<endl;
    cout<<"分数1+分数2="<<f1+f2<<endl;
    cout<<"分数1-分数2="<<f1-f2<<endl;
    cout<<"分数1*分数2="<<f1*f2<<endl;
    cout<<"分数1/分数2="<<f1/f2<<endl;

    cout<<"正分数1="<<+f1<<endl;
    cout<<"负分数1="<<-f1<<endl;
    cout<<"正分数2="<<+f2<<endl;
    cout<<"负分数2="<<-f2<<endl;

    cout<<"分数1>分数2吗？1-是 0-否"<<(f1>f2)<<endl;
    cout<<"分数1<分数2吗？1-是 0-否"<<(f1<f2)<<endl;
    cout<<"分数1==分数2吗？1-是 0-否"<<(f1==f2)<<endl;
    cout<<"分数1!=分数2吗？1-是 0-否"<<(f1!=f2)<<endl;
    cout<<"分数1>=分数2吗？1-是 0-否"<<(f1>=f2)<<endl;
    cout<<"分数1<=分数2吗？1-是 0-否"<<(f1<=f2)<<endl;
}

void CalculatorAssistant::complexCompute()
{
    Complex c1;
    Complex c2;
    Complex c3;
    double number;
    cout<<"****复数计算****"<<endl;
    cout<<"请输入两个复数，比如(1,4)："<<endl;
    cin>>c1>>c2;
    cout<<"请输入一个小数[double类型]：";
    cin>>number;
    cout<<"复数1 = ";
    c1.display();
    cout<<"复数2 = ";
    c2.display();
    cout<<"小数="<<number<<endl;
    cout<<"下面是重载运算符的计算结果："<<endl;
    cout<<"复数1 + 复数2 = ";
    c3=c1+c2;
    c3.display();

    cout<<"复数1 + 小数 = ";
    (c1+number).display();

    cout<<"小数 + 复数1 = ";
    (number+c1).display();

    cout<<"复数1 - 复数2 = ";
    c3=c1-c2;
    c3.display();

    cout<<"复数1 - 小数 = ";
    (c1-number).display();

    cout<<"小数 - 复数1 = ";
    (number-c1).display();

     cout<<"复数1 * 复数2 = ";
    c3=c1*c2;
    c3.display();

    cout<<"复数1 * 小数 = ";
    (c1*number).display();

    cout<<"小数 * 复数1 = ";
    (number*c1).display();

    cout<<"复数1 / 复数2 = ";
    c3=c1/c2;
    c3.display();

    cout<<"复数1 / 小数 = ";
    (c1/number).display();

    cout<<"小数 / 复数1 = ";
    (number/c1).display();

}