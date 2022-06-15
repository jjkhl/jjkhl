/*
 * @Description: 
 * @Autor: jhl
 * @Date: 2022-01-11 20:34:20
 * @LastEditors: jjkhl
 * @LastEditTime: 2022-01-13 10:33:33
 */
#include"list2.h"
void list::insert_people(people *n)
{
    string key;
    people *cur=root;
    people *pre=NULL;
    key=n->ID;
    while(cur!=NULL&&cur->ID<key)
    {
        pre=cur;
        cur=cur->next;
    }
    n->newperson();
    n->ptr->next=cur;

    //身份证号相同的只能由一个
    if(cur!=NULL&&cur->ID==key)
    {
        cout<<"对不起，该身份证号已被注册！"<<endl;
    }
    else
    {
        cout<<"信息插入成功"<<endl;
    }

    if(pre==NULL)
        root=n->ptr;
    else
        pre->next=n->ptr;
}

void list::remove(string id)
{
    people *cur=root;
    people *pre=NULL;
    while(cur!=NULL&&cur->ID!=id)
    {
        pre=cur;
        cur=cur->next;
    }

    if(cur!=NULL&&pre==NULL)
    {
        root=cur->next;
        delete cur;
        cout<<"身份证号为："<<id<<"的记录已经成功删除了！"<<endl;
    }
    else if(cur!=NULL&&pre!=NULL)
    {
        pre->next=cur->next;
        delete cur;
        cout<<"身份证号为："<<id<<"的记录已经成功删除了！"<<endl;
    }
    else
    {
        cout<<"不存在身份证号为："<<id<<"的记录！"<<endl;
    }
}

void list::print_list()
{
    people * cur=root;
    if(cur==NULL)
        cout<<"暂无人员信息"<<endl;
    cout<<endl;
    while(cur)
    {
        cur->print();
        cur=cur->next;
    }
}

void list::search(string id)
{
    people *cur=root;
    people *pre=NULL;

    while(cur&&cur->ID!=id)
    {
        pre=cur;
        cur=cur->next;
    }
    if(cur)
    {
        cur->print();
    }
    else
    {
        cout<<"查无此人，请重新输入身份证号!"<<endl;
    }
}