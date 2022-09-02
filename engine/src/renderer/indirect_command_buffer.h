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

struct DrawArraysIndirectCommand {
    GLuint  count;
    GLuint  instanceCount;
    GLuint  first;
    GLuint  baseInstance;
};

class IndirectCommandBuffer {
public:
    IndirectCommandBuffer() = default;

    ~IndirectCommandBuffer() = default;

    void init(const std::vector<DrawElementsIndirectCommand> &commands);

    void init(const std::vector<DrawArraysIndirectCommand> &commands);

    void destroy();

    void draw() const;

    void drawElements() const;

    void drawArrays() const;

private:
    GLuint buffer;
    GLsizei count;
    bool isIndexed;
};


#endif //ENGINE_SRC_RENDERER_INDIRECT_COMMAND_BUFFER_H
