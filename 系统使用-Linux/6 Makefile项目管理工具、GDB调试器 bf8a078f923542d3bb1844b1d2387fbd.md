# 6.Makefile项目管理工具、GDB调试器

### Makefile项目管理工具

### 概述：

- Linux下使用Makefile管理项目,
- 开发者通过Makefile语言编写出Makefile脚本，并使用该脚本管理编译项目
- IDE(集成开发环境)中使用build工具管理项目

### GNU工具链：是开发者必须掌握的工具链

- 调试器：GDB
- 编译器：gcc
- 编辑器：Vim
- 项目管理：Makefile
- 链接器：LD

### Makefile项目管理工具的作用：

- 节省编译时间(优势)，
- 能够自动编译源代码
- 便于管理编译关联源代码，一次编写终身受益（复用性极强）

### Makefile本质：

- 项目管理脚本语言，用于编写项目管理脚本程序
- 在进行项目管理时，使用Makefile语言编写的脚本程序以工作

### 编译时间长的原因：

- 项目编译时期生成二进制文件和中间文件占有极大时间

### 一个项目的编译流程：

1. 生成可重新定位的二进制文件
2. 通过Id链接器，将.o文件链接
3. 生成可执行程序

### Makefile脚本如何节省时间：

- 每重新编译项目时Makefile检测==是否有文件发生改动==
- 仅重新编译生成改动文件及其相关文件
- 使新文件与原有文件链接
- 无需再次编译已生成的文件，大幅节省编译时间。

### Makefile脚本的三要素：

- 目标：目标文件，这里为编译过后的文件（要得到谁）
- 依赖：编译出自目标文件所需要的源文件 （通过谁）
- 命令：依赖执行何种操作能够得到目标 （怎么做）

### Makefile脚本的格式：

```
目标：依赖项A 依赖项B 依赖项C
    命令

app：while.c
    gcc while.c -o app
```

- 注意:命令前的缩进==必须使用tab缩进==，不能使用空格代替，缩进后命令会变色

### Makefile脚本的编写：

- 创建一个Makefile脚本文件：
    - 可直接创建，Makefile脚本文件无后缀 （**vi Makefile**）
    - 文件名只能由字母构成，且仅忽略首字母大小写。

### 执行Makefile脚本文件：

- 写好Makefile脚本文件后，在Makefile所在目录下 直接使用 make命令 即可完成编译项目的工作
- **make命令**能够 识别并执行 当前目录下的Makefile脚本文件
    
    ### Makefile示例：使用Makefile脚本编译一个项目
    
    ### 项目示例：简单四则运算项目
    
- Linux/Unix项目框架：
    - Makefile脚本文件
        - include：存放头文件的目录
        - lib： 存放库文件的目录(静态库和动态库文件)
        - src： 存放源代码的目录
        - 缓存目录
        - 配置文件目录
- 注意：
    - 框架中的Makefile脚本文件，与src源代码目录中的Makefile脚本文件是不同的;
    - makefile中使用的命令和在终端中使用命令的过程是相同的
    - 

### 项目代码：

### 头文件test.h

(test.h文件放在include目录下)

```
#include<stdio.h>      //c标准输入输出
#include<stdlib.h>     //c标准库
#include<unistd.h>     //Unix标准库

int add(int ,int);     //四个函数的声明
int des(int ,int);
int mul(int ,int);
int sub(int ,int);
```

### 源文件 add.c des.c mul.c sub.c main.c

五个函数的实现源代码文件定义在src目录中：

```
add.c

  #include<test.h>
  int add(int a,int b)
  {
    return a+b;
  }

des.c

  #include<test.h>
  int des(int a,int b)
  {
    return a-b;
  }

mul.c

  #include<test.h>
  int mul(int a,int b)
  {
    return a*b;
  }

sub.c

  #include<test.h>
  int sub(int a,int b)
  {
    return a/b;
  }

main.c

  #include<test.h>
  int main(void)
  {
    printf("add:%d\n",add(199,6));
    printf("sub:%d\n",sub(199,6));
    printf("mul:%d\n",mul(199,6));
    printf("des:%d\n",des(des,6));
    return 0；
  }
```

示例项目文件层级树如下：

```
---include
   ---test.h
---lib
---Makefile
---src
   ---add.c
   ---des.c
   ---main.c
   ---Makefile
   ---mul.c
   ---sub.c
```

项目完成后，使用命令方法编译：

```
gcc*.c -I(+头文件目录路径) -o app
```

- **.c** : * 为通配符，表示全部的.c文件 -o：指定生成文件名 -I:指定头文件目录
- **.c** : * 为通配符，表示全部的.c文件 -o：指定生成文件名 -I:指定头文件目录

### 能够管理项目的Makefile脚本

- 第一版，最简单的Makefile,由三要素构成的脚本,能够编译单个文件
    
    ```
    app：add.c des.c mul.c sub.c main.c
        gcc *.c -I../include -o app
        //直接按照格式书写，不能节省编译时间。
    ```
    
    - 注意：
        1. 为通配符，仅在终端上作为命令可以使用，不适用于Makefile脚本语言中
        2. 命令使用shell语言，命令中可使用*通配符。
        3. 通配符表示选取多个文件均包含某部分文件名
        4. 此时如果仅修改单独一个.c文件,makefile脚本,仍会重新编译全部的.c文件;并不能节省编译时间;
            1. 原因:此时使用make命令后,在原文件目录下不存在.o的链接文件(系统默认编译后即删除),故无法进行比较,从而无法节省时间;
- 第二版 可节省时间，但复用性低
    
    ```
    app：add.o des.o mul.o sub.o main.o
        gcc *.o -I../include -o app
    add.o:add.c
        gcc -c add.c
    ```
    

完成后使用make命令出现如下结果

更改add.c中代码后再次执行make命令 若仅打印出编译add.c文件的行 说明只重新生成有变化的.c文件

生成文件时使用头文件 预编译时将头文件解包，直接粘到源代码所在的地方（完整的头文件）

Makefile运行原理： 自顶向下建立依赖关系，执行时自底向上执行命令 先确定目标，再去执行;类似于递归（个人见解）

第三版 提高复用性 解决方法： 定义一些变量以存储不同项目中近似的部分，如：路径，库名..等 这样针对于不同文件，只需更改变量中的文件名即可使用原来的Makefile代码 从而提高了代码的复用性 需要功能： 使用Makefile脚本语言函数 函数名后加空格再加参数 几个需要用到的函数： 文件名获取函数

使用wildcard函数获取所有.c文件的文件名 对此函数取值赋给FILENAME(取值符号为$,用法可近似理解为取地址符号) 字符串替换函数

TODO： Makefile变量：默认情况下存储字符串 变量的的定义：所有变量名均大写 变量的赋值：变量名=所赋的值 当使用变量的值时要使用取值符＄，仅使用变量名赋值无意义 常使用的变量 CC 存放编译器的变量
CFLAGS 编译选项 -I../include 指定头文件路径 -g
-Wall开启严格编译 -c CPPFLAGS 预处理选项 LDFLAGS 库路径及库名 -L../lib库路径 -l 库名 INCLUDE 头文件路径 INCLUDE=../include TARGET 最终程序名 TARGET=app 三个特殊变量： ＄@ 当前目标 ＄^ 所有依赖 ＄< 当前依赖中的第一个

Makefile内建语法： %是Makefile语言的通配符

默认情况下： 当出现多个目标时：多个目标存在依赖关系时可视为一个目标 由目标的先后顺序执行且只会执行一个目标 无依赖的目标被称为功能目标 使用make+功能名 output: 输出信息 clear 清除目标： 删除程序文件和中间文件 install 安装：将编译生成的程序拷贝到/usr/bin Linux 安装程序三种方法 Appget 在线安装 第一闭包 源码安装 distclear 卸载：

GDB调试器 基本概述： 可以让开发者，在程序运行时暂停或其它操作，快速定位检测错误原因以及程序的坏点(BUG调试) 常见的调试工具类型： 1.图形化调试工具（更友善） GUI eg：VS的调试器 消耗大量系统资源，速度慢 简单上手 2.命令调试工具（更快） GDB 仅使用命令进行调试 无额外开销，速度快 较为复杂 计算机领域中的“三个虫子”： ①蠕虫病毒：网络安全 ②爬虫：数据分析，数据可视化，数据挖掘 搜索引擎（离不开爬虫） ③BUG（软硬件错误坏点）：调试器用来查找软件中的异常错误和坏点 GNU工具链：GCC MAKEFILE VIM LD GDB

GDB命令： gdb 只能调试带有-g 的app文件 gcc- g 编译时添加调试信息

断点编号是随机分配 VS可以查看