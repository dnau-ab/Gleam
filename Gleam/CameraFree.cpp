#include "CameraFree.h"

void CameraFree::updateCameraVectors()
{
	// Calculate the new Front vector
	front = glm::normalize(glm::inverse(transform.getRotation()) * glm::vec3(0, 0, -1));
	up = glm::normalize(glm::inverse(transform.getRotation()) * worldUp);
	right = glm::normalize(glm::cross(front, up));
}

// Processes input received from any keyboard-like input system. Accepts input parameter in the form of camera defined ENUM (to abstract it from windowing systems)
void CameraFree::processKeyboard(Camera_Movement direction, float deltaTime)
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
	if (direction == ROLL_LEFT) {
		glm::quat rollQuat = glm::angleAxis(200 * mouseSensitivity * deltaTime, glm::vec3(0.0f, 0.0f, 1.0f));
		glm::quat keyQuat = rollQuat * transform.getRotation();
		transform.setRotation(keyQuat);
		updateCameraVectors();
	}
	if (direction == ROLL_RIGHT) {
		glm::quat rollQuat = glm::angleAxis(-200 * mouseSensitivity * deltaTime, glm::vec3(0.0f, 0.0f, 1.0f));
		glm::quat keyQuat = rollQuat * transform.getRotation();
		transform.setRotation(keyQuat);
		updateCameraVectors();
	}
}

// Processes input received from a mouse input system. Expects the offset value in both the x and y direction.
void CameraFree::processMouseMovement(float xoffset, float yoffset)
{
	xoffset *= mouseSensitivity;
	yoffset *= mouseSensitivity;

	glm::quat pitchQuat = glm::angleAxis(yoffset, glm::vec3(1.0f, 0.0f, 0.0f));
	glm::quat yawQuat = glm::angleAxis(xoffset, glm::vec3(0.0f, 1.0f, 0.0f));

	glm::quat keyQuat = pitchQuat * yawQuat * transform.getRotation();
	transform.setRotation(glm::normalize(keyQuat));

	// Update Front, Right and Up Vectors using the updated Euler angles
	updateCameraVectors();	
}

// Processes input received from a mouse scroll-wheel event. Only requires input on the vertical wheel-axis
void CameraFree::processMouseScroll(float yoffset)
{
	if (zoom >= 1.0f && zoom <= 45.0f)
		zoom -= yoffset;
	if (zoom <= 1.0f)
		zoom = 1.0f;
	if (zoom >= 45.0f)
		zoom = 45.0f;
}

glm::mat4 CameraFree::getViewMatrix() {
	updateCameraVectors();
	//glm::vec3 position = transform.getPosition();
	//return glm::lookAt(position, position + front, up);
	glm::mat4 rotate = glm::mat4_cast(transform.getRotation());
	glm::mat4 translate = glm::mat4(1.0f);
	translate = glm::translate(translate, -transform.getPosition());

	return rotate * translate;
}

glm::mat4 CameraFree::getProjectionMatrix(float aspectRatio, float nearPlane, float farPlane) {
	return glm::perspective(glm::radians(zoom), aspectRatio, nearPlane, farPlane);
}