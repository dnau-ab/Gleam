#include "TestUtils.h"

void testShaderResource(){
	glm::mat4 mat(1.0f);

	ShaderResource resource;
	resource.setFloat("float1", 2.5f);
	resource.setVec2("vecA", glm::vec2(2.5f, 3.0f));

	for (int i = 0; i < 1000; i++) {
		resource.setMat4("mat4_" + std::to_string(i), mat);
	}

	for (auto itr = resource.begin(); itr != resource.end(); itr++) {
		//cout << itr->first << " " << (int)itr->second.type << endl;
	}

	for (int i = 0; i < 1000; i++) {
		resource.remove("mat4_" + std::to_string(i));
	}

	for (auto itr = resource.begin(); itr != resource.end(); itr++) {
		cout << itr->first << (int)itr->second.type << endl;
	}
}