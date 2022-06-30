**参考网址：**
[官方项目详解](https://mp.weixin.qq.com/mp/appmsgalbum?__biz=MzAxNzU2MzcwMw==&action=getalbum&album_id=1339230165934882817&scene=173&from_msgid=2649274278&from_itemidx=3&count=3&nolastread=1#wechat_redirect)
[Web服务器](https://blog.csdn.net/qq_38872537/article/details/113184114)
[WebServer项目详解](https://www.agedcat.com/programming_language/cpp/537.html)


# [01线程同步机制封装类](https://mp.weixin.qq.com/s?__biz=MzAxNzU2MzcwMw==&mid=2649274278&idx=3&sn=5840ff698e3f963c7855d702e842ec47&scene=19#wechat_redirect)
文件位置：`lock/locker.h`
## RAII
* 全称：Resource Acquisition is Initialization,中文称为资源获取即初始化
* 在构造函数中申请分配资源，在析构函数中释放资源。因为C++的语言机制保证了，当一个对象创建的时候，自动调用构造函数，当对象超出作用域的时候会自动调用析构函数。所以，在RAII的指导下，我们应该使用类来管理资源，将资源和对象的生命周期绑定
* 核心思想：将资源或者状态与对象的生命周期绑定，通过C++的语言机制，实现资源和状态的安全管理，智能指针就是RAII最好的例子。

## 信号量(sem)
信号量：特殊的变量，只能取自然数值并且只支持等待(P)和信号(V)
假设有信号量SV，对其的P、V操作如下：
* P，如果SV的值大于0，则将其减一；若SV=0，则挂起执行
* V，如果有其它进行因为等待SV而被挂起，则唤醒；若没有，则将SV值加1

sem_init()函数用于初始化一个未命名的信号量
sem_destory()函数用于销毁信号量
sem_wait()函数将以原子操作方式将信号量减一，信号量为0时，sem_wait阻塞
sem_post函数以原子操作方式将信号量加一,信号量大于0时,唤醒调用sem_post的线程
以上，成功返回0，失败返回errno

## 互斥锁(locker)
互斥锁也叫互斥量，用于保护关键代码段，以确保独占式访问。

pthread_mutex_init函数用于初始化互斥锁
pthread_mutex_destory函数用于销毁互斥锁
pthread_mutex_lock函数以原子操作方式给互斥锁加锁
pthread_mutex_unlock函数以原子操作方式给互斥锁解锁

成功返回0，失败返回errno

## 条件变量(cond)
cond参考网址：http://t.csdn.cn/qOqgb

条件变量：提供了一种线程间的通知机制,当某个共享数据达到某个值时,唤醒等待这个共享数据的线程.
主要包括两个动作：
1. 一个线程因等待“条件变量成立”
2. 另外一个线程使“条件成立”，给出信号，从而唤醒正在等待的线程

pthread_cond_init函数用于初始化条件变量
pthread_cond_destory函数销毁条件变量
[pthread_cond_broadcast函数](https://www.cnblogs.com/zhouzhuo/p/3781511.html)以广播的方式唤醒所有等待目标条件变量的线程
pthread_cond_wait函数用于等待目标条件变量.该函数调用时需要传入 mutex参数(加锁的互斥锁) ,函数执行时,先把调用线程放入条件变量的请求队列,然后将互斥锁mutex解锁,当函数成功返回为0时,互斥锁会再次被锁上. 也就是说函数内部会有一次解锁。加锁操作.
pthread_cond_timedwait比pthread_cond_wait多个时间结构`struct timespec t`

## [时间结构](https://blog.csdn.net/weixin_44880138/article/details/102605681)
```c++
#include<time.h>
struct timespec {
    time_t tv_sec; // seconds
    long tv_nsec; // and nanoseconds
};

struct timeval {
   time_t tv_sec; // seconds
   long tv_usec; // microseconds
};

struct timezone{
   int tz_minuteswest; //miniutes west of Greenwich
   int tz_dsttime; //type of DST correction
};

```

# [02.半同步半反应堆线程池上](https://mp.weixin.qq.com/s?__biz=MzAxNzU2MzcwMw==&mid=2649274278&idx=4&sn=caa323faf0c51d882453c0e0c6a62282&chksm=83ffbefeb48837e841a6dbff292217475d9075e91cbe14042ad6e55b87437dcd01e6d9219e7d&cur_album_id=1339230165934882817&scene=189#wechat_redirect)

##  服务器编程基本框架

```mermaid
graph LR;
id1(I/O处理单元)--请求队列---id2(多个逻辑单元)
id2--请求队列---id3(网络存储单元)
```

## 五种I/O模型
* **阻塞IO**:调用者调用了某个函数，等待这个函数返回，期间什么也不做，不停的去检查这个函数有没有返回，必须等这个函数返回才能进行下一步动作
* **非阻塞IO**:非阻塞等待，每隔一段时间就去检测IO事件是否就绪。没有就绪就可以做其他事。非阻塞I/O执行系统调用总是立即返回，不管时间是否已经发生，若时间没有发生，则返回-1，此时可以根据errno区分这两种情况，对于accept，recv和send，事件未发生时，errno通常被设置成eagain
* **信号驱动IO**:linux用套接口进行信号驱动IO，安装一个信号处理函数，进程继续运行并不阻塞，当IO时间就绪，进程收到SIGIO信号。然后处理IO事件。
* **IO复用**:linux用select/poll函数实现IO复用模型，这两个函数也会使进程阻塞，但是和阻塞IO所不同的是这两个函数可以同时阻塞多个IO操作。而且可以同时对多个读操作、写操作的IO函数进行检测。知道有数据可读或可写时，才真正调用IO操作函数
* **异步IO**:linux中，可以调用aio_read函数告诉内核描述字缓冲区指针和缓冲区的大小、文件偏移及通知的方式，然后立即返回，当内核将数据拷贝到缓冲区后，再通知应用程序。

> 注意：阻塞I/O，非阻塞I/O，信号驱动I/O和I/O复用都是同步I/O。同步I/O指内核向应用程序通知的是就绪事件，比如只通知有客户端连接，要求用户代码自行执行I/O操作，异步I/O是指内核向应用程序通知的是完成事件，比如读取客户端的数据后才通知应用程序，由内核完成I/O操作。

[同步I/O和异步I/O区别](https://www.jianshu.com/p/d7d33d7396ef)
同步I/O特点：
1、同步 io 是用户线程发起 io 请求并以阻塞或轮询的方式来等待 io 的完成
2、同步 io 是 io 的发起方，同时也是处理方
3、同步 io 是需要将内核态准备就绪的数据拷贝到用户态，所以需要阻塞用户态程序并等待 io 完成

异步I/O特点：
1、异步 io 在用户线程发起 io 请求后会立即返回继续执行后续的逻辑流
2、异步 io 是 io 的发起方，但内核态才是处理方
3、异步 io 的处理方是内核态，所以不需要阻塞

## 事件处理模式
reactor模式中，主线程(I/O处理单元)只负责监听文件描述符上是否有事件发生，有的话立即通知工作线程(逻辑单元 )，读写数据、接受新连接及处理客户请求均在工作线程中完成。通常由同步I/O实现。

proactor模式中，主线程和内核负责处理读写数据、接受新连接等I/O操作，工作线程仅负责业务逻辑，如处理客户请求。通常由异步I/O实现。


Reactor和Proactor的理解：https://www.zhihu.com/question/26943938
1.Reactor是非阻塞同步，理解为来了事件操作系统通知应用进程，让应用进程来处理
2.Proactor是异步网络模式，理解为来了事件操作系统来处理，处理完再通知应用进程

并发模式的同步和异步：
* 同步：程序完全按照代码序列的顺序执行
* 异步：程序的执行需要系统事件驱动

半同步/半反应堆是半同步/半异步的变体，将半异步具体化为某种事件处理模式。
半同步/半异步模式工作流程
* 同步线程用于处理客户逻辑
* 异步线程用于处理I/O事件
* 异步线程监听到客户请求后，就将其封装成请求对象并插入请求队列中
* 请求队列将通知某个工作在同步模式的工作线程来读取并处理该请求对象

半同步/半反应堆工作流程（以Proactor模式为例:
* 主线程充当异步线程，负责监听所有socket上的事件

* 若有新请求到来，主线程接收之以得到新的连接socket，然后往epoll内核事件表中注册该socket上的读写事件

* 如果连接socket上有读写事件发生，主线程从socket上接收数据，并将数据封装成请求对象插入到请求队列中

* 所有工作线程睡眠在请求队列上，当有任务到来时，通过竞争（如互斥锁）获得任务的接管权

## 线程池
* 空间换事件，浪费服务器硬件资源，换取运行效率
* 池是一组资源的集合,这组资源在服务器启动之初就被完全创建好并初始化,这称为静态资源.
* 当服务器进入正式运行阶段,开始处理客户请求的时候,如果它需要相关的资源,可以直接从池中获取,无需动态分配.
* 当服务器处理完一个客户连接后,可以把相关的资源放回池中,无需执行系统调用释放资源.

# [03.半同步版反应堆线程池(下)](https://mp.weixin.qq.com/s?__biz=MzAxNzU2MzcwMw==&mid=2649274278&idx=5&sn=87470bb3ade0150bb94fcbf33c43c2f8&chksm=83ffbefeb48837e843cfc8258248a1e1b69b48ed993c51861ec63e3b0541fa4714a3846adf90&cur_album_id=1339230165934882817&scene=189#wechat_redirect)

## 静态成员变量
将类成员变量声明为static，则为静态成员变量，与一般的成员变量不同，无论建立多少对象，都只有一个静态成员变量的拷贝，静态成员变量属于一个类，所有对象共享。

静态变量在编译阶段就分配了空间，对象还没创建时就已经分配了空间，放到全局静态区。

静态成员变量
* 最好是类内声明，类外初始化（以免类名访问静态成员访问不到）。
* 无论公有，私有，静态成员都可以在类外定义，但私有成员仍有访问权限。
* 非静态成员类外不能初始化。
* 静态成员数据是共享的。

## 静态成员函数
将类成员函数声明为static，则为静态成员函数

* 静态成员函数可以直接访问静态成员变量，不能直接访问普通成员变量，但可以通过参数传递的方式访问
* 普通成员函数可以访问普通成员变量，也可以访问静态成员变量。

* 静态成员函数没有this指针。非静态数据成员为对象单独维护，但静态成员函数为共享函数，无法区分是哪个对象，因此不能直接访问普通变量成员，也没有this指针。

## pthread_create陷阱
函数原型：
```c++
#include<pthread.h>
int pthread_create(pthread_t *thread_id,           //返回新生成的线程id
                   const pthread_attr_t &attr,     //指向线程属性的指针，默认NULL
                   void* (*start_routine) (void*), //处理线程函数的地址
                   void *arg);                     //start_routine()中的参数
```
函数原型中的第三个参数，为函数指针，指向处理线程函数的地址。该函数，要求为静态函数。如果处理线程函数为类成员函数时，需要将其设置为静态成员函数。

pthread_create的函数原型中第三个参数的类型为函数指针，指向的线程处理函数参数类型为(void *),若线程函数为类成员函数，则this指针会作为默认的参数被传进函数中，从而和线程函数参数(void*)不能匹配，不能通过编译。

静态成员函数就没有这个问题，里面没有this指针。

## 线程池分析
线程池的设计模式为半同步/半反应堆，其中反应堆具体为Proactor事件处理模式。

具体的，主线程为异步线程，负责监听文件描述符，接收socket新连接，若当前监听的socket发生了读写事件，然后将任务插入到请求队列。工作线程从请求队列中取出任务，完成读写数据的处理。

* 线程处理函数`static void* worker(void *arg)`和运行函数`void run()`设置为私有属性，

* **线程池创建与回收**：构造函数中创建线程池,pthread_create函数中将类的对象作为参数传递给静态函数(worker),在静态函数中引用这个对象,并调用其动态方法(run)。具体的，类对象传递时用this指针，传递给静态函数后，将其转换为线程池类，并调用私有成员函数run。

* **向请求队列中添加任务**：通过list容器创建请求队列，向队列中添加时，通过互斥锁保证线程安全，添加完成后通过信号量提醒有任务要处理，最后注意线程同步。

线程处理函数：
```c++
template <typename T>
void *threadpool<T>::worker(void *arg)
{
    //将参数强转为线程池类，调用成员方法
    threadpool *pool = (threadpool *)arg;
    pool->run();
    return pool;
}
```

run执行任务：主要实现工作线程从请求队列中取出某个任务进行处理，注意线程同步

# [04.http连接处理(上)](https://mp.weixin.qq.com/s?__biz=MzAxNzU2MzcwMw==&mid=2649274278&idx=6&sn=b0a34b4f59f28b0619dcc72f3fcc2243&chksm=83ffbefeb48837e8ae419ae1cbf61b112f24378c6db96a943c5f6671b1e4ab16ea83b4302a1e&cur_album_id=1339230165934882817&scene=189#wechat_redirect)
主要内容：梳理基础知识，结合代码分析http类及请求接收
## epoll
epoll_create函数：创建一个指示epoll内核事件表的文件描述符，该描述符将用作其他epoll系统调用的第一个参数，size不起作用。
```c++
#include<sys/epoll.h>
int epoll_create(int size)

struct epoll_event {
   __uint32_t events; /* Epoll events */
   epoll_data_t data; /* User data variable */
};
```

epoll_ctl函数：该函数用于操作内核事件表监控的文件描述符上的事件：注册、修改、删除。
```c++
#include<sys/epoll.h>
int epoll_ctl(int epfd, int op, int fd, struct epoll_event* event);
```
* epfd：为epoll_create的句柄
* op：表示动作，用3个宏表示
  * EPOLL_CTL_ADD：注册新的fd到epfd
  * EPOLL_CTL_MOD：修改已经注册的fd的监听事件
  * EPOLL_CTL_DEL：从epfd删除一个fd
* event：告诉内核需要监听的事件
* events描述描述事件类型：
  * EPOLLIN：表示对应的文件描述符可读(包括对端SOCKET正常关闭)
  * EPOLLOUT：表示对应文件描述符可写
  * EPOLLRDHUP：表示对端断开连接
  * EPOLLPRI：表示对应的文件描述符有紧急的数据可读（这里应该表示有带外数据到来）
  * EPOLLERR：表示对应的文件描述符发生错误
  * EPOLLHUP：表示对应的文件描述符被挂断；
  * EPOLLET：将EPOLL设为边缘触发(Edge Triggered)模式，这是相对于水平触发(Level Triggered)而言的
  * EPOLLONESHOT：只监听一次事件，当监听完这次事件之后，如果还需要继续监听这个socket的话，需要再次把这个socket加入到EPOLL队列里

epoll_wait函数：用于等待所监控文件描述符上有事件的产生，返回就绪的文件描述符个数
```c++
#include<sys/epoll.h>
int epoll_wait(int epfd, struct epoll_event *events, int maxevents, int timeout)
```
* events：用来存内核得到事件的集合，

* maxevents：告之内核这个events有多大，这个maxevents的值不能大于创建epoll_create()时的size，

* timeout：是超时时间

  * -1：阻塞

  * 0：立即返回，非阻塞

  * `>0`：指定毫秒

* 返回值：成功返回有多少文件描述符就绪，时间到时返回0，出错返回-1

## select/poll/epoll
* **调用函数**
  * select和poll是一个函数，epoll是一组函数
* **文件描述符数量**
  * select通过线性表描述文件描述符集合，文件描述符有上限，一般为1024。
  * poll是链表描述，突破了文件描述符上限，最大可以打开文件的数目
  * epoll通过红黑树，最大可以打开文件的数目，可以通过命令`ulimit -n number`修改，仅对当前终端有效
* **将文件描述符从用户传到内核**
  * select和poll通过将所有文件描述符拷贝到内核态，每次调用都需要拷贝
  * epoll通过epoll_create建立一棵红黑树，通过epoll_ctl将要监听的文件描述符注册到红黑树上
* **内核判断就绪的文件描述符**
  * select和poll通过遍历文件描述符集合，判断哪个文件描述符上有事件发生
  * epoll_create时，内核除了在epoll文件系统里建立红黑树用于存储以后epoll_ctl传来的fd外，还会再建立一个list链表，用于存储准备就绪的事件，但epoll_wait调用时，仅仅观察这个list链表里有没有数据即可
  * epoll是根据每个fd上面的回调函数(中断函数)判断，只有发生了事件的socket才会主动调用callback函数，其它空闲状态socket则不会，若是就绪事件，插入list
* **应用程序索引就绪文件描述符**
  * select/poll只返回发生了事件的文件描述符个数，若需要知道哪个发生了事件，同样需要遍历
  * epoll返回的是发生了事件的个数和结构体数组，结构体包含socket信息，因此直接处理返回的数组即可
* 工作模式
  * select和poll都只能工作在相对低效的LT模式下
  * epoll则可以工作在ET高效模式，并且epoll还支持EPOLLONESHOT事件，该事件能进一步减少可读、可写和异常事件被触发的次数。
* 应用场景
  * 当所有的fd都是活跃连接，使用epoll。需要建立文件系统，红黑树和链表对于此来说，效率反而不高，不如selece和poll
  * 当监测的fd数目较小，且各个fd都比较活跃，建议使用select或者poll
  * 当监测的fd数目非常大，成千上万，且单位时间只有其中的一部分fd处于就绪状态，这个时候使用epoll能够明显提升性能

## ET、LT和EPOLLONESHOT
参考网址：https://blog.csdn.net/liuhengxiao/article/details/46911129
* LT水平触发模式
  * epoll_wait检测到文件描述符有事件发生，则将其通知给应用程序，应用程序可以不立即处理该事件
  * 当下一次调用epoll_wait时，epoll_wait还会再次向应用程序报告此事件，直至被处理
* ET边缘触发模式
  * epoll_wait检测到文件描述符有事件发生，则将其通知给应用程序，应用程序必须立即处理该事件
  * 必须要一次性将数据读取完，使用非阻塞I/O，读取到出现eagain(请再次尝试)
* EPOLLONESHOT
  * 一个线程读取某个socket上的数据后开始处理数据，在处理过程中该socket上又有新数据可读，此时另一个线程被唤醒读取，此时出现两个线程处理同一个socket
  * 我们期望的是一个socket连接在任一时刻都只被一个线程处理，通过epoll_ctl对该文件描述符注册epolloneshot事件，一个线程处理socket时，其他线程将无法处理，当该线程处理完后，需要通过epoll_ctl重置epolloneshot事件

## HTTP报文格式
浏览器端向服务器发送的为请求报文，服务器处理后返回给浏览器端的为响应报文。
### 请求报文
HTTP请求报文有请求行(request line)、请求头部(header)、空行和请求数据四个部分组成
空行：最后一个请求头之后是一个空行，发送回车符和换行符，通知服务器后续不再有请求头。
请求分为GET和POST
[GET和POST区别：](https://zhuanlan.zhihu.com/p/275695831)
1. 最直观的区别：GET把参数包含在URL中，POST通过请求体传递参数
2. POST比GET慢，因为POST请求包含更多的请求头，在其真正接收数据之前会先将请求头发送给服务器进行确认然后才真正发送数据；GET会将数据缓存，但POST不会。

面试回答：
1. POST更安全(不会作为URL的一部分，不会被缓存、保存在服务器日志，以及浏览器浏览记录中)
2. POST发送的数据更大(GET有URL长度限制)
3. POST能发送更多的数据类型(GET只能发送ASCII字符)
4. POST比GET慢
5. POST用于修改和写入数据，GET一般用于搜索排序和筛选之类的操作(淘宝、支付宝的搜索查询都是GET提交)，目的是资源的获取，读取数据。

---

请求行，用来说明请求类型,要访问的资源以及所使用的HTTP版本。
GET说明请求类型为GET，/562f25980001b1b106000338.jpg(URL)为要访问的资源，该行的最后一部分说明使用的是HTTP1.1版本。

请求头部，紧接着请求行（即第一行）之后的部分，用来说明服务器要使用的附加信息。

HOST，给出请求资源所在服务器的域名。

User-Agent，HTTP客户端程序的信息，该信息由你发出请求使用的浏览器来定义,并且在每个请求中自动发送等。

Accept，说明用户代理可处理的媒体类型。

Accept-Encoding，说明用户代理支持的内容编码。

Accept-Language，说明用户代理能够处理的自然语言集。

Content-Type，说明实现主体的媒体类型。

Content-Length，说明实现主体的大小。

Connection，连接管理，可以是Keep-Alive或close。

空行，请求头部后面的空行是必须的即使第四部分的请求数据为空，也必须有空行。

请求数据也叫主体，可以添加任意的其他数据。

---

* **GET**

```
GET /562f25980001b1b106000338.jpg HTTP/1.1
Host:img.mukewang.com
User-Agent:Mozilla/5.0 (Windows NT 10.0; WOW64)
AppleWebKit/537.36 (KHTML, like Gecko) Chrome/51.0.2704.106 Safari/537.36
Accept:image/webp,image/*,*/*;q=0.8
Referer:http://www.imooc.com/
Accept-Encoding:gzip, deflate, sdch
Accept-Language:zh-CN,zh;q=0.8
空行
请求数据
```

**典型请求头**：
* User-Agent：产生请求的浏览器类型
* Accept：客户端可识别的响应的内容类型列表，`*`用于按范围将类型分组，`*/*`表示可接收全部类型，`type/*`表示可接受type类型的所有子类型
* Accept-Language：客户端可接收的自然语言
* Accept-Encoding：客户端可接受的编码解压格式
* Accept-Charset：可接受的应答字符集
* Host：请求的主机名
* Refer：请求访问服务器的来源URL
* Connection：连接方式(close或keep-alive)
* Cookie：存储客户端扩展字段，向同一域名的服务端发送属于该域的Cookie
* If-Modified-Since：客户机通过这个头告诉服务器，资源的缓存时间。只有当所请求的内容在指定的时间后又经过修改才返回它，否则返回304“Not Modified”应答。
---

* **POST**

```
POST / HTTP1.1
Host:www.wrox.com
User-Agent:Mozilla/4.0 (compatible; MSIE 6.0; Windows NT 5.1; SV1; .NET CLR 2.0.50727; .NET CLR 3.0.04506.648; .NET CLR 3.5.21022)
Content-Type:application/x-www-form-urlencoded
Content-Length:40
Connection: Keep-Alive
空行
name=Professional%20Ajax&publisher=Wiley
```
### 响应报文
HTTP响应也由四个部分组成，分别是：状态行、消息报头、空行和响应正文。
```
HTTP/1.1 200 OK
Date: Fri, 22 May 2009 06:07:21 GMT
Content-Type: text/html; charset=UTF-8
空行
<html>
      <head></head>
      <body>
            <!--body goes here-->
      </body>
</html>
```
状态行，由HTTP协议版本号， 状态码， 状态消息 三部分组成。
第一行为状态行，（HTTP/1.1）表明HTTP版本为1.1版本，状态码为200，状态消息为OK。

消息报头，用来说明客户端要使用的一些附加信息。
第二行和第三行为消息报头，Date:生成响应的日期和时间；Content-Type:指定了MIME类型的HTML(text/html),编码类型是UTF-8。

空行，消息报头后面的空行是必须的。

响应正文，服务器返回给客户端的文本信息。空行后面的html部分为响应正文。

**HTTP状态码**
* 1XX：信息性状态码——接收的请求正在处理
* 2XX：成功状态码——请求正常处理完成
  * 200 OK：客户端请求被正常处理
  * 206 Partial content：客户端进行了范围请求
* 3XX：重定向状态码——需要进行附加操作以完成操作
  * 301 Moved Permanently：永久重定向，该资源已被永久移动到新位置，将来任何对该资源的访问都要使用本相应返回的若干个URI(URI=URL+URN)之一
  * 302 Found：临时重定向，请求的资源现在临时从不同的URI中获得
* 4XX：客户端错误状态码——服务器无法处理请求
  * 400 Bad Request：请求报文存在语法错误
  * 403 Forbidden：请求被服务器拒绝
  * 404 Not Found：请求不存在，服务器上找不到请求的资源
* 5XX：服务器错误状态码——服务器处理请求出错
  * 500 Internal Server Error：服务器在执行请求时出现错误

###  有限状态机
有限状态机，是一种抽象的理论模型，它能够把有限个变量描述的状态变化过程，以可构造可验证的方式呈现出来。比如，封闭的有向图。

有限状态机可以通过if-else,switch-case和函数指针来实现，从软件工程的角度看，主要是为了封装逻辑。

```c++
STATE_MACHINE(){
    State cur_State = type_A;
    while(cur_State != type_C){
        Package _pack = getNewPackage();
        switch(){
            case type_A:
                process_pkg_state_A(_pack);
                cur_State = type_B;
                break;
            case type_B:
                process_pkg_state_B(_pack);
                cur_State = type_C;
                break;
        }
    }
}
```
该状态机包含三种状态：type_A，type_B和type_C。其中，type_A是初始状态，type_C是结束状态。

状态机的当前状态记录在cur_State变量中，逻辑处理时，状态机先通过getNewPackage获取数据包，然后根据当前状态对数据进行处理，处理完后，状态机通过改变cur_State完成状态转移。

有限状态机一种逻辑单元内部的一种高效编程方法，在服务器编程中，服务器可以根据不同状态或者消息类型进行相应的处理逻辑，使得程序逻辑清晰易懂。

## HTTP处理流程
* HTTP报文处理流程
  * 浏览器端发出http连接请求，主线程创建http对象接收请求并将所有数据读入对应buffer，将该对象插入任务队列，工作线程从任务队列中取出一个任务进行处理。
  * 工作线程取出任务后，调用process_read函数，通过主、从状态机对请求报文进行解析。
  * 解析完之后，跳转do_request函数生成响应报文，通过process_write写入buffer，返回给浏览器端

# [05 HTTP连接处理(中)](https://mp.weixin.qq.com/s?__biz=MzAxNzU2MzcwMw==&mid=2649274278&idx=7&sn=d1ab62872c3ddac765d2d80bbebfb0dd&chksm=83ffbefeb48837e808caad089f23c340e1348efb94bef88be355f4d9aedb0f9784e1f9e072b1&cur_album_id=1339230165934882817&scene=189#wechat_redirect)

## 流程图与状态机
![](picture/主状态机.jpg)

## 主状态机
三种状态，标识解析位置
* CHECK_STATE_REQUESTLINE，解析请求行
* CHECK_STATE_HEADER，解析请求头
* CHECK_STATE_CONTENT，解析消息体，仅用于解析POST请求

## 从状态机
三种状态，标识解析一行的读取状态
* LINE_OK，完整读取一行
* LINE_BAD，报文语法有误
* LINE_OPEN，读取的行不完整

## HTTP报文解析
浏览器端发出http连接请求，服务器端主线程创建http对象接收请求并将所有数据读入对应buffer，将该对象插入任务队列后，工作线程从任务队列中取出一个任务进行处理。

各子线程通过process函数对任务进行处理，调用process_read函数和process_write函数分别完成报文解析与报文响应两个任务。

## HTTP_CODE
表示HTTP请求的处理结果，报文解析中只涉及四种：
* NO_REQUEST
  * 请求不完整，需要继续读取请求报文数据
* GET_REQUEST
  * 获得了完整的HTTP请求
* BAD_REQUEST
  * HTTP请求报文有语法错误
* INTERNAL_ERROR
  * 服务器内部错误，该结果在主状态机逻辑switch的default下，一般不会触发

## 解析报文整体流程
process_read通过while循环，将主从状态机进行封装，对报文的每一行进行循环处理。

* 判断条件
  * 主状态机转移到CHECK_STATE_CONTENT，该条件涉及解析消息体
  * 从状态机转移到LINE_OK，该条件涉及解析请求行和请求头部
  * 两者为或关系，当条件为真则继续循环，否则退出
* 循环体
  * 从状态机读取数据
  * 调用get_line函数，通过m_start_line将从状态机读取数据间接赋给text
  * 主状态机解析text

## 从状态机逻辑
在HTTP报文中，每一行的数据由`\r\n`作为结束字符，空行则是仅仅是字符`\r\n`。
因此，可以通过查找`\r\n`将报文拆解成单独的行进行解析，项目中便是利用了这一点。

从状态机负责读取buffer中的数据，将每行数据末尾的\r\n置为\0\0，并更新从状态机在buffer中读取的位置m_checked_idx，以此来驱动主状态机解析。
* 从状态机从m_read_buf中逐字节读取，判断当前字节是否为\r
  * 接下来的字符是\n，将\r\n修改成\0\0，将m_checked_idx指向下一行的开头，则返回LINE_OK
  * 接下来达到了buffer末尾，表示buffer还需要继续接收，返回LINE_OPEN
  * 否则，表示语法错误，返回LINE_BAD
* 当前字节不是\r，判断是否是\n（一般是上次读取到\r就到了buffer末尾，没有接收完整，再次接收时会出现这种情况）
  * 如果前一个字符是\r，则将\r\n修改成\0\0，将m_checked_idx指向下一行的开头，并返回LINE_OK
* 当前字节既不是\r，也不是\n
  * 表示接收不完整，需要继续接收，返回LINE_OPEN

解析完请求行后，主状态机继续分析请求头。在报文中，请求头和空行的处理使用的同一个函数，这里通过判断当前的text首位是不是\0字符，若是，则表示当前处理的是空行，若不是，则表示当前处理的是请求头。

* CHECK_STATE_HEADER
  * 调用parse_headers函数解析请求头部信息
  * 判断是空行还是请求头，若是空行，进而判断content-length是否为0，如果不是0，表明是POST请求，则状态转移到CHECK_STATE_CONTENT，否则说明是GET请求，则报文解析结束。
  * 若解析的是请求头部字段，则主要分析connection字段，content-length字段，其他字段可以直接跳过，各位也可以根据需求继续分析。
  * connection字段判断是keep-alive还是close，决定是长连接还是短连接
  * content-length字段，这里用于读取post请求的消息体长度

如果仅仅是GET请求，如项目中的欢迎界面，那么主状态机只设置之前的两个状态足矣。

GET和POST请求报文的区别之一是有无消息体部分，GET请求没有消息体，当解析完空行之后，便完成了报文的解析。

但后续的登录和注册功能，为了避免将用户名和密码直接暴露在URL中，我们在项目中改用了POST请求，将用户名和密码添加在报文中作为消息体进行了封装。

---

解析报文部分添加解析消息体的模块：
```c++
while((m_check_state==CHECK_STATE_CONTENT && line_status==LINE_OK)||((line_status=parse_line())==LINE_OK))
```
1. 那么，这里的判断条件为什么要写成这样呢？

在GET请求报文中，每一行都是\r\n作为结束，所以对报文进行拆解时，仅用从状态机的状态line_status=parse_line())==LINE_OK语句即可。

但，在POST请求报文中，消息体的末尾没有任何字符，所以不能使用从状态机的状态，这里转而使用主状态机的状态作为循环入口条件。

2. 后面的`&& line_status==LINE_OK`又是为什么

解析完消息体后，报文的完整解析就完成了，但此时主状态机的状态还是CHECK_STATE_CONTENT，也就是说，符合循环入口条件，还会再次进入循环，这并不是我们所希望的。

为此，增加了该语句，并在完成消息体解析后，将line_status变量更改为LINE_OPEN，此时可以跳出循环，完成报文解析任务。

* CHECK_STATE_CONTENT
  * 仅用于解析POST请求，调用parse_content函数解析消息体
  * 用于保存post请求消息体，为后面的登录和注册做准备

---



