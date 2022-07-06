/*************************************************************
循环数组实现的阻塞队列，m_back = (m_back + 1) % m_max_size;
线程安全，每个操作前都要先加互斥锁，操作完后，再解锁
该队列的使用的是生产者消费者模型。
**************************************************************/

#ifndef BLOCK_QUEUE_H
#define BLOCK_QUEUE_H
#include "../lock/locker.h"
template <class T>
class block_queue
{
public:
    //初始化私有成员
    block_queue(int max_size = 1000)
    {
        if (max_size <= 0) exit(-1);
        //构造函数创建循环数组
        m_max_size = max_size;
        m_array = new T[max_size];
        m_size = 0;
        m_front = -1;
        m_back = -1;
    }
    ~block_queue()
    {
        m_mutex.lock();
        if (m_array)
            delete[] m_array;
        m_mutex.unlock();
    }
    void clear()
    {
        m_mutex.lock();
        m_size = 0;
        m_front = -1;
        m_back = -1;
        m_mutex.unlock();
    }
    //判断队列是否满了
    bool full()
    {
        m_mutex.lock();
        if (m_size >= m_max_size)
        {
            m_mutex.unlock();
            return true;
        }
        m_mutex.unlock();
        return false;
    }
    //判断队列是否为空
    bool empty()
    {
        m_mutex.lock();
        if (0 == m_size)
        {
            m_mutex.unlock();
            return true;
        }
        m_mutex.unlock();
        return false;
    }
    //返回队首元素
    bool front(T &value)
    {
        m_mutex.lock();
        if (0 == m_size)
        {
            m_mutex.unlock();
            return false;
        }
        value = m_array[m_front];
        m_mutex.unlock();
        return true;
    }
    //返回队尾元素
    bool back(T &value)
    {
        m_mutex.lock();
        if (0 == m_size)
        {
            m_mutex.lock();
            return false;
        }
        value = m_array[m_back];
        m_mutex.unlock();
        return true;
    }
    //返回队列大小
    int size()
    {
        m_mutex.lock();
        int res = m_size;
        m_mutex.unlock();
        return res;
    }
    //返回队列最大大小
    int max_size()
    {
        m_mutex.lock();
        int res = m_max_size;
        m_mutex.unlock();
        return res;
    }
    /*
    往队列添加元素，需要将所有使用队列的线程先唤醒
    当有元素push进入队列，相当于生产者生产了一个元素
    若当前没有线程等待条件变量，则唤醒无意义
    */
    bool push(const T &item)
    {
        m_mutex.lock();
        if (m_size >= m_max_size)
        {
            m_cond.broadcast();
            m_mutex.unlock();
            return false;
        }
        //将新增数据放在循环数组的对应位置
        m_back = (m_back + 1) % m_max_size;
        m_array[m_back] = item;

        m_size++;

        m_cond.broadcast();
        m_mutex.unlock();
        return true;
    }
    // pop时，如果当前队列没有元素，将会等待条件变量，同时item将指向下一位的数据
    bool pop(T &item)
    {
        m_mutex.lock();
        //多个消费者的时候，这里要使用while循环而不是if
        while (m_size <= 0)
        {
            //当重新抢到互斥锁，pthread_cond_wait返回0
            if (!m_cond.wait(m_mutex.get()))
            {
                m_mutex.unlock();
                return false;
            }
        }
        if (m_size <= 0)
        {
            m_mutex.unlock();
            return false;
        }
        //取出队列首的元素，使用循环数组模拟队列
        m_front = (m_front + 1) % m_max_size;
        item = m_array[m_front];
        m_size--;
        m_mutex.unlock();
        return true;
    }
    /*
    新增超时处理，目前项目没有使用到
    在pthread_cond_wait基础上增加了等待的时间，只要在指定时间内抢到互斥锁即可
    其它逻辑不变
    */
    bool pop(T &item, int ms_timeout)
    {
        timespec t={0,0};
        /*
        struct timespec{
            time_t tv_sec;//秒
            long tv_nsec;//纳秒
        };
        一般使用clock_gettime(clockid_t, struct timespec*)
        */
        timeval now={0,0};
        /*
        struct timeval{
            long tv_sec;//秒
            long tv_usec;//微妙
        };
        一般使用gettimeofday(struct timeval *tv,struct timezone *tz)
        标准化输出时间使用：strftime(char* str,size_t maxsize,const char* format, const struct tm* timeptr)
        strftime使用示例：https://blog.csdn.net/weixin_44880138/article/details/102605681
        */
        gettimeofday(&now,NULL);
        m_mutex.lock();
        if(m_size<=0)
        {
            t.tv_sec=now.tv_sec+ms_timeout/1000;
            t.tv_nsec=(ms_timeout%1000)*1000;
            if(!m_cond.timewait(m_mutex.get(),t))
            {
                m_mutex.unlock();
                return false;
            }
        }

        if(m_size<=0)
        {
            m_mutex.unlock();
            return false;
        }

        m_front=(m_front+1)%m_max_size;
        item=m_array[m_front];
        m_size--;
        m_mutex.unlock();
        return true;
    }

private:
    locker m_mutex;
    cond m_cond;
    T *m_array;
    int m_size;
    int m_max_size;
    int m_front;
    int m_back;
};

#endif