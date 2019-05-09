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

#include <glm/glm.hpp>

class Viewport {
protected:
	glm::vec2 _position;
	glm::vec2 _size;
	Shader _lightingShader;

	unsigned int _gBuffer = 0;
	unsigned int _gPosition = 0;
	unsigned int _gNormal = 0;
	unsigned int _gColorSpec = 0;

public:
	Scene* scene = nullptr;
	Camera* camera = nullptr;

	Viewport(float x, float y, float width, float height)
		: _position(glm::vec2(x, y)), _size(glm::vec2(width, height)), _lightingShader("res/shaders/gleam_default_shader_def_lighting.vert", "res/shaders/gleam_default_shader_def_lighting.frag") {
	}

	Viewport(glm::vec2 pos, glm::vec2 size)
		: _position(pos), _size(size), _lightingShader("res/shaders/gleam_default_shader_def_lighting.vert", "res/shaders/gleam_default_shader_def_lighting.frag") {
	}

	glm::vec2 getPosition();
	glm::vec2 getSize();

	void setPosition(glm::vec2 position);
	void setSize(glm::vec2 size);

	void render();
	void renderGeometry(float aspectRatio);
	void renderLighting();
};