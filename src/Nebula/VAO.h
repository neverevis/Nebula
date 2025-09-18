#pragma once
#include <glad/glad.h>
#include "VBO.h"
#include "EBO.h"

class VAO {
public:
    GLuint ID;

    VAO();
    ~VAO();

    void bind();

    void linkVBO(VBO& VBO, GLsizei stride);
    void linkEBO(EBO& EBO);
    void linkAttrib(GLuint layout, GLuint components, GLuint offset);
};
