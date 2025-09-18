#include "Mesh.h"

Mesh::Mesh(){
    vao.linkVBO(vertices,12 * sizeof(GLfloat));
    vao.linkEBO(triangles);
    vao.linkAttrib(0,3,0);
    vao.linkAttrib(1,3,12);
    vao.linkAttrib(2,4,24);
    vao.linkAttrib(3,2,40);
}

Mesh::~Mesh() {
}

