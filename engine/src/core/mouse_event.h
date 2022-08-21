#ifndef ENGINE_SRC_CORE_MOUSE_EVENT_H
#define ENGINE_SRC_CORE_MOUSE_EVENT_H

#include "event.h"
#include "mouse_codes.h"

class MouseButtonEvent : public Event {
public:
    [[nodiscard]] MouseCode getMouseButton() const { return button; }

protected:
    MouseButtonEvent(EventType type, const MouseCode button) :
            Event(type), button(button) {}

    MouseCode button;
};

class MouseButtonPressedEvent : public MouseButtonEvent {
public:
    explicit MouseButtonPressedEvent(const MouseCode button) :
            MouseButtonEvent(eventType, button) {}

    static const EventType eventType = EventType::MouseButtonPressed;

    [[nodiscard]] std::string toString() const override {
        return "MouseButtonPressedEvent: " + std::to_string(button);
    }
};

class MouseButtonReleasedEvent : public MouseButtonEvent {
public:
    explicit MouseButtonReleasedEvent(const MouseCode button) :
            MouseButtonEvent(eventType, button) {}

    static const EventType eventType = EventType::MouseButtonReleased;

    [[nodiscard]] std::string toString() const override {
        return "MouseButtonReleasedEvent: " + std::to_string(button);
    }
};

class MouseMovedEvent : public Event {
public:
    MouseMovedEvent(const float x, const float y) :
            Event(eventType), mouseX(x), mouseY(y) {}

    [[nodiscard]] float getX() const { return mouseX; }

    [[nodiscard]] float getY() const { return mouseY; }

    static const EventType eventType = EventType::MouseMoved;

    [[nodiscard]] std::string toString() const override {
        return "MouseMovedEvent: " + std::to_string(mouseX) + "x" + std::to_string(mouseY);
    }

private:
    float mouseX, mouseY;
};

class MouseScrolledEvent : public Event {
public:
    MouseScrolledEvent(const float xOffset, const float yOffset) :
            Event(eventType), xOffset(xOffset), yOffset(yOffset) {}

    [[nodiscard]] float getXOffset() const { return xOffset; }

    [[nodiscard]] float getYOffset() const { return yOffset; }

    static const EventType eventType = EventType::MouseScrolled;

    [[nodiscard]] std::string toString() const override {
        return "MouseScrolledEvent: " + std::to_string(xOffset) + " " + std::to_string(yOffset);
    }

private:
    float xOffset, yOffset;
};

#endif //ENGINE_SRC_CORE_MOUSE_EVENT_H
