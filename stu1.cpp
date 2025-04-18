#include <Windows.h>
#include <tchar.h>

//�����ص�����
LRESULT CALLBACK WndProc(HWND, UINT, WPARAM, LPARAM);

int WINAPI WinMain(
    _In_ HINSTANCE hInstance,
    _In_opt_ HINSTANCE hPrevInstance,
    _In_ LPSTR lpCmdLine,
    _In_ int nCmdShow)
{
    // 1. ע�ᴰ����
    WNDCLASSEX wndclassex = { sizeof(WNDCLASSEX) };
    const TCHAR szClassName[] = TEXT("MyWindowsApp");

    wndclassex.style = CS_HREDRAW | CS_VREDRAW;
    wndclassex.lpfnWndProc = WndProc;
    wndclassex.hInstance = hInstance;
    wndclassex.hIcon = LoadIcon(NULL, IDI_APPLICATION);  // ��ȷͼ��
    wndclassex.hCursor = LoadCursor(NULL, IDC_ARROW);
    wndclassex.hbrBackground = (HBRUSH)(COLOR_WINDOW + 1);
    wndclassex.lpszClassName = szClassName;
    wndclassex.hIconSm = LoadIcon(NULL, IDI_APPLICATION);  // Сͼ��

    //��ƴ�����
    if (!RegisterClassEx(&wndclassex)) {
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

    return (int)msg.wParam;//ǿת�����д
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

        return 0;
    }

    case WM_PAINT: {
        PAINTSTRUCT ps;
        HDC hdc = BeginPaint(hWnd, &ps);

        // �����������ɫ
        SelectObject(hdc, hFont);
        SetTextColor(hdc, RGB(30, 144, 255));  // ������(�ο�RGB��ɫ��)
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