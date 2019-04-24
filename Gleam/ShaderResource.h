#pragma once

#include <glad/glad.h>

#include <glm/glm.hpp>

#include <ctype.h>
#include <string>
#include <fstream>
#include <sstream>
#include <iostream>
#include <unordered_map>

/* all types gleam allows to be used in shader uniforms */
enum class GleamType : uint8_t {
	BOOL, FLOAT, INT, UNSIGNED,
	BVEC2, BVEC3, BVEC4,
	IVEC2, IVEC3, IVEC4,
	UVEC2, UVEC3, UVEC4,
	VEC2, VEC3, VEC4,
	MAT2, MAT3, MAT4
};
/* union of all GleamTypes */
union UniformType {
	bool bool_value;
	float float_value;
	int int_value;
	unsigned unsigned_value;
	glm::vec<2, bool>* bvec2_value;
	glm::vec<3, bool>* bvec3_value;
	glm::vec<4, bool>* bvec4_value;
	glm::vec<2, int>* ivec2_value;
	glm::vec<3, int>* ivec3_value;
	glm::vec<4, int>* ivec4_value;
	glm::vec<2, unsigned>* uvec2_value;
	glm::vec<3, unsigned>* uvec3_value;
	glm::vec<4, unsigned>* uvec4_value;
	glm::vec<2, float>* vec2_value;
	glm::vec<3, float>* vec3_value;
	glm::vec<4, float>* vec4_value;
	glm::mat2* mat2_value;
	glm::mat3* mat3_value;
	glm::mat4* mat4_value;
	void* void_value;
};

struct GleamUniform {
	~GleamUniform() {
		if (type > GleamType::UNSIGNED) {
			delete data.void_value;
		}
	}
	UniformType data;
	GleamType type;
};

class ShaderResource {
protected:
	std::unordered_map<std::string, GleamUniform> _uniformTable;

public:
	std::unordered_map<std::string, GleamUniform>::const_iterator begin();
	std::unordered_map<std::string, GleamUniform>::const_iterator end();

	void remove(const std::string& name);

	void setBool(const std::string& name, bool value);
	void setFloat(const std::string& name, float value);
	void setInt(const std::string& name, int value);
	void setUnsigned(const std::string& name, unsigned value);

	void setVec2(const std::string& name, const glm::vec<2, bool>& value);
	void setVec2(const std::string& name, bool v1, bool v2);
	void setVec3(const std::string& name, const glm::vec<3, bool>& value);
	void setVec3(const std::string& name, bool v1, bool v2, bool v3);
	void setVec4(const std::string& name, const glm::vec<4, bool>& value);
	void setVec4(const std::string& name, bool v1, bool v2, bool v3, bool v4);

	void setVec2(const std::string& name, const glm::vec<2, float>& value);
	void setVec2(const std::string& name, float v1, float v2);
	void setVec3(const std::string& name, const glm::vec<3, float>& value);
	void setVec3(const std::string& name, float v1, float v2, float v3);
	void setVec4(const std::string& name, const glm::vec<4, float>& value);
	void setVec4(const std::string& name, float v1, float v2, float v3, float v4);

	void setVec2(const std::string& name, const glm::vec<2, int>& value);
	void setVec2(const std::string& name, int v1, int v2);
	void setVec3(const std::string& name, const glm::vec<3, int>& value);
	void setVec3(const std::string& name, int v1, int v2, int v3);
	void setVec4(const std::string& name, const glm::vec<4, int>& value);
	void setVec4(const std::string& name, int v1, int v2, int v3, int v4);

	void setVec2(const std::string& name, const glm::vec<2, unsigned>& value);
	void setVec2(const std::string& name, unsigned v1, unsigned v2);
	void setVec3(const std::string& name, const glm::vec<3, unsigned>& value);
	void setVec3(const std::string& name, unsigned v1, unsigned v2, unsigned v3);
	void setVec4(const std::string& name, const glm::vec<4, unsigned>& value);
	void setVec4(const std::string& name, unsigned v1, unsigned v2, unsigned v3, unsigned v4);

	void setMat2(const std::string& name, const glm::mat2& value);
	void setMat3(const std::string& name, const glm::mat3& value);
	void setMat4(const std::string& name, const glm::mat4& value);
};
