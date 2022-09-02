//
// Created by naszly on 8/23/22.
//

#include "model_loader.h"
#include "core/log.h"
#include "renderer/bindless_texture.h"

#include <tiny_obj_loader.h>
#include <filesystem>

RenderComponent ModelLoader::getRenderComponent(const ModelComponent &modelComponent) {
    auto &path = modelComponent.path;
    if (renderComponentCache.find(path) != renderComponentCache.end()) {
        return renderComponentCache[path];
    }

    std::shared_ptr<Model> model = loadModel(path.c_str());

    RenderComponent renderComponent;

    std::vector<Vertex> vertices;
    std::vector<uint32_t> indices;
    std::vector<DrawElementsIndirectCommand> commands;

    if (materialBuffer.getId() == 0) {
        materialBuffer.init(BufferUsage::DynamicDraw);
    }

    size_t indexOffset = 0;
    size_t vertexOffset = 0;
    for (auto &mesh: model->meshes) {
        if (mesh.hasMaterial()) {
            BindlessTexture diffuseTexture;
            if (!mesh.diffusePath.empty())
                diffuseTexture.init(mesh.diffusePath.c_str());

            materialArray[mesh.materialIndex].diffuseMap = diffuseTexture.getId();
        }

        vertices.insert(vertices.end(), mesh.vertices.begin(), mesh.vertices.end());
        indices.insert(indices.end(), mesh.indices.begin(), mesh.indices.end());

        commands.emplace_back(DrawElementsIndirectCommand{
                .count = static_cast<GLuint>(mesh.indices.size()),
                .instanceCount = 1,
                .firstIndex = static_cast<GLuint>(indexOffset),
                .baseVertex = static_cast<GLuint>(vertexOffset),
                .baseInstance = static_cast<GLuint>(mesh.materialIndex)
        });

        indexOffset += mesh.indices.size();
        vertexOffset += mesh.vertices.size();
    }

    materialBuffer.bufferData(&materialArray[0], materialsCount * (GLsizeiptr) sizeof(materialArray[0]));

    LogCore::info("Loaded model: {} vertices: {} indices: {}", path, vertices.size(), indices.size());

    renderComponent.vertexArray.init();

    renderComponent.vertexBuffer.init(BufferUsage::StaticDraw);
    renderComponent.vertexBuffer.bufferData(vertices);

    renderComponent.elementBuffer.init(BufferUsage::StaticDraw);
    renderComponent.elementBuffer.bufferData(indices);

    renderComponent.vertexArray.bindVertexBuffer(renderComponent.vertexBuffer, {
            VertexArrayAttrib(0, VertexType::Float, 3), // position
            VertexArrayAttrib(1, VertexType::Float, 3), // color
            VertexArrayAttrib(2, VertexType::Float, 3), // normal
            VertexArrayAttrib(3, VertexType::Float, 2)  // texture coord
    });
    renderComponent.vertexArray.bindElementBuffer(renderComponent.elementBuffer);

    renderComponent.indirectCommandBuffer.init(commands);

    renderComponentCache[path] = renderComponent;

    return renderComponent;
}

std::shared_ptr<Model> ModelLoader::loadModel(const char *path) {
    return loadObjModel(path);
}

std::shared_ptr<Model> ModelLoader::loadObjModel(const char *path) {
    if (modelCache.find(path) != modelCache.end()) {
        return modelCache[path];
    }

    std::filesystem::path filePath(path);

    tinyobj::ObjReaderConfig readerConfig;
    readerConfig.mtl_search_path = filePath.parent_path().string();
    readerConfig.triangulate = true;

    tinyobj::ObjReader reader;

    if (!reader.ParseFromFile(path, readerConfig)) {
        if (!reader.Error().empty()) {
            LogCore::error("TinyObjReader: {}", reader.Error());
        }
        return nullptr;
    }

    if (!reader.Warning().empty()) {
        LogCore::warning("TinyObjReader: {}", reader.Warning());
    }

    std::shared_ptr<Model> model = std::make_shared<Model>();

    auto &attrib = reader.GetAttrib();
    auto &shapes = reader.GetShapes();
    auto &materials = reader.GetMaterials();

    for (const auto &shape: shapes) {
        Mesh mesh;
        std::unordered_map<Vertex, uint32_t> uniqueVertices;

        for (const auto &index: shape.mesh.indices) {
            Vertex vertex{};
            vertex.position = {
                    attrib.vertices[3 * index.vertex_index + 0],
                    attrib.vertices[3 * index.vertex_index + 1],
                    attrib.vertices[3 * index.vertex_index + 2]
            };
            vertex.color = {
                    attrib.colors[3 * index.vertex_index + 0],
                    attrib.colors[3 * index.vertex_index + 1],
                    attrib.colors[3 * index.vertex_index + 2]
            };
            vertex.normal = {
                    attrib.normals[3 * index.normal_index + 0],
                    attrib.normals[3 * index.normal_index + 1],
                    attrib.normals[3 * index.normal_index + 2]
            };
            vertex.texCoord = {
                    attrib.texcoords[2 * index.texcoord_index + 0],
                    attrib.texcoords[2 * index.texcoord_index + 1]
            };
            if (uniqueVertices.find(vertex) == uniqueVertices.end()) {
                uniqueVertices[vertex] = mesh.vertices.size();
                mesh.vertices.push_back(vertex);
            }
            mesh.indices.push_back(uniqueVertices[vertex]);
        }

        if (!materials[shape.mesh.material_ids[0]].diffuse_texname.empty()) {
            std::filesystem::path diffusePath =
                    filePath.parent_path() / materials[shape.mesh.material_ids[0]].diffuse_texname;
            mesh.diffusePath = diffusePath.string();
        }

        mesh.materialIndex = materialsCount;

        model->meshes.push_back(mesh);
        ++materialsCount;
    }
    modelCache[path] = model;
    return model;
}

