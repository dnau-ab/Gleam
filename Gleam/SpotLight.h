#pragma once

#include "PointLight.h"

class SpotLight : PointLight {
public:
	glm::vec3 normal;
	float cutoff;

	SpotLight(const glm::vec3& ambient, const glm::vec3& diffuse, const glm::vec3& specular, const glm::vec3& position, const glm::vec3& normal, const float& cutoff)
		: PointLight(ambient, diffuse, specular, position), normal(normal), cutoff(cutoff) {}
};