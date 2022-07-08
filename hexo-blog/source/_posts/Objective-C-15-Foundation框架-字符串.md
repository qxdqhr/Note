 \1. 框架: 就是系统(苹果)或者第三方(其他的一些高手)事先写好了一些很牛X功能的类.

​     把这些类交给我们使用.这些类的集合我们叫做框架.

 

​     框架中有很多很多功能相似的类. 函数库

 

   Foundation框架: 是1个包 这里面有很多类、函数、定义了一些数据类型.

​           这个框架中的类都是一些最基础的类. NSString NSObject

​           其他的框架都是基于Foundation框架的.

 

   UIKit.

   AVFoundation.

   ......

 

 

 \2. Foundation框架中的最常用的类. 简单的爆.量大.



   

 

 \3. NSString

 

   1). NSString是1个数据类型.保存OC字符串的.

​     NSString的本质是1个类.既然是1个类.

 

​     所以,最标准的创建NSString对象的方式:

​     NSString *str1 = [NSString new];

​     NSString *str2 = [[NSString alloc] init];

​     NSString *str3 = [NSString string];

 

​     使用这种方式创建的字符串是1个空的字符. @""

 

​     NSString对象就是用来存储字符串.

 

 

   2). NSString是OC中最常用的1个类了.所以OC提供了一种更为快速的创建字符串对象的方式.

​     使用前缀@

 

​     @"jack"; 本质上这是1个NSString对象.这个NSString对象中存储的是"jack"这个字符串.

 



​    NSString *str1 = @"rose";

 

​    1). @"rose"本质上是1个NSString对象,这个对象中存储的是字符串"rose".

​    2). 将这个字符串对象的地址返回赋值给str1指针.

 

 

 

 

​     格式控制符%p: 打印指针变量的值.打印地址.

​         %@: 打印指针指向的对象.

 

 

 \4. NSString的恒定性.

 

   1). 当我们使用简要的创建字符串对象的时候.也就是使用1个OC字符串常量来初始化字符串指针的时候.

​     这个字符串对象是存储在 常量区(数据段) 的.

 

​     NSString *str = @"jack";

 

​     当我们调用NSString的类方法来创建对象的时候.

 

​     NSString *str = [NSString stringWithFormar:@"jack"];

​     NSString *str1 = [NSString new];

​     创建的字符串对象是存储在堆区.

 

 

   2). 当在内存中创建1个字符串对象以后.这个字符串对象的内容就无法更改.

​     当我们重新为字符串指针初始化值的时候.并不是修改原来的字符串对象 

​     而是重新的创建1个字符串对象 将这个字符串对象的地址重新复制给字符串指针变量.

 

 

   3). 当系统准备要在内存中创建字符串对象的时候.会先检查内存中是否有相同内容的字符串对象.

​     如果有,直接指向. 如果没有才会重新创建.

 

 

   4). 存储在常量区的数据不会被回收. 所以存储在常量区的字符串对象也不会被回收.

 

  \1. NSString是1个类.那么肯定其中有很多的方法.

 

 

 \2. 使用频率最最高的几个方法.

 

   1). 使用拼接的方式创建1个NSString对象.

 

​     \+ (instancetype)stringWithFormat:(NSString *)format, ... 

 

 

   2). 得到字符串的长度.

​     @property (readonly) NSUInteger length;

 

   3). 得到字符串中指定下标的字符.

​     \- (unichar)characterAtIndex:(NSUInteger)index;

 

​     返回值是unichar类型的 要打印的话使用%C

 

 

   4). 判断两个字符串的内容是否相同.

 

​     a. 能否使用 == 来判断两个OC字符串的内容是否相同.

 

​     b. == 运算符的作用: 比较左右两边的数据是否相同.

 

​      ->  10 == 10 这个时候直接比较的是左右两边的数据是否相同.

​      ->  a == b  两边也可以写1个变量.这个时候比较是左右两边的变量的值是否相同.

​      ->  如果两边是1个指针变量.那么比较的也是变量的值. 只不过指针变量的值是地址.

 

 

​     c. 所以,如果我们要比较两个OC字符串的内容是否相同.不能使用 == 去比较.

​      因为 == 比较的是字符串指针变量的值.而我们要比的是两个字符串指针指向的字符串对象的内容是否相同.

 

​     c. 调用方法: 

​      \- (BOOL)isEqualToString:(NSString *)aString;

​      就可以比较当前字符串对象和传入的字符串对象的内容是否相同.

 

 

   5). 将C语言的字符串转换为OC字符串对象.

 

​     \+ (instancetype)stringWithString:(NSString *)string;

 

 

   6). 将OC字符串对象转换为C语言的字符串.

 

​     @property (nullable, readonly) __strong const char *UTF8String

 \1. 将字符串写入到指定的文件中.

 

   \- (BOOL)writeToFile:(NSString *)path atomically:(BOOL)useAuxiliaryFile encoding:(NSStringEncoding)enc error:(NSError **)error;

 

 

 \2. 将文件中的内容读取到字符串中.

   \+ (nullable instancetype)stringWithContentsOfFile:(NSString *)path encoding:(NSStringEncoding)enc error:(NSError **)error;

 

   nullable 代表返回的对象有可能是nil

 

 \3. 使用NSURL读写资源.

   

   1). NSURL对象. 专门用来保存资源地址的. 资源地址: 本地磁盘路径、网页地址、ftp文件地址.

 

   2). 资源路径的地址的写法:

​     http://  开头的是网页路径的写法.

​     file://  开头的是本地磁盘的路径

​     ftp://  开头的是ftp文件资源的路径

​     如果要讲1个资源路径的地址保存到NSURL对象中 地址一定要是标准写法.

 

   3). 如何将资源地址存储到NSURL对象中.

​     NSURL *url1 = [NSURL URLWithString:@"http://www.itcast.cn"];

​     NSURL *url2 = [NSURL URLWithString:@"ftp://server.itcast.cn/ccc.txt"];

​     NSURL *url3 = [NSURL URLWithString:@"file:///Users/Apple/Desktop/abc.txt"];

 

   4). 字符串就提供了对应的方法去读写NSURL对象中封装的资源路径

 

 

​     从指定资源路径读取文本内容.

​     \+ (nullable instancetype)stringWithContentsOfURL:(NSURL *)url encoding:(NSStringEncoding)enc error:(NSError **)error;

 

​     将字符串的内容写入到资源路径中.

​     \- (BOOL)writeToURL:(NSURL *)url atomically:(BOOL)useAuxiliaryFile encoding:(NSStringEncoding)enc error:(NSError **)error;

 

​     如果要向网页或者ftp写内容要有权限.

 

 

 \4. 字符串比较.

   \- (NSComparisonResult)compare:(NSString *)string;

 

 

 \5. 字符串比较:忽略大小写的比较:

 

 

 \6. 字符串的相等判断.

 

 

​     

​     

 \7. 判断字符串是否以指定的字符串开头

   \- (BOOL)hasPrefix:(NSString *)str;

 

 \8. 判断字符串是否以指定的字符串结尾

   \- (BOOL)hasSuffix:(NSString *)str;

 

 

 \9. 在主串中搜索子串.从前往后

 

   \- (NSRange)rangeOfString:(NSString *)searchString;

 

   返回值是1个NSRange类型的结构体变量.

 

   typedef struct _NSRange {

​     NSUInteger location; 代表子串在主串出现的下标.

​     NSUInteger length; 代表子串在主串中匹配的长度.

   } NSRange;

 

   如果没有找到:

   location 为NSUInteger的最大值, 也就是NSNotFound

   length 的值为0

 

 

   这个方法,是从前往后搜索. 第1次匹配的子串.

 

 

 10.在主串中搜索子串.从后往前.

 

​    NSString *str = @"i love itcast love!";

 

​    NSRange range = [str rangeOfString:@"love" options:NSBackwardsSearch];

 

 

 

 \11. NSRange结构体.

 

   1). 是Foundation框架中定义的1个结构体.

 

​     typedef struct _NSRange {

​      NSUInteger location;

​      NSUInteger length;

​     } NSRange;

 

​     NSRange range;

 

​     这个结构体变量一般情况下用来表示1段范围.特别用在子串在主串中的范围表示.

 

​    @"hahajackhehe" @"jack" 

 

​     4 4

 

​    NSRange range = {4, 4};



 

 

  2). 声明并初始化结构体变量的方式.

 

​    1). 最原始的方式.

​       NSRange range;

​       range.location = 3;

​       range.length = 4;

 

​    2). 第二种方式:  NSRange range = {3, 7};

​    3). 第三种方式:  NSRange range = {.location = 3,.length = 7};

 

 

​    4). Foundation框架中定义了1个函数.这个函数可以快速的创建1个NSRange结构体会,

 

​      NSRange range = NSMakeRange(loc, len);

​      返回1个指定属性的NSRange结构体变量.

 

 

​    5). Foundation框架中定义了1个函数 可以将1个NSRange结构体变量转换为NSString

 

​       NSStringFromRange(ran) 函数可以将NSRange结构体变量转换为指定格式的字符串.

 

  \1. 字符串的截取.

   取到字符串中的1部分.

 

 

   \- (NSString *)substringFromIndex:(NSUInteger)from; 从指定的下标出一直截取到最后.

   \- (NSString *)substringToIndex:(NSUInteger)to; 从第0个开始截取指定的个数.

   \- (NSString *)substringWithRange:(NSRange)range; 截取指定的1段范围.

 

 

 \2. 字符串的替换

 

   \- (NSString *)stringByReplacingOccurrencesOfString:(NSString *)target withString:(NSString *)replacement

 

   将字符串中第1个参数替换为第2个参数.友情提示: 原来的指针指向字符串的内容是不会变的 会全部替换.

   新串是以方法的返回值返回的.

 

   这个方法还可以做删除. 原理: 将其替换为@""

 

 

 \3. 字符串数据转换为其他的类型. 使用频率很高.

 

   @property (readonly) double doubleValue;

   @property (readonly) float floatValue;

   @property (readonly) int intValue;

   @property (readonly) NSInteger integerValue

   @property (readonly) long long longLongValue

   @property (readonly) BOOL boolValue

 

 

   转换注意. 从头开始转换,能转换多少就是多少. 到遇到不能转换的时候就停止转换.

 

 

 \4. 去掉字符串前后的空格.

   str = [str stringByTrimmingCharactersInSet:[NSCharacterSet whitespaceCharacterSet]];

   中间的空格无法去掉.

 \1. 字符串的恒定性.

   一旦创建1个字符串对象,那么这个字符串对象的内容就无法更改, 当我们修改字符串的时候,其实是重新的创建了1个字符串对象.

 

   代码案例:

   NSLog(@"-------------------");

   NSString *str = @""; //@""

   for(int i = 0; i < 50000; i++)

   {

​    str = [NSString stringWithFormat:@"%@%d",str,i];

   }

   NSLog(@"-------------------");

   会耗费很长的时间. 每次循环的时候 都会创建1个新的字符串对象.50000个,

   因为字符串的恒定性.

 

 

 \2. 如何让这样的大批量的字符串拼接可以更加快速的1点.

 

  1). 慢得原因: 因为字符串的恒定性,每次修改字符串的时候,是重新的创建1个对象,

 

  2). 希望: 有没有一种对象是用来存储字符串的,并且存储在这个对象中的字符串数据可以更改.

 

 

 \3. NSMutableString

 

  1). 是Foundation框架中的1个类.从NSString继承.

​    所以,NSMutableString对象是用来存储字符串数据的.

 

   

  2). NSMutbaleString在父类NSString的基础之上的做扩展.

 

​    存储在NSSMutableString对象中的字符串数据可以更改.具备可变性.

​    直接可以改存储在NSMutableStirng对象中的字符串数据,不会新创建对象.

 

 

 \4. NSMutableString的用法

  

  1). 既然是1个类,要使用的话,就得创建1个对象.

 

 

​    NSMutableString *str = [NSMutableString string];

 

 

  2). 往可变字符串对象中追加字符串.

 

​     \- (void)appendString:(NSString *)aString; 直接追加内容.

​     \- (void)appendFormat:(NSString *)format, ... 以拼接的方式往可变字符串对象中追加内容.

 

 

  3). 创建NSMutableString对象的时候,记住下面这样的初始化方式是不行的.

​     

​    NSMutableString *str = @"jack";

 

​    @"jack" 是1个NSString对象,是1个父类对象.

​    而str指针是1个NSMutableString类型的 是1个子类类型的.    

​    如果通过子类指针去调用子类独有的成员 就会运行错误.

 

 

  4). NSMutableString从NSString继承.

​    在使用NSString的地方完全可以使用NSMutableString

 

 

 

 \5. 使用NSMutableString来做大批量的字符串拼接.

 

   NSLog(@"~~~~~~~~~~~~");

   NSMutableString *str = [NSMutableString string];

   for(int i = 0; i < 100000; i++)

   {

​    [str appendFormat:@"%d",i];

   }

   NSLog(@"~~~~~~~~~~~~");

 

  这个时候 "biu"的一下就结束了. 为什么这么快>? 因为NSMutableString只有1个.每次修改的时候 直接修改的是这个对象中的数据.

   

 

 \6. 使用建议

   

  1). 我们平时使用的时候,还是使用NSString. 因为效率高.

​    NSString *str1 = @"jack";

​    NSString *str2 = @"jack";

 

 

  2). NSMutbaleString: 只在做大批量的字符串拼接的时候才使用.

​    大量拼接的时候,就不要去使用NSString 因为效率低下.\

 

​    10次以上.

 



 \1. 回忆C语言中的数组

   特点:

   a. 存储多个数据.

   b. 类型相同.

   c. 长度固定.

   d. 每1个元素都是紧密相连的.

 

 \2. NSArray

   1). 是Foundation框架中的一个类.这个类的对象是来存储多个数据的,具备数组的功能.

​     所以,NSArray是OC中的数组.

 

   2). 特点:

​     a. 只能存储OC对象.任意的OC对象 无法存储

​     b. 长度固定. 一旦NSArray数组创建完毕之后,元素的长度固定,无法新增 无法删除元素.

​     c. 每1个元素都是紧密相连的. 每1个元素仍然有自己的下标.

​     d. 元素的类型是id类型的.

 

 

 \3. NSArray数组的创建.

 

   1). 因为这是1个类,所以当然就是创建NSArray对象.

 

​     NSArray *arr1 = [NSArray new];

​     NSArray *arr2 = [[NSArray alloc] init];

​     NSArray *arr3 = [NSArray array];

 

​     这样创建出来的NSArray数组的元素的个数是0个,因为长度固定.所以没有任何意义.

 

 

   2). 创建数组的同时指定1个数组的元素

 

​     \+ (instancetype)arrayWithObject:(ObjectType)anObject;



​     NSArray *arr = [NSArray arrayWithObject:@"jack"];

​     仍然没有意义,因为这个数组中只有1个元素.

 

 

   3). 最常用的创建NSArray数组的方式.

 

​     \+ (instancetype)arrayWithObjects:(ObjectType)firstObj, ...

 

​     NSArray *arr = [NSArray arrayWithObjects:@"jack",@"rose",@"lili",@"hanmeimei",nil];

 

​     使用注意

​     1). 只能存储OC对象.不能存储非OC对象.

​     2). 将元素写完以后,最后要写1个nil 表示元素到此结束了.

​     

 

   4). 创建NSArray数组的简要方式.

 

​     NSArray *arr = @[写上每1个元素的值用逗号分隔.];

​     NSArray *arr = @[@"jack",@"rose",@"lili"];

​     注意: 这种创建方式 不需要在最后加nil.

 

 

 

  \4. NSArray数组的使用.

 

   1). 在NSLog函数中使用%@可以直接输出NSArray对象中的所有的元素的值.

 

   2). NSArray数组中不能存储基本数据类型.不能存储非OC对象.

​     nil的本质其实就是0 所以nil无法存储到NSArray数组中.

 

   3). 这样创建数组没有任何意义.

​       NSArray *arr1 = [NSArray new];

​       NSArray *arr2 = [[NSArray alloc] init];

​       NSArray *arr3 = [NSArray array];

​     这些数组是没有元素的 而NSArray数组元素无法新增和删除,所以没有任何意义.

   

 \5. 取出存储在NSArray数组中的元素的值.

 

   1). 可以使用下标取出对应的元素的值.

 

​     NSArray *arr = @[@"jack",@"rose",@"lili"];

​     

​     NSLog(@"%@",arr[0]);

​     NSLog(@"%@",arr[1]);

​     NSLog(@"%@",arr[2]);

 

​     如果下标越界 就直接运行报错.

 

 

   2). 调用数组对象的对象方法来取出指定下标的元素的值.

 

​    \- (ObjectType)objectAtIndex:(NSUInteger)index;

 

   

​     NSArray *arr = @[@"jack",@"rose",@"lili"];

​     NSString *str = [arr objectAtIndex:3];

​     NSLog(@"%@",str);

​     

 

 

 \6. NSArray数组的其他的常用方法

 

   1). 得到NSArray数组中的元素的个数.

 

​     @property (readonly) NSUInteger count;

 

   2). 判断NSArray数组中是否包含指定的元素.

 

​     \- (BOOL)containsObject:(ObjectType)anObject;

 

 

   3). 取到NSArray数组中的第1个元素.

​     @property (nullable, nonatomic, readonly) ObjectType firstObject

 

​     与arr[0]的区别.

​     如果数组中没有任何元素.arr[0]报错. firstObject取到nil 不报错.

 

   4). 取到NSArray数组中的最后1个元素.

​     @property (nullable, nonatomic, readonly) ObjectType lastObject

 

   5). 查找指定的元素在NSArray数组中第一次出现的下标.

​     \- (NSUInteger)indexOfObject:(ObjectType)anObject;

 

​     如果没有找到 返回的是NSUInteger的最大值.

 

 

 \7. NSArray数组的遍历.

 

   1). 使用for循环来遍历数组中的每1个元素.

 

​     NSArray *arr = @[@"jack",@"rose",@"lili",@"jack",@"rose",@"lili"];

​     

​     for(int i = 0; i < arr.count; i++)

​     {

​       //NSLog(@"%@",arr[i]);

​       NSLog(@"%@",[arr objectAtIndex:i]);

​     }

 

​     原理: 将下标挨个挨个遍历出来 取值.

 

 

   2). 使用增强for循环来遍历NSArray数组中的元素.

​     

​     a. 语法格式:

​      for(元素类型 变量名 in 数组名)

​      {

​        直接通过变量名就可以拿到数组中的每1个元素.

​      }

 

​     b. 声明在for()中的变量叫做迭代变量.

 

​     c. 执行的原理.  

 

​      将数组中的第1个元素的值赋值给迭代变量.执行循环体.  

​      将数组中的第2个元素的值赋值给迭代变量.执行循环体. 

​      将数组中的第3个元素的值赋值给迭代变量.执行循环体.  

​      .......

​      将数组中的最后1个元素的值赋值给迭代变量.执行循环体.  

​      结束循环.

 

 

​     d. 语法总结:

​      -> 迭代变量的类型和数组中的元素的类型保持一致.

​      -> 迭代变量的名称可以任意取,根据自己的爱好.

​      -> in是固定的.

​      -> 遍历那1个数组,就降数组写在in后面.

​      -> 循环体里面.迭代变量的值就是元素的值.

 

 

​     当NSArray数组中存储的数据的类型不一致时候 迭代变量的类型建议使用id类型.

 

 

   3). 使用block遍历.

 

​     \- (void)enumerateObjectsUsingBlock:(void (^)(ObjectType obj, NSUInteger idx, BOOL *stop))block

 

​     这是1个方法.这个方法的作用就是来遍历数组中的每1个元素.

 

 

 

 

 \8. NSArray与字符串的两个方法

 

   1). 将数组中的元素连接起来组成1个新的字符串.

 

​     \- (NSString *)componentsJoinedByString:(NSString *)separator

 

​     参数: 连接符.

 

 

   2). 将字符串以指定的分隔符分成1个数组. 每1部分就是数组的1个元素.    

​     \- (NSArray<NSString *> *)componentsSeparatedByString:(NSString *)separator;

 

 

  \1. 非常重要的问题

​     

   %p : 打印的是指针变量的值.

   %@ : 打印的是指针变量指向的对象.

 

 

 \2. 使用NSLog函数 %@ 打印对象的原理.

 

   1). 调用传入的对象的description方法.

 

​     description是定义在NSObject协议中的1个方法.因为NSObject类遵守了NSObject协议.

​     所以,NSObject类中就有这个description方法的实现.

​     所以.所有的OC对象中都有description方法

 

​     这个方法的返回值是NSString字符串.

 

 

   2). 取到description方法的返回值,然后输出返回值的内容.

 

 

 

   \3) description方法是NSObject类中实现的.

 

​     在NSObject类中的description方法是如何实现的呢?

​     实现: 返回如下格式的字符串

​       @"<对象所属的类名:对象的地址>"

 

 

   4). 如果我们自定义的类不想打印NSObject中description方法的返回值.

​     而是我自己定义的额.

 

​     这个时候只需要子类重写父类的description方法



\1. NSMutableArray是NSArray的子类.

 

   1). NSMutableArray仍然是1个数组.具备NSArray数组的特点.

​     只能存储OC对象.每1个元素的紧密相连的.

 

   2). NSMutableArray相对于父类做的扩展:NSMutableArray数组的元素可以动态的新增和删掉.

​     其他的用法均与NSArray一致.

 

​     所以: NSArray数组一旦创建,其元素的个数就固定,无法新增删除.

​       NSMutableArray数组.元素可以新增 可以删除. 其他用法和父类一样.

 

 

 

 2.NSMutableArray数组的创建.

 

   NSMutableArray *arr1 = [NSMutableArray new];

   NSMutableArray *arr2 = [[NSMutableArray alloc] init];

   NSMutableArray *arr3 = [NSMutableArray array];

 

   这样创建出来的数组对象.数组的元素是0 仍然是有意义的 因为我们可以动态的新增和删除元素.

 

 

 

   也可以使用这样的方式来创建可变数组对象.这个数组的元素可以新增和删除.

   NSMutableArray *arr4 = [NSMutableArray arrayWithObjects:@"jack",@"rose",@"lili", nil];

 

 

   最容易犯错:这样写是不可以的

   NSMutableArray *arr5 = @[@"jack",@"rose",@"lili"];

 

   @[@"jack",@"rose",@"lili"];这是1个NSArray对象.

   arr5是1个子类指针. 子类指针指向父类对象的就有可能会出问题.



 

 ---------插入---------

 

 \1. 任意的指针其实可以指向任意的对象. 编译不会报错 只会给1个警告.

 

 \2. 虽然语法上可以乱指.但是你千万别乱指.因为运行的适合可能出错.

 

  当我们调用指针类型特有的方法的时候.

 

 \-------------------------

 

 

 \3. 如何往可变数组中新增元素.

 

   \- (void)addObject:(ObjectType)anObject; 将传入的参数作为数组的元素添加进去.

 

 

 \4. 将另外1个数组中的每1个元素添加到可变数组中.

 

   \- (void)addObjectsFromArray:(NSArray<ObjectType> *)otherArray;

 

 

 \5. 在可变数组中指定的下标出插入1个元素.

 

  \- (void)insertObject:(ObjectType)anObject atIndex:(NSUInteger)index;

 

 

 \--------------

 

 \6. 删除可变数组中指定下标的元素.

 

  \- (void)removeObjectAtIndex:(NSUInteger)index;

 

 \7. 删除可变数组中所有的指定的元素.

 

  \- (void)removeObject:(ObjectType)anObject;

 

 \8. 删除指定范围中的所有指定元素.

 

  \- (void)removeObject:(ObjectType)anObject inRange:(NSRange)range;

 

 \9. 删除最后1个元素

   

  \- (void)removeLastObject;

 

 10.删除所有的元素.

 

  \- (void)removeAllObjects;

 

 \1. 无论是NSArray还是NSMutbaleArray里面都只能存储OC对象.

   基本数据类型是无法存储的.

 

 

 \2. 如何将基本数据类型的数据存储到NSArray数组中.

 

 

 \3. 自定义包装类来包装基本数据类型.

 

   定义1个类,这个类的对象的作用是用来存储1个int类型的数据.再将这个对象存储到NSArray数组中.

 

 

 

 

 \4. NSNumber是Foundation框架中定义好的1个类.这个类的对象的作用就是用来包装基本数据类型的.

   

   将基本数据类型存储到NSArray数组中的步骤.

 

   1). 先讲基本数据类型包装到NSNumber对象中.

   2). 再降NSNumber对象存储到NSArray数组中.

 

 

   NSNumber *number1 = [NSNumber numberWithFloat:10.1f];

   NSNumber *number2 = [NSNumber numberWithFloat:10.2f];

   NSNumber *number3 = [NSNumber numberWithFloat:10.3f];

   

   NSArray *arr = @[number1,number2,number3];

   for(NSNumber *num in arr)

   {

​      NSLog(@"%f",num.floatValue);

   }

 

 

 \5. 简写方式.

 

   创建NSNumber对象的简写方式:

 

 

   @10; 代表是1个NSNumber对象.这个对象中包装的是整形的10

​      这个不是整形的10

   [NSNumber numberWithInt:10];

 

 

   包装注意:

 

   如果后面的数据是1个变量 那么这个变量就必须要使用小括弧括起来.

 

   @(10);

 

   int num = 10;

   @(num)



\1. NSArray与NSMutableArray 是OC中的数组.

   存储数据的特点: 每1个元素紧密相连.并且每1个元素中都是直接存储的值.

   缺点: 数组元素的下标不固定.都有可能会发生变化.无法通过下标来唯一确定数组中的元素.

 

   希望: 有一种存储数据的方式 存储到数组中.可以快速唯一的确定数组的元素.

 

   存储数据的时候.必须要为存储的数据取1个别名.

   这个别名的作用: 就是用来确定别名对应的数据的.

   要找存储在数组中的数据. 使用别名来找 而不是通过下标来找 因为下标有可能会发生变化.

 

   这种存储数据的方式 就叫做 键值对 的存储方式

 

   Key-Value

   Key 就是键 就是为数据取得别名.

   Value 就是值 就是真正存储的数据.

 

 

 \2. NSDictionary 与 NSMutableDictionary

 

   1). 它们是数组. 它们就是以键值对的形式存储数据的.

​     往这个数组中存储数据的同时.必须要指定这个数据的别名才可以.

​     要找到存储在这个数组中的数据 通过别名来找 而不是通过下标.

 

 

   

 \3. NSDictionary 字典数组

 

   1). 存储数据的原理.

​     a. 以键值对的形式存储数据.

​     b. 字典数组一旦创建,其中的元素就无法动态的新增和删除.

​     c. 键: 只能是遵守了NSCoping协议的对象. 而NSString就是遵守了这个协议.

​      值: 只能是OC对象.

 

   2). 创建字典数组

 

​     NSDictionary *dict1 = [NSDictionary new];

​     NSDictionary *dict2 = [[NSDictionary alloc] init];

​     NSDictionary *dict3 = [NSDictionary dictionary];

 

​     这种方式创建出来的字典数组中没有任何元素.所以没有意义.

 

   3). 一般创建方式

 

​     \+ (instancetype)dictionaryWithObjectsAndKeys:(id)firstObject, ...

 

​     将字典数组的值键 挨个的写在后面初始化.

 

​     NSDictionary *dict = [NSDictionary dictionaryWithObjectsAndKeys:@"jack",@"name",@"北京市XX街道",@"address", nil];

 

 

   4). 简要创建方式.

​       

​     NSDictionary *dict = @{键1:值1,键2:值2,键3:值3,........};

​      

​     NSDictionary *dict = @{@"name":@"rose",@"age":@"18",@"addredd":@"BeiJingXXSttreet"};

 

 

 

 \4. 使用字典数组.

 

   1). 如何取出存储在字典数组中的数据.

​     a. 存储在字典数组中的元素不能使用下标去取 而是用键 也就是别名去取.

 

​     -> 使用中括弧的方式.

​      字典数组名[键]; 这样就可以去到字典数组中这个键对应的值.

 

​      NSLog(@"%@",dict[@"name"]); 取出dict字典数组中@"name"这个键对应的值.

 

 

​     -> 调用字典数组对象的方法也可以取出键对应的值.

 

​      \- (nullable ObjectType)objectForKey:(KeyType)aKey;

 

​    如果给定的key在数组中不存在,取到的值是nil 不会报错.

 

 

   2). 取到字典数组的键值对的个数.

 

​     @property (readonly) NSUInteger count;

 

 

   3). 往字典数组中存储键值对的时候 键不允许重复.



​     如果键重复: 后加的无效.. ???????????????

​       



 

 \5. 遍历字典数组

 

 

   1). 字典数组中的数据无法使用下标去取 所以普通的for循环遍历下标发就无用武之地了.

 

   2). 使用for in循环. 遍历出来的是字典数组中所有的键. 再通过键取出对应的值.

 

​     NSDictionary *dict = @{

​         @"name":@"rose",

​         @"age":@"18",

​         @"address":@"BeiJingXXSttreet"

​     };

​     

​     

​     for(id item in dict)

​     {

​        NSLog(@"%@ = %@",item,dict[item]);

​     }

 

  3). 使用block遍历.

​     

 

​     [dict enumerateKeysAndObjectsUsingBlock:^(id _Nonnull key, id _Nonnull obj, BOOL * _Nonnull stop) {

​     

​        NSLog(@"%@ = %@",key,obj);

​     

​     }];

 

 

 

 \6. 字典数组存储数据的原理.

 

   1). 当往字典数组中存储1个键值对的时候,这个键值对应该存储在下标为几的元素中呢?

​     -> 并不是按照顺序挨个挨个的存储的.

 

​     -> 存储键值对的时候,会根据键和数组的长度做1个哈希算法.算出1个下标.将这个键值对存储在该下标处.

 

 

   2). 取值的时候:

​     也是根据键做1个哈希算法.就可以算出这个键值对存储的下标 然后直接找到这个下标的数据取出就可以了.

 

 

 

   与NSArray对比

 

   1). NSArray数组的元素 挨个挨个的屁股后面. 按照顺序来存储的.

​     字典数组中不是挨个挨个的存储的.存储的下标是算出来的.

 

 

   2). 存的效率: 肯定是NSArray要高一些.

​     取得时候: 如果取值的时候,是全部一股脑的取出来.这个时候NSArray块一些.

​         如果取值的时候.只会取数组中指定的几个元素.字典数组取值更快一些.

​     

 

 

  什么时候是有NSArray 什么时候使用字典数组?

 

  存储进去之后,一旦要取值.就是全部取出. NSArray

  存储进去之后.取值只会取指定的几个元素 字典数组.

 

 \---------------------------------------------------

 

 

 \1. NSMutableDictionary

 

  1). 是NSDictionary的子类.所以NSMutableDictionary也是1个字典数组,也是以键值对的形式存储数据的.

 

  2). 重点:NSMutableDictionary在父类基础之上做的扩张:

 

​    存储在其中的元素可以动态的新增和删除.

 

  3). 创建可变字典数组.

​     NSMutableDictionary *dict1 = [NSMutableDictionary new];

​     NSMutableDictionary *dict2 = [[NSMutableDictionary alloc] init];

​     NSMutableDictionary *dict3 = [NSMutableDictionary dictionary];

​     

​     这样创建出来的可变字典数组的长度为0 但是有意义 因为可以动态的新增和删除.

 

 

​     NSMutableDictionary *dict = [NSMutableDictionary dictionaryWithObjectsAndKeys:@"jack",@"name",@"18",@"age", nil];

​     在创建可变字典数组的同时初始化键值对.

 

​     注意: NSMutableDictionary *dict = @{}; 这样是不行的.

 

 

 \2. 如何新增键值对.

 

  \- (void)setObject:(ObjectType)anObject forKey:(KeyType <NSCopying>)aKey;

 

  如果键重复.后添加的就会替换原有的.

 

 \3. 如何删除.

 

  \- (void)removeAllObjects; 删除所有的键值对.

 

  \- (void)removeObjectForKey:(KeyType)aKey; 删除指定的键值对.

 

 

 \4. 也可以将字典数组的信息持久化起来.

 

  将字典数组的信息保存到plist文件中.

  \- (BOOL)writeToFile:(NSString *)path atomically:(BOOL)useAuxiliaryFile;



  从plist文件中还原回字典.

  \+ (nullable NSDictionary<KeyType, ObjectType> *)dictionaryWithContentsOfFile:(NSString *)path;

  \1. 集合

   NSArray集合、NSDictionary字典集合 就叫做集合.

 

 

 \2. 在MRC的模式下 将1个对象存储到集合中,会不会影响对象的引用计数器.

 

   将对象存储到集合之中,会为这个对象的引用计数器+1

   当集合销毁的时候 就会像存储在集合中的所有的对象发送1条release消息.

 

   

 \3. 使用@[]或者@{}创建的集合已经是被autorelease过的了.   

   直接调用和类同名的类方法创建的对象 也是被autorelease过的了.

 



 \4. 在ARC的模式下.集合的元素是1个强类型的指针.

 

 \1. NSFileManger是Foundation框架提供的1个类.  

   这个类作用: 用来操作磁盘上的文件 文件夹 对他们进行创建、删除、复制 拷贝 移动.....

 

 \2. NSFileManager是1个类.

   这个类的对象是以单例模式创建的.

   如何得到NSFileManager的1个单例对象.

   掉用这个类的类方法,defaultManager 就可以得到这个类的单例对象

   NSFileManager *fileManager = [NSFileManager defaultManager];

 

 \3. 常用方法之 判断.

   1). 判断指定的文件或者文件夹在磁盘上是否真实的存在

​    \- (BOOL)fileExistsAtPath:(NSString *)path;

 

   2).判断指定的路径是否真实的存储在我们的磁盘之上,并且判断这个路径是1个文件夹路径还是1个文件路径.

​    \- (BOOL)fileExistsAtPath:(NSString *)path isDirectory:(BOOL *)isDirectory;

​    返回值:代表这个路径是否真实存在.

​    参数指针: 代表这个路径是否是1个文件夹路径

   

   3). 判断指定的文件夹或者文件是否可以读取.

​     \- (BOOL)isReadableFileAtPath:(NSString *)path;

 

   4). 判断指定的文件夹或者文件是否可以写入.

​     \- (BOOL)isWritableFileAtPath:(NSString *)path;

 

   5). 判断指定的文件夹或者文件是否可以删除.

​     \- (BOOL)isDeletableFileAtPath:(NSString *)path

 

 \4. 常见方法之 获取信息.

  1).获取指定文件或者文件夹的属性信息.

​    \- (NSDictionary *)attributesOfItemAtPath:(NSString *)path error:(NSError **)error

​    返回的是1个字典,如果要拿到特定的信息 通过key

 

  2).获取指定目录下的所有的文件和目录. 是拿到指定目录下的所有的文件和目录 所有的后代目录和文件.

​    子目录的子目录的子目录 所有的都可以拿到.

​    \- (NSArray *)subpathsAtPath:(NSString *)path;

 

  3).获取指定目录下的所有的子目录和文件 不保护孙子辈.

​    \- (NSArray *)contentsOfDirectoryAtPath:(NSString *)path error:(NSError **)error

 

 \5. 常见方法之 文件/目录的创建

   

  1). 在指定的目录创建文件.

​    \- (BOOL)createFileAtPath:(NSString *)path contents:(NSData *)data attributes:(NSDictionary *)attr

​    第1个参数: 要创建的文件的路径.

​    第2个参数: 这个文件的内容. 要传递这个文件的二进制格式. 

​         这个二进制的数据格式 使用NSData对象来封装.

 

​         NSData: 将别的格式的数据转换为二进制数据.

   

​         将字符串转换为NSData二进制的方式.调用字符串对象的

​          \- (NSData *)dataUsingEncoding:(NSStringEncoding)encoding

​          编码参数: NSUTF8StringEncoding

​         指定1个编码 就可以将字符串转换为二进制数据 存储在NSData对象之中.

 

​         最后再将这个二进制对象通过这个方法写入.

 

​         如果想创建1个空文件 第2个参数就给nil

 

​    第3个参数: 指定创建的文件的属性.如果想要使用系统的默认值使用nil

 

  2). 在指定的目录创建文件夹.

​    \- (BOOL)createDirectoryAtPath:(NSString *)path withIntermediateDirectories:(BOOL)createIntermediates attributes:(NSDictionary *)attributes error:(NSError **)error

 

​    第1个参数: 路径.

​    第2个参数: YES,做一路创建. 如果是NO就不会做一路创建.

​    第3个参数: 指定属性 nil为系统默认属性.

​    第4个参数.

 

  3).拷贝文件.

​    \- (BOOL)copyItemAtPath:(NSString *)srcPath toPath:(NSString *)dstPath error:(NSError **)error

   

  4).移动文件 剪切 文件的重命名. 重名的原理: 将文件移动到原来的目录并改名.

​    \- (BOOL)moveItemAtPath:(NSString *)srcPath toPath:(NSString *)dstPath error:(NSError **)error

 

  5).删除文件.

​    \- (BOOL)removeItemAtPath:(NSString *)path error:(NSError **)error

 

   注意 删除的文件不会倒废纸篓 而是直接删除,所以请小心使用.

 

 \1. 定义1个变量来保存按钮在iOS界面上得位置.

   

   我们定义1个结构体来表示控件在界面上得坐标.

 

   typedef struct

   {

​    int x;

​    int y;

   }CZPoint;

 

 

   CZPoint p1 = {20,30};

 

 

   在Foundation框架中,已经定义了1个结构体CGPoint.

 

   struct CGPoint {

​    CGFloat x;

​    CGFloat y;

   };

   typedef struct CGPoint CGPoint;

 

   CGFloat类型的实际上就是1个double类型的.

 

 

   这个结构体一般情况下是用来表示坐标的. 用来表示控件在界面上得位置.

   CGPoint与NSPoint都是同1个结构体,只不过定义两个名字.

   typedef CGPoint NSPoint;

 

 

   ---------声明CGPoint变量并初始化的方式-------

   1). CGPoint p1;

​     p1.x = 20;

​     p1.y = 30;

 

 

   2). CGPoint p1 = {20,30};

   

   3). CGPoint p1 = {.x = 20, .y = 30};

 

 

   4). Foundation框架中提供的函数来快速的创建1个CGPoint变量.

​     

​     a. CGPointMake(x,y);

​      CGPoint p1 = CGPointMake(20, 30);

 

​     b. NSMakePoint(x,y);

​      NSPoint p2 = NSMakePoint(20, 30);

 

 

 

  \2. 声明1个变量来保存某个控件的大小.

 

   1个控件的大小,无非就是两个数据. 宽度、高度.

 

   typedef struct

   {

​     double width;

​     double height;

   }CZSize;

 

   

   CZSize size = {50,20};

 

 

   Foundation框架中已经定义好了1个结构体叫做CGSize;

   struct CGSize {

​    CGFloat width;

​    CGFloat height;

   };

   typedef struct CGSize CGSize;

 

   typedef CGSize NSSize;

   NSSize和CGSize是同1个结构体,只不过定义了两个名称.

 

   CGSize结构体一般情况下用来表示控件的大小.

 

 

   ------CGSize声明并初始化的方式----------

   1). CGSize size;

​     size.width = 100;

​     size.height = 30;

 

   2). CGSize size = {100,30};

 

   3). CGSize size = {.width = 100, .height = 30};

 

 

   4). Foundation框架中提供了函数用来快速的得到1个CGSize结构体变量.

​     

​     a. CGSizeMake(width,height);

 

​       CGSize size0 = CGSizeMake(100, 30);

 

​     b. NSMakeSize(w,h);

​       CGSize size1 = NSMakeSize(100, 30);

 

 

   

 

 \3. CGRect和NSRect

 

   这是定义在Foundation框架中的1个结构体.

​     struct CGRect {

​       CGPoint origin;

​       CGSize size;

​     };

​     typedef struct CGRect CGRect;

 

   所以,这个结构体变量一般情况下存储1个控件的位置和大小.

 

   typedef CGRect NSRect;

 

   NSRect和CGRect是一样的.

 

   ----CGRect的声明和初始化-----

 

   1).

​     CGRect rect;

​     rect.origin.x = 20;

​     rect.origin.y = 40;

​     rect.size.width = 100;

​     rect.size.height = 30;

 

​     当结构体作为另外1个结构体或者对象的1个属性的时候,不能直接{}赋值.

 

​     CGRect rect;

​     rect.origin = (CGPoint){10,20};

​     rect.size = (CGSize){100,30};

​     

 

 

   2). 也提供了函数来快速的创建CGRect变量.

 

​     CGRect rect = CGRectMake(10, 20, 100, 30);

​     CGRect rect1 = NSMakeRect(10, 20, 100, 30);

​     

 

   

 

 使用的时候. CGSize NSSize 建议使用CG...

  \1. 我们之前学习的结构体.

   NSRange

   CGPoint

   CGSize

   CGRect

   这些都是结构体,它们的变量是无法存储到集合之中.

 

  \2. 解决方案:

   

   先将这写结构体变量存储到OC对象中,再将OC对象存储到集合之中.

 

 

  \3. NSValue 类 的对象就是用来包装结构体变量的.

 

\1. NSDate 时间处理.

 

  1). 可以得到当前时间. 创建1个NSDate对象就可以了,将这个对象输出,就是当前时间

​    得到的是当前系统的格林威治时间. 0时区的时间. 东8区.

 

​    NSDate *date = [NSDate date];

​    NSLog(@"%@",date);

 

  2). 格式化输出日期. 指定日期输出的格式

​    默认的格式 年-月-日 时:分:秒 +时区.

​     NSDate *date = [NSDate date];

​     NSLog(@"%@",date);

 

​     //1.先要创建1个NSDateFormatter对象,这个对象作用:将1个日期转换成1个指定的格式.

​     NSDateFormatter *formatter = [[NSDateFormatter alloc] init];

​     //2.告诉这个日期格式化器对象 要把日期转换个什么样子的.

 

​     yyyy: 年份

​     MM: 月份.

​     mm: 分钟.

​     dd: 天.

​     hh: 12小时.

​     HH: 24小时

​     ss: 秒

 

​     formatter.dateFormat = @"yyyy年MM月dd日 HH点mm分ss秒";



​     //3.使用日期格式化器 将指定的日期转换指定格式的字符串.

​     NSString *str =[formatter stringFromDate:date];

​     NSLog(@"str = %@",str);



 

 \- (NSString *)stringFromDate:(NSDate *)date; //将日期类型换换为字符串

 \- (NSDate *)dateFromString:(NSString *)string;//将字符串转换为日期对象.

 

  注意: NSDate取到的时间是格林威治的时间.

​     NSDateFormatter转换成字符串以后 会转换为当前系统的时区的时间.

 

 \2. 计算时间.

   

  1). 想得到明天此时此刻的时间.

​    当前时间的基础之上 + 1天的时间.

 

​    在当前时间的基础之上,新增指定的时间.得到的1个新的时间.

 

​    \+ (instancetype)dateWithTimeIntervalSinceNow:(NSTimeInterval)secs;

​    在当前的时间的基础之上,新增指定的秒.后的时间

​    得到东八区的时间:

​    NSDate *d1 =[NSDate dateWithTimeIntervalSinceNow:8*60*60];

 

   

​    传入1个负数 就是在当前时间的基础之上减指定的秒数.

 

 

  2). 求两个时间之间的差.

​    可以实现的效果.就是可以计算出执行代码所花费的时间.

 

​    \- (NSTimeInterval)timeIntervalSinceDate:(NSDate *)anotherDate;

 

 

 \3. 得到NSDate中的年月日时分秒.

   

  1). 得到时间的各个部分。可以使用日期格式化器来得到.

  2). 比较复杂.

 

   NSDate *date = [NSDate date];

   

   //1.创建1个日历对象. 调用类方法currentCalendar得到1个日历对象.

   NSCalendar *calendar = [NSCalendar currentCalendar];

   //2.指定日历对象取到日期的对象的那些部分. 是要取那1个时间对象的部分.

   // 返回1个日期组件对象.这个对象中就有指定日期的指定部分.

   NSDateComponents *com = [calendar components:NSCalendarUnitYear|NSCalendarUnitMonth|NSCalendarUnitDay fromDate:date];

   

   NSLog(@"%ld-%ld-%ld",com.year,com.month,com.day);

 

 */



   

//  NSDate *date = [NSDate date];

//  //1. 先创建1个日历对象.日历对象的作用可以从日期对象中取到日期的各个部分.

//  NSCalendar *calendar = [NSCalendar currentCalendar];

//  //2. 让日历对象从日期对象中取出日期的各个部分.

//  NSDateComponents *com = [calendar components: NSCalendarUnitYear|NSCalendarUnitMonth|NSCalendarUnitDay|NSCalendarUnitWeekday|NSCalendarUnitHour fromDate:date];

//   

//   

//  NSLog(@"%lu---%lu----%lu---%lu",com.year,com.month,com.day,com.weekday);

 

 \1. 无论在MRC还是ARC下,如果属性的类型是NSString类型的. @property参数使用copy.

 

 

 \2. copy 复制

 

   1). copy是1个方法.定义在NSObject类之中. 作用:拷贝对象.

 

​     NSString ----> copy ---> 不可变字符串 没有产生新对象,而是直接将对象本身的地址返回. 这种拷贝我们叫做浅拷贝

​     NSMutableString --> copy --> 是1个不可变的字符串对象 . 有产生1个新对象.这样的拷贝我们叫做深拷贝.

 

 

   2). mutableCopy.定义在NSObject类之中. 作用:拷贝对象.

 

​     NSString ---> mutableCopy --> 可变字符串对象. 深拷贝.

​     NSMutableString --> mutableCopy --> 可变字符串对象 深拷贝.

 

 

   这是字符串的对象拷贝特点.

 

 \3. 字符串对象拷贝的引用计数器的问题.

 

   1). 若字符串对象存储在常量区中. 存储在常量区的数据是不允许被回收的.

​     所以存储在常量区的字符串对象的引用计数器是1个超大的数.并且retain和release无效.

 

   2). 若字符串存储在堆区. 这个字符串对象和普通的对象一样的.引用计数器默认是1.

 

   3). 字符串对象如果是浅拷贝. 会将对象的引用计数器+1

 

​     字符串对象如果是深拷贝. 原来的对象的引用计数器不变.新拷贝出来的对象的引用计数器为1.

 

 

 \4. 

 

  //需求:将str赋值给p1.name属性以后.

  //再修改str的值 不要影响p1.name

  //解决: 在setter方法赋值的时候.将传进来的对象先拷贝1份.

  //NSMutableString *str = [NSMutableString stringWithFormat:@"jack"];



\1. copy方法的确是定义在NSObject类中的1个方法.

   copy方法的内部调用了另外1个方法. copyWithZone:

 

   

   这个方法是定义在NSCoping协议之中的.

 

 

  因为我们的类没有遵守NSCoping协议,那么我们的类中就没有 copyWithZone:这个方法.  

  所以,当我们自定义的类调用copy方法的时候就会出错/

 

 

 

 \2. 如果我们想要让我们自己的类具备对象拷贝的能力.那么就让我们的类遵守NSCoping协议

  并实现copyWithZone:这个方法. 

 

  如果想要实现深拷贝:那么就重新创建1个对象.并将对象的属性的值复制.返回.

  如果想要实现浅拷贝:那么就直接返回self





 \1. 单例模式:

 

   1个类的对象,无论在何时创建也无论在什么地方创建 也无论创建多少次.创建出来的都是同1个对象.

 

 

 \2. 无论如何创建对象,最终都会调用alloc方法来创建对象.

   

   1). alloc方法的内部. 其实什么都没有做,只是调用了allocWithZone:方法.

 

   2). 实际上真正申请空间 创建对象的事情是allocWithZone:方法在做.

 

 

 \3. 要实现单例模式.

 

   重写+ allocWithZone:

 

   \+ (instancetype)allocWithZone:(struct _NSZone *)zone

   {

​     static id instance = nil;

​     if(instance == nil)

​     {

​      instance = [super allocWithZone:zone];

​     }

​     return instance;

   }

 

 

 \4. 单例模式的规范:

   如果类是1个单例模式.要求为类提供1个类方法.来返回这个单例对象.

 

 

   类方法的名称必须以 shared类名; default类名;

 

 

 

 \5. 什么时候要把类搞成单例.

   1). 单例的特点

​     无论何时、何地、创建对象,也不管创建多少次对象,得到都是同1个对象.

​     单例对象可以被共享. 存储在单例对象中的数据可以被共享.

​     也就是无论在什么地方创建单例对象 访问的都是同1个对象.

 

 

   2).

 

 

 

   做游戏:

   游戏面板的宽度: 800

   游戏面板的高度: 600

 

   这两个数据基本上在很多的地方都会使用到.

 

   \1. 直接写. 滚蛋.

   \2. 宏. 程序运行的时候无法更改.

   \3. 还是要定义为变量.

 

   定义为属性保存在对象中. 如果不是单例对象.

 

 

 

   如果数据需要被整个程序所共享. 将数据以属性的方式存储在单例对象中.

 

 

 

 