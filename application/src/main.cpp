
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

    auto entity1 = entityManager->buildEntity();
    entity1.addComponent<RenderComponent>();
    entity1.addComponent<ModelComponent>("resources/Sponza/sponza.obj");
    entity1.addComponent<TransformComponent>(glm::vec3(0.0f, 0.0f, 0.0f),
                                             glm::vec3(0.0f, 0.0f, 0.0f),
                                             glm::vec3(0.1f, 0.1f, 0.1f));

    auto entity3 = entityManager->buildEntity();
    entity3.addComponent<RenderComponent>();
    entity3.addComponent<ModelComponent>("resources/boxes.obj");
    entity3.addComponent<TransformComponent>(glm::vec3(0.0f, 4.0f, 0.0f),
                                             glm::vec3(0.0f, 0.0f, 0.0f),
                                             glm::vec3(4.0f, 4.0f, 4.0f));
/*
    auto entity2 = entityManager->buildEntity();
    entity2.addComponent<RenderComponent>();
    entity2.addComponent<ModelComponent>("resources/Sponza/sponza.obj");
    entity2.addComponent<TransformComponent>(glm::vec3(0.0f, 0.0f, 250.0f),
                                             glm::vec3(0.0f, 0.0f, 0.0f),
                                             glm::vec3(0.1f, 0.1f, 0.1f));
*/

    engine.getWindow().addLayer<RendererSystem, CameraControllerSystem>("3dScene");
    engine.getWindow().addLayer<GuiSystem>("gui");
    engine.start();

    return 0;
}
