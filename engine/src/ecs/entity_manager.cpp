
#include "entity_manager.h"
#include "entity.h"

Entity EntityManager::buildEntity() {
    return {registry.create(), registry};
}

Entity EntityManager::getEntityByTag(entt::hashed_string tag) {
    auto view = registry.view<entt::hashed_string>();
    auto it = view.begin();
    entt::entity entity = entt::null;
    while (it != view.end()) {
        if (view.get<entt::hashed_string>(*it) == tag) {
            entity = *it;
            break;
        }
        ++it;
    }
    return Entity{entity, registry};
}
