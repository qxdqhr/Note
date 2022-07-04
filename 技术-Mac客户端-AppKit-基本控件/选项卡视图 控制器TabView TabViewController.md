# 选项卡视图/控制器TabView/TabViewController

# 是什么

 以选项卡形式来切换管理不同视图的视图控件

# 类

选项卡视图: NSTabView

选项卡视图项: NSTabViewItem

选项卡视图控制器: NSTabViewController

# 怎么用

## 重要属性/方法

- 选项卡的项: tabViewItems
    - 通过 [NSTabViewItem] 来表示
- 确定代理方法实现类: delegate = self
- 标签条所在 tabView 的位置: tabPosition = .top
- tab边框的风格: tabViewBorderType = .line
- 向 TabView 中添加一个 Item: addTabViewItem()

## 代理方法

### 选中某一项之前调用的方法

`func tabView(_ tabView: NSTabView, shouldSelect tabViewItem: NSTabViewItem?) -> Bool`

### 选中某一项时调用的方法

`func tabView(_ tabView: NSTabView, willSelect tabViewItem: NSTabViewItem?)`

### 选中某一项之后调用的方法

`func tabView(_ tabView: NSTabView, didSelect tabViewItem: NSTabViewItem?)`

### tabView中的项数发生变化

`func tabViewDidChangeNumberOfTabViewItems(_ tabView: NSTabView)`

## 注意

1. 视图控件 所以其中一般都会包含一些子控件
2. 记住视图赋值的操作的前提是视图已经创建

## 代码实例

- 创建一个 item 的函数 在 NSTabView中添加 Item项

```swift
func getItem(_ string:String) -> NSTabViewItem{
  //item 的视图控制器
  var item1Controller = NSViewController()
  //创建这个视图控制器的所属视图
  item1Controller.view = NSView(frame: .zero)
  //创建 item
  var item1 = NSTabViewItem(viewController: item1Controller)
  //设置 item 的 tab 标签
  item1.label = string
  //item 的视图赋值
  item1.view = item1Controller.view
  //确定一个在 item 的 view 中的一个子控件
  let lbl1 = NSTextField(labelWithString: string)
  //加入子视图
  item1Controller.view.addSubview(lbl1)
  //设置布局
  lbl1.snp.makeConstraints{
      $0.center.equalToSuperview()
  }
  
  return item1
}
```

- 通过 TabController 连接子视图的 NSViewController来进行切换视图

```swift

```