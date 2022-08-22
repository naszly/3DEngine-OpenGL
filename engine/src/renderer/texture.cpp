//
// Created by naszly on 8/22/22.
//

#include "texture.h"
#include "core/log.h"

#define STB_IMAGE_IMPLEMENTATION

#include <stb/stb_image.h>

void Texture::init(const char *path) {
    int width, height, channels;

    stbi_set_flip_vertically_on_load(true);

    unsigned char *data = stbi_load(path, &width, &height, &channels, 0);

    if (data) {
        glCreateTextures(GL_TEXTURE_2D, 1, &id);
        glTextureStorage2D(id, 1, GL_RGB8, width, height);
        glTextureSubImage2D(id, 0, 0, 0, width, height, GL_RGB, GL_UNSIGNED_BYTE, data);
        glGenerateTextureMipmap(id);
    } else {
        LogCore::error("Failed to load texture {}", path);
    }
}
