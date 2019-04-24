
#include "TestUtils.h"

void _print(glm::vec3 v) {
	printf("<%f, %f, %f>\n", v.x, v.y, v.z);
}

void _print(glm::vec4 v) {
	printf("<%f, %f, %f, %f>\n", v.x, v.y, v.z, v.w);
}

void _print(glm::mat4 m) {
	cout << endl;
	for (int i = 0; i < 4; i++) {
		cout << '|';
		for (int j = 0; j < 4; j++) {
			if (j == 0)
				cout << std::setw(10) << m[i][j];
			else
				cout << ", " << std::setw(12) << m[i][j];
		}
		cout << "|\n";
	}
	cout << endl;
}

void _print(glm::quat q) {
	printf("<%f, %f, %f, %f>\n", q.x, q.y, q.z, q.w);
}


bool _approxEqual(double a, double b) {
	return (std::abs(a - b) < 0.01);
}