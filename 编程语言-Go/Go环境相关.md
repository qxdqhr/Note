# Goland安装 :

Mac上需要下载ARMv8框架的安装包(?)

## Goland 无法调试:

MacBookPro 使用M1芯片,但在Goland2020.3.2后,修复了这一点,若配置文件被修改,需要将其复原,即:

- 编辑自定义设置
- 删除dlv.path=/path/to/delve/binary 这一行
- 重启Goland

# Go Moudule

## GoPath的弊端:版本不一致问题

- 没有版本控制的概念
  - 使用go get 命令只能获取最新的包
- 无法保证依赖库的版本一致性
  - 无法同步一致的版本号
  - 无法指定当前项目引用的依赖库的版本号

## 使用Go Module创建项目

- 设定go env -w GO111MODULE=on

  - 或(linux source~/.bashrc中)用户启动脚本中 export GO111MODULE=on

- 使用mkdir命令创建文件夹 (不要求在$GOPATH/src)

  - 项目名/模块名

- 移动至模块名目录下,使用命令 **go mod init+当前模块名称**

  - 会生成对应的 go.mod文件
  - 其中保存着模块路径以及go版本号

- 创建main.go文件,添加需要依赖项的代码,**注意:此时依赖包并没有下载**

  - 使用Go Path:将依赖的文件全部下载后放在src目录下
  - 使用Go Module:(更新go.mod文件,生成go.sum文件) 
    - 使用命令: go get +依赖包网址
    - 最终下载包文件到了GOPATH/pkg/项目名/引用包名+校验码的文件
    - 使项目可以位于任意路径,仍可以保证所有依赖均有效

- 在go.mod文件中就会出现如下语句:

  - require 依赖包网址 版本号 //indirect(表示仅依赖主包的几个子包,即部分依赖)

- go.sum文件如下所示:(保证当前下载的库是完整的库)

  - 标明了 引用的包的地址 版本号 校验码h1 (所有文件的hash值,不存在则表示依赖的库有可能用不上)

  ![截屏2021-06-30 下午8.28.42](/Users/didi/Library/Application Support/typora-user-images/截屏2021-06-30 下午8.28.42.png)

  

# 修改项目模块的依赖关系

- 使用命令 go mod edit -replace=要替换的的依赖名(过去使用过的依赖位于GOPATH/pkg/项目名/引用包名+校验码的文件)

- 此命令执行后 go.mod文件中会出现新的行
  - replace 包=>包
  - 国外的包无法访问时,可以重定向到可以使用的包,保证依赖的完整性
