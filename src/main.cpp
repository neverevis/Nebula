#include "core/window.h"
#include <vulkan/vulkan.h>
#include <iostream>
#include <windows.h>

int main()
{
     Window window(800,800,"OpenGL WINDOW");

     while(!window.should_close())
     {
        window.poll_events();
     }
}