
#ifndef ENGINE_SRC_CORE_WINDOW_H
#define ENGINE_SRC_CORE_WINDOW_H

#include <utility>

#include "context.h"
#include "event.h"
#include "input.h"
#include "key_event.h"
#include "mouse_event.h"
#include "application_event.h"
#include "layer.h"

class Window {
public:
    Window(int width, int height, const std::string &name);

    ~Window();

    void init();

    void update(double dt);

    template<typename... Systems>
    void addLayer(const std::string& name) {
        layers.emplace_back(
                name,
                std::vector<std::shared_ptr<System>>{std::make_shared<Systems>(context, input)...}
        );
    }

    [[nodiscard]] bool isRunning() const { return running; }

private:
    struct WindowData {
        WindowData(int width, int height, std::string name, EventCallbackFn eventCallback)
                : width(width), height(height), name(std::move(name)), eventCallback(std::move(eventCallback)) {}

        int width, height;
        std::string name;

        EventCallbackFn eventCallback;
    };

    WindowData windowData;

    Context context;
    Input input;

    bool running{true};

    GLFWwindow *glfwWindow{};

    std::vector<Layer> layers;

    void onEvent(Event &event);

    bool onWindowCloseEvent(WindowCloseEvent &event);

    static void glfwErrorCallback(int error, const char *description);
};

#endif //ENGINE_SRC_CORE_WINDOW_H
