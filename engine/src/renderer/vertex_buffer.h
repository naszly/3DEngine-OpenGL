//
// Created by naszly on 8/21/22.
//

#ifndef ENGINE_SRC_RENDERER_VERTEX_BUFFER_H
#define ENGINE_SRC_RENDERER_VERTEX_BUFFER_H

#include "buffer.h"

class VertexBuffer : public Buffer {
public:
    VertexBuffer() : Buffer(BufferType::arrayBuffer, BufferUsage::staticDraw) {

    }

    explicit VertexBuffer(BufferUsage usage) : Buffer(BufferType::arrayBuffer, usage) {

    }

    void buffer(const std::vector<float> &vertices) {
        Buffer::bufferData<float>(vertices);
    }

    void buffer(const float *vertices, GLsizeiptr n) {
        Buffer::bufferData<float>(vertices, n);
    }

};

#endif //ENGINE_SRC_RENDERER_VERTEX_BUFFER_H
