#pragma once
#include "Shader.h"
#include "Transform.h"
#include "Camera.h"

#include <glm/mat4x4.hpp>

class Renderable {
protected:
	Shader* shader;

public:
	Transform transform;

	glm::mat4 getModelMatrix();
	glm::mat3 getNormalMatrix();

	virtual void render(const Camera& camera) = 0;
};