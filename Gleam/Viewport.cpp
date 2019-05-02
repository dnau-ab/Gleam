#include "Viewport.h"

glm::vec2 Viewport::getPosition() {
	return _position;
}

glm::vec2 Viewport::getSize() {
	return _size;
}

void Viewport::render() {
	glm::mat4 projection = camera->getProjectionMatrix((float)_size.x / (float)_size.y, 0.1f, 1000.0f);
	glm::mat4 view = camera->getViewMatrix();
	for (Renderable* &renderable : scene->getRenderables()) {
		renderable->render(projection, view);
	}
}