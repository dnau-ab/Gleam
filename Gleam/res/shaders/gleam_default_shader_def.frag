#version 330 core

layout (location = 0) out vec3 gPosition;
layout (location = 1) out vec3 gNormal;
layout (location = 2) out vec4 gColorSpec;

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
	gPosition = fragPos;
	gNormal = normalize(normal);
	gColorSpec.rgb = texture(material.diffuse1, texCoord).rgb;
	gColorSpec.a = texture(material.specular1, texCoord).r;
} 