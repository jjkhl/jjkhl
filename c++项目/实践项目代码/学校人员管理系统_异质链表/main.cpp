#include"list.cpp"
using namespace std;
int main(int argc,char *argv[])
{
    int i=1;
    cout<<"----------------------------------"<<endl;
    cout<<"*                                *"<<endl;
    cout<<"��ӭ������������ķǶ�̬��ʵ�ֳ���"<<endl;
    cout<<"*                                *"<<endl;
    cout<<"----------------------------------"<<endl;
    list people;
    node tmp;

    char name_s[15];
    char sex_s[2];
    int age_s;
    char ID_s[20];
    char add_s[30];
    long phone_s;
    int type_s;
    float annual_salary;
    float hourly_salary;
    float average;
    int grade;

    while(i)
    {
        cout<<"��ѡ����ѡ������ݣ�"<<endl;
        cout<<"1.�����в���ڵ�"<<endl;
        cout<<"2.������ɾ���ڵ�"<<endl;
        cout<<"3.��ʾ��������"<<endl;
        cout<<"4.��ѯ�����еĽ��"<<endl;
        cout<<"��ѡ�񰴼�(0-4): ";
        cin>>i;
        cout<<endl;
        if(i>=0&&i<=4)
        {
            switch(i)
            {
                case 1:
                    {
                        cout<<"������������";
                        cin>>name_s;

                        cout<<"�������Ա�";
                        cin>>sex_s;

                        cout<<"���������䣺";
                        cin>>age_s;

                        cout<<"���������֤�ţ�";
                        cin>>ID_s;

                        cout<<"�������ͥ��ַ��";
                        cin>>add_s;

                        cout<<"������绰���룺";
                        cin>>phone_s;

                        cout<<"��������Ա���0��ѧ����1�����ڣ�2��ְ������";
                        cin>>type_s;

                        switch(type_s)
                        {
                            case 0:
                                cout<<"������ƽ���֣�";
                                cin>>average;

                                cout<<"�������꼶��";
                                cin>>grade;

                                tmp.set_average(average);
                                tmp.set_grade(grade);
                                tmp.set_node_type(student);
                                break;
                            case 1:
                                cout<<"��������н��";
                                cin>>annual_salary;

                                tmp.set_annual_salary(annual_salary);
                                tmp.set_node_type(professor);
                                break;
                            case 2:
                                cout<<"������Сʱ���ʣ�";
                                cin>>hourly_salary;

                                tmp.set_hourly_salary(hourly_salary);
                                tmp.set_node_type(staff);
                                break;
                        }
                        tmp.set_name(name_s);
                        tmp.set_sex(sex_s);
                        tmp.set_age(age_s);
                        tmp.set_ID(ID_s);
                        tmp.set_address(add_s);
                        tmp.set_phone(phone_s);
                        people.insert(&tmp);

                        break;
                    }
                    //ɾ�����
                    case 2:
                        cout<<"������Ҫɾ������Ա�����֤�ţ�";
                        cin>>ID_s;

                        people.remove(ID_s);
                        break;
                    case 3:
                        people.print_list();
                        break;
                    case 4:
                        cout<<"��������Ҫ��ѯ����Ա�����֤�ţ�";
                        cin>>ID_s;

                        people.search(ID_s);
                        break;

            }
        }
        else
        {
            cout<<"��������������ѡ��!"<<endl;
            cout<<endl;
        }
    }
    system("pause");
    return 0;
}