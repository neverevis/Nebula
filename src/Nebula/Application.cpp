#include "Application.h"

Application::Application():
window(1280,720,"app"), renderer(window){}

Application::~Application() = default;

void Application::run() {
    while (!window.shouldClose()) {
        glClear(GL_COLOR_BUFFER_BIT);
        step();
        window.pollEvents();
        window.swapBuffers();
    }
}