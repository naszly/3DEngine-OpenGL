
#ifndef ENGINE_SRC_CORE_INPUT_H
#define ENGINE_SRC_CORE_INPUT_H

#include <GLFW/glfw3.h>
#include "key_codes.h"
#include "mouse_codes.h"

enum class CursorMode {
    Normal = GLFW_CURSOR_NORMAL,
    Hidden = GLFW_CURSOR_HIDDEN,
    Disabled = GLFW_CURSOR_DISABLED
};

class Input {
public:
    Input() = default;

    ~Input() = default;

    Input(Input const &) = delete;

    void operator=(Input const &) = delete;

    void init(GLFWwindow *window) {
        glfwWindow = window;
    }

    [[nodiscard]] bool isKeyPressed(KeyCode keyCode) const {
        auto state = glfwGetKey(glfwWindow, keyCode);
        return state == GLFW_PRESS;
    }

    [[nodiscard]] bool isMouseButtonPressed(MouseCode mouseCode) const {
        auto state = glfwGetMouseButton(glfwWindow, mouseCode);
        return state == GLFW_PRESS;
    }

    [[nodiscard]] inline bool isMouseLeftButtonPressed() const {
        return isMouseButtonPressed(MouseCode::ButtonLeft);
    }

    [[nodiscard]] inline bool isMouseMiddleButtonPressed() const {
        return isMouseButtonPressed(MouseCode::ButtonMiddle);
    }

    [[nodiscard]] inline bool isMouseRightButtonPressed() const {
        return isMouseButtonPressed(MouseCode::ButtonRight);
    }

    [[nodiscard]] std::pair<float, float> getCursorPosition() const {
        double x, y;
        glfwGetCursorPos(glfwWindow, &x, &y);
        return {x, y};
    }

    void setCursorMode(CursorMode mode) {
        glfwSetInputMode(glfwWindow, GLFW_CURSOR, static_cast<int>(mode));
    }

private:
    GLFWwindow *glfwWindow{nullptr};
};

#endif //ENGINE_SRC_CORE_INPUT_H
