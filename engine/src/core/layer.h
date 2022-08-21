
#ifndef ENGINE_SRC_CORE_LAYER_H
#define ENGINE_SRC_CORE_LAYER_H

#include <utility>

#include "event.h"
#include "ecs/system.h"

class Layer {
public:
    Layer(std::string name, std::vector<std::shared_ptr<System>> systems)
            : name(std::move(name)), systems(std::move(systems)) {}

    ~Layer() = default;

    void render() {
        for (auto &system: systems) system->render();
    }

    void update(double dt) {
        for (auto &system: systems) system->update(dt);
    }

    void onEvent(Event &event) {
        for (auto &system: systems) system->onEvent(event);
    }

private:
    std::string name;
    std::vector<std::shared_ptr<System>> systems;
};

#endif //ENGINE_SRC_CORE_LAYER_H
