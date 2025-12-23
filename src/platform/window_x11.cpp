#include <platform/platform.h>
#ifdef PLATFORM_LINUX

#include <platform/window.h>
#include <X11/Xlib.h>
#include <X11/Xutil.h>
#include <utils/log.h>

static Atom WM_DELETE_WINDOW;

NBL::Window::Window(int width, int height, const char* title, FLAGS flags) :
data(new Platform_Data),
close_flag(false)
{
    data->display = XOpenDisplay(nullptr);
    if(!data->display)
    {
        log_error("Failed to connect to X server");
    }

    int screen = XDefaultScreen(data->display);

    data->window = XCreateSimpleWindow(data->display, RootWindow(data->display, screen), 0, 0, width, height, 1, BlackPixel(data->display, screen), WhitePixel(data->display, screen));

    XStoreName(data->display, data->window, title);

    XSelectInput(data->display, data->window, ExposureMask | KeyPressMask);

    WM_DELETE_WINDOW = XInternAtom(data->display, "WM_DELETE_WINDOW",False);
    
    if (WM_DELETE_WINDOW == None) {
        log_error("Failed to intern WM_DELETE_WINDOW atom");
    }
    XSetWMProtocols(data->display, data->window, &WM_DELETE_WINDOW, 1);
}

NBL::Window::~Window()
{
    XDestroyWindow(data->display, data->window);
}

void NBL::Window::poll_events()
{
    XEvent event;
    while(XPending(data->display) > 0)
    {
        XNextEvent(data->display, &event);
        if(event.type == ClientMessage && (Atom)event.xclient.data.l[0] == WM_DELETE_WINDOW)
        {
            close_flag = true;
        }
    }
}

bool NBL::Window::should_close()
{
    return close_flag;
}

void NBL::Window::show()
{
    XWindowAttributes attr;
    XGetWindowAttributes(data->display, data->window, &attr);

    int screen = XDefaultScreen(data->display);

    int x = XDisplayWidth(data->display, screen)/2 - attr.width/2;
    int y = XDisplayHeight(data->display, screen)/2 - attr.height/2;

    XMapWindow(data->display, data->window);

    XMoveWindow(data->display, data->window, x, y);
}

#endif