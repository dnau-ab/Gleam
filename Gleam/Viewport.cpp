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

void Viewport::render() {

}

void Viewport::renderGeometry() {
	glm::mat4 projection = camera->getProjectionMatrix((float)_size.x / (float)_size.y, 0.1f, 1000.0f);
	glm::mat4 view = camera->getViewMatrix();

	for (Renderable*& renderable : scene->getRenderables()) {
		renderable->render(projection, view);
	}
}

void Viewport::renderLighting() {
	Shader* _lightingShader = &(this->_lightingShader);
	_lightingShader->use();

	_lightingShader->setInt("gPosition", 0);
	_lightingShader->setInt("gNormal", 1);
	_lightingShader->setInt("gColorSpec", 2);

	unsigned int numSpotLights = 0;
	unsigned int numPointLights = 0;
	unsigned int numDirLights = 0;
	std::vector<Light*> lights = scene->getLights();
	for (size_t i = 0; i < lights.size(); i++) {

		SpotLight* sl = dynamic_cast<SpotLight*>(lights[i]);
		if (sl != nullptr) {

			numSpotLights++;
			continue;
		}

		PointLight* pl = dynamic_cast<PointLight*>(lights[i]);
		if (pl != nullptr) {
			_lightingShader->setVec3("pointLights[" + std::to_string(numPointLights) + "].ambient", pl->ambient);
			_lightingShader->setVec3("pointLights[" + std::to_string(numPointLights) + "].diffuse", pl->diffuse);
			_lightingShader->setVec3("pointLights[" + std::to_string(numPointLights) + "].specular", pl->specular);

			_lightingShader->setVec3("pointLights[" + std::to_string(numPointLights) + "].position", pl->position);

			_lightingShader->setFloat("pointLights[" + std::to_string(numPointLights) + "].constant", pl->constant);
			_lightingShader->setFloat("pointLights[" + std::to_string(numPointLights) + "].linear", pl->linear);
			_lightingShader->setFloat("pointLights[" + std::to_string(numPointLights) + "].quadratic", pl->quadratic);
			numPointLights++;
			continue;
		}

		DirectionalLight* dl = dynamic_cast<DirectionalLight*>(lights[i]);
		if (dl != nullptr) {
			_lightingShader->setVec3("directionalLights[" + std::to_string(numDirLights) + "].ambient", dl->ambient);
			_lightingShader->setVec3("directionalLights[" + std::to_string(numDirLights) + "].diffuse", dl->diffuse);
			_lightingShader->setVec3("directionalLights[" + std::to_string(numDirLights) + "].specular", dl->specular);

			_lightingShader->setVec3("directionalLights[" + std::to_string(numDirLights) + "].direction", dl->direction);
			numDirLights++;
			continue;
		}
	}
	_lightingShader->setVec3("viewPos", camera->transform.getPosition());

	_lightingShader->setInt("numSpotLights", numSpotLights);
	_lightingShader->setInt("numPointLights", numPointLights);
	_lightingShader->setInt("numDirectionalLights", numDirLights);
}