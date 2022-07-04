# GO 概述

- 21世纪的C语言
- 企业级编程语言
-  天生支持并发

# Go 开发环境的安装

## 安装GO开发包

- 下载链接:https://studygolang.com/dl

![image-20210312185309842](.\GO.assets\image-20210312185309842.png)

- 安装后测试版本 go version

  ![image-20210312185358540](.\GO.assets\image-20210312185358540.png)

## GO PATH

- 存放Go语言项目的开发目录,默认在安装时自动配置到:**C:\Users\用户名\go**

- 为方便存放项目,更改为D:/Go Path

![image-20210312185700688](.\GO.assets\image-20210312185700688.png)

### Go Path 的配置

- Go Path 文件夹下需要新建bin pkg src文件夹

  - src:存放Go 语言源代码
  - pkg:编译时中间状态的包
  - bin:编译后生成的可执行文件

- 环境变量中需要将bin目录加入 PATH环境变量中

  ![image-20210312190448852](.\GO.assets\image-20210312190448852.png)

## 检查Go环境配置是否成功:

- 使用命令 go env

![image-20210312190728447](.\GO.assets\image-20210312190728447.png)

# Go项目的目录结构

![image-20210312190951613](.\GO.assets\image-20210312190951613.png)

![image-20210312194228334](.\GO.assets\image-20210312194228334.png)

# GO开发IDE

GO使用UTF-8文本文件方式存放源代码

## 常用IDE 

VS Code:开源

Go Land:付费

## 安装扩展

- 扩展栏-搜索go-下载VSCode的go插件

## 安装Go语言的插件

### 安装Git

官网下载安装包

# VSCode安装插件

## 修改网络连接(国内无法访问)

- 之后或许可以使用VSCode自行更新包

```
go env -w GOPROXY=https://goproxy.cn
```

## 下载工具包

在%GOPATH%\src\目录下，建立路径golang.org\x
进入到%GOPATH%\src\golang.org\x，下载需要工具的源码git clone https://github.com/golang/tools.git （tools可以是其它项目名）
clone完成后，会生成一个tools文件夹，这样工具所需要的源码已经准备好了
进入到%GOPATH%下，执行

```
go get github.com/rogpeppe/godef
go get github.com/cweill/gotests/gotests

go install github.com/acroca/go-symbols@latest
go install github.com/cweill/gotests@latest
go install github.com/cweill/gotests/gotests@latest
go install github.com/golang/lint/golint@latest
go install github.com/lukehoban/go-outline@latest
go install github.com/newhook/go-symbols@latest
go install github.com/nsf/gocode@latest
go install github.com/ramya-rao-a/go-outline@latest
go install github.com/rogpeppe/godef@latest
go install github.com/sqs/goreturns@latest
go install github.com/zmb3/gogetdoc@latest
go install golang.org/x/tools/cmd/gorename@latest
go install golang.org/x/tools/cmd/guru@latest
go install sourcegraph.com/sqs/goreturns@latest
go install golang.org/x/lint/golint@latest
```



GO的明星作品:

docker

kubernetes

非完全兼容C语言



goland中自定义的包无法引入，提示 package **** is not in GOROOT (***)

解决步骤：

第一步，在项目的当前目录里，执行命令：go mod init ，会在当前项目目录下自动创建go.mod文件。

第二步，在命令行下，进入当前项目目录，执行命令：go run main.exe，此时会自动下载和关联该项目用到的包。

 

执行完后，go.mod文件内容中会有引用的相关包。项目就可以正常运行了。