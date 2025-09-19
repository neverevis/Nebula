#ifndef APPLICATION_H
#define APPLICATION_H
#include "../Graphics/Renderer.h"
#include "Window.h"
#include <chrono>
class Application {
public:
    Window window;
    Renderer renderer;
    Application(int width, int height, const std::string& title);
    virtual ~Application();

    void run();

    virtual void step(float dt) = 0;
};
#endif
