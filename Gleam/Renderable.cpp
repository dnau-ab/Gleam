#include "Renderable.h"

glm::mat3 Renderable::getNormalMatrix() const {
	glm::mat4 transformation = transform.getTransformationMatrix();
	return glm::mat3(glm::transpose(glm::inverse(transformation)));
}