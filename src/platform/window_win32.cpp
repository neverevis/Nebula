#include <platform/definitions.h>
#ifdef PLATFORM_WINDOWS

#include <platform/window.h>
#include <utils/log.h>
#define WIN32_LEAN_AND_MEAN
#define NOMINMAX
#include <windows.h>

LRESULT CALLBACK wndProc(HWND hWnd, UINT msg, WPARAM wParam, LPARAM lParam)
{
    Window* window = (Window*) GetWindowLongPtr(hWnd, GWLP_USERDATA);

    switch(msg)
    {
        case WM_CLOSE: window->close_flag = true; break;
        case WM_KEYDOWN: log_trace("tecla pressionada!");
    }

    return DefWindowProcA(hWnd, msg, wParam, lParam);
}

Window::Window(int width, int height, const std::string& title):
close_flag(false)
{
    WNDCLASSA wc = {};
    wc.hInstance = GetModuleHandleA(nullptr);
    wc.lpfnWndProc = wndProc;
    wc.lpszClassName = "window";
    
    if(!RegisterClassA(&wc))
    {
        MessageBoxA(nullptr, "Erro ao Registrar classe janela", "Erro", MB_OK | MB_ICONERROR);
        log_error("Failed to register window class");
    }

    int screen_x = GetSystemMetrics(SM_CXSCREEN);
    int screen_y = GetSystemMetrics(SM_CYSCREEN);
    int x = screen_x/2 - width/2;
    int y = screen_y/2 - height/2;
    
    handle = CreateWindowExA(0, "window", title.c_str(), WS_OVERLAPPEDWINDOW, x, y, width, height, nullptr, nullptr, wc.hInstance, nullptr);
    
    if (!(HWND)handle)
    {
        log_error("Failed to create window");
    }
    
    SetWindowLongPtr((HWND) handle, GWLP_USERDATA, (LONG_PTR)this);
}

Window::~Window()
{
    DestroyWindow((HWND)handle);
    UnregisterClassA("window",GetModuleHandleA(nullptr));
}

void Window::show()
{
    ShowWindow((HWND)handle, SW_SHOW);
}

bool Window::should_close(){
    return close_flag;
}

void Window::poll_events()
{
    MSG msg;
    
    while(PeekMessageA(&msg, (HWND) handle, 0, 0, PM_REMOVE))
    {
        TranslateMessage(&msg);
        DispatchMessage(&msg);
    }
}

void Window::swap_buffers()
{
    SwapBuffers(GetDC((HWND) handle));
}

#endif
