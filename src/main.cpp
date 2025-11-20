// =-=-=-=-= Platform Globals =-=-=-=-=
static bool running = true;

// =-=-=-=-= Platform Functions =-=-=-=-=
bool platform_create_window(int width, int height, char* title);
void platform_update_window();

// =-=-=-=-= Windows platform =-=-=-=-=
#ifdef _WIN32
#define WIN32_LEAN_AND_MEAN
#define NOMINXMAX
#include <windows.h>

// =-=-=-=-= Windows Globals =-=-=-=-=
static HWND hWnd;

// =-=-=-=-= Platform Implementations =-=-=-=-=
LRESULT CALLBACK windows_window_callback(HWND hWnd, UINT msg, WPARAM wParam, LPARAM lParam)
{
    LRESULT result = 0;

    switch(msg)
    {
        case WM_CLOSE:
        {
            running = false;
            break;
        }

        default:
        {
            result = DefWindowProcA(hWnd, msg, wParam, lParam);
            break;
        }
    }

    return result;
}

bool platform_create_window(int width, int height, char* title)
{
    HINSTANCE instance = GetModuleHandleA(0);
    char* className = "platform_window";
    int style = WS_OVERLAPPEDWINDOW;

    WNDCLASSA wc = {};
    wc.hInstance = instance;
    wc.hIcon = LoadIcon(instance, IDI_APPLICATION);
    wc.hCursor = LoadCursor(instance, IDC_ARROW);
    wc.lpszClassName = className;
    wc.lpfnWndProc = windows_window_callback;

    if (!RegisterClassA(&wc))
    {
        return false;
    }

    int screenW = GetSystemMetrics(SM_CXSCREEN);
    int screenH = GetSystemMetrics(SM_CYSCREEN);

    int x = screenW / 2 - width / 2;
    int y = screenH / 2 - height / 2;

    hWnd = CreateWindowExA(0, className, title, style, x, y, width, height, nullptr, nullptr, instance, nullptr);

    if(!hWnd)
    {
        return false;
    }

    ShowWindow(hWnd, SW_SHOW);

    return true;
}

void platform_update_window()
{
    MSG msg;

    while(PeekMessageA(&msg, hWnd, 0, 0, PM_REMOVE))
    {
        TranslateMessage(&msg);
        DispatchMessage(&msg);
    }
}

#endif

int main()
{
    platform_create_window(800,800,"Game");

    while(running)
    {
        platform_update_window();
    }
}