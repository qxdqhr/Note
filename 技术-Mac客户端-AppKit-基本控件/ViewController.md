# ViewController

# 是什么

- 最基本的视图控制器

- 实现了不同视图控制器之间的跳转方式接口
    
    ![IMG_E549023A998D-1.jpeg](ViewController%20b52e493ffe06405c99d1371df3a6d570/IMG_E549023A998D-1.jpeg)
    

- 用于存放子视图/子视图控制器
    
    ![IMG_BBB57F627E33-1.jpeg](ViewController%20b52e493ffe06405c99d1371df3a6d570/IMG_BBB57F627E33-1.jpeg)
    

- 管理视图生命周期
    
    ![IMG_3847D4433F8E-1.jpeg](ViewController%20b52e493ffe06405c99d1371df3a6d570/IMG_3847D4433F8E-1.jpeg)
    
- 显示方式:(2 种:)
    - 视图向窗口赋值子视图 : `NSWindow.main.window?.contentView = NSViewController.view`
    - 窗口以子视图控制器赋值 : `NSWindow.init(contentViewController: NSViewController)`

# 类

- NSViewController

# 怎么用

## 1. View 的生命周期

1. 加载视图  
2. 准备显示
3. 开始布局
4. 显示完成 

### 视图控制器打开视图:(实际函数调用顺序)

1. 外部通过 ViewController 访问 View 
    - View 为空 :`loadView` 会从 xib/storyboard 中加载视图
    - View 不为空 :`loadView` 会加载 View
2. 试图加载完成 , 调用 `viewDidLoad`  
3.  View 显示之前 调用 `viewWillAppear`
4. 布局相关方法
    1. `updateViewConstrains`
    2. 布局之前: `viewWillLayout`
    3. 布局之后 : `viewDidLayout`
5. View 显示完成后 调用 `viewDidAppear`

### 视图控制器关闭视图:

1. 关闭视图之前 调用 `viewWillDisappear` 
2. 关闭视图之后 调用 `viewDidDisappear`

## 2. 创建视图的方法

### XIB 方式创建

### StoryBoard 方式创建

### 代码直接创建

```swift
//ViewController类外创建视图控制器
let viewController = NSViewController()
let frame = CGRect(x:0,y:0,width:100,height:100)
viewController.view = NSView(frame:frame)

//ViewController类内 通过重写 loadView 函数并在其中执行类似代码
class MyViewController:NSViewController{
	override funcloadView(){
		let frame = CGRect(x:0,y:0,width:100,height:100)
		self.view = NSView(frame:frame)
	}
}
```

## 3. 重要属性:

### representObject 属性

- 当前绑定的 数据模型对象
- 通用的模型属性对象，通过修改它可以实 现UI的更新
- CollectionView 中
    - 通过在`func collectionView(_ collectionView: NSCollectionView, itemForRepresentedObjectAt indexPath: IndexPath) -> NSCollectionViewItem` 函数中
    - 为CollectionView 的 representObject属性进行赋值
    - 并在 CollectionViewItem 类中 覆盖 Item的representObject属性来获取到每一个 Item的值
    - 实现每一项的赋值

### 子视图相关:

- 父视图控制器 : parent : NSViewController?
- 所有的子视图控制器 : childViewController  : [NSViewController]
- 增加子视图控制器方法 : `func addChildViewController(_ childViewController: NSViewController)`
- 从父视图控制器中删除自身视图 :`func removeFromParentViewController()`

## 4.多个子视图控制器的切换显示方式

- Popover `func presentViewController(_ viewController: NSViewController, asPopoverRelativeTo positioningRect: NSRect, of positioningView: NSView, preferredEdge: NSRectEdge, beh avior: NSPopoverBehavior)`
- 模态方式 `func presentViewControllerAsModalWindow(_ viewController: NSViewController)`
- sheet `func presentViewControllerAsSheet(_ viewController: NSViewController)`
- 自定义动画模式 `func presentViewController(_ viewController: NSViewController, animator: NSViewCont rollerPresentationAnimator)`
- 子视图间转场变换 `func transition(from fromViewController: NSViewController, to toViewController: NSViewController, options: NSViewControllerTransitionOptions = [], completionHandler c ompletion: (() -> Swift.Void)? = nil)`
- 关闭切换显示的 controller
    - `func dismissViewController(_ viewController: NSViewController)`
    - `func dismiss(_ sender: AnyObject?)`

## 5. 视图中的手势识别

- NSClickGestureRecognizer (点击)
- NSPanGestureRecognizer (滑动)
- NSPressGestureRecognizer (按)
- NSMagnificationGestureRecognizer (缩放)
- NSRotationGestureRecognizer (旋转)