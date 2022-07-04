# 菜单项菜单栏:Menu

# 是什么

- 各种位置上的菜单栏,菜单项
- 顶部菜单栏
- 视图右键菜单栏
- 程序坞右键产生的菜单栏
- 状态栏右键产生的菜单栏

# 类

- NSMenu
- NSMenuItem

# 怎么用

## 菜单的结构

- 上级菜单(项)连接下级菜单(项)

## 程序顶部菜单栏

- 如果未删除 xib 文件 菜单栏会自动显示默认形式
- 在 AppDelegate 类 的 `applicationDidFinishLaunching` 方法中调用
    - 菜单结构添加好后 需要设定创建的根菜单为主菜单
        
        ```swift
        NSApp.mainMenu = mainMenu
        ```
        
- 结构
    
    ```swift
    |____根菜单 NSMenu
        |____根菜单项 NSMenuItem :第一菜单项
    		|		|____第一菜单项的下属菜单 NSMenu :实际会显示在菜单栏上的菜单,名字为NSMenu 的 title 属性 (第一个下属菜单,名称默认为项目名称)
    		|				|____第一菜单项的下属菜单的菜单项1:NSMenuItem
    		|				|____第一菜单项的下属菜单的菜单项2:NSMenuItem
    		|				|____第一菜单项的下属菜单的菜单项3:NSMenuItem
    		|						|____第一菜单项的二级下属菜单项1:NSMenu
    		|								|____第一菜单项的下属菜单的菜单项1:NSMenuItem
    		|								|____第一菜单项的下属菜单的菜单项2:NSMenuItem
        |____根菜单项 NSMenuItem :第二菜单项  
    				|____第二菜单项的下属菜单 NSMenu :实际会显示在菜单栏上的菜单,名字为NSMenu 的 title 属性 
    						|____第二菜单项的下属菜单的菜单项1:NSMenuItem
    						|____第二菜单项的下属菜单的菜单项2:NSMenuItem
    						|____第二菜单项的下属菜单的菜单项3:NSMenuItem
    ```
    
- 上级菜单(项)连接下级菜单(项)
    
    ```swift
    //上级NSMenu 连接下级 NSMenuItem
    menu.addItem(menuItem)
    //上级NSMenu 连接下级 NSMenu
    menuItem.submenu = menu
    ```
    

## 程序坞右键菜单

- 在 AppDelegate 类中实现 `func applicationDockMenu(_ sender: NSApplication) -> NSMenu?` 协议方法中调用
- 菜单结构与上述相同
    
    ```swift
    //程序坞右键菜单
        func applicationDockMenu(_ sender: NSApplication) -> NSMenu? {
            let menu = NSMenu()
            menu.addItem(NSMenuItem(title: "aa", action: nil, keyEquivalent: ""))
            menu.addItem(NSMenuItem(title: "aa", action: nil, keyEquivalent: ""))
            return menu
        }
    ```
    

## 视图右键菜单

- 视图控制器中 重写的`viewDidLoad`函数中设定视图的菜单 即可完成

```swift
override func viewDidLoad() {
    super.viewDidLoad()
    view.menu = popMenu //设置视图右键的菜单
}
```

## 按钮点击创建菜单

- 视图控制器中创建
    - 按钮控件
    - 菜单控件
- 按钮点击事件中
    - 设定好要创建菜单的位置
    - 菜单控件调用 popUp(positioning: nil, at: point, in: view) 函数
    
    ```swift
    @objc func popUpBtn(sender:NSButton){
            var point = sender.frame.origin
            point.x = point.x + sender.frame.size.width
            popMenu.popUp(positioning: nil, at: point, in: view)
            
        }
    ```
    

## 菜单可用性TODO

- validateMenuItem