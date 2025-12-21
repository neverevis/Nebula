#include <platform/window.h>

int main()
{
    NBL::Window window(800,800,"test");
    window.show();

    while(!window.should_close())
    {
        window.poll_events();
    }
}