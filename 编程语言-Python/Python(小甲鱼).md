01=============================================================
Python中自带SHELL 叫做IDLE，可以通过键入文本与程序进行交互
    1）print()的用法
        1.输出字符串  print("string")
                输出结果：string
        不支持的格式：      
        print   "string" (Python2用法，Python3中不支持)
        print("string");  (C语言用法，Python不适用)
        2.进行运算    print(5+3)
                输出结果：8
            此处的计算也可以不加print；
            直接在IDLE中输入数字和数字的运算表达式即可进行运算；
            同时，IDLE中的运算无数值大小限制；
            可以进行较大位数数字的计算；
        3.输出拼接的字符串  print("string"+"string")
                输出结果：stringstring
            直接拼接，不留空格；
            此时，拼接的必定是相同类型的数据；
            数字+数字为计算两数之和；
            字符串+字符串为拼接连字符串；
            数字+字符串会报错；
        4.多次输出某一字符串    print("hello world\n"*8)   
                输出结果：
                hello world
                hello world
                hello world
                hello world
                hello world
                hello world
                hello world
                hello world
            转义字符与C语言中的转义字符基本相同
02===============================================================
IDLE的简单使用：
    1.创建新程序：[File]--[New File]
        创建新窗口写程序源代码；
        窗口写完源代码后要保存（CTRL+s）；
    2.运行代码：[Run]/F5
        在源代码页面进行运行
03===============================================================
Python语法：
1.使用缩进来表示代码段，类似于C语言的大括号
2.BIF（Built-in functions）是Python中的内置函数
    例如：print()，input()，int()
    在shell中输入
        dir（_）
        help()
3.变量：Python中可理解为：把名字贴到名字上面
    1.使用变量前需要对变量进行赋值
    2.变量名可以包括字母、数字、下划线，但变量名不能以数字开头
    3.字母可以是大写或小写，但大小写是不同的（区分大小写）
    4.等号是赋值的意思，名字=值（不可写反）
    5.变量取名要贴近意思
    举例：
        >>> teache  r="qhr"   #将字符串qhr赋值给变量teacher
        >>> print(teacher ) #打印teacher变量中的值
        qhr                 #打印出qhr
        >>> teacher="hhh"   #对teacher重新赋值
        >>> print(teacher ) #打印出teacher中现在的值
        hhh                 #打印出hhh
        >>> first=3         #将3，4，5分别赋值给first，second，third中，并求和
        >>> second=4
        >>> third=5
        >>> print(first+second+third)
        12
        >>> first="hello"   #拼接first，second，third变量中所存储的三个字符串
        >>> second=" "
        >>> third="world"
        >>> print(first+second+third)
        hello world
4.字符串：引号内的一切东西，也把字符串叫做文本.
    1.创建字符串的时候，要在字符的两边加上单引号和双引号，但对应引号必须成对；
    2.在字符串中要使用引号时，确定字符串的时候可以使用转义字符  或  对应不同的引号；
    3.只想打印出单个\时，使用\\可以直接打印出有斜杠，即\+任意字符可以使后一字符的转义失效。
        原始字符串：在字符串之前加上r即可让整个字符串的所有\都失效。     
        举例：   str=r'c:\hello\str\test'                                      
                print("str")
                c:\\hello\\str\\test


                    