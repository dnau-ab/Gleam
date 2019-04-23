#pragma once

#define GLM_ENABLE_EXPERIMENTAL

#include <glm/vec3.hpp>
#include <glm/gtc/quaternion.hpp>
#include <glm/mat3x3.hpp>

#include <glm/gtx/quaternion.hpp>
#include <glm/gtx/matrix_decompose.hpp>
#include <glm/gtx/euler_angles.hpp>

class Transform {
private:
	glm::vec3 _position;
	glm::quat _rotation;
	glm::vec3 _scale;

public:
	Transform(const glm::vec3& position = glm::vec3(0.0f, 0.0f, 0.0f), const glm::quat& rotation = glm::quat(1.0f, 0.0f, 0.0f, 0.0f), const glm::vec3& scale = glm::vec3(1.0f, 1.0f, 1.0f));

	Transform(const Transform& transform);
	void operator=(const Transform& transform);
	
	void translate(const glm::vec3& direction);
	void scale(const glm::vec3& amount);
	void rotate(const glm::quat& quaternion);
	void rotate(const glm::vec3& euler);
	
	void lookAt(const glm::vec3& target, const glm::vec3& up = glm::vec3(0.0f, 1.0f, 0.0f));

	glm::vec3 getPosition() const;
	glm::vec3 toEuler() const;
	glm::quat getRotation() const;
	glm::vec3 getScale() const;

	glm::mat4 getTransformationMatrix() const;

	void setPosition(const glm::vec3& position);
	void setRotation(const glm::vec3& euler);
	void setRotation(const glm::quat& quaternion);
	void setScale(const glm::vec3& scale);
};