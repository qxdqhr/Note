# TODO:集合视图控件 Collection View

- [https://blog.csdn.net/lovechris00/article/details/77984376](https://blog.csdn.net/lovechris00/article/details/77984376)

# 是什么

- 多行多列格子式显示内容

# 类

- 集合视图控件 :NSCollectionView
- 数据源协议 :NSCollectionViewDataSource
- 代理协议 :NSCollectionViewDelegate
- 滚动条类 :NSScrollView
- 布局视图类 :NSCollectionViewFlowLayout

# 怎么用

## 1. 定义CollectionView控件 及其 重要属性赋值

1. 设定 实现代理协议 的类: delegate  ,一般值为 self 
2. 设定 数据源协议 的类: dataSource  ,一般值为 self 
3. 设定 内部遵守的布局属性: collectionViewLayout 
4. 注册 item 控件: register(Item 子类名.self, forItemWithIdentifier: .identifier)
    
    ```swift
    //identfier
    extension NSUserInterfaceItemIdentifier{
        static let identifier = NSUserInterfaceItemIdentifier("com.itiger.collectionView.item.identifier")
    }
    
    ```
    

## 2. CollectionView所在类的协议实现

### 代理协议: 所在类遵守 NSCollectionViewDelegate 协议

1. 保证

### 数据源协议:所在类遵守 NSCollectionViewDataSource 协议

1. 遵守此协议则必须实现如下两个方法
    1. 返回 CollectionView 中item 的数量: `func collectionView(_ collectionView: NSCollectionView, numberOfItemsInSection section: Int) -> Int {}`
        1. data 是存储在 viewController 中的一个数组,表示数据源
        2. 返回的值如果在 b 中没有限制 就会创建对应数量的 item
        
        ```swift
        func collectionView(_ collectionView: NSCollectionView, numberOfItemsInSection section: Int) -> Int {
                return data.count 
            }
        ```
        
    2. 返回 创建的 item :`func collectionView(_ collectionView: NSCollectionView, itemForRepresentedObjectAt indexPath: IndexPath) -> NSCollectionViewItem {}`
        1. .identifier 是一个标识符 用于注册 item
        2. representedObject 用于给 item 中子控件 赋值 , 此处会从 data(数据源) 中获得要放在每一个 item 中的字典项,保存在representedObject中 ,并在 item 中解开 再对应控件中赋值
        3. indexPath.item 表示 每一个 item 的 下标 和 data 中的数据项相对应 他们两个如果不相同会报错
        4. data 是类中自定义的数据来源 数组类成员
        
        ```swift
        func collectionView(_ collectionView: NSCollectionView, itemForRepresentedObjectAt indexPath: IndexPath) -> NSCollectionViewItem {
                let item = collectionView.makeItem(withIdentifier: .identifier, for: indexPath)
                item.representedObject = self.data.object(at: indexPath.item)
                return item   
            }
        ```
        

## 3.实现CollectionView中item滚动条的成员属性

1. documentView 需要滚动的子视图 ,是 CollectionView 必须的父视图,一般赋值为 CollectionView 控件
2. hasHorizontalScroller 显示水平/竖直滚动条

## 4. 设定CollectionViewItem 类的 identifier

```swift
//identfier
extension NSUserInterfaceItemIdentifier{
    static let identifier = NSUserInterfaceItemIdentifier("com.itiger.collectionView.item.identifier")
}
```

## 5.定义CollectionViewItem

1. 创建类继承 NSCollectionViewItem
2. 创建 item 中应包含的子视图或控件
3. 重写 representedObject 属性 并获取到数据源中的数据
    
    ```swift
    override var representedObject: Any? {
            didSet{ //属性访问器
                let data = self.representedObject as? NSDictionary //解开 representedObject 可选转化 为 NSDictionary
                if let title = (data?["title"] as? String) { //获取到 NSDictionary 中 title 键的对应值
                    self.lblName.stringValue = title
                }
    						//其他子控件通上四行
            }
        }
    ```
    
4. 重写 loadView 并在其中创建 view
5. 重写 viewDidLoad
    1. 调用父类viewDidLoad
    2. item 子控件添加父视图
    3. item子控件 布局

## 6.CollectionView 内部的布局

### 流式布局TODO`NSCollectionViewFlowLayout`

- 提供了一个灵活的网格状的布局。对于绝大多数 app，这种布局方式都适用。
- 如图所示,对应属性确定长度即可
- Header
- Footer p207

![IMG_EB7C717DDE70-1.jpeg](TODO%20%E9%9B%86%E5%90%88%E8%A7%86%E5%9B%BE%E6%8E%A7%E4%BB%B6%20Collection%20View%20c786486830814bed95760dd995ca19ac/IMG_EB7C717DDE70-1.jpeg)

### 网格式布局 `NSCollectionViewGridLayout`

- 为了兼容 OS X 10.11 和以前的版本所保留的布局方式，对于新创建的 app 不推荐使用。
1. 只有一个分组(Section)
2. 四周边距 `margins`
3. item 中上下边距 `minimumInteritemSpacing`
4. item 中左右边距 `minimumLineSpacing`
5. 每行最多 item 数量 `maximumNumberOfRows`
6. 每列最多 item 数量 `maximumNumberOfColumns`
7. item 最小 Size `minimumItemSize`
8. item 最大 Size  `maximumItemSize`

## 7.点击事件 TODO:

## 注意

1. 数据来源一般是 NSArray<[String]:[String]> 键值对的数组