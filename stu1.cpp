#include <Windows.h>
#include <tchar.h>
#include <Shlwapi.h>    // 路径处理
#pragma comment(lib, "Winmm.lib")
#pragma comment(lib, "Shlwapi.lib")

#define SOUND_FILE  TEXT("sound.wav")  // 使用英文文件名

LRESULT CALLBACK WndProc(HWND, UINT, WPARAM, LPARAM);

int WINAPI WinMain(
    _In_ HINSTANCE hInstance,
    _In_opt_ HINSTANCE hPrevInstance,
    _In_ LPSTR lpCmdLine,
    _In_ int nCmdShow)
{
    // 1. 注册窗口类
    WNDCLASSEX wcex = { sizeof(WNDCLASSEX) };
    const TCHAR szClassName[] = TEXT("MyWindowsApp");

    wcex.style = CS_HREDRAW | CS_VREDRAW;
    wcex.lpfnWndProc = WndProc;
    wcex.hInstance = hInstance;
    wcex.hIcon = LoadIcon(NULL, IDI_APPLICATION);  // 正确图标
    wcex.hCursor = LoadCursor(NULL, IDC_ARROW);
    wcex.hbrBackground = (HBRUSH)(COLOR_WINDOW + 1);
    wcex.lpszClassName = szClassName;
    wcex.hIconSm = LoadIcon(NULL, IDI_APPLICATION);  // 小图标

    if (!RegisterClassEx(&wcex)) {
        MessageBox(NULL,
            TEXT("窗口类注册失败!"),
            TEXT("严重错误"),
            MB_ICONERROR | MB_OK);
        return 1;
    }

    // 2. 创建窗口
    HWND hWnd = CreateWindowEx(
        0,
        szClassName,
        TEXT("Windows应用程序示例"),
        WS_OVERLAPPEDWINDOW,
        CW_USEDEFAULT, CW_USEDEFAULT,
        400, 300,
        NULL,
        NULL,
        hInstance,
        NULL);

    if (!hWnd) {
        MessageBox(NULL,
            TEXT("窗口创建失败!"),
            TEXT("错误"),
            MB_ICONERROR | MB_OK);
        return 1;
    }

    // 3. 显示窗口
    ShowWindow(hWnd, nCmdShow);
    UpdateWindow(hWnd);

    // 4. 消息循环
    MSG msg;
    while (GetMessage(&msg, NULL, 0, 0)) {
        TranslateMessage(&msg);
        DispatchMessage(&msg);
    }

    return (int)msg.wParam;
}

// 窗口过程函数
LRESULT CALLBACK WndProc(
    HWND hWnd,
    UINT message,
    WPARAM wParam,
    LPARAM lParam)
{
    static HFONT hFont = NULL;

    switch (message) {
    case WM_CREATE: {
        // 初始化字体
        hFont = CreateFont(
            24, 0, 0, 0,
            FW_NORMAL,
            FALSE, FALSE, FALSE,
            DEFAULT_CHARSET,
            OUT_OUTLINE_PRECIS,
            CLIP_DEFAULT_PRECIS,
            CLEARTYPE_QUALITY,
            VARIABLE_PITCH,
            TEXT("微软雅黑"));

        // 获取声音文件路径
        TCHAR szPath[MAX_PATH];
        GetModuleFileName(NULL, szPath, MAX_PATH);
        PathRemoveFileSpec(szPath);
        PathAppend(szPath, SOUND_FILE);

        // 播放声音（带错误检查）
        if (!PlaySound(szPath, NULL, SND_FILENAME | SND_ASYNC | SND_NODEFAULT)) {
            MessageBox(hWnd,
                TEXT("无法加载音频文件\n请确认文件存在且格式正确"),
                TEXT("音频错误"),
                MB_ICONWARNING | MB_OK);
        }
        return 0;
    }

    case WM_PAINT: {
        PAINTSTRUCT ps;
        HDC hdc = BeginPaint(hWnd, &ps);

        // 设置字体和颜色
        SelectObject(hdc, hFont);
        SetTextColor(hdc, RGB(30, 144, 255));  // 道奇蓝
        SetBkMode(hdc, TRANSPARENT);

        // 绘制文本
        const TCHAR szText[] = TEXT("Hello Windows API!");
        TextOut(hdc, 50, 100, szText, _tcslen(szText));

        EndPaint(hWnd, &ps);
        return 0;
    }

    case WM_SIZE: {
        // 窗口尺寸变化时重绘
        InvalidateRect(hWnd, NULL, TRUE);
        return 0;
    }

    case WM_DESTROY: {
        // 清理资源
        if (hFont) DeleteObject(hFont);
        PostQuitMessage(0);
        return 0;
    }

    default:
        return DefWindowProc(hWnd, message, wParam, lParam);
    }
}