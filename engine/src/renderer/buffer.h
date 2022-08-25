//
// Created by naszly on 8/21/22.
//

#ifndef ENGINE_SRC_RENDERER_BUFFER_H
#define ENGINE_SRC_RENDERER_BUFFER_H

#include <GL/glew.h>

enum class BufferUsage {
    StreamDraw = GL_STREAM_DRAW,
    StreamRead = GL_STREAM_READ,
    StreamCopy = GL_STREAM_COPY,
    StaticDraw = GL_STATIC_DRAW,
    StaticRead = GL_STATIC_READ,
    StaticCopy = GL_STATIC_COPY,
    DynamicDraw = GL_DYNAMIC_DRAW,
    DynamicRead = GL_DYNAMIC_READ,
    DynamicCopy = GL_DYNAMIC_COPY
};

class Buffer {
public:
    Buffer() = default;

    ~Buffer() = default;

    void init() {
        glCreateBuffers(1, &id);
    }

    void init(BufferUsage bufferUsage) {
        usage = bufferUsage;
        glCreateBuffers(1, &id);
    }

    void destroy() {
        glDeleteBuffers(1, &id);
    }

    [[nodiscard]] unsigned int getId() const {
        return id;
    }

    [[nodiscard]] GLsizeiptr getSize() const {
        return bufferSize;
    }

    template<typename T>
    void bufferData(const std::vector<T> &data) {
        GLsizeiptr newSize = data.size() * sizeof data[0];
        if (newSize > bufferSize) {
            glNamedBufferData(id, newSize, &data[0], static_cast<GLenum>(usage));
            bufferSize = newSize;
        } else {
            glNamedBufferSubData(id, 0, newSize, &data[0]);
        }
    }

    template<typename T>
    void bufferData(const T *data, GLsizeiptr n) {
        GLsizeiptr newSize = n;
        if (newSize > bufferSize) {
            glNamedBufferData(id, newSize, data, static_cast<GLenum>(usage));
            bufferSize = newSize;
        } else {
            glNamedBufferSubData(id, 0, newSize, data);
        }
    }

private:
    unsigned int id{0};
    GLsizeiptr bufferSize{0};
    BufferUsage usage{BufferUsage::StaticDraw};
};


#endif //ENGINE_SRC_RENDERER_BUFFER_H
