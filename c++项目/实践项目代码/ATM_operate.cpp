#include <iostream>
#include <iomanip>
#include <conio.h>
using namespace std;
int password = 666666;
double balance = 50000;
bool Input_pass();
void work();
void display_balance();
void draw_money();
void save_money();
void transfer_money();
void updatePassword();
void menu_select();
void Bank_card();

void Bank_Card()
{
    cout << "***************���п�****************" << endl;
    cout << "*                                   *" << endl;
    cout << "*" << setw(15) << "���룺" << password << setw(15) << "*" << endl;
    cout << "*" << setw(15) << " ��" << balance << setw(16) << "*" << endl;
    cout << "*                                   *" << endl;
    cout << "*                                   *" << endl;
    cout << "*************************************" << endl;
}

void menu_select() //�˵���ѡ��
{
    cout << "************************************************************" << endl;
    cout << "***********************���д���ϵͳ v1.0********************" << endl;
    cout << "*                                                          *" << endl;
    cout << "*                         1.��ѯ                           *" << endl;
    cout << "*                         2.ȡ��                           *" << endl;
    cout << "*                         3.���                           *" << endl;
    cout << "*                         4.ת��                           *" << endl;
    cout << "*                         5.����                           *" << endl;
    cout << "*                         0.�˳�                           *" << endl;
    cout << "************************************************************" << endl;
    cout << endl
         << endl;
}

int main()
{
    Bank_Card();
    if (Input_pass())
    {
        system("cls");
        work();
    }
    else
        cout << "��������ѳ����������ޣ�����ϵ���й�����Ա������" << endl;
    system("pause");
    return 0;
}
bool Input_pass()
{
    int num = 0;
    int Ipass = 0;
    do
    {
        cout << "���������룺" << endl;
        if (num > 0)
            cout << "���ǵ�" << num << "���������룬���β��Խ��������п�" << endl;
        cin >> Ipass;
        ++num;
        if (Ipass == password)
            return true;
        else
            return false;

    } while (!Ipass && num < 4);
}
void work()
{
    cout << setw(10) << "��ӭʹ�����д���ϵͳ" << endl;
    menu_select();
    int select = -1;
    bool out = false;
    do
    {
        cout << "����������Ҫ����ҵ������" << endl;
        cin >> select;
        if (select < 0 || select > 5)
        {
            cout << "������������ȷ��ҵ�����" << endl;
            continue;
        }
        else
        {
            switch (select)
            {
            case 1:
                display_balance();
                break;
            case 2:
                draw_money();
                break;
            case 3:
                save_money();
                break;
            case 4:
                transfer_money();
                break;
            case 5:
                updatePassword();
                break;
            case 0:
                system("cls");
                Bank_Card();
                cout << "��ܰ��ʾ����ȡ���������п���" << endl;
                out = true;
                break;
            }
        }
    } while (!out);
}
void display_balance()
{
    cout << "����ǰ�����Ϊ��" << balance << endl;
}

void draw_money()
{
    double money = 0;
    cout << "������ȡ����";
    cin >> money;
    if (money <= balance)
    {
        balance -= money;
        cout << "����ʣ�ࣺ" << balance << endl;
    }
    else
    {
        cout << "���㣬ȡ��ʧ��" << endl;
    }
}

void save_money()
{
    double money = 0;
    cout << "���������";
    cin >> money;
    while (money < 0)
    {
        cout << "�������������0�Ĵ���" << endl;
        cin >> money;
    }
    balance += money;
    cout << "���������Ϊ��" << balance << endl;
}

void transfer_money()
{
    double money;
    int iAccount2;
    cout << "������ת�˽�";
    cin >> money;
    cout << "������Է��˻���";
    cin >> iAccount2;
    if (money > balance)
    {
        cout << "�����˻����㣬ת��ʧ��" << endl;
    }
    else
    {
        balance -= money;
        cout << "ת��" << iAccount2 << "���������Ϊ��" << balance << "Ԫ��" << endl;
    }
}

void updatePassword()
{
    int p1, p2;
    cout << "����������룺";
    cin >> p1;
    if (p1 != password)
    {
        cout << "��������������󣬲������޸�����" << endl;
    }
    else
    {
        cout << "�������µ����룺" << endl;
        cin >> p1;
        cout << "��ȷ�����룺" << endl;
        cin >> p2;
        if (p1 == p2)
        {
            password = p1;
            cout << "�����޸ĳɹ�" << endl;
        }
        else
        {
            cout << "�����������벻һ�£������޸Ĵ���" << endl;
        }
    }
}