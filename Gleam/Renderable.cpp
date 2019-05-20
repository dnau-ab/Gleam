#include "Renderable.h"

glm::mat3 Renderable::getNormalMatrix() const {
	glm::mat4 transformation = transform.getTransformationMatrix();
	return glm::mat3(glm::transpose(glm::inverse(transformation)));
}

void Renderable::setShader(Shader* shader) {
	_shader = shader;
}

void Renderable::setResource(ShaderResource& resource) {
	_shaderResource = &resource;
}

void Renderable::updateResource() {
	if (_shaderResource == nullptr) return;
	for (auto itr = _shaderResource->begin(); itr != _shaderResource->end(); itr++) {
		_shader->setUniform(itr->first, itr->second);
	}
}