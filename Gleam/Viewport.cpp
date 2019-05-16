#include "Viewport.h"

glm::vec2 Viewport::getPosition() {
	return _position;
}

glm::vec2 Viewport::getSize() {
	return _size;
}

void Viewport::setPosition(glm::vec2 position) {
	_position = position;
}

void Viewport::setSize(glm::vec2 size) {
	_size = size;
}

Shader* Viewport::getLightingShader() {
	return &_lightingShader;
}

void Viewport::setLightingShader(Shader* shader) {
	_lightingShader = *shader;
}

Skybox* Viewport::getSkybox() {
	return _skybox;
}

void Viewport::setSkybox(Skybox* skybox) {
	_skybox = skybox;
}

void Viewport::renderSkybox(glm::vec2 renderSize) {

	glm::vec4 dimensions = getDimensions(renderSize);

	glViewport(dimensions.x, dimensions.y, dimensions.z, dimensions.w);
	glScissor(dimensions.x, dimensions.y, dimensions.z, dimensions.w);

	float aspectRatio = (float)dimensions.z / dimensions.w;

	glm::mat4 projection = camera->getProjectionMatrix(aspectRatio, camera->getNearPlane(), camera->getFarPlane());
	glm::mat4 view = camera->getViewMatrix();
	
	glStencilMask(0x00);
	glStencilFunc(GL_ALWAYS, 1, 0xFF);
	if (_skybox != nullptr) {
		_skybox->render(projection, view);
	}
}

void Viewport::renderGeometry(glm::vec2 renderSize) {
	glm::vec4 dimensions = getDimensions(renderSize);

	glViewport(dimensions.x, dimensions.y, dimensions.z, dimensions.w);
	glScissor(dimensions.x, dimensions.y, dimensions.z, dimensions.w);

	float aspectRatio = (float)dimensions.z / dimensions.w;

	glm::mat4 projection = camera->getProjectionMatrix(aspectRatio, camera->getNearPlane(), camera->getFarPlane());
	glm::mat4 view = camera->getViewMatrix();

	glStencilMask(0xFF);
	glStencilFunc(GL_ALWAYS, 1, 0xFF);
	for (Renderable*& renderable : scene->getRenderables()) {
		renderable->render(projection, view);
	}

}

void Viewport::renderLighting(glm::vec2 renderSize) {
	glm::vec4 dimensions = getDimensions(renderSize);

	glScissor(dimensions.x, dimensions.y, dimensions.z, dimensions.w);

	Shader* _lightingShader = &(this->_lightingShader);
	_lightingShader->use();

	_lightingShader->setInt("gPosition", 0);
	_lightingShader->setInt("gNormal", 1);
	_lightingShader->setInt("gColorSpec", 2);

	_lightingShader->setVec2("viewportSize", _size);
	_lightingShader->setVec2("viewportPosition", _position);

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
			float maxBrightness = std::fmaxf(std::fmaxf(pl->diffuse.r, pl->diffuse.g), pl->diffuse.b);
			float radius = (-pl->linear + std::sqrt(pl->linear * pl->linear - 4 * pl->quadratic * (pl->constant - (256.0f / 5.0f) * maxBrightness))) / (2.0f * pl->quadratic);
			_lightingShader->setVec3("pointLights[" + std::to_string(numPointLights) + "].ambient", pl->ambient);
			_lightingShader->setVec3("pointLights[" + std::to_string(numPointLights) + "].diffuse", pl->diffuse);
			_lightingShader->setVec3("pointLights[" + std::to_string(numPointLights) + "].specular", pl->specular);

			_lightingShader->setVec3("pointLights[" + std::to_string(numPointLights) + "].position", pl->position);

			_lightingShader->setFloat("pointLights[" + std::to_string(numPointLights) + "].constant", pl->constant);
			_lightingShader->setFloat("pointLights[" + std::to_string(numPointLights) + "].linear", pl->linear);
			_lightingShader->setFloat("pointLights[" + std::to_string(numPointLights) + "].quadratic", pl->quadratic);
			_lightingShader->setFloat("pointLights[" + std::to_string(numPointLights) + "].radius", radius);
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