//
// Created by naszly on 8/21/22.
//

#include "vertex_array_attrib.h"

VertexArrayAttrib::VertexArrayAttrib(int location, VertexType type, int count, bool normalized) :
        location(location), type(static_cast<int>(type)), typeSize(getSize(type)), numOfComponents(count), normalized(normalized) {}

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
    };
    return 0;
}