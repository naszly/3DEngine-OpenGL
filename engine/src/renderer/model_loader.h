//
// Created by naszly on 8/23/22.
//

#ifndef ENGINE_SRC_RENDERER_MODEL_LOADER_H
#define ENGINE_SRC_RENDERER_MODEL_LOADER_H

#include "ecs/components.h"

struct Material {
    GLuint64 diffuseMap{0};
    GLuint64 specularMap{0};
    GLuint64 normalMap{0};

    [[nodiscard]] bool empty() const {
        return diffuseMap == 0 && specularMap == 0 && normalMap == 0;
    }
};

class ModelLoader {
public:
    static RenderComponent getRenderComponent(const ModelComponent &modelComponent);

    static const Buffer &getMaterialBuffer() {
        return materialBuffer;
    }

private:
    inline static std::unordered_map<std::string, RenderComponent> renderComponentCache;
    inline static Buffer materialBuffer;
    inline static Material materialArray[1024];
    inline static unsigned int materialsCount{0};
};

#endif //ENGINE_SRC_RENDERER_MODEL_LOADER_H
