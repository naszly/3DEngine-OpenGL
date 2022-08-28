
#ifndef ENGINE_SRC_CORE_INPUT_H
#define ENGINE_SRC_CORE_INPUT_H

#include <GLFW/glfw3.h>
#include "key_codes.h"
#include "mouse_codes.h"

enum class CursorMode {
    Normal = GLFW_CURSOR_NORMAL,
    Hidden = GLFW_CURSOR_HIDDEN,
    Disabled = GLFW_CURSOR_DISABLED,
    Captured = GLFW_CURSOR_CAPTURED
};

enum class CursorShape {
    Arrow = GLFW_ARROW_CURSOR,
    IBeam = GLFW_IBEAM_CURSOR,
    Crosshair = GLFW_CROSSHAIR_CURSOR,
    Hand = GLFW_POINTING_HAND_CURSOR,
    ResizeEastWest = GLFW_RESIZE_EW_CURSOR,
    ResizeNorthSouth = GLFW_RESIZE_NS_CURSOR,
    ResizeNorthEastSouthWest = GLFW_RESIZE_NESW_CURSOR,
    ResizeNorthWestSouthEast = GLFW_RESIZE_NWSE_CURSOR,
    ResizeAll = GLFW_RESIZE_ALL_CURSOR,
    NotAllowed = GLFW_NOT_ALLOWED_CURSOR
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
        auto state = glfwGetKey(glfwWindow, static_cast<int>(keyCode));
        return state == GLFW_PRESS;
    }

    [[nodiscard]] bool isMouseButtonPressed(MouseCode mouseCode) const {
        auto state = glfwGetMouseButton(glfwWindow, static_cast<int>(mouseCode));
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

    void setCursorShape(CursorShape shape) {
        if (shape != cursorShape) {
            GLFWcursor *cursor = glfwCreateStandardCursor(static_cast<int>(shape));
            glfwSetCursor(glfwWindow, cursor);
            glfwDestroyCursor(glfwCursor);
            glfwCursor = cursor;
            cursorShape = shape;
        }
    }

private:
    GLFWwindow *glfwWindow{nullptr};
    GLFWcursor *glfwCursor{nullptr};
    CursorShape cursorShape{CursorShape::Arrow};
};

#endif //ENGINE_SRC_CORE_INPUT_H
