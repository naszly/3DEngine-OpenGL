//
// Created by kornel on 8/9/22.
//

#include "engine.h"
#include "ecs/entity.h"
#include "ecs/components.h"

int main() {
    Log::info("Hello, world!");
    Engine &engine = Engine::getInstance();
    auto entityManager = engine.getEntityManager();

    auto entity = entityManager->buildEntity();

    entity.addComponent<RenderComponent>();

    engine.start();

    return 0;
}
