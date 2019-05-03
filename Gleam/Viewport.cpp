#include "Viewport.h"

glm::vec2 Viewport::getPosition() {
	return _position;
}

glm::vec2 Viewport::getSize() {
	return _size;
}

void Viewport::setPosition(glm::vec<2, int> position) {
	_position = position;
}

void Viewport::setSize(glm::vec<2, unsigned> size) {
	_size = size;
}
/*
void Viewport::render() {
	// geometry pass
	
	glBindFramebuffer(GL_FRAMEBUFFER, 0);
	
	// lighting pass
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	//lightingPassShader.use();
	glActiveTexture(GL_TEXTURE0);
	glBindTexture(GL_TEXTURE_2D, _gPosition);
	glActiveTexture(GL_TEXTURE1);
	glBindTexture(GL_TEXTURE_2D, _gNormal);
	glActiveTexture(GL_TEXTURE2);
	glBindTexture(GL_TEXTURE_2D, _gColorSpec);
	// set light uniform info
	

	// render quad
	
	// copy geometry's depth buffer to default framebuffer's depth buffer
	glBindFramebuffer(GL_READ_FRAMEBUFFER, _gBuffer);
	// write to default framebuffer
	glBindFramebuffer(GL_DRAW_FRAMEBUFFER, 0);
	// blit to default framebuffer
	glBlitFramebuffer(0, 0, _size.x, _size.y, 0, 0, _size.x, _size.y, GL_DEPTH_BUFFER_BIT, GL_NEAREST);
	glBindFramebuffer(GL_FRAMEBUFFER, 0);
	
	// forward rendered lights here vvv
}
*/

void Viewport::renderGeometry() {
	glm::mat4 projection = camera->getProjectionMatrix((float)_size.x / (float)_size.y, 0.1f, 1000.0f);
	glm::mat4 view = camera->getViewMatrix();

	for (Renderable*& renderable : scene->getRenderables()) {
		renderable->render(projection, view);
	}
}

void Viewport::renderLighting() {
	std::vector<Light*> lights = scene->getLights();
	for (size_t i = 0; i < lights.size(); i++) {

	}
}