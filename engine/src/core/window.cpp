
#include "window.h"
#include "log.h"

Window::Window(int width, int height, const std::string &name)
        : windowData(width, height, name, [this](Event &event) { onEvent(event); }) {}

Window::~Window() {
    glfwDestroyWindow(glfwWindow);
}

void Window::init() {
    glfwSetErrorCallback(glfwErrorCallback);

    if (!glfwInit()) {
        LogCore::critical("Failed to initialize GLFW");
        throw std::runtime_error("Failed to initialize GLFW");
    }

    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 4);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 5);
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
    glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE);

    glfwWindow = glfwCreateWindow(windowData.width, windowData.height, windowData.name.c_str(), nullptr, nullptr);
    if (!glfwWindow) {
        LogCore::critical("Failed to create GLFW window");
        glfwTerminate();
        throw std::runtime_error("Failed to create GLFW window");
    }

    context.init(glfwWindow);
    input.init(glfwWindow);

    // set pointer for callbacks
    glfwSetWindowUserPointer(glfwWindow, &windowData);

    // disable mouse pointer
    //glfwSetInputMode(window, GLFW_CURSOR, GLFW_CURSOR_DISABLED);

    // vsync off
    //glfwSwapInterval( 0 );

    glfwSetWindowSizeCallback(glfwWindow, [](GLFWwindow *window, int width, int height) {
        auto data = *reinterpret_cast<WindowData *>(glfwGetWindowUserPointer(window));
        data.width = width;
        data.height = height;

        WindowResizeEvent event(width, height);
        data.eventCallback(event);
    });

    glfwSetWindowCloseCallback(glfwWindow, [](GLFWwindow *window) {
        auto data = *reinterpret_cast<WindowData *>(glfwGetWindowUserPointer(window));
        WindowCloseEvent event;
        data.eventCallback(event);
    });

    glfwSetKeyCallback(glfwWindow, [](GLFWwindow *window, int key, int scancode, int action, int mods) {
        auto data = *reinterpret_cast<WindowData *>(glfwGetWindowUserPointer(window));

        switch (action) {
            case GLFW_PRESS: {
                KeyPressedEvent event(static_cast<const KeyCode>(key), false);
                data.eventCallback(event);
                break;
            }
            case GLFW_RELEASE: {
                KeyReleasedEvent event(static_cast<const KeyCode>(key));
                data.eventCallback(event);
                break;
            }
            case GLFW_REPEAT: {
                KeyPressedEvent event(static_cast<const KeyCode>(key), true);
                data.eventCallback(event);
                break;
            }
        }
    });

    glfwSetCharCallback(glfwWindow, [](GLFWwindow *window, unsigned int keycode) {
        auto data = *reinterpret_cast<WindowData *>(glfwGetWindowUserPointer(window));

        KeyTypedEvent event(static_cast<const KeyCode>(keycode));
        data.eventCallback(event);
    });

    glfwSetMouseButtonCallback(glfwWindow, [](GLFWwindow *window, int button, int action, int mods) {
        auto data = *reinterpret_cast<WindowData *>(glfwGetWindowUserPointer(window));

        switch (action) {
            case GLFW_PRESS: {
                MouseButtonPressedEvent event(static_cast<const MouseCode>(button));
                data.eventCallback(event);
                break;
            }
            case GLFW_RELEASE: {
                MouseButtonReleasedEvent event(static_cast<const MouseCode>(button));
                data.eventCallback(event);
                break;
            }
        }
    });

    glfwSetScrollCallback(glfwWindow, [](GLFWwindow *window, double xOffset, double yOffset) {
        auto data = *reinterpret_cast<WindowData *>(glfwGetWindowUserPointer(window));

        MouseScrolledEvent event((float) xOffset, (float) yOffset);
        data.eventCallback(event);
    });

    glfwSetCursorPosCallback(glfwWindow, [](GLFWwindow *window, double xPos, double yPos) {
        auto data = *reinterpret_cast<WindowData *>(glfwGetWindowUserPointer(window));

        MouseMovedEvent event((float) xPos, (float) yPos);
        data.eventCallback(event);
    });
}

void Window::update(float dt) {
    glfwPollEvents();

    for (auto &layer: layers) {
        layer.update(dt);
    }

    for (auto &layer: layers) {
        layer.render();
    }

    context.swapBuffers();
}

void Window::onEvent(Event &event) {
    LogCore::info("Event: {}", event.toString());
    EventDispatcher dispatcher(event);
    if (dispatcher.dispatch<WindowCloseEvent>([this](WindowCloseEvent &event) { return onWindowCloseEvent(event); }))
        return;

    for (auto &layer: layers) {
        layer.onEvent(event);
        if (event.handled) return;
    }
}

bool Window::onWindowCloseEvent(WindowCloseEvent &event) {
    running = false;
    return true;
}

void Window::glfwErrorCallback(int error, const char *description) {
    LogCore::error("GLFW error {}: {}", error, description);
}
