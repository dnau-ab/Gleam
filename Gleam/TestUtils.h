#pragma once

#define GLM_ENABLE_EXPERIMENTAL

#include <glm/glm.hpp>
#include <glm/gtx/quaternion.hpp>

#include <iostream>
#include <iomanip>
#include <assert.h>

#include "Window.h"
#include "Viewport.h"
#include "Transform.h"
#include "Scene.h"
#include "ShaderResource.h"

#include "DirectionalLight.h"
#include "PointLight.h"
#include "SpotLight.h"

#include "Model.h"

using std::cout;
using std::endl;

void _print(glm::vec3 v);
void _print(glm::vec4 v);
void _print(glm::mat4 m);
void _print(glm::quat q);

bool _approxEqual(double a, double b);

void testWindow();
void testTransform();
void testTexture();
void testMeshLoader();
void testModel();
void testScene();
void testShaderResource();

