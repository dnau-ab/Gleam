#pragma once

#include "Light.h"

class PointLight : public Light {
public:
	glm::vec3 position;
	float constant;
	float linear;
	float quadratic;

	PointLight(const glm::vec3& ambient, const glm::vec3& diffuse, const glm::vec3& specular,
		float linear, float quadratic, float constant, const glm::vec3& position)
		: Light(ambient, diffuse, specular), constant(constant), linear(linear), quadratic(quadratic), position(position) {}
};