//
// Created by naszly on 8/22/22.
//

#include "camera_controller_system.h"
#include "services/services.h"
#include "services/i_camera.h"
#include "core/mouse_event.h"

CameraControllerSystem::CameraControllerSystem(Context &context, Input &input)
        : System(context, input) {
    input.setCursorMode(CursorMode::Disabled);
}

void CameraControllerSystem::update(double deltaTime) {
    auto &camera = Services::get<ICamera>();
    double dx = 0.0f;
    double dy = 0.0f;
    double dz = 0.0f;

    if (input.isKeyPressed(KeyCode::W))
        dz -= deltaTime;

    if (input.isKeyPressed(KeyCode::S))
        dz += deltaTime;

    if (input.isKeyPressed(KeyCode::A))
        dx -= deltaTime;

    if (input.isKeyPressed(KeyCode::D))
        dx += deltaTime;

    if (input.isKeyPressed(KeyCode::LeftShift))
        dy -= deltaTime;

    if (input.isKeyPressed(KeyCode::Space))
        dy += deltaTime;

    camera.move(dx * speed, dy * speed, dz * speed);
}

void CameraControllerSystem::onEvent(Event &event) {

    EventDispatcher dispatcher(event);
    dispatcher.dispatch<MouseMovedEvent>([&](MouseMovedEvent &event) {
        auto &camera = Services::get<ICamera>();
        static float lastX = event.getX(), lastY = event.getY();
        float dx = event.getX() - lastX;
        float dy = event.getY() - lastY;
        lastX = event.getX();
        lastY = event.getY();
        camera.rotate(dx * sensitivity, -dy * sensitivity);
        return true;
    });

}
