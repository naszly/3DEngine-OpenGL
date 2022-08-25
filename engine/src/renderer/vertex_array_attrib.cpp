//
// Created by naszly on 8/21/22.
//

#include "vertex_array_attrib.h"


VertexArrayAttrib::VertexArrayAttrib(int location, VertexType type, int count,
                                     VertexInternalType internalType, bool normalized) :
        location(location), type(static_cast<int>(type)), typeSize(getSize(type)),
        numOfComponents(count), internalType(internalType), normalized(normalized) {}

constexpr int VertexArrayAttrib::getSize(VertexType type) {
    switch (type) {
        case VertexType::Byte:
        case VertexType::UnsignedByte:
            return 1;
        case VertexType::Short:
        case VertexType::UnsignedShort:
        case VertexType::HalfFloat:
            return 2;
        case VertexType::Int:
        case VertexType::UnsignedInt:
        case VertexType::Float:
        case VertexType::Fixed:
            return 4;
        case VertexType::Double:
            return 8;
    }
    return 0;
}

void VertexArrayAttrib::setVertexArrayAttribFormat(GLuint id, int offset) const {
    glEnableVertexArrayAttrib(id, location);
    switch (internalType) {
        case VertexInternalType::Int:
            glVertexArrayAttribIFormat(id, location, numOfComponents, type, offset);
            break;
        case VertexInternalType::Float:
            glVertexArrayAttribFormat(id, location, numOfComponents, type, normalized, offset);
            break;
        case VertexInternalType::Double:
            glVertexArrayAttribLFormat(id, location, numOfComponents, type, offset);
            break;
    }
}
