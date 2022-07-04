解决升级node后，已经安装了最新的版本，但是默认的node版本不是最新版本还是当前版本。

最近遇到个错误：The engine node is incompatible with this module. Expected version ^6.14.0 || ^8.10.0 || >=9.10.0. Got 9.5.0

意思说你需要安装的module与当前node版本不匹配，期望升级到9.10.0版本以上。

更新node版本：

清除npm缓存：npm cache clean -f

安装n模块：npm install -g n

安装官方稳定版本：n stable

安装最新官方版本：n latest

安装某个指定版本：n 11.6.0

查看已安装的node版本: n

查看当前node版本：node -v

删除指定版本：n rm 7.5.0

指定版本执行脚本：n use 7.5.0 index.js

发现当前版本不是最新的版本，然后已经安装有了最新的版本，造成不生效的原因：

node默认的安装目录与使用管理工具n安装的目录不一致

解决方法：

查看当前node安装路径：which node

我的当前安装路径是：/usr/local/Cellar/node/9.5.0/bin/node

而 n 默认安装路径是 /usr/local，需要通过通过N_PREFIX变量来修改 n 的默认node安装路径。

![img](/Users/tiger/Desktop/qxdqhr.github.io/系统使用-MacOS/L3Byb3h5L2h0dHBzL2ltZzIwMTguY25ibG9ncy5jb20vYmxvZy8xMTE1OTE4LzIwMTkwMy8xMTE1OTE4LTIwMTkwMzAxMTU0OTIyMDI0LTQ4NDA1MDQ0MS5wbmc=.png)

编辑环境配置文件：vim ~/.bash_profile

修改node安装位置：在末尾增加export PATH=/usr/local/bin:$PATH shift+:wq 保存退出

让新配置生效：socuce ~/.bash_profile

重新安装稳定版本：n stable

查看当前node版本：node -v (已经是最新的稳定版本了)解决升级node后，已经安装了最新的版本，但是默认的node版本不是最新版本还是当前版本。

最近遇到个错误：The engine node is incompatible with this module. Expected version ^6.14.0 || ^8.10.0 || >=9.10.0. Got 9.5.0

意思说你需要安装的module与当前node版本不匹配，期望升级到9.10.0版本以上。

更新node版本：

清除npm缓存：npm cache clean -f

安装n模块：npm install -g n

安装官方稳定版本：n stable

安装最新官方版本：n latest

安装某个指定版本：n 11.6.0

查看已安装的node版本: n

查看当前node版本：node -v

删除指定版本：n rm 7.5.0

指定版本执行脚本：n use 7.5.0 index.js

发现当前版本不是最新的版本，然后已经安装有了最新的版本，造成不生效的原因：

node默认的安装目录与使用管理工具n安装的目录不一致

解决方法：

查看当前node安装路径：which node

我的当前安装路径是：/usr/local/Cellar/node/9.5.0/bin/node

而 n 默认安装路径是 /usr/local，需要通过通过N_PREFIX变量来修改 n 的默认node安装路径。

![img](/Users/tiger/Desktop/qxdqhr.github.io/系统使用-MacOS/L3Byb3h5L2h0dHBzL2ltZzIwMTguY25ibG9ncy5jb20vYmxvZy8xMTE1OTE4LzIwMTkwMy8xMTE1OTE4LTIwMTkwMzAxMTU0OTIyMDI0LTQ4NDA1MDQ0MS5wbmc=.png)

编辑环境配置文件：vim ~/.bash_profile

修改node安装位置：在末尾增加export PATH=/usr/local/bin:$PATH shift+:wq 保存退出

让新配置生效：socuce ~/.bash_profile

重新安装稳定版本：n stable

查看当前node版本：node -v (已经是最新的稳定版本了)