#version 460 core
#extension GL_ARB_bindless_texture : require
#extension GL_ARB_gpu_shader5 : require

layout(location=0) in vec3 aPos;
layout(location=1) in vec3 aNormal;
layout(location=2) in vec2 aTexCoord;

out vec3 vNormal;
out vec2 vTexCoord;
flat out uint vMaterialIndex;
out vec3 vFragPos;

uniform mat4 uModel;
uniform mat4 uView;
uniform mat4 uProjection;

void main() {
    gl_Position = uProjection * uView * uModel * vec4(aPos, 1.f);
    vNormal = mat3(transpose(inverse(uModel))) * aNormal;
    vTexCoord = aTexCoord;
    vMaterialIndex = gl_BaseInstance;
    vFragPos = vec3(uModel * vec4(aPos, 1.f));
}