#include "Shader.h"

Shader* Shader::_defaultShader = nullptr;
Shader* Shader::_defaultLightingShader = nullptr;

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

	fragment = glCreateShader(GL_FRAGMENT_SHADER);
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
		_defaultShader = new Shader("res/shaders/gleam_default_shader_def.vert", "res/shaders/gleam_default_shader_def.frag");
	}
	return _defaultShader;
}

Shader* Shader::getDefaultLighting() {
	if (_defaultLightingShader == nullptr) {
		_defaultLightingShader = new Shader("res/shaders/gleam_default_shader_def_lighting.vert", "res/shaders/gleam_default_shader_def_lighting.frag");
	}
	return _defaultLightingShader;
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
	glUniform1i(glGetUniformLocation(_ID, name.c_str()), (int)value);
}
void Shader::setFloat(const std::string& name, float value) const {
	glUniform1f(glGetUniformLocation(_ID, name.c_str()), value);
}
void Shader::setInt(const std::string& name, int value) const {
	glUniform1i(glGetUniformLocation(_ID, name.c_str()), (int)value);
}
void Shader::setUnsigned(const std::string& name, unsigned value) const {
	glUniform1ui(glGetUniformLocation(_ID, name.c_str()), value);
}
/* bool vectors */
void Shader::setVec2(const std::string& name, const glm::vec<2, bool>& value) const {
	glUniform2iv(glGetUniformLocation(_ID, name.c_str()), 1, (int*)&value[0]);
}
void Shader::setVec2(const std::string& name, bool v1, bool v2) const {
	glUniform2i(glGetUniformLocation(_ID, name.c_str()), (int)v1, (int)v2);
}
void Shader::setVec3(const std::string& name, const glm::vec<3, bool>& value) const {
	glUniform3iv(glGetUniformLocation(_ID, name.c_str()), 1, (int*)&value);
}
void Shader::setVec3(const std::string& name, bool v1, bool v2, bool v3) const {
	glUniform3i(glGetUniformLocation(_ID, name.c_str()), (int)v1, (int)v2, (int)v3);
}
void Shader::setVec4(const std::string& name, const glm::vec<4, bool>& value) const {
	glUniform4iv(glGetUniformLocation(_ID, name.c_str()), 1, (int*)&value);
}
void Shader::setVec4(const std::string& name, bool v1, bool v2, bool v3, bool v4) const {
	glUniform4i(glGetUniformLocation(_ID, name.c_str()), (int)v1, (int)v2, (int)v3, (int)v4);
}
/* float vectors */
void Shader::setVec2(const std::string& name, const glm::vec<2, float>& value) const {
	glUniform2fv(glGetUniformLocation(_ID, name.c_str()), 1, &value[0]);
}
void Shader::setVec2(const std::string& name, float v1, float v2) const {
	glUniform2f(glGetUniformLocation(_ID, name.c_str()), v1, v2);
}
void Shader::setVec3(const std::string& name, const glm::vec<3, float>& value) const {
	glUniform3fv(glGetUniformLocation(_ID, name.c_str()), 1, &value[0]);
}
void Shader::setVec3(const std::string& name, float v1, float v2, float v3) const {
	glUniform3f(glGetUniformLocation(_ID, name.c_str()), v1, v2, v3);
}
void Shader::setVec4(const std::string& name, const glm::vec<4, float>& value) const {
	glUniform4fv(glGetUniformLocation(_ID, name.c_str()), 1, &value[0]);
}
void Shader::setVec4(const std::string& name, float v1, float v2, float v3, float v4) const {
	glUniform4f(glGetUniformLocation(_ID, name.c_str()), v1, v2, v3, v4);
}
/* int vectors */
void Shader::setVec2(const std::string& name, const glm::vec<2, int>& value) const {
	glUniform2iv(glGetUniformLocation(_ID, name.c_str()), 1, &value[0]);
}
void Shader::setVec2(const std::string& name, int v1, int v2) const {
	glUniform2i(glGetUniformLocation(_ID, name.c_str()), v1, v2);
}
void Shader::setVec3(const std::string& name, const glm::vec<3, int>& value) const {
	glUniform3iv(glGetUniformLocation(_ID, name.c_str()), 1, &value[0]);
}
void Shader::setVec3(const std::string& name, int v1, int v2, int v3) const {
	glUniform3i(glGetUniformLocation(_ID, name.c_str()), v1, v2, v3);
}
void Shader::setVec4(const std::string& name, const glm::vec<4, int>& value) const {
	glUniform4iv(glGetUniformLocation(_ID, name.c_str()), 1, &value[0]);
}
void Shader::setVec4(const std::string& name, int v1, int v2, int v3, int v4) const {
	glUniform4i(glGetUniformLocation(_ID, name.c_str()), v1, v2, v3, v4);
}
/* unsigned vectors */
void Shader::setVec2(const std::string& name, const glm::vec<2, unsigned>& value) const {
	glUniform2uiv(glGetUniformLocation(_ID, name.c_str()), 1, &value[0]);
}
void Shader::setVec2(const std::string& name, unsigned v1, unsigned v2) const {
	glUniform2ui(glGetUniformLocation(_ID, name.c_str()), v1, v2);
}
void Shader::setVec3(const std::string& name, const glm::vec<3, unsigned>& value) const {
	glUniform3uiv(glGetUniformLocation(_ID, name.c_str()), 1, &value[0]);
}
void Shader::setVec3(const std::string& name, unsigned v1, unsigned v2, unsigned v3) const {
	glUniform3ui(glGetUniformLocation(_ID, name.c_str()), v1, v2, v3);
}
void Shader::setVec4(const std::string& name, const glm::vec<4, unsigned>& value) const {
	glUniform4uiv(glGetUniformLocation(_ID, name.c_str()), 1, &value[0]);
}
void Shader::setVec4(const std::string& name, unsigned v1, unsigned v2, unsigned v3, unsigned v4) const {
	glUniform4ui(glGetUniformLocation(_ID, name.c_str()), v1, v2, v3, v4);
}
/* float matrices */
void Shader::setMat2(const std::string& name, const glm::mat2& value) const {
	glUniformMatrix2fv(glGetUniformLocation(_ID, name.c_str()), 1, GL_FALSE, &value[0][0]);
}
void Shader::setMat3(const std::string& name, const glm::mat3& value) const {
	glUniformMatrix3fv(glGetUniformLocation(_ID, name.c_str()), 1, GL_FALSE, &value[0][0]);
}
void Shader::setMat4(const std::string& name, const glm::mat4& value) const {
	glUniformMatrix4fv(glGetUniformLocation(_ID, name.c_str()), 1, GL_FALSE, &value[0][0]);
}