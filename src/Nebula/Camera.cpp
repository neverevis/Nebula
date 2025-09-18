#include "Camera.h"

glm::mat4 Camera::getView() {
    return glm::lookAt(position,target,up);
}

glm::mat4 Camera::getProj() {
    return glm::perspective(glm::radians(fov), aspect, nearPlane, farPlane);
}
