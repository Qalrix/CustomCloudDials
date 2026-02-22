#pragma comment(linker,"\"/manifestdependency:type='win32' \
name='Microsoft.Windows.Common-Controls' version='6.0.0.0' \
processorArchitecture='*' publicKeyToken='6595b64144ccf1df' language='*'\"")

#pragma comment(lib, "comctl32.lib")
#pragma comment(lib, "user32.lib")
#pragma comment(lib, "gdi32.lib")

#ifndef UNICODE
#define UNICODE
#endif
#ifndef _UNICODE
#define _UNICODE
#endif

#define WIN32_LEAN_AND_MEAN
#include <windows.h>
#include "mkWatchFace.h" 
#define IDM_FILE_NEW  101
#define IDM_FILE_EXIT 102
#define IDM_HELP_ABOUT 103
#define ID_BTN_UPLOAD_ICON 1001
#define ID_COMBOBOX_WIDGETS 2001
LRESULT CALLBACK WindowProc(HWND hwnd, UINT uMsg, WPARAM wParam, LPARAM lParam) {
    switch (uMsg) {
        case WM_CTLCOLORSTATIC: {
            HDC hdcStatic = (HDC)wParam;
            HWND hwndChild = (HWND)lParam;
            int controlID = GetDlgCtrlID(hwndChild);

            if (controlID == 2) { 
                // 设置画布黑色
                SetBkColor(hdcStatic, RGB(0, 0, 0));
                return (LRESULT)GetStockObject(BLACK_BRUSH);
            } else {
                // 设置标签透明度
                SetBkMode(hdcStatic, TRANSPARENT);
                return (LRESULT)GetStockObject(NULL_BRUSH);
            }
        }
        case WM_DESTROY:
            PostQuitMessage(0);
            return 0;
    }
    return DefWindowProc(hwnd, uMsg, wParam, lParam);
}

int WINAPI wWinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, PWSTR pCmdLine, int nCmdShow) {
    const wchar_t CLASS_NAME[] = L"WatchFaceClass";
    
    WNDCLASSW wc = { }; 
    wc.lpfnWndProc   = WindowProc;
    wc.hInstance     = hInstance;
    wc.lpszClassName = CLASS_NAME;
    wc.hCursor       = LoadCursor(NULL, IDC_ARROW); 

    if (!RegisterClassW(&wc)) return 0;

    // 设置菜单栏
    HMENU hMenu = CreateMenu();
    HMENU hFileMenu = CreatePopupMenu();
    AppendMenuW(hFileMenu, MF_STRING, 101, L"Import iwf.json");
    AppendMenuW(hFileMenu, MF_STRING, 102, L"Export iwf.json");
    AppendMenuW(hFileMenu, MF_STRING, 103, L"Export font.json");
    AppendMenuW(hFileMenu, MF_STRING, 104, L"Export dial as .zip");
    AppendMenuW(hFileMenu, MF_SEPARATOR, 0, NULL);
    AppendMenuW(hFileMenu, MF_STRING, 105, L"Exit");
    AppendMenuW(hMenu, MF_POPUP, (UINT_PTR)hFileMenu, L"&File");

    // 创建主窗口
    HWND hwnd = CreateWindowExW(0, CLASS_NAME, L"mkWatchFace", WS_OVERLAPPEDWINDOW, 
                                CW_USEDEFAULT, CW_USEDEFAULT, 1280, 720, 
                                NULL, hMenu, hInstance, NULL);
    if (hwnd == NULL) return 0;

    // 应用现代字体
    HFONT hCustomFont = CreateFont(20, 0, 0, 0, FW_NORMAL, FALSE, FALSE, FALSE, 
                                   ANSI_CHARSET, OUT_DEFAULT_PRECIS, CLIP_DEFAULT_PRECIS, 
                                   CLEARTYPE_QUALITY, DEFAULT_PITCH | FF_SWISS, L"Segoe UI");

    // 创建元素
    // 帆布
    HWND hwndCanvas = CreateWindowEx(0, L"STATIC", NULL, WS_VISIBLE | WS_CHILD | SS_NOTIFY, 
                                     15, 15, 240, 240, hwnd, (HMENU)2, hInstance, NULL);

    // 图像按钮
    HWND hwndButton1 = CreateWindowEx(0, L"BUTTON", L"Upload Bkground", 
                                      WS_TABSTOP | WS_VISIBLE | WS_CHILD | BS_DEFPUSHBUTTON, 
                                      15, 265, 240, 40, hwnd, (HMENU)1, hInstance, NULL);

    // 观看小部件按钮
    HWND hwndButton2 = CreateWindowEx(0, L"BUTTON", L"Add Watch Widget", 
                                      WS_TABSTOP | WS_VISIBLE | WS_CHILD | BS_PUSHBUTTON, 
                                      15, 310, 240, 40, hwnd, (HMENU)1001, hInstance, NULL);

    // 创建标签
HWND hwndLabel = CreateWindowEx(
    0, L"STATIC", L"custom", 
    WS_VISIBLE | WS_CHILD | SS_LEFT, 
    15, 362, 100, 25,
    hwnd, NULL, hInstance, NULL);

                // 创建组合框
HWND hwndCombo = CreateWindowEx(
    0, L"COMBOBOX", L"", 
    WS_CHILD | WS_VISIBLE | CBS_DROPDOWNLIST | WS_VSCROLL,
    115, 360, 140, 200,
    hwnd, (HMENU)ID_COMBOBOX_WIDGETS, hInstance, NULL);

// 应用现代字体
SendMessage(hwndCombo, WM_SETFONT, (WPARAM)hCustomFont, TRUE);

// 添加自定义小部件项目
SendMessage(hwndCombo, CB_ADDSTRING, 0, (LPARAM)L"time");
SendMessage(hwndCombo, CB_ADDSTRING, 0, (LPARAM)L"hour");
SendMessage(hwndCombo, CB_ADDSTRING, 0, (LPARAM)L"hourhi");
SendMessage(hwndCombo, CB_ADDSTRING, 0, (LPARAM)L"hourlo");
SendMessage(hwndCombo, CB_ADDSTRING, 0, (LPARAM)L"min");
SendMessage(hwndCombo, CB_ADDSTRING, 0, (LPARAM)L"minhi");
SendMessage(hwndCombo, CB_ADDSTRING, 0, (LPARAM)L"minlo");
SendMessage(hwndCombo, CB_ADDSTRING, 0, (LPARAM)L"second");
SendMessage(hwndCombo, CB_ADDSTRING, 0, (LPARAM)L"week");
SendMessage(hwndCombo, CB_ADDSTRING, 0, (LPARAM)L"date");
SendMessage(hwndCombo, CB_ADDSTRING, 0, (LPARAM)L"day");
SendMessage(hwndCombo, CB_ADDSTRING, 0, (LPARAM)L"month");
SendMessage(hwndCombo, CB_ADDSTRING, 0, (LPARAM)L"year");
SendMessage(hwndCombo, CB_ADDSTRING, 0, (LPARAM)L"exercise");
SendMessage(hwndCombo, CB_ADDSTRING, 0, (LPARAM)L"walk");
SendMessage(hwndCombo, CB_ADDSTRING, 0, (LPARAM)L"step");
SendMessage(hwndCombo, CB_ADDSTRING, 0, (LPARAM)L"calorie");
SendMessage(hwndCombo, CB_ADDSTRING, 0, (LPARAM)L"distance");
SendMessage(hwndCombo, CB_ADDSTRING, 0, (LPARAM)L"heartrate");
SendMessage(hwndCombo, CB_ADDSTRING, 0, (LPARAM)L"battery");
SendMessage(hwndCombo, CB_ADDSTRING, 0, (LPARAM)L"apm");
SendMessage(hwndCombo, CB_ADDSTRING, 0, (LPARAM)L"units");
SendMessage(hwndCombo, CB_ADDSTRING, 0, (LPARAM)L"gradient");
SendMessage(hwndCombo, CB_ADDSTRING, 0, (LPARAM)L"anima");
SendMessage(hwndCombo, CB_ADDSTRING, 0, (LPARAM)L"shortcut");
SendMessage(hwndCombo, CB_ADDSTRING, 0, (LPARAM)L"icon");
SendMessage(hwndCombo, CB_ADDSTRING, 0, (LPARAM)L"multimeter");
SendMessage(hwndCombo, CB_ADDSTRING, 0, (LPARAM)L"bluetooth");
SendMessage(hwndCombo, CB_ADDSTRING, 0, (LPARAM)L"sleep");

// 将默认选择设置为第一项
SendMessage(hwndCombo, CB_SETCURSEL, 0, 0);

    // 将现代字体应用于一切
    SendMessage(hwndButton1, WM_SETFONT, (WPARAM)hCustomFont, TRUE);
    SendMessage(hwndButton2, WM_SETFONT, (WPARAM)hCustomFont, TRUE);
    SendMessage(hwndLabel, WM_SETFONT, (WPARAM)hCustomFont, TRUE);

    ShowWindow(hwnd, nCmdShow);

    MSG msg = { };
    while (GetMessage(&msg, NULL, 0, 0)) {
        TranslateMessage(&msg);
        DispatchMessage(&msg);
    }
    return 0;
}