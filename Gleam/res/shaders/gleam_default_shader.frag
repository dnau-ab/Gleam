#version 330 core

out vec4 fragColor;

in vec3 position;
in vec3 normal;
in vec2 texCoord;

in vec3 fragPos;

void main() {
	fragColor = vec4(1.0, 0, 1.0, 1.0);
} 