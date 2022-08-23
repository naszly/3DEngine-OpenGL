
#ifndef ENGINE_SRC_ENGINE_H
#define ENGINE_SRC_ENGINE_H

#include "core/log.h"
#include "core/window.h"
#include "ecs/entity_manager.h"

class Engine {
public:
    ~Engine() = default;

    Engine(Engine const &) = delete;

    void operator=(Engine const &) = delete;

    static Engine &getInstance() {
        static Engine instance;
        return instance;
    }

    std::shared_ptr<EntityManager> getEntityManager() {
        return entityManager;
    }

    void start();

private:
    Engine() = default;

    Window window{1280, 720, "Engine"};
    std::shared_ptr<EntityManager> entityManager{std::make_shared<EntityManager>()};

    std::chrono::high_resolution_clock timer;
    std::chrono::time_point<std::chrono::high_resolution_clock> lastTime;

};

#endif //ENGINE_SRC_ENGINE_H
