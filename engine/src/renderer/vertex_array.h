//
// Created by naszly on 8/21/22.
//

#ifndef ENGINE_SRC_RENDERER_VERTEX_ARRAY_H
#define ENGINE_SRC_RENDERER_VERTEX_ARRAY_H

#include <GL/glew.h>
#include "vertex_array_attrib.h"
#include "buffer.h"

class VertexArray {
public:
    VertexArray() = default;

    ~VertexArray() = default;

    void init() {
        glCreateVertexArrays(1, &id);
    }

    void destroy() {
        glDeleteVertexArrays(1, &id);
    }

    void bind() {
        glBindVertexArray(id);
    }

    void bindVertexBuffer(Buffer &vb, std::initializer_list<VertexArrayAttrib> attributes) {
        int offset = 0;
        for (auto &attrib: attributes) {
            glEnableVertexArrayAttrib(id, attrib.location);
            glVertexArrayAttribFormat(id,
                                      attrib.location,
                                      attrib.numOfComponents,
                                      attrib.type,
                                      attrib.normalized,
                                      offset);
            offset += attrib.typeSize * attrib.numOfComponents;
        }

        glVertexArrayVertexBuffer(id, bindings, vb.getId(), 0, offset);

        for (auto &attrib: attributes) {
            glVertexArrayAttribBinding(id, attrib.location, bindings);
        }

        ++bindings;
    }

    void bindElementBuffer(Buffer &eb) {
        glVertexArrayElementBuffer(id, eb.getId());
    }

private:
    unsigned int id{0};
    unsigned int bindings{0};
    GLsizei elementsCount{0};
};

#endif //ENGINE_SRC_RENDERER_VERTEX_ARRAY_H
