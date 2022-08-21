//
// Created by naszly on 8/21/22.
//

#ifndef ENGINE_SRC_RENDERER_BUFFER_H
#define ENGINE_SRC_RENDERER_BUFFER_H

#include <GL/glew.h>

enum BufferUsage {
    streamDraw = GL_STREAM_DRAW,
    streamRead = GL_STREAM_READ,
    streamCopy = GL_STREAM_COPY,
    staticDraw = GL_STATIC_DRAW,
    staticRead = GL_STATIC_READ,
    staticCopy = GL_STATIC_COPY,
    dynamicDraw = GL_DYNAMIC_DRAW,
    dynamicRead = GL_DYNAMIC_READ,
    dynamicCopy = GL_DYNAMIC_COPY
};

enum BufferType {
    arrayBuffer = GL_ARRAY_BUFFER,
    elementArrayBuffer = GL_ELEMENT_ARRAY_BUFFER,
};

class Buffer {
public:
    Buffer() = delete;

    void init() {
        glGenBuffers(1, &id);
    }

    void bind() const {
        glBindBuffer(target, id);
    }

    void unbind() const {
        glBindBuffer(target, 0);
    }

    [[nodiscard]] GLsizei getSize() const {
        return bufferSize;
    }

protected:
    Buffer(BufferType target, BufferUsage usage) : target(target), usage(usage) {

    }

    template<typename T>
    void bufferData(const std::vector<T> &data) {
        bind();
        GLsizei newSize = data.size() * sizeof data[0];
        if (newSize > bufferSize) {
            glBufferData(target, newSize, &data[0], usage);
            bufferSize = newSize;
        } else
            glBufferSubData(target, 0, newSize, &data[0]);
    }

    template<typename T>
    void bufferData(const T *data, GLsizei n) {
        bind();
        GLsizei newSize = n;
        if (newSize > bufferSize) {
            glBufferData(target, newSize, data, usage);
            bufferSize = newSize;
        } else
            glBufferSubData(target, 0, newSize, data);
    }

private:
    unsigned int id{0};
    GLsizei bufferSize{0};
    BufferType target;
    BufferUsage usage;
};


#endif //ENGINE_SRC_RENDERER_BUFFER_H
