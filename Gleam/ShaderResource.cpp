#include "ShaderResource.h"

std::unordered_map<std::string, GleamUniform>::const_iterator ShaderResource::begin() {
	return _uniformTable.cbegin();
}
std::unordered_map<std::string, GleamUniform>::const_iterator ShaderResource::end() {
	return _uniformTable.cend();
}

void ShaderResource::remove(const std::string& name) {
	_uniformTable.erase(name);
}

void ShaderResource::setBool(const std::string& name, bool value) {
	GleamUniform uniform;
	uniform.data.bool_value = value;
	uniform.type = GleamType::BOOL;
	_uniformTable[name] = uniform;
}
void ShaderResource::setFloat(const std::string& name, float value) {
	GleamUniform uniform;
	uniform.data.float_value = value;
	uniform.type = GleamType::FLOAT;
	_uniformTable[name] = uniform;
}
void ShaderResource::setInt(const std::string& name, int value) {
	GleamUniform uniform;
	uniform.data.int_value = value;
	uniform.type = GleamType::INT;
	_uniformTable[name] = uniform;
}
void ShaderResource::setUnsigned(const std::string& name, unsigned value) {
	GleamUniform uniform;
	uniform.data.unsigned_value = value;
	uniform.type = GleamType::UNSIGNED;
	_uniformTable[name] = uniform;
}

/* bool vectors */
void ShaderResource::setVec2(const std::string& name, const glm::vec<2, bool>& value) {
	auto itr = _uniformTable.find(name);
	if (itr == _uniformTable.end()) {
		GleamUniform uniform;
		uniform.data.bvec2_value = new glm::vec<2, bool>(value);
		uniform.type = GleamType::BVEC2;
		_uniformTable[name] = uniform;
	}
	else {
		*(itr->second.data.bvec2_value) = value;
		itr->second.type = GleamType::BVEC2;
	}
}
void ShaderResource::setVec2(const std::string& name, bool v1, bool v2) {
	auto itr = _uniformTable.find(name);
	if (itr == _uniformTable.end()) {
		GleamUniform uniform;
		uniform.data.bvec2_value = new glm::vec<2, bool>(v1, v2);
		uniform.type = GleamType::BVEC2;
		_uniformTable[name] = uniform;
	}
	else {
		*(itr->second.data.bvec2_value) = glm::vec<2, bool>(v1, v2);
		itr->second.type = GleamType::BVEC2;
	}
}
void ShaderResource::setVec3(const std::string& name, const glm::vec<3, bool>& value) {
	auto itr = _uniformTable.find(name);
	if (itr == _uniformTable.end()) {
		GleamUniform uniform;
		uniform.data.bvec3_value = new glm::vec<3, bool>(value);
		uniform.type = GleamType::BVEC3;
		_uniformTable[name] = uniform;
	}
	else {
		*(itr->second.data.bvec3_value) = value;
		itr->second.type = GleamType::BVEC3;
	}
}
void ShaderResource::setVec3(const std::string& name, bool v1, bool v2, bool v3) {
	auto itr = _uniformTable.find(name);
	if (itr == _uniformTable.end()) {
		GleamUniform uniform;
		uniform.data.bvec3_value = new glm::vec<3, bool>(v1, v2, v3);
		uniform.type = GleamType::BVEC3;
		_uniformTable[name] = uniform;
	}
	else {
		*(itr->second.data.bvec3_value) = glm::vec<3, bool>(v1, v2, v3);
		itr->second.type = GleamType::BVEC3;
	}
}
void ShaderResource::setVec4(const std::string& name, const glm::vec<4, bool>& value) {
	auto itr = _uniformTable.find(name);
	if (itr == _uniformTable.end()) {
		GleamUniform uniform;
		uniform.data.bvec4_value = new glm::vec<4, bool>(value);
		uniform.type = GleamType::BVEC4;
		_uniformTable[name] = uniform;
	}
	else {
		*(itr->second.data.bvec4_value) = value;
		itr->second.type = GleamType::BVEC4;
	}
}
void ShaderResource::setVec4(const std::string& name, bool v1, bool v2, bool v3, bool v4) {
	auto itr = _uniformTable.find(name);
	if (itr == _uniformTable.end()) {
		GleamUniform uniform;
		uniform.data.bvec4_value = new glm::vec<4, bool>(v1, v2, v3, v4);
		uniform.type = GleamType::BVEC4;
		_uniformTable[name] = uniform;
	}
	else {
		*(itr->second.data.bvec4_value) = glm::vec<4, bool>(v1, v2, v3, v4);
		itr->second.type = GleamType::BVEC4;
	}
}

/* float vectors */
void ShaderResource::setVec2(const std::string& name, const glm::vec<2, float>& value) {
	auto itr = _uniformTable.find(name);
	if (itr == _uniformTable.end()) {
		GleamUniform uniform;
		uniform.data.vec2_value = new glm::vec<2, float>(value);
		uniform.type = GleamType::VEC2;
		_uniformTable[name] = uniform;
	}
	else {
		*(itr->second.data.vec2_value) = value;
		itr->second.type = GleamType::BVEC4;
	}
}
void ShaderResource::setVec2(const std::string& name, float v1, float v2) {
	auto itr = _uniformTable.find(name);
	if (itr == _uniformTable.end()) {
		GleamUniform uniform;
		uniform.data.vec2_value = new glm::vec<2, float>(v1, v2);
		uniform.type = GleamType::VEC2;
		_uniformTable[name] = uniform;
	}
	else {
		*(itr->second.data.vec2_value) = glm::vec<2, float>(v1, v2);
		itr->second.type = GleamType::VEC2;
	}
}
void ShaderResource::setVec3(const std::string& name, const glm::vec<3, float>& value) {
	auto itr = _uniformTable.find(name);
	if (itr == _uniformTable.end()) {
		GleamUniform uniform;
		uniform.data.vec3_value = new glm::vec<3, float>(value);
		uniform.type = GleamType::VEC3;
		_uniformTable[name] = uniform;
	}
	else {
		*(itr->second.data.vec3_value) = value;
		itr->second.type = GleamType::VEC2;
	}
}
void ShaderResource::setVec3(const std::string& name, float v1, float v2, float v3) {
	auto itr = _uniformTable.find(name);
	if (itr == _uniformTable.end()) {
		GleamUniform uniform;
		uniform.data.vec3_value = new glm::vec<3, float>(v1, v2, v3);
		uniform.type = GleamType::VEC3;
		_uniformTable[name] = uniform;
	}
	else {
		*(itr->second.data.vec3_value) = glm::vec<3, float>(v1, v2, v3);
		itr->second.type = GleamType::VEC3;
	}
}
void ShaderResource::setVec4(const std::string& name, const glm::vec<4, float>& value) {
	auto itr = _uniformTable.find(name);
	if (itr == _uniformTable.end()) {
		GleamUniform uniform;
		uniform.data.vec4_value = new glm::vec<4, float>(value);
		uniform.type = GleamType::VEC4;
		_uniformTable[name] = uniform;
	}
	else {
		*(itr->second.data.vec4_value) = value;
		itr->second.type = GleamType::VEC4;
	}
}
void ShaderResource::setVec4(const std::string& name, float v1, float v2, float v3, float v4) {
	auto itr = _uniformTable.find(name);
	if (itr == _uniformTable.end()) {
		GleamUniform uniform;
		uniform.data.vec4_value = new glm::vec<4, float>(v1, v2, v3, v4);
		uniform.type = GleamType::VEC4;
		_uniformTable[name] = uniform;
	}
	else {
		*(itr->second.data.vec4_value) = glm::vec<4, float>(v1, v2, v3, v4);
		itr->second.type = GleamType::VEC4;
	}
}

/* int vectors */
void ShaderResource::setVec2(const std::string& name, const glm::vec<2, int>& value) {
	auto itr = _uniformTable.find(name);
	if (itr == _uniformTable.end()) {
		GleamUniform uniform;
		uniform.data.ivec2_value = new glm::vec<2, int>(value);
		uniform.type = GleamType::IVEC2;
		_uniformTable[name] = uniform;
	}
	else {
		*(itr->second.data.ivec2_value) = value;
		itr->second.type = GleamType::IVEC2;
	}
}
void ShaderResource::setVec2(const std::string& name, int v1, int v2) {
	auto itr = _uniformTable.find(name);
	if (itr == _uniformTable.end()) {
		GleamUniform uniform;
		uniform.data.ivec2_value = new glm::vec<2, int>(v1, v2);
		uniform.type = GleamType::IVEC2;
		_uniformTable[name] = uniform;
	}
	else {
		*(itr->second.data.ivec2_value) = glm::vec<2, int>(v1, v2);
		itr->second.type = GleamType::IVEC2;
	}
}
void ShaderResource::setVec3(const std::string& name, const glm::vec<3, int>& value) {
	auto itr = _uniformTable.find(name);
	if (itr == _uniformTable.end()) {
		GleamUniform uniform;
		uniform.data.ivec3_value = new glm::vec<3, int>(value);
		uniform.type = GleamType::IVEC3;
		_uniformTable[name] = uniform;
	}
	else {
		*(itr->second.data.ivec3_value) = value;
		itr->second.type = GleamType::IVEC3;
	}
}
void ShaderResource::setVec3(const std::string& name, int v1, int v2, int v3) {
	auto itr = _uniformTable.find(name);
	if (itr == _uniformTable.end()) {
		GleamUniform uniform;
		uniform.data.ivec3_value = new glm::vec<3, int>(v1, v2, v3);
		uniform.type = GleamType::IVEC3;
		_uniformTable[name] = uniform;
	}
	else {
		*(itr->second.data.ivec3_value) = glm::vec<3, int>(v1, v2, v3);
		itr->second.type = GleamType::IVEC3;
	}
}
void ShaderResource::setVec4(const std::string& name, const glm::vec<4, int>& value) {
	auto itr = _uniformTable.find(name);
	if (itr == _uniformTable.end()) {
		GleamUniform uniform;
		uniform.data.ivec4_value = new glm::vec<4, int>(value);
		uniform.type = GleamType::IVEC4;
		_uniformTable[name] = uniform;
	}
	else {
		*(itr->second.data.ivec4_value) = value;
		itr->second.type = GleamType::IVEC4;
	}
}
void ShaderResource::setVec4(const std::string& name, int v1, int v2, int v3, int v4) {
	auto itr = _uniformTable.find(name);
	if (itr == _uniformTable.end()) {
		GleamUniform uniform;
		uniform.data.ivec4_value = new glm::vec<4, int>(v1, v2, v3, v4);
		uniform.type = GleamType::IVEC4;
		_uniformTable[name] = uniform;
	}
	else {
		*(itr->second.data.ivec4_value) = glm::vec<4, int>(v1, v2, v3, v4);
		itr->second.type = GleamType::IVEC4;
	}
}

/* unsigned vectors */
void ShaderResource::setVec2(const std::string& name, const glm::vec<2, unsigned>& value) {
	auto itr = _uniformTable.find(name);
	if (itr == _uniformTable.end()) {
		GleamUniform uniform;
		uniform.data.uvec2_value = new glm::vec<2, unsigned>(value);
		uniform.type = GleamType::UVEC2;
		_uniformTable[name] = uniform;
	}
	else {
		*(itr->second.data.uvec2_value) = value;
		itr->second.type = GleamType::UVEC2;
	}
}
void ShaderResource::setVec2(const std::string& name, unsigned v1, unsigned v2) {
	auto itr = _uniformTable.find(name);
	if (itr == _uniformTable.end()) {
		GleamUniform uniform;
		uniform.data.uvec2_value = new glm::vec<2, unsigned>(v1, v2);
		uniform.type = GleamType::UVEC2;
		_uniformTable[name] = uniform;
	}
	else {
		*(itr->second.data.uvec2_value) = glm::vec<2, unsigned>(v1, v2);
		itr->second.type = GleamType::UVEC2;
	}
}
void ShaderResource::setVec3(const std::string& name, const glm::vec<3, unsigned>& value) {
	auto itr = _uniformTable.find(name);
	if (itr == _uniformTable.end()) {
		GleamUniform uniform;
		uniform.data.uvec3_value = new glm::vec<3, unsigned>(value);
		uniform.type = GleamType::UVEC3;
		_uniformTable[name] = uniform;
	}
	else {
		*(itr->second.data.uvec3_value) = value;
		itr->second.type = GleamType::UVEC3;
	}
}
void ShaderResource::setVec3(const std::string& name, unsigned v1, unsigned v2, unsigned v3) {
	auto itr = _uniformTable.find(name);
	if (itr == _uniformTable.end()) {
		GleamUniform uniform;
		uniform.data.uvec3_value = new glm::vec<3, unsigned>(v1, v2, v3);
		uniform.type = GleamType::UVEC3;
		_uniformTable[name] = uniform;
	}
	else {
		*(itr->second.data.uvec3_value) = glm::vec<3, unsigned>(v1, v2, v3);
		itr->second.type = GleamType::UVEC3;
	}
}
void ShaderResource::setVec4(const std::string& name, const glm::vec<4, unsigned>& value) {
	auto itr = _uniformTable.find(name);
	if (itr == _uniformTable.end()) {
		GleamUniform uniform;
		uniform.data.uvec4_value = new glm::vec<4, unsigned>(value);
		uniform.type = GleamType::UVEC4;
		_uniformTable[name] = uniform;
	}
	else {
		*(itr->second.data.uvec4_value) = value;
		itr->second.type = GleamType::UVEC4;
	}
}
void ShaderResource::setVec4(const std::string& name, unsigned v1, unsigned v2, unsigned v3, unsigned v4) {
	auto itr = _uniformTable.find(name);
	if (itr == _uniformTable.end()) {
		GleamUniform uniform;
		uniform.data.uvec4_value = new glm::vec<4, unsigned>(v1, v2, v3, v4);
		uniform.type = GleamType::UVEC4;
		_uniformTable[name] = uniform;
	}
	else {
		*(itr->second.data.uvec4_value) = glm::vec<4, unsigned>(v1, v2, v3, v4);
		itr->second.type = GleamType::UVEC4;
	}
}

/* float matrices */
void ShaderResource::setMat2(const std::string& name, const glm::mat2& value) {
	auto itr = _uniformTable.find(name);
	if (itr == _uniformTable.end()) {
		GleamUniform uniform;
		uniform.data.mat2_value = new glm::mat2(value);
		uniform.type = GleamType::MAT2;
		_uniformTable[name] = uniform;
	}
	else {
		*(itr->second.data.mat2_value) = value;
		itr->second.type = GleamType::MAT2;
	}
}
void ShaderResource::setMat3(const std::string& name, const glm::mat3& value) {
	auto itr = _uniformTable.find(name);
	if (itr == _uniformTable.end()) {
		GleamUniform uniform;
		uniform.data.mat3_value = new glm::mat3(value);
		uniform.type = GleamType::MAT3;
		_uniformTable[name] = uniform;
	}
	else {
		*(itr->second.data.mat3_value) = value;
		itr->second.type = GleamType::MAT3;
	}
}
void ShaderResource::setMat4(const std::string& name, const glm::mat4& value) {
	auto itr = _uniformTable.find(name);
	if (itr == _uniformTable.end()) {
		GleamUniform uniform;
		uniform.data.mat4_value = new glm::mat4(value);
		uniform.type = GleamType::MAT4;
		_uniformTable[name] = uniform;
	}
	else {
		*(itr->second.data.mat4_value) = value;
		itr->second.type = GleamType::MAT4;
	}
}