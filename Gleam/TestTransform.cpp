#include "TestUtils.h"

void testTransforms() {
	Transform t1;
	Transform t2(glm::vec3(10.0f, -10.0f, 0.0f));
	Transform t3(glm::vec3(0.0f, 0.0f, 100.0f), glm::quat(glm::vec3(0.3, 0.2f, 0.0f)));
	Transform t4(glm::vec3(100.0f, 0.0f, 0.0f), glm::quat(glm::vec3(0.0f, 0.0f, 0.0f)), glm::vec3(1.0f, 3.0f, 1.0f));

	cout << "T1: ";
	_print(t1.getTransformationMatrix());
	cout << "T2: ";
	_print(t2.getTransformationMatrix());
	cout << "T3: ";
	_print(t3.getTransformationMatrix());
	cout << "T4: ";
	_print(t4.getTransformationMatrix());

	t1.rotate(glm::vec3(glm::radians(90.0f), 0.0f, 0.0f));
	cout << "T1 rot 90 x: ";
	_print(t1.getTransformationMatrix());
	t1.scale(glm::vec3(1.0f, 2.0f, 3.0f));
	cout << "T1 scale 1,2,3 : ";
	_print(t1.getTransformationMatrix());

	cout << "P, R(Q), R(E), S:\n";
	_print(t1.getPosition());
	_print(t1.getRotation());
	_print(t1.toEuler());
	_print(t1.getScale());

	t1.translate(glm::vec3(15.0f, -15.0f, 45.0f));
	t1.rotate(glm::vec3(0.0f, glm::radians(93.2f), 0.0f));

	cout << "P, R(Q), R(E), S:\n";
	_print(t1.getPosition());
	_print(t1.getRotation());
	_print(t1.toEuler());
	_print(t1.getScale());

	Transform t5;
	t5.rotate(glm::vec3(-1.570796, -1.514946, 3.141593));

	cout << "P, R(Q), R(E), S:\n";
	_print(t1.getPosition());
	_print(t1.getRotation());
	_print(t1.toEuler());
	_print(t1.getScale());
}