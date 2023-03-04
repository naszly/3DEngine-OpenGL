//
// Created by naszly on 8/20/22.
//

#include "shader.h"
#include "../core/log.h"

void Shader::setInt(const char *name, int value) const {
    int loc;
    if (findUniformLocation(name, &loc)) {
        glUniform1i(loc, value);
    }
}

void Shader::setIVec2(const char *name, const glm::ivec2 &vec) const {
    int loc;
    if (findUniformLocation(name, &loc)) {
        glUniform2iv(loc, 1, &vec[0]);
    }
}

void Shader::setIVec3(const char *name, const glm::ivec3 &vec) const {
    int loc;
    if (findUniformLocation(name, &loc)) {
        glUniform3iv(loc, 1, &vec[0]);
    }
}

void Shader::setIVec4(const char *name, const glm::ivec4 &vec) const {
    int loc;
    if (findUniformLocation(name, &loc)) {
        glUniform4iv(loc, 1, &vec[0]);
    }
}

void Shader::setFloat(const char *name, float value) const {
    int loc;
    if (findUniformLocation(name, &loc)) {
        glUniform1f(loc, value);
    }
}

void Shader::setVec2(const char *name, const glm::vec2 &vec) const {
    int loc;
    if (findUniformLocation(name, &loc)) {
        glUniform2fv(loc, 1, &vec[0]);
    }
}

void Shader::setVec3(const char *name, const glm::vec3 &vec) const {
    int loc;
    if (findUniformLocation(name, &loc)) {
        glUniform3fv(loc, 1, &vec[0]);
    }
}

void Shader::setVec4(const char *name, const glm::vec4 &vec) const {
    int loc;
    if (findUniformLocation(name, &loc)) {
        glUniform4fv(loc, 1, &vec[0]);
    }
}

void Shader::setMat2(const char *name, const glm::mat2 &mat) const {
    int loc;
    if (findUniformLocation(name, &loc)) {
        glUniformMatrix2fv(loc, 1, GL_FALSE, &mat[0][0]);
    }
}

void Shader::setMat3(const char *name, const glm::mat3 &mat) const {
    int loc;
    if (findUniformLocation(name, &loc)) {
        glUniformMatrix3fv(loc, 1, GL_FALSE, &mat[0][0]);
    }
}

void Shader::setMat4(const char *name, const glm::mat4 &mat) const {
    int loc;
    if (findUniformLocation(name, &loc)) {
        glUniformMatrix4fv(loc, 1, GL_FALSE, &mat[0][0]);
    }
}

void Shader::setBuffer(const char *name, const Buffer &buffer, unsigned int binding) const {
    GLuint uniformBlockIndex = glGetUniformBlockIndex(id, name);
    glUniformBlockBinding(id, uniformBlockIndex, binding);
    glBindBufferBase(GL_UNIFORM_BUFFER, binding, buffer.getId());
}


void Shader::createFromFiles(const char *vertexPath, const char *fragmentPath) {
    // 1. retrieve the vertex/fragment source code from filePath
    std::string vertexCode;
    std::string fragmentCode;
    std::ifstream vShaderFile;
    std::ifstream fShaderFile;
    // ensure ifstream objects can throw exceptions:
    vShaderFile.exceptions(std::ifstream::failbit | std::ifstream::badbit);
    fShaderFile.exceptions(std::ifstream::failbit | std::ifstream::badbit);
    try {
        // open files
        vShaderFile.open(vertexPath);
        fShaderFile.open(fragmentPath);
        std::stringstream vShaderStream, fShaderStream;
        // read file's buffer contents into streams
        vShaderStream << vShaderFile.rdbuf();
        fShaderStream << fShaderFile.rdbuf();
        // close file handlers
        vShaderFile.close();
        fShaderFile.close();
        // convert stream into string
        vertexCode = vShaderStream.str();
        fragmentCode = fShaderStream.str();
    }
    catch (std::ifstream::failure &e) {
        LogOpenGL::error("Shader failed to load: {0} ", e.what());
    }

    const char *vShaderCode = vertexCode.c_str();
    const char *fShaderCode = fragmentCode.c_str();

    compileShader(vShaderCode, fShaderCode);
}

void Shader::compileShader(const char *vertexCode, const char *fragmentCode) {

    unsigned int vertex, fragment;
    // vertex shader
    vertex = glCreateShader(GL_VERTEX_SHADER);
    glShaderSource(vertex, 1, &vertexCode, nullptr);
    glCompileShader(vertex);
    checkCompileErrors(vertex, "VERTEX");
    // fragment Shader
    fragment = glCreateShader(GL_FRAGMENT_SHADER);
    glShaderSource(fragment, 1, &fragmentCode, nullptr);
    glCompileShader(fragment);
    checkCompileErrors(fragment, "FRAGMENT");
    // shader Program
    id = glCreateProgram();
    glAttachShader(id, vertex);
    glAttachShader(id, fragment);
    glLinkProgram(id);
    checkCompileErrors(id, "PROGRAM");
    // delete the shaders as they're linked into our program now and no longer necessary
    glDeleteShader(vertex);
    glDeleteShader(fragment);
}

void Shader::checkCompileErrors(unsigned int shader, const std::string &type) {
    int success;
    char infoLog[1024];
    if (type != "PROGRAM") {
        glGetShaderiv(shader, GL_COMPILE_STATUS, &success);
        if (!success) {
            glGetShaderInfoLog(shader, 1024, nullptr, infoLog);
            LogOpenGL::error("Shader compilation error of type {0}\n{1}", type, infoLog);
        }
    } else {
        glGetProgramiv(shader, GL_LINK_STATUS, &success);
        if (!success) {
            glGetProgramInfoLog(shader, 1024, nullptr, infoLog);
            LogOpenGL::error("Shader linking error of type {0}\n{1}", type, infoLog);
        }
    }
    assert(success);
}

void Shader::getUniforms() {
    GLuint i;
    GLint count;

    GLint size; // size of the variable
    GLenum type; // type of the variable (float, vec3 or mat4, etc)

    const GLsizei bufSize = 48; // maximum name length
    GLchar name[bufSize]; // variable name in GLSL
    GLsizei length; // name length

    glGetProgramiv(id, GL_ACTIVE_UNIFORMS, &count);
    LogOpenGL::info("Active Uniforms: {0}", count);

    for (i = 0; i < count; i++) {
        glGetActiveUniform(id, i, bufSize, &length, &size, &type, name);

        //LogOpenGL::info("Uniform #{0} Type: {1} Name: {2}", i, type, name);
        uniformLocations[name] = glGetUniformLocation(id, name);
    }
}

bool Shader::findUniformLocation(const char *str, int *location) const {
    auto iterator = uniformLocations.find(str);

    if (iterator == uniformLocations.end()) {
        LogOpenGL::error("No uniform named {0}", str);
        return false;
    } else {
        *location = iterator->second;
        return true;
    }
}
