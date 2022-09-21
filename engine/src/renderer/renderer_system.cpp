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
        // measure time
        auto start = std::chrono::high_resolution_clock::now();
        render = ModelLoader::getRenderComponent(model);
        auto end = std::chrono::high_resolution_clock::now();
        auto elapsed = std::chrono::duration_cast<std::chrono::milliseconds>(end - start).count();
        LogCore::info("Loaded model: {} vertices: {} indices: {} in {} ms",
                      model.path, render.posBuffer.getSize() / sizeof(float) / 3,
                      render.indexBuffer.getSize() / sizeof(uint32_t),
                      elapsed);
    }

    shader.bind();

    shader.setBuffer("uMaterialArray", ModelLoader::getMaterialBuffer(), 0);

    shader.setVec3("uDirectionalLight.color", glm::vec3(1.0f, 1.0f, 1.0f));
    shader.setVec3("uDirectionalLight.direction", glm::vec3(0.0f, 1.0f, 0.0f));
    shader.setFloat("uDirectionalLight.ambientStrength", 0.1f);
    shader.setFloat("uDirectionalLight.diffuseStrength", 0.8f);


    glEnable(GL_DEPTH_TEST);
    glEnable(GL_CULL_FACE);
    glCullFace(GL_BACK);
}

RendererSystem::~RendererSystem() {
    auto view = entityManager->getRegistry().view<RenderComponent>();

    for (auto entity: view) {
        auto [renderComp] = view.get(entity);
        renderComp.vertexArray.destroy();
        renderComp.posBuffer.destroy();
        renderComp.normalBuffer.destroy();
        renderComp.texCoordBuffer.destroy();
        renderComp.indexBuffer.destroy();
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
    shader.setVec3("uCameraPosition", camera.position);

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
