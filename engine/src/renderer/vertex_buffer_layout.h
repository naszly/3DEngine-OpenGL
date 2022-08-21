//
// Created by naszly on 8/21/22.
//

#ifndef ENGINE_SRC_RENDERER_VERTEX_BUFFER_LAYOUT_H
#define ENGINE_SRC_RENDERER_VERTEX_BUFFER_LAYOUT_H

#include <GL/glew.h>

enum VertexType {
    Byte = GL_BYTE,
    UnsignedByte = GL_UNSIGNED_BYTE,
    Short = GL_SHORT,
    UnsignedShort = GL_UNSIGNED_SHORT,
    Int = GL_INT,
    UnsignedInt = GL_UNSIGNED_INT,
    Double = GL_DOUBLE,
    Float = GL_FLOAT,
    HalfFloat = GL_HALF_FLOAT,
    Fixed = GL_FIXED
};

struct VertexBufferElement {
public:
    VertexBufferElement(int location, VertexType type, int count, bool normalized);

    int location;
    int type;
    int typeSize;
    int numOfComponents;
    bool normalized;
private:
    static constexpr int getSize(VertexType type);
};

class VertexBufferLayout {
public:
    VertexBufferLayout &push(int location, VertexType type, int count, bool normalized = false);

    void enable();

private:
    std::vector<VertexBufferElement> elements;
    int size{0};
};

#endif //ENGINE_SRC_RENDERER_VERTEX_BUFFER_LAYOUT_H
