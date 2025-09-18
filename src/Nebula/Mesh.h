#ifndef MESH_H
#define MESH_H
#include <glad/glad.h>
#include "Vertex.h"
#include <vector>

#include "VAO.h"

class Mesh {
public:
    VAO vao;
    VBO vertices;
    EBO triangles;
    Mesh();
    ~Mesh();
};
#endif
