# 下拉菜单:Combo Box

- 参考 [https://blog.csdn.net/lovechris00/article/details/77986945](https://blog.csdn.net/lovechris00/article/details/77986945)

# 是什么

- 下拉菜单

# 重要的类

- NSComboBox
- 继承自 NSTextField（所以有 backgroundColor 属性）。

# 重要属性

- 同NSTextField

# 不使用数据源代理

```swift
private lazy var comboBox: NSComboBox = {
    var ctrl = NSComboBox()
    ctrl.backgroundColor = NSColor.yellow
//不使用数据源
    ctrl.usesDataSource = false
    ctrl.addItems(withObjectValues: datas)
//        ctrl.removeItem(withObjectValue: "虎") //值删除
//        ctrl.removeItem(at: 0) //索引删除
//        ctrl.removeAllItems()
    ctrl.selectItem(at: 0) //将哪一项作为默认显示
    return ctrl
}()
```

# 如何使用协议

- 实现 NSComboBoxDelegate, NSComboBoxDataSource 协议种方法

## 重要的属性

```swift
private lazy var comboBox: NSComboBox = {
    var ctrl = NSComboBox()
    ctrl.backgroundColor = NSColor.yellow //背景颜色
    ctrl.usesDataSource = true //是否使用数据源 (必选)
    ctrl.isEditable = false //是否可编辑
    ctrl.dataSource = self //实现 NSComboBoxDataSource 协议的类
    ctrl.delegate = self //实现 NSComboBoxDelegate 协议的类
//        ctrl.selectItem(at: 0) //初始化即选中哪一项
    return ctrl
}()
```

## 需要实现的协议方法

- datas 是一个存放内容的数组

```swift
//NSComboBoxDataSource协议实现
func numberOfItems(in comboBox: NSComboBox) -> Int {
    return datas.count
}
func comboBox(_ comboBox: NSComboBox, objectValueForItemAt index: Int) -> Any? {
    return self.datas[index]
}
//NSComboBoxDelegate协议实现
//触发先调用
func comboBoxSelectionIsChanging(_ notification: Notification) {
    var comboBox = notification.object as? NSComboBox
    print("change1",datas[comboBox?.indexOfSelectedItem ?? 0])
}
//触发再调用
func comboBoxSelectionDidChange(_ notification: Notification) {
    var comboBox = notification.object as? NSComboBox
    print("change",datas[comboBox?.indexOfSelectedItem ?? 0])
    
}
```

# 事件方法

- 按钮点击事件