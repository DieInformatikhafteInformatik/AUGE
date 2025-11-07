#include <iostream>
#include <memory>
#include <functional>
#include <windows.h>
#include <thread>

#include "command.h"
#include "stringutils.h"
#include "auge.h"
#include "mouse.h"

LRESULT CALLBACK WindowProc(HWND hWindow, UINT uMsg, WPARAM wParam, LPARAM lParam)
{
    switch(uMsg)
    {
        case WM_CLOSE:
            DestroyWindow(hWindow);
            return 0;
        case WM_DESTROY:
            PostQuitMessage(0);
            return 0;
        default:
            return DefWindowProc(hWindow, uMsg, wParam, lParam);
    }
}

int main()
{
    HINSTANCE hInstance = GetModuleHandle(NULL);

    WNDCLASSA wc{};
    wc.lpfnWndProc = WindowProc;
    wc.hInstance = hInstance;
    wc.lpszClassName = "Testing";
    RegisterClassA(&wc);

    HWND hWindow = CreateWindowExA(
        0,
        wc.lpszClassName,
        "Test Window",
        WS_OVERLAPPEDWINDOW,

        CW_USEDEFAULT, CW_USEDEFAULT, CW_USEDEFAULT, CW_USEDEFAULT,

        NULL,
        NULL,
        hInstance,
        NULL
    );

    if(hWindow == NULL)
    {
        std::cerr << "Fehler beim Erstellen vom Fenster\n";
        return -1;
    }

    ShowWindow(hWindow, 1);
    UpdateWindow(hWindow);

    LoopThread lt = createMousePositionThread(hWindow, [](POINT p)
    {
        std::cout << p.x << std::endl << p.y << std::endl << std::endl;
    });

    
    lt.start();
    lt.setDaemon();


    MSG msg{};
    long n = 0;
    while(GetMessage(&msg, NULL, 0, 0))
    {
        TranslateMessage(&msg);
        DispatchMessage(&msg);
    }
}