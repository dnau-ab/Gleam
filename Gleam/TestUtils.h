#pragma once

#define GLM_ENABLE_EXPERIMENTAL

#include <glm/glm.hpp>
#include <glm/gtx/quaternion.hpp>

#include <iostream>
#include <iomanip>
#include <assert.h>

#include "Window.h"
#include "Texture.h"
#include "Transform.h"

using std::cout;
using std::endl;

void _print(glm::vec3 v);
void _print(glm::vec4 v);
void _print(glm::mat4 m);
void _print(glm::quat q);

void testTransforms();
void testTexture();