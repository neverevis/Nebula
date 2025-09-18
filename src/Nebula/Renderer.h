#ifndef RENDERER_H
#define RENDERER_H
#include "Camera.h"
#include "VAO.h"
#include "VBO.h"
#include "EBO.h"
#include "Mesh.h"
#include "Window.h"
#include "Shader.h"
class Renderer {
private:
    Window* window;
    Camera* _camera;
public:
    Renderer(Window& window);
    ~Renderer();

    void setCamera(Camera& camera);
    void begin();
    void end();
    void draw(Mesh& mesh, Shader& shader, glm::mat4 model);
    void setClearColor(float R, float G, float B, float A);
};
#endif //RENDERER_H
