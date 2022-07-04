# 标签:Label

- 参考:[https://blog.csdn.net/lovechris00/article/details/77977541](https://blog.csdn.net/lovechris00/article/details/77977541)

# 是什么

- 文件标签 ,放置一段文本
- coca 中没有 NSLabel 本质是 TextField
- 无边框 无背景 不可编辑 不可选择

# 常用子类/类

- 本质上是 : NSTextField 类

# 常用属性

- 文字颜色: textColor = NSColor.yellow
    - 背景色设定也不会生效 : lbl.backgroundColor
- 不可编辑: isEditable  =  false
- 不可选中: isSelectable = false
- Label 的普通文本内容(获取/修改): stringValue
- Label 的富文本内容(获取/修改): attributedStringValue
- 单行多行显示
- 文字对齐方式:
    - alignment = NSTextAlignment.right (右对齐)
    - alignment = NSTextAlignment.right (左对齐)
    - alignment = NSTextAlignment.center (居中)
    - alignment = NSTextAlignment.justified (两端对齐) 文字量不够时左对齐
    - alignment = NSTextAlignment.natural ( 自然对齐) 根据选定的地区决定向左或向右
- 换行模式
    - lineBreakMode = byWordWrapping (默认 按照单词换行)
    - lineBreakMode = byCharWrapping (按字母换行)
    - lineBreakMode = byClipping (单纯截断)
    - lineBreakMode = byTruncatingHead (显示为"...wxyz")
    - lineBreakMode = byTruncatingTail (显示为"abcd...")
    - lineBreakMode = byTruncatingMiddle(显示为 "ab...yz")
- 换行策略:
    - lineBreakStrategy = NSParagraphStyle.LineBreakStrategy.hangulWordPriority 用于显示韩语字符
    - lineBreakStrategy = NSParagraphStyle.LineBreakStrategy.pushOut 保证换行时段落最后一行出现孤立词
    - lineBreakStrategy = NSParagraphStyle.LineBreakStrategy.standrd 优化较短字符串,不适于大量文本

# 重要方法:

- 创建 普通文本 label : NSTextField.init(labelWithString: String)
- 创建富文本 label : NSTextField(labelWithAttributedString: String)
- 创建可选择的 label: NSTextField(wrappingLabelWithString: String)

# 富文本的处理

[富文本 NSMutableAttributedString](../%E5%AF%8C%E6%96%87%E6%9C%AC%20NSMutableAttributedString%20cf36924c1526457894ff3989b6e79fe1.md)