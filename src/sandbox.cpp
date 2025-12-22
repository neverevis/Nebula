#include <platform/window.h>

int main()
{
    NBL::Window window(800,800,"Sandbox",BUTTON_MENU);
    window.show();

    while(!window.should_close())
    {
        window.poll_events();
    }
}