
#ifndef ENGINE_SRC_ECS_ENTITY_MANAGER_H
#define ENGINE_SRC_ECS_ENTITY_MANAGER_H

#include "system.h"
#include <entt/entt.hpp>

class Entity;

class EntityManager {
    friend class Entity;

public:
    EntityManager() = default;

    ~EntityManager() = default;

    EntityManager(EntityManager const &) = delete;

    void operator=(EntityManager const &) = delete;

    [[nodiscard]] Entity buildEntity();

private:
    entt::registry registry;
};

#endif //ENGINE_SRC_ECS_ENTITY_MANAGER_H
