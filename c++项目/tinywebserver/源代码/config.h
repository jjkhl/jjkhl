#ifndef CONFIG_H
#define CONFIG_H

#include "webserver.h"

class Config
{
public:
    Config();
    ~Config(){};

    void parse_arg(int argc, char **argv);

    //端口号
    int PORT;
    //日志写入方式
    int LOGWrite;
    //触发组合模式
    int TRIGMode;
    // listenfd触发模式
    int LISTENTrigmode;
    // connfd触发模式
    int CONNTrigmode;
    //优雅关闭连接
    int OPT_LINGER;
    //数据库连接池数量
    int sql_num;
    //线程池内的线程数量
    int thread_num;
    //是否关闭日志
    int close_log;
    /*
    Reactor和Proactor的理解：https://www.zhihu.com/question/26943938
    1.Reactor是非阻塞同步，理解为来了事件操作系统通知应用进程，让应用进程来处理
    2.Proactor是异步网络模式，理解为来了事件操作系统来处理，处理完再通知应用进程
    */
    //并发模型选择
    int actor_model;
};
#endif