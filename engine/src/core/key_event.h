
#ifndef ENGINE_SRC_CORE_KEY_EVENT_H
#define ENGINE_SRC_CORE_KEY_EVENT_H

#include "event.h"
#include "key_codes.h"

class KeyEvent : public Event {
public:
    [[nodiscard]] KeyCode getKeyCode() const { return keyCode; }

protected:
    KeyEvent(EventType type, const KeyCode keyCode) :
            Event(type), keyCode(keyCode) {}

    KeyCode keyCode;
};

class KeyPressedEvent : public KeyEvent {
public:
    explicit KeyPressedEvent(const KeyCode keyCode, bool repeat = false) :
            KeyEvent(eventType, keyCode), repeat(repeat) {}

    [[nodiscard]] bool isRepeat() const { return repeat; }

    static const EventType eventType = EventType::KeyPressed;

    [[nodiscard]] std::string toString() const override {
        return "KeyPressedEvent: " + std::string(magic_enum::enum_name(keyCode)) + " (" + std::to_string(repeat) + ")";
    }

private:
    bool repeat;
};

class KeyReleasedEvent : public KeyEvent {
public:
    explicit KeyReleasedEvent(const KeyCode keyCode) :
            KeyEvent(eventType, keyCode) {}

    static const EventType eventType = EventType::KeyReleased;

    [[nodiscard]] std::string toString() const override {
        return "KeyReleasedEvent: " + std::string(magic_enum::enum_name(keyCode));
    }
};

class KeyTypedEvent : public KeyEvent {
public:
    explicit KeyTypedEvent(const KeyCode keyCode) :
            KeyEvent(eventType, keyCode) {}

    static const EventType eventType = EventType::KeyTyped;

    [[nodiscard]] std::string toString() const override {
        return "KeyTypedEvent: " + std::string(magic_enum::enum_name(keyCode));
    }
};

#endif //ENGINE_SRC_CORE_KEY_EVENT_H
