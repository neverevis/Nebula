#pragma once
#include <string>

struct Platform_Data;

class Window
{
public:
    Platform_Data*   data;
    bool            close_flag;

    Window(int width, int height, const std::string& title);
    ~Window();

    void show();
    void poll_events();
    void swap_buffers();
    bool should_close();
};