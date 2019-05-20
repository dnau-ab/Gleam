#include "Camera.h"

void Camera::setMovement(CameraMovement movement) {
	movementVector |= (uint8_t)movement;
}

void Camera::unsetMovement(CameraMovement movement) {
	movementVector &= ~(uint8_t)movement;
}

bool Camera::isMovementSet(CameraMovement movement) {
	return movementVector &(uint8_t)movement;
}