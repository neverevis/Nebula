#include "Window.h"

Window::Window(int w, int h, std::string title) :
width(w), height(h), title(title) {
    if (!glfwInit()) {
        std::cerr << "[Window] Error initializing GLFW." << std::endl;
    }else {
        std::cout << "[Window] GLFW Initialized." << std::endl;
    }

    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 4);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 6);
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

    window = glfwCreateWindow(w,h,title.c_str(),nullptr,nullptr);

    if (!window) {
        std::cerr << "[Window] Error creating a window." << std::endl;
    }else {
        std::cout << "[Window] Window initialized." << std::endl;
    }

    glfwMakeContextCurrent(window);

    gladLoadGLLoader((GLADloadproc)glfwGetProcAddress);

    glfwSetWindowUserPointer(window, this);
    glfwSetFramebufferSizeCallback(window, [](GLFWwindow* w, int width, int height){
        Window* win = static_cast<Window*>(glfwGetWindowUserPointer(w));
        win->width = width;
        win->height = height;
        glViewport(0, 0, width, height);
    });
}

Window::~Window() {
    glfwDestroyWindow(window);
    glfwTerminate();
}

bool Window::shouldClose() {
    return glfwWindowShouldClose(window);
}

void Window::pollEvents() {
    glfwPollEvents();
}

void Window::swapBuffers() {
    glfwSwapBuffers(window);
}

int Window::getWidth() {
    return this->width;
}

int Window::getHeight() {
    return this->height;
}


