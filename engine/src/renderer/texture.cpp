//
// Created by naszly on 8/22/22.
//

#include "texture.h"
#include "core/log.h"

#include <stb/stb_image.h>

void Texture::init(const char *path) {
    if (textureCache.find(path) != textureCache.end()) {
        id = textureCache[path];
        return;
    }

    int width, height, channels;

    stbi_set_flip_vertically_on_load(true);

    unsigned char *data = stbi_load(path, &width, &height, &channels, 0);

    if (data) {
        glCreateTextures(GL_TEXTURE_2D, 1, &id);
        GLenum format = channels == 4 ? GL_RGBA : GL_RGB;
        GLenum internalFormat = channels == 4 ? GL_RGBA16 : GL_RGB16;
        glTextureStorage2D(id, 1, internalFormat, width, height);
        glTextureSubImage2D(id, 0, 0, 0, width, height, format, GL_UNSIGNED_BYTE, data);
        glGenerateTextureMipmap(id);
        textureCache[path] = id;
    } else {
        LogCore::error("Failed to load texture {}", path);
    }
}
