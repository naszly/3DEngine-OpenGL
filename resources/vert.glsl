#version 450

layout(location=0) in vec3 aPos;
layout(location=1) in vec3 aColor;
layout(location=2) in vec2 aTexCoord;

layout(location=0) out vec3 vColor;
layout(location=1) out vec2 vTexCoord;

uniform mat4 uModel;
uniform mat4 uView;
uniform mat4 uProjection;

void main() {
	gl_Position = uProjection * uView * uModel * vec4(aPos, 1.f);
	vColor = aColor;
	vTexCoord = aTexCoord;
}