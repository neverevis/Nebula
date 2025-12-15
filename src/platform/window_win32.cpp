#include <platform/platform.h>
#ifdef PLATFORM_WINDOWS

#include <platform/window.h>
#include <utils/log.h>

static bool class_registered = false;

LRESULT CALLBACK wndProc(HWND hWnd, UINT msg, WPARAM wParam, LPARAM lParam)
{
    Window* window = (Window*) GetWindowLongPtr(hWnd, GWLP_USERDATA);

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

Window::Window(int width, int height, const std::string& title):
close_flag(false),
data(new Platform_Data)
{
    data->handle_window = nullptr;
    data->handle_device_context = nullptr;
    data->handle_gl_render_context = nullptr;

    if(!class_registered)
    {
        WNDCLASSA wc = {};
        wc.hInstance = GetModuleHandleA(nullptr);
        wc.lpfnWndProc = wndProc;
        wc.lpszClassName = "window_class";

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

    int screen_x = GetSystemMetrics(SM_CXSCREEN);
    int screen_y = GetSystemMetrics(SM_CYSCREEN);
    int x = screen_x/2 - width/2;
    int y = screen_y/2 - height/2;
    
    data->handle_window = CreateWindowExA(0, "window_class", title.c_str(), WS_OVERLAPPEDWINDOW, x, y, width, height, nullptr, nullptr, GetModuleHandleA(nullptr), nullptr);
    
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

Window::~Window()
{
    ReleaseDC(data->handle_window ,data->handle_device_context);
    DestroyWindow(data->handle_window);
    delete data;
}

void Window::show()
{
    ShowWindow(data->handle_window, SW_SHOW);
}

bool Window::should_close(){
    return close_flag;
}

void Window::poll_events()
{
    MSG msg;
    
    while(PeekMessageA(&msg, data->handle_window, 0, 0, PM_REMOVE))
    {
        TranslateMessage(&msg);
        DispatchMessage(&msg);
    }
}

void Window::swap_buffers()
{
    SwapBuffers(data->handle_device_context);
}

#endif
