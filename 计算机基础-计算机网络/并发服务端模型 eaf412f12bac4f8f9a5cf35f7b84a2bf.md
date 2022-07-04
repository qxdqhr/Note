# 并发服务端模型

# 服务器

## 1. 服务端基本概述：

- 客户端和服务端是互联网应用程序的基本组成部件，几乎所有应用程序都有对应的服务端程序以支持。
- 后台开发包括服务端开发。

## 2. 服务端的几种功能：

- 服务端为客户端提供 数据支持；更新支持；存储支持；交互支持等功能。

## 3. 客户-服务端模型的由来：

### 问题的引出:

- 通信软件能收发信息，若采用 **端对端的发送机制** ,则两端必定互相要知道**各自的IP地址**，
- 而在实际生活中，每个用户的客户端会**频繁更换IP地址** （多地登录/更换网络登录）
- 由此会产生两种问题：
    1. 当对方客户端更换了一个**新的IP地址**进行登录时,本机客户端**无法找到**对方的IP地址，无法连接。
    2. 每个**客户端**不能存储**所有对方客户端**曾使用过的**所有IP地址**（数据量较多且过于随机）
- 所以引入作为第三端(服务器)作为中介者解决问题。

### 问题的解决：服务器的数据中转作用

- 服务器中设定一个**IP地址表**,用于记录**所有用户**的**IP地址信息**。
- 每当一个用户登陆时，将此用户**客户端的登陆IP地址**加入**服务端中的IP地址表**中;
- 若用户**改变IP地址登陆**，必定使得用户的客户端重新登陆；进而**更新用户的IP地址信息表**，可以获取用户的最新地址；
- 这样QQ就能够**实时获取**用户的最新的IP地址;解决了更换地址无法连接的问题。

## 4. 简单总结：

1. 客户-服务端的概念实现了**互联网中的多个用户实时互联**，这一能力被称为**网络穿透**。
2. 在发送数据时，客户端要把数据传送给服务端再通过服务端程序进行转发，服务端起**中转数据的作用**。
3. 服务端的产生也表明：要达成通信功能，登陆时**客户端一定要先连接服务端**。

## 5. 服务端的种类：

1. 中转(处理)服务器 : **处理性能非常强大**
2. 代理服务器 : 一般具有**负载均衡能力**，用于接收外部链接请求，成百上千的客户端与服务器连接时先接入代理服务器
3. 数据库服务器： 用于 **数据持久化** 以及 **组织数据关系(表关系)**
4. 文件服务器： 负责存储数据；持久化磁盘，文件系统管理

## 6. 服务器的其他相关概念

1. 服务器集群:服务器机房 多个服务器**集中在一起**叫做服务器集群。
2. 分布式： **服务器集群**采用**分布式架构**统一组织管理**若干个服务器的软件和硬件设施**。

## 7.服务器的基本能力：

1. 中转能力：服务端主要工作之一就是数据中转
2. 处理能力
3. 并发能力：对于服务器来说客户端总是**多对一**进行访问的，在处理**多用户请求**的时候一定需要**并发能力**； 服务器的并发能力体现在**并发模型**上 。 ## 8. 阿里云
4. 阿里云是**性价比较高**的服务器方案
5. 租用阿里云相当于申请一块**网络空间**（网络资源，吞吐量等），会**提供对应服务器的公有IP地址**。
6. 租用阿里云后，自己写好客户端，服务端代码，并将服务端代码上传至阿里云服务器，并通过阿里云服务器运行自己写的服务端代码。
7. 在本地运行客户端代码，和远程服务器进行数据交互，测试服务端代码是否正确
8. 一般在阿里云运行的基本上是业务处理代码（协议制定/协议解析），而非服务器实现代码。
9. 阿里云服务器实现并发模型（redoctor，IO复用，多进线程模型），并发模型的实现即是如何是服务器实现一对多的工作。
    
    # 并发模型
    

## 并发模型的概念：

1. **并发模型**是一系列采用 **并发技术(多进程，多线程技术)** 实现 **并发能力** 的 **服务端程序**
2. **并发效果**指能够使**多**个客户端**并发地访问**服务器
3. 并发模型大都能够达成并发效果， 但**并发技术**与**并发效果**并**无直接关系**, **一些并发模型**可能**不需要使用多线程与多进程技术**。 eg：基本UDP模型 (单进程实现**基本一对多**)
4. 注意：**单进程**的并发模型是不可能做到**高并发效果**的。 ## 再议基本TCP模型： ### 基本TCP模型的代码示例：

```
#include<unistd.h>#include<stdlib.h>#include<string.h>#include<sys/socket.h>#include<arpa/inet.h>#include<ctype.h>int main(){    //初始化网络信息    struct sockaddr_in severaddr,client;    severaddr.sin_family =AF_INET;    seversddr.sin_port =htons( 8000 );    severaddr.sin_addr.s_addr= htonl( INADDR_ANY );//INADDR_ANY表示本机任意IP    // 创建socket    int severfd =socket( AF_INET , SOCKET_STREAM , 0 );    //绑定，固定IP地址与端口号    bind( severfd , (struct sockaddr*)&severaddr , sizeof(severaddr) );    //监听连接状态    listen( severfd , 128 );    //等待客户端连接    int clientfd;    socklen_t size =sizeof( clientaddr );    char ip[16];    int port;    bzero( ip , sizeof( ip ) );    printf("TCP SEVER ACCEPTING...\n");    if( ( clientfd = accept(severfd,(struct sockaddr*)&clientaddr,&size))>0 )    {        //将accept函数的返回值赋给clientfd 大于0时 代表成功连接        inet_ntop(AF_INET, &clientaddr.sin_addr.s_addr , ip , sizeof(ip) );        port= ntohs (clientaddr.sin_port);        printf("SEVER ACCEPT SUCCESS CLIENT INFO:[%s:%d]\n",ip,port);    }    //业务处理：完成客户端数据转换和反馈    int len,j;    char buf[1500];    bzero(buf,sizeof(buf));    //读取请求    while(1)    {        len = recv(clientfd , buf , sizeof(buf) , 0);        j=0;        while(len > j)        {            buf[j]= toupper(buf[j]);            j++;        }        //反馈响应        send(clientfd , buf , len , 0);        bzero( buf , sizeof(buf) );    }    close(severfd);    close(clientfd);    return 0;}
```

### 基本TCP模型的工作流程：

1. 初始化客户端与服务端的**网络信息变量**和**服务端的各项参数**
2. 调用socket函数，创建socket，并得到返回的服务器描述符
3. 将**服务器的网络信息变量**与**服务器描述符**使用**bind函数**绑定
4. 调用**listen函数**，检测服务器描述符是否有客户端请求连接
5. 初始化客户端网络信息变量
6. 等待客户端连接服务器，调用accept函数，将客户端的地址与客户端描述符链接，使服务器通过客户端描述符操作客户端。
    1. 使用**阻塞方式调用accept函数**，未连接到客户端时一直阻塞，直到有客户端连接时返回
    2. 使用**非阻塞方式调用accept函数**，未连接到客户端时直接返回。
7. 初始化业务处理模块相关变量
8. 使用recv函数读取客户端中的数据并存入刚刚创建好的变量中，并执行工作，
9. 将数据处理完成后反馈给客户端。

### 基本TCP模型无法实现并发(一对多)的原因：

1. 等待连接过程（accept函数） 与 业务处理过程（recv函数） 是**互相冲突**的；
    - 在进行等待连接功能时，TCP**整个进程需要阻塞**以等待新的客户端连接；
    - 此时主进程阻塞，**已经连接的客户端**就无法进行**业务处理流程**；
    - 同理，当进程在处理客户端工作的时候，也会发生阻塞，此时不能检测是否有新的客户端连接。
    - 即使**设定RECV函数为非阻塞态**，同样会引发问题;因为**RECV函数的非阻塞态**即使**没接收到数据**也会**进行数据处理流程**，导致ACCEPT函数无法检测是否有新客户端进行连接
2. 基本TCP模型为**单进程**，存在于（1）中更深层的原因：
    - 单进程不能并发处理多项工作，即使能够处理，仅能排队线性的处理**待处理用户集合**，效率低下，出错率高。

### ACCEPT函数与RECV函数的 阻塞态 与 非阻塞态：

- 当执行RECV函数时，检测已连接的客户端没有数据时要做的工作；
    - 有数据时直接返回
    - READ|WRITE 的阻塞态：
        - 没有数据时，一直阻塞等待，直到接收到数据时，返回
    - READ|WRITE 的非阻塞态：
        - 没有数据时直接返回
1. 解决冲突的方法： 多进程并发服务端模型

# 多进程并发服务端模型 — 基本TCP+多进程

## 多进程并发模型概述：

- 由于TCP模型无法解决accept函数与recv函数之间的冲突问题，引入**多进程技术**实现**分工工作**，但多进程并发模型仍具有许多缺点。

## 多进程并发模型的设计思路（以银行举例）：

- 在基本TCP模型的设计思路中，多个**用户（客户端程序）**仅能对应一个**操作员（TCP主进程）**，导致**工作效率极低**同时**无法实现并发**。
- 在多进程并发服务端模型中，设立一个**接待人员**，接待人员负责**沟通用户（将服务端与客户端建立连接）**，不负责业务处理。
- 同时，接待人员会为**用户**配备一个**唯一对应的操作员**，处理人员仅负责**对应用户的业务流程（实现1对1的工作方式）**，这样就能基本解决并发问题。

## 多进程并发模型的缺点：

- 操作员**随用户的增多而增多**，导致 **处理 操作员的开销巨大，维护成本高**
- 维护成本的产生：
    - 当一个用户的工作被一个操作员完成后，用户会减少，同时对应处理人员也应被开除;
    - 用户高峰期时接待员需要**频繁进行生成与开除操作员的工作**，这样产生了极大的无用开销;

## 多进程并发模型的实现；

- 上述思路的接待人员可以以父进程的方式来实现
- **操作员**可以以**父进程的子进程**方式实现
- **父进程的工作**是**与客户端建立连接**，并且**创建子进程**
- **服务端与客户端进行数据交互**使用accept函数返回的**clientfd**以实现
- 每创建一个新的子进程，都要通过父进程传递用户的clientfd才能完成链接（通过父子进程的继承关系实现），即，父进程建立连接成功后，创建子进程，这样创建的子进程会继承父进程刚刚进行连接的clientfd，这一描述符就是对应要处理用户的客户端描述符

## 多进程并发模型的代码示例：

```
#include<unistd.h>#include<stdlib.h>#include<string.h>#include<sys/socket.h>#include<arpa/inet.h>#include<ctype.h>using  namespace std;int main(){    //初始化网络信息    struct sockaddr_in severaddr;    struct sockaddr_in clientaddr;    severaddr.sin_family =AF_INET;    severaddr.sin_port =htons( 8000 );    severaddr.sin_addr.s_addr= htonl( INADDR_ANY );//INADDR_ANY表示本机任意IP    // 创建socket    int severfd =socket( AF_INET ,SOCK_STREAM , 0 );    //绑定，固定IP地址与端口号    bind( severfd , (struct sockaddr*)&severaddr , sizeof(severaddr) );    //监听连接状态    listen( severfd , 128 );    //等待客户端连接    int clientfd;    socklen_t size =sizeof( clientaddr );    char ip[16];    bzero( ip , sizeof( ip ) );    int port;    pid_t pid;    printf("PROCESS SEVER ACCEPTING...\n");    while(1){        if( ( clientfd = accept( severfd , (struct sockaddr * )& clientaddr , &size ) )>0 ){            //将accept函数的返回值赋给clientfd 大于0时 代表成功连接            inet_ntop(AF_INET, &clientaddr.sin_addr.s_addr , ip , sizeof(ip) );            port= ntohs (clientaddr.sin_port);            //创建处理业务的子进程            pid=fork();            if( pid >0 ) {                //任意设定一种父进程工作                printf("SEVER ACCEPT SUCCESS CLIENT INFO:[%s:%d]\n",ip,port);            }            else if( pid == 0) {                //此处为子进程要执行的工作，除此以外均为父进程工作。                //此时子进程已经完成从父进程继承clientfd的过程。                //子进程执行业务处理流程                //业务处理：完成客户端数据转换和反馈                int len,j;                char buf[1500];                bzero(buf,sizeof(buf));                //读取请求                while( ( len = recv(clientfd , buf , sizeof(buf) , 0) ) >0 ){                    j=0;                    while(len > j){                        buf[j]= toupper(buf[j]);                        j++;                    }                    //反馈响应                    send(clientfd , buf , len , 0);                    bzero( buf , sizeof(buf) );                }                exit(0);//子进程不应离开工作区            }            else{                perror("fork call failed");                exit(0);            }        }    }    close(severfd);    close(clientfd);    return 0;}
```

## 多进程并发模型中存在的问题：

### 子进程回收问题：(僵尸进程)：

- 危害：占用一个进程PCB，导致新创建的进程不能被分配到PCB而创建失败
- 产生原因：在客户端发生异常结束后，子进程服务端不能被回收。
- 问题分析:
    - **子进程该由谁来回收?**
        - 由**父进程**完成回收工作:
            - 多进程并发模型中,父进程的工作是阻塞链接(ACCEPT模块); 一般情况下,父进程**需要调用WAIT函数** 以回收**因异常导致需要回收**的子进程; 但WAIT函数是一个**阻塞回收的函数**. 如果由父进程回收子进程,又会产生**两种工作均阻塞的冲突**. (多进程并发模型最初要解决的问题)
        - 由兄弟进程完成回收工作:
            - **子进程终止后,内核只会通知结束进程的父进程,而不会通知其兄弟进程,因此兄弟回收是不成立的.**
            - 在进程终止时内核向其父进程发送信号(SIGCHLD),由父进程进行回收.
    - **子进程该如何被回收?**
        - 为父进程**再创建一条线程**以分工工作; 使父进程就有两条线程在工作:主控线程+普通线程;
        - 当内核向父进程发送一个信号时,父进程中的所有线程均可以接收到此信号;
        - 因为线程是进程中的执行单元,都是进程的一部分;
        - 由此,可以使父进程的主控线程执行等待连接的工作(ACCEPT);
        - 使父进程的普通线程执行回收子进程的工作(WAIT);

### 问题解决:多线程+信号屏蔽

### 使用多线程的原因:

- 子进程异常终止后只能由其父进程来回收;
- 父进程仅采用单线程工作会阻塞在客户端连接的工作中;
- 主控线程和普通线程均使用父进程的PCB,所以内核发送信号时,二者均可接受得到;(同一进程中,线程间PCB共享)
- 同一进程的多线程间以不同线程的TCB(Thread Control Block)区分,但他们共享同一个PCB(Process Control Block)

### 使用信号屏蔽集的原因:

- 进程中多条线程间信号屏蔽字是非共享资源,每个线程拥有独立的屏蔽字;
- 区分两线程工作的有序且互不干扰,应保证SIGCHILD信号仅能被普通线程接受到;所以要设立信号屏蔽字;
- 信号屏蔽主控线程的原因:
    - 使服务器的主要工作(建立连接)能够正常运行,因为,服务器的客户端连接能力重要于服务器的业务处理能力;

## 多进程模型的优化的运行流程:

1. 当需要回收子进程时,调用WAIT函数,内核向父进程发送信号(SIGCHILD);
2. 主控线程设置屏蔽字;
3. 主控线程创建普通线程;(主控线程和普通线程存在继承关系,此时普通线程继承了主控线程当前的屏蔽字,普通线程也屏蔽SIGCHILD信号)
4. 普通线程解除对SIGCHILD信号的屏蔽;(普通线程所修改的屏蔽字不会影响主控线程的屏蔽字,线程屏蔽字不共享)
5. 信号经过信号屏蔽集;(信号被主控线程屏蔽;不被普通线程所屏蔽;)
6. 普通线程遇异常终止的子进程能够接收到信号并回收;主控线程能够不接收到信号而完成客户端连接的工作;
    1. 主控线程工作:客户端连接
        1. 客户端连接是服务器的基本工作,比起数据交互,链接客户端更加重要;客户端连接决不能被中断
    2. 普通线程工作:回收子进程
        1. 直接调用函数工作:仅能做子进程回收工作,不能进行其他工作,灵活性较低;
            1. 直接调用WAIT函数(阻塞函数), 产生阻塞开销(一直阻塞直到回收子进程)
            2. 直接调用WAITPID函数(非阻塞函数), 产生轮询开销(一直轮询直到回收子进程)
            3. 由于普通线程是父进程中的一个工作单元,将其视为父进程;
            4. 注意:
                - 理想情况是:当子进程因异常结束后,父进程捕捉到内核发送来的信号,再调用回收子进程的函数将其回收;所以要使用信号捕捉的方法;
        2. 使用信号捕捉方法:当接收到信号后再执行工作
            1. 设置信号捕捉,定义实现信号捕捉函数;
            2. 设置信号触发行为;
            3. 捕捉到信号后可以使用WAIT函数/WAITPID函数回收子进程:
            4. 注意:
                1. 先设置信号屏蔽字后捕捉信号的原因:
                    1. 内核发送信号时,父进程中所有线程都能够接收到;所以要先设置信号屏蔽字;
                    2. 信号捕捉函数的调用过程:内核调用捕捉函数;
                    3. 主控线程如果接收到了信号,客户端连接的工作(ACCEPT的阻塞状态)会被中断;
                    4. ACCEPT在中断期间,但凡传来信号,中断的ACCEPT都不会接收到,这样会导致连接丢失,违背了服务器的本职工作.

## 简单总结:

1. TCP模型:
    1. 仅能一对一工作;
    2. 一对多工作时会导致监听工作和数据处理工作产生冲突;
        1. 原因:等待连接工作调用的ACCEPT函数是阻塞函数;RECV函数也是阻塞函数
2. 多进程并发模型:
    1. 设定父进程作为中继者,实时等待连接;
    2. 将处理工作交给子进程,此时出现子进程无法回收问题;
        1. 原因:父进程专注于等待连接,没空去回收;
    3. 将父进程分成两线程处理回收工作和等待连接工作;
    4. 保证主控线程能持续请求连接 必须使用子进程的原因:子进程回收可以被信号控制

## 优化后的多进程并发模型的代码示例：

```
#include<unistd.h>
#include<stdlib.h>
#include<string.h>
#include<sys/socket.h>
#include<arpa/inet.h>
#include<pthread.h>
#include<signal.h>
#include<sys/wait.h>

#include<ctype.h>

//线程捕捉函数
void SIG_WAIT(int n){
    pid_t wpid;
    while( ( wpid=waitpid(-1,NULL,WNOHANG) ) >0 ){ //设置任意进程可回收,并采用轮询回收方式
        printf("WAIT THREAD TID : 0x%x WPID: %d:%d\n",(unsigned int)pthread_self(),wpid);
    }

}
//线程工作函数
void * THREAD_JOB(void * arg){

    //防止出现线程回收问题设置线程分离态
    printf("WAIT THREAD TID :0x%x WATING...\n",(unsigned int)pthread_self()) ;
    pthread_detach(pthread_self());
    //先进行信号捕捉
    struct sigaction act,oast;
    act.sa_handler = SIG_WAIT;//捕获函数
    act.sa_flags = 0;
    sigemptyset(&act.sa_mask);
    sigaction(SIGCHILD,&act,&oact);

    //后解除SIGCHILD信号屏蔽,防止信号传来,被默认处理掉使捕捉函数不能捕捉到信号;
    sigset_t set;
    sigemptyset(&set);
    sigprocmask(SIG_SETMASK,&set,NULL);

    //如果有工作,可执行自定义工作,否则挂起等待信号回收
    while(1){
        sleep(1);
    }
}

int main(){

    //初始化网络信息
    struct sockaddr_in severaddr,client;
    severaddr.sin_family =AF_INET;
    seversddr.sin_port =htons( 8000 );
    severaddr.sin_addr.s_addr= htonl( INADDR_ANY );//INADDR_ANY表示本机任意IP

    // 创建socket
    int severfd =socket( AF_INET , SOCKET_STREAM , 0 );

    //绑定，固定IP地址与端口号
    bind( severfd , (struct sockaddr*)&severaddr , sizeof(severaddr) );

    //监听连接状态
    listen( severfd , 128 );

    //等待客户端连接
    int clientfd;
    socklen_t size =sizeof( clientaddr );
    char ip[16];
    int port;
    pid_t pid;//子进程
    bzero( ip , sizeof( ip ) );

    //主控线程设置屏蔽字屏蔽SIGCHILD信号
    sigset_t set,oset;
    sigemptyset(&set);
    sigaddset(&set,SIGCHILD);
    sigprocmask(SIG_SETMASK,&set,&oset);

    //创建普通线程,普通线程默认继承此屏蔽字
    pthread_t tid;
    pthread_create(&tid,NULL,THREAD_JOB,NULL);

    printf("PROCESS SEVER ACCEPTING...\n");
    while(1){
        if( ( clientfd = accept( severfd , (struct sockaddr * )& clientaddr , &size ) )>0 ){

            //将accept函数的返回值赋给clientfd 大于0时 代表成功连接
            inet_ntop(AF_INET, &clientaddr.sin_addr.s_addr , ip , sizeof(ip) );
            port= ntohs (clientaddr.sin_port);

            //创建处理业务的子进程
            pid=fork();
            if( pid >0 ) {
                //任意设定一种父进程工作
                printf("SEVER ACCEPT SUCCESS CLIENT INFO:[%s:%d]\n",ip,port);
            }
            else if( pid == 0) {
                //子进程同样继承了severfd,但是并不会使用severfd,一开始就将其关闭;
                close(severfd);
                //此处为子进程要执行的工作，除此以外均为父进程工作。
                //此时子进程已经完成从父进程继承clientfd的过程。
                //子进程执行业务处理流程

                //业务处理：完成客户端数据转换和反馈
                int len,j;
                char buf[1500];
                bzero(buf,sizeof(buf));

                //读取请求
                while( ( len = recv(clientfd , buf , sizeof(buf) , 0) ) >0 ){

                    j=0;
                    while(len > j){
                        buf[j]= toupper(buf[j]);
                        j++;
                    }
                    //反馈响应
                    send(clientfd , buf , len , 0);
                    bzero( buf , sizeof(buf) );
                }
                //检测客户端异常,结束子进程;
                if(len == 0){
                    printf("Sever child pid [%d ] RECV 0 PROCESS EXIT..\n",getpid());//打印异常信息
                    close(clientfd);//关闭异常终止的客户端文件描述符
                    exit(0);//结束子进程
                }
                exit(0);//子进程不应离开工作区,应在离开子进程之前将其结束
            }
            else{
                perror("fork call failed");
                exit(0);
            }
        }
    }

    close(severfd);
    close(clientfd);
    return 0;
}
```

# 多线程并发服务端模型

## 多线程并发模型的设计思路:

1. 总体设计类似于多进程并发模型
2. 在多线程并发模型中,分为操作员(主控线程),用户(客户端),接待人员(普通线程)
3. 多进程并发模型需要考虑子进程回收问题,而多线程并发模型不需要;
4. ACCEPT函数返回的clientfd交给普通线程使其与用户交互
5. 多进程模型和多线程模型使用哪个视需求而定

## 多线程并发模型概述:

Ngix：多线程模型

## 示例代码：

```
#include <stdio.h>
#include <unistd.h>
#include <sys/socket.h>
#include <stdlib.h>
#include <string.h>
#include <pthread.h>
#include <ctype.h>
#include <arpa/inet.h>

void * thread_job(void * arg)
{
        pthread_detach(pthread_self());//将线程置为分离态

        char buf[1500];
        int len,j;
        int clientfd = *(int*)arg;//线程函数传递参数,需要强转
        while((len = read(clientfd,buf,sizeof(buf)))-0)
        {
                j=0;
                while(len - j)
                {
                        buf[j] = toupper(buf[j]);
                        j++;
                }
                write(clientfd,buf,len);
                bzero(buf,sizeof(buf));
        }
        close(*(int*)arg);
        pthread_exit(NULL);
}

int main(void)
{
        //网络初始化
        struct sockaddr_in serveraddr,clientaddr;
        bzero(&serveraddr,sizeof(serveraddr));
        serveraddr.sin_family = AF_INET;
        serveraddr.sin_port = htons(8000);
        serveraddr.sin_addr.s_addr = htonl(INADDR_ANY);
        int clientfd;
        pthread_t tid;
        int serverfd = socket(AF_INET,SOCK_STREAM,0);
        bind(serverfd,(struct sockaddr *)&serveraddr,sizeof(serveraddr));
        listen(serverfd,128);
        //主控线程ACCEPT
        while(1)
        {
                socklen_t size = sizeof(clientaddr);
                clientfd = accept(serverfd,(struct sockaddr *)&clientaddr,&size);
                //创建线程,在
                pthread_create(&tid,NULL,thread_job,(void*)&clientfd);

        }
        close(serverfd);
        return 0;

}
```

ps-Lf 查看线程详细信息

```
void * THREAD_JOB(void * arg)
{
    pthread_detach(pthread_self());
    //业务处理，完成客户端数据的转换和反馈
    int len ,j;
    char buf[1500];
    int clientfd =*(int *)arg;
    bzero(buf,sizeof(buf));
    while((len=recv(clientfd,buf,sizeof(buf),0))-0){
        if(len == -1)
        {
            perror("recv error");
        }
        j=0;
        while(len -j){
            buf[j] = toupper(buf[j]);
            j++;
        }
        send(clientfd,buf,len,0);
        bzero(buf,sizeof(buf));
    }
    //检测客户端异常，线程终止
    if(len ==0){
        printf("Sever Thread tid [0x%x] recv 0 thread exit ..\n",(unsigned int)pthread_self());
        close(clientfd);
        pthread_exit((void*)0);
    }
}
int main(void){
    struct sockaddr_in sever addr,clientaddr;
    severaddr.sin_family =AF_INET;
    severaddr.sin_port =htons(8000);
    severaddr.sin_addr =htonl(INADDR_ANY);
    //INADDR_ANY表示本机任意IP地址
    int severfd =socket(AF_INET,SOCK_STREAM,0);
    ?????

}
```

这样的多进程模型的缺点： 没有管理多线程和多进程的机能(进程线程的重用性，任务的监听与传递，进线程可用性计算)

# 多路IO复用技术模型（多路IO转接模型）

## IO操作:

- 顾名思义,input output 操作,就是对一块缓冲区的输入数据和输出数据的操作,即读写操作
- 对于文件的操作(文件描述符)
- 对于管道的操作(管道的文件描述符)
- 对于socket的操作(socket的文件描述符)本质是对缓冲区的IO操作,可以通信信道操作数据

## IO复用技术:TODO

- 一般的IO操作只能是读或写

### 主要作用：单进程监听多个IO事件,实现简易并发(多对一)效果

- IO复用技术和网络无必然联系,本质处理IO操作的模型(是否可以用于文件传输?)
- 基本TCP模型中产生的冲突问题可以用TCP基本模型+IO复用实现单进程实现一对多处理的简易并发效果 当挂起的单位不能推进时，可以切换到其他可以推进的

## 经典IO复用技术：

- select模型
    - 用户态建立socket签到表,拷贝到内核区,等待一段时间,内核去发送回来,遍历签到表,寻找到有链接的socket,处理IO事件
- poll模型
- epoll模型
- 完成端口
- 重叠IO
- 信号驱动IO

POLL模型无监听数量限制，未使用监听集合（fd_set，监听集合类型）

## IO复用是如何结合到TCP模型的:

- socket也算IO技术，因为对用文件描述符表示的socket的操作本质也是IO操作
- 设定一个监听集合,其中每一个元素都代表一个socket
- 每个socket可以取值0或1,0/1都代表监听情况，0表示未就绪，1表示就绪
- 监听集合作用是监听IO上的事件 select模型可以设置监听的事件 读事件 写事件 异常事件 read函数，recv函数，默认阻塞函数，有人向他写数据时，；立刻被唤醒 accept阻塞等待连接，没人给链接

唤醒函数都是由于事件 某一天客户端会向connect发送请求时就是发送一个事件（握手请求），这一事件会被发送给severfd，severfd读取这一事件是会被触发一个读事件，这个读事件一定会被监听（被listen监听的毒事件） 整个挂起和唤醒的事件 accept和read阻塞的原因是相同的：等待某一个事件(event) accept和read冲突的解决： accept和read冲突是由于两函数都要阻塞等待来监听事件 将accept和read等待事件触发的工作交给select来做

都是由内核监听的事件

# Select模型

使用的是select调用accept 调用马上建立连接

让select去监听多路IO，有多少个socket就放入监听集合中，让select监听 监听集合最大可以放置1024个socket select采用轮询的方式

1.将socket加入监听集合 2.设置监听事件 3.有就绪的socket时，判断找出并进行相应的处理 如何判断哪个socket就绪？

## 使用的函数

### select函数

### 返回值：

- 已经建立好链接的IO操作的数量

### 参数：

- 监听数量
- 要监听读事件的集合地址，监听集合的读事件并传出 readfds
- 要监听写事件的集合地址，监听集合的写事件
- 要监听异常事件的集合地址，监听集合的异常事件
- 阻塞时长,是一个时间结构体可以设置微秒的时间精度
    - 一般为NULL,select阻塞监听
    - timeval>0,select定时阻塞监听,可以设定隔一段时间返回一次
    - timeval=0,select非阻塞监听

### 注意：

- 集合地址都是是一个传入传出性质的参数
- 当select调用时，作为传入参数监听这些socket的指定事件
- 传出时，内核会根据就绪情况改变传入的集合
- (将就绪的socket位保留为1，未就绪的置0，传出时改变是为了方便查看已经就绪的socket)

### FD_ISSET

此函数结合传出就绪集合，判断就绪 避免集合使用异常，分离传入和传出

### FD_ZERO(&set)

将监听集合初始化为0

### FD_SET(severfd,&set)

将监听集合对应的 socket 置1

### FD_CLR(=severfd,&set)

将监听集合对应的 socket 置0

客户端异常时，socket去除，监听集合去除，关闭socket，NREADY–

针对两类不同的就绪，实现了单进程的1对多的实现效果

## select模型的优缺点：

### 优点：

1. 兼容性和跨平台能力较强
2. 实现起来较为简单便于维护
3. 如果对时间精度要求较高，select支持微秒级别定时

### 缺点：

1. s elect 最大监听数为1024，不能满足高并发需求
2. select采用轮询监听方式，导致轮询数量的增加，IO处理效率呈线性下降,甚至效率会低于多进程模型,但开销小于多进程模型
3. select没有将集合传入传出(监听就绪集合)分离，用户需要自行设置
4. select在传递监听集合和设置监听时会产生大量无意义的拷贝和开销,监听集合中有的socket同样会被拷贝一遍产生大量开销
5. select就绪时，只返回就绪的数量，用户需要自行遍历查找就绪的socket 使用比较麻烦，代码混乱;
    1. 举例：假设1023个socket，倒数第一个就绪了，要花费大量时间遍历未就绪的socket

## 代码示例:

```
#include<unistd.h>
#include<stdlib.h>
#include<string.h>
#include<sys/socket.h>
#include<arpa/inet.h>
#include<iostream>
#include<ctype.h>

using  namespace std;
int main()
{
    //初始化网络信息
    struct sockaddr_in severaddr;
    struct sockaddr_in clientaddr;
    severaddr.sin_family =AF_INET;
    severaddr.sin_port =htons( 8000 );
    severaddr.sin_addr.s_addr= htonl( INADDR_ANY );//INADDR_ANY表示本机任意IP

    // 创建socket
    int serverfd =socket( AF_INET ,SOCK_STREAM , 0 );

    //绑定，固定IP地址与端口号
    bind( serverfd , (struct sockaddr*)&severaddr , sizeof(severaddr) );
    listen( serverfd , 128 );//监听连接状态

    //等待客户端连接
    int clientfd;
    socklen_t size =sizeof( clientaddr );

    char ip[16];//声明IP地址
    bzero( ip , sizeof( ip ) );

    int port;//声明端口号
    printf("SELECT SEVER ACCEPTING...\n");//打印提示信息

    //准备工作
    int clientarr[1023];//定义的一个socket数组
    //select只能监听1024的数组，除去服务端创建的serversocket 还剩下1023个

    int maxfd=serverfd; //确定监听的socket的最大数量

    //定义监听集合
    fd_set iset;//传入集合
    fd_set oset;//传出集合

    int nReady;//已就绪的socket数量

    //初始化socket数组,数组只有1023的大小
    for(int i=0;i<1023;i++)
       clientarr[i]=-1;//-1表示未接收到，0表示接收到未链接，1表示有链接
    //初始化监听集合，调用FD_ZERO，FD_SET
    FD_ZERO(&iset);
    FD_SET(serverfd,&iset);
    //定义一个待处理的数据
    char buf[1500];
    bzero( buf , sizeof( buf ) );

   int len=0;//定义一个接受数据的长度变量

    while(1)
    {
        //分离传入集合与传出集合
        //直接将传入集合赋值给传出集合，这样在select调用后就可以直接得到处理完毕的传出集合
        oset=iset;
        //循环进行监听
        nReady = select(maxfd+1,&oset,NULL,NULL,NULL);
        while(nReady)//如果此时传出集合中已经有就绪的socket，即nReady大于0
        {
            //判断是哪个socket就绪了，看看是谁闲下来，可以接收连接了
            if(FD_ISSET(serverfd,&oset))//如果是服务器的socket就绪了
            {
                //服务端接受客户端的链接，accept()返回接收到的客户端链接
                // accept (socket函数返回的socket，指向的定义的SOCKADDR_IN 结构体指针，指针大小值的地址)
                clientfd=accept(serverfd,(struct sockaddr*)&clientaddr,&size);
                cout<<clientfd<<"is connected"<<endl;
                //加入socket集合中
                for(int j=0;j<1023;j++)
                {
                    //如果socket集合中有可以使用的位置（socket集合未满）
                    if(clientarr[j]==-1)
                    {
                        //更新一下新接收到的socket
                        clientarr[j]=clientfd;
                        break;
                    }
                }
                //将接收到的客户端socket加入监听集合中
                FD_SET(clientfd,&iset);
                //更新最大的maxfd
                if(clientfd>maxfd)
                {
                    maxfd=clientfd;
                }
                //就绪集合中需要将serverfd置为空，否则传出集合中会一直为1,仍然在accept阻塞
                FD_CLR(serverfd,&oset);
            }
            else//如果是客户端的socket就绪了
            {
                //遍历查找是哪个clientfd就绪了
                for(int i=0;i<1023;i++)
                {
                    //如果这一位仍然可用，不是未赋值状态
                    if(clientarr[i]!=-1)
                    {
                        //如果当前客户端socket是就绪的,即已经被加入监听集合中
                        if(FD_ISSET(clientarr[i],&oset))
                        {
                            //读取当前客户端传输过来的数据
                            len=recv(clientarr[i],buf,sizeof(buf),0);
                            if(len>0)
                            {
                                //如果读取到了数据,开始处理数据
                                int j=0;
                                while (len>j)
                                {
                                    buf[j]=toupper(buf[j]);
                                    j++;
                                }
                                //处理数据完成后，发送数据
                                send(clientarr[i],buf,len,0);
                                bzero(buf,sizeof (buf));
                                //就绪集合中需要将对应clientarr置为空，否则就绪集合中会一直为1,仍然在accept阻塞
                                FD_CLR(clientarr[i],&oset);
                            }
                            if (len==0)//如果此时客户端异常
                            {
                                //将他从监听集合中删去
                                FD_CLR(clientarr[i],&iset);
                                //就绪集合中需要将对应clientarr置为空，否则就绪集合中会一直为1,仍然在accept阻塞
                                FD_CLR(clientarr[i],&oset);
                                close(clientarr[i]);
                                clientarr[i]=-1;
                            }
                            break;
                        }

                    }
                }
            }
            nReady--;//每次执行结束后，将已经就绪的socket数量减少
        }
    }

    close(serverfd);
    close(clientfd);
    return 0;
}
```

# POLL模型

- 很少使用，并未继承select的全部优点，反而诞生了更多的缺点。

## 特点：

1. 将监听集合的传入传出的分离
2. POLL模型突破了1024的监听限制
    1. 并未使用fd_set作为监听集合，而是让用户指定类型的自定义长度数组作为监听集合
    2. 这一举措并未解决轮询问题，盲目的突破监听数量，不能解决根本问题,某些情况下还有可能导致处理速度过慢
3. POLL模型可监听的事件种类多与select,select只能监听三种事件
4. 时间上并不能达成微妙级别的,仅支持秒或毫秒
5. 兼容性和跨系统能力较差(Linux系系统都兼容不全)
6. 仍存在轮询问题需要自行查找就绪的socket
7. poll在传递监听集合和设置监听时会产生大量无意义的拷贝和开销,监听集合中有的socket同样会被拷贝一遍产生大量开销
8. poll就绪时，只返回就绪的数量，用户需要自行遍历查找就绪的socket 使用比较麻烦，代码混乱，

## 关于POLL模型的API与类型:

- 自定义的监听集合数组：struct pollfd set [4096],成员如下：
    - fd:要监听的socket
        - fd>0表示要监听;
        - fd==-1表示非监听
    - events 要对socket设置的监听事件
        - 多种事件
        - POLLIN读事件
        - POLLOUT写事件
    - revents 内核传出的就绪事件,一般不用设置
    - 内核通过判断fd的值判断是否需要监听
- poll(),返回nReady
    - 监听的集合
    - 最大监听数量,一般等于监听集合的大小
    - 时间
        - 1:阻塞监听

### SELECT和POLL模型的处理过程：

1. 在用户空间定义监听集合，每次需要内核监听时， 将其从用户空间拷贝至内核空间
2. 从内核空间中的监听集合中提取监听项，将监听项挂载到IO设备等待队列中
3. 都通过IO设备帮助监听事件,并且因为IO设备等待队列的监听方式是轮询方式,所以依赖于IO设备等待队列进行监听的模型都采用轮询方式

## 代码示例:

```
#include<unistd.h>
#include<stdlib.h>
#include<string.h>
#include<sys/socket.h>
#include<arpa/inet.h>
#include<iostream>
#include<ctype.h>
#include<poll.h>//poll模型需要的头文件

#define MAX_FD 100
using  namespace std;
int main()
{
    //初始化网络信息
    struct sockaddr_in severaddr;
    struct sockaddr_in clientaddr;
    severaddr.sin_family =AF_INET;
    severaddr.sin_port =htons( 8000 );
    severaddr.sin_addr.s_addr= htonl( INADDR_ANY );//INADDR_ANY表示本机任意IP

    // 创建socket
    int serverfd =socket( AF_INET ,SOCK_STREAM , IPPROTO_TCP );

    //绑定，固定IP地址与端口号
    bind( serverfd , (struct sockaddr*)&severaddr , sizeof(severaddr) );
    listen( serverfd , 128 );//监听连接状态

    //等待客户端连接
    int clientfd;

    char ip[16];//声明IP地址
    bzero( ip , sizeof( ip ) );

    int port;//声明端口号
    printf("POLL SEVER ACCEPTING...\n");//打印提示信息

    //准备工作

    //定义POLL结构体数组
    struct pollfd clientarr[MAX_FD];//socket集合与监听就绪集合都被包含在了结构体中
    int nReady=0;//已就绪的socket数量
    //初始化POLL结构体数组
    for(int i=0;i<MAX_FD;i++)
    {
        clientarr[i].fd=-1;//-1表示未接收到，0表示接收到未链接，1表示有链接
        clientarr[i].events=POLLIN;//监听读事件
    }
    clientarr[0].fd=serverfd;//初始化服务器的fd
    clientarr[0].events=POLLIN;//监听读事件
    //定义一个待处理的数据
    char buf[1500];
    bzero( buf , sizeof( buf ) );

   int i;
   int j;

    while(1)
    {
        //循环进行监听
        nReady = poll(clientarr,MAX_FD,-1);//监听数组，监听数量，阻塞监听：-1
        if (nReady == -1)
         {
           perror("poll error:");
           return 0;
         }
        while(nReady!=0)//如果此时传出集合中已经有就绪的socket，即nReady大于0
        {
            //判断是哪个socket就绪了，看看是谁闲下来，可以接收连接了
            if(clientarr[0].revents==POLLIN)//如果是服务器的socket就绪了
            {
                //服务端接受客户端的链接，accept()返回接收到的客户端链接
                // accept (socket函数返回的socket，指向的定义的SOCKADDR_IN 结构体指针，指针大小值的地址)
                socklen_t size =sizeof( clientaddr );
                clientfd=accept(serverfd,(struct sockaddr*)&clientaddr,&size);
                cout<<clientfd<<"is connected"<<endl;
                //加入socket集合中
                for(int i=1;i<MAX_FD;i++)
                {
                    //如果socket集合中有可以使用的位置（socket集合未满）
                    if(clientarr[i].fd == -1)
                    {
                        //更新一下新接收到的socket
                        clientarr[i].fd = clientfd;
                        //设置监听读事件
                        clientarr[i].events=POLLIN;
                        break;
                    }
                }
                clientarr[0].revents=0;
            }
            else//如果是客户端的socket就绪了
            {
                //遍历查找是哪个clientfd就绪了
                for(int i=1;i<MAX_FD;i++)
                {
                    //如果这一位客户端值为0或者1,即客户端可用，不是未赋值状态
                    if(clientarr[i].fd != -1)
                    {
                        //如果当前客户端socket是就绪的,即已经被加入监听集合中
                        if(clientarr[i].revents==POLLIN)
                        {
                            //读取当前客户端传输过来的数据
                            int len=recv(clientarr[i].fd,buf,sizeof(buf),0);
                            if(len>0)
                            {
                                cout<<"get data"<<endl;
                                //如果读取到了数据,开始处理数据
                                int j=0;
                                while (len>j)
                                {
                                    //处理数据
                                    buf[j]=toupper(buf[j]);
                                    j++;
                                }
                                //处理数据完成后，发送数据
                                send(clientarr[i].fd,buf,len,0);
                                bzero(buf,sizeof (buf));
                                //就绪集合中需要将对应clientarr置为空，否则就绪集合中会一直为1,仍然在accept阻塞
                                clientarr[i].revents=0;
                            }
                            if (len==0)//如果此时客户端异常
                            {
                                //将他从监听集合中删去
                                //就绪集合中需要将对应clientarr置为空，否则就绪集合中会一直为1,仍然在accept阻塞
                                close(clientarr[i].fd);
                                clientarr[i].fd=-1;
                            }
                            break;
                        }

                    }
                }
            }
            nReady--;//每次执行结束后，将已经就绪的socket数量减少
        }
    }

    close(serverfd);
    close(clientfd);
    return 0;

}
```

# EPOLL模型

- 底层红黑树

## 关于EPOLL模型的API与类型:

### epoll_create 创建监听集合并制定监听数量

- `int epoll_create(int n)`
    - 初始化一棵具有n个节点红黑树,n表示能够监听的socket数量
    - 创建成功返回指向红黑树的文件描述符 epfd
    - epfd 也是 监听集合,可通过使用epfd来操作监听集合

### epoll_ctl 操作监听集合,返回就绪数量

- `epoll_ctl(int epfd,//红黑树的监听集合
EPOLL_CTL_ADD||EPOLL_CTL_DEL||EPOLL_CTL_MOD,//操作的方式
int socketfd,//要操作的socket
struct epoll_event*env//树节点类型
);`

### struct epoll_event 类型成员

- events:要监听的事件
    - EPOLLIN
    - EPOLLOUT
- data:要监听的socket

### epoll_wait返回就绪数量

- `epoll_wait(int epfd,//红黑树的监听集合
//就绪队列:传出就绪socket的数组
//最大就绪数量,一般等于就绪队列的长度
-1//监听方式,-1表示阻塞监听
);`
- 用于阻塞监听时间
- 不仅返回就绪数量还返回就绪的socket
- 监听集合

## EPOLL模型的优缺点：

### 优点：

1. EPOLL模型的监听集合突破了1024的大小限制
    1. 理论上电脑能创建多少个文件描述符（IO），EPOLL就能监听多少个IO事件,且不会增加系统开销
2. EPOLL模型采用非轮询机制,无轮询开销；
    1. EPOLL并未使用内核的IO设备等待队列,而是在内核底层自定义IO设备监听队列
    2. 因此监听机制并非轮询机制,不会因监听的IO事件过多导致系统性能处理下降,提升了效率，减小了开销
3. EPOLL模型会将就绪socket的数量和所有就绪的socket传出到就绪队列中
    1. 用户可以直接遍历处理已经就绪的IO事件，无需再次查找，使用简单
    2. 而SELECT和POLL模型仅返回已经就绪的IO事件数，需要不停遍历监听集合，自己找出已经就绪的事件，逻辑麻烦，浪费时间
4. EPOLL模型中无SELECT和POLL模型中的拷贝开销（将监听集合从用户空间拷贝至内核空间）的原因：
    1. EPOLL模型的监听集合采用红黑树的结构 并且监听集合是直接在内核空间中创建 而非用户空间中创建的变量，
    2. 每次设置一个监听事件的时候仅需定义一个节点，将其拷贝到内核空间，后挂载到内核空间的监听集合上；
    3. 即，select的监听集合被创建在用户空间，每次要创建监听事件时，需要先将整个监听集合创建在用户空间中
    4. 而EPOLL模型的监听集合被创建在内核空间，每次创建时间的时候，在用户空间中仅创建一个节点，拷贝此节点至内核空间，挂载到监听集合上
5. 当监听队列中有节点就绪时,采用了MMAP(内存共享映射)方式拷贝就绪队列,开销最小
    1. 当节点就绪时,内核中的监听集合(红黑树),将就绪节点弹出至内核中的就绪队列中
    2. 内核的就绪队列和用户空间中的就绪队列采用共享内存映射的方式,
        1. 一块数据改变,另一块立刻同步,速度快,拷贝开销小

### 缺点：

1. EPOLL大大提升了监听能力,但是处理数据效率上并没有改变,与Select和poll差不多
2. 红黑树的平衡操作可能会占用系统资源,使处理效率低于select和poll

## EPOLL的两种工作方式:作用于某一个待监听的socket节点

### 电平触发模式（关键字:EPOLLLT）(默认)

- 事件就绪时，内核缓冲区中的数据被读取拷贝至用户自定义缓冲区，进而处理事件
- 若此时内核缓冲区中的的数据并未一次性读取完毕，EPOLL会不断地向用户发送通知消息,直到才终止发送通知;
- EPOLLwait函数，阻塞函数，阻塞时监听，但如果上次的消息并未处理完成，则直接返回，不能使用EPOLL进行新的一轮读取监听

### 优点：

- 能保证数据全部被处理完成，不易丢失。

### 缺点：

- 系统开销较大

### 边缘触发模式（EPOLLET）（电平触发模式的一种优化）

- 事件就绪时，EPOLL仅发送一遍通知，无论数据是否被处理完成，不会再产生新通知
- 此时可以调用EOPOLLwait函数，进行新的一轮读取监听

### 优点：

- 无对内核缓冲区的反复检测，系统开销小。
- 数据处理快

### 缺点：

- 可能会丢失数据，需要由用户保证数据完整性
- （未处理的数据会被强制flush掉（刷新掉，消失））

### 如何设置EPOLL的工作方式

```
struct epoll_event env;
env.data.fd=severfd;
env.events=EPOLLIN
env.events=EPOLLET
```

## 代码示例:

```
#include<unistd.h>
#include<stdlib.h>
#include<string.h>
#include<sys/socket.h>
#include<arpa/inet.h>
#include<iostream>
#include<ctype.h>
#include<sys/epoll.h>//epoll模型需要的头文件

#define MAX_FD 8192
using  namespace std;
int main()
{
    //初始化网络信息
    struct sockaddr_in severaddr;
    struct sockaddr_in clientaddr;
    severaddr.sin_family =AF_INET;
    severaddr.sin_port =htons( 8000 );
    severaddr.sin_addr.s_addr= htonl( INADDR_ANY );//INADDR_ANY表示本机任意IP

    // 创建socket
    int serverfd =socket( AF_INET ,SOCK_STREAM , IPPROTO_TCP );

    //绑定，固定IP地址与端口号
    bind( serverfd , (struct sockaddr*)&severaddr , sizeof(severaddr) );
    listen( serverfd , 128 );//监听连接状态

    //等待客户端连接
    int clientfd;

    char ip[16];//声明IP地址
    bzero( ip , sizeof( ip ) );

    int port;//声明端口号
    printf("EPOLL SEVER ACCEPTING...\n");//打印提示信息

    //准备工作
    //定义一个待处理的数据
    char buf[1500];
    bzero( buf , sizeof( buf ) );
    int i;
    int j;

    //创建Epoll监听集合
    int epfd = epoll_create(MAX_FD);
    //定义已就绪的socket数量
    int nReady=0;
    //定义EPOLL就绪队列
    struct epoll_event envs[MAX_FD];
    //定义一个操作使用的临时节点（添加/修改）
    struct epoll_event env;
    //将服务器的节点的值加入临时节点中
    env.data.fd=serverfd;
    env.events=EPOLLIN;
    //添加服务器节点进入监听集合中
    epoll_ctl(epfd,//监听集合
              EPOLL_CTL_ADD,//操作方式
              serverfd,//操作的socket
              &env//操作的监听集合节点
              );
    while(1)
    {
        //循环进行监听事件
        nReady = epoll_wait(epfd,//监听集合
                            envs,//传出的就绪队列
                            MAX_FD,//最大就绪数，就绪队列长度,一般等于监听队列长度，也等于监听集合创建大小
                            -1//返回时间，阻塞监听：-1
                            );
        if (nReady == -1)
        {
            perror("epoll error:");
            return 0;
        }
        while(nReady)//如果此时传出集合中已经有就绪的socket，即nReady大于0
        {
            //通过epoll_wait后，开始检测传输的就绪队列
            //需要遍历就绪队列
            int i=0;
            //判断是哪个socket就绪了，看看是谁闲下来，可以接收连接了
            if(envs[i].data.fd==serverfd)//如果是服务器的socket就绪了
            {
                //服务端接受客户端的链接，accept()返回接收到的客户端链接
                // accept (socket函数返回的socket，指向的定义的SOCKADDR_IN 结构体指针，指针大小值的地址)
                socklen_t size =sizeof( clientaddr );
                clientfd=accept(serverfd,(struct sockaddr*)&clientaddr,&size);
                cout<<clientfd<<"is connected"<<endl;
                //加入socket集合中
                //1.制作好要添加的节点（使用临时节点完成）
                env.data.fd=clientfd;
                //1.1这里可以设置添加客户端的监听方式（LT，ET）
                //EPOLLIN是监听事件
                env.events=EPOLLIN;//设定水平触发模式 Level Trigger
                //env.events = EPOLLIN | EPOLLET;//设定边缘触发模式 Edge Trigger
                //2.将客户端节点拷贝进监听集合中
                epoll_ctl(epfd,//监听集合
                          EPOLL_CTL_ADD,//操作方式
                          clientfd,//操作的socket
                          &env//操作的监听集合节点
                          );
            }
            else//如果是客户端的socket就绪了
            {
                //如果当前客户端socket是就绪的,即已经被加入监听集合中
                //在监听集合中选取对应的节点进行读取
                //客户端正常运行读取当前客户端传输过来的数据
                int len=recv(envs[i].data.fd,buf,sizeof(buf),0);
                if(len>0)
                {
                    cout<<"get data"<<endl;
                    //如果读取到了数据,开始处理数据
                    int j=0;
                    while (len>j)
                    {
                        //处理数据
                        buf[j]=toupper(buf[j]);
                        j++;
                    }
                    //处理数据完成后，发送数据
                    send(envs[i].data.fd,buf,len,0);
                    bzero(buf,sizeof (buf));
                }
                if (len==0)//如果此时客户端异常
                {
                    //将客户端从监听集合中删去
                    epoll_ctl(epfd,EPOLL_CTL_DEL,envs[i].data.fd,NULL);
                    close(envs[i].data.fd);
                }
            }
            nReady--;//每次执行结束后，将已经就绪的socket数量减少
            i++;//继续向下遍历就绪队列
        }
    }

    close(serverfd);
    close(clientfd);
    return 0;
}
```

工作流程： 从客户端发送消息至多路IO监听 EPOLL进行事件监听，如果监听到了读事件，则处理就绪，

线程分为用户级线程和内核级线程 用户级的多线程是不能？？？，按照进程分配CPU，尽管如此，用户级的多线程效率仍然高于单线程的工作效率 内核级线程若系统下支持内核级线程，每一个内核级线程都可以。。。

常用的API所产生的线程基本都是用户级线程。

服务器测压思路 :

客户端中循环创建socket,向服务器发送请求,服务器接收到请求后连接数量+1