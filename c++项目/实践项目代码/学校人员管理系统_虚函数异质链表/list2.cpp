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

    //���֤����ͬ��ֻ����һ��
    if(cur!=NULL&&cur->ID==key)
    {
        cout<<"�Բ��𣬸����֤���ѱ�ע�ᣡ"<<endl;
    }
    else
    {
        cout<<"��Ϣ����ɹ�"<<endl;
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
        cout<<"���֤��Ϊ��"<<id<<"�ļ�¼�Ѿ��ɹ�ɾ���ˣ�"<<endl;
    }
    else if(cur!=NULL&&pre!=NULL)
    {
        pre->next=cur->next;
        delete cur;
        cout<<"���֤��Ϊ��"<<id<<"�ļ�¼�Ѿ��ɹ�ɾ���ˣ�"<<endl;
    }
    else
    {
        cout<<"���������֤��Ϊ��"<<id<<"�ļ�¼��"<<endl;
    }
}

void list::print_list()
{
    people * cur=root;
    if(cur==NULL)
        cout<<"������Ա��Ϣ"<<endl;
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
        cout<<"���޴��ˣ��������������֤��!"<<endl;
    }
}