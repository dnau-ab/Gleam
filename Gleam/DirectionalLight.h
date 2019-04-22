#pragma once

#include "Light.h"

class DirectionalLight : public Light {
public:
	glm::vec3 direction;

	DirectionalLight(const glm::vec3& ambient, const glm::vec3& diffuse, const glm::vec3& specular, const glm::vec3& direction)
		: Light(ambient, diffuse, specular), direction(direction) {}

};