---
title: Objective-C-3-语言特性-SEL消息
date: 2022-07-05 21:22:11
categories: Objective-C
tags:
---

# OC中类的实际形态是如何的？

- 类是以Class对象的形式存储在代码段之中.
- OC 中，一个类 被认为是 元类的对象

类名:存储的这个类的类名. NSString 

方法存储在类对象之中.如何将方法存储在类对象之中.

# OC中的SEL是什么？

- 叫做 selector 选择器
- 是一种变量类型，所以要在内存中申请空间存储数据.
- 转定义后，SEL本质是1个结构体. 
- **SEL结构体变量用于存储消息.类似于函数指针**
  - 消息类似于方法，OC中调用方法一般被称为发送消息
- 使用SEL对象类发送消息 使编译器不会验证这个方法是否声明，直接向对象发送消息
- 一般作为Class对象 的属性，用于将类方法存储到 Class对象 中



# SEL应如何使用？

- 创建1个SEL对象，将方法的信息存储在这个SEL对象之中.


 ~~~   
SEL s1 = @selector(方法名);
 ~~~

- SEL使用时不需要加*

![image-20220703122856297](./Objective-C-3-语言特性-SEL消息/1.png)

# OC中调用方法的内部原理是怎样的？

- 现有这样一个方法，p1是Person类的对象，sayHi是其实例方法

  ~~~
  [p1 sayHi];
  ~~~

1. 获取到 sayHi 这一消息的 SEL 对象
2. 将这个SEL消息发送给p1对象，此时，p1对象接收到这个SEL消息以后 就知道要调用方法
3. 根据p1对象的isa指针寻找存储类Person（Class对象）
4. 找到这个类（Class对象）以后 在其中去搜寻是否有和传入的SEL数据相匹配的方法
5. 如果有 就执行  如果没有再向父类寻找 直到NSObject类，若都没有匹配的方法，则抛出异常

   # OC的重要机制:消息机制

- 调用方法的本质其实就是向对象发送SEL消息.
- [p1 sayHi]; 向p1对象发送1条sayHi消息.
- 重点掌握:
  1).方法是以SEL对象的形式存储起来.
  2).如何拿到存储方法的SEL对象：Class 对象获取

 # SEL消息的其他用法？

## 手动发送消息

```
调用对象的方法 将SEL数据发送给对象.
- (id)performSelector:(SEL)aSelector;
```

~~~
   Person *p1 = [Person new];
   SEL s1 = @selector(sayHi); //先得到方法的SEL数据.
   [p1 performSelector:s1];  // 将这个SEL消息发送给p1对象，与 [p1 sayHi]效果是完全一样的.
~~~

# 注意事项:

1. 使用 SEL 对象时，如果方法有参数 那么方法名是带了冒号的 
   1. @selector(sayHi:);
2. 如果方法有参数就调用如下方法:

 - (id)performSelector:(SEL)aSelector withObject:(id)object;
 - (id)performSelector:(SEL)aSelector withObject:(id)object1 withObject:(id)object2;

# 总结：

  1. 类是以Class对象的形式存储在代码段.

  2. 如何取到存储类的类对象.

  3. 如何使用类对象调用类的类方法 

  4. 方法是以SEL数据的形式存储的.

  5. 调用方法的两种方式.

