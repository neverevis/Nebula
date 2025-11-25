#include "platform/window.h"
#include <iostream>
#include <windows.h>
#include <GL/gl.h>

int main()
{
   
   Window window(800,800,"Janela!");
   
   while(!window.should_close())
   {
      glClearColor(1,15,0,1);
      glClear(GL_COLOR_BUFFER_BIT);
      window.poll_events();

      glBegin(GL_TRIANGLES);
      glColor3f(1,0,0);
      glVertex2f(0.0f, 0.5f);
      glColor3f(0,1,0);
      glVertex2f(0.5f, -0.5f);
      glColor3f(0,0,1);
      glVertex2f(-0.5f, -0.5f);
      glEnd();

      window.swap_buffers();
   }
}