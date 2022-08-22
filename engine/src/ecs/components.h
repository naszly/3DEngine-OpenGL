//
// Created by naszly on 8/21/22.
//

#ifndef ENGINE_SRC_ECS_COMPONENTS_H
#define ENGINE_SRC_ECS_COMPONENTS_H

#include <glm/glm.hpp>

#include "../renderer/vertex_array.h"

struct TransformComponent {
    glm::vec3 position;
    glm::vec3 rotation;
    glm::vec3 scale;
};

struct RenderComponent {
    VertexArray vertexArray;
    Buffer vertexBuffer;
    Buffer elementBuffer;
};

#endif //ENGINE_SRC_ECS_COMPONENTS_H
