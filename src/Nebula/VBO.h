#pragma once
#ifndef VBO_H
#define VBO_H
#include <vector>
#include <glad/glad.h>
#include "Vertex.h"

class VBO {
public:
    GLuint ID;

    VBO();
    ~VBO();
    void operator=(const std::vector<GLfloat>& vertices);
    void operator=(const std::vector<glm::mat4>& mat4s);
};
#endif //VBO_H
