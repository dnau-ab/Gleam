#include "Camera.h"

void Camera::setMovement(Camera_Movement movement) {
	movementVector |= movement;
}

void Camera::unsetMovement(Camera_Movement movement) {
	movementVector &= ~movement;
}

bool Camera::isMovementSet(Camera_Movement movement) {
	return movementVector & movement;
}