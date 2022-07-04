# TODO:表格视图: Table View

# 是什么

 表格视图

# 类

- 表格视图 : NSTableView
- 放置表格的滚动视图 : NSScrollView
- 表格列 : NSTableColumn

# 怎么用

1. 需要 NSScrollView 控件承接 : 设定 NSScrollView 的 documentView 属性为要显示的表格控件
2. 

## 重要属性

1. 代理 : delegate
2. 数据源 : dataSource
3. 表格网格线设置 : gridStyleMask
4. 表格背景色 : backgroundColor 
5. 是否表格背景颜色交替 : usesAlternatingRowBackgroundColors
6. 表格行选中样式 : style
7. 设定双击表格项 的事件函数 : doubleAction

## 代理方法

### 数据源

- 返回表格中的项数

```swift
func numberOfRows(in tableView: NSTableView) -> Int {
        return self.datas.count
}
```

### 基于cell的表格

- 一般只显示值的表格(?)
- 重写函数 : `func tableView(_ tableView: NSTableView, objectValueFor tableColumn: NSTableColumn?, row: Int) -> Any?`

```swift
func tableView(_ tableView: NSTableView, objectValueFor tableColumn: NSTableColumn?, row: Int) -> Any? {
    let data = datas[row] //获取到要显示的行
    let key = tableColumn?.identifier //获取当前这一列的标识符
    let value = data[key!.rawValue] //从数据源中获取对应数据
    return value
}
```

### 基于View的表格

- 可以向单元格中添加控件
- 重写函数 : `func tableView(_ tableView: NSTableView, viewFor tableColumn: NSTableColumn?, row: Int) -> NSView?`

```swift
//view 模式的赋值
    func tableView(_ tableView: NSTableView, viewFor tableColumn: NSTableColumn?, row: Int) -> NSView? {
        //获取当前列的标识符
        let key = (tableColumn?.identifier)!
        //创建单元格cell视图
        var view = tableView.makeView(withIdentifier: key, owner: self)
        if (view == nil){
            view = NSView()
        }
        //获取当前行的 数据值 类内数组
        let dic = datas[row]
        guard let value = dic[key.rawValue] else { return nil }
        //判断当前列的标识符是哪一列
        if(key.rawValue == "name" || key.rawValue == "gender" || key.rawValue == "job" || key.rawValue == "name"){
            var textField = NSTextField(labelWithString: value)
            view?.addSubview(textField)
        }
        else if(key.rawValue == "married" ){
            var checkBoxField = NSButton(checkboxWithTitle: value, target: self, action: nil)
            view?.addSubview(checkBoxField)
            checkBoxField.state = NSControl.StateValue(rawValue:  value == "yes" ? 1:0)
        }
        return view
    }
```

### 选中按钮时发送通知

```swift
//点击选中事件函数
    func tableViewSelectionDidChange(_ notification: Notification) {
        let tableView = notification.object as! NSTableView
        let row = tableView.selectedRow
        let col = tableView.selectedColumn
        print("\(row) \(col)")
    }
```

### 创建表格三级菜单

 

```swift

```

### 表格排序