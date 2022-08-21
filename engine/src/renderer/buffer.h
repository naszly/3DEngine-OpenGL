//
// Created by naszly on 8/21/22.
//

#ifndef ENGINE_SRC_RENDERER_BUFFER_H
#define ENGINE_SRC_RENDERER_BUFFER_H

#include <GL/glew.h>

class Buffer {
public:
    Buffer() = default;
    ~Buffer() = default;

    void init() {
        glCreateBuffers(1, &id);
    }

    [[nodiscard]] unsigned int getId() const {
        return id;
    }

    [[nodiscard]] GLsizei getSize() const {
        return bufferSize;
    }

    template<typename T>
    void bufferData(const std::vector<T> &data) {
        GLsizei newSize = data.size() * sizeof data[0];
        if (newSize > bufferSize) {
            glNamedBufferStorage(id, newSize, &data[0], GL_DYNAMIC_STORAGE_BIT);
            bufferSize = newSize;
        } else {
            glNamedBufferSubData(id, 0, newSize, &data[0]);
        }
    }

    template<typename T>
    void bufferData(const T *data, GLsizei n) {
        GLsizei newSize = n;
        if (newSize > bufferSize) {
            glNamedBufferStorage(id, newSize, data, GL_DYNAMIC_STORAGE_BIT);
            bufferSize = newSize;
        } else {
            glNamedBufferSubData(id, 0, newSize, data);
        }
    }

private:
    unsigned int id{0};
    GLsizei bufferSize{0};
};


#endif //ENGINE_SRC_RENDERER_BUFFER_H
