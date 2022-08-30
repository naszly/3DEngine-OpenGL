//
// Created by naszly on 8/21/22.
//

#ifndef ENGINE_SRC_RENDERER_RENDERER_SYSTEM_H
#define ENGINE_SRC_RENDERER_RENDERER_SYSTEM_H

#include "../ecs/system.h"
#include "shader.h"
#include "vertex_array.h"
#include "buffer.h"
#include "sampler.h"

class RendererSystem : public System {
public:
    RendererSystem(Context &context, Input &input);

    ~RendererSystem() override;

    void render() override;

private:
    Shader shader;
    Entity player;
};

#endif //ENGINE_SRC_RENDERER_RENDERER_SYSTEM_H
