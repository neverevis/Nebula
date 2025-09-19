#include "Renderer.h"

Renderer::Renderer(Window& window):
window(&window)
{
    glEnable(GL_DEPTH_TEST);
    const GLubyte* version = glGetString(GL_VERSION);
    std::cout << "[Renderer] OpenGL Version: " << version << std::endl;

    glViewport(0, 0, window.getWidth(), window.getHeight());
}


Renderer::~Renderer() {
}

void Renderer::setCamera(Camera& camera) {
    _camera = &camera;
}


void Renderer::begin() {
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
}

void Renderer::end() {
}


void Renderer::draw(Mesh& mesh, Shader& shader, Transform& transform) {
    shader.use();
    mesh.vao.bind();

    glm::mat4 view = _camera->getView();
    glm::mat4 proj = _camera->getProj();

    shader.setMat4("view", view);
    shader.setMat4("proj",proj);
    shader.setMat4("model",transform.getModel());

    glDrawElements(GL_TRIANGLES,mesh.triangles.getCount(),GL_UNSIGNED_INT,0);
}

void Renderer::drawInstance(Mesh& mesh, Shader& shader, std::vector<Transform>& transforms) {

}


void Renderer::setClearColor(float R, float G, float B, float A) {
    glClearColor(R,G,B,A);
}


