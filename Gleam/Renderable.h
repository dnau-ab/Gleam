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
	void setShader(Shader* shader);
	void setResource(ShaderResource& resource);

	virtual void render(const glm::mat4& projection, const glm::mat4& view) = 0;
};