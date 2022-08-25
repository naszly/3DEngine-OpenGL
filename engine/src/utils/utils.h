//
// Created by naszly on 8/23/22.
//

#ifndef ENGINE_SRC_UTILS_UTILS_H
#define ENGINE_SRC_UTILS_UTILS_H

#include <functional>

inline void hashCombine(std::size_t& seed) { }

template <typename T, typename... Rest>
inline void hashCombine(std::size_t& seed, const T& v, Rest... rest) {
    seed ^= std::hash<T>{}(v) + 0x9e3779b9 + (seed << 6) + (seed >> 2);
    hashCombine(seed, rest...);
}

#endif //ENGINE_SRC_UTILS_UTILS_H
