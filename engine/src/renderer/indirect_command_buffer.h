//
// Created by naszly on 8/24/22.
//

#ifndef ENGINE_SRC_RENDERER_INDIRECT_COMMAND_BUFFER_H
#define ENGINE_SRC_RENDERER_INDIRECT_COMMAND_BUFFER_H

#include <GL/glew.h>

struct DrawElementsIndirectCommand {
    GLuint  count;
    GLuint  instanceCount;
    GLuint  firstIndex;
    GLuint  baseVertex;
    GLuint  baseInstance;
};

class IndirectCommandBuffer {
public:
    IndirectCommandBuffer() = default;

    ~IndirectCommandBuffer() = default;

    void init(const std::vector<DrawElementsIndirectCommand> &commands);

    void destroy();

    void bind() const;

    void draw() const;

private:
    GLuint buffer;
    GLsizei count;
};


#endif //ENGINE_SRC_RENDERER_INDIRECT_COMMAND_BUFFER_H
