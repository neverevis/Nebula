#include <platform/gl_loader.h>
#include <platform/window.h>
#include <windows.h>
#include <iostream>
#include <GL/gl.h>

int main()
{
   
   Window window(800,800,"Janela!");
   gl_load_context(window);
   window.show();
   
   while(!window.should_close())
   {
      glClearColor(1,1,1,1);
      glClear(GL_COLOR_BUFFER_BIT);
      window.poll_events();

      glBegin(GL_TRIANGLES);
      glColor3f(1,0,0);
      glVertex2f(0.0f, 0.5f);
      glColor3f(0,1,1);
      glVertex2f(0.5f, -0.5f);
      glColor3f(0,0,1);
      glVertex2f(-0.5f, -0.5f);
      glEnd();

      window.swap_buffers();
   }
}