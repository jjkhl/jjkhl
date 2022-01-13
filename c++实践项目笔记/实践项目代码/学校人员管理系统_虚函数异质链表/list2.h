/*
 * @Description: 多态实现的异质链表程序的头文件
 * @Autor: jhl
 * @Date: 2022-01-11 20:33:18
 * @LastEditors: jjkhl
 * @LastEditTime: 2022-01-12 22:17:22
 */
#ifndef LIST2_H
#define LIST2_H
#include<iostream>
#include<string.h>
using namespace std;
class people;
class list
{
    private:
        people *root;
    public:
        list(){root=NULL;}
        void insert_people(people *n);//链表中插入结点
        void remove(string id);//链表中删除结点
        void search(string id);//查询某个结点
        void print_list();//遍历展示整个链表
};
//people类的定义
class people
{
    private:
        friend class list;
    protected:
        string name;
        string sex;
        int age;
        string ID;
        string address;
        long phone;
        static people* ptr;
        people *next;
    public:
        people(string p_name,string p_sex,int p_age,string p_ID,string p_address,long p_phone)
        {
            name=p_name;
            sex=p_sex;
            age=p_age;
            ID=p_ID;
            address=p_address;
            phone=p_phone;
            next=NULL;
        }
        people()
        {
            name="";
            sex="";
            age=0;
            ID="";
            address="";
            next=NULL;
        }
        void set_name(string p_name)
        {
            name=p_name;
        }
        void set_sex(string p_sex)
        {
            sex=p_sex;
        }
        void set_age(int p_age)
        {
            age=p_age;
        }
        void set_ID(string p_ID)
        {
            ID=p_ID;
        }
        void set_address(string p_address)
        {
            address=p_address;
        }
        void set_phone(long p_phone)
        {
            phone=p_phone;
        }

        virtual void print()
        {
            cout<<"\t姓名："<<name<<endl;
            cout<<"\t性别："<<sex<<endl;
            cout<<"\t年龄："<<age<<endl;
            cout<<"\t身份证号："<<ID<<endl;
            cout<<"\t地址："<<address<<endl;
            cout<<"\t电话号码："<<phone<<endl;            
        }
        virtual void newperson() =0;
};

class student:public people
{
    friend class list;
    private:
        float average;
        int grade;
    public:
        student(string s_name,string s_sex,int s_age,string s_ID,string s_address,long s_phone,float s_average,int s_grade)
        :people(s_name,s_sex,s_age,s_ID,s_address,s_phone)
        { 
            this->average=s_average;
            this->grade=s_grade;
        }
        student():people()
        {
            average=0.0;
            grade=0;
        }
        void set_average(float s_average)
        {
            average=s_average;
        }
        void set_grade(int s_grade)
        {
            grade=s_grade;
        }
        void print()
        {
            people::print();
            cout<<"\t人员身份：学生"<<endl;
            cout<<"\t平均分："<<average<<endl;
        }
        void newperson()
        {
            ptr=new student(name,sex,age,ID,address,phone,average,grade);
        }
};
class professor:public people
{
    friend class list;
    private:
        float annual_salary;
    public:
        professor(string p_name,string p_sex,int p_age,string p_ID,string p_address,long p_phone,float p_salary)
        :people(p_name,p_sex,p_age,p_ID,p_address,p_phone)
        {
            annual_salary=p_salary;
        }
        professor():people()
        {
            annual_salary=0;
        }
        void set_annual_salary(float salary)
        {
            annual_salary=salary;
        }
        void print()
        {
            people::print();
            cout<<"\t人员身份：教授"<<endl;
            cout<<"\t年薪："<<annual_salary<<endl;
        }
        void newperson()
        {
            ptr=new professor(name,sex,age,ID,address,phone,annual_salary);
        }
};
class staff:public people
{
    friend class list;
    private:
        float hourly_salary;
    public:
        staff(string s_name,string s_sex,int s_age,string s_ID,string s_address,long s_phone,float s_hsalary)
        :people(s_name,s_sex,s_age,s_ID,s_address,s_phone)
        {
            this->hourly_salary=s_hsalary;
        }
        staff():people()
        {
            hourly_salary=0.0;
        }
        void set_hourly_salary(float hsalary)
        {
            hourly_salary=hsalary;
        }
        void print()
        {
            people::print();
            cout<<"\t人员身份：教工"<<endl;
            cout<<"\t时薪："<<hourly_salary<<endl;
        }
        void newperson()
        {
            ptr=new staff(name,sex,age,ID,address,phone,hourly_salary);
        }
};

#endif