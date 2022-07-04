# 修改窗口的外观: 
## MFC中各类中有关窗口的创建的函数
### App类中
- 初始化实例函数(InitInstance())中
- 先进行注册窗口相关操作

        if(!ProcessShellCommand(cmdInfo)) return False;
- 通过主窗口指针(m_pMainWnd)调用:窗口显示(ShowWindow())和窗口更新(UpdateWindow())函数
### Frame类中
- 窗口预创建函数中(PreCreateWindow(CREATESTRUCT &cs)) 
  - 函数参数cs结构体中的成员变量决定了窗口的样式
- 窗口创建函数中(OnCreate(LPCREATESTRUCT lpCreateStruct))
  - 工具条和菜单栏是在窗口创建完成之后再放置在主窗口上的
### View类中
- OnDraw(CDC* pDC)视图绘制函数
  - 可以在视图中进行绘图操作
- 视图预创建函数中(PreCreateWindow(CREATESTRUCT &cs)) 
  - 函数参数cs结构体中的成员变量决定了视图的样式
### CDoc类中:
- OnNewDocument();新文档函数


## MFC中修改窗口外观的实际操作
### 修改窗口初始位置:
#### 修改位置:Frame类
- PreCreate预创建函数
- 修改cs结构体中成员
  - (内成员与Win32Api中CreateWindow函数参数像大致相同)

        LPVOID      lpCreateParams;//
        HINSTANCE   hInstance;//新窗口的实例句柄
        HMENU       hMenu;//新窗口的菜单句柄
        HWND        hwndParent;//父窗口的句柄
        int         cy;//窗口的高度
        int         cx;//窗口的宽度
        int         y;//窗口左上坐标点y,表示初始化位置
        int         x;//窗口左上坐标点x,表示初始化位置
        LONG        style;//窗口风格
        LPCWSTR     lpszName;//新窗口的名字
        LPCWSTR     lpszClass;
        DWORD       dwExStyle;
#### 修改过程:
- 调节窗口位置:(左上角)

        cs.x=0;
        cs.y=0;
- 调节窗口位置:(窗口居中)
  
        int CX =::GetSystemMetrics(SM_CXSCREEN);
        int CY =::GetSystemMetrics(SM_CYSCREEN);
        cs.x=(CX-cs.cx)/2;//(桌面宽度-窗口宽度)/2
        cs.y=(CY-cs.cy)/2;
- 调节窗口大小

        cs.cx=300;
        cs.cy=300;
### 修改窗口风格:
#### 窗口风格的有关参数:
- 查找"pFrame->LoadFrame"查找范围:C:\Program Files (x86)\Microsoft Visual Studio 11.0\VC\atlmfc
- 进入MFC框架内部发现如下参数:
- WS_OVERLAPPEDWINDOW
  - 表示窗口创建样式,此参数在Win32Api函数:CreateWindow中也使用
  - 转定义后发现是如下参数的定义:

            #define WS_OVERLAPPEDWINDOW(WS_OVERLAPPED     | \
                                        WS_CAPTION        | \
                                        WS_SYSMENU        | \
                                        WS_THICKFRAME     | \ //窗口不能拉伸
                                        WS_MINIMIZEBOX    | \ //最小化按钮
                                        WS_MAXIMIZEBOX)       //最大化按钮
  - WS_OVERLAPPEDWINDOW,根据定义,此参数由多个值位或得出,所以再进行添加或删除某一种窗口风格时,需要对这个宏进行位运算(添加值使用位或运算,删除值使用异或运算)
  - 每一个单独的样式中定义的宏都是根据位来区分的,所以能够使用位运算进行基本的区分
##### 位运算简述
  - 位或: |  两值中有1时,表达式为1
  - 位与: &  两值中均为1时,表达式为1
  - 异或: ^  两值相同为0,两值不同为1
  - 取反: ~  0变1,1变0
  - 左移: << 值转换二进制原码,后补0
  - 右移: >> 值转换二进制原码,前补1
#### 修改位置:(不能在MFC框架的源码中修改)
##### Frame类
- PreCreate预创建函数
- 修改cs结构体中成员
#### 修改过程:
- 更改窗口风格:(去除最小化与最大化按钮)

        cs.style = cs.style ^ WS_MINIMIZEBOX;
        cs.style = cs.style ^ WS_MAXIMIZEBOX;
  - 注意:仅去除一个按钮时,只会将去除的按钮变灰,并不会去掉,只有当两个按钮都被去除时,最大化和最小化按钮才会同时消失;
- 更改窗口风格:(使窗口无法被拉伸)

        cs.style = cs.style ^ WS_THICKFRAME;
- 更改窗口风格:(去掉窗口边框)

        cs.style =WS_POPUP;

### 更改窗口标题:
#### 修改位置:
##### Frame类
- PreCreate预创建函数
- 修改cs结构体中成员
#### 修改过程:
        cs.style = cs.style ^ FWS_ADDTOTITLE;//窗口标题不由活动视图决定
        cs.IpszName =_T("asdasd");//仅包含此语句不能修改成功
#### 注意:
##### FWS_ADDTOTITLE :
- 此参数决定窗口标题是否由当前活动视图决定;
- 当前活动视图指MDI框架，或当前活动的MDI子框架窗口;
- 可以通过去掉窗口风格(style)中的FWS_ADDTOTITLE样式来禁用。
##### 宽字符集:
- MFC项目中所有字符应使用宽字符(可修改),在一般字符串前加"_T("字符串")"即可表示一个字符串的宽字符形式;
- 也可以在项目属性中将Unicode字符集转换为多字节字符集
- _T转定义后实际上只是在一个字符串前拼接了一个'L'

### 更改窗口图标(标题左侧):
- 窗口背景,图标,光标,窗口刷新方式等由窗口设计图纸决定,调用时根据窗口设计图纸名确定;
#### Win32Api中更改方式
- 有关窗口背景,图标,光标,窗口刷新方式的设定如下(部分);
  - 窗口设计模块中:

            //修改窗口背景
            wndclass.hbrBackground = (HBRUSH)COLOR_WINDOW;
            //修改窗口光标
            wndclass.hCursor = LoadCursor(0,MAKEINTRESOURCE(IDC_ARROW));
            //修改窗口图标
            wndclass.hIcon = 0;
            //略过...
            //窗口图纸名,创建窗口函数中依照设计窗口图纸名建立窗口;
            wndclass.lpszClassName = "lele";
            //窗口刷新方式(水平刷新垂直刷新)
            wndclass.style = CS_HREDRAW|CS_VREDRAW;
#### MFC中
- MFC项目在创建时即有一份已经默认写好的设计窗口图纸;
- 空MFC项目所建立的窗口由默认窗口图纸创建;
- 用户也可以在创建窗口时使用自己完成的窗口图纸来创建窗口;
- **窗口背景,图标,光标,窗口刷新**方式几项根据设定的**窗口图纸名**设定在一个**窗口图纸中**
- MFC中将**生成一个窗口图纸的功能**直接封装成一个函数:**注册窗口类函数(AfxRegisterWndClass)**
#### 修改位置:
##### Frame类
- PreCreate预创建函数
- 更改窗口设计图纸:调用注册窗口类函数(AfxRegisterWndClass)
  - 参数:
    - 窗口刷新方式
    - 光标句柄(HCURSOR)
    - 背景句柄(HBRUSH)
    - 图标句柄(HICON)
  - 返回值:窗口设计图纸名lpszClassName;
#### 修改过程:
- 资源视图中添加对应自定义图片资源(窗口图标)
  - 具体过程:资源视图->添加资源->删除所有默认的图像类型->添加一个自定义的图像类型(32*32 24位 )
- 预创建函数中定义对应句柄加载资源:
  
        HICON hIcon =TheApp.LoadIcon(图标资源名);
- 更改窗口设计图纸:调用注册窗口类函数(AfxRegisterWndClass)
  
        cs.lpszClass=AfxRegisterWndClass(CS_HREDRAW|CS_VREDRAW,0,0,hIcon);
#### 注意:
- 修改窗口图标的位置是Frame类中的窗口预创建的函数;
- 修改窗口背景与光标的位置在View类中的窗口预创建的函数;
### 更改窗口光标与窗口背景(标题左侧):
#### 修改位置:
##### View类
- PreCreate预创建函数
#### 修改过程:
- 资源视图中添加对应自定义图片资源(窗口光标,窗口背景)
  - 具体过程:资源视图->添加资源->删除所有默认的图像类型->添加一个自定义的图像类型(32*32 24位 )
- 预创建函数中定义对应句柄加载资源:
  
        HCURSOR hCursor =TheApp.LoadCursor(光标资源名);
        //创建一个纯绿色的画刷
        HBRUSH hBrush =::CreateSoildBrush(RGB(0,255,0));
- 更改窗口设计图纸:调用注册窗口类函数(AfxRegisterWndClass)
  
        cs.lpszClass=AfxRegisterWndClass(CS_HREDRAW|CS_VREDRAW,hCursor,hBrush,0);

### 工具栏,状态栏,菜单栏
- 窗口工具栏与状态栏是在窗口创建之后放置于窗口之上的,修改应在窗口中创建函数中实现(OnCreate);
- 设置空菜单需要调用本类中的SetMenu函数
#### 修改位置:
##### Frame类
- OnCreate窗口创建函数
#### 修改过程:
- 删除掉工具栏创建相关代码:
  
        if (!m_wndToolBar.CreateEx(this, TBSTYLE_FLAT, WS_CHILD | WS_VISIBLE | CBRS_TOP | CBRS_GRIPPER | CBRS_TOOLTIPS | CBRS_FLYBY | CBRS_SIZE_DYNAMIC) ||
                !m_wndToolBar.LoadToolBar(IDR_MAINFRAME))
        {
                TRACE0("未能创建工具栏\n");
                return -1;      // 未能创建
        }
- 删除掉状态栏创建相关代码:

        if (!m_wndStatusBar.Create(this))
        {
                TRACE0("未能创建状态栏\n");
                return -1;      // 未能创建
        }
        m_wndStatusBar.SetIndicators(indicators, sizeof(indicators)/sizeof(UINT));
- 删除掉工具栏状态栏创建相关代码(不删除会报错)

        //TODO: 如果不需要可停靠工具栏，则删除这三行
        m_wndToolBar.EnableDocking(CBRS_ALIGN_ANY);
        EnableDocking(CBRS_ALIGN_ANY);
        DockControlBar(&m_wndToolBar);
- 设定空菜单
  
        this->SetMenu(0);

### 设定初始化全屏(非窗口形式)
#### 修改位置:
##### App类
- InitInstance程序创建函数中;
#### 修改过程:
- 在ShowWindow函数中参数SW_SHOW(窗口显示))转定义->找到SW_MAXIMIZE(最大化显示)
- 更改代码如下:

        // 唯一的一个窗口已初始化，因此显示它并对其进行更新
        m_pMainWnd->ShowWindow(SW_MAXIMIZE);
        m_pMainWnd->UpdateWindow();