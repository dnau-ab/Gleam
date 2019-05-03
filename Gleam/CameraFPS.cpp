#include "CameraFPS.h"

void CameraFPS::updateCameraVectors()
{
	// Calculate the new Front vector
	front = glm::normalize(transform.getRotation() * glm::vec3(0, 0, -1));
	right = glm::normalize(glm::cross(front, worldUp));
	up = glm::normalize(glm::cross(right, front));
}

// Processes input received from any keyboard-like input system. Accepts input parameter in the form of camera defined ENUM (to abstract it from windowing systems)
void CameraFPS::processKeyboard(Camera_Movement direction, float deltaTime)
{
	float velocity = movementSpeed * deltaTime;
	//printf("DIR: %f\nV: %f\nMVS: %f\nDT: %f\n\n", front * velocity, velocity, movementSpeed, deltaTime);
	if (direction == FORWARD) {
		transform.translate(front * velocity);
	}
	if (direction == BACKWARD) {
		transform.translate(-(front * velocity));
	}
	if (direction == LEFT) {
		transform.translate(-(right * velocity));
	}
	if (direction == RIGHT) {
		transform.translate(right * velocity);
	}
	if (direction == UP) {
		transform.translate(up * velocity);
	}
	if (direction == DOWN) {
		transform.translate(-(up * velocity));
	}
}

// Processes input received from a mouse input system. Expects the offset value in both the x and y direction.
void CameraFPS::processMouseMovement(float xoffset, float yoffset)
{
	xoffset *= mouseSensitivity;
	yoffset *= mouseSensitivity;

	transform.rotate(glm::vec3(xoffset, yoffset, 0.0f));

	// Make sure that when pitch is out of bounds, screen doesn't get flipped
	/*
	glm::vec3 euler = transform.toEuler();
	euler.x = glm::mod(euler.x, 360.0f);
	if (euler.y > 89.0f)
		transform.setRotation(glm::vec3(euler.x, 89.0f, euler.z));
	if (euler.y < -89.0f)
		transform.setRotation(glm::vec3(euler.x, -89.0f, euler.z));
	*/
	// Update Front, Right and Up Vectors using the updated Euler angles
	updateCameraVectors();
}

// Processes input received from a mouse scroll-wheel event. Only requires input on the vertical wheel-axis
void CameraFPS::processMouseScroll(float yoffset)
{
	if (zoom >= 1.0f && zoom <= 45.0f)
		zoom -= yoffset;
	if (zoom <= 1.0f)
		zoom = 1.0f;
	if (zoom >= 45.0f)
		zoom = 45.0f;
}

glm::mat4 CameraFPS::getViewMatrix() {
	updateCameraVectors();
	glm::vec3 position = transform.getPosition();
	return glm::lookAt(position, position + front, up);
}

glm::mat4 CameraFPS::getProjectionMatrix(float aspectRatio, float nearPlane, float farPlane) {
	return glm::perspective(glm::radians(zoom), aspectRatio, nearPlane, farPlane);
}