/*
  filename: threadpool.h
  半同步/半反应堆并发模式的线程池
  使用了一个工作线程完全解除了主线程和工作线程的耦合关系：
  主线程往工作队列中插入任务，工作线程通过竞争来取得任务并执行它
  必须保证所有客户请求都是无状态的，因为同一个连接上的不同请求可能会由不同的线程处理
*/
#ifndef THREADPOOL_H
#define THREADPOOL_H

#include <list>
#include <cstdio>
#include <exception>
#include <pthread.h>
#include "locker.h"

template< typename T >
class threadpool
{
public:
    /*
    thread_number：线程池中线程的数量
    max_requests：请求队列中最多允许的、等待处理的请求的数量
    */
    threadpool( int thread_number = 8, int max_requests = 10000 );
    ~threadpool();
    //往请求队列中添加队列
    bool append( T* request );

private:
    //工作线程运行的函数，它不断从工作队列中取出任务并执行
    static void* worker( void* arg );
    void run();

private:
    //线程池中的线程数
    int m_thread_number;
    //请求队列中允许的最大请求数
    int m_max_requests;
    //描述线程池的数组，大小为m_thread_number
    pthread_t* m_threads;
    //请求队列
    std::list< T* > m_workqueue;
    //保护请求队列的互斥锁
    locker m_queuelocker;
    //是否有请求队列的互斥锁
    sem m_queuestat;
    //结束线程的标识符
    bool m_stop;
};

template< typename T >
threadpool< T >::threadpool( int thread_number, int max_requests ) : 
        m_thread_number( thread_number ), m_max_requests( max_requests ), m_stop( false ), m_threads( NULL )
{
    if( ( thread_number <= 0 ) || ( max_requests <= 0 ) )
    {
        throw std::exception();
    }

    m_threads = new pthread_t[ m_thread_number ];
    if( ! m_threads )
    {
        throw std::exception();
    }

    for ( int i = 0; i < thread_number; ++i )
    {
        printf( "create the %dth thread\n", i );
        /*
        静态函数中使用类的动态成员方式：
        方式一：通过类的静态对象来调用。比如单体模式中，静态函数可以通过类的全局唯一实例来访问动态成员函数
        方式二：将类的对象作为参数传递给该静态函数，然后在静态函数中引用这个对象，并调用其动态方法

        本代码采用方式二：将线程参数设置为this指针，然后在worker函数中获取该指针并调用其动态方法run
        */
        //创建线程失败
        if( pthread_create( m_threads + i, NULL, worker, this ) != 0 )
        {
            delete [] m_threads;
            throw std::exception();
        }
        //分离线程
        if( pthread_detach( m_threads[i] ) )
        {
            delete [] m_threads;
            throw std::exception();
        }
    }
}

template< typename T >
threadpool< T >::~threadpool()
{
    delete [] m_threads;
    m_stop = true;
}

template< typename T >
bool threadpool< T >::append( T* request )
{
    //操作工作队列一定要加锁，因为它被所有线程共享
    m_queuelocker.lock();
    if ( m_workqueue.size() > m_max_requests )
    {
        m_queuelocker.unlock();
        return false;
    }
    m_workqueue.push_back( request );
    m_queuelocker.unlock();
    m_queuestat.post();
    return true;
}

template< typename T >
void* threadpool< T >::worker( void* arg )
{
    threadpool* pool = ( threadpool* )arg;
    pool->run();
    return pool;
}

template< typename T >
void threadpool< T >::run()
{
    while ( ! m_stop )
    {
        m_queuestat.wait();
        m_queuelocker.lock();
        if ( m_workqueue.empty() )
        {
            m_queuelocker.unlock();
            continue;
        }
        T* request = m_workqueue.front();
        m_workqueue.pop_front();
        m_queuelocker.unlock();
        if ( ! request )
        {
            continue;
        }
        request->process();
    }
}

#endif
