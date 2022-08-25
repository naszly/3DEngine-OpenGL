//
// Created by naszly on 8/23/22.
//

#ifndef ENGINE_SRC_RENDERER_BINDLESS_TEXTURE_H
#define ENGINE_SRC_RENDERER_BINDLESS_TEXTURE_H

#include "texture.h"
#include "sampler.h"

class BindlessTexture {
public:
    BindlessTexture() = default;

    ~BindlessTexture() = default;

    void init(const char *path) {
        texture.init(path);

        if (texture.getId()) {
            id = glGetTextureHandleARB(texture.getId());
            if (!glIsTextureHandleResidentARB(id)) {
                glMakeTextureHandleResidentARB(id);
            }
        }
    }

    void init(const char* path, const Sampler &sampler) {
        texture.init(path);

        if (texture.getId()) {
            id = glGetTextureSamplerHandleARB(texture.getId(), sampler.getId());
            if (!glIsTextureHandleResidentARB(id)) {
                glMakeTextureHandleResidentARB(id);
            }
        }
    }

    [[nodiscard]] GLuint64 getId() const {
        return id;
    }

private:
    Texture texture;
    GLuint64 id{0};
};

#endif //ENGINE_SRC_RENDERER_BINDLESS_TEXTURE_H
