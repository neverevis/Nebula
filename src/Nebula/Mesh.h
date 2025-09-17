#ifndef MESH_H
#define MESH_H
#include <glad/glad.h>
#include "Vertex.h"
#include <vector>

class Mesh {
public:
    unsigned int VAO, VBO, EBO;
    std::vector<Vertex> vertices;
    std::vector<unsigned int> indices;

    Mesh(const std::vector<Vertex>& vertices, const std::vector<unsigned int>& indices);
    ~Mesh();
};
#endif
