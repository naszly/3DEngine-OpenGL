//
// Created by naszly on 8/21/22.
//

#ifndef ENGINE_SRC_ECS_COMPONENTS_H
#define ENGINE_SRC_ECS_COMPONENTS_H

#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>

#include "renderer/vertex_array.h"
#include "renderer/buffer.h"
#include "renderer/indirect_command_buffer.h"

struct TransformComponent {
    glm::vec3 position;
    glm::vec3 rotation;
    glm::vec3 scale;
};

struct RenderComponent {
    VertexArray vertexArray;
    Buffer posBuffer;
    Buffer normalBuffer;
    Buffer texCoordBuffer;
    Buffer indexBuffer;
    IndirectCommandBuffer indirectCommandBuffer;
};

struct ModelComponent {
    std::string path;
};

struct PerspectiveCameraComponent {
    glm::vec3 position;
    glm::vec3 front;
    glm::vec3 up;
    float fov;
    float nearPlane;
    float farPlane;
    float aspect;

    [[nodiscard]] glm::mat4 getViewMatrix() const {
        return glm::lookAt(position, position + front, up);
    }

    [[nodiscard]] glm::mat4 getProjectionMatrix() const {
        return glm::perspective(fov, aspect, nearPlane, farPlane);
    }

    void move(float dx, float dy, float dz) {
        glm::vec4 movement = glm::vec4(dx, dy, dz, 0) * getViewMatrix();
        position.x += movement.x;
        position.y += movement.y;
        position.z += movement.z;
    }

    void setRotation(float pitch, float yaw) {
        front.x = cosf(yaw) * cosf(pitch);
        front.y = sinf(pitch);
        front.z = sinf(yaw) * cosf(pitch);
        front = glm::normalize(front);
    }
};

#endif //ENGINE_SRC_ECS_COMPONENTS_H
