
#include "engine.h"

#include "renderer/renderer_system.h"


void Engine::start() {
    window.init();
    window.addLayer<RendererSystem>("test");
    while (window.isRunning()) {
        auto dt = getDeltaTime();
        window.update(dt);
    }
}