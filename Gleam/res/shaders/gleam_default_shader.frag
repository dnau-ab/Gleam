#version 330 core

out vec4 fragColor;

in vec3 position;
in vec3 normal;
in vec2 texCoord;

in vec3 fragPos;

struct Material {
	sampler2D diffuse1;
	sampler2D specular1;
	sampler2D normal1;
	sampler2D height1;
	float shininess;
};
uniform Material material;

void main() {
	fragColor = texture(material.diffuse1, texCoord);
} 