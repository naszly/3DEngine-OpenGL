
#include "engine.h"
#include "ecs/entity.h"
#include "ecs/components.h"
#include "renderer/renderer_system.h"
#include "controller/camera_controller_system.h"
#include "gui_system.h"

int main() {
    Log::info("Hello, world!");
    Engine &engine = Engine::getInstance();
    auto entityManager = engine.getEntityManager();

    auto player = entityManager->buildEntity();
    player.addTag("player");
    player.addComponent<PerspectiveCameraComponent>(
            glm::vec3(0.0f, 0.0f, 0.0f), // position
            glm::vec3(1.0f, 0.0f, 0.0f), // front
            glm::vec3(0.0f, 1.0f, 0.0f), // up
            glm::radians(45.0f), // fov
            0.1f, // near
            1000.0f // far
    );

    auto sponza = entityManager->buildEntity();
    sponza.addComponent<RenderComponent>();
    sponza.addComponent<ModelComponent>("resources/Sponza/sponza.obj");
    sponza.addComponent<TransformComponent>(glm::vec3(0.0f, 0.0f, 0.0f),
                                             glm::vec3(0.0f, 0.0f, 0.0f),
                                             glm::vec3(0.1f, 0.1f, 0.1f));


    engine.getWindow().addLayer<RendererSystem, CameraControllerSystem>("3dScene");
    engine.getWindow().addLayer<GuiSystem>("gui");
    engine.start();

    return 0;
}
