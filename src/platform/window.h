#pragma once
#include <string>

typedef void* native_handle;

class Window
{
public:
    native_handle   handle;
    bool            close_flag;

    Window(int width, int height, const std::string& title);
    ~Window();

    void show();
    void poll_events();
    void swap_buffers();
    bool should_close();
};