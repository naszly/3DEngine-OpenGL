//
// Created by naszly on 8/22/22.
//

#ifndef ENGINE_SRC_CONTROLLER_CAMERA_CONTROLLER_SYSTEM_H
#define ENGINE_SRC_CONTROLLER_CAMERA_CONTROLLER_SYSTEM_H

#include "ecs/system.h"

class CameraControllerSystem : public System {
public:
    CameraControllerSystem(Context &context, Input &input);

    ~CameraControllerSystem() override = default;

    void update(float deltaTime) override;

    void onEvent(Event &event) override;

private:
    float sensitivity = 0.03f;
    float speed = 30.0f;
};


#endif //ENGINE_SRC_CONTROLLER_CAMERA_CONTROLLER_SYSTEM_H
