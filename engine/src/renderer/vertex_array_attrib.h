//
// Created by naszly on 8/21/22.
//

#ifndef ENGINE_SRC_RENDERER_VERTEX_ARRAY_ATTRIB_H
#define ENGINE_SRC_RENDERER_VERTEX_ARRAY_ATTRIB_H

#include <GL/glew.h>

enum class VertexType {
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

struct VertexArrayAttrib {
public:
    VertexArrayAttrib(int location, VertexType type, int count, bool normalized = false);

    int location;
    int type;
    int typeSize;
    int numOfComponents;
    bool normalized;
private:
    static constexpr int getSize(VertexType type);
};

#endif //ENGINE_SRC_RENDERER_VERTEX_ARRAY_ATTRIB_H
