#include "Transform.h"


Transform::Transform(const glm::vec3& position, const glm::quat& rotation, const glm::vec3& scale)
	: _position(position), _rotation(rotation), _scale(scale) { }

Transform::Transform(const Transform& transform) {
	_position = transform._position;
	_rotation = transform._rotation;
	_scale = transform._scale;
}

void Transform::operator=(const Transform& transform) {
	_position = transform._position;
	_rotation = transform._rotation;
	_scale = transform._scale;
}

void Transform::translate(const glm::vec3& direction) {
	_position += direction;
}

void Transform::scale(const glm::vec3& amount) {
	_scale *= amount;
}

void Transform::rotate(const glm::quat& quaternion) {
	_rotation *= quaternion;
}

void Transform::rotate(const glm::vec3& euler) {
	_rotation *= glm::quat(glm::radians(euler));
}

void Transform::lookAt(const glm::vec3& target, const glm::vec3& up) {
	_rotation = glm::lookAt(_position, target, up);
}

glm::vec3 Transform::getPosition() const {
	return _position;
}

glm::vec3 Transform::toEuler() const {
	return glm::eulerAngles(_rotation);
}

glm::quat Transform::getRotation() const {
	return _rotation;
}

glm::vec3 Transform::getScale() const {
	return _scale;
}

glm::mat4 Transform::getTransformationMatrix() const {
	glm::mat4 transform(1.0f);
	transform = glm::translate(transform, _position);
	transform = glm::rotate(transform, glm::angle(_rotation), glm::axis(_rotation));
	transform = glm::scale(transform, _scale);
	return transform;
}

void Transform::setPosition(const glm::vec3& position) {
	_position = position;
}

void Transform::setRotation(const glm::vec3& euler) {
	_rotation = glm::quat(glm::radians(euler));
}

void Transform::setRotation(const glm::quat& quaternion) {
	_rotation = quaternion;
}

void Transform::setScale(const glm::vec3& scale) {
	_scale = scale;
}

