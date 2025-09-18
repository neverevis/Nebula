#include "Application.h"

Application::Application(int width, int height, const std::string& title):
window(width,height,title.c_str()), renderer(window){}

Application::~Application() = default;

void Application::run() {
    using clock = std::chrono::high_resolution_clock;
    using time = std::chrono::time_point<std::chrono::system_clock>;

    time lastTime = clock::now();
    time currentTime = clock::now();
    std::chrono::duration<float> delta;
    float dt;

    while (!window.shouldClose()) {
        currentTime = clock::now();
        delta = currentTime - lastTime;
        lastTime = currentTime;
        dt = delta.count();
        step(dt);
        window.pollEvents();
        window.swapBuffers();
    }
}
