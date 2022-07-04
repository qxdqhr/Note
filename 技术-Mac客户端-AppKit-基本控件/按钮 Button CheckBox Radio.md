# 按钮:Button/CheckBox/Radio

- 参考:  [https://blog.csdn.net/lovechris00/article/details/83446855](https://blog.csdn.net/lovechris00/article/details/83446855)

# 是什么

- 常见的按钮
- 以及其他类型的按钮
    - 多选框:CheckBox
    - 单选框:Radio

# 常用子类/类

- NSButton

# 常用属性

- 按钮文字 : title = "按钮"
- 发送事件的类 事件函数所在类 : target = self
- 触发事件函数 : action = #selector(btnOnClick)
- 状态文字 : alternateTitle = "选中"
- 按钮状态 : state = NSControl.StateValue.mixed
- 按钮图片 : image  = NSImage.init(named: "icon_norm")
- 状态图片 : alternateImage = NSImage(named: "icon_high")
- 图片文字位置 : imagePosition = NSControl.ImagePosition.imageBelow
- 图片缩放 : imageScaling = NSImageScaling.scaleNone
- 突出显示 isHighLighted
    - 一般使用事件函数实现突出显示而非此属性

## checkBox属性

- CheckBox控件在触发点击事件时系统会自动的 改变其 .state

```swift
private lazy var checkBox: NSButton = {
	var ctrl = NSButton()
	ctrl.setButtonType(.switch)
	ctrl.state = .on
	ctrl.target = self
	ctrl.action = #selector(checkBoxOnClick)
	return ctrl
}()
```

## radio属性

```swift
private lazy var radio: NSButton = {
    var ctrl = NSButton()
    ctrl.setButtonType(.radio)
    ctrl.state = .off
    ctrl.target = self
    ctrl.action = #selector(checkBoxOnClick)
    ctrl.tag = 2 //用于判断逻辑
    return ctrl
}()
```

## 外观

- 是否有边框 : isBordered = true
- 是否透明 : isTransparent = false
- highlight(true)
- 是否高光显示 : isHighlighted = true

## 快捷键

- 设定快捷键 触发方式与输入对应字符相同 , 值会覆盖,重复赋值取最新
    - keyEquivalent = "z"
- 与对应快捷键,配对的辅助按键
    - 数组中元素表示触发时需要一同按下
    - keyEquivalentModifierMask = [ NSEvent.ModifierFlags.option , .shift]

# 常见事件函数

```swift
@objc func btnOnClick (sender:NSButton){
    print("push Button")
}
@objc func checkBoxOnClick (sender:NSButton){
    print("push checkbox")
    var flag = (sender.state == .on)
    print(flag,sender.state)
  sender.state = ( flag ? .on : .off)
}
```

# 常用按钮配置

## 无边框按钮

```swift
func noBoardBtn() -> NSButton {
    var ctrl = NSButton(frame: NSRect(x: 0, y: 0, width: 0, height: 0))
    ctrl.bezelStyle = NSButton.BezelStyle.roundRect
    ctrl.bezelColor = NSColor.clear
    ctrl.isBordered = false
    ctrl.wantsLayer = true
    ctrl.layer?.backgroundColor = CGColor.clear
    ctrl.imagePosition = NSControl.ImagePosition.imageLeft
	  return ctrl
}
```

## 纯图片按钮

```swift
func picBtn() -> NSButton {
    var ctrl = NSButton(frame: NSRect(x: 0, y: 0, width: 0, height: 0))
    ctrl.image = NSImage(named: "aaa")
    ctrl.imageScaling = NSImageScaling.scaleNone
    ctrl.imagePosition = NSControl.ImagePosition.imageOnly
    return ctrl
}
```

## 设置按钮文字颜色

```swift
func coloredBtn(color:NSColor?) -> NSButton {
    var col = color
    if col == nil {
        col = NSColor.red
    }
    let ctrl = NSButton(frame: NSRect(x: 0, y: 0, width: 0, height: 0))
    ctrl.attributedTitle = NSMutableAttributedString(string: "a", attributes:([
        .font  : self.btn.font as Any,
        .foregroundColor : col
    ]))
    
    return ctrl
}
```

## 按钮文字靠左

```swift
func textLeftBtn(color:NSColor?) -> NSButton {
    var col = color
    if col == nil {
        col = NSColor.red
    }
    let ctrl = NSButton(frame: NSRect(x: 0, y: 0, width: 0, height: 0))
    ctrl.attributedTitle = NSMutableAttributedString(string: "a", attributes:([
        .font            : self.btn.font as Any,
        .paragraphStyle  : NSParagraphStyle.default,
        .foregroundColor : col
        
    ]))
    
    return ctrl
}
```