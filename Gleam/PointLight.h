#pragma once

#include "Light.h"

class PointLight : public Light {
public:
	glm::vec3 position;

	PointLight(const glm::vec3& ambient, const glm::vec3& diffuse, const glm::vec3& specular, const glm::vec3& position)
		: Light(ambient, diffuse, specular), position(position) {}
};