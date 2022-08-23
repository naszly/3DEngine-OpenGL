//
// Created by naszly on 8/22/22.
//

#ifndef ENGINE_SRC_SERVICES_PERSPECTIVE_CAMERA_H
#define ENGINE_SRC_SERVICES_PERSPECTIVE_CAMERA_H

#include "i_camera.h"

class PerspectiveCamera : public ICamera {
public:
    PerspectiveCamera(glm::vec3 position, float yaw, float pitch, float fov);

    [[nodiscard]] glm::mat4 getViewMatrix() const override;

    [[nodiscard]] glm::mat4 getProjectionMatrix() const override;

    [[nodiscard]] glm::vec3 getPosition() const override;

    [[nodiscard]] glm::vec3 getDirection() const override;

    void setPosition(glm::vec3 position) override;

    void setAspectRatio(float aspectRatio) override;

    void rotate(float dx, float dy) override;

    void move(float dx, float dy, float dz) override;

private:

    glm::vec3 pos;
    glm::vec3 front{};
    glm::vec3 worldUp{0, 1, 0};

    float fov;

    float yaw;
    float pitch;

    float nearPlane = 0.1f, farPlane = 1000.0f;
    float aspect{1.0f};

    void update();
};

#endif //ENGINE_SRC_SERVICES_PERSPECTIVE_CAMERA_H
