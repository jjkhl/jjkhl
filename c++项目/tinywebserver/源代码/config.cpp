#include "config.h"

Config::Config()
{
    //默认端口号9006
    PORT = 9006;
    //日志写入方式，默认同步
    LOGWrite = 0;
    //触发组合模式，默认listenfd LT+ connfd LT
    TRIGMode = 0;
    // listenfd触发模式，默认LT
    LISTENTrigmode = 0;
    // connfd触发模式，默认LT
    CONNTrigmode = 0;
    //优雅关闭链接，默认不使用
    OPT_LINGER = 0;
    //数据库连接池数量，默认为8
    sql_num=8;
    //线程池内线程数量，默认为8
    thread_num = 8;
    //关闭日志，默认不关闭
    close_log = 0;
    //并发模式，默认proactor
    actor_model = 0;
}

void Config::parse_arg(int argc, char **argv)
{
    int opt;
    /*
    -p：指定端口号
    -l：指定日志写入方式，默认同步
    -m：指定触发模式，默认LT
    -o：指定是否优雅关闭链接，默认0表示不使用
    -s：指定数据库连接池数量，默认为8
    -t：指定线程池内线程数量，默认为8
    -c：指定是否关闭日志，默认0表示不关闭
    -a：指定并发模式，默认proactor
    */
    const char *str = "p:l:m:o:s:t:c:a:";
    /*
    getopt使用方式：https://blog.csdn.net/afei__/article/details/81261879
    一个冒号表示后面必须带有输入参数，两个冒号表示可以不带输入参数
    外部变量说明：
    optarg：如果某个选项有参数，则包含当前选项的参数字符串
    返回值：-1表示结束，?表示缺少输入参数
    */
    while ((opt = getopt(argc, argv, str)) != -1)
    {
        switch (opt)
        {
        case 'p':
        {
            PORT=atoi(optarg);
            break;
        }
        case 'l':
        {
            LOGWrite=atoi(optarg);
            break;
        }
        case 'm':
        {
            TRIGMode=atoi(optarg);
            break;
        }
        case 'o':
        {
            OPT_LINGER=atoi(optarg);
            break;
        }
        case 's':
        {
            sql_num=atoi(optarg);
            break;
        }
        case 't':
        {
            thread_num=atoi(optarg);
            break;
        }
        case 'c':
        {
            close_log=atoi(optarg);
            break;
        }
        case 'a':
        {
            actor_model=atoi(optarg);
            break;
        }
        default:
            break;
        }
    }
}