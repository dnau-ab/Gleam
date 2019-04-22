#pragma once

#include <GLFW/glfw3.h>
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
private:
	glm::vec2 pos;
	glm::vec2 size;

public:
	Scene* scene = nullptr;
	Camera* camera = nullptr;

	Viewport(int x, int y, unsigned width, unsigned height);
	Viewport(glm::vec2 pos, glm::vec2 size);

	void render();
};