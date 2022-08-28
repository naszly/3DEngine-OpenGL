
#include "engine.h"

#include "renderer/renderer_system.h"
#include "controller/camera_controller_system.h"
#include "services/services.h"
#include "services/i_camera.h"
#include "services/perspective_camera.h"

void Engine::start() {

    if (!Services::exist<ICamera>()) {
        Services::set<ICamera, PerspectiveCamera>(glm::vec3(0.0f, 0.0f, 1.0f),
                                                  glm::radians(-90.0f),
                                                  glm::radians(0.0f),
                                                  glm::radians(60.0f));
    }

    lastTime = std::chrono::high_resolution_clock::now();

    while (window.isRunning()) {
        auto now = std::chrono::high_resolution_clock::now();
        float deltaTime = std::chrono::duration_cast<std::chrono::duration<float>>(now - lastTime).count();

        window.update(deltaTime);

        lastTime = now;
    }
}

Engine::Engine() {
    window.init();
}
