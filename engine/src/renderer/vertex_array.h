//
// Created by naszly on 8/21/22.
//

#ifndef ENGINE_SRC_RENDERER_VERTEX_ARRAY_H
#define ENGINE_SRC_RENDERER_VERTEX_ARRAY_H

#include <GL/glew.h>

class VertexArray {
public:
    VertexArray() = default;

    void init() {
        glGenVertexArrays(1, &id);
    }

    void bind() const {
        glBindVertexArray(id);
    }

    void unbind() const {
        glBindVertexArray(0);
    }

private:
    unsigned int id{0};
};

#endif //ENGINE_SRC_RENDERER_VERTEX_ARRAY_H
