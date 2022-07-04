# 标题视图区/分割线 Box

# 是什么

- 标题视图区
- 分割线
- 阴影区域,可放置控件

# 类

- NSBox
- 继承 NSView

# 怎么用

- 设置标题 title
- 设置标题位置 titlePosition
- 设置内部子控件
    - 代码:
    
    ```swift
    private lazy var boxTest: NSBox = {
            var ctrl = NSBox()
            ctrl.title = "标题"
            ctrl.titlePosition = .atBottom
            ctrl.contentView?.addSubview(boxlabelTest)
            boxlabelTest.snp.makeConstraints{
    						//此控件的父视图 就是 Box
    						//boxlabelTest 是一个 label
                $0.center.equalToSuperview()
            }
            return ctrl
    ```