
#ifndef ENGINE_SRC_CORE_EVENT_H
#define ENGINE_SRC_CORE_EVENT_H

enum class EventType {
    None = 0,
    WindowClose, WindowResize,
    KeyPressed, KeyReleased, KeyTyped,
    MouseButtonPressed, MouseButtonReleased, MouseMoved, MouseScrolled
};

class EventDispatcher;

class Event {
public:
    friend class EventDispatcher;

    virtual ~Event() = default;

    bool Handled = false;

    [[nodiscard]] EventType getEventType() const { return type; }

    [[nodiscard]] virtual std::string toString() const {
        return type == EventType::None ? "None" : "Unknown";
    }

protected:
    explicit Event(EventType type) : type(type) {}

private:
    EventType type;
};

using EventCallbackFn = std::function<void(Event &)>;

class EventDispatcher {
public:
    explicit EventDispatcher(Event &event)
            : event(event) {}

    // F will be deduced by the compiler
    template<typename T, typename F>
    bool dispatch(const F &func) {
        if (event.getEventType() == T::eventType) {
            event.Handled |= func(static_cast<T &>(event));
            return true;
        }
        return false;
    }

private:
    Event &event;
};

#endif //ENGINE_SRC_CORE_EVENT_H
