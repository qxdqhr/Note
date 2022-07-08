---
title: Objective-C-6-语言特性-构造方法
date: 2022-07-06 21:22:11
categories: Objective-C
tags:

---

# new 方法是什么?

- 用于创建对象

- new实际上是1个类方法 其中进行的操作:

  - 创建对象:调用的alloc方法
    - alloc 方法:分配空间并创建对应类的对象
  - 初始化对象:	调用的init方法

  - 返回对象地址

- 使用未经初始化的对象是极其危险的.千万不要这么做.

 ~~~objective-c
    Person *p1 = [Person new]; //  类名 *指针名 = [类名 new];
    //完全等价于
    Person *p1 = [[Person alloc] init];
 ~~~

# init方法是什么? 

- 作用: 初始化对象,为对象的属性赋初始值/默认值
- init方法也被叫做构造方法,在调用 new 方法创建对象时会自动调用对应类的构造方法
  - 即使创建对象时没有为属性赋值,这些属性都会被设置为默认值
- 属性的类型是:
  - 基本数据类型,赋值为0
  - C指针,赋值为NULL
  - OC指针,赋值为nil

# 如何让创建的对象默认值不是 0 或 nil ?

- 重写init方法.并为对象的对应属性赋值
- 每次调用 new 方法创建的对象都会使用 init 中的赋值

##  重写init方法的规范

 ~~~objective-c
 - (instancetype)init
 {
     if(self = [super init])
       //先调用父类的init方法,并判断父类(对应属性)是否初始化成功
       //调用init方法 初始化失败会返回 nil
     {
        //当前对象属性赋值
     }
     return self; //最后 返回self的值
 }
 ~~~

## 为什么要调用父类的init方法?

- 因为父类的init方法 会初始化父类的属性,必须要保证当前对象中的父类属性也同时被初始化.

## 为什么要赋值给self？

- 因为 调用父类的init方法 会返回初始化成功的父类属性的对象
- 实际上返回的就是当前对象。但是我们要判断是否初始化成功.



# 如何通过 init 方法创建属性值不同的对象?

- 重写init方法后,每次创建出来的对象的属性的值都是一样的

-  创建对象的时候,对象的属性的值不应写死在init方法中

- 使用自定义构造方法创建对象

 ~~~objective-c
 - (instancetype)initWithName:(NSString *)name andAge:(int)age
 {
     if(self = [super init])
     {
         self.name = name;
         self.age = age;
     }
     return self;
 }
 ~~~

  ## 自定义构造方法注意:

1. 自定义构造方法的返回值必须是instancetype
2. 自定义构造方法的名称必须以initWith开头
3. 方法的实现和init的要求一样
4. 调用自定义的构造方法时,不应直接使用 new,应先alloc 再调用自定义的initWith

