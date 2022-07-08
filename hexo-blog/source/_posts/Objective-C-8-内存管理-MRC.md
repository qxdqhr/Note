---
title: Objective-C-8-内存管理-MRC
date: 2022-07-07 11:27:10
categories: Objective-C
tags:
---

# MRC 和 ARC 是什么意思?

- MRC: Manual Reference Counting 手动引用计数.手动内存管理.
  - 要求程序员手动的管理内存(发送retain消息 或 relase消息)
  - 早期的APP开发使用的MRC技术

- ARC: Automatic Reference Counting 自动引用计数.自动内存管理
  - 系统自动的在合适的地方发送retain relase消息
  - ARC是基于MRC
  - iOS5开始. Xcode4.2开始就支持ARC,Xcode7 默认支持ARC开发

# 引用计数器是什么?

- 为了让系统知道何时需要将某个对象所占用的内存清理掉,系统引入了引用计数器的概念
- 每个对象都有1个叫做retainCount的属性
- 这一属性叫做引用计数器
- 类型是unsigned long 占据8个字节

## 引用计数器有什么作用?

- 记录当前对象有多少个人在使用它.   
- 默认情况下,创建1个对象后,其引用计数器的默认值是1
- 当多1个人使用这个对象的时候.应该先让这个对象的引用计数器的值+1 代表这个对象多1个人使用.
- 当这个对象少1个人使用的时候.应该先让这个对象的引用计数器的值-1 代表这个对象少1个人使用.
- 当这个对象的引用计数器变为0的时候.代表这个对象无人使用. 这个时候系统就会自动回收这个对象.

## 如何操作引用计数器?

- 每多1个人使用对象时,为对象发送1条retain消息. 对象的引用计数器就会加1
- 每少1个人使用对象的时候,为对象发送1条release消息.对象的引用计数器就会减1
- 为对象发送1条retainCount消息. 就可以获取到对象的引用计数器的值
- 就这样++ -- 当对象的引用计数器变为0的时候,对象就会被系统立即回收,并自动调用对象的dealloc方法. 

##  重写dealloc方法的规范:

- 必须要调用父类的dealloc方法. 并且要放在最后一句代码.

# 野指针是什么?

-  OC中的野指针: 
  - 指针指向的对象已经被回收

-  C语言中的野指针: 
  - 定义1个指针变量且没有初始化
  - 这个指针变量的值指向1块随机的空间

# 对象回收的是怎样的?

- 回收对象后,对象占用的空间可以分配给别人
- 当这个对象占用的内存空间没有分配给别人之前 其实对象数据还在

## 内存回收的本质是怎样的?

- 申请1个变量,实际上就是向系统申请指定字节数的空间.这些空间系统就不会再分配给别人了.
- 当变量被回收的时候,代表变量占用的字节空间从此以后系统可以分配给别人使用了.
- 但此时字节空间中存储的数据还在.

# 僵尸对象是什么?

- 已经被释放的对象,但是这个对象所占的空间还没有分配给别人.这样的对象叫做僵尸对象.

- 通过野指针去访问僵尸对象的时候:
  - 当僵尸对象占用的空间还没有分配给别人的时候.这是可以的
  - 当僵尸对象占用的空间分配给了别人使用的时候 就不可以
  - 因此,只要对象称为了僵尸对象,无论如何 都不允许访问 

- 编译器支持 僵尸对象的实时检查机制 
  - 打开之后 只要访问的是僵尸对象,无论空间是否分配 就会报错
  - 但默认状态下僵尸对象检测,不会打开,由于僵尸对象检测打开后,每访问1个对象 都会先检查这个对象是否为僵尸对象,极其消耗性能
- 释放过的僵尸对象不能动态回复

# 如何避免野指针访问僵尸对象?

- 当1个指针的空间被回收后,将这个指针的值设置nil

- nil指针调用对象的方法(包括使用点语法)时,不会报错. 只是没有任何反应
  - 但nil 指针不能直接访问属性,会报错.

# 内存泄露是什么意思?

- 指的是1个对象没有被及时的回收.会一直驻留在内存中,直到程序结束的时候才回收
- 这种内存空间,既不能被使用,也不能被回收,不能再被访问到,使得进程中可利用的内存变少,所以被称为内存泄漏

##  单个对象会在什么时候发生内存泄露?

- 有对象的创建,而没有对应的relase

- retain的次数和relase的次数不匹配

- 在不适当的时候,为指针赋值为nil
- 在方法中为传入的对象进行不适当的retain

## 如何保证单个对象可以被回收,规避内存泄漏?

- 有对象的创建 就必须要匹配1个relase

- retain次数和release次数一定要匹配

- 只有在指针称为野指针的时候才赋值为nil

- 在方法中布要随意的为传入的对象retain

# MRC 模式下,当属性为OC对象时,setter方法的写法

- 对象一般都放置在堆区,因此以对象作为属性时,也要遵守 MRC 手动回收内存的原则
- 将参数赋值给当前对象的属性,代表
  - 属性原值要被删除:	原对象需要先释放	为原对象发送一个 release 消息
  - 属性新值需要被存储:	参数对象要被存储	为参数对象发送一个 retain 消息 
  - 属性新值赋值:	将参数对象赋值到类属性中

- 当对象销毁时,代表属性指向的对象应被释放. 就应该在dealloc中relase

~~~objective-c
- (void)setCar:(Car *)car
{
		[_car release];
		_car = [car retain];
}
- (void)dealloc //MRC 下需要重写dealloc,手动释放内存
{
    [_car release];
    [super dealloc];
}
~~~

# 循环引用是什么意思?

- 当两个类相互包含时,会出现循环引用的问题. 会造成无限递归,而导致无法编译通过
  -  Person.h 中 包含(#import) Book.h 同时 Book.h 中 包含(#import) Person.h

## 如何打破循环引用?

1. 将 A.h 中的 #import "B.h" 更换为 @class B; 
2. 在 A.m 文件中 添加  #import "B.h"

#  @class与#import的区别?

- #import是将指定的文件的内容拷贝到写指令的地方
- @class 并不会拷贝任何内容. 而是令编译器在编译的时候才可以知道xxx是1个类,防止循环引用的产生

# MRC 标准的代码如下:

~~~objective-c
//---Person.h
#import <Foundation/Foundation.h>
@interface Person : NSObject
{
    //NSString *_name;
}
//- (void)setName:(NSString *)name;
//- (NSString *)name;
@property(nonatomic,assign)NSString *name; 

@end

//---Person.m
#import "Person.h"
@implementation Person

- (void)dealloc
{
    [_name release]; //释放掉属性
    [super dealloc]; //调用父类 dealloc
}

~~~

# 自动释放池是什么?

-  一种代码结构
- 当自动释放池被销毁时,会自动调用存储在池中的所有对象的release方法
- 将创建的对象存储到自动释放池中,不需要再写release

## 解决了什么问题?

-   将对象存入到自动释放池中. 就不需手动relase这个对象了,减少了代码量

~~~
@autoreleasepool
{
	//自动释放池的范围
 
}
~~~

## 如何使用自动释放池?

### 将对象存储到自动释放池中:

- 在自动释放池之中调用对象的autorelease方法,写法如下:

~~~
@autoreleasepool
{
	Person *p1 = [[[Person alloc] init] autorelease];//autorealse方法返回的是对象本身
	Person *p1 = [[Person new] autorelease];//autorealse方法返回的是对象本身

}
~~~

- 当这个自动释放池执行完毕之后,就会立即为这个自动释放池中的对象发送1条release消息

### atuoreleasepool 添加对象注意:

- 自动释放池中调用对象的autorelease方法,这个对象才会被存储到这个自动释放池之中
- 对象可在自动释放池外创建,并在自动释放池中调用对象的autorelease方法,才可将这个对象存储入当前这个自动释放池中

- 自动释放池结束时只是向存储在其中的对象发送1条release消息 而不是销毁对象
  - 对象的 dealloc 中对应属性仍应该正常 release,与自动释放池无关

### 向自动释放池中存储对象时,对象的引用计数不会增加:

- 自动释放池中,对于一个对象,应只autorelease1次
  - 多次向同1个对象发送autorelease消息,会将此对象多次存储到自动释放池中
  - 自动释放池结束时,会为对象发送多条release消息,此时对象的引用计数仍是 1,会出现僵尸对象错误

- 自动释放池中,不应调用了存储到自动释放中的对象的release方法
  - 在自动释放池结束的时候,还会再调用对象的release方法,引用计数已经为 0,会出现野指针错误
- 自动释放池中的对象的retain方法,记得 release

### 自动释放池可以嵌套

- 调用对象的autorelease方法,会讲对象加入到当前自动释放池之中
- 只有在当前自动释放池结束的时候才会像对象发送release消息

~~~objective-c
@autoreleasepool
{
    Person *p1 = [[[Person alloc] init] autorelease];
    @autoreleasepool
    {    
        Person *p2 = [[[Person alloc] init] autorelease];       
        @autoreleasepool
        {
             Person *p3 = [[[Person alloc] init] autorelease];
        }//p3发送 release
    }//p2 发送 release
}//p1 发送 release  
~~~

# 类方法是什么?

- 可以使用类名来调用的类所属方法,声明与实现时以+开头

## 自定义构造类方法:

- 对于一个类,需要提供**与自定义构造方法相同功能的类方法**    且 在这一类方法中初始化的对象需要调用 autorelease
  - 创建对象时,可以直接使用这种类方法来创建对象
  - 这种写法保证了 在自动释放池中, 调用类方法来创建的对象会被自动的加入到自动释放中
  - 这种写法是 Apple 的编程规范
- 格式如下:

~~~Objective-C
//--- 声明
- (instancetype)initWithName:(NSString *)name andAge:(int)age andWeight:(float)weight;    //实例方法
+ (instancetype)pig;                                                                      //类方法
+ (instancetype)pigWithName:(NSString *)name andAge:(int)age andWeight:(float)weight;     //类方法
//--- 实现
- (instancetype)initWithName:(NSString *)name andAge:(int)age andWeight:(float)weight
{		//自定义构造方法
    if(self = [super init])
    {
        _name = name;
        _age = age;
        _weight = weight;
    }
    return self;
}
+ (instancetype)pig
{
    return [[[self alloc] init] autorelease];
}
+ (instancetype)pigWithName:(NSString *)name andAge:(int)age andWeight:(float)weight
{
  	//类方法分配空间,然后调用已存在的自定义初始化方法
  	//初始化对象后还需要为对象调用 autorelease
    return [[[self alloc] initWithName:name andAge:age andWeight:weight] autorelease];
}
~~~

# OC 中结构体和类的区别?

## 属性+方法 = 类

- 结构体只能封装属性
- 类不仅可以封装属性还可以封装方法
  -   如果1个封装数据既有属性也有行为,只能用类.

 ## 分配内存位置

-  结构体变量分配在栈
  - 栈的空间相对较小.但是存储在栈中的数据访问效率相对较高
- OC对象分配在堆
  - 堆的空间相对较大.但是存储在堆中的数据的访问效率相对较低

- 如果1个封装数据只有属性
  - 如果用结构体就会分配在栈 效率就会高
    - 如果这个结构体中有很多个属性,结构体变量在栈中就会占据很大空间 反而会降低效率
  - 如果使用类 对象就分配在堆 效率相对就会低

## 赋值方式

- 结构体赋值是 直接赋值
- 对象的指针 赋值的是对象的地址.

## 总结

- 什么时候使用结构体:
  - 封装数据只有属性 
  - 属性较少. 3个以下
- 什么时候使用类: 
  - 封装数据既有属性也有行为
  - 只有属性 但是属性较多.

 

 

 

 
