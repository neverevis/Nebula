#include "Camera.h"
std::vector<Camera*> Camera::cameras;

Camera::Camera() {
    cameras.push_back(this);
}

Camera::~Camera() {
    cameras.erase(std::remove(cameras.begin(),cameras.end(),this),cameras.end());
}


glm::mat4 Camera::getView() {
    return glm::lookAt(position,target,up);
}

glm::mat4 Camera::getProj() {
    return glm::perspective(glm::radians(fov), aspect, nearPlane, farPlane);
}
