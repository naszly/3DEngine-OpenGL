
#ifndef ENGINE_SRC_CORE_APPLICATION_EVENT_H
#define ENGINE_SRC_CORE_APPLICATION_EVENT_H

#include "event.h"

class WindowResizeEvent : public Event {
public:
    WindowResizeEvent(unsigned int width, unsigned int height) :
            Event(eventType), width(width), height(height) {}

    [[nodiscard]] unsigned int GetWidth() const { return width; }

    [[nodiscard]] unsigned int GetHeight() const { return height; }

    static const EventType eventType = EventType::WindowResize;

    [[nodiscard]] std::string toString() const override {
        return "WindowResizeEvent" + std::to_string(width) + "x" + std::to_string(height);
    }

private:
    unsigned int width, height;
};

class WindowCloseEvent : public Event {
public:
    WindowCloseEvent() :
            Event(eventType) {}

    static const EventType eventType = EventType::WindowClose;

    [[nodiscard]] std::string toString() const override {
        return "WindowCloseEvent";
    }
};

#endif //ENGINE_SRC_CORE_APPLICATION_EVENT_H
