#pragma once

#include <glad/glad.h>
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>

#define GLM_ENABLE_EXPERIMENTAL
#include <glm/gtx/quaternion.hpp>
#include <glm/gtc/quaternion.hpp>

#include <vector>

#include "Transform.h"

const float DEFAULT_NEAR_PLANE = 0.5f;
const float DEFAULT_FAR_PLANE = 1000.0f;

enum class CameraMovement {
	NONE = 0,
	FORWARD = 1,
	BACKWARD = 2,
	LEFT = 4,
	RIGHT = 8,
	UP = 16,
	DOWN = 32,
	ROLL_LEFT = 64,
	ROLL_RIGHT = 128
};

class Camera {
private:
	float _nearPlane;
	float _farPlane;
protected:
	Camera(glm::vec3 position = glm::vec3(0.0f, 0.0f, 0.0f), 
		glm::vec3 rotation = glm::vec3(0.0f, 0.0f, 0.0f), 
		glm::vec3 worldUp = glm::vec3(0.0f, 1.0f, 0.0f), 
		float nearPlane = DEFAULT_NEAR_PLANE, float farPlane = DEFAULT_FAR_PLANE)
		: transform(position, rotation), worldUp(worldUp), up(worldUp), front(0.0f, 0.0f, -1.0f), _nearPlane(nearPlane), _farPlane(farPlane), movementVector((uint8_t)CameraMovement::NONE) {}

	Camera(float posX, float posY, float posZ, 
		float rotX, float rotY, float rotZ,
		float worldUpX, float worldUpY, float worldUpZ,
		float nearPlane = DEFAULT_NEAR_PLANE, float farPlane = DEFAULT_FAR_PLANE)
		: transform(glm::vec3(posX, posY, posZ), glm::vec3(rotX, rotY, rotZ)), worldUp(worldUpX, worldUpY, worldUpZ), up(worldUpX, worldUpY, worldUpZ), front(0.0f, 0.0f, -1.0f), _nearPlane(nearPlane), _farPlane(farPlane), movementVector((uint8_t)CameraMovement::NONE) {}

	virtual void updateCameraVectors() = 0;
	uint8_t movementVector;
public:
	Transform transform;
	glm::vec3 front;
	glm::vec3 up;
	glm::vec3 right;
	glm::vec3 worldUp;

	virtual glm::mat4 getViewMatrix() = 0;
	virtual glm::mat4 getProjectionMatrix(float aspectRatio, float nearPlane, float farPlane) = 0;

	float getNearPlane() {
		return _nearPlane;
	}

	void setNearPlane(float nearPlane) {
		_nearPlane = nearPlane;
	}

	float getFarPlane() {
		return _farPlane;
	}

	void setFarPlane(float farPlane) {
		_farPlane = farPlane;
	}

	void setMovement(CameraMovement movement);
	void unsetMovement(CameraMovement movement);
	bool isMovementSet(CameraMovement movement);

	virtual void update(float deltaTime) = 0;
};