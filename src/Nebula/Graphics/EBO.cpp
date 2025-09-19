#include "EBO.h"

#include "glad/glad.h"

EBO::EBO() {
    //generates the buffer
    glCreateBuffers(1,&ID);
}

EBO::~EBO() {
    glDeleteBuffers(1,&ID);
}

void EBO::operator=(const std::vector<unsigned int>& triangles) {
    //copy the data to the GPU
    glNamedBufferData(ID,triangles.size() * sizeof(unsigned),triangles.data(),GL_STATIC_DRAW);
    count = triangles.size();
}

int EBO::getCount() {
    return count;
}


