
#include "engine.h"

#include "renderer/renderer_system.h"

Engine::Engine() {
    window.init();
    window.addLayer<RendererSystem>("test");
}

Engine::~Engine() {

}

void Engine::start() {
    while (window.isRunning()) {
        auto dt = getDeltaTime();
        window.update(dt);
    }
}