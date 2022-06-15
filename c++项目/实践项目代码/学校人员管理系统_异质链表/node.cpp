/*
 * @Description: 
 * @Autor: jhl
 * @Date: 2021-12-18 19:55:59
 * @LastEditors: jjkhl
 * @LastEditTime: 2021-12-18 20:56:23
 */
#include<iostream>
#include<string.h>
using namespace std;
//枚举3种结点类型
enum node_type{student,staff,professor};

struct student_type
{
    float average;
    int grade;
};

class node
{
    friend class list;
    private:
        char name[15];
        char sex[2];
        int age;
        char ID[20];
        char address[30];
        long phone;
        node_type type;
        // student_type s;
        // float annual_salary;
        // float hourly_salary;
        //使用匿名联合体(无名字的联合体)起到枚举的作用
        union
        {
            student_type s;
            float annual_salary;
            float hourly_salary;
        };
        node *next;
    public:
        node(char *name1,char *sex1,int age1,char *ID1,char *address1,long phone1,node_type type1)
        {
            strcpy(name,name1);
            cout<<name<<endl;
            strcpy(sex,sex1);
            age=age1;
            strcpy(ID,ID1);
            strcpy(address,address1);
            phone=phone1;
            type=type1;
            next=0;
        }

        node()
        {
            name[0]='\0';
            sex[0]='\0';
            age=0;
            address[0]='\0';
            phone=0;
            next=0;
        }
        
        void set_node_type(node_type Type)
        {
            this->type=Type;
        }

        void set_name(char* Name)
        {
            strcpy(this->name,Name);
        }

        void set_sex(char *Sex)
        {
            strcpy(this->sex,Sex);
        }

        void set_age(int Age)
        {
            this->age=Age;
        }

        void set_ID(char *id)
        {
            strcpy(this->ID,id);
        }

        void set_address(char *Addr)
        {
            strcpy(this->address,Addr);
        }

        void set_phone(long Phone)
        {
            this->phone=Phone;
        }

        void set_average(float Ave)
        {
            s.average=Ave;
        }

        void set_grade(int Grade)
        {
            s.grade=Grade;
        }

        void set_annual_salary(float salary)
        {
            annual_salary=salary;
        }

        void set_hourly_salary(float hsalary)
        {
            hourly_salary=hsalary;
        }
};