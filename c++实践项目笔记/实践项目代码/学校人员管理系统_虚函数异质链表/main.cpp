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
    cout<<"*��ӭ������������ķǶ�̬��ʵ�ֳ���*"<<endl;
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
        cout<<"����������Ҫ��ѯ�����ݣ�"<<endl;
        cout<<"1.�����в�����"<<endl;
        cout<<"2.������ɾ�����"<<endl;
        cout<<"3.��ʾ��������"<<endl;
        cout<<"4.��ѯ�����еĽ��"<<endl;
        cout<<"0.�˳�"<<endl;
        cout<<"��ѡ�񰴼�(0-4): ";
        cin>>i;
        cout<<endl;
        if(i>=0&&i<=4)
        {
            switch(i)
            {
                case 0:
                    cout<<"��ӭ�´�ʹ�ñ�����"<<endl;
                    break;
                case 1:
                    {
                        cout<<"����������Ҫ�������Ա����"<<endl;
                        
                        cout<<"ѧ���밴0�������밴1���̹��밴2"<<endl;
                        cin>>type;
                        cout<<"����������: ";
                        cin>>m_name;
                        cout<<"�������Ա�";
                        cin>>m_sex;
                        cout<<"���������䣺";
                        cin>>m_age;
                        cin.clear();
                        cout<<"���������֤�ţ�";
                        cin>>m_ID;
                        cout<<"�������ͥ��ַ��";
                        cin>>m_address;
                        cout<<"������绰���룺";
                        cin>>m_phone;

                        //ѧ����Ϣ
                        if(type==0)
                        {
                            cout<<"������ѧ����ƽ���֣�";
                            cin>>m_average;
                            cout<<"������ѧ�����꼶��";
                            cin>>m_grade;
                            student stu(m_name,m_sex,m_age,m_ID,m_address,m_phone,m_average,m_grade);
                            person.insert_people(&stu);
                        }
                        //������Ϣ
                        else if(type==1)
                        {
                            cout<<"��������ڵ���н��";
                            cin>>m_annual_salary;

                            professor pro(m_name,m_sex,m_age,m_ID,m_address,m_phone,m_annual_salary);
                            person.insert_people(&pro);

                        }
                        //�̹���Ϣ
                        else if(type==2)
                        {
                            cout<<"������̹���ʱн��";
                            cin>>m_hourly_salary;

                            staff sta(m_name,m_sex,m_age,m_ID,m_address,m_phone,m_hourly_salary);
                            person.insert_people(&sta);
                        }
                        //
                    }
                    break;
                case 2:
                    {
                        cout<<"��������Ҫɾ������Ա�����֤�ţ�";
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
                        cout<<"������Ҫ��ѯ����Ա�����֤�ţ�";
                        cin>>m_ID;

                        person.search(m_ID);
                        break;
                    }

            }
        }
        else
        {
            cout<<"��������������ѡ��"<<endl;
        }
        cout<<endl;
    }
    system("pause");
    return 0;
}