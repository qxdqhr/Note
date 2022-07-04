# 文本输入框:TextField

- 参考 [https://blog.csdn.net/lovechris00/article/details/78012495](https://blog.csdn.net/lovechris00/article/details/78012495)

# 是什么

- 常见的单行文本输入框

# 常用子类/类

- 基本文字输入控件: NSTextField
- 安全文字输入控件 : NSSecureTextField
    - 用于输入密码 文字会变为 ●

# 常用属性

- 输入框文字 : cell?.title = "aaa”
    - 输入框创建时就存在与文本框中的字符串
- 提示性文字 : placeholderString = "ccc”
    - 输入框未输入时的文字
- 提示性富文本文字: placeholderAttributedString
- 文字颜色: textColor = NSColor.yellow
- 是否可编辑: isEditable  = true
- 是否可选中: isSelectable = false
- 输入框中的普通文本内容(获取/修改): stringValue
- 输入框中的富文本内容(获取/修改): attributedStringValue
- 文本框背景颜色: backgroundColor
- 去掉外框响应 : focusRingType = NSFocusRingType.none

# 需要实现的 代理方法

- 代理方法需要在控件的定义中设置 delegate 属性为某一类 后即可遵守协议重写方法

## 光标进入文本框后按下键盘时 发送通知

- 开始编辑之后会调用
- `func controlTextDidBeginEditing(Notification)`

## 光标离开文本框 发送通知 : 点击其他控件时触发

- `func controlTextDidEndEditing(Notification)`

## 文本框内容发生变化后 发送通知 :每次输入后都会触发

- `func controlTextDidChange(Notification)`

# 其他常用方法

- NSControl 中 NSObjectProtocol协议的可选代理方法
- 可以用于 NSTextField / NSMatrix 类中

## 检测文本内容是否改变

- `control(_ control: NSControl, isValidObject obj: Any?) -> Bool`
- *输入文字后，在 EndEditing 之前调用。如果文字没有改变，就不会调用。*
- *返回 false 时，这个窗口不会响应其他的点击事件（不能去填别的）。*

## 是否允许文本框开始输入

- `control(_ control: NSControl, textShouldBeginEditing fieldEditor: NSText) -> Bool`
- `control` 表示 输入的控件 可以用来判断哪个控件可以开始输入
- 返回 true 允许开始输入
- 返回 false 禁止开始输入

## 是否允许文本框结束输入

- `control(_ control: NSControl, textShouldEndEditing fieldEditor: NSText) -> Bool`
- 返回 true 允许结束输入
- 返回 false 禁止结束输入

## 在文本框中按下特定按键后会触发的方法

- `func control(_ control: NSControl, textView: NSTextView, doCommandBy commandSelector: Selector) -> Bool`
- `commandSelector`.description 为按下按键的名称
- `control` 控件
- `textView` 文本框
- 会触发此函数的按键:
    - 上  :  `moveUp:`                          下 :  `moveDown:`
    - 左 :  `moveLeft:`                       右 :  `moveRight:`
    - Tab : `insertTab:`            回车键 :  `insertNewline:`
    - ESC : `cancelOperation:`     Del : `deleteBackward:`
- 返回 true (Del , Tab , 上下左右) 会在文本编辑框中的功能失效
- 返回 false (Del , Tab , 上下左右) 会在文本编辑框中的功能生效

# 重写代理方法的一般写法

- 类方法 需要  遵守代理协议 重写代理方法
- 对话框控件的 delegate 属性确定为对应的类
- 一般是本类

```swift
func controlTextDidChange (_ obj:Notification){
        if(obj.object as! NSTextField == self.控件名){
            
        }
}
```

# 限定只输入数字/字母

## 正则

## 重写controlTextDidChange并在其中添加判断逻辑

```swift
func controlTextDidChange (_ obj:Notification){
				//过滤当前控件
        guard let textField = obj.object as? NSTextField else { return }
        //获取控件中值
        var text = textField.stringValue
        //将值转化为 Int           
        let num = (text as NSString).intValue
        //判断转换前后长度
        if text.count != "\(num)".count {
						//不同 说明输入了字母 移除刚刚的字母
            text.removeLast()
						//赋为原来的值
            textField.stringValue = text
        }
        print("----> text: \(text), num: \(num)")
}
```

# 文本框作为第一响应时 使其光标在文字末尾

- 重写 becomeFirstResponder

# 自定义光标

- NSTextField 的 cell 继承自 NSTextFieldCell
- NSSearchField 的 cell 继承自 NSSearchFieldCell
- NSSecureTextField 的 cell 继承自 NSSecureTextFieldCell
- 重写