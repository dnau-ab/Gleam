#pragma once

#include <algorithm>

#include <glm/glm.hpp>
#include <glm/vec2.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>

#include <string>

#include "Camera.h"
#include "Model.h"
#include "Scene.h"
#include "Shader.h"

#include "PointLight.h"
#include "DirectionalLight.h"
#include "SpotLight.h"

#include "Skybox.h"

#include <glm/glm.hpp>

class Viewport {
private:
	glm::vec4 getDimensions(glm::vec2 renderSize) {
		glm::vec<4, int> dimensions;
		dimensions.x = (int)(_position.x * renderSize.x);
		dimensions.y = (int)(_position.y * renderSize.y);
		dimensions.z = (int)(_size.x * renderSize.x);
		dimensions.w = (int)(_size.y * renderSize.y);
		return dimensions;
	}

protected:
	glm::vec2 _position;
	glm::vec2 _size;
	Shader* _lightingShader;
	ShaderResource* _shaderResource;

	Skybox* _skybox;

	unsigned int _gBuffer = 0;
	unsigned int _gPosition = 0;
	unsigned int _gNormal = 0;
	unsigned int _gColorSpec = 0;

public:
	Scene* scene = nullptr;
	Camera* camera = nullptr;

	Viewport(float x, float y, float width, float height)
		: _position(glm::vec2(x, y)), _size(glm::vec2(width, height)), _lightingShader(Shader::getDefaultLighting()) {
	}

	Viewport(glm::vec2 pos, glm::vec2 size)
		: _position(pos), _size(size), _lightingShader(Shader::getDefaultLighting()) {
	}

	glm::vec2 getPosition();
	glm::vec2 getSize();

	void setPosition(glm::vec2 position);
	void setSize(glm::vec2 size);

	Skybox* getSkybox();
	void setSkybox(Skybox* skybox);

	Shader* getLightingShader();
	void setLightingShader(Shader* shader);

	void setResource(ShaderResource* resource);
	void updateResource();

	void renderSkybox(glm::vec2 renderSize);
	void renderGeometry(glm::vec2 renderSize);
	void renderLighting(glm::vec2 renderSize);
};