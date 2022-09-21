//
// Created by naszly on 8/23/22.
//

#include "model_loader.h"
#include "core/log.h"
#include "renderer/bindless_texture.h"

#include <filesystem>

#include <assimp/Importer.hpp>
#include <assimp/scene.h>
#include <assimp/postprocess.h>

static const aiScene *loadModel(const char *path);

RenderComponent ModelLoader::getRenderComponent(const ModelComponent &modelComponent) {
    auto &path = modelComponent.path;
    if (renderComponentCache.find(path) != renderComponentCache.end()) {
        return renderComponentCache[path];
    }

    if (materialBuffer.getId() == 0) {
        materialBuffer.init();
        materialArray[0] = Material{};
        materialsCount = 1;
        materialBuffer.bufferData(&materialArray[0], materialsCount * (GLsizeiptr) sizeof(materialArray[0]));
    }

    RenderComponent renderComponent;

    const aiScene *scene = loadModel(path.c_str());

    if (!scene)
        return renderComponent;

    std::vector<uint32_t> materialIndices;

    if (scene->HasMaterials()) {
        std::filesystem::path modelPath(path);
        for (int i = 0; i < scene->mNumMaterials; ++i) {
            aiMaterial *material = scene->mMaterials[i];

            Material materialStruct{};

            if (material->GetTextureCount(aiTextureType_AMBIENT) > 0) {
                BindlessTexture bindlessTexture;
                aiString texturePath;
                material->GetTexture(aiTextureType_AMBIENT, 0, &texturePath);
                std::filesystem::path textureFullPath = modelPath.parent_path() / texturePath.C_Str();
                bindlessTexture.init(textureFullPath.string().c_str());
                materialStruct.ambientMap = bindlessTexture.getId();
            }

            if (material->GetTextureCount(aiTextureType_DIFFUSE) > 0) {
                BindlessTexture bindlessTexture;
                aiString texturePath;
                material->GetTexture(aiTextureType_DIFFUSE, 0, &texturePath);
                std::filesystem::path textureFullPath = modelPath.parent_path() / texturePath.C_Str();
                bindlessTexture.init(textureFullPath.string().c_str());
                materialStruct.diffuseMap = bindlessTexture.getId();
            }

            if (material->GetTextureCount(aiTextureType_SPECULAR) > 0) {
                BindlessTexture bindlessTexture;
                aiString texturePath;
                material->GetTexture(aiTextureType_SPECULAR, 0, &texturePath);
                std::filesystem::path textureFullPath = modelPath.parent_path() / texturePath.C_Str();
                bindlessTexture.init(textureFullPath.string().c_str());
                materialStruct.specularMap = bindlessTexture.getId();
            }

            if (material->GetTextureCount(aiTextureType_NORMALS) > 0) {
                BindlessTexture bindlessTexture;
                aiString texturePath;
                material->GetTexture(aiTextureType_NORMALS, 0, &texturePath);
                std::filesystem::path textureFullPath = modelPath.parent_path() / texturePath.C_Str();
                bindlessTexture.init(textureFullPath.string().c_str());
                materialStruct.normalMap = bindlessTexture.getId();
            }

            aiColor3D color;
            if (material->Get(AI_MATKEY_COLOR_AMBIENT, color) == AI_SUCCESS) {
                materialStruct.ambientColor = glm::vec3(color.r, color.g, color.b);
            }

            if (material->Get(AI_MATKEY_COLOR_DIFFUSE, color) == AI_SUCCESS) {
                materialStruct.diffuseColor = glm::vec3(color.r, color.g, color.b);
            }

            if (material->Get(AI_MATKEY_COLOR_SPECULAR, color) == AI_SUCCESS) {
                materialStruct.specularColor = glm::vec3(color.r, color.g, color.b);
            }

            float opacity;
            if (material->Get(AI_MATKEY_OPACITY, opacity) == AI_SUCCESS) {
                materialStruct.opacity = opacity;
            }

            float shininess;
            if (material->Get(AI_MATKEY_SHININESS, shininess) == AI_SUCCESS) {
                materialStruct.shininess = shininess;
            }

            float shininessStrength;
            if (material->Get(AI_MATKEY_SHININESS_STRENGTH, shininessStrength) == AI_SUCCESS) {
                materialStruct.specularStrength = shininessStrength;
            }

            if (materialStruct.empty()) {
                materialIndices.push_back(0);
            } else {
                materialArray[materialsCount] = materialStruct;
                materialIndices.push_back(materialsCount);
                materialsCount++;
            }

            materialBuffer.bufferData(&materialArray[0], materialsCount * (GLsizeiptr) sizeof(materialArray[0]));
        }
    }

    if (scene->HasMeshes()) {
        size_t vertexCount = 0;
        size_t indexCount = 0;
        size_t vertexOffset = 0;
        size_t indexOffset = 0;

        std::vector<DrawElementsIndirectCommand> commands;

        for (int i = 0; i < scene->mNumMeshes; ++i) {
            vertexCount += scene->mMeshes[i]->mNumVertices;
            indexCount += scene->mMeshes[i]->mNumFaces * 3;
        }

        auto *positions = new aiVector3D[vertexCount];
        auto *normals = new aiVector3D[vertexCount];
        auto *texCoords = new aiVector2D[vertexCount];

        auto *indices = new uint32_t[indexCount];


        for (int i = 0; i < scene->mNumMeshes; ++i) {
            aiMesh *mesh = scene->mMeshes[i];

            GLuint materialIndex = mesh->mMaterialIndex < materialIndices.size() ?
                                   materialIndices[mesh->mMaterialIndex] :
                                   0;

            commands.emplace_back(DrawElementsIndirectCommand{
                    .count = static_cast<GLuint>(mesh->mNumFaces * 3),
                    .instanceCount = 1,
                    .firstIndex = static_cast<GLuint>(indexOffset),
                    .baseVertex = static_cast<GLuint>(vertexOffset),
                    .baseInstance = materialIndex
            });

            memcpy(&positions[vertexOffset], mesh->mVertices, sizeof(aiVector3D) * mesh->mNumVertices);
            memcpy(&normals[vertexOffset], mesh->mNormals, sizeof(aiVector3D) * mesh->mNumVertices);

            if (mesh->HasTextureCoords(0)) {
                for (int j = 0; j < mesh->mNumVertices; ++j)
                    texCoords[vertexOffset + j] = {mesh->mTextureCoords[0][j].x, mesh->mTextureCoords[0][j].y};
            } else {
                memset(&texCoords[vertexOffset], 0, sizeof(aiVector2D) * mesh->mNumVertices);
            }

            vertexOffset += mesh->mNumVertices;

            for (int j = 0; j < mesh->mNumFaces; ++j) {
                aiFace face = mesh->mFaces[j];
                for (int k = 0; k < face.mNumIndices; ++k) {
                    indices[indexOffset++] = face.mIndices[k];
                }
            }
        }

        renderComponent.vertexArray.init();

        renderComponent.posBuffer.init();
        renderComponent.posBuffer.bufferData(positions, sizeof(aiVector3D) * vertexCount);
        renderComponent.normalBuffer.init();
        renderComponent.normalBuffer.bufferData(normals, sizeof(aiVector3D) * vertexCount);
        renderComponent.texCoordBuffer.init();
        renderComponent.texCoordBuffer.bufferData(texCoords, sizeof(aiVector2D) * vertexCount);
        renderComponent.indexBuffer.init();
        renderComponent.indexBuffer.bufferData(indices, sizeof(uint32_t) * indexCount);

        renderComponent.vertexArray.bindVertexBuffer(renderComponent.posBuffer, {
                VertexArrayAttrib(0, VertexType::Float, 3), // position
        });
        renderComponent.vertexArray.bindVertexBuffer(renderComponent.normalBuffer, {
                VertexArrayAttrib(1, VertexType::Float, 3), // normal
        });
        renderComponent.vertexArray.bindVertexBuffer(renderComponent.texCoordBuffer, {
                VertexArrayAttrib(2, VertexType::Float, 2), // texCoord
        });
        renderComponent.vertexArray.bindElementBuffer(renderComponent.indexBuffer);

        renderComponent.indirectCommandBuffer.init(commands);

        delete[] positions;
        delete[] normals;
        delete[] texCoords;
        delete[] indices;
    }

    renderComponentCache[path] = renderComponent;

    return renderComponent;
}

static const aiScene *loadModel(const char *path) {
    std::filesystem::path filePath(path);

    static Assimp::Importer importer;
    const aiScene *scene = importer.ReadFile(path,
                                             aiProcess_Triangulate |
                                             aiProcess_GenNormals |
                                             aiProcess_JoinIdenticalVertices);

    if (!scene || scene->mFlags & AI_SCENE_FLAGS_INCOMPLETE || !scene->mRootNode) {
        Log::error("Assimp error: {}", importer.GetErrorString());
        return nullptr;
    }

    return scene;
}