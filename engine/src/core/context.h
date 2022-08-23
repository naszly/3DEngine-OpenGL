
#ifndef ENGINE_SRC_CORE_CONTEXT_H
#define ENGINE_SRC_CORE_CONTEXT_H

#include <GL/glew.h>
#include <GLFW/glfw3.h>

#include "log.h"

class Context {
public:
    Context() = default;

    ~Context() = default;

    Context(Context const &) = delete;

    void operator=(Context const &) = delete;

    [[nodiscard]] std::pair<int, int> getSize() const {
        int width{0}, height{0};
        glfwGetFramebufferSize(glfwWindow, &width, &height);
        return {width, height};
    }

    void getSize(int *width, int *height) const {
        glfwGetFramebufferSize(glfwWindow, width, height);
    }

    void init(GLFWwindow *window) {
        glfwWindow = window;
        glfwMakeContextCurrent(glfwWindow);

        glewExperimental = GL_TRUE;

        auto code = glewInit();
        if (code != GLEW_OK) {
            const char *error = (const char *) glewGetErrorString(code);
            LogCore::critical("Failed to initialize GLEW: {}", error);
            throw std::runtime_error("Failed to initialize GLEW");
        }
    }

    void swapBuffers() {
        int width{0}, height{0};
        glfwSwapBuffers(glfwWindow);
        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
        glfwGetFramebufferSize(glfwWindow, &width, &height);
        glViewport(0, 0, width, height);
    }

private:
    GLFWwindow *glfwWindow{nullptr};
};

#endif //ENGINE_SRC_CORE_CONTEXT_H
