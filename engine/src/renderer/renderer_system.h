//
// Created by naszly on 8/21/22.
//

#ifndef ENGINE_SRC_RENDERER_RENDERER_SYSTEM_H
#define ENGINE_SRC_RENDERER_RENDERER_SYSTEM_H

#include "../ecs/system.h"
#include "shader.h"
#include "vertex_array.h"
#include "vertex_buffer.h"
#include "vertex_buffer_layout.h"
#include "element_buffer.h"

class RendererSystem : public System {
public:
    RendererSystem(Context &context, Input &input);
    ~RendererSystem() override;
    void update(double deltaTime) override;
    void render() override;

private:
    Shader shader;
    VertexArray va;
    VertexBuffer vb;
    ElementBuffer eb;
};

#endif //ENGINE_SRC_RENDERER_RENDERER_SYSTEM_H
