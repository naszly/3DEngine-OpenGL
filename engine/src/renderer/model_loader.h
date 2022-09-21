//
// Created by naszly on 8/23/22.
//

#ifndef ENGINE_SRC_RENDERER_MODEL_LOADER_H
#define ENGINE_SRC_RENDERER_MODEL_LOADER_H

#include "ecs/components.h"

struct Material {
    glm::vec3 ambientColor{0.0f};
    float opacity{1.0f};
    glm::vec3 diffuseColor{0.0f};
    float shininess{0};
    glm::vec3 specularColor{0.0f};
    float specularStrength{1.0f};
    GLuint64 ambientMap{0};
    GLuint64 diffuseMap{0};
    GLuint64 specularMap{0};
    GLuint64 normalMap{0};

    [[nodiscard]] bool empty() const {
        Material emptyMaterial;
        return *this == emptyMaterial;
    }

    bool operator==(const Material &other) const {
        return ambientColor == other.ambientColor &&
               diffuseColor == other.diffuseColor &&
               specularColor == other.specularColor &&
               diffuseMap == other.diffuseMap &&
               specularMap == other.specularMap &&
               normalMap == other.normalMap &&
               opacity == other.opacity &&
               shininess == other.shininess &&
               specularStrength == other.specularStrength;
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
