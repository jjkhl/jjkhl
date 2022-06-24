#include <iostream>
#include <string.h>
#include <sys/socket.h>
#include <sys/epoll.h>
#include <arpa/inet.h>
#include <unistd.h>
#include <signal.h>
#include <errno.h>
#include <fcntl.h>

#include "threadpool.h"
#include "locker.h"
#include "http_conn.h"

//最大文件描述符个数
#define MAX_FD 65535
//监听的最大事件数量
#define MAX_EVENT_NUMBER 10000
using namespace std;

//添加信号捕捉
/*
    https://www.cnblogs.com/deyuanqin/p/5755039.html

    void(handler)(int)：指向返回void值的函数指针
*/

/*
    struct sigaction
{
    void (*sa_handler) (int);
    sigset_t sa_mask;
    int sa_flags;
    void (*sa_restorer) (void);
}
1、sa_handler 此参数和signal()的参数handler 相同, 代表新的信号处理函数, 其他意义请参考signal().
2、sa_mask 用来设置在处理该信号时暂时将sa_mask 指定的信号搁置.
3、sa_restorer 此参数没有使用.
4、sa_flags 用来设置信号处理的其他相关操作, 下列的数值可用：
   A_NOCLDSTOP: 如果参数signum 为SIGCHLD, 则当子进程暂停时并不会通知父进程
   SA_ONESHOT/SA_RESETHAND: 当调用新的信号处理函数前, 将此信号处理方式改为系统预设的方式.
   SA_RESTART: 被信号中断的系统调用会自行重启
   SA_NOMASK/SA_NODEFER: 在处理此信号未结束前不理会此信号的再次到来. 如果参数oldact 不是NULL 指针, 则原来的信号处理方式会由此结构sigaction 返回.

int sigaction(int signum, const struct sigaction *act, struct sigaction *oldact);
signum：要操作的信号
act：要设置的对信号的新处理方式
oldact：原来对信号的处理方式
*/
void addsig(int sig, void(handler)(int))
{
    struct sigaction sa;
    //初始化sa
    memset(&sa, '\0', sizeof(sa));
    //设置sa的处理函数
    sa.sa_handler = handler;
    //将sa.sa_mask信号集初始化，然后把所有信号加入到此信号集
    sigfillset(&sa.sa_mask);
    //为sig注册处理方式sa，其中包含处理函数
    sigaction(sig, &sa, NULL);
}

//添加文件描述符到epoll中
extern void addfd(int epollfd,int fd,bool oneshot);
//从epoll中删除文件描述符
extern void removefd(int epollfd,int fd);
//修改文件描述符
extern void modfd(int epollfd,int fd,int ev);
int main(int argc, char **argv)
{
    if (argc <= 1)
    {
        cerr << "按照如下格式运行："
             << basename(argv[0])
             << "port_number" << endl;
        return 0;
    }
    int port = atoi(argv[1]);

    //对SIGPIPE信号进行忽略处理
    // SIGPIPE：客户端程序向服务器端程序发送了消息，然后关闭客户端，服务器端返回消息的时候就会收到内核给的SIGPIPE信号。
    addsig(SIGPIPE, SIG_IGN);

    //创建线程池，初始化线程池
    threadpool<http_conn> *pool = NULL;
    try
    {
        pool = new threadpool<http_conn>;
    }
    catch (...)
    {
        return -1;
    }

    //创建一个数组用于保存所有的客户端信息
    http_conn *users = new http_conn[MAX_FD];

    int listenfd = socket(PF_INET, SOCK_STREAM, 0);

    int reuse = 1;
    /*
    绑定之前设置设置端口复用
    SOL_SOCKET以存取socket层
    SO_REUSEADDR允许在bind()过程中本地地址可以重复使用
    reuse表示预设定的值
    */
    setsockopt(listenfd, SOL_SOCKET, SO_REUSEADDR, &reuse, sizeof(reuse));

    sockaddr_in address;
    memset(&address, 0, sizeof(address));
    address.sin_family=AF_INET;
    address.sin_addr.s_addr=INADDR_ANY;
    address.sin_port=htons(port);

    //绑定
    bind(listenfd, (sockaddr *)&address, sizeof(address));

    //监听
    listen(listenfd,5);

    //创建epoll对象、事件数组，添加
    epoll_event events[MAX_EVENT_NUMBER];
    //epoll_create中参数必须大于0，同时该参数会被忽略
    int epollfd=epoll_create(5);

    //将监听的文件描述符添加到epoll对象中
    addfd(epollfd,listenfd,false);
    http_conn::m_epollfd=epollfd;

    while (1)
    {
        int num=epoll_wait(epollfd,events,MAX_EVENT_NUMBER,-1);
        //如果不是中断的错误
        if((num==-1)&&(errno!=EINTR))
        {
            cout<<"epoll failure"<<endl;
            break;
        }

        //循环遍历事件数组
        for(int i=0;i<num;i++)
        {
            int sockfd=events[i].data.fd;
            //有客户端连接
            if(sockfd==listenfd)
            {   
                sockaddr_in client_address;
                socklen_t client_addrlen=sizeof(client_address);
                int connfd=accept(listenfd,(sockaddr*)&client_address,&client_addrlen);
                //目前连接数过多
                if(http_conn::m_user_count>=MAX_FD)
                {
                    //TODO:给客户端返回：服务器内部正忙。
                    close(connfd);
                    continue;
                }

                //将新客户的数据初始化，放入数组中
                users[connfd].init(connfd,client_address);


            }
            //对方异常断开或错误等事件
            else if(events[i].events&(EPOLLRDHUP|EPOLLHUP|EPOLLERR))
            {
                users[sockfd].close_conn();
            }
            //如果有读事件发生
            else if(events[i].events&EPOLLIN)
            {
                //一次性把所有数据都读完
                if(users[sockfd].read())
                {
                    pool->append(users+sockfd);
                }
                else
                {
                    users[sockfd].close_conn();
                }
            }
            //写事件发生
            else if(events[i].events&EPOLLOUT)
            {
                //一次性写完所有数据
                if(!users[sockfd].write())//失败
                {
                    users[sockfd].close_conn();
                }
            }
        }
    }
    close(epollfd);
    close(listenfd);
    delete []users;
    delete pool;
    return 0;
}