#ifndef WINDOW_H
#define WINDOW_H
#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include <iostream>
class Window {
private:
    GLFWwindow* window;
    std::string title;
    int width, height;

    void framebuffer_size_callback(GLFWwindow* window, int width, int height);
public:
    Window(int w, int h, std::string title);
    ~Window();

    bool shouldClose();
    void pollEvents();
    void swapBuffers();
    void setSize(int width, int height);

    int getWidth();
    int getHeight();
    int getKey(int key);
};
#endif
