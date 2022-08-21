//
// Created by naszly on 8/21/22.
//

#include "vertex_array_attrib.h"

VertexArrayAttrib::VertexArrayAttrib(int location, VertexType type, int count, bool normalized) :
        location(location), type(type), typeSize(getSize(type)), numOfComponents(count), normalized(normalized) {}

constexpr int VertexArrayAttrib::getSize(VertexType type) {
    switch (type) {
        case Byte:
        case UnsignedByte:
            return 1;
        case Short:
        case UnsignedShort:
        case HalfFloat:
            return 2;
        case Int:
        case UnsignedInt:
        case Float:
        case Fixed:
            return 4;
        case Double:
            return 8;
    };
    return 0;
}