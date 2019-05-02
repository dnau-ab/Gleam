#include "Viewport.h"

glm::vec2 Viewport::getPosition() {
	return _position;
}

glm::vec2 Viewport::getSize() {
	return _size;
}

void Viewport::render() {
	for (Renderable* &renderable : scene->getRenderables()) {
		renderable->render(camera);
	}
}