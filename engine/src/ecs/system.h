
#ifndef ENGINE_SRC_ECS_SYSTEM_H
#define ENGINE_SRC_ECS_SYSTEM_H

#include "core/context.h"
#include "core/input.h"
#include "core/event.h"
#include "ecs/entity_manager.h"
#include "ecs/components.h"

class System {

public:
    System(Context &context, Input &input);

    virtual ~System() = default;

    System(System const &) = delete;

    void operator=(System const &) = delete;

    virtual void render() {}// = 0;
    virtual void update(double dt) {}// = 0;
    virtual void onEvent(Event &event) {}// = 0;
protected:
    Context &context;
    Input &input;
    std::shared_ptr<EntityManager> entityManager;
};

#endif //ENGINE_SRC_ECS_SYSTEM_H
