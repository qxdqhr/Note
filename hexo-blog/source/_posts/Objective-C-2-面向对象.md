---
title: Objective-C-2-面向对象
date: 2022-07-04 21:22:11
categories: Objective-C
tags:

---

# 如何定义一个 OC类？

-  类的定义分为两个部分：类的声明/实现

- 类的声明：一般写在.h文件中

  ~~~
  @inteface 类名 : NSObject
  {
  		类成员变量声明
  }
  方法的声明写在这里
  @end
  ~~~

- 类的属性名 必须要以下划线开头

- 类的实现：一般写在.m文件中

  ~~~
  @implementation 类名
  
        将方法的实现写在这里
  
  @end
  ~~~

# 如何创建 OC 类的对象？

- ~~~
  类名 *对象名 = [类名 new];
  ~~~

- 



