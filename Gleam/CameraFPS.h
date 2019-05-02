#pragma once
#include "Camera.h"

class CameraFPS : public Camera{
private:
	static constexpr float SPEED = 2.5f;
	static constexpr float SENSITIVITY = 0.1f;
	static constexpr float ZOOM = 45.0f;

	// Calculates the front vector from the Camera's (updated) Euler Angles
	void updateCameraVectors();

public:
	CameraFPS(glm::vec3 position = glm::vec3(0.0f, 0.0f, 0.0f), glm::vec3 worldUp = glm::vec3(0.0f, 1.0f, 0.0f),
		float movementSpeed = SPEED, float sensitivity = SENSITIVITY, float zoom = ZOOM)
		: Camera(position), movementSpeed(movementSpeed), mouseSensitivity(mouseSensitivity), zoom(zoom) {}
	
	CameraFPS(float posX, float posY, float posZ, float worldUpX, float worldUpY, float worldUpZ,
		float movementSpeed = SPEED, float sensitivity = SENSITIVITY, float zoom = ZOOM)
		: Camera(posX, posY, posZ, worldUpX, worldUpY, worldUpZ), movementSpeed(movementSpeed), mouseSensitivity(mouseSensitivity), zoom(zoom) {}
	
	glm::mat4 getViewMatrix() override;
	glm::mat4 getProjectionMatrix(float aspectRatio, float nearPlane, float farPlane) override;

	void ProcessKeyboard(Camera_Movement direction, float deltaTime);
	void ProcessMouseMovement(float xoffset, float yoffset);
	void ProcessMouseScroll(float yoffset);
	
	// Camera options
	float movementSpeed;
	float mouseSensitivity;
	float zoom;
};