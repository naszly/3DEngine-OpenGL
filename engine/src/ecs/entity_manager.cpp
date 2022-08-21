
#include "entity_manager.h"
#include "entity.h"

Entity EntityManager::buildEntity() {
    return {registry.create(), registry};
}
