/*
 * @Description: 
 * @Autor: jhl
 * @Date: 2021-12-21 19:24:06
 * @LastEditors: jjkhl
 * @LastEditTime: 2022-01-13 10:15:02
 */
#include<Windows.h>
#include"list2.h"
people *people::ptr=0;
void welcome()
{
    SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), FOREGROUND_INTENSITY|FOREGROUND_GREEN|FOREGROUND_BLUE);
    cout<<"------------------------------------"<<endl;
    cout<<"*                                  *"<<endl;
    cout<<"*欢迎进入异质链表的非多态性实现程序*"<<endl;
    cout<<"*                                  *"<<endl;
    cout<<"------------------------------------"<<endl;
    SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE),FOREGROUND_GREEN|FOREGROUND_BLUE|FOREGROUND_RED);
}

int main()
{
    welcome();
    list person;
    int type;
    string m_name,m_sex,m_ID,m_address;
    long m_phone;
    float m_annual_salary,m_hourly_salary,m_average;
    int m_age,m_grade;
    int i=1;
    while(i)
    {
        cout<<endl<<endl;
        cout<<"请输入您需要查询的内容："<<endl;
        cout<<"1.链表中插入结点"<<endl;
        cout<<"2.链表中删除结点"<<endl;
        cout<<"3.显示整个链表"<<endl;
        cout<<"4.查询链表中的结点"<<endl;
        cout<<"0.退出"<<endl;
        cout<<"请选择按键(0-4): ";
        cin>>i;
        cout<<endl;
        if(i>=0&&i<=4)
        {
            switch(i)
            {
                case 0:
                    cout<<"欢迎下次使用本程序"<<endl;
                    break;
                case 1:
                    {
                        cout<<"请输入您需要插入的人员级别"<<endl;
                        
                        cout<<"学生请按0，教授请按1，教工请按2"<<endl;
                        cin>>type;
                        cout<<"请输入姓名: ";
                        cin>>m_name;
                        cout<<"请输入性别：";
                        cin>>m_sex;
                        cout<<"请输入年龄：";
                        cin>>m_age;
                        cin.clear();
                        cout<<"请输入身份证号：";
                        cin>>m_ID;
                        cout<<"请输入家庭地址：";
                        cin>>m_address;
                        cout<<"请输入电话号码：";
                        cin>>m_phone;

                        //学生信息
                        if(type==0)
                        {
                            cout<<"请输入学生的平均分：";
                            cin>>m_average;
                            cout<<"请输入学生的年级：";
                            cin>>m_grade;
                            student stu(m_name,m_sex,m_age,m_ID,m_address,m_phone,m_average,m_grade);
                            person.insert_people(&stu);
                        }
                        //教授信息
                        else if(type==1)
                        {
                            cout<<"请输入教授的年薪：";
                            cin>>m_annual_salary;

                            professor pro(m_name,m_sex,m_age,m_ID,m_address,m_phone,m_annual_salary);
                            person.insert_people(&pro);

                        }
                        //教工信息
                        else if(type==2)
                        {
                            cout<<"请输入教工的时薪：";
                            cin>>m_hourly_salary;

                            staff sta(m_name,m_sex,m_age,m_ID,m_address,m_phone,m_hourly_salary);
                            person.insert_people(&sta);
                        }
                        //
                    }
                    break;
                case 2:
                    {
                        cout<<"请输入需要删除的人员的身份证号：";
                        cin>>m_ID;

                        person.remove(m_ID);
                        break;
                    }
                case 3:
                    {
                        person.print_list();
                        break;
                    }
                case 4:
                    {
                        cout<<"请输入要查询的人员的身份证号：";
                        cin>>m_ID;

                        person.search(m_ID);
                        break;
                    }

            }
        }
        else
        {
            cout<<"按键错误，请重新选择！"<<endl;
        }
        cout<<endl;
    }
    system("pause");
    return 0;
}