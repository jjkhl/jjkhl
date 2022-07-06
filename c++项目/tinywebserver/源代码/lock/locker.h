/*
线程同步机制包装类
===============
多线程同步，确保任一时刻只能有一个线程能进入关键代码段.
> * 信号量
> * 互斥锁
> * 条件变量

解释参考网址：https://mp.weixin.qq.com/s?__biz=MzAxNzU2MzcwMw==&mid=2649274278&idx=3&sn=5840ff698e3f963c7855d702e842ec47&chksm=83ffbefeb48837e86fed9754986bca6db364a6fe2e2923549a378e8e5dec6e3cf732cdb198e2&scene=178&cur_album_id=1339230165934882817#rd
*/
#ifndef LOCKER_H
#define LOCKER_H
#include "../allhead.h"
/*
信号量：特殊的变量，只能取自然数值并且只支持等待(P)和信号(V)
假设有信号量SV，对其的P、V操作如下：
* P，如果SV的值大于0，则将其减一；若SV=0，则挂起执行
* V，如果有其它进行因为等待SV而被挂起，则唤醒；若没有，则将SV值加1

sem_init()函数用于初始化一个未命名的信号量
sem_destory()函数用于销毁信号量
sem_wait()函数将以原子操作方式将信号量减一，信号量为0时，sem_wait阻塞
sem_post函数以原子操作方式将信号量加一,信号量大于0时,唤醒调用sem_post的线程
以上，成功返回0，失败返回errno
*/
class sem
{
public:
    sem()
    {
        /*
        第一个0指信号量m_sem被进程内的线程共享
        第二个0指信号量的初始值
        */
        if (sem_init(&m_sem, 0, 0) != 0) //信号初始化失败
            throw std::exception();
    }
    sem(int num)
    {
        if (sem_init(&m_sem, 0, num) != 0) //信号初始化失败
            throw std::exception();
    }
    ~sem()
    {
        sem_destroy(&m_sem);
    }
    //当一个线程调用Wait操作时，它要么得到资源然后将信号量减一，要么一直等下去（指放入阻塞队列），直到信号量大于等于一时。
    bool wait()
    {
        return sem_wait(&m_sem) == 0;
    }
    //实际上是在信号量上执行加一操作，对应于车辆离开停车场，该操作之所以叫做“释放”是因为释放了由信号量守护的资源。
    bool post()
    {
        return sem_post(&m_sem) == 0;
    }

private:
    sem_t m_sem;
};

/*
互斥锁也叫互斥量，用于保护关键代码段，以确保独占式访问。
pthread_mutex_init函数用于初始化互斥锁

pthread_mutex_destory函数用于销毁互斥锁

pthread_mutex_lock函数以原子操作方式给互斥锁加锁

pthread_mutex_unlock函数以原子操作方式给互斥锁解锁

成功返回0，失败返回errno
*/
class locker
{
public:
    locker()
    {
        if (pthread_mutex_init(&m_mutex, NULL) != 0)
            throw std::exception();
    }
    ~locker()
    {
        pthread_mutex_destroy(&m_mutex);
    }
    bool lock()
    {
        return pthread_mutex_lock(&m_mutex) == 0;
    }
    bool unlock()
    {
        return pthread_mutex_unlock(&m_mutex) == 0;
    }
    //指针函数，返回互斥锁地址
    pthread_mutex_t *get()
    {
        return &m_mutex;
    }

private:
    pthread_mutex_t m_mutex;
};

/*
使用参考网址：http://t.csdn.cn/qOqgb
条件变量：提供了一种线程间的通知机制,当某个共享数据达到某个值时,唤醒等待这个共享数据的线程.
主要包括两个动作：
1. 一个线程因等待“条件变量成立”
2. 另外一个线程使“条件成立”，给出信号，从而唤醒正在等待的线程

pthread_cond_init函数用于初始化条件变量

pthread_cond_destory函数销毁条件变量

pthread_cond_broadcast函数以广播的方式唤醒所有等待目标条件变量的线程

pthread_cond_wait函数用于等待目标条件变量.该函数调用时需要传入 mutex参数(加锁的互斥锁) ,
函数执行时,先把调用线程放入条件变量的请求队列,然后将互斥锁mutex解锁,
当函数成功返回为0时,互斥锁会再次被锁上. 也就是说函数内部会有一次解锁和加锁操作.

*/
class cond
{
public:
    cond()
    {
        if (pthread_cond_init(&m_cond, NULL) != 0)
            throw std::exception();
    }
    ~cond()
    {
        pthread_cond_destroy(&m_cond);
    }
    bool wait(pthread_mutex_t *mutex)
    {
        int ret = 0;
        pthread_mutex_lock(mutex);
        /*
        pthread_cond_wait() 用于阻塞当前线程，等待别的线程使用pthread_cond_signal()或pthread_cond_broadcast来唤醒它。
        pthread_cond_wait()函数一进入wait状态就会自动release mutex。
        当其他线程通过pthread_cond_signal()或pthread_cond_broadcast，把该线程唤醒，使pthread_cond_wait()通过（返回）时，该线程又自动获得该mutex。
        经典的生产者消费者模型。
        */
        ret = pthread_cond_wait(&m_cond, mutex);
        pthread_mutex_unlock(mutex);
        return 0 == ret;
    }
    bool timewait(pthread_mutex_t *m_mutex, struct timespec t)
    {
        int ret = 0;
        pthread_mutex_lock(m_mutex);
        /*
        struct timespec {
            time_t tv_sec; // seconds
            long tv_nsec; // and nanoseconds
        };
        */
        ret = pthread_cond_timedwait(&m_cond, m_mutex, &t);
        pthread_mutex_unlock(m_mutex);
        return ret == 0;
    }
    //发送一个信号给另外一个正在处于阻塞等待状态的线程,使其脱离阻塞状态,继续执行
    bool signal()
    {
        return pthread_cond_signal(&m_cond) == 0;
    }
    /*
    使用参考思路：https://www.cnblogs.com/zhouzhuo/p/3781511.html
    唤醒所有被阻塞的线程
    */
    bool broadcast()
    {
        return pthread_cond_broadcast(&m_cond) == 0;
    }

private:
    pthread_cond_t m_cond;
};
#endif
