#include "Renderer.h"

Renderer::Renderer(Window& window):
window(&window)
{
    const GLubyte* version = glGetString(GL_VERSION);
    std::cout << "[Renderer] OpenGL Version: " << version << std::endl;

    glViewport(0,0,window.getWidth(),window.getHeight());
}

Renderer::~Renderer() = default;

void Renderer::setClearColor(float R, float G, float B, float A) {
    glClearColor(R,G,B,A);
}


