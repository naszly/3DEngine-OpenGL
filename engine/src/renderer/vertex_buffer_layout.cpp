//
// Created by naszly on 8/21/22.
//

#include "vertex_buffer_layout.h"
#include "../core/log.h"

VertexBufferElement::VertexBufferElement(int location, VertexType type, int count, bool normalized) :
        location(location), type(type), typeSize(getSize(type)), numOfComponents(count), normalized(normalized) {}

constexpr int VertexBufferElement::getSize(VertexType type) {
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

VertexBufferLayout &VertexBufferLayout::push(int location, VertexType type, int count, bool normalized) {
    bool elementExists = std::any_of(
            elements.begin(),
            elements.end(),
            [&](const VertexBufferElement &element) {
                return element.location == location;
            });

    if (elementExists) {
        LogOpenGL::error("Vertex buffer layout at location {0} already in bind", location);
    } else {
        VertexBufferElement element(location, type, count, normalized);
        elements.push_back(element);
        size += element.numOfComponents * element.typeSize;
    }
    return *this;
}

void VertexBufferLayout::enable() {
    int offset = 0;
    for (auto element: elements) {
        glVertexAttribPointer(
                element.location,
                element.numOfComponents,
                element.type,
                element.normalized,
                size,
                reinterpret_cast<const void *>(offset)
        );
        glEnableVertexAttribArray(element.location);

        offset += element.numOfComponents * element.typeSize;
    }
}
