//
// Created by naszly on 8/21/22.
//

#include "renderer_system.h"
#include "services/i_camera.h"

#include <glm/gtc/matrix_transform.hpp>

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

    float vertices[] = {
            -0.5f, -0.5f, 0.0f, 1.0f, 0.0f, 0.0f,
            0.5f, -0.5f, 0.0f, 0.0f, 1.0f, 0.0f,
            0.5f, 0.5f, 0.0f, 0.0f, 0.0f, 1.0f,
            -0.5f, 0.5f, 0.0f, 1.0f, 1.0f, 1.0f
    };

    unsigned int indices[] = {
            0, 1, 2,
            2, 3, 0
    };

    auto view = entityManager->getRegistry().view<RenderComponent>();

    for (auto entity: view) {
        auto [renderComp] = view.get(entity);
        renderComp.vertexBuffer.init();
        renderComp.vertexBuffer.bufferData(vertices, sizeof(vertices));
        renderComp.elementBuffer.init();
        renderComp.elementBuffer.bufferData(indices, sizeof(indices));
        renderComp.vertexArray.init();
        renderComp.vertexArray.bindVertexBuffer(renderComp.vertexBuffer, {
                VertexArrayAttrib(0, VertexType::Float, 3),
                VertexArrayAttrib(1, VertexType::Float, 3)
        });
        renderComp.vertexArray.bindElementBuffer(renderComp.elementBuffer);
    }

    glDisable(GL_CULL_FACE);
}

RendererSystem::~RendererSystem() {
    auto view = entityManager->getRegistry().view<RenderComponent>();

    for (auto entity: view) {
        auto [renderComp] = view.get(entity);
        renderComp.vertexArray.destroy();
        renderComp.vertexBuffer.destroy();
        renderComp.elementBuffer.destroy();
    }
}

void RendererSystem::render() {

    glClearColor(0.1f, 0.1f, 0.1f, 1.0f);
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

    shader.bind();

    auto &camera = entt::locator<ICamera>::value();

    int width, height;
    context.getSize(&width, &height);
    camera.setAspectRatio((float) width / (float) height);

    shader.setMat4("uProjection", camera.getProjectionMatrix());
    shader.setMat4("uView", camera.getViewMatrix());


    auto view = entityManager->getRegistry().view<RenderComponent, TransformComponent>();

    for (auto entity: view) {
        auto [renderComp, transform] = view.get(entity);
        glm::mat4 model{1.0f};
        model = glm::translate(model, transform.position);
        model = glm::scale(model, transform.scale);
        model = glm::rotate(model, transform.rotation.x, glm::vec3(1.0f, 0.0f, 0.0f));
        model = glm::rotate(model, transform.rotation.y, glm::vec3(0.0f, 1.0f, 0.0f));
        model = glm::rotate(model, transform.rotation.z, glm::vec3(0.0f, 0.0f, 1.0f));

        shader.setMat4("uModel", model);
        renderComp.vertexArray.drawElements(GL_TRIANGLES);
    }

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
