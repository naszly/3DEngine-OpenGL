//
// Created by naszly on 8/20/22.
//

#ifndef ENGINE_SRC_RENDERER_SHADER_H
#define ENGINE_SRC_RENDERER_SHADER_H

#include <GL/glew.h>
#include <glm/glm.hpp>
#include "buffer.h"

class Shader {
public:
    Shader() = default;

    ~Shader() {
        deleteShader();
    }

    void init(const char *vertexPath, const char *fragmentPath) {
        createFromFiles(vertexPath, fragmentPath);
        getUniforms();
    }

    void bind() const {
        glUseProgram(id);
    }

    void deleteShader() const {
        glDeleteProgram(id);
    }

    void setInt(const char *name, int value) const;

    void setIVec2(const char *name, const glm::ivec2 &vec) const;

    void setIVec3(const char *name, const glm::ivec3 &vec) const;

    void setIVec4(const char *name, const glm::ivec4 &vec) const;

    void setFloat(const char *name, float value) const;

    void setVec2(const char *name, const glm::vec2 &vec) const;

    void setVec3(const char *name, const glm::vec3 &vec) const;

    void setVec4(const char *name, const glm::vec4 &vec) const;

    void setMat2(const char *name, const glm::mat2 &mat) const;

    void setMat3(const char *name, const glm::mat3 &mat) const;

    void setMat4(const char *name, const glm::mat4 &mat) const;

    void setBuffer(const char *name, const Buffer &buffer, unsigned int binding) const;

private:
    unsigned int id{0};

    std::unordered_map<std::string, int> uniformLocations;

    void createFromFiles(const char *vertexPath, const char *fragmentPath);

    void compileShader(const char *vertexCode, const char *fragmentCode);

    static void checkCompileErrors(unsigned int shader, const std::string &type);

    void getUniforms();

    bool findUniformLocation(const char *str, int *location) const;
};


#endif //ENGINE_SRC_RENDERER_SHADER_H
