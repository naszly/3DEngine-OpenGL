
#ifndef ENGINE_SRC_ECS_ENTITY_H
#define ENGINE_SRC_ECS_ENTITY_H

#include "entity_manager.h"

class Entity {
    friend class EntityManager;

public:
    Entity() = delete;

    template<typename T, typename... Args>
    void addComponent(Args &&... args) {
        registry.emplace<T>(id, std::forward<Args>(args)...);
    }

private:
    Entity(entt::entity entity, entt::registry &registry) : id(entity), registry(registry) {}

    entt::entity id;
    entt::registry &registry;
};

#endif //ENGINE_SRC_ECS_ENTITY_H
