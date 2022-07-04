# Spring框架概述：版本Spring5

# 是什么：

1. 轻量级的：要引入的依赖jar包较少而小
2. 开源的：免费提供源代码
3. JavaEE框架：简化开发而生
4. 能做什么事情：简化开发代码

# 两个核心部分：IOC，AOP

1. IOC：控制反转：利用Spring创建对象,并为对象赋值
2. AOP：面向切面：不修改源代码情况下增强功能

# Spring的特点：

1. 方便解耦，简化开发
2. AOP的支持
3. 方便程序的测试
4. 方便集成其他框架（MyBatis）
5. 方便进行事务的操作
6. 降低API开发难度

# IOC容器

1. 什么是IOC？使用XML文件和Spring框架来创建对象
    1. IOC（控制反转） 的目的：降低代码间的耦合性
    2. 无需自己创建对象，将对象的创建和对象之间调用的过程，均交给Spring框架来管理
2. IOC底层的原理：
    1. XML解析
    2. 工厂设计模式
    3. Java反射机制

# 使用Spring的IOC方式创建对象并赋值

## 建立Spring项目

1. 下载Spring框架
2. 新建普通java项目
3. 在项目目录中创建lib文件夹，并导入相关jar包
4. 创建普通类及类方法

## 使用XML配置文件创建对象:spring1

1. 直接创建xml文件
2. 在<beans>标签中写一个bean标签
3. 程序中测试
    1. 加载配置文件
4. **Spring中的获取配置文件默认通过类的无参构造函数创建对象**

## 为对象赋值(属性注入)

### 对象的基本类型赋值:spring2

1. Set方法注入
2. 有参构造方法注入
3. p标签名称空间注入（用于简化标签格式）

### 对象的特殊值赋值:spring3

1. **null值**：null标签
2. **值中带有特殊符号（字符串):**
    1. 转义字符：&lt;&gt
    2. <![CDATA[值]]>
3. **对象作为成员的赋值:**
    1. 外部bean注入属性:使用**ref标签引用其他bean标签**
    2. 内部bean注入属性:直接在**propertry标签中附加bean标签** 
4. **对象中包含Set,Array,Map,List类型的成员**
    1. 结构元素为基本类型:
        1. array:
            
            ```xml
            <property name="names">
                <array>
                    <value>数据库</value>
                    <value>计算机网络</value>
                    <value>数据结构</value>
                </array>
            </property>
            ```
            
        2. list:
            
            ```xml
            <property name="list">
                <list>
                    <value>A</value>
                    <value>B</value>
                    <value>C</value>
                </list>
            </property>
            ```
            
        3. map:
            
            ```xml
            <property name="map">
                <map>
                    <entrykey="java"value="JAVA"></entry>
                    <entrykey="C"value="c"></entry>
                </map>
            </property>
            ```
            
        4. set:
            
            ```xml
            <property name="set">
                <set>
                    <value>MYSQL</value>
                    <value>REDIS</value>
                </set>
            </property>
            ```
            
    2. 结构元素为自定义类型:
        
        ```xml
        <property name="courseList">
            <list>
                <value>MYSQL</value>
                <value>REDIS</value>
            </list>
        </property>
        ```