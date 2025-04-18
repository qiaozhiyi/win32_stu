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

先讲解一下cbSize，实际上就是确定结构体的大小，其中作用如下：

1.  **确定结构体的版本**
    - 微软会更新Windows Api(添加新的结构体成员),通过cbsize的大小确定当前版本
2.  **防止缓冲区溢出执行恶意代码**
    - 系统会根据cbsize确定结构体有效范围，避免访问超过分配的内存。
3.  **兼容性处理**
    - 保证可以向下兼容旧的结构体。
    
