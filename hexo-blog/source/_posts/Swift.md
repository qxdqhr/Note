除了使用函数做为获取接口的方法外,在swift中给出了[private](https://so.csdn.net/so/search?q=private&spm=1001.2101.3001.7020)(set)申明的方式来限制外部对属性的修改.但在当前文件中依然可改.

~~~
private(set) var name : String?
~~~

