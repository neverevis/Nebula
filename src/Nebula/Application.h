#ifndef APPLICATION_H
#define APPLICATION_H
#include "Renderer.h"
#include "Window.h"
#include <chrono>
class Application {
public:
    Window window;
    Renderer renderer;
    Application();
    virtual ~Application();

    void run();
    virtual void step() = 0;
};
#endif
