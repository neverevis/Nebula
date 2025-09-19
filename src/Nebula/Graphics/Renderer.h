#ifndef RENDERER_H
#define RENDERER_H
#include "../Math/Camera.h"
#include "../Graphics/VAO.h"
#include "VBO.h"
#include "EBO.h"
#include "Mesh.h"
#include "../Core/Window.h"
#include "Shader.h"
#include "../Math/Transform.h"
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
    void draw(Mesh& mesh, Shader& shader, Transform& transform);
    void drawInstance(Mesh& mesh, Shader& shader, std::vector<Transform>& transforms);
    void setClearColor(float R, float G, float B, float A);
};
#endif //RENDERER_H
