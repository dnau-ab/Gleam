#pragma once
#include "Camera.h"

class CameraFPS : public Camera{
private:
	static constexpr float SPEED = 12.5f;
	static constexpr float SENSITIVITY = 0.1f;
	static constexpr float ZOOM = 45.0f;

	// Calculates the front vector from the Camera's (updated) Euler Angles
	void updateCameraVectors();

public:
	CameraFPS(glm::vec3 position = glm::vec3(0.0f, 0.0f, 0.0f),
		glm::vec3 rotation = glm::vec3(0.0f, 0.0f, 0.0f),
		glm::vec3 worldUp = glm::vec3(0.0f, 1.0f, 0.0f), 
		float movementSpeed = SPEED, float sensitivity = SENSITIVITY, float zoom = ZOOM)
		: Camera(position, rotation, worldUp), movementSpeed(movementSpeed), mouseSensitivity(mouseSensitivity), zoom(zoom) {}
	
	CameraFPS(float posX, float posY, float posZ, 
		float rotX, float rotY, float rotZ,
		float worldUpX, float worldUpY, float worldUpZ, 
		float movementSpeed = SPEED, float sensitivity = SENSITIVITY, float zoom = ZOOM)
		: Camera(posX, posY, posZ, rotX, rotY, rotZ, worldUpX, worldUpY, worldUpZ), movementSpeed(movementSpeed), mouseSensitivity(mouseSensitivity), zoom(zoom) {}
	
	glm::mat4 getViewMatrix() override;
	glm::mat4 getProjectionMatrix(float aspectRatio, float nearPlane, float farPlane) override;

	void processKeyboard(Camera_Movement direction, float deltaTime);
	void processMouseMovement(float xoffset, float yoffset);
	void processMouseScroll(float yoffset);
	
	// Camera options
	float movementSpeed;
	float mouseSensitivity;
	float zoom;
};