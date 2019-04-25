#pragma once

#include <glad/glad.h>

#include <glm/glm.hpp>

#include <string>
#include <fstream>
#include <sstream>
#include <iostream>
#include <unordered_map>

#include "ShaderResource.h"


class Shader {
protected:
	unsigned int _ID;
	static Shader* _defaultShader;

	void checkCompileErrors(GLuint shader, std::string type);
public:
	Shader(const std::string& vertexPath, const std::string& fragmentPath);

	static Shader* getDefault();
	unsigned int getID();
	void use();

	void setUniform(const std::string& name, const GleamUniform& uniform) const;

	void setBool(const std::string& name, bool value) const;
	void setFloat(const std::string& name, float value) const;
	void setInt(const std::string& name, int value) const;
	void setUnsigned(const std::string& name, unsigned value) const;

	void setVec2(const std::string& name, const glm::vec<2, bool>& value) const;
	void setVec2(const std::string& name, bool v1, bool v2) const;
	void setVec3(const std::string& name, const glm::vec<3, bool>& value) const;
	void setVec3(const std::string& name, bool v1, bool v2, bool v3) const;
	void setVec4(const std::string& name, const glm::vec<4, bool>& value) const;
	void setVec4(const std::string& name, bool v1, bool v2, bool v3, bool v4) const;

	void setVec2(const std::string& name, const glm::vec<2, float>& value) const;
	void setVec2(const std::string& name, float v1, float v2) const;
	void setVec3(const std::string& name, const glm::vec<3, float>& value) const;
	void setVec3(const std::string& name, float v1, float v2, float v3) const;
	void setVec4(const std::string& name, const glm::vec<4, float>& value) const;
	void setVec4(const std::string& name, float v1, float v2, float v3, float v4) const;

	void setVec2(const std::string& name, const glm::vec<2, int>& value) const;
	void setVec2(const std::string& name, int v1, int v2) const;
	void setVec3(const std::string& name, const glm::vec<3, int>& value) const;
	void setVec3(const std::string& name, int v1, int v2, int v3) const;
	void setVec4(const std::string& name, const glm::vec<4, int>& value) const;
	void setVec4(const std::string& name, int v1, int v2, int v3, int v4) const;

	void setVec2(const std::string& name, const glm::vec<2, unsigned>& value) const;
	void setVec2(const std::string& name, unsigned v1, unsigned v2) const;
	void setVec3(const std::string& name, const glm::vec<3, unsigned>& value) const;
	void setVec3(const std::string& name, unsigned v1, unsigned v2, unsigned v3) const;
	void setVec4(const std::string& name, const glm::vec<4, unsigned>& value) const;
	void setVec4(const std::string& name, unsigned v1, unsigned v2, unsigned v3, unsigned v4) const;

	void setMat2(const std::string& name, const glm::mat2& value) const;
	void setMat3(const std::string& name, const glm::mat3& value) const;
	void setMat4(const std::string& name, const glm::mat4& value) const;
	/* TODO: Visitor pattern uniform setting w/ type */
};
