#include <iostream>
#include <memory>
#include <functional>
#include <windows.h>
#include <thread>

#include "command.h"
#include "stringutils.h"
#include "auge.h"

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

static bool running = false;

void checkMousePosition(HWND hWindow)
{
    while(running)
    {
        POINT mousePos;
        GetCursorPos(&mousePos);

        std::cout << 
            "x: " << mousePos.x << std::endl <<
            "y: " << mousePos.y << std::endl << std::endl;
    }

    std::cout << "Thread End" << std::endl;
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

    running = true;
    std::thread t{checkMousePosition, hWindow};

    MSG msg{};
    long n = 0;
    while(GetMessage(&msg, NULL, 0, 0))
    {
        TranslateMessage(&msg);
        DispatchMessage(&msg);
    }
    running = false;
}