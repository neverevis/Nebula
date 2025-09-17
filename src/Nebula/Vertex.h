#ifndef VERTEX_H
#define VERTEX_H
#include<glm/glm.hpp>
struct Vertex {
    glm::vec3 pos;
    glm::vec3 normal;
    glm::vec4 color;
    glm::vec2 uv;
};
#endif
