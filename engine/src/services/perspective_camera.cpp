//
// Created by naszly on 8/22/22.
//

#include "perspective_camera.h"
#include <glm/gtc/matrix_transform.hpp>

PerspectiveCamera::PerspectiveCamera(glm::vec3 position, float yaw, float pitch, float fov)
        : position(position),
          yaw(yaw), pitch(pitch),
          FOV(fov) {
    update();
}

glm::mat4 PerspectiveCamera::getViewMatrix() const {
    return glm::lookAt(position, position + front, worldUp);
}

glm::mat4 PerspectiveCamera::getProjectionMatrix() const {
    return glm::perspective(FOV, aspect, nearPlane, farPlane);
}

glm::vec3 PerspectiveCamera::getPosition() const {
    return position;
}

glm::vec3 PerspectiveCamera::getDirection() const {
    return front;
}

void PerspectiveCamera::setPosition(glm::vec3 position) {
    this->position = position;
}

void PerspectiveCamera::setAspectRatio(float aspectRatio) {
    this->aspect = aspectRatio;
}

void PerspectiveCamera::rotate(float dx, float dy) {
    yaw += dx;
    pitch += dy;

    pitch = glm::clamp(pitch, -M_PIf / 2, M_PIf / 2);

    update();
}

void PerspectiveCamera::move(float dx, float dy, float dz) {
    glm::vec4 movement = (glm::vec4(dx, dy, dz, 0) * getViewMatrix());
    position.x += movement.x;
    position.y += movement.y;
    position.z += movement.z;
}

void PerspectiveCamera::update() {
    front.x = cosf(yaw) * cosf(pitch);
    front.y = sinf(pitch);
    front.z = sinf(yaw) * cosf(pitch);
    front = glm::normalize(front);

    glm::vec3 right = glm::normalize(glm::cross(front, worldUp));
    up = glm::normalize(glm::cross(right, front));
}
