#version 460 core
#extension GL_ARB_bindless_texture : require
#extension GL_ARB_gpu_shader5 : require

#define MAX_MATERIALS 1024u

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
    Material materials[MAX_MATERIALS];
};

out vec4 color;

Material getMaterial(uint index) {
    Material material;
    if (index < MAX_MATERIALS) material = materials[index];
    return material;
}

vec4 sampleTexture(sampler2D sampler, vec2 texCoord) {
    uvec2 samplerHandle = uvec2(sampler);
    bool validSampler = samplerHandle.x != 0 || samplerHandle.y != 0;
    return validSampler ? texture(sampler, texCoord) : vec4(1.0);
}

void main() {
    sampler2D diffuse = getMaterial(vMaterialIndex).diffuse;
    vec4 textureColor = sampleTexture(diffuse, vTexCoord);
    color = vec4(vColor, 1.0) * textureColor;
}