#pragma once
#include <string>

class Window
{
public:
    Window(int width, int height, const std::string& title);
    ~Window() = default;

    void poll_events();
    bool should_close();
};
