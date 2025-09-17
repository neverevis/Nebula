#include "Mesh.h"

Mesh::Mesh(const std::vector<Vertex> &vertices, const std::vector<unsigned> &indices) {
    glCreateVertexArrays(1,&VAO);
    glCreateBuffers(1,&VBO);
    glCreateBuffers(1,&EBO);
}

Mesh::~Mesh() {
}
