#pragma once

#include "PointLight.h"

class SpotLight : public PointLight {
public:
	glm::vec3 normal;
	float cutoff;

	SpotLight(const glm::vec3& ambient, const glm::vec3& diffuse, const glm::vec3& specular, float linear, float quadratic, float constant, const glm::vec3& position, const glm::vec3& normal, const float& cutoff)
		: PointLight(ambient, diffuse, specular, linear, quadratic, constant, position), normal(normal), cutoff(cutoff) {}
};