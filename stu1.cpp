#include <Windows.h>
#include <tchar.h>
#include <Shlwapi.h>    // ·������
#pragma comment(lib, "Winmm.lib")
#pragma comment(lib, "Shlwapi.lib")

#define SOUND_FILE  TEXT("sound.wav")  // ʹ��Ӣ���ļ���

LRESULT CALLBACK WndProc(HWND, UINT, WPARAM, LPARAM);

int WINAPI WinMain(
    _In_ HINSTANCE hInstance,
    _In_opt_ HINSTANCE hPrevInstance,
    _In_ LPSTR lpCmdLine,
    _In_ int nCmdShow)
{
    // 1. ע�ᴰ����
    WNDCLASSEX wcex = { sizeof(WNDCLASSEX) };
    const TCHAR szClassName[] = TEXT("MyWindowsApp");

    wcex.style = CS_HREDRAW | CS_VREDRAW;
    wcex.lpfnWndProc = WndProc;
    wcex.hInstance = hInstance;
    wcex.hIcon = LoadIcon(NULL, IDI_APPLICATION);  // ��ȷͼ��
    wcex.hCursor = LoadCursor(NULL, IDC_ARROW);
    wcex.hbrBackground = (HBRUSH)(COLOR_WINDOW + 1);
    wcex.lpszClassName = szClassName;
    wcex.hIconSm = LoadIcon(NULL, IDI_APPLICATION);  // Сͼ��

    if (!RegisterClassEx(&wcex)) {
        MessageBox(NULL,
            TEXT("������ע��ʧ��!"),
            TEXT("���ش���"),
            MB_ICONERROR | MB_OK);
        return 1;
    }

    // 2. ��������
    HWND hWnd = CreateWindowEx(
        0,
        szClassName,
        TEXT("WindowsӦ�ó���ʾ��"),
        WS_OVERLAPPEDWINDOW,
        CW_USEDEFAULT, CW_USEDEFAULT,
        400, 300,
        NULL,
        NULL,
        hInstance,
        NULL);

    if (!hWnd) {
        MessageBox(NULL,
            TEXT("���ڴ���ʧ��!"),
            TEXT("����"),
            MB_ICONERROR | MB_OK);
        return 1;
    }

    // 3. ��ʾ����
    ShowWindow(hWnd, nCmdShow);
    UpdateWindow(hWnd);

    // 4. ��Ϣѭ��
    MSG msg;
    while (GetMessage(&msg, NULL, 0, 0)) {
        TranslateMessage(&msg);
        DispatchMessage(&msg);
    }

    return (int)msg.wParam;
}

// ���ڹ��̺���
LRESULT CALLBACK WndProc(
    HWND hWnd,
    UINT message,
    WPARAM wParam,
    LPARAM lParam)
{
    static HFONT hFont = NULL;

    switch (message) {
    case WM_CREATE: {
        // ��ʼ������
        hFont = CreateFont(
            24, 0, 0, 0,
            FW_NORMAL,
            FALSE, FALSE, FALSE,
            DEFAULT_CHARSET,
            OUT_OUTLINE_PRECIS,
            CLIP_DEFAULT_PRECIS,
            CLEARTYPE_QUALITY,
            VARIABLE_PITCH,
            TEXT("΢���ź�"));

        // ��ȡ�����ļ�·��
        TCHAR szPath[MAX_PATH];
        GetModuleFileName(NULL, szPath, MAX_PATH);
        PathRemoveFileSpec(szPath);
        PathAppend(szPath, SOUND_FILE);

        // �����������������飩
        if (!PlaySound(szPath, NULL, SND_FILENAME | SND_ASYNC | SND_NODEFAULT)) {
            MessageBox(hWnd,
                TEXT("�޷�������Ƶ�ļ�\n��ȷ���ļ������Ҹ�ʽ��ȷ"),
                TEXT("��Ƶ����"),
                MB_ICONWARNING | MB_OK);
        }
        return 0;
    }

    case WM_PAINT: {
        PAINTSTRUCT ps;
        HDC hdc = BeginPaint(hWnd, &ps);

        // �����������ɫ
        SelectObject(hdc, hFont);
        SetTextColor(hdc, RGB(30, 144, 255));  // ������
        SetBkMode(hdc, TRANSPARENT);

        // �����ı�
        const TCHAR szText[] = TEXT("Hello Windows API!");
        TextOut(hdc, 50, 100, szText, _tcslen(szText));

        EndPaint(hWnd, &ps);
        return 0;
    }

    case WM_SIZE: {
        // ���ڳߴ�仯ʱ�ػ�
        InvalidateRect(hWnd, NULL, TRUE);
        return 0;
    }

    case WM_DESTROY: {
        // ������Դ
        if (hFont) DeleteObject(hFont);
        PostQuitMessage(0);
        return 0;
    }

    default:
        return DefWindowProc(hWnd, message, wParam, lParam);
    }
}