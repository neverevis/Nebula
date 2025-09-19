#ifndef TRANSFORM_H
#define TRANSFORM_H
#include "glm/glm.hpp"
#include "glm/gtc/matrix_transform.hpp"

class Transform {
public:
    glm::vec3 position = glm::vec3(0.0f);
    glm::vec3 rotation = glm::vec3(0.0f);
    glm::vec3 scale = glm::vec3(1.0f);

    glm::mat4 getModel();
};
#endif
