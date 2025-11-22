#ifdef _WIN32
#define WIN32_LEAN_AND_MEAN
#define NOMINMAX
#include <windows.h>
#include "../core/window.h"
#include "../utils/log.h"

static HWND hWnd;
static bool closeFlag = false;

LRESULT CALLBACK wndProc(HWND hWnd, UINT msg, WPARAM wParam, LPARAM lParam)
{
    switch(msg)
    {
        case WM_CLOSE: closeFlag = true; break;
        case WM_KEYDOWN: log_trace("tecla pressionada!");
    }

    return DefWindowProcA(hWnd, msg, wParam, lParam);
}

bool Window::should_close(){
    return closeFlag;
}

Window::Window(int width, int height, const std::string& title)
{
    WNDCLASSA wc = {
        .lpfnWndProc = wndProc,
        .hInstance = GetModuleHandleA(nullptr),
        .lpszClassName = "window"
    };

    if(!RegisterClassA(&wc))
    {
        MessageBoxA(nullptr, "Erro ao Registrar classe janela", "Erro", MB_OK | MB_ICONERROR);
        log_error("Failed to register window class");
    }

    hWnd = CreateWindowExA(0, "window", title.c_str(), WS_OVERLAPPEDWINDOW, 100, 100, width, height, nullptr, nullptr, wc.hInstance, nullptr);

    if (!hWnd)
    {
        log_error("Failed to create window");
    }
    
    ShowWindow(hWnd, SW_SHOW);
}

void Window::poll_events()
{
    MSG msg;

    while(PeekMessageA(&msg, hWnd, 0, 0, PM_REMOVE))
    {
        TranslateMessage(&msg);
        DispatchMessage(&msg);
    }
}

#endif
