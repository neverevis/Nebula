#ifndef RENDERER_H
#define RENDERER_H
#include <glad/glad.h>
#include "Window.h"
class Renderer {
private:
    Window* window;
public:
    Renderer(Window& window);
    ~Renderer();

    void setClearColor(float R, float G, float B, float A);
};
#endif //RENDERER_H
