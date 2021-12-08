/*
 * @Description: �����������Ķ���
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
    cout<<"********ϵͳ�˵�********"<<endl;
    cout<<"*     1.��������       *"<<endl;
    cout<<"*     2.��������       *"<<endl;
    cout<<"*     3.�����ʷ       *"<<endl;
    cout<<"*     0.�˳�ϵͳ       *"<<endl;
    cout<<"************************"<<endl;
    cout<<"����������ѡ��[0-3]��";
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
            //���������ַ���Ӱ��
            while((ch=getchar())!='\n')
            {
                continue;
            }
            cout<<"��������������������������ѡ��"<<endl;
            cin.clear();
            cin>>chooseItem;
        }
    }
    
}

void CalculatorAssistant::fractionCompute()
{
    Fraction f1;
    Fraction f2;
    cout<<"****��������****"<<endl;
    cout<<"����������������[��ʽΪ1/4]��"<<endl;
    cin>>f1>>f2;
    cout<<"����1��"<<f1<<endl;
    cout<<"����2��"<<f2<<endl;
    cout<<"����1+����2="<<f1+f2<<endl;
    cout<<"����1-����2="<<f1-f2<<endl;
    cout<<"����1*����2="<<f1*f2<<endl;
    cout<<"����1/����2="<<f1/f2<<endl;

    cout<<"������1="<<+f1<<endl;
    cout<<"������1="<<-f1<<endl;
    cout<<"������2="<<+f2<<endl;
    cout<<"������2="<<-f2<<endl;

    cout<<"����1>����2��1-�� 0-��"<<(f1>f2)<<endl;
    cout<<"����1<����2��1-�� 0-��"<<(f1<f2)<<endl;
    cout<<"����1==����2��1-�� 0-��"<<(f1==f2)<<endl;
    cout<<"����1!=����2��1-�� 0-��"<<(f1!=f2)<<endl;
    cout<<"����1>=����2��1-�� 0-��"<<(f1>=f2)<<endl;
    cout<<"����1<=����2��1-�� 0-��"<<(f1<=f2)<<endl;
}

void CalculatorAssistant::complexCompute()
{
    Complex c1;
    Complex c2;
    Complex c3;
    double number;
    cout<<"****��������****"<<endl;
    cout<<"��������������������(1,4)��"<<endl;
    cin>>c1>>c2;
    cout<<"������һ��С��[double����]��";
    cin>>number;
    cout<<"����1 = ";
    c1.display();
    cout<<"����2 = ";
    c2.display();
    cout<<"С��="<<number<<endl;
    cout<<"����������������ļ�������"<<endl;
    cout<<"����1 + ����2 = ";
    c3=c1+c2;
    c3.display();

    cout<<"����1 + С�� = ";
    (c1+number).display();

    cout<<"С�� + ����1 = ";
    (number+c1).display();

    cout<<"����1 - ����2 = ";
    c3=c1-c2;
    c3.display();

    cout<<"����1 - С�� = ";
    (c1-number).display();

    cout<<"С�� - ����1 = ";
    (number-c1).display();

     cout<<"����1 * ����2 = ";
    c3=c1*c2;
    c3.display();

    cout<<"����1 * С�� = ";
    (c1*number).display();

    cout<<"С�� * ����1 = ";
    (number*c1).display();

    cout<<"����1 / ����2 = ";
    c3=c1/c2;
    c3.display();

    cout<<"����1 / С�� = ";
    (c1/number).display();

    cout<<"С�� / ����1 = ";
    (number/c1).display();

}