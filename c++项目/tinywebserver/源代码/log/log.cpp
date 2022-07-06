#include "log.h"
Log::Log()
{
    m_count = 0;
    m_is_async = false;
}

Log::~Log()
{
    if (m_fp)
        fclose(m_fp);
}
//异步需要设置阻塞队列的长度，同步不需要设置
bool Log::init(const char *file_name, int close_log, int log_buf_size, int split_lines, int max_queue_size)
{
    //如果设置了max_queue_size，则为异步
    if (max_queue_size >= 1)
    {
        //设置写入方式flag
        m_is_async = true;
        //创建并设置阻塞队列长度
        m_log_queue = new block_queue<string>(max_queue_size);
        pthread_t tid;
        // flush_log_thread为回调函数，这里表示创建线程异步写日志
        pthread_create(&tid, NULL, flush_log_thread, NULL);
    }
    //成员变量赋值
    m_close_log = close_log;
    //输出内容的长度
    m_log_buf_size = log_buf_size;
    m_buf = new char[m_log_buf_size];
    memset(m_buf, '\0', m_log_buf_size);
    //日志的最大行数
    m_split_lines = split_lines;

    time_t t = time(NULL);
    tm *sys_tm = localtime(&t);
    tm my_tm = *sys_tm;

    // XXX:查看file_name的全部字符串
    // cout << "file_name: " << file_name << endl;
    // strrchr在str字符串中搜索最后一次出现字符c的位置,并返回该位置之后的字符串
    const char *p = strrchr(file_name, '/');
    char log_full_name[256] = {0};

    //相当于自定义日志名
    //若输入的文件名没有/，则直接将时间+文件名作为日志名
    if (p == NULL)
    {
        /*
        int snprintf(char *str, size_t size, const char *format, ...)
        设将可变参数(...)按照 format 格式化成字符串，并将字符串复制到 str 中，size 为要写入的字符的最大数目，超过 size 会被截断。
        */
        snprintf(log_full_name, 255, "%s%d_%02d_%02d_%s",
                 dir_name, my_tm.tm_year + 1900, my_tm.tm_mon + 1, my_tm.tm_mday, log_name);
    }
    else
    {
        //将/的位置向后移动一个位置，然后复制到logname中
        // p - file_name + 1是文件所在路径文件夹的长度
        // dirname相当于./
        strcpy(log_name, p + 1);
        strncpy(dir_name, file_name, p - file_name + 1);
        //后面的参数与format有关
        snprintf(log_full_name, 255, "%s%d_%02d_%02d_%s", dir_name, my_tm.tm_year + 1900, my_tm.tm_mon + 1, my_tm.tm_mday, log_name);
    }
    m_today = my_tm.tm_mday;

    //以追加的方式写入文件，如果文件不存在则创建文件
    m_fp = fopen(log_full_name, "a");
    if (m_fp == NULL)
    {
        return false;
    }
    return true;
}

void Log::write_log(int level, const char *format, ...)
{
    timeval now = {0, 0};
    gettimeofday(&now, NULL);
    time_t t = now.tv_sec;
    tm *sys_tm = localtime(&t);
    tm my_tm = *sys_tm;
    char s[16] = {0};
    switch (level)
    {
    case 0:
        strcpy(s, "[debug]:");
        break;
    case 1:
        strcpy(s, "[info]:");
        break;
    case 2:
        strcpy(s, "[warn]:");
        break;
    case 3:
        strcpy(s, "[erro]:");
        break;
    default:
        strcpy(s, "[info]:");
        break;
    }
    //写入一个log，对m_count++，m_split_lines最大行数
    m_mutex.lock();
    //更新现有行数
    m_count++;
    //如果不是当天的日志或者记录的日志行数为最大日志行数的倍数
    if (m_today != my_tm.tm_mday || m_count % m_split_lines == 0)
    {
        char new_log[256] = {0};
        //将m_fp缓存区文件写入文件
        fflush(m_fp);
        fclose(m_fp);
        char tail[16] = {0};
        // 格式化日志名中的时间部分格式：年月日
        snprintf(tail, 16, "%d_%02d_%02d_", my_tm.tm_year + 1900, my_tm.tm_mon + 1, my_tm.tm_mday);
        //如果不是当天日志，则创建今天的日志，更新m_today和m_count
        if (m_today != my_tm.tm_mday)
        {
            snprintf(new_log, 255, "%s%s%s", dir_name, tail, log_name);
            m_today = my_tm.tm_mday;
            m_count = 0;
        }
        else
        {
            //超过了最大行，在之前的日志名基础上加上后缀，m_count/m_split_lines
            snprintf(new_log, 255, "%s%s%s.%lld", dir_name, tail, log_name, m_count / m_split_lines);
        }
        m_fp = fopen(new_log, "a");
    }
    m_mutex.unlock();

    //解析可变参数
    va_list valst;
    /*
    void va_start(va_list ap, last_arg) 初始化 ap 变量，
    它与 va_arg 和 va_end 宏是一起使用的。last_arg 是最后一个传递给函数的已知的固定参数，即省略号之前的参数。
    */
    //将传入的format参数赋值给valst，便于格式化输出
    va_start(valst, format);

    string log_str;
    m_mutex.lock();

    //写入的具体时间内容格式：时间+内容
    /*
    int snprintf(char *str, size_t size, const char *format, ...) 设将可变参数(...)按照 format 格式化成字符串，
    并将字符串复制到 str 中，size 为要写入的字符的最大数目，超过 size 会被截断。
    成功返回写字符的总数，其中不包括结尾的NULL字符
    */
    int n = snprintf(m_buf, 48, "%d-%02d-%02d %02d:%02d:%02d.%06ld %s ",
                     my_tm.tm_year + 1900, my_tm.tm_mon + 1, my_tm.tm_mday,
                     my_tm.tm_hour, my_tm.tm_min, my_tm.tm_sec, now.tv_usec, s);
    /*
    int vsnprintf (char * s, size_t n, const char * format, va_list arg );
    将格式化的数据从变量参数列表写入大小已设置的缓冲区
    s：指向存储结果缓冲区的指针
    n：缓冲区要使用的最大字节数
    format：格式
    arg：可变参数
    */
    //内容格式化，用于向字符串中打印数据、数据格式用户自定义，返回写入到字符数组str中的字符个数(不包含终止符)
    int m = vsnprintf(m_buf + n, m_log_buf_size - 1, format, valst);
    m_buf[n + m] = '\n';
    m_buf[n + m + 1] = '\0';
    // XXX:查看log_str字符串
    log_str = m_buf;

    m_mutex.unlock();
    //若异步，则将日志信息加入阻塞队列，同步则加锁向文件中写
    if (m_is_async && !m_log_queue->full())
    {
        m_log_queue->push(log_str);
    }
    else
    {
        m_mutex.lock();
        fputs(log_str.c_str(), m_fp);
        m_mutex.unlock();
    }

    va_end(valst);
}

void Log::flush(void)
{
    m_mutex.lock();
    //强制刷新写入流缓冲区,将缓冲区内容输出至文件
    fflush(m_fp);
    m_mutex.unlock();
}