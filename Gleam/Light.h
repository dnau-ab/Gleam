#pragma once

#include <glm/vec3.hpp>
#include "Renderable.h"

class Light {
protected:
	Light(const glm::vec3& ambient, const glm::vec3& diffuse, const glm::vec3& specular)
		: ambient(ambient), diffuse(diffuse), specular(specular) {}

public:
	virtual ~Light() {}

	glm::vec3 ambient;
	glm::vec3 diffuse;
	glm::vec3 specular;
};