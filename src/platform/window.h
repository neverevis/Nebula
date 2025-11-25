#pragma once
#include <string>

struct Handle;

class Window
{
public:
    bool close_flag;

    Window(int width, int height, const std::string& title);
    ~Window();

    void poll_events();
    void swap_buffers();
    bool should_close();

private:
    Handle* handle;
};
