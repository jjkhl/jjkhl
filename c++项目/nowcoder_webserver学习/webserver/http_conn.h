#ifndef HTTPCONN_H
#define HTTPCONN_H
#include<iostream>
#include<string.h>
#include<signal.h>
#include<arpa/inet.h>
#include<sys/socket.h>
#include<sys/epoll.h>
#include<sys/mman.h>
#include<sys/uio.h>
#include<sys/stat.h>
#include<unistd.h>
#include<fcntl.h>
#include<stdarg.h>  //变参数va_list
#include"locker.h"
using namespace std;
//任务类
class http_conn{
public:
    //所有socket上的事件都被注册到同一个epoll对象中
    static int m_epollfd;

    //统计用户数量
    static int m_user_count;
    //读缓冲区大小
    static const int READ_BUFFER_SIZE=2048;
    //写缓冲区大小
    static const int WRITE_BUFFER_SIZE=1024;
    //文件名的最大长度
    static const int FILENAME_LEN=200;

    // HTTP请求方法，这里只支持GET
    enum METHOD {GET = 0, POST, HEAD, PUT, DELETE, TRACE, OPTIONS, CONNECT};
    /*
        解析客户端请求时，主状态机的状态
        CHECK_STATE_REQUESTLINE:当前正在分析请求行
        CHECK_STATE_HEADER:当前正在分析头部字段
        CHECK_STATE_CONTENT:当前正在解析请求体
    */
    enum CHECK_STATE { CHECK_STATE_REQUESTLINE = 0, CHECK_STATE_HEADER, CHECK_STATE_CONTENT };
    
    /*
        服务器处理HTTP请求的可能结果，报文解析的结果
        NO_REQUEST          :   请求不完整，需要继续读取客户数据
        GET_REQUEST         :   表示获得了一个完成的客户请求
        BAD_REQUEST         :   表示客户请求语法错误
        NO_RESOURCE         :   表示服务器没有资源
        FORBIDDEN_REQUEST   :   表示客户对资源没有足够的访问权限
        FILE_REQUEST        :   文件请求,获取文件成功
        INTERNAL_ERROR      :   表示服务器内部错误
        CLOSED_CONNECTION   :   表示客户端已经关闭连接了
    */
    enum HTTP_CODE { NO_REQUEST, GET_REQUEST, BAD_REQUEST, NO_RESOURCE, FORBIDDEN_REQUEST, FILE_REQUEST, INTERNAL_ERROR, CLOSED_CONNECTION };
    
    /* 
    从状态机的三种可能状态，即行的读取状态，分别表示
    1.读取到一个完整的行 2.行出错 3.行数据尚且不完整
    */
    enum LINE_STATUS { LINE_OK = 0, LINE_BAD, LINE_OPEN };

    http_conn(){}
    ~http_conn(){}
    //处理客户端请求
    void process();
    //初始化新接收的连接
    void init(int sockfd,const sockaddr_in& addr);
    //关闭连接
    void close_conn();
    //非阻塞读取
    bool read();
    //非阻塞写入
    bool write();
    


private:
    //通信的socket
    int m_sockfd;
    //通信socket地址
    sockaddr_in m_address;
    //读缓冲区
    char m_read_buf[READ_BUFFER_SIZE];
    //标识读缓冲区中以及读入的客户端数据最后一个字节的下一个位置
    int m_read_idx;
    //当前正在分析的字符在读缓冲区的位置
    int m_checked_idx;
    //当前正在解析行的起始位置
    int m_start_line;
    //请求目标的文件名
    char *m_url;
    //协议版本只支持HTTP1.1
    char *m_version;
    //请求方法
    METHOD m_method;
    //主机名
    char *m_host;
    //HTTP请求是否保持连接
    bool m_linger;
    //HTTP请求的消息总长度
    int m_content_length;

    //写缓冲区
    char m_write_buf[WRITE_BUFFER_SIZE];
    //写缓冲区待发送的字节数
    int m_write_idx;
    //客户请求的目标被mmap到内存中的起始位置
    char* m_file_address;
    //stat详细介绍：http://c.biancheng.net/cpp/html/326.html
    //目标文件的状态。用以判断文件是否存在、是否为目录、是否可读，并获取文件大小等信息
    struct stat m_file_stat;
    //writev执行写操作，定义下面2个成员，其中m_iv_count表示被写内存块的数量
    struct iovec m_iv[2];
    int m_iv_count;

    //将要发送的数据的字节数
    int bytes_to_send;
    //已经发送的字节数
    int bytes_have_send;

    //主状态机当前所处状态
    CHECK_STATE m_check_state;

    // 客户请求的目标文件的完整路径，其内容等于 doc_root + m_url, doc_root是网站根目录
    char m_real_file[READ_BUFFER_SIZE];



private:
    //初始化连接其余信息
    void init();

    //解析HTTP请求
    HTTP_CODE process_read();
    //解析请求首行
    HTTP_CODE parse_request_line(char *text);
    //解析请求头
    HTTP_CODE parse_headers(char *text);
    //解析请求体
    HTTP_CODE parse_content(char *text);
    //解析单行
    LINE_STATUS parse_line();

    char* get_line(){return m_read_buf+m_start_line;}
    HTTP_CODE do_request();

private:
    //下面函数被process_write调用以填充HTTP应答
    void unmap();
    bool add_response(const char* format,...);
    bool add_content( const char* content );
    bool add_content_type();
    bool add_status_line( int status, const char* title );
    bool add_headers( int content_length );
    bool add_content_length( int content_length );
    bool add_linger();
    bool add_blank_line();

    bool process_write(HTTP_CODE ret);
};
#endif

//GET请求报文
// GET / HTTP/1.1
// Host: 192.168.0.237:10000
// Connection: keep-alive
// Upgrade-Insecure-Requests: 1
// User-Agent: Mozilla/5.0 (Windows NT 10.0; Win64; x64) AppleWebKit/537.36 (KHTML, like Gecko) Chrome/102.0.5005.63 Safari/537.36
// Accept: text/html,application/xhtml+xml,application/xml;q=0.9,image/avif,image/webp,image/apng,*/*;q=0.8,application/signed-exchange;v=b3;q=0.9
// Accept-Encoding: gzip, deflate
// Accept-Language: zh-CN,zh;q=0.9