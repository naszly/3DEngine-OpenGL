//
// Created by naszly on 8/22/22.
//

#ifndef ENGINE_SRC_SERVICES_SERVICES_H
#define ENGINE_SRC_SERVICES_SERVICES_H

#include "entt/entt.hpp"

class Services {
public:
    template<typename I, typename T, typename... Args>
    static void set(Args &&... args) {
        entt::locator<I>::template emplace<T>(args...);
    }

    template<typename I>
    static I &get() {
        return entt::locator<I>::value();
    }

    template<typename I>
    static bool exist() {
        return entt::locator<I>::has_value();
    }
};


#endif //ENGINE_SRC_SERVICES_SERVICES_H
