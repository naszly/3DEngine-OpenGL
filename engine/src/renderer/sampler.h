//
// Created by naszly on 8/22/22.
//

#ifndef ENGINE_SRC_RENDERER_SAMPLER_H
#define ENGINE_SRC_RENDERER_SAMPLER_H

#include <GL/glew.h>
#include <glm/glm.hpp>

enum class SamplerFilter {
    Nearest = GL_NEAREST,
    Linear = GL_LINEAR
};

enum class SamplerWrap {
    ClampToEdge = GL_CLAMP_TO_EDGE,
    Repeat = GL_REPEAT,
    MirroredRepeat = GL_MIRRORED_REPEAT,
    ClampToBorder = GL_CLAMP_TO_BORDER
};

class Sampler {
public:
    Sampler() = default;

    ~Sampler() = default;

    void init() {
        glCreateSamplers(1, &id);
        GLint maxAnisotropy = 0;
        glGetIntegerv(GL_MAX_TEXTURE_MAX_ANISOTROPY_EXT, &maxAnisotropy);
        glSamplerParameteri(id, GL_TEXTURE_MAX_ANISOTROPY_EXT, maxAnisotropy);
    }

    void setFilter(SamplerFilter minFilter, SamplerFilter magFilter) const {
        glSamplerParameteri(id, GL_TEXTURE_MIN_FILTER, static_cast<GLint>(minFilter));
        glSamplerParameteri(id, GL_TEXTURE_MAG_FILTER, static_cast<GLint>(magFilter));
    }

    void setWrap(SamplerWrap wrap) const {
        glSamplerParameteri(id, GL_TEXTURE_WRAP_S, static_cast<GLint>(wrap));
        glSamplerParameteri(id, GL_TEXTURE_WRAP_T, static_cast<GLint>(wrap));
        glSamplerParameteri(id, GL_TEXTURE_WRAP_R, static_cast<GLint>(wrap));
    }

    void setBorderColor(glm::vec4 borderColor) const {
        glSamplerParameterfv(id, GL_TEXTURE_BORDER_COLOR, &borderColor[0]);
    }

    void destroy() {
        glDeleteSamplers(1, &id);
    }

    void bind(unsigned int unit) const {
        glBindSampler(unit, id);
    }

    [[nodiscard]] unsigned int getId() const {
        return id;
    }

private:
    unsigned int id{0};
};


#endif //ENGINE_SRC_RENDERER_SAMPLER_H
