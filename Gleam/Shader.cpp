#include "Shader.h"

Shader* Shader::_defaultShader = nullptr;

Shader::Shader(const std::string& vertexPath, const std::string& fragmentPath) {
	std::string vertexCode;
	std::string fragmentCode;

	std::ifstream vertexFile;
	std::ifstream fragmentFile;

	vertexFile.exceptions(std::ifstream::failbit | std::ifstream::badbit);
	fragmentFile.exceptions(std::ifstream::failbit | std::ifstream::badbit);

	try {
		vertexFile.open(vertexPath);
		fragmentFile.open(fragmentPath);
		std::stringstream vShaderStream, fShaderStream;

		vShaderStream << vertexFile.rdbuf();
		fShaderStream << fragmentFile.rdbuf();

		vertexFile.close();
		fragmentFile.close();

		vertexCode = vShaderStream.str();
		fragmentCode = fShaderStream.str();
	}
	catch (std::ifstream::failure e) {
		std::cout << "ERROR::SHADER::FILE_NOT_SUCCESFULLY_READ" << std::endl;
		return;
	}

	unsigned int vertex, fragment;
	const char* vCode = vertexCode.c_str();
	const char* fCode = fragmentCode.c_str();
	vertex = glCreateShader(GL_VERTEX_SHADER);
	glShaderSource(vertex, 1, &vCode, NULL);
	glCompileShader(vertex);
	checkCompileErrors(vertex, "VERTEX");

	fragment = glCreateShader(GL_FRAGMENT_SHADER);;
	glShaderSource(fragment, 1, &fCode, NULL);
	glCompileShader(fragment);
	checkCompileErrors(fragment, "FRAGMENT");

	_ID = glCreateProgram();
	glAttachShader(_ID, vertex);
	glAttachShader(_ID, fragment);

	glLinkProgram(_ID);
	checkCompileErrors(_ID, "PROGRAM");

	glDeleteShader(vertex);
	glDeleteShader(fragment);
}

void Shader::use() {
	glUseProgram(_ID);
	
}

Shader* Shader::getDefault() {
	if (_defaultShader == nullptr) {
		_defaultShader = new Shader("gleam_default_shader.vert", "gleam_default_shader.frag");
	}
	return _defaultShader;
}

unsigned int Shader::getID() {
	return _ID;
}

void Shader::checkCompileErrors(GLuint shader, std::string type)
{
	GLint success;
	GLchar infoLog[1024];
	if (type != "PROGRAM")
	{
		glGetShaderiv(shader, GL_COMPILE_STATUS, &success);
		if (!success)
		{
			glGetShaderInfoLog(shader, 1024, NULL, infoLog);
			std::cout << "ERROR::SHADER_COMPILATION_ERROR of type: " << type << "\n" << infoLog << std::endl;
		}
	}
	else
	{
		glGetProgramiv(shader, GL_LINK_STATUS, &success);
		if (!success)
		{
			glGetProgramInfoLog(shader, 1024, NULL, infoLog);
			std::cout << "ERROR::PROGRAM_LINKING_ERROR of type: " << type << "\n" << infoLog << std::endl;
		}
	}
}

void Shader::setUniform(const std::string& name, const GleamUniform& uniform) const {
	switch (uniform.type) {
	case GleamType::BOOL:
		setBool(name, uniform.data.bool_value);
		break;
	case GleamType::FLOAT:
		setFloat(name, uniform.data.float_value);
		break;
	case GleamType::INT:
		setInt(name, uniform.data.int_value);
		break;
	case GleamType::UNSIGNED:
		setUnsigned(name, uniform.data.unsigned_value);
		break;
	case GleamType::BVEC2:
		setVec2(name, *(uniform.data.bvec2_value));
		break;
	case GleamType::BVEC3:
		setVec3(name, *(uniform.data.bvec3_value));
		break;
	case GleamType::BVEC4:
		setVec4(name, *(uniform.data.bvec4_value));
		break;
	case GleamType::IVEC2:
		setVec2(name, *(uniform.data.ivec2_value));
		break;
	case GleamType::IVEC3:
		setVec3(name, *(uniform.data.ivec3_value));
		break;
	case GleamType::IVEC4:
		setVec4(name, *(uniform.data.ivec4_value));
		break;
	case GleamType::UVEC2:
		setVec2(name, *(uniform.data.uvec2_value));
		break;
	case GleamType::UVEC3:
		setVec3(name, *(uniform.data.uvec3_value));
		break;
	case GleamType::UVEC4:
		setVec4(name, *(uniform.data.uvec4_value));
		break;
	case GleamType::VEC2:
		setVec2(name, *(uniform.data.vec2_value));
		break;
	case GleamType::VEC3:
		setVec3(name, *(uniform.data.vec3_value));
		break;
	case GleamType::VEC4:
		setVec4(name, *(uniform.data.vec4_value));
		break;
	case GleamType::MAT2:
		setMat2(name, *(uniform.data.mat2_value));
		break;
	case GleamType::MAT3:
		setMat3(name, *(uniform.data.mat3_value));
		break;
	case GleamType::MAT4:
		setMat4(name, *(uniform.data.mat4_value));
		break;
	}
}

void Shader::setBool(const std::string& name, bool value) const {

}
void Shader::setFloat(const std::string& name, float value) const {

}
void Shader::setInt(const std::string& name, int value) const {

}
void Shader::setUnsigned(const std::string& name, unsigned value) const {

}
/* bool vectors */
void Shader::setVec2(const std::string& name, const glm::vec<2, bool>& value) const {

}
void Shader::setVec2(const std::string& name, float v1, bool v2) const {

}
void Shader::setVec3(const std::string& name, const glm::vec<3, bool>& value) const {

}
void Shader::setVec3(const std::string& name, bool v1, bool v2, bool v3) const {

}
void Shader::setVec4(const std::string& name, const glm::vec<4, bool>& value) const {

}
void Shader::setVec4(const std::string& name, bool v1, bool v2, bool v3, bool v4) const {

}
/* float vectors */
void Shader::setVec2(const std::string& name, const glm::vec<2, float>& value) const {

}
void Shader::setVec2(const std::string& name, float v1, float v2) const {

}
void Shader::setVec3(const std::string& name, const glm::vec<3, float>& value) const {

}
void Shader::setVec3(const std::string& name, float v1, float v2, float v3) const {

}
void Shader::setVec4(const std::string& name, const glm::vec<4, float>& value) const {

}
void Shader::setVec4(const std::string& name, float v1, float v2, float v3, float v4) const {

}
/* int vectors */
void Shader::setVec2(const std::string& name, const glm::vec<2, int>& value) const {

}
void Shader::setVec2(const std::string& name, int v1, int v2) const {

}
void Shader::setVec3(const std::string& name, const glm::vec<3, int>& value) const {

}
void Shader::setVec3(const std::string& name, int v1, int v2, int v3) const {

}
void Shader::setVec4(const std::string& name, const glm::vec<4, int>& value) const {

}
void Shader::setVec4(const std::string& name, int v1, int v2, int v3, int v4) const {

}
/* unsigned vectors */
void Shader::setVec2(const std::string& name, const glm::vec<2, unsigned>& value) const {

}
void Shader::setVec2(const std::string& name, unsigned v1, unsigned v2) const {

}
void Shader::setVec3(const std::string& name, const glm::vec<3, unsigned>& value) const {

}
void Shader::setVec3(const std::string& name, unsigned v1, unsigned v2, unsigned v3) const {

}
void Shader::setVec4(const std::string& name, const glm::vec<4, unsigned>& value) const {

}
void Shader::setVec4(const std::string& name, unsigned v1, unsigned v2, unsigned v3, unsigned v4) const {

}
/* float matrices */
void Shader::setMat2(const std::string& name, const glm::mat2& value) const {

}
void Shader::setMat3(const std::string& name, const glm::mat3& value) const {

}
void Shader::setMat4(const std::string& name, const glm::mat4& value) const {

}