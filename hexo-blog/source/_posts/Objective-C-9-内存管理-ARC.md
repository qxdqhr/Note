---
title: Objective-C-9-内存管理-ARC
date: 2022-07-07 12:17:20
categories: Objective-C
tags:
---

# 什么是ARC

- Automatic Reference Counting，自动引用计数
- 系统自动的帮助我们去计算对象的引用计数器的值
- 在WWDC2011和iOS5引入的最大的变革和最激动人心的变化
- ARC是新的LLVM3.0编译器的一项特性

# ARC 如何使用?

- 永远不要写retain、release、autorelease
- 永远要手动的调用 dealloc 这三个关键字就好,这是ARC的最基本的原则.
- 编译器自动为对象做引用计数. 而作为开发者,完全不需要担心编译器会做错(除非开发者自己错用了ARC).

## 注意: 

- ARC是编译器机制
- 在编译器编译代码的时候,会在适时的位置加入retain、release和autorealse代码.

# ARC机制下,对象何时被释放

-  理论:对象的引用计数器为0的时候,自动释放
-  实际:只要没有强指针指向这个对象,这个对象就会立即回收

# 强指针与弱指针是什么?

-   无论是强指针还是弱指针,都是指针,都可以用来存储地址,这1点没有任何区别

 ## 强指针

-  默认情况下,我们声明1个指针 这个指针就是1个强指针
- 也可以使用__strong来显式的声明这是1个强指针

       ~~~objective-c
       Person *p1; //这是1个强指针. 指针默认情况下都是1个强指针
       __strong Person *p2; // 这也是1个强指针.使用__strong来显示的声明强指针.
       ~~~

## 弱指针

-  使用__weak标识的指针就叫做弱指针.



强指针与弱指针的声明.

   

   默认情况下,所有的指针都是强类型的,也就是说我们之前声明的指针变量都是强类类型的

 

   p1指针是强类型的,因为默认情况下指针都是强类型的.

   Person *p1 = [[Person alloc] init];

 

   不过我们可以使用__strong来显示的标识指针是强类型指针.

   __strong Person *p2 = [Person new];

   这个时候p2指针类型是强指针类型的.其实写不写__strong都是强类型的指针.

​     

   指针类型也可以是弱指针类型.

   使用__weak标识指针的类型是弱类型指针.

   __weak Person *p3 = p2;

   这个时候,p3指针就是1个弱类型的指针. p3弱指针也指向p2指针指向的对象.

 

  在操作对象的时候,通过强指针或者弱指针都可以操作,没有任何区别.

# 确认程序是否开启ARC机制

- 默认情况下,Xcode开启ARC机制.
- ARC机制下,不允许调用retain、relase、retainCount、autorelease方法.
- 在dealloc中 不允许[super dealloc];

# ARC案例

- 原对象没有强指针指向时,被回收

~~~
int main(int argc, const char * argv[])
{
   @autoreleasepool
   {
     
     Person *p1 = [Person new];//p1是1个强指针.
     
     NSLog(@"------");
   }
   //执行到这里时 p1指针被回收,没有任何强指针指向原对象 对象被立即回收
   return 0;
}
~~~

- 将所有指向对象的强指针赋值为nil的时候.对象就会被立即回收

~~~
int main(int argc, const char * argv[])
{
 		@autoreleasepool
    {
   		 Person *p1 = [Person new];//p1是1个强指针.
       p1 = nil;//p1赋值为nil.
       //Person对象没有被任何的指针所指向立即释放,所以.Person对象在这里被释放.
       NSLog(@"------");
    }
    return 0;
}
~~~

ARC模式下的对象回收标准

 

   ARC机制下释放1个对象的标准是: 没有任何强指针指向对象的时候,对象就会被释放.

   如果这个时候有弱指针指向,也会被释放.

   int main(int argc, const char * argv[])

   {

​     @autoreleasepool

​     {

​       //使用__strong来标识p1指针是强类型的,其实不写__strong也是强类型的.

​       __strong Person *p1 = [[Person alloc] init];

​        

​       //使用__weak标识指针p2的类型是弱类型指针.

​       __weak Person *p2 = p1;

​       //这个时候,p2指针和p1指针都指向Person对象.

​        

​       //这个时候如果设置p1的值为nil

​       p1 = nil;

​       //这个时候Person对象只有被1个弱指针p2指向,没有任何强指针指向

​       //所以Person对象在这里被回收.

​     }

​     return 0;

   }

 

 

   3).最重要的1点:不能创建对象用1个弱指针存储这个对象的指针.

   这样的话,刚创建出来的对象,就没有任何强指针指向,创建出来就会被回收.

   int main(int argc, const char * argv[])

   {

​     @autoreleasepool

​     {

​       //创建1个对象,将这个对象的地址赋值给1个弱指针

​       //后果就是创建出来的这个对象没有被任何强指针指向.

​       //刚创建出来就会被释放.

​       __weak Person *p1 = [[Person alloc] init];

​        

​     }

​     return 0;

   }

 

 

   4). 在ARC机制下. 当对象被回收的时候. 原来指向这个对象的弱指针会被自动设置为nil

​      \1. ARC机制下的对象的回收的标准: 当没有任何强类型的指针指向对象的时候,这个对象就会被立即回收.

 

 \2. 强类型指针 弱类型指针.

 

 \3. 什么情况下叫做对象没有强指针向指向.

 

   1). 指向对象的强指针被回收.

 

   2). 指向对象的强指针被赋值为nil

 

 \4. 在ARC的机制下,@property参数不能使用retain

   因为retain代表生成的setter方法是MRC的标准的内存管理代码.

   而我们在ARC的机制下 不需要这些代码.

 

   所以,在ARC机制下的setter方法 什么都不需要做.直接赋值就可以了.

 

 

 \5. ARC机制下,我们关注的重点.

   当1个类的属性是1个OC对象的时候.这个属性应该声明为强类型的还是弱类型的.

   很明显,应该声明为1个强类型的.

 

   问题来了?

 

   如何控制@property生成的私有属性,是1个强类型的还是1个弱类型的呢?

 

   使用参数, strong和weak

 

   @property(nonatomic,strong)Car *car;

   代表生成的私有属性_car 是1个强类型的.

 

   @property(nonatomic,weak)Car *car;

   代表生成的私有属性_car 是1个弱类型的.

 

 

   如果不写,默认是strong.

 

 

 \6. 使用建议.

 

   1). 在ARC机制下.如果属性的类型是OC对象类型的.绝大多数场景下使用strong

   2). 在ARC机制下.如果属性的类型不是OC对象类型的.使用assign

 

   3). strong和weak都是应用在属性的类型是OC对象的时候. 属性的类型不是OC对象的时候就使用assign.

 

 

 

   \--------

   在ARC机制下,将MRC下的retain换位strong

 

   @property(nonatomic,strong)Car *car;

   做的事情:

   1). 生成私有属性.并且这个私有属性是strong

   2). 生成getter setter方法的声明

   3). 生成getter setter方法的声明

 

​     setter的实现:直接赋值.

 

  在ARC机制下.当两个对象相互引用的时候.如果两边都使用strong 那么就会先内存泄露.

   

 解决方案: 1端使用strong 1端使用weak





 \1. 有可能会遇到的问题.

 

 

   程序使用的是ARC机制开发的,但是其中的某些类使用的是MRC.

 

​    

 

  \2. 使用命令. -fno-objc-arc



可以将整个MRC程序,转换为ARC程序;

