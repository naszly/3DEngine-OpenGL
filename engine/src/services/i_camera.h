//
// Created by naszly on 8/22/22.
//

#ifndef ENGINE_SRC_RENDERER_I_CAMERA_H
#define ENGINE_SRC_RENDERER_I_CAMERA_H

#include <glm/glm.hpp>

class ICamera {
public:
    [[nodiscard]] virtual glm::mat4 getViewMatrix() const = 0;

    [[nodiscard]] virtual glm::mat4 getProjectionMatrix() const = 0;

    [[nodiscard]] virtual glm::vec3 getPosition() const = 0;

    [[nodiscard]] virtual glm::vec3 getDirection() const = 0;

    virtual void setPosition(glm::vec3 position) = 0;

    virtual void setAspectRatio(float aspectRatio) = 0;

    virtual void rotate(float dx, float dy) = 0;

    virtual void move(float dx, float dy, float dz) = 0;

};


#endif //ENGINE_SRC_RENDERER_I_CAMERA_H
