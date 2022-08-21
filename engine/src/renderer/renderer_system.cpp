//
// Created by naszly on 8/21/22.
//

#include "renderer_system.h"

void GLAPIENTRY MessageCallback(GLenum source,
                                GLenum type,
                                GLuint id,
                                GLenum severity,
                                GLsizei length,
                                const GLchar *message,
                                const void *userParam);

RendererSystem::RendererSystem(Context &context, Input &input) : System(context, input) {
    glEnable(GL_DEBUG_OUTPUT);
    glDebugMessageCallback(MessageCallback, nullptr);

    shader.init("resources/vert.glsl", "resources/frag.glsl");

    vb.init();
    float vertices[] = {
            -0.5f, -0.5f, 0.0f,
            0.5f, -0.5f, 0.0f,
            0.5f, 0.5f, 0.0f,
            -0.5f, 0.5f, 0.0f
    };
    vb.bufferData(vertices, sizeof(vertices));

    eb.init();
    unsigned int indices[] = {
            0, 1, 2,
            2, 3, 0
    };
    eb.bufferData(indices, sizeof(indices));

    va.init();
    va.bindVertexBuffer(vb, {VertexArrayAttrib(0, VertexType::Float, 3)});
    va.bindElementBuffer(eb);

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

    glDrawElements(GL_TRIANGLES, eb.getSize() / sizeof(unsigned int), GL_UNSIGNED_INT, nullptr);

}

void GLAPIENTRY MessageCallback(GLenum source,
                                GLenum type,
                                GLuint id,
                                GLenum severity,
                                GLsizei length,
                                const GLchar *message,
                                const void *userParam) {
    if (type == GL_DEBUG_TYPE_ERROR)
        LogOpenGL::error("{0} {1}", id, message);
    else
        LogOpenGL::warning("{0} {1}", id, message);
}
