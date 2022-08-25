//
// Created by naszly on 8/24/22.
//

#include "indirect_command_buffer.h"

void IndirectCommandBuffer::init(const std::vector<DrawElementsIndirectCommand> &commands) {
    glCreateBuffers(1, &buffer);
    glNamedBufferStorage(buffer,
                         commands.size() * sizeof(DrawElementsIndirectCommand),
                         commands.data(),
                         GL_DYNAMIC_STORAGE_BIT);

    count = commands.size();
}

void IndirectCommandBuffer::destroy() {
    glDeleteBuffers(1, &buffer);
}

void IndirectCommandBuffer::draw() const {
    glBindBuffer(GL_DRAW_INDIRECT_BUFFER, buffer);
    glMultiDrawElementsIndirect(GL_TRIANGLES, GL_UNSIGNED_INT, nullptr, count, sizeof(DrawElementsIndirectCommand));
}
