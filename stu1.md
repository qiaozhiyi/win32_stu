# ��� `stu1.cpp` ��ѧϰ�ʼ�

## �ؼ������ܽ�

Windows���ڴ������ĸ����Ĳ��裺

1. **ע�ᴰ����**  
   - ʹ�� `RegisterClassEx()` ����  
   - ע�⣺ע��ǰ������䴰�ڽṹ�壨������ϸ˵����

2. **��������**  
   - ʹ�� `CreateWindowEx()` ����

3. **������ʾ**  
   - ��ʾ���ڣ�`ShowWindow()`  
   - ˢ�¿ͻ�����`UpdateWindow()`

4. **��Ϣѭ������**  
   ��Ϣ������������̣�  
   - **��ȡ��Ϣ**��`GetMessage()`  
   - **ת����Ϣ**��`TranslateMessage()`  
   - **�ַ�����**��`DispatchMessage()`�����ս��ɻص���������
## ��ϸ����
###	һ.ע�ᴰ����RegisterClassEx()
```cpp 
ATOM WINAPI RegisterClassExA(_In_ CONST WNDCLASSEXA *);
```
�������������չʾ������ʵ���Ϸ�����һ��ATOM����
> * ����ATOM��ʵ���Ͼ���һ��WORD����ʮ��λ�޷�������������ı�������ͼ��ݹ���ϵͳ֮�е�ISBN�ţ���־��ͼ���Ψһλ�õ��Ǳ����Ͼͽ�����һ���ַ�����

> * ����WINAPI��ʵ���Ͼ���һ��_stdcall�����궨�塣

ע��֮ǰ��ҪԤ����һ��WNDCLASSEX����ʵ�ֶ��ڴ��ڵĳ�ʼ��������WNDCLASSEX�ṹ��������չʾ
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

�Ƚ���һ��cbSize��ʵ���Ͼ���ȷ���ṹ��Ĵ�С�������������£�

1.  **ȷ���ṹ��İ汾**
    - ΢������Windows Api(����µĽṹ���Ա),ͨ��cbsize�Ĵ�Сȷ����ǰ�汾
2.  **��ֹ���������ִ�ж������**
    - ϵͳ�����cbsizeȷ���ṹ����Ч��Χ��������ʳ���������ڴ档
3.  **�����Դ���**
    - ��֤�������¼��ݾɵĽṹ�塣
    
