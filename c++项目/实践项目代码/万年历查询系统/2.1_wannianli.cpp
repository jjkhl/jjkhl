/*
 * @Description: 
 * @Autor: jhl
 * @Date: 2021-12-04 13:53:56
 * @LastEditors: jjkhl
 * @LastEditTime: 2021-12-05 15:22:14
 */
#include <iostream>
#include <thread>
#include <chrono>
#include <iomanip>
#include <Windows.h>
using namespace std;
bool back_menu = false;
const char *week[] = {"星期日", "星期一", "星期二", "星期三", "星期四", "星期五", "星期六"};
int count_days(int year);
int month_days(int year, int month);
void show_year();
void show_month(int year, int month);
void show_day(int day, int month, int year);
void welcome();
void menu1();
int main()
{
    int i = 1;
    while (i)
    {
        welcome();
        menu1();
        cin >> i;
        cout << endl;
        if (i >= 0 && i <= 3)
        {
            switch (i)
            {
            case 0:
                cout << "期待您的下次使用" << endl;
                break;
            case 1:
            {
                show_year();
                break;
            }
            case 2:
            {
                int year, month;
                cout << "请输入您查询的年份和月份(例如2021 12)：" << endl;
                cin.sync();
                cin >> year >> month;
                while ((month < 1 || month > 12))
                {
                    cout << "请重新输入您查询的月份(例如1-12)：" << endl;
                    cin >> month;
                }
                system("cls");
                cout << "正在查询..." << endl;
                this_thread::sleep_for(chrono::seconds(2));
                system("cls");
                welcome();
                show_month(year, month);
                break;
            }
            case 3:
            {
                system("cls");
                welcome();
                cout << "请按照年-月-日的顺序输入您查询的日期(例如2021 12 04)：" << endl;
                int year, month, day;
                cin >> year >> month >> day;
                show_day(day, month, year);
                break;
            }
            }
        }
        else
        {
            cout << "按键错误，请重新选择" << endl;
        }
        if (back_menu)
        {
            cout << "即将返回主菜单" << endl;
            this_thread::sleep_for(chrono::seconds(2));
            system("cls");
        }
        back_menu = false;
    }
    system("pause");
    return 0;
}
int count_days(int year)
{
    if ((year % 4 == 0 && year % 100 != 0) || (year % 400) == 0)
    {
        return 366;
    }
    else
    {
        return 365;
    }
}
int month_days(int year, int month)
{
    int flag = 0;
    int days = 0;
    switch (month)
    {
    //大月
    case 1:
    case 3:
    case 5:
    case 7:
    case 8:
    case 10:
    case 12:
        days = 31;
        break;
    //小月
    case 4:
    case 6:
    case 9:
    case 11:
        days = 30;
        break;
    case 2:
    {
        flag = (year % 4 == 0 && year % 100 != 0) || (year % 400) == 0;
        if (flag == 0)
        {
            days = 28;
        }
        else
        {
            days = 29;
        }
    }
    }
    return days;
}
void show_year()
{
    while(true)
    {
    system("cls");
    welcome();
    int year;
    cout << "请输入您需要查询的年份：" << endl;
    cin.sync();
    cin >> year;
    int year_sum = count_days(year);
    int color=0x01;
    for (int month = 1; month <= 12; month++)
    {
        int day=1;
        int replace_month=month;
        int replace_year=year;
        if (month == 1 || month == 2)
        {
            replace_year -= 1;
            replace_month += 12;
        }
        int iWeek = (day + 2 * replace_month + 3 * (replace_month + 1) / 5 + replace_year + replace_year / 4 - replace_year / 100 + replace_year / 400) % 7 + 1;
        SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 8 | color);
        cout << month << "月: " << endl;
        SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 8 | FOREGROUND_GREEN);
        cout << "一\t二\t三\t四\t五\t六\t日" << endl;
        SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), color);
        for (int tmp = 1; tmp < iWeek; tmp++)
        {
            cout << "\t";
        }
        int days = month_days(year, month);
        int temp = 0;
        for (int j = iWeek; j <= 7; j++)
        {
            cout << day++ << "\t";
        }
        cout << endl;
        temp = day - 1;
        if(temp==7)
            temp=0;
        while (day <= days)
        {
            cout << day << "\t";
            if (temp == (day++ % 7))
                cout << endl;
        }
        cout<<endl;
        color++;
    }
    bool tmp=true;
    SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 7);
    cout << "继续查询请按1，返回上级菜单请按0：";
    cin.sync();
    cin >> tmp;
    if (tmp)
    {
        system("cls");
        welcome();
        continue;
    }
    else
    {
        back_menu = true;
        break;
    }
    }
}
void show_month(int year, int month)
{
    while (true)
    {
        int day=1;
        if (month == 1 || month == 2)
        {
            year -= 1;
            month += 12;
        }
        int iWeek = (day + 2 * month + 3 * (month + 1) / 5 + year + year / 4 - year / 100 + year / 400) % 7 + 1;
        cout << year<<"年"<<month << "月: " << endl;
        SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 8 | FOREGROUND_GREEN);
        cout << "一\t二\t三\t四\t五\t六\t日" << endl;
        SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 7);
        for (int tmp = 1; tmp < iWeek; tmp++)
        {
            cout << "\t";
        }
        int days = month_days(year, month);
        int temp = 0;
        for (int j = iWeek; j <= 7; j++)
        {
            cout << day++ << "\t";
        }
        cout << endl;
        temp = day - 1;
        if(temp==7)
            temp=0;
        while (day <= days)
        {
            cout << day << "\t";
            // int a=day%7;
            if (temp == (day++ % 7))
                cout << endl;
        }
        bool tmp = true;
        cout<<endl;
        cout << "继续查询请按1，返回上级菜单请按0：";
        cin.sync();
        cin >> tmp;
        if (tmp)
        {
            system("cls");
            welcome();
            cout << "请输入您查询的年份和月份(例如2021 12)：" << endl;
            cin.sync();
            cin >> year >> month;
            while ((month < 1 || month > 12))
            {
                cout << "请重新输入您查询的月份(例如1-12)：" << endl;
                cin >> month;
            }
            continue;
        }
        else
        {
            back_menu = true;
            break;
        }
    }
}

void show_day(int day, int month, int year)
{
    //基姆拉尔森计算公式：W= (d+2*m+3*(m+1)/5+y+y/4-y/100+y/400) mod 7
    //把一月和二月看成是上一年的十三月和十四月，例：如果是2004-1-10则换算成：2003-13-10来代入公式计算。
    while (true)
    {
        int replace_month=month;
        int replace_year=year;
        if (month == 1 || month == 2)
        {
            replace_year -= 1;
            replace_month += 12;
        }
        int iWeek = (day + 2 * replace_month + 3 * (replace_month + 1) / 5 + replace_year + replace_year / 4 - replace_year / 100 + replace_year / 400) % 7 + 1;
        switch (iWeek)
        {
        case 1:
            cout << year << "年" << month << "月" << day << "日是星期一" << endl;
            break;
        case 2:
            cout << year << "年" << month << "月" << day << "日是星期二" << endl;
            break;
        case 3:
            cout << year << "年" << month << "月" << day << "日是星期三" << endl;
            break;
        case 4:
            cout << year << "年" << month << "月" << day << "日是星期四" << endl;
            break;
        case 5:
            cout << year << "年" << month << "月" << day << "日是星期五" << endl;
            break;
        case 6:
            cout << year << "年" << month << "月" << day << "日是星期六" << endl;
            break;
        case 7:
            cout << year << "年" << month << "月" << day << "日是星期日" << endl;
            break;
        }
        cout << "继续查询请按1，返回上级菜单请按0：";
        bool tmp = true;
        cin.sync();
        cin >> tmp;
        if (tmp)
        {
            system("cls");
            welcome();
            cout << "请按照年-月-日的顺序继续输入您查询的日期(例如2021 12 04)：" << endl;
            cin >> year >> month >> day;
            continue;
        }
        else
        {
            back_menu = true;
            break;
        }
    }
}
void welcome()
{
    cout << "------------------------" << endl;
    cout << "*                      *" << endl;
    SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 8 | 4); //设置红色
    cout << " 欢迎来到万年历查询系统" << endl;
    SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 7);
    cout << "*                      *" << endl;
    cout << "------------------------" << endl;
}
void menu1()
{
    cout << "请选择您查询的内容：" << endl;
    cout << "\t1.显示该年的日历" << endl;
    cout << "\t2.显示该月的日历" << endl;
    cout << "\t3.显示某天是星期几" << endl;
    cout << "\t0.退出" << endl;
    cout << "请选择您使用的功能：" << endl;
}