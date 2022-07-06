/*
http连接处理类
===============
根据状态转移,通过主从状态机封装了http连接类。其中,主状态机在内部调用从状态机,从状态机将处理状态和数据传给主状态机
> * 客户端发出http连接请求
> * 从状态机读取数据,更新自身状态和接收数据,传给主状态机
> * 主状态机根据从状态机状态,更新自身状态,决定响应请求还是继续读取
*/
#ifndef HTTPCONNECTION_H
#define HTTPCONNECTION_H
#include "../lock/locker.h"
#include "../CGImysql/sql_connection_pool.h"
#include "../timer/lst_timer.h"
#include "../log/log.h"

class http_conn
{
public:
    //设置读取文件名称m_real_file大小
    static const int FILENAME_LEN = 200;
    //设置读缓冲区m_read_buf大小
    static const int READ_BUFFER_SIZE = 2048;
    //设置写缓冲区m_write_buf大小
    static const int WRITE_BUFFER_SIZE = 1024;
    //报文的请求方法，本项目只用到GET和POST
    enum METHOD {GET = 0,POST,HEAD,PUT,DELETE,TRACE,OPTIONS,CONNECT,PATH};
    /*
        主状态机的状态。是在解析客户端请求时。
    */
    enum CHECK_STATE
    {
        CHECK_STATE_REQUESTLINE = 0,    //正在分析请求行
        CHECK_STATE_HEADER,             //正在分析请求头
        CHECK_STATE_CONTENT             //正在分析请求体
    };
    /*
        服务器处理HTTP请求的可能结果，报文解析的结果
    */
    enum HTTP_CODE
    {
        NO_REQUEST,             //请求不完整，需要继续读取客户数据，跳转主线程继续监测读事件
        GET_REQUEST,            //获得了一个完成的客户请求，使用do_request完成请求资源映射
        BAD_REQUEST,            //客户请求语法错误或请求资源为目录，跳转process_write完成响应报文
        NO_RESOURCE,            //服务器没有资源，跳转process_write完成响应报文
        FORBIDDEN_REQUEST,      //客户对资源没有足够的访问权限，跳转process_write完成响应报文
        FILE_REQUEST,           //文件请求，获取文件成功，体哦啊转process_write完成响应报文
        INTERNAL_ERROR,         //服务器内部错误，该结果在主状态机逻辑switch的default下，一般不会触发
        CLOSED_CONNECTION       //客户端已关闭连接
    };

    /*
    从状态机的三种可能状态，即行的读取状态，分别表示
    1.读取到一个完整的行 2.行出错 3.行数据尚且不完整
    */
    enum LINE_STATUS
    {
        LINE_OK = 0, //读取一个完整的行
        LINE_BAD, //行错误
        LINE_OPEN //行数据不完整
    };

public:
    http_conn() {}
    ~http_conn() {}

public:
    //初始化套接字地址，函数内部会调用私有方法init
    void init(int sockfd, const sockaddr_in &addr, char *, int, int, string user, string passwd, string sqlname);
    //关闭HTTP连接
    void close_conn(bool real_close = true);
    //处理客户端请求
    void process();
    //读取浏览器端发来的全部数据
    bool read_once();
    //响应报文非阻塞写入
    bool write();
    //返回通信地址
    sockaddr_in *get_address()
    {
        return &m_address;
    }
    //同步线程初始化数据库读取表
    void initmysql_result(connection_pool *connPool);

    int timer_flag;
    //XXX:待查明improv解释
    int improv;

private:
    //初始化连接其余信息
    void init();
    //从m_read_buf中解析HTTP请求
    HTTP_CODE process_read();
    //向m_write_buf写入HTTP报文响应
    bool process_write(HTTP_CODE ret);
    //主状态机解析请求首行
    HTTP_CODE parse_request_line(char *text);
    //主状态机解析请求头
    HTTP_CODE parse_headers(char *text);
    //主状态机解析请求体
    HTTP_CODE parse_content(char *text);
    //生成响应报文
    HTTP_CODE do_request();
    /*
    m_start_line是行在buffer中的起始位置，将该位置后面的数据赋给text
    此时从状态机已提前将一行的末尾字符\r\n变为\0\0，所以text可以直接取出完整的行进行解析
    */
    char *get_line() { return m_read_buf + m_start_line; };
    //从状态机读取一行，分析是请求报文额哪一部分
    LINE_STATUS parse_line();
    //下面函数被process_write调用，使用do_request函数完成填充HTTP应答
    void unmap();
    bool add_response(const char *format, ...);
    bool add_content(const char *content);
    bool add_status_line(int status, const char *title);
    bool add_headers(int content_length);
    bool add_content_type();
    bool add_content_length(int content_length);
    bool add_linger();
    bool add_blank_line();

public:
    static int m_epollfd;
    static int m_user_count;
    MYSQL *mysql;
    int m_state; //读为0, 写为1

private:
    //通信socket
    int m_sockfd;
    //通信socket地址
    sockaddr_in m_address;
    //读缓冲区
    char m_read_buf[READ_BUFFER_SIZE];

    //标识读缓冲区中m_read_buf中数据的最后一个字节的下一个位置
    int m_read_idx;
    //从状态机在m_read_buf读取的位置
    int m_checked_idx;
    //m_read_buf中已经解析的字符个数
    int m_start_line;
    
    //写缓冲区
    char m_write_buf[WRITE_BUFFER_SIZE];
    //指示buffer中的长度
    int m_write_idx;
    //主状态机当前所处状态,默认为CHECK_STATE_REQUESTLINE
    CHECK_STATE m_check_state;
    //请求方法,默认为GET
    METHOD m_method;
    // 客户请求的目标文件的完整路径，其内容等于 doc_root + m_url, doc_root是网站根目录
    char m_real_file[FILENAME_LEN];
    //请求目标的文件名
    char *m_url;
    //请求的协议版本
    char *m_version;
    //主机名
    char *m_host;
    // HTTP请求的消息总长度
    int m_content_length;
    // HTTP请求是否保持连接,默认false,即不保持连接
    bool m_linger;
    //客户请求的目标被mmap到内存中的位置
    char *m_file_address;
    // stat详细介绍：http://c.biancheng.net/cpp/html/326.html
    //目标文件的状态。用以判断文件是否存在、是否为目录、是否可读，并获取文件大小等信息
    struct stat m_file_stat;

    /*
    定义下面2个成员，其中m_iv_count表示被写内存块的数量
    */
    struct iovec m_iv[2];
    int m_iv_count;

    //是否启用的POST，1启动，0不启动
    int cgi;
    //存储请求头数据
    char *m_string;
    //将要发送的数据的字节数
    int bytes_to_send;
    //已经发送的字节数
    int bytes_have_send;
    //网站根目录
    char *doc_root;

    map<string, string> m_users;
    //1表示ET，0表示LT
    int m_TRIGMode;
    int m_close_log;

    char sql_user[100];
    char sql_passwd[100];
    char sql_name[100];
};

#endif

//请求报文
// GET / HTTP/1.1
// Accept: text/html,application/xhtml+xml,application/xml;q=0.9,image/avif,image/webp,image/apng,*/*;q=0.8,application/signed-exchange;v=b3;q=0.9
// Accept-Encoding: gzip, deflate
// Accept-Language: zh-CN,zh;q=0.9
// Connection: keep-alive
// Host: 192.168.0.237:9006
// Upgrade-Insecure-Requests: 1
// User-Agent: Mozilla/5.0 (Windows NT 10.0; Win64; x64) AppleWebKit/537.36 (KHTML, like Gecko) Chrome/103.0.0.0 Safari/537.36

//响应报文
// HTTP/1.1 200 OK
// Content-Length:612
// Connection:keep-alive
