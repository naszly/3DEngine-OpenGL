//
// Created by naszly on 8/22/22.
//

#include "camera_controller_system.h"
#include "services/services.h"
#include "services/i_camera.h"
#include "core/mouse_event.h"
#include "core/key_event.h"

CameraControllerSystem::CameraControllerSystem(Context &context, Input &input)
        : System(context, input) {
}

void CameraControllerSystem::update(float deltaTime) {
    auto &camera = Services::get<ICamera>();
    camera.move(dx * deltaTime * speed, dy * deltaTime * speed, dz * deltaTime * speed);
}

void CameraControllerSystem::onEvent(Event &event) {
    EventDispatcher dispatcher(event);

    static bool firstMouse = true;
    static bool cameraControl = false;

    dispatcher.dispatch<KeyPressedEvent>([&](KeyPressedEvent &event) {
        if (event.getKeyCode() == KeyCode::LeftAlt) {
            input.setCursorMode(CursorMode::Disabled);
            firstMouse = true;
            cameraControl = true;
            return true;
        }
        if (event.getKeyCode() == KeyCode::W && !event.isRepeat()) {
            dz -= 1.0f;
            return true;
        }
        if (event.getKeyCode() == KeyCode::S && !event.isRepeat()) {
            dz += 1.0f;
            return true;
        }
        if (event.getKeyCode() == KeyCode::A && !event.isRepeat()) {
            dx -= 1.0f;
            return true;
        }
        if (event.getKeyCode() == KeyCode::D && !event.isRepeat()) {
            dx += 1.0f;
            return true;
        }
        if (event.getKeyCode() == KeyCode::LeftShift && !event.isRepeat()) {
            dy -= 1.0f;
            return true;
        }
        if (event.getKeyCode() == KeyCode::Space && !event.isRepeat()) {
            dy += 1.0f;
            return true;
        }
        return false;
    });

    dispatcher.dispatch<KeyReleasedEvent>([&](KeyReleasedEvent &event) {
        if (event.getKeyCode() == KeyCode::LeftAlt) {
            input.setCursorMode(CursorMode::Normal);
            cameraControl = false;
            return true;
        }
        if (event.getKeyCode() == KeyCode::W) {
            dz += 1.0f;
            return true;
        }
        if (event.getKeyCode() == KeyCode::S) {
            dz -= 1.0f;
            return true;
        }
        if (event.getKeyCode() == KeyCode::A) {
            dx += 1.0f;
            return true;
        }
        if (event.getKeyCode() == KeyCode::D) {
            dx -= 1.0f;
            return true;
        }
        if (event.getKeyCode() == KeyCode::LeftShift) {
            dy += 1.0f;
            return true;
        }
        if (event.getKeyCode() == KeyCode::Space) {
            dy -= 1.0f;
            return true;
        }
        return false;
    });

    dispatcher.dispatch<MouseButtonPressedEvent>([&](MouseButtonPressedEvent &event) {
        if (event.getMouseButton() == MouseCode::ButtonLeft) {
            input.setCursorMode(CursorMode::Disabled);
            firstMouse = true;
            cameraControl = true;
            return true;
        }
        return false;
    });

    dispatcher.dispatch<MouseButtonReleasedEvent>([&](MouseButtonReleasedEvent &event) {
        if (event.getMouseButton() == MouseCode::ButtonLeft) {
            input.setCursorMode(CursorMode::Normal);
            cameraControl = false;
            return true;
        }
        return false;
    });

    if (cameraControl) {
        dispatcher.dispatch<MouseMovedEvent>([&](MouseMovedEvent &event) {
            auto &camera = Services::get<ICamera>();
            static float lastX = event.getX(), lastY = event.getY();
            float mdx = event.getX() - lastX;
            float mdy = event.getY() - lastY;
            lastX = event.getX();
            lastY = event.getY();
            if (firstMouse) {
                firstMouse = false;
            } else {
                camera.rotate(mdx * sensitivity, -mdy * sensitivity);
            }
            return true;
        });
    }

}
