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
    cout << "***************银行卡****************" << endl;
    cout << "*                                   *" << endl;
    cout << "*" << setw(15) << "密码：" << password << setw(15) << "*" << endl;
    cout << "*" << setw(15) << " 余额：" << balance << setw(16) << "*" << endl;
    cout << "*                                   *" << endl;
    cout << "*                                   *" << endl;
    cout << "*************************************" << endl;
}

void menu_select() //菜单中选项
{
    cout << "************************************************************" << endl;
    cout << "***********************银行储蓄系统 v1.0********************" << endl;
    cout << "*                                                          *" << endl;
    cout << "*                         1.查询                           *" << endl;
    cout << "*                         2.取款                           *" << endl;
    cout << "*                         3.存款                           *" << endl;
    cout << "*                         4.转账                           *" << endl;
    cout << "*                         5.改密                           *" << endl;
    cout << "*                         0.退出                           *" << endl;
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
        cout << "密码错误已超出当天上限，请联系银行工作人员！……" << endl;
    system("pause");
    return 0;
}
bool Input_pass()
{
    int num = 0;
    int Ipass = 0;
    do
    {
        cout << "请输入密码：" << endl;
        if (num > 0)
            cout << "这是第" << num << "次输入密码，三次不对将冻结银行卡" << endl;
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
    cout << setw(10) << "欢迎使用银行储蓄系统" << endl;
    menu_select();
    int select = -1;
    bool out = false;
    do
    {
        cout << "请输入您需要办理业务的序号" << endl;
        cin >> select;
        if (select < 0 || select > 5)
        {
            cout << "请重新输入正确的业务序号" << endl;
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
                cout << "温馨提示：请取走您的银行卡。" << endl;
                out = true;
                break;
            }
        }
    } while (!out);
}
void display_balance()
{
    cout << "您当前的余额为：" << balance << endl;
}

void draw_money()
{
    double money = 0;
    cout << "请输入取款余额：";
    cin >> money;
    if (money <= balance)
    {
        balance -= money;
        cout << "您还剩余：" << balance << endl;
    }
    else
    {
        cout << "余额不足，取款失败" << endl;
    }
}

void save_money()
{
    double money = 0;
    cout << "请输入存款金额：";
    cin >> money;
    while (money < 0)
    {
        cout << "请重新输入大于0的存款金额：" << endl;
        cin >> money;
    }
    balance += money;
    cout << "您现在余额为：" << balance << endl;
}

void transfer_money()
{
    double money;
    int iAccount2;
    cout << "请输入转账金额：";
    cin >> money;
    cout << "请输入对方账户：";
    cin >> iAccount2;
    if (money > balance)
    {
        cout << "您的账户余额不足，转账失败" << endl;
    }
    else
    {
        balance -= money;
        cout << "转给" << iAccount2 << "后，您的余额为：" << balance << "元。" << endl;
    }
}

void updatePassword()
{
    int p1, p2;
    cout << "请输入旧密码：";
    cin >> p1;
    if (p1 != password)
    {
        cout << "您的密码输入错误，不允许修改密码" << endl;
    }
    else
    {
        cout << "请输入新的密码：" << endl;
        cin >> p1;
        cout << "请确定密码：" << endl;
        cin >> p2;
        if (p1 == p2)
        {
            password = p1;
            cout << "密码修改成功" << endl;
        }
        else
        {
            cout << "两次密码输入不一致，密码修改错误。" << endl;
        }
    }
}