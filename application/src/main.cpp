//
// Created by kornel on 8/9/22.
//

#include "engine.h"

int main() {
    Log::info("Hello, world!");
    Engine &engine = Engine::getInstance();

    engine.start();

    return 0;
}
