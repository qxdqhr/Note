# 图像显示控件: Image View

# 是什么

- 用于图像显示的控件

# 所属类

- NSImageView
- 继承于 NSControl, NSAccessibilityImage, NSMenuItemValidation 类

# 怎么用

## 基本属性

- 显示的图片: image:
    - NSImage?
- 是否可拖入新图片: isEditable:
    - Bool
- 图片的排列方式: imageAlignment:
    - NSImageAlignment
- 图片的缩放比例: imageScaling:
    - NSImageScaling
- 图片的边框风格: imageFrameStyle:
    - NSImageView.FrameStyle
- layer 属性(NSView 继承来的,需要保证wantsLayer 为 true)
    - 边框宽度 layer?.borderWidth
    - 边框颜色 layer?.borderColor
    - 设置ImageView圆角 layer?.cornerRadius
    - 设置 裁剪边界 layer?.masksToBounds
    - 阴影颜色 layer?.shadowColor
    - 设定阴影的偏移量(显示效果?) layer?.shadowOffset
    - 设定阴影透明度 layer?.shadowOpacity
    - 设定阴影半径 layer?.shadowRadius