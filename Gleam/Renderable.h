#pragma once
#include "Shader.h"
#include "Transform.h"
#include "Camera.h"

#include <glm/mat4x4.hpp>

class Renderable {
protected:
	Shader* _shader;
	ShaderResource* _shaderResource;
public:
	Transform transform;

	glm::mat3 getNormalMatrix() const;
	void setResource(ShaderResource& resource);

	virtual void render(const Camera& camera) = 0;
};