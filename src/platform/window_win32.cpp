#include <platform/platform.h>
#ifdef PLATFORM_WINDOWS

#include <platform/window.h>
#include <utils/log.h>

static bool class_registered = false;

LRESULT CALLBACK wndProc(HWND hWnd, UINT msg, WPARAM wParam, LPARAM lParam)
{
    NBL::Window* window = (NBL::Window*) GetWindowLongPtr(hWnd, GWLP_USERDATA);

    switch(msg)
    {
        case WM_CLOSE: window->close_flag = true; break;
        case WM_KEYDOWN:
        {
            log_trace("%d",wParam);
        }
    }

    return DefWindowProcA(hWnd, msg, wParam, lParam);
}

NBL::Window::Window(int width, int height, const char* title, FLAGS flags):
close_flag(false),
data(new Platform_Data)
{
    if(!class_registered)
    {
        WNDCLASSA wc = {};
        wc.hInstance = GetModuleHandleA(nullptr);
        wc.lpfnWndProc = wndProc;
        wc.lpszClassName = "window_class";
        wc.style = CS_OWNDC;

         if(!RegisterClassA(&wc))
        {
            MessageBoxA(nullptr, "Failed to register window class", "Erro", MB_OK | MB_ICONERROR);
            log_error("Failed to register window class");
        }

        class_registered = true;
    }

    RECT borderRect = {0, 0, width, height};
    AdjustWindowRectEx(&borderRect, WS_OVERLAPPEDWINDOW, NULL, NULL);
    width = borderRect.right - borderRect.left;
    height = borderRect.bottom - borderRect.top;

    int x = GetSystemMetrics(SM_CXSCREEN)/2 - width/2;
    int y = GetSystemMetrics(SM_CYSCREEN)/2 - height/2;

    DWORD style = 0;

    if(flags & BUTTON_MENU)
    {
        style |= WS_SYSMENU;
    }
    if(flags & RESIZE_BUTTON)
    {
        style |= WS_SIZEBOX;
    }
    if(flags & MINIMIZE_BUTTON)
    {
        style |= WS_MINIMIZEBOX;
        style |= WS_MAXIMIZEBOX;
    }
    
    data->handle_window = CreateWindowExA(0, "window_class", title, style, x, y, width, height, nullptr, nullptr, GetModuleHandleA(nullptr), nullptr);
    
    if (!data->handle_window)
    {
        log_error("Failed to create window");
    }

    data->handle_device_context = GetDC(data->handle_window);

    if (!data->handle_window)
    {
        log_error("Failed to load device context");
    }
    
    SetWindowLongPtr(data->handle_window, GWLP_USERDATA, (LONG_PTR)this);
}

NBL::Window::~Window()
{
    ReleaseDC(data->handle_window ,data->handle_device_context);
    DestroyWindow(data->handle_window);
    delete data;
}

void NBL::Window::show()
{
    ShowWindow(data->handle_window, SW_SHOW);
}

bool NBL::Window::should_close(){
    return close_flag;
}

void NBL::Window::poll_events()
{
    MSG msg;
    
    while(PeekMessageA(&msg, data->handle_window, 0, 0, PM_REMOVE))
    {
        TranslateMessage(&msg);
        DispatchMessage(&msg);
    }
}

void NBL::Window::swap_buffers()
{
    SwapBuffers(data->handle_device_context);
}

#endif
