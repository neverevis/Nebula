#include "VBO.h"

VBO::VBO() {
    //generates the buffer
    glCreateBuffers(1,&ID);
}

VBO::~VBO() {
    glDeleteBuffers(1,&ID);
}

void VBO::operator=(const std::vector<GLfloat>& vertices) {
    //copy the vertices to the buffer
    glNamedBufferData(ID,vertices.size() * sizeof(GLfloat),vertices.data(),GL_STATIC_DRAW);
}

void VBO::operator=(const std::vector<glm::mat4>& mat4s) {
    glNamedBufferData(ID,mat4s.size() * sizeof(glm::mat4),mat4s.data(),GL_STATIC_DRAW);
}