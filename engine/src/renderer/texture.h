//
// Created by naszly on 8/22/22.
//

#ifndef ENGINE_SRC_RENDERER_TEXTURE_H
#define ENGINE_SRC_RENDERER_TEXTURE_H

#include <GL/glew.h>

class Texture {
public:
    Texture() = default;

    ~Texture() = default;

    void init(const char* path);

    void destroy() {
        glDeleteTextures(1, &id);
    }

    void bind(unsigned int unit) {
        glBindTextureUnit(unit, id);
    }

    [[nodiscard]] unsigned int getId() const {
        return id;
    }

private:
    unsigned int id{0};
};


#endif //ENGINE_SRC_RENDERER_TEXTURE_H
