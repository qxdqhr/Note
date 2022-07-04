通过IP地址+端口号即可找到MySql进程

创建一个Win32控制台项目

# 配置项目头文件与库文件

## stdafx.h

 MySql.cpp粘贴#include "stdafx.h";

若没有#include "stdafx.h",换成有的头文件



## 包含mysql.h文件的两种方法:

![image-20200926084804479](.\VS操作数据库.assets\image-20200926084804479.png)

1. 将此路径粘贴到头文件处

2. 将MySql的include文件夹包含进入项目中

   属性-VC++目录-包含目录中,将上述路径粘贴到其中



## 包含MySql库

![1](.\VS操作数据库.assets\image-20200926085509253.png)

1. 将MySql的include文件夹包含进入项目中

   属性-VC++目录-库目录中,将上述路径粘贴到其中

2. 将lib.下的libmysql.dll放入C:\Windows\System32文件夹下''

## 项目位数

调整项目为64位(由所安装的MySql决定,保证与项目相同)



## 可能会出现的问题

若安装的是MySql 8.0,需要在

# 连接数据库

1. 包含C++中的头文件与命名空间

2. 若出现参数报错,在参数前面加上const

3. 定义CMySql类的对象

4. 调用ConnectMySql函数,将对应参数传入,并输出对应结果

## 代码示例

```
#include "stdafx.h"
#include"CMySql.h"
#include<iostream>
using namespace std;

int _tmain(int argc, _TCHAR* argv[])
{
	CMySql my ;
	if(my.ConnectMySql("localhost","root","776688","qhr"))
	//参数,IP地址(本机为localhost),用户名,密码,数据库名
		cout<<"Connection Standby"<<endl;
	else
		cout<<"Connection Failed"<<endl;

	system("pause");
		
	return 0;

}
```

# 开始操作数据

## 插入数据

1. 首先拼接出一个SQL语句

```
insert into course values('05','化学','05');
```

2. 调用UpdateMySql(Sql),参数为待执行的Sql语句,成功返回1

### 代码示例

	//使用SQL语句修改数据库
	char* Sql="insert into course values('05','化学','05');";
	if(my.UpdateMySql(Sql)) 
		cout<<"Data insert successful"<<endl;
	else 
		cout<<"Data insert failed"<<endl;
## 删除数据

1. 拼接SQL语句,可以覆盖已有SQL字符串

```
delete form student where snum=15
```

2. 调用UpdateMySql(Sql),参数为待执行的Sql语句,成功返回1

## 查询数据:

1. 创建一个string类链表,用作Select的参数
2. 拼接SQL语句,可以覆盖已有SQL字符串

```
select Cnum,Cname,Tnum from course
```

3. 调用SelectMySql()

### SelectMySql函数分析:

1. 返回值:
   1. 查询成功返回true,失败返回false
2. 参数:
   1. SQL语句:char*缓存
   2. 列数,由SQL语句决定,列数表示查询到的表中有几列,也是SQL中select的项数
   3. 用于存储查询结果的字符链表
3. 使用方法:
   1. 调用此函数之前,需要创建一个字符链表用于保存结果
   2. 调用完查询函数后使用循环遍历字符链表
   3. 按照SQL中查询数据项的顺序去除头节点
   4. 转存结点的字符串可以被用于其他用途
      1. 数据包赋值
      2. 显示

#### 代码示例

	//使用Sql语句查询数据库中的值
	char* Sql1="select Cnum,Cname,Tnum from course";
	list<string>lstStr;
	my.SelectMySql(Sql1,3,lstStr);
	while(lstStr.size()>0)
	{
		string strCnum=lstStr.front();
		lstStr.pop_front();
		string strCname=lstStr.front();
		lstStr.pop_front();
		string strTnum=lstStr.front();
		lstStr.pop_front();
		cout<<"num:"<<strCnum.c_str()<<"	name:"<<strCname.c_str()<<"	num:"<<strTnum.c_str()<<endl;
	
	}
## 注意:

cout不能直接输出string类型变量

