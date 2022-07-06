#include "lst_timer.h"
#include "../http/http_conn.h"

sort_timer_lst::sort_timer_lst()
{
    head = NULL;
    tail = NULL;
}

sort_timer_lst::~sort_timer_lst()
{
    util_timer *tmp = head;
    while (tmp)
    {
        head = tmp->next;
        delete tmp;
        tmp = head;
    }
}

void sort_timer_lst::add_timer(util_timer *timer)
{
    if (!timer)
    {
        return;
    }
    if (!head)
    {
        head = tail = timer;
        return;
    }
    /*
    如果新的定时器超时时间小于当前头部结点
    直接将当前定时器结点作为头部结点
    */
    if (timer->expire < head->expire)
    {
        timer->next = head;
        head->prev = timer;
        head = timer;
        return;
    }
    //否则调用私有成员，调整内部结点
    add_timer(timer, head);
}

void sort_timer_lst::add_timer(util_timer *timer, util_timer *lst_head)
{
    //已经排除了timer作为头结点的情况，所以从头结点的下一位开始查找
    util_timer *prev = lst_head;
    util_timer *tmp = prev->next;
    //遍历当前结点之后的链表，按照超时时间找到目标定时器对应的位置，常规双向链表插入操作
    while (tmp)
    {
        if (timer->expire < tmp->expire)
        {
            prev->next = timer;
            timer->next = tmp;
            tmp->prev = timer;
            timer->prev = prev;
            break;
        }
        prev = tmp;
        tmp = tmp->next;
    }
    //遍历完发现，目标定时器需要放到尾结点处
    if (!tmp)
    {
        prev->next = timer;
        timer->prev = prev;
        timer->next = NULL;
        tail = timer;
    }
}

//调整定时器，任务发生变换时，调整定时器在链表中的位置
void sort_timer_lst::adjust_timer(util_timer *timer)
{
    // timer是被调整的定时器，head是定时器链表
    if (!timer)
    {
        return;
    }
    util_timer *tmp = timer->next;
    /*
    被调整的定时器在链表尾部
    定时器超时值仍然小于下一个定时器超时值，不调整
    */
    if (!tmp || (timer->expire < tmp->expire))
    {
        return;
    }
    //如果timer是头结点，则将单独的timer(双向都是NULL)插入到原head->next中
    if (timer == head)
    {
        head = head->next;
        head->prev = NULL;
        timer->next = NULL;
        add_timer(timer, head);
    }
    //如果timer不是头结点，则将其单独出来，然后加入到原timer->next中
    else
    {
        timer->prev->next = timer->next;
        timer->next->prev = timer->prev;
        //上面两步相当于在head链表中分割了timer结点
        add_timer(timer, timer->next);
    }
}

void sort_timer_lst::del_timer(util_timer *timer)
{
    if (!timer)
    {
        return;
    }
    //链表中只有一个定时器，需要删除该定时器
    if ((timer == head) && (timer == tail))
    {
        delete timer;
        head = NULL;
        tail = NULL;
        return;
    }
    //被删除的定时器为头结点
    if (timer == head)
    {
        head = head->next;
        head->prev = NULL;
        delete timer;
        return;
    }
    //被删除的定时器为尾结点
    if (timer == tail)
    {
        tail = tail->prev;
        tail->next = NULL;
        delete timer;
        return;
    }
    //被删除的定时器在链表内部，常规链表结点删除
    timer->prev->next = timer->next;
    timer->next->prev = timer->prev;
    delete timer;
}

void sort_timer_lst::tick()
{
    if (!head)
    {
        return;
    }
    //获取当前时间
    time_t cur = time(NULL);
    util_timer *tmp = head;
    //遍历定时器链表
    while (tmp)
    {
        //升序链表在当前时间小于定时器的超时时间时，后续的定时器也没有过期
        if (cur < tmp->expire)
        {
            break;
        }
        //当前定时器到期，则调用回调函数，执行定时事件
        tmp->cb_func(tmp->user_data);
        //重置头结点，将处理后的定时器从链表容器中删除
        head = tmp->next;
        if (head)
        {
            head->prev = NULL;
        }
        delete tmp;
        tmp = head;
    }
}

void Utils::init(int timeslot)
{
    m_TIMESLOT = timeslot;
}

int Utils::setnonblocking(int fd)
{
    int old_option = fcntl(fd, F_GETFL);
    int new_option = old_option | O_NONBLOCK;
    fcntl(fd, F_SETFL, new_option);
    return old_option;
}

void Utils::addfd(int epollfd, int fd, bool one_shot, int TRIGMode)
{
    epoll_event event;
    event.data.fd = fd;
    /*
    参考网址：https://blog.csdn.net/q576709166/article/details/8649911
    对端正常关闭（程序里close()，shell下kill或ctr+c），触发EPOLLIN和EPOLLRDHUP
    */
    if (1 == TRIGMode)
        event.events = EPOLLIN | EPOLLET | EPOLLRDHUP;
    else
        event.events = EPOLLIN | EPOLLRDHUP;
    /*
    采用EPOLLONETSHOT事件的文件描述符上的注册事件只触发一次，
    要想重新注册事件则需要调用epoll_ctl重置文件描述符上的事件，
    这样前面的socket就不会出现竞态。
    */
    if (one_shot)
        event.events |= EPOLLONESHOT;
    epoll_ctl(epollfd, EPOLL_CTL_ADD, fd, &event);
    setnonblocking(fd);
}
//信号处理函数
void Utils::sig_handler(int sig)
{
    //为保证函数的可重入性，保留原来的errno
    //可重入性表示中断后再次进入该函数，环境变量与之前相同，不会丢失数据
    int save_errno = errno;
    int msg = sig;
    //将信号值从管道写端写入，传输字符类型，而非整型
    send(u_pipefd[1], (char *)&msg, 1, 0);
    errno = save_errno;
}

/*
通过管道发送信号值，不处理信号对应的逻辑，缩短异步执行事件，减少对主程序的影响
设置信号函数
*/
void Utils::addsig(int sig, void(handler)(int), bool restart)
{
    //创建sigaction结构体变量
    struct sigaction sa;
    memset(&sa, '\0', sizeof(sa));
    //信号处理函数中只发送信号值，不做对应逻辑处理
    sa.sa_handler = handler;
    if (restart)
        sa.sa_flags |= SA_RESTART;
    //将所有信号加入到信号集
    sigfillset(&sa.sa_mask);
    //执行sigaction函数，设置信号新的处理方式
    assert(sigaction(sig, &sa, NULL) != -1);
}

void Utils::timer_handler()
{
    m_timer_lst.tick();
    alarm(m_TIMESLOT);
}

void Utils::show_error(int connfd, const char *info)
{
    send(connfd, info, strlen(info), 0);
    close(connfd);
}

int *Utils::u_pipefd = 0;
int Utils::u_epollfd = 0;

class Utils;
//定时器回调函数
void cb_func(client_data *user_data)
{
    //删除非活动连接在socket上的注册事件
    epoll_ctl(Utils::u_epollfd, EPOLL_CTL_DEL, user_data->sockfd, 0);
    assert(user_data);
    //关闭文件描述符
    close(user_data->sockfd);
    //减少连接数
    http_conn::m_user_count--;
}