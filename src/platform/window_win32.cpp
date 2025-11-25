#ifdef _WIN32
#include "window.h"
#include "../utils/log.h"
#define WIN32_LEAN_AND_MEAN
#define NOMINMAX
#include <windows.h>

struct Handle
{
    HWND hWnd;
    HDC hdc;
    HGLRC hglrc;
};

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
handle(new Handle), close_flag(false)
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
    
    handle->hWnd = CreateWindowExA(0, "window", title.c_str(), WS_OVERLAPPEDWINDOW, 100, 100, width, height, nullptr, nullptr, wc.hInstance, nullptr);
    
    if (!handle->hWnd)
    {
        log_error("Failed to create window");
    }
    
    SetWindowLongPtr(handle->hWnd, GWLP_USERDATA, (LONG_PTR)this);
    
    handle->hdc = GetDC(handle->hWnd);
    
    PIXELFORMATDESCRIPTOR pfd = {};
    pfd.nSize = sizeof(PIXELFORMATDESCRIPTOR);
    pfd.nVersion = 1;
    pfd.dwFlags = PFD_DRAW_TO_WINDOW | PFD_SUPPORT_OPENGL| PFD_DOUBLEBUFFER;
    pfd.iPixelType = PFD_TYPE_RGBA;
    pfd.cColorBits = 32;
    pfd.cDepthBits = 24;
    pfd.cStencilBits = 8;
    pfd.iLayerType = PFD_MAIN_PLANE;
    
    int pixelFormat = ChoosePixelFormat(handle->hdc, &pfd);
    
    if(!pixelFormat)
    {
        log_error("failed to load pixel format");
    }
    
    if(!SetPixelFormat(handle->hdc, pixelFormat, &pfd))
    {
        log_error("failed to set pixel format");
    }
    
    handle->hglrc = wglCreateContext(handle->hdc);

    if(!handle->hglrc)
    {
        log_error("failed to create OpenGL context")
    }

    if(!wglMakeCurrent(handle->hdc, handle->hglrc))
    {
        log_error("failed to set OpenGL context");
    }
    
    ShowWindow(handle->hWnd, SW_SHOW);
}

Window::~Window()
{
    wglMakeCurrent(nullptr, nullptr);
    wglDeleteContext(handle->hglrc);
    ReleaseDC(handle->hWnd, handle->hdc);
    DestroyWindow(handle->hWnd);
    UnregisterClassA("window",GetModuleHandleA(nullptr));

    delete handle;
}

bool Window::should_close(){
    return close_flag;
}

void Window::poll_events()
{
    MSG msg;
    
    while(PeekMessageA(&msg, handle->hWnd, 0, 0, PM_REMOVE))
    {
        TranslateMessage(&msg);
        DispatchMessage(&msg);
    }
}

void Window::swap_buffers()
{
    SwapBuffers(handle->hdc);
}

#endif
