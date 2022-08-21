//
// Created by naszly on 8/21/22.
//

#ifndef ENGINE_SRC_RENDERER_ELEMENT_BUFFER_H
#define ENGINE_SRC_RENDERER_ELEMENT_BUFFER_H

#include "buffer.h"

class ElementBuffer : public Buffer {
public:
    ElementBuffer() : Buffer(BufferType::elementArrayBuffer, BufferUsage::staticDraw) { }

    explicit ElementBuffer(BufferUsage usage) : Buffer(BufferType::elementArrayBuffer, usage) { }

    void buffer(const std::vector<unsigned int> &indices) {
        Buffer::bufferData<unsigned int>(indices);
    }

    void buffer(const unsigned int *indices, GLsizeiptr n) {
        Buffer::bufferData<unsigned int>(indices, n);
    }
};

#endif //ENGINE_SRC_RENDERER_ELEMENT_BUFFER_H
