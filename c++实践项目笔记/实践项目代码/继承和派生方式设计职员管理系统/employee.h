/*
 * @Description: 
 * @Autor: jhl
 * @Date: 2021-12-09 13:55:28
 * @LastEditors: jjkhl
 * @LastEditTime: 2021-12-10 20:39:44
 */
class employee
{
    protected:
        char *name;
        int individual_number;
        int grade;
        float paycheck;
    public:
        employee();
        ~employee();
        void pay(){};//������н
        void prompt(int);//��������
        void displayStatus(){};//��ʾ������Ա��Ϣ
};

class technician:virtual public employee
{
    protected:
        double bonus;//����
        int jixiao;//��Ч����
    public:
        technician();
        void pay();
        void displayStatus();
};

class salesman:virtual public employee
{
    protected:
        double rate_bonus;//���۶����
        double sales;//���۶�
    public:
        salesman();
        void pay();
        void displayStatus();
};

class manager:virtual public employee
{
    protected:
        double  monthlypay;
    public:
        manager();
        void pay();
        void displayStatus();
};

class salesmanager:public manager,public salesman
{
    public:
        salesmanager();
        void pay();
        void displayStatus();
};

class techmanager:public manager,public technician
{
    public:
        techmanager();
        void pay();
        void displayStatus();
};