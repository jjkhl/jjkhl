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
        cout << "����Ա�����밴1���ͻ������밴2��";
        ticket = 0;
        while (j)
        {
            cin >> j;
            if (j < 1 && j > 2)
            {
                cout << "������1��2�����񺽹���ϵͳ: " << endl;
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
                    cout << "���������Ա�˻���6λ������(Ĭ�����룺888888)��" << endl;

                    string password = "888888";
                    while (cin >> tmp)
                    {
                        if (tmp.size() == 6 && tmp == password)
                        {
                            cout << "������ȷ" << endl;
                            int temp = f1();
                            if (temp == 0)
                            {
                                break;
                            }
                        }
                        else
                            cout << "�����������ʣ��" << --i << "�λ���" << endl;
                        if (i == 0)
                        {
                            cout << "���Ļ���û���ˣ�������ѡ��ϵͳ����" << endl;
                            cout << "����Ա�����밴1���ͻ������밴2��";
                            break;
                        }
                    }
                    break;
                }
                case 2:
                {
                    cout << "�ѽ���ͻ����棬�����ܲ�ѯ������Ϣ" << endl;
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
    cout << "����������ҪԤ���Ļ�Ʊ��";
    while (true)
    {
        if (ticket > 0 && ticket <= 3)
        {
            watch();
            cout << "��������0�������ϼ��˵������Ʊ���ٽ��ж�Ʊ" << endl;
        }
        cin >> ticket;
        if (ticket >= 0 && ticket <= 3)
        {
            switch (ticket)
            {
            case 1:
                cout << "���ɹ������������Ϻ��Ļ�Ʊ" << endl;
                break;
            case 2:
                cout << "���ɹ������ӱ�������۵Ļ�Ʊ" << endl;
                break;
            case 3:
                cout << "���ɹ������ӱ������Ͼ��Ļ�Ʊ" << endl;
                break;
            case 0:
            {
                cout << "���������ϼ��˵�" << endl;
                f1();
                break;
            }
            }
            break;
        }
        else
        {
            cout << "��ǰû�иú��࣬������ѡ��" << endl;
            continue;
        }
    }
}
void tuipiao()
{
    system("cls");
    welcome();
    watch();
    cout << "��ȷ����Ҫ��Ʊ��" << endl;
    int tmp = 0;
    cout << "1 ȷ����0 ȡ���������ϼ��˵�" << endl;
    cin >> tmp;
    if (tmp == 1)
    {
        ticket = 0;
        cout << "���ѳɹ���Ʊ" << endl;
    }
}

void watch()
{
    if (ticket == 1)
    {
        cout << "����ǰ�Ļ�ƱΪ���������Ϻ�" << endl;
    }
    else if (ticket == 2)
    {
        cout << "����ǰ�Ļ�ƱΪ�����������" << endl;
    }
    else if (ticket == 3)
    {
        cout << "����ǰ�Ļ�ƱΪ���������Ͼ�" << endl;
    }
    else
    {
        cout << "����ǰû�ж�������˾�Ļ�Ʊ" << endl;
    }
}

void browseticket()
{
    cout << "��ǰ�����У�" << endl;
    cout << "1.Beijing-->Shanghai" << endl;
    cout << "2.Beijing-->Hongkong" << endl;
    cout << "3.Beijing->Nanjin" << endl;
}

void change()
{
    system("cls");
    welcome();
    watch();
    //��Ʊ
    cout << "��ȷ����Ҫ��Ʊ��" << endl;
    int tmp = 0;
    cout << "1 ȷ����0 ȡ���������ϼ��˵�" << endl;
    cin >> tmp;
    if (tmp == 1)
    {
        ticket = 0;
        browseticket();
        dingpiao();
    }
}

//����Ա����
int f1()
{
    int select = 1;
    while (select != 0)
    {
        system("cls");
        welcome();
        cout << "\033[31;47m��Ŀǰλ�ڹ���Ա����\033[0m" << endl;
        menu();
        cout << "����������Ҫ�Ĳ���(0-5)��" << endl;
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
                cout << "ллʹ�ã�" << endl;
                return select;
                break;
            }
            }
        }
        else
        {
            cout << "������������������0-5�Ĳ�����";
        }
        this_thread::sleep_for(chrono::seconds(3));
    }
}
//�ͻ�����
int f2()
{
    int select = 1;
    while (select != 0)
    {
        system("cls");
        cout << "\033[31;47m��λ���û�����\033[0m" << endl;
        cout << "\t1 ������Ʊ\t" << endl;
        cout << "\t2 �˶���Ʊ\t" << endl;
        cout << "\t3 �鿴������Ϣ\t" << endl;
        cout << "\t4 ��ѯ������Ϣ\t" << endl;
        cout << "\t0 ����������\t" << endl;
        cout << "����������Ҫ�Ĳ���(0-4)��";
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
                cout << "ллʹ�ã�" << endl;
                return select;
                break;
            }
            }
        }
        else
        {
            cout << "������������������0-4�Ĳ�����" << endl;
        }
        this_thread::sleep_for(chrono::seconds(3));
    }
}
//��ӭ����
void welcome()
{
    cout << "\033[32m$\t\t\t\t$" << endl;
    cout << "|\t\t\t\t|" << endl;
    cout << "|     *��ӭ�����񺽹���ϵͳ*    |" << endl;
    cout << "|\t\t\t\t|" << endl;
    cout << "@\t\t\t\t@\033[0m" << endl;
}
//��ӭ����2
void welcome2()
{
    cout << "��ӭ����������˾�ķɻ�Ʊ��" << endl;
    cout << "�ǳ���л��" << endl;
    cout << "���ǽ�Ϊ���ṩ���ʷ���" << endl;
    cout << "�������Ҫ����������0�������ϼ��˵���" << endl;
}
//��һ���˵�
void menu()
{
    cout << "\t1 ������Ʊ\t" << endl;
    cout << "\t2 �˶���Ʊ\t" << endl;
    cout << "\t3 �鿴������Ϣ\t" << endl;
    cout << "\t4 ��ѯ������Ϣ\t" << endl;
    cout << "\t5 �޸ĺ�����Ϣ\t" << endl;
    cout << "\t0 ����������\t" << endl;
}