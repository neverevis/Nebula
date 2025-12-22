#pragma once

#define FLAGS char

#define BUTTON_MENU     0x1
#define RESIZE_BUTTON   0x2
#define MINIMIZE_BUTTON 0x4

struct Platform_Data;

namespace NBL
{
    class Window
    {
    public:
        Platform_Data*  data;
        FLAGS           flags;
        bool            close_flag;

        Window(int width, int height, const char* title, FLAGS flags);
        ~Window();

        void show();
        void poll_events();
        void swap_buffers();
        bool should_close();
    };
}