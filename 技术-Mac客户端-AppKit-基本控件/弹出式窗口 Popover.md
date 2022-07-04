# 弹出式窗口:Popover

- [https://blog.csdn.net/lovechris00/article/details/77996141](https://blog.csdn.net/lovechris00/article/details/77996141)

# 是什么

- 弹出式窗口

# 类

- NSPopover

# 怎么用

## 重要属性

- 何种行为会关闭弹出窗口: behavior
    - .semitransient 点击弹出窗口以外,且 在 App 窗口之内时会关闭
    - .transient 点击弹出窗口以外 时 会关闭
- animates = true
- 必须是带有 view 的 viewController:
    - contentViewController = CollectionViewViewController()
- 弹出窗口的外观
    - ctrl.appearance = NSAppearance(named: .vibrantDark)

## 使用流程

1. 作为控件定义在父视图控制器中
2. 设置属性
3. 动作函数中 弹出窗口控件调用 
    1. `show(relativeTo:` sender.bounds`, of:` sender`, preferredEdge:` .max`)`
        1. `relativeTo` 显示时参考矩形 一般是 positioningView 的 bounds
        2. `of` 显示时的参考点 View
        3. `preferredEdge` 显示的位置参考的边