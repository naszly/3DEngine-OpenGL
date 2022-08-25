#version 460 core
#extension GL_ARB_bindless_texture : require
#extension GL_ARB_gpu_shader5 : require

layout(location = 0) in vec3 vColor;
layout(location = 1) in vec2 vTexCoord;
layout(location = 2) flat in uint vMaterialIndex;

struct Material {
    sampler2D diffuse;
    sampler2D specular;
    sampler2D normal;
};

layout(binding = 0) uniform uMaterialArray
{
    Material materials[1024];
};

out vec4 color;

void main() {
    sampler2D diffuse = materials[vMaterialIndex].diffuse;
    vec4 textureColor = texture(diffuse, vTexCoord);
    color = vec4(vColor, 1.0) * textureColor;
}