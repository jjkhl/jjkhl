#include"list.cpp"
using namespace std;
int main(int argc,char *argv[])
{
    int i=1;
    cout<<"----------------------------------"<<endl;
    cout<<"*                                *"<<endl;
    cout<<"欢迎进入异质链表的非多态性实现程序"<<endl;
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
        cout<<"请选择您选择的内容："<<endl;
        cout<<"1.链表中插入节点"<<endl;
        cout<<"2.链表中删除节点"<<endl;
        cout<<"3.显示整个链表"<<endl;
        cout<<"4.查询链表中的结点"<<endl;
        cout<<"请选择按键(0-4): ";
        cin>>i;
        cout<<endl;
        if(i>=0&&i<=4)
        {
            switch(i)
            {
                case 1:
                    {
                        cout<<"请输入姓名：";
                        cin>>name_s;

                        cout<<"请输入性别：";
                        cin>>sex_s;

                        cout<<"请输入年龄：";
                        cin>>age_s;

                        cout<<"请输入身份证号：";
                        cin>>ID_s;

                        cout<<"请输入家庭地址：";
                        cin>>add_s;

                        cout<<"请输入电话号码：";
                        cin>>phone_s;

                        cout<<"请输入人员类别（0：学生；1：教授；2：职工）：";
                        cin>>type_s;

                        switch(type_s)
                        {
                            case 0:
                                cout<<"请输入平均分：";
                                cin>>average;

                                cout<<"请输入年级：";
                                cin>>grade;

                                tmp.set_average(average);
                                tmp.set_grade(grade);
                                tmp.set_node_type(student);
                                break;
                            case 1:
                                cout<<"请输入年薪：";
                                cin>>annual_salary;

                                tmp.set_annual_salary(annual_salary);
                                tmp.set_node_type(professor);
                                break;
                            case 2:
                                cout<<"请输入小时工资：";
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
                    //删除结点
                    case 2:
                        cout<<"请输入要删除的人员的身份证号：";
                        cin>>ID_s;

                        people.remove(ID_s);
                        break;
                    case 3:
                        people.print_list();
                        break;
                    case 4:
                        cout<<"请输入需要查询的人员的身份证号：";
                        cin>>ID_s;

                        people.search(ID_s);
                        break;

            }
        }
        else
        {
            cout<<"按键错误，请重新选择!"<<endl;
            cout<<endl;
        }
    }
    system("pause");
    return 0;
}