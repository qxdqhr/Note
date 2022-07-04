# increbuild显示License is invalid

找到C:\Users\%USERNAME%\AppData\Roaming\Unreal Engine\UnrealBuildTool\BuildConfiguration.xml
添加bAllowXGE为false:

```
<?xml version="1.0" encoding="utf-8" ?>
<Configuration xmlns="https://www.unrealengine.com/BuildConfiguration">
	<BuildConfiguration>
    	<bAllowXGE>false</bAllowXGE>
    </BuildConfiguration>
</Configuration>
```

这个问题可能是因为你电脑上安装的increbuild对unreal使用的vs有问题。所以禁止使用XGE就好了

# UE4 报错.NET Framework SDK at 4.6.0 or higher解决

使用UE4 4.23/4.24打包时，出现报错，[识别不到.NET](https://link.zhihu.com/?target=http%3A//%E8%AF%86%E5%88%AB%E4%B8%8D%E5%88%B0.NET) 4.6以上版本。报错如下：

```text
UATHelper: Packaging (Windows (64-bit)):   ERROR: Could not find NetFxSDK install dir; this will prevent SwarmInterface from installing.  Install a version of .NET Framework SDK at 4.6.0 or higher.
PackagingResults: Error: Could not find NetFxSDK install dir; this will prevent SwarmInterface from installing.  Install a version of .NET Framework SDK at 4.6.0 or higher.
```

进入以下页面中，安装开发所需.NET运行库

[https://dotnet.microsoft.com/download ](https://link.zhihu.com/?target=https%3A//dotnet.microsoft.com/download%E9%A1%B5%E9%9D%A2%E4%B8%8B%EF%BC%8C%E5%AE%89%E8%A3%85%E5%BC%80%E5%8F%91%E6%89%80%E9%9C%80.NET%E8%BF%90%E8%A1%8C%E5%BA%93)[dotnet.microsoft.com](https://link.zhihu.com/?target=https%3A//dotnet.microsoft.com/download%E9%A1%B5%E9%9D%A2%E4%B8%8B%EF%BC%8C%E5%AE%89%E8%A3%85%E5%BC%80%E5%8F%91%E6%89%80%E9%9C%80.NET%E8%BF%90%E8%A1%8C%E5%BA%93)

安装Dev Pack！不要安装Runtime！

安装后问题解决。

建议如果使用新版本UE4时提前查看是否支持部分功能，及时更新库与相关SDK。