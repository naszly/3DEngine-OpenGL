
#ifndef ENGINE_SRC_ECS_SYSTEM_H
#define ENGINE_SRC_ECS_SYSTEM_H

#include "core/context.h"
#include "core/input.h"
#include "core/event.h"

class System {

public:
    constexpr System(Context& context, Input& input) : context(context), input(input) {}
    virtual ~System() = default;
    virtual void render() {}// = 0;
    virtual void update(double dt) {}// = 0;
    virtual void onEvent(Event &event) {}// = 0;
protected:
    Context& context;
    Input& input;
};

#endif //ENGINE_SRC_ECS_SYSTEM_H
