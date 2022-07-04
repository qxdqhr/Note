# 1 :简述const的作用，const与#define相比，有何优点。

 

# 2 :头文件中的 ifndef / define / endif 干什么用？

 

# 3 :局部变量array1 和 array2 都可以当做指针使用，区别？

char array1[100];

char *array2;



 

4 :

what’s the difference among the data types "char *p",

"const char *p", "char * const p"and"const char *const p" ?

 

5 :

当一个应用程序运行时，出现了地址访问非法的问题，系统出错信息是：地址0x00000088不能被读。

对应到C程序中，可能发生了什么情况？

 

6 :

从程序的执行效果看，递归相当于一个循环语句，那么在相同任务下，用递归和循环两种方法去实现时，其性能哪一个较好？为什么？

 

7 :

局部变量能否和全局变量重名

 

8 :

请简述typedef int(*FUN)(int x, int y)及其作用

 

9 :

C语言中的main函数返回值有什么用？

 

10 :

VC中有哪些方法避免C编程中的头文件重复包含?

 

11 :

将程序移植到不同的32位cpu中，经常出现结构字节对齐和大小端的问题，有哪些方法避免？

 

 



12 :

sizeof

struct

{

 short a;

 long b;

 char c;

}d;

sizeof(d)为什么在不同的平台上得到的值不一样？

 

13 :

strcpy（）为什么会造成缓冲区溢出？可用哪个函数代替？

 

14 :

strcat的效率问题，有没有更好的解决方案.

 

15 :

Heap和Stack有什么区别(堆和栈的区别)

 

16 :

请描述C语言中static, inline, volatile关键词的作用及其使用场景。

 

17 :

请简述大端字节序和小端字节序的概念，设计一个小程序来判断当前操作系统的字节序。

 

18 :

全局变量和static变量有什么区别。

 

19 :

二进制数11101101转换为十八进制数是多少？

 

20 :

在函数体内声明[1] char *str = "abc";和 [2] char str[] = {'a','b','c'}有什么区别

 

21 :

strcpy,memcpy,sprintf的区别

字符串拷贝 缓冲区拷贝 字符串格式拼接

22 :

(1)使用define定义一年有多少毫秒 

 

(2)使用define定义max函数

\#define max(a,b) ((a)>(b)?(a):(b))

(3)define中为何经常会使用 do{}while（0）；来包装多条语句代码

if不加括号的单一包含的性质

 

23 :

实现一个死循环

while(1)

24 :

什么是预编译

编译之前,执行以#开始的指令,例如宏替换,头文件展开

25 :

\#include<filename.h>和#include"filename.h"有什么区别？

<系统头文件> “自定义路径”

 

# 26 :写出三种交换两个int 变量a 和 b的方法:

1.引入新变量

2.异或

3.使用 ^= 

 

# 27 :若x,y均是int型变量，则执行以下语句后，写出x,y的值

```
for(y = 1,x = 1;y<=50;y++)
{
     if(x>=10)break;
     if(x%2 == 1)
     {
         x+=5;
         continue;
     }
     x-=3;
}
```

x=10

y=6

# 28 :写出以下代码段的输出结果:值传递,未交换变量

```
void swap(int m,int n)
{
 int temp;
 temp = m;m = n;n = temp;
}
main()
{
 int m = 7,n = 5;
 swap(m,n);
 printf("m = %d,n = %d\n",m,n);
}
```

输出结果为(  )        

# 29 :请说明下面例子中const的用途（）

1) const int d = 100; 
2) const char *pStr1 = "ABCD";   
3) char *const pStr2 = "abcd";      
4) int func1(int value)const;  
5) const int func2(int value);    

# 30 :写出以下程序的运行结果

```
int count(int data)//求32位二进制数中1的个数
{
 	int mask = 1;
 	int i,count = 0;
 	for(i = 0;i<sizeof(data)*8;i++)
 	{
 		if(data & mask)//与操作，仅同1为1，所以是data为1的时候进入if条件 
 		{
  		count++;//计算个数
 		}
 		mask<<=1;
 	}
 	return count;
}
```

```
data = 0x3; count = ________          
data = 0x12345678;count = ___________ 
```

# 31 :下面程序的运行结果是____________

```
#define ADD(a+b) a+b
int main()
{
 printf("%d\n",5*ADD(3+4));
}
```



 

32 :在C语言程序中，要绝对地址0x100赋值，我们可以用：

*(unsigned int*)0x100 = 1234;

那么，要是想让程序跳转到绝对地址0x100的位置上执行。怎样用一段代码实现___________      

1

33 :在C语言中，若要定义一个只允许本源文件中所有函数适用的全局变量，则该变量应该加关键字（  ）修饰

1

 

34 :经过下列运算后，i和a的值分别是____和______

int i = 4,a = 0;

for(;i>0;i--)

{

 if(i ==2 )

 {

 continue;

 }

 a++;

}

1

2

 

35 :请问执行完下面的程序后x[0]至x[5]的值应为    ______________

int x[6] = {5,7,4,6,3,8};

int i,k,t;

for(i = 0;i<5;i++)

{

 for(k=(i+1);k<6;k++)

 {

 t = x[i];

 x[i] = x[k];

 x[k] = t;

 }

}

1

 

36 :

试着写出结果及原因(1)问题

unsigned char endian[2] = {1,0};

short x;(2)问题

int i = 1;

if(*(char *)&i == 0)return true;

else return false;

x = *(short*)endian;

代码运行后，x的值是多少？

1

2

 

 

37 :x = 5858,下面函数的返回值为___________

int foo(int x)

{

 int c = 0;

 while(0 != x)

 {

 ++c;

 x = x&(x-1);

 }

 return c;

}

1

 

38 :以下程序的输出结果为___________      

char a[] = "hello world";

char *p = a;

cout << sizeof(a) <<endl;

cout <<sizeof(p)<<endl;

void Func(char c[100])

{

 cout<<sizeof(c)<<endl;

}

1

2

3

 

38 :以下程序的输出结果为___________      

char a[] = "hello world";

char *p = a;

cout << sizeof(a) <<endl;

cout <<sizeof(p)<<endl;

void Func(char c[100])

{

 cout<<sizeof(c)<<endl;

}

1

2

3

 

40 :在 int b[][3] = {{1} ,{3 2},{4 5 6},{0}};中 sizeof(b)是多少（ ）

1

 

 

 

41 :请写出下面代码的输出结果________________

void main(void)

{

 int a[5] = { 1, 2, 3, 4, 5, };

 int *ptr = (int*)(&a + 1);

 printf("%d,%d", *(a + 1), *(ptr - 1));

}

1

2

 

42 :在64位机器下的输出为_______ .

int(*p[10])(int);

fprintf(stderr, "%d", sizeof(p));

1

 

43 :

在little-endian机器，以下代码的输出是_______ .

union

{

 int i, j;

 char a, b;

}x;

int main(void)

{

 x.a = 1;

 x.b = 2;

 x.j = x.a + x.b;

 x.i = x.a + x.j;

 printf("0x%x\n", x.i);

 return 0;

}

1

 

44 :如果x = 2014下面函数的返回值是_______ .

int fun(unsigned int x)

{

 int n = 0;

 while (x&255)

 {

 n++;

 x = x&(x - 1);

 }

 return n;

}

45 :

\#include <stdio.h>

main()

{

 FILE *fp;

 int i, a[4] = { 1, 2, 3, 4 }, b;

 fp = fopen("data.dat", "wb");//从这里帮忙解释一下

 for (i = 0; i < 4;i++)

 {

 fwrite(&a[i], sizeof(int), 1, fp);//从这里帮忙解释一下

 }

 fclose(fp);

 fp = fopen("data.dat", "rb");

 fseek(fp, -2L * sizeof(int), SEEK_END);//从这里帮忙解释一下

 fread(&b, sizeof(int), 1, fp);//从这里帮忙解释一下

 fclose(fp);

 printf("b = %d\n", b);

}最终的结果为________

1

2

3

4

 

46 :#define RECTANGLE_AREA(a, b) a*b

如果 int i = 3, j = 4; 那么

请问：RECTANGLE_AREA(i + 5, i + j);的结果是_________  .

1

 

47 :程序的局部变量存在于_____中，全局变量存在于_______中，动态申请数据存在于_____中。

1

2

3

 

48 :若一个视频中图像分辨率为1920 * 1080，每像素采样精度为16 - bit，每秒25帧图像，则每秒图像占内存_________byte（所有数据连续存放）。

1

 

49 :请写出”得到两参数中较小值“的宏：

\#define MIN(a,b)________

1

 

50 :请写出”判断是否为2的幂次“的宏：

\#define IS_POWER_OF_2(a)________

51 :int16_t x = 32767; x++; printf("%d", x);

输出的结果为_________

1

 

52 :下面程序运行后的输出结果是__________.

main()

{

 char a[] = "phoerix", b[] = "finance";

 char *pa, *pb;

 int i;

 pa = a;

 pb = b;

 for (i = 0; i < 7;i++)

 {

 if (*(pa+i)==*(pb+i))

 {

  printf("%c", *(pa + i));

 }

 }

}

1

 

53 :a = 1; a += ++(a++); 此时a的值为多少。

1

 

54 :a = 0xf0; b = 0xf1; c = 1 << ((a&b) ^ (a | b)); c的值为多少？

1

 

55 :count_ones是计算非零整数x的二进制表示下，有多少个bit是1.例如：10 = （1010）2，则返回2，填写空行。

int count_ones(unsigned int x)

{

 assert(x > 0);

 int ones = 1;  

 while (___________)ones++;

 return ones;

}

1

 

56 :在一个64位的PC机器上存储0x12345678, 如果该机器为小端，

从高位到低位存储的字节顺序是_____,

如果为大端，从高位到低位存储的字节为______.

1

2

57 :请实现32位大小端转换宏

1

 

58 :32位机器，以下代码的输出结果_____.

char *p;

char *q[20];

char m[20][20];

int(*n)[10];

struct Mystruct

{

 char dda;

 double dda1;

 int type;

};

Mystruct k;

printf("%d,%d,%d,%d,%d", sizeof(p), sizeof(q), sizeof(m), sizeof(n), sizeof(k));

1

2

3

4

5

 

59 :int a[] = { 2, 8, 16, 24 };

char *p1 = a;

char *p2 = &a[3];

那么 p2-p1=__________.

 

60 :以下代码的执行结果是（）

int main()

{

 int i = -2147483648;

 return printf("%d,%d,%d,%d\n", ~i, -i, 1 - i, -1 - i);

}

运行结果为

1

2

3

4

 

61 :数值转换：

十进制123转成十六进制______

十六进制F3转成十进制____

八进制456转成十六进制___

十进制数64表示成7进制应该是_____.

62 :下列程序的运行结果是_____.

int main()

{

 int a[5][2] = { 0, 1, 2, 3, 4, 5, 6, 7, 8, 9 };

 int* p = a;

 int(*p2)[2] = &a[1];

 ++p;

 ++p2;

 printf("%d\n", *p); 1

 printf("%d\n", **p2);  4

 printf("%d\n", p2[1][2]); 8

 return 0;

}

1

2

3

 

63 :32位X86平台，4字节对齐，下列代码的结果是_______________.

union uni

{

 struct

 {

 char* p1;

 int n2;

 char c;

 }s1;

 struct

 {

 int n3;

 char* p4;

 }s2;

};

int main()

{

 union uni u;

 printf("%d %d %d %d \n", sizeof(u), sizeof(&u),

 (int*)&u.s2.p4 - (int*)&u.s1.p1,

 (char*)&u.s2.n3 - (char*)&u.s1.p1);

 return 0;

}

1

2

3

4

64 :

用变量a给出下面的定义

一个整型数

一个指向整型数的指针

一个指向指针的指针，它指向的指针是指向一个整型数

一个有10个整型数的数组

一个有10个指针的数组，该指针式指向一个整型数的

1

2

3

4

5

 

65 :

用变量a给出下面的定义

一个整型数

 

一个指向有10个整型数数组的指针

一个指向函数的指针，该函数有一个整型参数并返回一个整型数

一个有10个指针的数组，该指针指向一个函数，该函数有一个整型参数并返回一个整型数

1

2

3

 

66 :设

typedef struct

{

 char flag; short len; char *pdata;

}CMD_PKT;

CMD_PKT pkt = { 0xFF, 8, "12345678"

 };

在32位x86CPU环境下，sizeof(CMD_PKT)为___,sizeof(pkt)为______.

在64位x86CPU环境下，sizeof（CMD_PKT)为_____,sizeof(pkt)为____.

1

2

3

4

 

67 :在32位x86CPU环境下，下列三行语句结束后，result值为___.

unsigned char port = 0x5a;

unsigned char result;

result = (~port) >> 4;

1

 

68 :设

int arr[] = { 6, 7, 8, 9, 10 };

int *ptr = arr;

*(ptr++) += 123;

printf(“%d, %d”, *ptr, *(++ptr));

输出______.

 

69 :下面程序，求count的值________.

int func()

{

 int count = 0;

 unsigned int a = 1;

 int b = -5;

 while (b++ <= 5)

 {

 if (a + b > 5)

 {

  count++;

 }

 }

 return count;

}

1

 

70 :

位运算（32位X86平台）

1）0x321 & 0x2f = ___

2）0x321 ^ 0x3f = ___ 

3）~0x321 = ______

 

71 :请描述下面代码的运行结果______，并说明原因

\#include<stdio.h>

int main()

{

 int i = 0;

 int name[10] = { 1, 2, 3, 4, 5, 6, 7, 8, 9, 10 };

 for (i = 0; i <= 10; i++)

 {

 name[i] = 0;

 printf(“ok\n”);

 }

 return 0;

}

 

72 :

下面的数据声明代表什么？

float(**def)[10];

double*(*gh)[10];

double(*f[10])();

int*((*b)[10]);

long(*fun)(int);

int(*(*f)(int, int))(int);

1

2

3

4

5

6

 

73 :下面程序输出结果为_______.

\#include <stdio.h>

int main()

{

 int v[2][10] = { { 1, 2, 3, 4, 5, 6, 7, 8, 9, 10 }, { 11, 12, 13, 14, 15, 16, 17, 18, 19, 20 } };

 int(*a)[10] = v;

 printf(**a);

 printf(**(a + 1));

 printf(*(*a + 1));

 printf(*(a[0] + 1));

 printf(*(a[1]));

 return 0;

}

 

74 :下面程序的输出结果为___________.

int fun(int *p)

{

 *p = *p * 2;

 return *p++;

}

main()

{

 int a = 1;

 int sum = 0;

 int i;

 for (i = 0; i<3; i++)

 sum += fun(&a);

 printf("%d", sum);

}

75 :程序的运行结果为 ?

unsigned char* p1;

unsigned char* p2;

p1 = (unsigned char*)0x801000;

p2 = (unsigned char*)0x810000;

请问:

p1 + 5 = ? ____________.

p2 + 5 = ? ____________.

1

2

 