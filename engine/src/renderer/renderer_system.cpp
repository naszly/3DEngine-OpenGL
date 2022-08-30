//
// Created by naszly on 8/21/22.
//

#include "renderer_system.h"
#include "model_loader.h"

#include <glm/gtc/matrix_transform.hpp>

void GLAPIENTRY messageCallback(GLenum source,
                                GLenum type,
                                GLuint id,
                                GLenum severity,
                                GLsizei length,
                                const GLchar *message,
                                const void *userParam);

RendererSystem::RendererSystem(Context &context, Input &input)
        : System(context, input), player(entityManager->getEntityByTag("player")) {
    glEnable(GL_DEBUG_OUTPUT);
    glDebugMessageCallback(messageCallback, nullptr);

    shader.init("resources/vert.glsl", "resources/frag.glsl");

    auto view = entityManager->getRegistry().view<RenderComponent, ModelComponent>();

    for (auto entity: view) {
        auto [render, model] = view.get<RenderComponent, ModelComponent>(entity);

        render = ModelLoader::getRenderComponent(model);
    }

    shader.setBuffer("uMaterialArray", ModelLoader::getMaterialBuffer(), 0);

    glEnable(GL_DEPTH_TEST);
    glEnable(GL_CULL_FACE);
    glCullFace(GL_BACK);
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

    auto &camera = player.getComponent<PerspectiveCameraComponent>();

    int width, height;
    context.getSize(&width, &height);
    camera.aspect = (float) width / (float) height;

    shader.setMat4("uProjection", camera.getProjectionMatrix());
    shader.setMat4("uView", camera.getViewMatrix());

    auto view = entityManager->getRegistry().view<RenderComponent, TransformComponent>();
    for (auto entity: view) {
        auto [mesh, transform] = view.get(entity);
        glm::mat4 model{1.0f};
        model = glm::translate(model, transform.position);
        model = glm::scale(model, transform.scale);
        model = glm::rotate(model, transform.rotation.x, glm::vec3(1.0f, 0.0f, 0.0f));
        model = glm::rotate(model, transform.rotation.y, glm::vec3(0.0f, 1.0f, 0.0f));
        model = glm::rotate(model, transform.rotation.z, glm::vec3(0.0f, 0.0f, 1.0f));

        shader.setMat4("uModel", model);

        mesh.vertexArray.bind();
        mesh.indirectCommandBuffer.draw();
    }


}

void GLAPIENTRY messageCallback(GLenum source,
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
