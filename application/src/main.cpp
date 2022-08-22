
#include "engine.h"
#include "ecs/entity.h"
#include "ecs/components.h"

int main() {
    Log::info("Hello, world!");
    Engine &engine = Engine::getInstance();
    auto entityManager = engine.getEntityManager();

    auto entity1 = entityManager->buildEntity();
    entity1.addComponent<RenderComponent>();
    entity1.addComponent<TransformComponent>(glm::vec3(0.5f, 0.0f, 0.0f), glm::vec3(0.0f, 0.0f, 0.0f), glm::vec3(1.0f, 1.0f, 1.0f));

    auto entity2 = entityManager->buildEntity();
    entity2.addComponent<RenderComponent>();
    entity2.addComponent<TransformComponent>(glm::vec3(0.0f, 0.5f, 0.0f), glm::vec3(0.0f, glm::radians(45.0f), 0.0f), glm::vec3(1.0f, 1.5f, 1.0f));

    engine.start();

    return 0;
}
