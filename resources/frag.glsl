#version 460 core
#extension GL_ARB_bindless_texture : require
#extension GL_ARB_gpu_shader5 : require

#define MAX_MATERIALS 1024u

in vec3 vNormal;
in vec2 vTexCoord;
flat in uint vMaterialIndex;
in vec3 vFragPos;

struct Material {
    vec3 ambientColor;
    float opacity;
    vec3 diffuseColor;
    float shininess;
    vec3 specularColor;
    float specularStrength;
    sampler2D ambientMap;
    sampler2D diffuseMap;
    sampler2D specularMap;
    sampler2D normalMap;
};

struct DirectionalLight {
    vec3 color;
    float ambientStrength;
    vec3 direction;
    float diffuseStrength;
};

uniform vec3 uCameraPosition;
uniform DirectionalLight uDirectionalLight;

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
    return validSampler ? texture(sampler, texCoord) : vec4(1.0f);
}

vec4 calculateDirectionalLight(DirectionalLight light, Material material, vec3 normal, vec3 viewDirection) {
    vec3 lightDirection = normalize(light.direction);
    vec3 reflectDirection = reflect(-lightDirection, normal);

    float diffuse = max(dot(normal, lightDirection), 0.0f);
    float specular = pow(max(dot(viewDirection, reflectDirection), 0.0f), material.shininess);

    vec4 ambientLight = vec4(light.color * light.ambientStrength * material.ambientColor, material.opacity);
    vec4 diffuseLight = vec4(light.color * light.diffuseStrength * material.diffuseColor * diffuse, material.opacity);
    vec3 specularLight = light.color * material.specularStrength * material.specularColor * specular;

    sampler2D ambientMap = material.ambientMap;
    sampler2D diffuseMap = material.diffuseMap;
    sampler2D specularMap = material.specularMap;

    vec4 ambientColor = sampleTexture(ambientMap, vTexCoord) * ambientLight;
    vec4 diffuseColor = sampleTexture(diffuseMap, vTexCoord) * diffuseLight;
    vec3 specularColor = vec3(sampleTexture(specularMap, vTexCoord)) * specularLight;

    return vec4(ambientColor.rgb + diffuseColor.rgb + specularColor, ambientColor.a * diffuseColor.a);
}

void main() {
    Material material = getMaterial(vMaterialIndex);
    vec3 normal = normalize(vNormal);
    vec3 viewDirection = normalize(uCameraPosition - vFragPos);

    color = calculateDirectionalLight(uDirectionalLight, material, normal, viewDirection);

}