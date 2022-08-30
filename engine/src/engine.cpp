
#include "engine.h"

void Engine::start() {

    lastTime = std::chrono::high_resolution_clock::now();

    while (window.isRunning()) {
        auto now = std::chrono::high_resolution_clock::now();
        float deltaTime = std::chrono::duration_cast<std::chrono::duration<float>>(now - lastTime).count();

        window.update(deltaTime);

        lastTime = now;
    }
}

Engine::Engine() {
    window.init();
}
