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
	glm::vec<2, int> _position;
	glm::vec<2, unsigned> _size;
	Shader _lightingShader;

public:
	Scene* scene = nullptr;
	Camera* camera = nullptr;

	Viewport(int x, int y, unsigned width, unsigned height)
		: _position(glm::vec<2, int>(x, y)), _size(glm::vec<2, unsigned>(width, height)), _lightingShader("res/shaders/gleam_default_shader_def_lighting.vert", "res/shaders/gleam_default_shader_def_lighting.frag") {
	}

	Viewport(glm::vec2 pos, glm::vec2 size)
		: _position(pos), _size(size), _lightingShader("res/shaders/gleam_default_shader_def_lighting.vert", "res/shaders/gleam_default_shader_def_lighting.frag") {
	}

	glm::vec2 getPosition();
	glm::vec2 getSize();

	void setPosition(glm::vec<2, int> position);
	void setSize(glm::vec<2, unsigned> size);

	void render();
	void renderGeometry();
	void renderLighting();
};