//
// Created by naszly on 8/23/22.
//

#ifndef ENGINE_SRC_RENDERER_MODEL_LOADER_H
#define ENGINE_SRC_RENDERER_MODEL_LOADER_H

#include "ecs/components.h"
#include "utils/utils.h"

#define GLM_ENABLE_EXPERIMENTAL

#include <glm/gtx/hash.hpp>

struct Vertex {
    glm::vec3 position;
    glm::vec3 color;
    glm::vec3 normal;
    glm::vec2 texCoord;

    bool operator==(const Vertex &other) const {
        return position == other.position &&
               color == other.color &&
               normal == other.normal &&
               texCoord == other.texCoord;
    }
};

struct Material {
    GLuint64 diffuseMap;
    GLuint64 specularMap;
    GLuint64 normalMap;
};

struct Mesh {
    std::vector<Vertex> vertices;
    std::vector<uint32_t> indices;
    GLuint materialIndex;
    std::string diffusePath;
    std::string specularPath;
    std::string normalPath;
};

struct Model {
    std::vector<Mesh> meshes;
};

class ModelLoader {
public:
    static RenderComponent getRenderComponent(const ModelComponent &modelComponent);

    static std::shared_ptr<Model> loadModel(const char *path);

    static std::shared_ptr<Model> loadObjModel(const char *path);

    static const Buffer &getMaterialBuffer() {
        return materialBuffer;
    }

private:
    inline static std::unordered_map<std::string, std::shared_ptr<Model>> modelCache;
    inline static std::unordered_map<std::string, RenderComponent> renderComponentCache;
    inline static Buffer materialBuffer;
    inline static Material materialArray[1024];
    inline static unsigned int materialsCount{0};
};

namespace std {
    template<>
    struct hash<Vertex> {
        size_t operator()(Vertex const &vertex) const {
            size_t seed = 0;
            hashCombine(seed, vertex.position, vertex.color, vertex.normal, vertex.texCoord);
            return seed;
        }
    };
}

#endif //ENGINE_SRC_RENDERER_MODEL_LOADER_H
