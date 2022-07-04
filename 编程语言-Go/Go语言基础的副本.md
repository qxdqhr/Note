# go语言基础

## go 环境相关

### GOROOT

- Golang的安装路径,随着GO的安装结束而产生

### GOPATH

-  是go语言设定的工作目录路径
- 需要被配置到环境变量中
- 形式

	- GOPATH

		- bin

			- 存放golang语言的经编译后的可执行文件

		- pkg

			- 存放 go在编译包时产生的 .a文件

		- src

			- 存放 golang 语言的源代码

	- 

### 常用命令

- go env
  -  查看go语言的环境变量
- go run (路径) 在当前路径下 编译运行某代码
- go build (路径) 在对应路径下编译某代码 但不运行

  - 一般在GOPATH下执行此命令 但是需要加对应的 go代码所在目录路径

    - 直接在main.go目录下使用 go build 会以main.go所在文件夹名作为编译好的二进制文件的名字
    - go build ./src/helloworld

  - 也可以直接在.go文件目录下执行 编译单文件
- go env -w GO111MODULE=“auto” 修改环境变量

	- GOPROXY=“https://goproxy.cn”
- go get github.com/gin-gonic/gin 安装依赖

	- 从远程下载需要的包
	- 执行 go install
- go install  

	- 编译任意程序 生成可执行文件 直接放入bin目录下
	- 编译任意包 生成.a文件 放在pkg目录下
- go clean -modcache 清空本地下载的module缓存

## 依赖相关

### GOPATH模式

- 此时需要保证Go的环境变量中的GO111MODULE = “off” 或 “auto”

	- GO111MODULE

		- on

			- 命令行只使用 modules ,完全不去GOPATH目录下查找;没有go.mod文件会报错

				- 即便开启module支持,下载的依赖包仍然放在$GOPATH/src
				- go install 的结果放在 ¥GOPATH/bin

		- off

			- 命令行仅通过vendor或GOPATH目录下查找,不支持module功能

		- auto

			- 命令行会根据当前目录来决定是否启用module功能

				- 当前所在目录位于$GOPATH/src之外 且 项目根目录中包含go.mod文件时 开启module支持

- 不支持go module功能
- 项目必须放在$GOPATH/src下

### go vendor 模式

- go vendor 是go 1.5 官方引入管理包依赖的方式，1.6正式引入
- 工作原理

	- 将当前项目所依赖的包复制到当前项目的vendor目录下
	- 在进行编译的时候 go会优先从vendor目录下寻找依赖包

- 将单一项目的依赖包统筹到/vendor目录下,减少了项目的外部依赖,更方便移动,规避了重新go get依赖包时版本不一致的问题
- 会生成一个元数据文件 记录依赖包与其版本信息

	- vendor/vendor.json 
	- 不会记录已拉取依赖的版本信息

		- 无精确的依赖包版本控制,外部包升级时,以拉取的依赖包不能自动升级

- govendor的使用

	- 安装

		- go get -u github.com/kardianos/govendor

	- 一般流程

		- 找到在GOPATH下的项目
		- govendor init
		- govendor add +external
		- govendor update +vendor

	- 常用命令

		- add命令也可将非vendor项目转化为vendor项目

			- govendor add  inport_out_packagename

		- 

	- 包的状态

### go mod 模式

- 是Golang1.11中新引入的处理依赖包的方式 解决了依赖包版本号的问题
- 要求

	- go的 环境变量中 G111MODULE=“ ture ”或“ auto ”
	- go语言版本应该在1.11以后

		- 1.11 之前只能使用GOPATH方式和第三方方式管理依赖包

- go mod 的使用

	- 通过 go init mod 生成一个 go.mod 文件

		- 在GO111MODULE=“on”时,不创建go.mod是无法进行编译的

	- 当项目需要添加新依赖时,执行go get命令,下载好依赖包后,会将依赖包的信息写入go.mod和go.sum中

		- go.sum 会自己维护,一般不需要操作
		- go .mod记录着所需要依赖包以及其版本信息
		
	- go mod命令

- 关于go.mod文件
- go mod项目添加vendor管理

  - 项目移动至GOPATH目录下
  - govendor init
  - govendor add +external
  - govendor update +vendor
  - go build 提示需要更新 

  - 执行go mod vendor
  - go build 成功

- go vendor项目添加mod管理

  - 将vendor文件夹移动至上一级目录
  - 命令 go mod init
  - 将vendor文件夹移动回当前目录
  - go build 提示需要更新 

  - 执行go mod vendor
  - go build 成功

## go中的包

### 是多个Go源码的集合,即多份源码可以放置在同一个包中

- 存放go代码的文件夹

### 内置包

- fmt,os,io等

### 自定义的包

- go代码在第一行都要声明自己所归属的包
- 在导入其他自定义包的时 注意 “项目名/存储包的文件夹名”

	- 存储包的文件夹尽量和包名一致,以防出错

- 引用其他包的内容时需要注意

	- 被引用包的成员的对外可见性
	- 调用成员时需要使用被引用包的包名

### 导入包的方式

- import “包的路径”
- 匿名导入包

	- import  _“包的路径”
	- 只导入包,不使用包中的数据

- 导入包的路径

	- $GOPATH /src/+import “路径”

### 注意

- 一个实际文件夹下面所包含的.go文件 只能归属于一个package

	- 同一个包中的代码不能分成多个文件夹存放

- 首字母成员 的大小写 表示 成员的外部可见性 大写:可见;小写:不可见
- main程序包 是应用程序的入口包 编译main包后会得到一个可执行文件,非main包编译后无可执行文件

## go语言标准库相关

### 字符串

- strings

	- 操作字符串的功能

- bytes

	- 提供对字符型分片的操作

- strconv

	- 将字符串转换为基本类型的功能

		- 字符串与整形的互相转化

			- Atoi
			- Itoa

		- 字符串转换为其他类型

			- ParseBool

				- 1、0、t、f、T、F、true、false、True、False、TRUE、FALSE均可转化，其他会报错

			- ParseInt(str,进制,赋值不溢出的类型)

				- 进制数(2~36,0则判断字符串前置的 0x，0；16进制，8进制)
				- 不溢出的类型(0,8,16,32,64):(int int8 int16 int32 int64 )
				- 返回的错误类型 

					- 错误类型时是*NumErr类型的
					- 语法有误：err.Error = ErrSyntax；
					- 结果超出类型范围err.Error = ErrRange;

			- ParseUint(str,进制,赋值不溢出的类型)
			- ParseFloat(str,赋值不溢出的类型)

		- 其他类型转换为字符串

			- FormatBool(bool)
			- FormatInt(int,进制)
			- FormatUint(uint,进制)
			- FormatFloat(float,fmt表示格式,prec控制精度,float类型)

				- fmt

					- ’f’（-ddd.dddd）
					- ’b’（-ddddp±ddd，指数为二进制）
					- ’e’（-d.dddde±dd，十进制指数）
					- ’g’（指数很大时用’e’格式，否则’f’格式）
					- ’E’（-d.ddddE±dd，十进制指数）
					- ’G’（指数很大时用’E’格式，否则’f’格式）

				- prec

					- 对’f’、’e’、’E’，它表示小数点后的数字个数；
					- 对’g’、’G’，它控制总的数字个数。
					- 如果prec 为-1，则代表使用最少数量的、但又必需的数字来表示f。

				- float类型

					- float32
					- float64

		- 其他字符串处理函数

			- isPrint(rune r)

				- 判断r是否是字母，数字，标点，符号 ASCII空间
				- rune类型是一种字符类型

			- CanBackquote(string)

				- 是否可以表示为一个单行的、没有空格和tab之外控制字符的反引号字符串

			- AppendInt(int,进制)

				- 将一个整形数字拼接在[]byte数组之后

			- Quote(str)

				- 使当前的转义字符失效并返回"s"

- regexp 

	- 正则表达式功能

- unicode 

	- unicode型字符串的功能

- index/suffixarray

	- 子字符串查询功能

### I/O

- io

	- 基本输入输出,大多为系统功能封装

- fmt

  - 输入功能:向控制台中写入数据

    - Print	Printf	Println
  - 向reader中写入数据
    - Fprint	Fprintf	Fprintln
    - reader可由string/文件/os.Stdout创建
  - 向字符串中写入数据
    - Sprint	Sprintf	Sprintln
  - 自定义错误类型		Errorf 
    - 自定义错误类型,返回一个err
    - 可使用%w 打印一个err的错误信息
  - 输出功能

  	- Scan 

  		- Scanf

  			- Scanln

  				- 向控制台中读取数据至变量

  	- Fscan 

  		- Fscanf

  			- Fscanln

  				- 向reader中写入数据

  					- 使用标准输入流

  				- reader可由string/文件/os.Stdout创建

  	- Sscan 

  		- Sscanf

  			- Sscanln

  				- 向字符串中读取数据至变量

  	- 一般由空格区分多个变量

- bufio

	- 缓冲区输入输出功能

### 数据结构(集合)/算法

- heap
- list

	- 双向链表

- ring

	- 环形链表

- sort

### 网络

- context
- net/http

	- 提供了一个可扩展的 HTTP 服务器和基础客户端，解析 HTTP 请求和回复。

- net 

	- 网络数据的基本操作

- html 

	- HTML5解析器
	- template

		- 通过数据模版生成网页HTML
		- 可以通过模版来表示数据

			- 通过编写模版文件
			- 在程序中编写对应变量
			- 解析模版后,向模版中镶嵌对应的变量值
			- 得出编辑后的HTML文件,并可以部署到浏览器上

		- 主要流程

			- 项目外创建模版文件
			- 解析模版文件前的操作

				- 定义数据对象
				- 创建模版对象

					- New()

				- 声明自定义函数表

					- FuncMap

				- 向模版对象内导入函数表

					- Funcs

				- 加载网页静态资源

					- CSS
					- image
					- js

			- 解析模版文件

				- Parse
				- ParseFile

			- 向解析好的模版文件中插入数据

				- Execute函数

### 调试测试

- log

	- 记录日志相关功能

		- 创建日志对象

			- log.New()

	- 打印一段日志

		- Print

			- Printf
			- Fatalln
			- Panicln

	- 日志配置针对于一个日志对象

		- 查看配置

			- Flags

		- 修改配置 

			- SetFlags

				- 

		- 设定日志前缀

			- SetPerfix

		- 设定日志输出 方式

			- SetOutput

				- 可输出至文件/Stdout

- error
- testing
- pprof
- json

### 操作系统

- os

	- 操作系统相关功能

- os/exec

	- 执行操作系统命令相关功能

- syscall

	- 系统调用的接口

- path

	- 操作系统中目标文件的路径

- flag

	- 命令行参数相关功能

		- 直接从命令行中获取参数

			- 直接使用os.Arg

				- 使用range遍历

			- 是 []string 类型

				- string类型的切片

		- 定义flag命令行参数

			- 直接创建命令行变量的指针

				- name1:=flag.String("name1","qhr","姓名")
				- 因为是指针,在之后对命令行参数的参数设定时,需要对变量进行间接引用
				- 使用flag.Type()函数

			- 先声明变量,再向变量中赋值

				- flag.StringVar(&name2,"name2","wjw","xingming")
				- 变量已声明好,在引用时直接使用变量即可

		- 解析命令行参数

			- flag.Parse()

				- 解析命令行参数才可以被使用

					- 在Parse()之后可以放置命令行参数的相关逻辑

			- -flag xxx （使用空格，一个-符号）
	--flag xxx （使用空格，两个-符号）
	-flag=xxx （使用等号，一个-符号）
	--flag=xxx （使用等号，两个-符号）

				- bool类型 必须使用等号

			- -help 查看已定义好的命令行参数
			- 测试时先go build 出可执行文件 在使用 ./main -命令行参数 的方式进行测试
			- 混用命令行参数和非命令行参数时注意:

				- 对应的flag命令行参数应该位于 非命令行参数之前使用 否则位于后面的flag参数就不会生效

		- 命令行参数的其他函数

			- 

- sync
- time

	- 日期时间基本功能

		- time.Now() 获取当前时间
		- Year()/Month()/Day()/Hour()/Minute()/Second() 获取时间对象的各种信息

	- 时间戳

		- 自1970年1月1日（08:00:00GMT）至当前时间(调用的时间对象)的总毫秒数。

			- Unix()
			- UnixNano()

				- 微毫秒数

		- 将时间戳转换为时间对象

			- time.Unix(时间戳,纳秒) time

	- Duration

		- 多个常量记录时间间隔
		- Duration的函数一般都是获取这个对象的部分信息

			- Duration.Hour()

				- 这个时间段有多少hour

	- 操作时间的功能

		- Add()

			- 返回两时间之和

		- Sub()

			- 调用Sub的时间点-参数的时间点

		- Equal()

			- 两时间是否相等

		- Before()

			- 调用是否早于参数

		- After()

			- 调用是否晚于参数

	- 定时器

		- 定时器，本质上是一个通道channel
		- 每一段设定时间后向channel中放入一个当前时间的对象(Now())，channel 一旦被写入就取出数据
		- time.Tick(定时时间段)
		- 使用for-range遍历,每个遍历变量都是一个time

	- 时间的格式化输出

		- Formate(时间模版字符串)
		- 模版字符串需要保证时间点必须是2006-01-02 15:04:05.000 Mon Jan

			- 
			- Go语言的出生日期

	- 通过字符串和时区得出一个时间对象

		- LoadLocation(时区字符串)
		- PraseInLocation(模版字符串,带解析字符串,时区)
		- 注意处理错误

- runtime

	- 协程创建
	- 垃圾回收

- reflect

	- 反射相关

### 数据库

- database/sql
- driver

### 数学相关

- math

	- 基本数学函数

- cmath 

	- 复数操作

- rand 

	- 随机数相关

- big

	- 大数实现与计算

### 编解码相关

- encoding/json

	- 解析json数据

- encoding/xml

	- 解析xml数据

- text/template

	- 通过数据模版生成数据(类似于HTML)
	- 可以通过模版来表示数据

		- 通过编写模版文件
		- 在程序中编写对应变量
		- 解析模版后,向模版中镶嵌对应的变量值
		- 得出编辑后的文本文件

	- 主要流程

		- 项目外创建模版文件
		- 解析模版文件前的操作

			- 定义数据对象
			- 创建模版对象

				- New()

			- 声明自定义函数表

				- FuncMap

			- 向模版对象内导入函数表

				- Funcs

		- 解析模版文件

			- Parse
			- ParseFile

		- 向解析好的模版文件中插入数据

			- Execute函数

### 解压缩相关

- archive/tar
- zip-compress

## go基本框架相关

### gin

### gorm

## Linux常用命令

### 系统命令

- mv 移动/重命名

	- mv 文件 文件 文件 目录:将所有文件移入目录

- cat 文件 直接显示文件内容
- echo 显示环境变量值
- cp-r  文件夹1 文件夹2 复制文件夹

### vim命令

- u 撤销
- GG跳至末尾
- gg跳至文首
- :w 保存文件，不退出 vim
- :w file  -将修改另外保存到 file 中，不退出 vim
- :w!          -强制保存，不退出 vim
- :wq          -保存文件，退出 vim
- :wq!        -强制保存文件，退出 vim
- :q            -不保存文件，退出 vim
- :q!          -不保存文件，强制退出 vim
- :e!          -放弃所有修改，从上次保存文件开始再编辑

## 出现问题

### 

- 引用其他包的.go文件中的import路径不对

### 

- go 

### Go当中*_test.go结尾的文件不是go build命令编译的目标，而是go test编译的目标。

go test 子命令是Go语言包的测试驱动程序。



### GoLand中自定义包导入失败 

- go mod init+项目名
- 设置中启用GoModule

