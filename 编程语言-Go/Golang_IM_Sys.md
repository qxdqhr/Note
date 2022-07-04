

# Demo1:服务器监听客户端连接

## Server类 server.go

- 构造函数
  - IP,端口号赋值
- 服务器启动函数
  - 根据IP端口号 net.Listen() 创建监听socket,有错误返回
  - defer close socket
  - 循环 accept 获取conn,客户端连接
  - 监听到客户端连接,即创建go程处理客户端连接
- 处理客户端连接函数
  - 通过go程调用,将接收到的客户端连接作为参数传入

## main.go

- 创建Server类对象
- server调用Start函数

# Demo2:服务器监听用户上线并广播

## User类 user.go

- 构造函数
  - 从conn连接中获取远程网络地址
  - 创建User对象,各项赋值
- 监听函数
  - 读取UserChan数据,通过网络发送给客户端
  - User一旦被创建好,就说明当前新用户已上线,服务器需要不断将User成员channel中的数据通过网络发送给对应客户端
  - 在构造函数中创建好User对象之后即可开启go程调用监听函数

## Server类的补充

- 补充成员并make初始化
  - 用户上线映射表(网络地址&User对象)
    - map的读写锁,无需初始化
  - 用于广播消息的channel(向各个User的channel中发送数据的channel)
- handle方法的补充
  - 创建User对象并赋值
  - 更新在线用户映射表(加锁maplock)
  - 向Servchannel发送数据
- 发送数据到ServChannel函数
  - 拼接好要发送的数据
  - 将数据写入成员的ServChan
- 广播函数(监听ServChan函数)
  - listen(socket)建立完成后调用
  - 不断地(go程调用)
    - 从ServChan中读取数据
    - 循环遍历map(加锁),对于每一个用户发送对应消息

# Demo3:添加用户广播功能

- Server类的补充
  - handler函数的补充
    - 广播已上线的消息之后,使用go程调用等待客户端数据函数
  - 等待客户端数据函数
    - 创建读取数据缓冲区make
    - 不断地
      - 从conn中读取数据并返回读取长度和错误码
      - 读取长度为0表示use正常下线
      - 错误码非空且错误码不为io.EOF表示读取出错
      - 获得缓冲区中数据(不包含最后的\n)
      - 将获得的数据加入ServerChannel,将其广播

# Demo4:重构代码结构

- Server.go中的如下几个功能属于User的动作应在user.go中实现
- User类中添加相关联的Server对象
  - 用户上线:map赋值对应上线用户,向Servchannel发送广播上线消息
  - 用户下线:map中删除对应下线用户,向Servchannel发送广播下线消息
  - 用户处理数据:switch处理msg

# Demo5:添加查看在线用户功能

- 用户处理数据函数中添加switch的case:
  - 若输入whoisonline 遍历map,获得每一个在线用户
  - 拼接出对应字段
  - 直接通过user的conn直接发送回查询的用户

# Demo6:更改用户名功能

- 用户处理数据函数中添加switch的case:
  - 传来的msg形态类似于“rename|张三”
    - 长度大于7
    - msg的1-7位 == “rename|”
  - 判断后一部分newname在map中是否存在
    - 存在则输出姓名已被占用
    - 不存在
      - 在map中删除掉旧的name-user元素
      - 生成新name-user元素
      - 修改user对象中的name元素
      - 发回给原User,新的name

# Demo7:超时强退功能

- sever.go的handle函数中:
  - 创建一个用于监听用户是否活跃的channel
  - 一旦开始处理用户数据，则代表用户是活跃的，向channel 中写入true
  - 保证当前handle阻塞,使用select+for 进行监听
    - select监听到isAlive可读出时,执行更新计时器的操作
    - select监听到计时器超时操作,执行超时时的工作

```Go
for{
   select {
   case <-isAlive:
   case <-time.After(time.Second*5):
      //超时的写法，提示用户超时
      user.SendMsg("已被踢下线")
      //销毁user用资源
      close(user.UserChannel)
      //删除对应映射
      delete(this.OnlineMap,user.Name)
      //关闭连接
      conn.Close()
      return

   }

}
```