#ifndef LOCKER_H
#define LOCKER_H
#include<pthread.h>
#include<exception>
#include<semaphore.h>
//线程同步机制封装类
/*
三种类的对比：https://www.cnblogs.com/549294286/p/3687678.html
用来同步一个进程中过的各个线程
互斥锁：用于保护临界区，以保护任何时刻只有一个线程在执行其中的代码
条件变量：发送信号与等待信号。互斥锁用户上锁，条件变量则用于等待。

信号量：提供不同进程间或线程间同步，由内核来维护，和互斥锁+条件变量类似
*/
//互斥锁类
class locker{
public:
    locker(){
        //创建默认属性的互斥锁(即快速互斥锁)
        //初始化成功返回0，出现错误返回非0值
        if(pthread_mutex_init(&m_mutex,NULL)!=0){
            throw std::exception();
        }
    }
    ~locker(){
        pthread_mutex_destroy(&m_mutex);
    }
    bool lock(){
        return pthread_mutex_lock(&m_mutex)==0;
    }
    bool unlock(){
        return pthread_mutex_unlock(&m_mutex)==0;
    }
    pthread_mutex_t *get(){
        return &m_mutex;
    }
private:
    pthread_mutex_t m_mutex;
};

//条件变量类
//理解：类似于信号，通知其它线程进行某些操作
class cond{
public:
    cond(){
        if(pthread_cond_init(&m_cond,NULL)!=0)
        {
            throw std::exception();
        }
    }
    ~cond(){
        pthread_cond_destroy(&m_cond);
    }

    //等待一个条件变量
    bool wait(pthread_mutex_t *mutex){
        return pthread_cond_wait(&m_cond,mutex)==0;
    }
    //等待一个条件变量，等待条件变量的同时可以设置超时
    bool timedwait(pthread_mutex_t *mutex,struct timespec t){
        return pthread_cond_timedwait(&m_cond,mutex,&t)==0;
    }
    //一个或多个唤醒
    bool signal(pthread_cond_t *mutex){
        return pthread_cond_signal(&m_cond)==0;
    }
    //所有唤醒
    bool broadcast(){
        return pthread_cond_broadcast(&m_cond)==0;
    }
private:
    pthread_cond_t m_cond;
};

//信号量类
/*
信号量和互斥锁(mutex)的区别：互斥锁只允许一个线程进入临界区，而信号量允许多个线程同时进入临界区。

信号量只能进行两种操作等待和发送信号，即P(sv)和V(sv),初始化时为1表示有1个可用资源，步骤如下：
P(sv)：如果sv的值大于零，就给它减1；如果它的值为零，就挂起该进程的执行
V(sv)：如果有其他进程因等待sv而被挂起，就让它恢复运行，如果没有进程因等待sv而挂起，就给它加1.
*/
class sem{
public:
    sem(){
        /*
        extern int sem_init __P ((sem_t *__sem, int __pshared, unsigned int __value));
        pshared不为０时此信号量在进程间共享，否则只能为当前进程的所有线程共享
        value给出了信号的初始值
        */
        if(sem_init(&m_sem,0,0)!=0)
        {
            throw std::exception();
        }
    }
    sem(int num){
        if(sem_init(&m_sem,0,num)!=0)
            throw std::exception();
    }
    ~sem(){
        sem_destroy(&m_sem);
    }
    bool wait(){
        return sem_wait(&m_sem)==0;
    }
    bool post(){
        return sem_post(&m_sem)==0;
    }
    
private:
    sem_t m_sem;
};

#endif