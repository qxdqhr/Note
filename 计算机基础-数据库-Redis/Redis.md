# 安装Redis:

## step1:下载源码压缩包

wget http://download.redis.io/releases/redis-3.2.8.tar.gz

##　step2:解压

tar -zxvf redis-3.2.8.tar.gz

## step3:复制redis目录

将解压好的redis源码包放到usr/local/redis⽬录下

sudo mv ./redis-3.2.8 /usr/local/redis/

## step4:进⼊redis目录

cd /usr/local/redis/

![image-20210418072829769](C:\Users\qhr\Desktop\Redis.assets\image-20210418072829769.png)

## step5:编译redis程序

### 5.1:安装C语言编译器GCC

sudo apt-get install gcc

### 5.2:安装编译命令make

sudo apt-get install make

### 5.3:使用make命令编译redis

在当前 /usr/local/redis/目录下直接使用make命令编译

sudo make

## step6:安装redis的命令

将redis的命令安装到/usr/local/bin/⽬录,在 /usr/local/redis/ 直接执行如下命令即可

sudo make install

## step7:测试是否安装成功

进入目录/usr/local/bin中查看

a)    redis-server   redis服务器

b)    redis-cli     redis命令行客户端

c)    redis-benchmark redis性能测试工具

d)    redis-check-aof  AOF文件修复工具

e)    redis-check-rdb  RDB文件检索工具

![image-20210418073620262](C:\Users\qhr\Desktop\Redis.assets\image-20210418073620262.png)

## step8:复制配置文件

创建/etc/redis/目录

 mkdir /etc/redis/ 

将原有的redis.conf复制到新目录中

sudo cp /usr/local/redis/redis.conf /etc/redis/

## step9:查看配置文件

sudo vi /etc/redis/redis.conf

### 重要内容：

- bind 127.0.0.1

  - 绑定ip：如果需要远程访问，可将此⾏注释，或绑定⼀个真实ip

- port 6379		 

  - 端⼝，默认为6379

- daemonize yes		

  - 是否以守护进程运⾏ 
    - 以守护进程运⾏(yes 推荐)，不会在命令⾏阻塞，类似于服务
    - 以⾮守护进程运⾏(no)，则当前终端被阻塞

- dbfilename dump.rdb

  - 数据⽂件

- dir /var/lib/redis      

  -  数据⽂件存储路径
  -  这个路径 可以是自己创建的 
  - mkdir /var/lib/redis

- logfile /var/log/redis/redis-server.log

  - ⽇志⽂件
  - 这个文件 可以是自己创建的 
  - mkdir /var/log/redis  
  - vim /var/log/redis/redis-server.log 

- database 16

  - 数据库数量，默认有16个

- slaveof

  - 主从复制，类似于双机备份。

  

## step10:启动redis服务器

- redis是C/S架构应用程序，所以要先启动Redis服务器
- **sudo redis-server /etc/redis/redis.conf**

## step11:查看redis服务器运行状况

- ps -aux|grep redis 
  - 查看redis服务器进程
  - 可使用 kill -9 进程号 杀死服务端进程

## step12:启动redis客户端

- redis-cli

## step13:测试redis客户端是否能链接服务器

- ping

![image-20210418092330656](C:\Users\qhr\Desktop\Redis.assets\image-20210418092330656.png)

# 安装Redis图形界面：

## 方法1：snap（要求较快网速）

终端输入： sudo snap install redis-desktop-manager

等待下载完成后即可启动

## 方法2：deb安装包

安装的时候，可能会提示需要几个依赖包，也可能提示依赖包不在当前的网络源中

- 更新下载源 
  - 修改/etc/apt/sources.list文件
  - apt-get update
- 安装缺少的依赖包（举例，可能缺少的包有多个，依次安装）
  - sudo apt-get -f install libicu52
  - 也可以依照对应缺少的依赖包名，在网站中下载.deb安装包
    - https://packages.ubuntu.com/bionic/amd64/zlibc/download
    - 下载依赖包的时候注意依赖包与当前系统的相容性(系统版本，系统位数)
    - https://blog.csdn.net/momomomomm/article/details/83626147
- 最后使用命令安装图形界面
  - sudo dpkg -i redis-desktop-manager_0.8.3-120_amd64.deb
- 遇到问题：
  - **无法安装 /lib/x86_64-linux-gnu/libpng12.so.0 的新版本: 没有那个文件或目录**（Ubuntu 19/20出现）
  - sudo add-apt-repository ppa:linuxuprising/libpng12
  - sudo apt update
  - sudo apt install libpng12-0



编译时报错函数无法识别未定义:库文件未导入

运行时只闪一下或无法启动:可能缺少动态库文件

# Redis 的开发库安装:lhiredis

## step1:解压lhredis压缩包

- 可以解压在任意文件夹

## step2:编译lhredis

- 使用make命令
- 在解压后的文件夹中执行

## step3:安装lhredis

- 使用make install命令
- 安装后	开发库在  /usr/local/lib/libhiredis.so

## step4:使用C++程序连接lhredis

### step4.1:先需要保证Redis数据库中有数据

- 启动redis服务器
  - **sudo redis-server /etc/redis/redis.conf**
- 启动redis客户端
  - **redis-cli**
- 执行插入数据命令
  - **set name harry**

### step4.2:使用Qt测试

- 新建qt控制台项目

- 在pro文件中包含库文件

  - LIBS += -lhiredis

- 在主函数中复制相关测试代码

  ```
  #include <QCoreApplication>
  #include <iostream>
  #include <hiredis/hiredis.h>
  using namespace std;
  int main(){
      redisContext *c = redisConnect("127.0.0.1",6379);
      if(c->err){
         redisFree(c);
         cout<<"connect to redis fail"<<endl;
         return 1;
      }
      cout<<"connect to redis success"<<endl;
      redisReply *r = (redisReply*)redisCommand(c,"get name");
      cout<<r->str<<endl;
      redisFree(c);
      while(1);
      return 0;
  }
  ```

  

### step4.3:使用命令行gcc测试

点击中⽂官⽹查看命令⽂档 http://redis.cn/commands.html

string类型

字符串类型是Redis中最为基础的数据存储类型，该类型可以接受任何格式的数据，如JPEG图像数据或Json对象描述信息等。在Redis中字符串类型的Value最多可以容纳的数据长度是512M。

# Redis相关命令

## 设定键值

- 设定一般键值	set key value
- 设置多个键值	mset key1 value1 key2 value2 ...
- 设定限制时间的键值(过期后自动清除对应键值,以秒为单位)	setex key seconds value
- 查看键值的剩余时间	ttl key 
- 

## 获取键值(以键查值)

- get 

## 追加键值

## 查看键值

- key +键值
- 

删除键值

del + 键值





## 编码格式: UTF-8

## 中文乱码问题

- 退出,再进入redis客户端

```
Exit
Redis-cli --raw
```

## SDS结构

获取sds长度 直接取得成员len,buf地址向前偏移8个字节

扩容时,每次扩大最终长度的2倍(小于1M)

原来:25 扩容后 51(25*2+1):1表示\0

兼容多种数据的原因:每次读取数据时仅依照len来读取数据,即使遇到\0也会继续读取

## 链表结构

类似于STL中的双向链表

迭代器的好处:适用于泛型数据统一使用迭代器遍历,并规范化操作隐藏了内部的数据提升了安全性,便于理解增强可读性

左侧插入:抓住待插入的链表头从左边向结构中插入,所以是逆序插入

右侧插入:抓住待插入的链表头从右边向结构中插入,所以是正序插入

源码文件:adlist.h与adlist.c

### 链表结构快速查找到节点(链表的优化)

hash

map

应用于LRU淘汰算法中 hsash表+双向链表

### 头插入时,如何省略判断链表头或尾的操作

头尾哨兵节点

## 字典结构

- 字典结构维护**redis中的所有key到value的映射**
- 字典结构维护**所有hash类型的键值**

### 哈希表结构

redis中哈希表定义在dict.h/dictht中。 

```
typedef struct dictht { //哈希表
  dictEntry **table;   //存放一个数组的地址，数组存放着哈希表节点dictEntry的地址。
  unsigned long size;   //哈希表table的大小，初始化大小为4
  unsigned long sizemask; //用于将哈希值映射到table的位置索引。它的值总是等于(size-1)。
  unsigned long used;   //记录哈希表已有的节点（键值对）数量。
} dictht;
```

### 哈希表节点结构

哈希表的table指向的数组存放这dictEntry类型的地址。也定义在dict.h/dictEntryt中。 

```
typedef struct dictEntry {
  void *key;         //key
  union {
    void *val;
    uint64_t u64;
    int64_t s64;
    double d;
  } v;            //value
  struct dictEntry *next;   //指向下一个hash节点，用来解决hash键冲突（collision）
} dictEntry;
```

 

## 跳跃表结构

### 跳跃表的特性

平均时间复杂度logN

是有序链表

通过建立多级索引来实现

### 设计跳跃表

#### 插入节点

找到节点的位置

更新索引

如何更新索引:随机数

判断更新几级索引的伪代码

```
while(random()%1&& k<=索引上限)
{
	k++;//索引数
}
```

插入节点

#### 删除节点

删除节点及其索引

重新连接索引

string(SDS) hash(大:字典,小:压缩列表(旧3.2前),快速列表(新3.2后)) set(存整数:整数集合) zset(hash+跳表) list(双向链表)

快速列表

HASH结构:仅能替代程序中的map映射,查询比数据库快