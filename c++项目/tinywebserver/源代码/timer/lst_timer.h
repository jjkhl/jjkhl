/*
定时器处理非活动连接
===============
由于非活跃连接占用了连接资源，严重影响服务器的性能，
通过实现一个服务器定时器，处理这种非活跃连接，释放连接资源。
利用alarm函数周期性地触发SIGALRM信号,该信号的信号处理函数利用管道通知主循环执行定时器链表上的定时任务.
> * 统一事件源
> * 基于升序链表的定时器
> * 处理非活动连接
*/

/*
定时器结点类util_timer，每个结点表示一个客户连接，它保存了双向链表的前后指针，客户数据client_data和回调函数。
如果我们判断到这个结点长时间无反应，就会调用这个回调函数传入client_data，然后回调函数就会把这个客户断开，并且做一些善后工作。
*/
#ifndef LST_TIMER
#define LST_TIMER
#include "../allhead.h"
#include "../log/log.h"
//连接资源结构体成员需要用到定时器类，所以需要前向声明
class util_timer;

//连接资源
struct client_data
{
    //客户端socket地址
    sockaddr_in address;
    //socket文件描述符
    int sockfd;
    //定时器 
    util_timer *timer;
};

//定时器类
class util_timer
{
public:
    util_timer():prev(NULL),next(NULL){}

public:
    //超时时间
    time_t expire;

    //指针函数，用作回调函数，执行定时事件
    void (*cb_func)(client_data *);
    //连接资源
    client_data* user_data;
    //前向定时器
    util_timer* prev;
    //后继定时器
    util_timer* next;
};

/*
基于升序双向链表的定时器
为每个连接创建一个定时器，并将其添加到链表中，并按照超时时间升序排序。
执行任务时，将到期的定时器从链表中删除
*/
class sort_timer_lst
{
public:
    sort_timer_lst();
    ~sort_timer_lst();

    //特殊情况升序插入结点：timer为NULL；head为NULL；timer为新的头结点
    void add_timer(util_timer *timer);
    //调整对应定时器在链表中的位置
    void adjust_timer(util_timer *timer);
    //删除超时的定时器
    void del_timer(util_timer *timer);
    //定时任务处理函数
    void tick();

private:
    //私有成员，被公有成员add_timer和adjust_time调用
    //主要用于调整链表内部结点
    void add_timer(util_timer *timer, util_timer *lst_head);

    util_timer *head;
    util_timer *tail;
};

/*
最外层的类，包含升序双向链表来对定时器进行相关操作
*/
class Utils
{
public:
    Utils() {}
    ~Utils() {}

    void init(int timeslot);

    //对文件描述符设置非阻塞
    int setnonblocking(int fd);

    //将内核事件表注册读事件，ET模式，选择开启EPOLLONESHOT
    void addfd(int epollfd, int fd, bool one_shot, int TRIGMode);

    //信号处理函数
    static void sig_handler(int sig);

    //设置信号函数
    void addsig(int sig, void(handler)(int), bool restart = true);

    //定时处理任务，重新定时以不断触发SIGALRM信号
    void timer_handler();

    void show_error(int connfd, const char *info);

public:
    /*
    u_pipefd[0]是管道读端，指从管道读出数据
    u_pipefd[1]是管道写端，指数据写入到管道
    */
    static int *u_pipefd;
    //升序双向定时器链表
    sort_timer_lst m_timer_lst;
    static int u_epollfd;
    int m_TIMESLOT;
};

//从u_epollfd中删除user_data中的sockfd，关闭sockfd，最后用户数量减一
void cb_func(client_data *user_data);
#endif