//
// Created by naszly on 8/21/22.
//

#include "renderer_system.h"

RendererSystem::RendererSystem(Context &context, Input &input) : System(context, input) {
    shader.init("resources/vert.glsl", "resources/frag.glsl");

    va.init();
    va.bind();

    vb.init();
    vb.bind();

    eb.init();
    eb.bind();

    VertexBufferLayout layout;
    layout.push(0, Float, 3);
    layout.enable();

    float vertices[] = {
            -0.5f, -0.5f, 0.0f,
            0.5f, -0.5f, 0.0f,
            0.0f, 0.5f, 0.0f
    };

    vb.buffer(vertices, sizeof(vertices));

    eb.bind();

    unsigned int indices[] = {
            0, 1, 2
    };

    eb.buffer(indices, sizeof(indices));

    va.unbind();
    vb.unbind();
    eb.unbind();

    glDisable(GL_CULL_FACE);
}

RendererSystem::~RendererSystem() {

}

void RendererSystem::update(double deltaTime) {
    System::update(deltaTime);


}

void RendererSystem::render() {
    System::render();

    glClearColor(0.1f, 0.1f, 0.1f, 1.0f);
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

    shader.bind();

    va.bind();

    eb.bind();

    glDrawElements(GL_TRIANGLES, eb.getSize() / (GLsizei)sizeof(unsigned int), GL_UNSIGNED_INT, nullptr);

}
