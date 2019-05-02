#pragma once

#include <glad/glad.h>
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>

#define GLM_ENABLE_EXPERIMENTAL
#include <glm/gtx/quaternion.hpp>
#include <glm/gtc/quaternion.hpp>

#include <vector>

#include "Transform.h"

enum Camera_Movement {
	FORWARD,
	BACKWARD,
	LEFT,
	RIGHT,
	UP,
	DOWN
};

class Camera {
private:
	virtual void updateCameraVectors() = 0;
protected:
	Camera(glm::vec3 position = glm::vec3(0.0f, 0.0f, 0.0f), glm::vec3 worldUp = glm::vec3(0.0f, 1.0f, 0.0f))
		: transform(position, worldUp), worldUp(worldUp) {}
	Camera(float posX, float posY, float posZ, float worldUpX, float worldUpY, float worldUpZ)
		: transform(glm::vec3(posX, posY, posZ)), worldUp(glm::vec3(worldUpX, worldUpY, worldUpZ)) {}
public:
	Transform transform;
	glm::vec3 front;
	glm::vec3 up;
	glm::vec3 right;
	glm::vec3 worldUp;

	virtual glm::mat4 getViewMatrix() = 0;
	virtual glm::mat4 getProjectionMatrix(float aspectRatio, float nearPlane, float farPlane) = 0;
};