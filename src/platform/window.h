#pragma once
#include <string>

class Window
{
public:
    void* handle;
    bool  close_flag;

    Window(int width, int height, const std::string& title);
    ~Window();

    void show();
    void poll_events();
    void swap_buffers();
    bool should_close();
};
