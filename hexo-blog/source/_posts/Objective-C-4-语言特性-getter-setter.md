---
title: Objective-C-4-语言特性-getter-setter
date: 2022-07-05 21:22:11
categories: Objective-C
tags:
---

 # OC中是如何访问对象的属性的?

- OC中可以使用点语法来访问对象的属性

- 语法如下所示: 

~~~objective-c
//对象名.去掉下划线的属性名;
p1.name = @"jack"; //这个时候就会将@"jack"赋值给p1对象的_name属性.
NSString *name = p1.name; //把p1对象的_name属性的值取出来
~~~

- 但,OC的对象如果要为属性赋值或者取值 就要调用对应的getter或者setter.

# 点语法实际是如何进行的?

   ~~~
     p1.age = 18;
   ~~~

- 点语法在编译器编译的时候.会将点语法转换为调用setter、getter的代码. 

## 赋值操作:

~~~
p1.age = 10;	//对象名.去掉下划线的属性名 = 数据; 转换为
[p1 setAge:10]; //  [对象名 set去掉下划线的属性名首字母大写:数据];
~~~

## 取值操作:

~~~
int age = p1.age;//     对象名.去掉下划线的属性名; 转换为
int age = [p1 age];	//    [对象名 去掉下划线的属性名];
~~~

 # 点语法注意:

- 在getter和setter中慎用点语法,因为有可能会造成无限递归 而程序崩溃

- setter方法和getter方法名不符合规范 点语法就会出问题.

- 如果属性没有封装getter setter 是无法使用点语法的 

#  @property关键字是什么?

- 为了简化类属性 getter/setter的声明代码,用于 **自动生成类属性的getter、setter方法的声明** 的关键字
- 会额外为类生成属性,并不会影响原来类已有的属性

- 因为是生成方法的声明,所以应该写在@interface类的声明之中.

- 语法: @property 数据类型 名称;

~~~
@property int age; 
~~~

# @property的原理是怎样的?

- 编译器在编译的时候.会根据@property生成getter和setter方法的实现

 ~~~
 @property int age;			 	//@property 数据类型 名称;
 - (void)setAge:(int)age;	//- (void)set首字母大写的名称:(数据类型)名称;
 - (int)age;								//- (数据类型)名称;
 ~~~

# @property注意:

- **@property的类型**和**属性的类型**一致.
- **@property的名称**和**属性的名称**一致(去掉下划线)

- @property只是生成getter和setter方法的声明. 实现还要自己来. 属性还要自己定义.

# @synthesize关键字是什么?

- 为了简化类属性 getter/setter的实现代码,用于 **自动生成类的getter、setter方法的实现** 的关键字

- 因为是生成方法的实现,所以应该写在@implement类的实现之中.
- 语法如下所示:

~~~objective-c
//--------Person.h
@interface Person : NSObject
{
   int _age;
}
@property int age;//age 的 getter,setter 声明
@end

//--------Person.m
@implmentation Person
@synthesize age; //age 的 getter,setter 实现 ;@synthesize @property名称;
@end


~~~

# @synthesize的原理是怎样的?

~~~objective-c
@implmentation Person
  @synthesize age;
@end
//----------上述代码等同于如下代码:
@implementaion Person
{
  int age;
}
- (void)setAge:(int)age
{
  self->age = age;
}
- (int)age
{
  return age;
}
@end
~~~

# @synthesize做什么工作呢?

## 会自动生成的完全私有属性:

- 如下写法会在这一类中自动生成一个完全私有的属性,以及这个属性的 getter 和 setter
- 自动生成的属性与外部其他属性无关

~~~
//类的实现部分
@synthesize name;//@synthesize 属性名称;
~~~

- 属性的类型应和@synthesize对应的@property类型或属性声明一致.
- 属性的名字应和@synthesize对应的@property名字或属性声明一致.

 ## 自动生成setter方法的实现:

-  实现的方式: 将参数直接赋值给**@synthesize自动生成的私有属性**.并且**不会做任何额外操作**,也不会对其他属性有影响

## 自动生成getter方法的实现.

- 实现的方式: 直接将**@synthesize自动生成的私有属性的值**返回

# 如果属性被写好了,如何使用@synthesize自动生成 getter 和 setter?

- 可以使用如下写法来实现:

~~~
@synthesize age = _age; //@synthesize 属性(@property 的)名称 = 已经存在的属性名;
~~~

- 这种写法的特点:
  - 不会再去生成私有属性.
  - 直接生成setter getter的实现,且操作的是指定的属性

 # 如何向@synthesize自动生成的getter 和 setter中添加新逻辑?

- @synthesize生成的setter方法实现中 是没有做任何逻辑验证的 是直接赋值.

- @synthesize生成的getter方法的实现中 是直接返回属性的值.

- 如果setter或者getter有自己的逻辑验证 那么就自己在类的实现中重写就可以了.

# 当类中有较多属性时,如何简便的向类中添加多个属性的声明及实现? 

- @property只是生成getter setter 的声明
- @synthesize是生成getter setter 的实现

## 声明多个类型一致的@property

 ~~~
 @property float height,weight;
 ~~~

## 声明多个@synthesize

~~~
@synthesize name = _name,age = _age,weight = _weight,height = _height;
~~~

# 新版本的@property

- Xcode4.4以后,Xcode对@property做了1个增强,只需@property关键字,编译器就会自动生成一个 OC 类中的一个属性

~~~
@property NSString *name;
~~~

## 新版本@porperty 都做了哪些事情?

1. 自动的为类生成1个私有属性
2. 属性的类型和@property类型一致 
3. 属性的名称和@property的名称一致 并自动为这个属性的名称添加1个下划线.
4. 自动的生成这个属性的getter setter方法的声明以及实现
   1. setter的实现: 直接将参数的值赋值给自动生成的私有属性.
   2. getter的实现: 直接返回生成的私有属性的值.

# 新版本@porperty的注意要点有哪些?

- @property的类型对应类成员属性类型
- @property的名称对应类成员属性的去掉下划线后的属性名
- 新版本的@property也支持相同类型的批量声明
- 新版本的@property生成的方法实现也没有做任何逻辑验证
- 自定义验证逻辑时
  - 如果重写了setter 还会自动生成getter
  - 如果重写了getter 还会自动生成setter 
  - 如果同时重写getter setter 那么就不会自动生成私有属性了,需要手动向类中添加属性
-   父类的@property一样可以被子类继承
  - @property生成的属性是私有的 在子类的内部无法直接访问,但可通过setter getter来访问    

- 生成的setter方法的实现中,无论是什么类型的,都是直接赋值
  - 若设定为 MRC 时,setter 和 dealloc 方法中对对象的复制与释放的都需要手动完成

# 新版本@property中参数有哪些?

- 语法:

  ~~~
  @property(atomic,assign,readwrite,getter = getter方法名字,setter = setter方法名字:)数据类型 名称;
  ~~~

- 按照使用功能来划分,@property有四组参数:

 ##  多线程相关

     ### atomic

-  默认值
- 如果写atomic,这个时候生成的setter方法的代码就会被加上一把线程安全锁.
- 特点: 安全、效率低下.

   ### nonatomic

-  如果写nonatomic 这个时候生成的setter方法的代码就不会加线程安全锁.

- 特点: 不安全,但是效率高.

   建议: 要效率. 选择使用nonatomic 在没有讲解多线程的知识以前 统统使用nonatomic

## 生成的setter方法的实现相关

### assign

-  默认值 
- 生成的setter方法的实现就是直接赋值
- 当属性的类型是非OC对象的时候,使用assign

  ### retain

- 生成的setter方法的实现就是标准的MRC内存管理代码
  - 先判断新旧对象是否为同1个对象 如果不是 release旧的  retain新的
  - 仍需要手动的在dealloc中release
- 当属性的类型是OC对象类型的时候,那么就使用retain

## 生成只读、读写的属性相关    

### readwrite

- 默认值
- 代表同时生成getter setter

### readonly

- 只会生成getter 不会生成setter

## 生成的getter setter方法名字相关

- 通过@property生成的getter setter方法名都是符合标准的
  - 但也可通过参数来	指定@property生成的方法名
- 使用getter setter修改了生成的方法名,使用点语法时,编译器会展示修改后的方法名

### (getter = getter方法名字) 

- 用来指定@property生成的getter方法的名字

#### 何时修改getter方法名?

- 当属性为BOOL类型时,就修改getter的方法名以is开头 提高代码的阅读性.

### (setter = setter方法名字:)

- 用来指定@property生成的setter方法的名字

- setter方法是带参数的 所以要加1个冒号

- 一般无需修改setter方法的名字,默认情况下生成的名字就是标准方法名

  

# 当两个对象的属性值相互引用时,出现内存泄漏?

- A对象中包含B类型属性b1; B对象中包含A类型属性a1;
- 此时,若这两个属性的@property 参数中均使用retain 那么就会发生内存泄露

## 原因:

- 互相持有导致A,B 对象的引用计数在 release 时都没有变为 0,两个对象都 不会调用 dealloc 方法

## 解决方案: 

- 令A中的b1属性的@property 参数使用assign 
- A类中的dealloc中不需 release b1 对象
- A:b1 可换为 B:a1

### 原因:

- assign 是直接赋值,不进行 release,retain操作
- 在进行相互引用时,拥有 assign属性 的对象 A 的引用计数就只会+1
- 因此在两个对象被回收时,B 对象的引用计数一定先到 0,进而调用自己的 dealloc 函数,从而 release 掉 A

 

# 总结:

- 如果你想为类写1个属性 并且为这个属性封装getter setter, 使用@property就搞定,不需要再使用@synthesize
- 对于一个属性的@property的参数;
  -  同组参数只能使用1个(getter/setter 方法名除外)
  - 参数的顺序可以随意

