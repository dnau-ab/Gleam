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
	NONE = 0,
	FORWARD = 1,
	BACKWARD = 2,
	LEFT = 4,
	RIGHT = 8,
	UP = 16,
	DOWN = 32
};

class Camera {
private:
	virtual void updateCameraVectors() = 0;
protected:
	Camera(glm::vec3 position = glm::vec3(0.0f, 0.0f, 0.0f), glm::vec3 rotation = glm::vec3(0.0f, -90.0f, 0.0f), glm::vec3 worldUp = glm::vec3(0.0f, 1.0f, 0.0f))
		: transform(position, rotation), worldUp(worldUp), up(worldUp), front(0.0f, 0.0f, -1.0f) {}
	Camera(float posX, float posY, float posZ, 
		float rotX, float rotY, float rotZ,
		float worldUpX, float worldUpY, float worldUpZ)
		: transform(glm::vec3(posX, posY, posZ), glm::vec3(rotX, rotY, rotZ)), worldUp(worldUpX, worldUpY, worldUpZ), up(worldUpX, worldUpY, worldUpZ), front(0.0f, 0.0f, -1.0f) {}
public:
	Transform transform;
	glm::vec3 front;
	glm::vec3 up;
	glm::vec3 right;
	glm::vec3 worldUp;

	virtual glm::mat4 getViewMatrix() = 0;
	virtual glm::mat4 getProjectionMatrix(float aspectRatio, float nearPlane, float farPlane) = 0;
};