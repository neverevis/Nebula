#pragma once

#define word char

#define RESIZABLE       0x1
#define CLOSE_BUTTON    0x2

struct Platform_Data;

namespace NBL
{
    class Window
    {
    public:
        Platform_Data*  data;
        bool            close_flag;
        word            flags;

        Window(int width, int height, const char* title);
        ~Window();

        void show();
        void poll_events();
        void swap_buffers();
        bool should_close();
    };
}