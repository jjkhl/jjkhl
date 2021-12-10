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
        void pay(){};//计算月薪
        void prompt(int);//升级函数
        void displayStatus(){};//显示所有人员信息
};

class technician:virtual public employee
{
    protected:
        double bonus;//奖金
        int jixiao;//绩效分数
    public:
        technician();
        void pay();
        void displayStatus();
};

class salesman:virtual public employee
{
    protected:
        double rate_bonus;//销售额提成
        double sales;//销售额
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