/*
 * @Description: 
 * @Version: 2.0
 * @Autor: jjkhl
 * @Date: 2021-11-29 16:12:06
 * @LastEditors: jjkhl
 * @LastEditTime: 2021-11-30 20:36:00
 */
#include <iostream>
#include <thread>
#include <chrono>
#include <string>
using namespace std;
int ticket = 0;
int f1();
int f2();
void welcome();
void welcome2();
void menu();
void dingpiao();
void tuipiao();
void watch();
void browseticket();
void change();
int main()
{
    int j = 1;
    while (true)
    {
        system("cls");
        welcome();
        cout << "管理员进入请按1，客户进入请按2：";
        ticket = 0;
        while (j)
        {
            cin >> j;
            if (j < 1 && j > 2)
            {
                cout << "请输入1或2进入民航管理系统: " << endl;
                continue;
            }
            else
            {
                int i = 3;
                switch (j)
                {
                case 1:
                {
                    string tmp = "";
                    cout << "请输入管理员账户的6位数密码(默认密码：888888)：" << endl;

                    string password = "888888";
                    while (cin >> tmp)
                    {
                        if (tmp.size() == 6 && tmp == password)
                        {
                            cout << "密码正确" << endl;
                            int temp = f1();
                            if (temp == 0)
                            {
                                break;
                            }
                        }
                        else
                            cout << "密码错误，您还剩余" << --i << "次机会" << endl;
                        if (i == 0)
                        {
                            cout << "您的机会没有了，请重新选择系统进入" << endl;
                            cout << "管理员进入请按1，客户进入请按2：";
                            break;
                        }
                    }
                    break;
                }
                case 2:
                {
                    cout << "已进入客户界面，您仅能查询航空信息" << endl;
                    int temp = f2();
                    if (temp == 0)
                        break;
                }
                }
                break;
            }
        }
    }
    system("pause");
    return 0;
}
void dingpiao()
{
    system("cls");
    welcome();
    welcome2();
    browseticket();
    cout << "请输入您需要预定的机票：";
    while (true)
    {
        if (ticket > 0 && ticket <= 3)
        {
            watch();
            cout << "请您输入0，返回上级菜单完成退票后再进行订票" << endl;
        }
        cin >> ticket;
        if (ticket >= 0 && ticket <= 3)
        {
            switch (ticket)
            {
            case 1:
                cout << "您成功订购北京到上海的机票" << endl;
                break;
            case 2:
                cout << "您成功订购从北京到香港的机票" << endl;
                break;
            case 3:
                cout << "您成功订购从北京到南京的机票" << endl;
                break;
            case 0:
            {
                cout << "即将返回上级菜单" << endl;
                f1();
                break;
            }
            }
            break;
        }
        else
        {
            cout << "当前没有该航班，请重新选择" << endl;
            continue;
        }
    }
}
void tuipiao()
{
    system("cls");
    welcome();
    watch();
    cout << "您确定需要退票吗？" << endl;
    int tmp = 0;
    cout << "1 确定；0 取消并返回上级菜单" << endl;
    cin >> tmp;
    if (tmp == 1)
    {
        ticket = 0;
        cout << "您已成功退票" << endl;
    }
}

void watch()
{
    if (ticket == 1)
    {
        cout << "您当前的机票为：北京到上海" << endl;
    }
    else if (ticket == 2)
    {
        cout << "您当前的机票为：北京到香港" << endl;
    }
    else if (ticket == 3)
    {
        cout << "您当前的机票为：北京到南京" << endl;
    }
    else
    {
        cout << "您当前没有订购本公司的机票" << endl;
    }
}

void browseticket()
{
    cout << "当前航班有：" << endl;
    cout << "1.Beijing-->Shanghai" << endl;
    cout << "2.Beijing-->Hongkong" << endl;
    cout << "3.Beijing->Nanjin" << endl;
}

void change()
{
    system("cls");
    welcome();
    watch();
    //退票
    cout << "您确定需要换票吗？" << endl;
    int tmp = 0;
    cout << "1 确定；0 取消并返回上级菜单" << endl;
    cin >> tmp;
    if (tmp == 1)
    {
        ticket = 0;
        browseticket();
        dingpiao();
    }
}

//管理员界面
int f1()
{
    int select = 1;
    while (select != 0)
    {
        system("cls");
        welcome();
        cout << "\033[31;47m您目前位于管理员界面\033[0m" << endl;
        menu();
        cout << "请输入您需要的操作(0-5)：" << endl;
        cin >> select;
        if (select >= 0 && select <= 5)
        {
            switch (select)
            {
            case 1:
                dingpiao();
                break;
            case 2:
                tuipiao();
                break;
            case 3:
                watch();
                break;
            case 4:
                browseticket();
                break;
            case 5:
                change();
                break;
            case 0:
            {
                cout << "谢谢使用！" << endl;
                return select;
                break;
            }
            }
        }
        else
        {
            cout << "按键错误！请重新输入0-5的操作：";
        }
        this_thread::sleep_for(chrono::seconds(3));
    }
}
//客户界面
int f2()
{
    int select = 1;
    while (select != 0)
    {
        system("cls");
        cout << "\033[31;47m您位于用户界面\033[0m" << endl;
        cout << "\t1 订购机票\t" << endl;
        cout << "\t2 退订机票\t" << endl;
        cout << "\t3 查看航班信息\t" << endl;
        cout << "\t4 查询航班信息\t" << endl;
        cout << "\t0 返回主界面\t" << endl;
        cout << "请输入您需要的操作(0-4)：";
        cin >> select;
        if (select >= 0 && select <= 4)
        {
            switch (select)
            {
            case 1:
                dingpiao();
                break;
            case 2:
                tuipiao();
                break;
            case 3:
                watch();
                break;
            case 4:
                browseticket();
                break;
            case 0:
            {
                cout << "谢谢使用！" << endl;
                return select;
                break;
            }
            }
        }
        else
        {
            cout << "按键错误！请重新输入0-4的操作：" << endl;
        }
        this_thread::sleep_for(chrono::seconds(3));
    }
}
//欢迎界面
void welcome()
{
    cout << "\033[32m$\t\t\t\t$" << endl;
    cout << "|\t\t\t\t|" << endl;
    cout << "|     *欢迎进入民航管理系统*    |" << endl;
    cout << "|\t\t\t\t|" << endl;
    cout << "@\t\t\t\t@\033[0m" << endl;
}
//欢迎界面2
void welcome2()
{
    cout << "欢迎您订购本公司的飞机票！" << endl;
    cout << "非常感谢！" << endl;
    cout << "我们将为您提供优质服务！" << endl;
    cout << "如果您需要，可以输入0来返回上级菜单。" << endl;
}
//下一级菜单
void menu()
{
    cout << "\t1 订购机票\t" << endl;
    cout << "\t2 退订机票\t" << endl;
    cout << "\t3 查看航班信息\t" << endl;
    cout << "\t4 查询航班信息\t" << endl;
    cout << "\t5 修改航班信息\t" << endl;
    cout << "\t0 返回主界面\t" << endl;
}