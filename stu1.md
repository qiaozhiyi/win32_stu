# 针对 `stu1.cpp` 的学习笔记

## 关键步骤总结

Windows窗口创建的四个核心步骤：

1. **注册窗口类**  
   - 使用 `RegisterClassEx()` 函数  
   - 注意：注册前需先填充窗口结构体（后续详细说明）

2. **创建窗口**  
   - 使用 `CreateWindowEx()` 函数

3. **窗口显示**  
   - 显示窗口：`ShowWindow()`  
   - 刷新客户区：`UpdateWindow()`

4. **消息循环处理**  
   消息处理的三步流程：  
   - **获取消息**：`GetMessage()`  
   - **转换消息**：`TranslateMessage()`  
   - **分发处理**：`DispatchMessage()`（最终交由回调函数处理）
## 详细讲解
###	一.注册窗口类RegisterClassEx()
```cpp 
ATOM WINAPI RegisterClassExA(_In_ CONST WNDCLASSEXA *);
```
正如这个代码所展示的那样实际上返回了一个ATOM对象。
> * 关于ATOM：实际上就是一个WORD对象，十六位无符号整数，形象的比喻就是图书馆管理系统之中的ISBN号，标志了图书的唯一位置但是本质上就仅仅是一段字符串。

> * 关于WINAPI：实际上就是一个_stdcall方法宏定义。

注册之前需要预定义一下WNDCLASSEX对象实现对于窗口的初始化操作，WNDCLASSEX结构体如下所展示
``` cpp
typedef struct tagWNDCLASSEXA {
    UINT        cbSize;
    /* Win 3.x */
    UINT        style;
    WNDPROC     lpfnWndProc;
    int         cbClsExtra;
    int         cbWndExtra;
    HINSTANCE   hInstance;
    HICON       hIcon;
    HCURSOR     hCursor;
    HBRUSH      hbrBackground;
    LPCSTR      lpszMenuName;
    LPCSTR      lpszClassName;
    /* Win 4.0 */
    HICON       hIconSm;
} WNDCLASSEXA, *PWNDCLASSEXA, NEAR *NPWNDCLASSEXA, FAR *LPWNDCLASSEXA;
```

### A. **先讲解一下cbSize，实际上就是确定结构体的大小，其中作用如下：**

> cbsize 英文全程count of byte size,微软简称cbsize。
1.  **确定结构体的版本**
    - 微软会更新Windows Api(添加新的结构体成员),通过cbsize的大小确定当前版本
2.  **防止缓冲区溢出执行恶意代码**
    - 系统会根据cbsize确定结构体有效范围，避免访问超过分配的内存。
3.  **兼容性处理**
    - 保证可以向下兼容旧的结构体。

### B. **讲解一下style类型**
* 实际上标志了窗口的刷新方式 

#### `style` 标志表
| 标志名称              | 值（十六进制） | 作用描述                                                                 |
|-----------------------|----------------|--------------------------------------------------------------------------|
| **`CS_HREDRAW`**      | `0x0001`       | 窗口水平尺寸（宽度）改变时，强制重绘整个窗口。                           |
| **`CS_VREDRAW`**      | `0x0002`       | 窗口垂直尺寸（高度）改变时，强制重绘整个窗口。                           |
| **`CS_OWNDC`**        | `0x0020`       | 为每个窗口实例分配独立的设备上下文（DC）。                               |
| **`CS_CLASSDC`**      | `0x0040`       | 同一窗口类的所有窗口共享一个类级别的设备上下文。                         |
| **`CS_PARENTDC`**     | `0x0080`       | 子窗口继承父窗口的设备上下文。                                           |
| **`CS_DBLCLKS`**      | `0x0008`       | 允许窗口接收鼠标双击事件（如 `WM_LBUTTONDBLCLK`）。                     |
| **`CS_SAVEBITS`**     | `0x0800`       | 将窗口的屏幕图像缓存为位图，用于快速恢复被遮挡区域。                     |
| **`CS_NOCLOSE`**      | `0x0200`       | 禁用窗口的关闭按钮（用户无法通过标题栏关闭窗口）。                       |
| **`CS_GLOBALCLASS`**  | `0x4000`       | 注册的窗口类为全局类，可被其他模块使用。                                 |
| **`CS_IME`**          | `0x00010000`   | 启用输入法编辑器（IME）支持。                                           |

---  
### C. **讲解一下`lpfnWndProc`：**
>全称 ​​Long Pointer to Window Procedure​​

根据名字可以看出来本质上是一个长指针指向之前定义的回调函数的返回值，然而那个回调函数是实现对于窗口的各种操作对应相应。

### D. **讲解一下`hInstance`：**
实际上就是一个实例化的句柄也可以称作一个模块标志。

### E. **讲解一下`hIcon`：**
    Icon很好理解吧，是一个图标的意思，实际上就是可执行文件的图标(是的没错就是你在桌面上看到的那个东西)
通过调用LoadIcon或者调用LoadImage进行调用。(Image也未尝不是一种Icon)
> 那么我们讲解一下LoadIcon函数吧

```cpp 
LoadIconA(
    _In_opt_ HINSTANCE hInstance,
    _In_ LPCSTR lpIconName);
WINUSERAPI
```
第一个参数是句柄第二个是加载的图标的`内定`名称(微软给的)。
可能取值如下

| 图标常量                 | 描述                                                                 |
|-------------------------|---------------------------------------------------------------------|
| `IDI_APPLICATION`       | 默认应用程序图标（通常是窗口或应用程序的默认图标）                  |
| `IDI_HAND`              | 错误图标（红色背景的“X”或手形图标，表示严重错误如系统崩溃）         |
| `IDI_QUESTION`          | 问号图标（旧版Windows中使用，现代UI可能已替换为其他设计）           |
| `IDI_EXCLAMATION`       | 感叹号图标（黄色三角形，用于警告或注意事项）                       |
| `IDI_ASTERISK`          | 信息图标（蓝色背景的“i”，通常用于提示性消息）                       |
| `IDI_WINLOGO`           | Windows徽标（经典Windows标志，如开始菜单图标）                      |
| `IDI_WARNING`           | 同 `IDI_EXCLAMATION`，表示警告                                      |
| `IDI_ERROR`             | 同 `IDI_HAND`，表示错误                                             |
| `IDI_INFORMATION`       | 同 `IDI_ASTERISK`，表示信息提示                                     |
| `IDI_SHIELD`            | 盾牌图标（用于UAC提示或需要管理员权限的操作）   

### F. **讲解一下`hCursor`：**
同上，本体函数如下
``` cpp
LoadCursorA(
    _In_opt_ HINSTANCE hInstance,
    _In_ LPCSTR lpCursorName);
```
一个句柄函数一个调用光标的名称，值得注意的是**光标**，就是你的鼠标的指示状态。

| 光标常量                | 描述                                                                 |
|-------------------------|---------------------------------------------------------------------|
| `IDC_ARROW`            | 标准箭头光标（默认光标）                                            |
| `IDC_IBEAM`            | I 形文本输入光标（用于可编辑文本区域）                              |
| `IDC_WAIT`             | 等待/忙碌光标（通常为沙漏或旋转圆圈）                               |
| `IDC_CROSS`            | 十字线光标（常用于绘图或选择区域）                                  |
| `IDC_UPARROW`          | 垂直箭头光标（指向正上方）                                          |
| `IDC_SIZE`             | 旧版 Windows 的调整大小光标（四向箭头）                             |
| `IDC_ICON`             | 旧版 Windows 的图标移动光标                                         |
| `IDC_SIZENWSE`         | 双箭头斜向光标（西北-东南方向，用于调整窗口大小）                   |
| `IDC_SIZENESW`         | 双箭头斜向光标（东北-西南方向，用于调整窗口大小）                   |
| `IDC_SIZEWE`           | 双箭头水平光标（左右方向，用于水平调整窗口大小）                    |
| `IDC_SIZENS`           | 双箭头垂直光标（上下方向，用于垂直调整窗口大小）                    |
| `IDC_SIZEALL`          | 四向箭头光标（用于移动窗口或对象）                                  |
| `IDC_NO`               | 禁止操作光标（带斜线的圆圈，表示当前操作不可用）                    |
| `IDC_HAND`             | 手形光标（通常用于超链接或可点击元素）                              |
| `IDC_APPSTARTING`      | 应用程序启动光标（箭头带小沙漏，表示程序正在启动）                  |
| `IDC_HELP`             | 帮助选择光标（箭头带问号）                                          |

### G. **讲解一下`hbrBackground`：**
如同它的名字一样就是个背景颜色。

### H. **讲解一下`lpszMenuName`：**
同之前上边长非零指针指向一个回调函数实现菜单的编写。

### I. **讲解一下`lpszClassName`：**
指定窗口的名称
>没错就是那个窗口名左上角显示的那个东西。

### J. **讲解一下`hIconSm`：**
与之前的不是Sm版本的相同。