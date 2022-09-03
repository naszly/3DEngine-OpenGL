#version 460 core
#extension GL_ARB_bindless_texture : require
#extension GL_ARB_gpu_shader5 : require

layout(location=0) in vec3 aPos;
layout(location=1) in vec3 aNormal;
layout(location=2) in vec4 aColor;
layout(location=3) in vec2 aTexCoord;

layout(location=0) out vec4 vColor;
layout(location=1) out vec2 vTexCoord;
layout(location=2) out uint vMaterialIndex;

uniform mat4 uModel;
uniform mat4 uView;
uniform mat4 uProjection;

void main() {
    gl_Position = uProjection * uView * uModel * vec4(aPos, 1.f);
    vColor = aColor;
    vTexCoord = aTexCoord;
    vMaterialIndex = gl_BaseInstance;
}