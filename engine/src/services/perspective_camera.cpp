//
// Created by naszly on 8/22/22.
//

#include "perspective_camera.h"
#include <glm/gtc/matrix_transform.hpp>

PerspectiveCamera::PerspectiveCamera(glm::vec3 position, float yaw, float pitch, float fov)
        : pos(position),
          yaw(yaw), pitch(pitch),
          fov(fov) {
    update();
}

glm::mat4 PerspectiveCamera::getViewMatrix() const {
    return glm::lookAt(pos, pos + front, worldUp);
}

glm::mat4 PerspectiveCamera::getProjectionMatrix() const {
    return glm::perspective(fov, aspect, nearPlane, farPlane);
}

glm::vec3 PerspectiveCamera::getPosition() const {
    return pos;
}

glm::vec3 PerspectiveCamera::getDirection() const {
    return front;
}

void PerspectiveCamera::setPosition(glm::vec3 position) {
    pos = position;
}

void PerspectiveCamera::setAspectRatio(float aspectRatio) {
    aspect = aspectRatio;
}

void PerspectiveCamera::rotate(float dx, float dy) {
    yaw += dx;
    pitch += dy;

    pitch = glm::clamp(pitch, -glm::radians(89.9f), glm::radians(89.9f));

    update();
}

void PerspectiveCamera::move(float dx, float dy, float dz) {
    glm::vec4 movement = (glm::vec4(dx, dy, dz, 0) * getViewMatrix());
    pos.x += movement.x;
    pos.y += movement.y;
    pos.z += movement.z;
}

void PerspectiveCamera::update() {
    front.x = cosf(yaw) * cosf(pitch);
    front.y = sinf(pitch);
    front.z = sinf(yaw) * cosf(pitch);
    front = glm::normalize(front);
}
