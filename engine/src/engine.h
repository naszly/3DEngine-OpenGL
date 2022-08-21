
#ifndef ENGINE_SRC_ENGINE_H
#define ENGINE_SRC_ENGINE_H

#include "core/log.h"
#include "core/window.h"
#include "ecs/entity_manager.h"

class Engine {
public:
    ~Engine();

    Engine(Engine const &) = delete;

    void operator=(Engine const &) = delete;

    static Engine &getInstance() {
        static Engine instance = Engine();
        return instance;
    }

    void start();

private:
    Engine();

    Window window{1280, 720, "Engine"};
    EntityManager entityManager;

    static double getDeltaTime() {
        using clock = std::chrono::high_resolution_clock;
        static auto now = clock::now();

        auto lt = now;
        now = clock::now();

        auto elapsed = now - lt;
        return std::chrono::duration<double>(elapsed).count();
    }

};

#endif //ENGINE_SRC_ENGINE_H
