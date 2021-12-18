#include"node.cpp"
using namespace std;

class list
{
    private:
        node *root;
    public:
        list()
        {
            root=0;
        }
    void insert(node *n);
    void remove(char *id);
    void search(char *id);
    void print_list();  
};

void list::insert(node *n)
{
    char key[18];
    strcpy(key,n->ID);

    node *cur_node=root;
    node *pre_node=0;

    while(cur_node!=0&&strcmp(cur_node->ID,key)>0)
    {
        pre_node=cur_node;
        cur_node=cur_node->next;
    }
    
    node *new_node=new node(n->name,n->sex,n->age,n->ID,n->address,n->phone,n->type);
    switch(n->type)
    {
        case student:
            new_node->s.grade=n->s.grade;
            new_node->s.average=n->s.average;
            break;
        case professor:
            new_node->annual_salary=n->annual_salary;
            break;
        case staff:
            new_node->hourly_salary=n->hourly_salary;
            break;
    }
    new_node->next=cur_node;
    if(pre_node==0)
        root=new_node;
    else
    {
        pre_node->next=new_node;
    }
}

void list::remove(char *id)
{
    node *cur_node=this->root;   
    node *pre_node=NULL;
    //��IDǰ
    while(cur_node!=NULL&&strcmp(cur_node->ID,id)<0)
    {
        pre_node=cur_node;
        cur_node=cur_node->next;
    }

    if(cur_node!=0&&pre_node==0)
    {
        root=cur_node->next;
        delete cur_node;
        cout<<"���֤�ţ�"<<id<<"�ɹ�ɾ��!"<<endl;
    }
    else if(cur_node!=0&&pre_node!=0)
    {
        pre_node->next=cur_node->next;
        delete cur_node;
        cout<<"���֤�ţ�"<<id<<"�ɹ�ɾ��!"<<endl;
    }
    else
    {
        cout<<"�Բ���������û�������Ա����Ϣ!"<<endl;
    }
}

void list::print_list()
{
    node *cur=root;

    while(cur!=0)
    {
        cout<<"\t������"<<cur->name<<endl;
        cout<<"\t�Ա�"<<cur->sex<<endl;
        cout<<"\t���䣺"<<cur->age<<endl;
        cout<<"\t���֤�ţ�"<<cur->ID<<endl;
        cout<<"\t��ַ��"<<cur->address<<endl;
        cout<<"\t�绰���룺"<<cur->phone<<endl;

        switch(cur->type)
        {
            case student:
                cout<<"\t��Ա��ݣ�ѧ��"<<endl;
                cout<<"\tƽ���֣�"<<cur->s.average<<endl;
                cout<<"\t�꼶��"<<cur->s.grade<<endl;
                break;
            case professor:
                cout<<"\t��Ա��ݣ�����"<<endl;
                cout<<"\t��н��"<<cur->annual_salary<<endl;
                break;
            case staff:
                cout<<"\t��Ա��ݣ��̹�"<<endl;
                cout<<"\tСʱ���ʣ�"<<cur->hourly_salary<<endl;
                break;
        }

        cur=cur->next;
        cout<<"=================================="<<endl;
    }
}

void list::search(char *id)
{
    node *cur=root;
    node *pre=NULL;

    while(cur&&strcmp(cur->ID,id)<0)
    {
        pre=cur;
        cur=cur->next;
    }
    if(cur)
    {
        cout<<"\t������"<<cur->name<<endl;
        cout<<"\t�Ա�"<<cur->sex<<endl;
        cout<<"\t���䣺"<<cur->age<<endl;
        cout<<"\t���֤�ţ�"<<cur->ID<<endl;
        cout<<"\t��ַ��"<<cur->address<<endl;
        cout<<"\t�绰���룺"<<cur->phone<<endl;

        switch(cur->type)
        {
            case student:
                cout<<"\t��Ա��ݣ�ѧ��"<<endl;
                cout<<"\tƽ���֣�"<<cur->s.average<<endl;
                cout<<"\t�꼶��"<<cur->s.grade<<endl;
                break;
            case professor:
                cout<<"\t��Ա��ݣ�����"<<endl;
                cout<<"\t��н��"<<cur->annual_salary<<endl;
                break;
            case staff:
                cout<<"\t��Ա��ݣ��̹�"<<endl;
                cout<<"\tСʱ���ʣ�"<<cur->hourly_salary<<endl;
                break;
        }
    }
    else
        cout<<"�Բ���û���ҵ������!"<<endl;
}