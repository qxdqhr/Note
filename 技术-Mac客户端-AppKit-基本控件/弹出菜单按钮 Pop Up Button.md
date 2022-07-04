# 弹出菜单按钮:Pop Up Button

# 是什么

- 弹出菜单
- 下拉菜单

# 所属类

- NSPopUpButton
- NSButton的子类

# 如何使用

## 常用属性

- 是否为下拉 : pullsDown
    - true : 下拉菜单方式显示窗口
    - false : 弹出式显示窗口
- 菜单出现位置 : preferredEdge
    - .maxX  点击产生的菜单出现在 横坐标最大位置
    - .minX   点击产生的菜单出现在 横坐标最小位置
    - .maxY  点击产生的菜单出现在 纵坐标最大位置
    - .minY   点击产生的菜单出现在 纵坐标最小位置

```swift
private lazy var popUpBtn: NSPopUpButton = {
    var ctrl = NSPopUpButton(title: "", target: self, action: #selector(pushEvent))
    ctrl.pullsDown = false
//        ctrl.preferredEdge = .maxX //点击产生的菜单出现在 横坐标最大位置
        ctrl.preferredEdge = .minX //点击产生的菜单出现在 横坐标最小位置
//        ctrl.preferredEdge = .maxY //点击产生的菜单出现在 纵坐标最大位置
//        ctrl.preferredEdge = .minY //点击产生的菜单出现在 纵坐标最小位置
    ctrl.addItems(withTitles: datas)
    return ctrl
}()
```

- 弹出菜单项数: numberOfItems
- 选中菜单项的下标: indexOfSelectedItem
- 选中项的字符串: titleOfSelectedItem as Any

## 方法

- 获取对应项的内容字符串: itemTitle(at: )