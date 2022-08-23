#version 450

layout(location = 0) in vec3 vColor;
layout(location = 1) in vec2 vTexCoord;

layout(binding = 0) uniform sampler2D tex;

out vec4 color;

void main() {
    color = vec4(vColor, 1.0) * texture(tex, vTexCoord);
}