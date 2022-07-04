学习爬虫时按照视频教程里的方法安装过一次，但是后来电脑重装系统了，没看教程自己配置了一下午也没搞定，特别是lxml的安装，因此记录一下。

#### ***\*运行环境\****

Win7 64位 + Python3.5.2

#### ***\*安装前的准备\****

1.确保Python安装成功,勾选add Python 3.5 to path
2.在cmd中输入pip --version确保pip可用

#### ***\*爬虫需要的库\****

BeautifulSoup4
requests
lxml

#### ***\*BeautifulSoup4的安装\****

可以在Pycharm中安装，也可以在命令行中安装，我采用了命令行安装，打开cmd，输入

pip3 install beautifulsoup4

#### ***\*requests安装\****

同样可以通过两种方式安装，在命令行中输入

pip3 install requests

#### ***\*lxml的安装\****

lxml的安装不同于前两个库的安装，稍微麻烦一点

###### ***\*1.下载lxml文件\****

下载地址：[lxml](#lxml)
找到lxml的位置，会看到一系列.whl文件，根据自己的Python版本和Windows版本选择相应的文件下载，cp代表Python版本，cp35指Python3.5，win32指Windows32位，amd64指Windows64位。***\*下载后不要修改文件名\****。

![img](D:\我的坚果云\笔记图片\wps1.jpg) 

###### ***\*2.安装whl\****

命令行输入

pip3 install wheel

###### ***\*3.安装lxml\****

找到whl的下载路径，在cmd里切换到该路径，输入

pip3 install xxx.whl

\#xxx是whl文件的名字

 