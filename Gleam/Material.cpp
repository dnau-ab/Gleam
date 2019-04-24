#include "Material.h"

Material::Material()
	: _shininess(32.0f), _baseColor(glm::vec3(1.0, 1.0, 1.0)), _textures() {

}

Material::Material(std::vector<Texture> textures) 
	: _shininess(32.0f), _baseColor(1.0, 1.0, 1.0), _textures(textures) {

}

float Material::getShininess() {
	return _shininess;
}

void Material::setShininess(float shininess) {
	_shininess = shininess;
}

const std::vector<Texture> Material::getTextures() const {
	return _textures;
}

void Material::setTextures(const std::vector<Texture>& textures) {
	_textures = textures;
}

void Material::addTexture(const Texture& texture) {
	_textures.push_back(texture);
}

void Material::removeTexture(const Texture& texture) {
	auto itr = std::find(_textures.begin(), _textures.end(), texture);
	if (itr != _textures.end()) {
		_textures.erase(itr);
	}
}

void Material::bind(Shader* shader) {
	// set diffuse, specular, ... uniforms
	shader->setFloat("material.shininess", _shininess);
	shader->setVec3("baseColor", _baseColor);

	// set texture uniforms
	unsigned diffuseNum = 1;
	unsigned specularNum = 1;
	unsigned normalNum = 1;
	unsigned heightNum = 1;
	std::string number;
	// reset textures
	for (size_t i = 0; i < 4; i++) {
		number = std::to_string(i);
		glActiveTexture(GL_TEXTURE0 + i);
		glUniform1i(glGetUniformLocation(shader->getID(), ("texture_diffuse" + number).c_str()), i);
		glBindTexture(GL_TEXTURE_2D, Texture::getDefaultID());

		glActiveTexture(GL_TEXTURE0 + i);
		glUniform1i(glGetUniformLocation(shader->getID(), ("texture_specular" + number).c_str()), i + 3);
		glBindTexture(GL_TEXTURE_2D, Texture::getDefaultID());

		glActiveTexture(GL_TEXTURE0 + i);
		glUniform1i(glGetUniformLocation(shader->getID(), ("texture_normal" + number).c_str()), i + 7);
		glBindTexture(GL_TEXTURE_2D, Texture::getDefaultID());

		glActiveTexture(GL_TEXTURE0 + i);
		glUniform1i(glGetUniformLocation(shader->getID(), ("texture_height" + number).c_str()), i + 11);
		glBindTexture(GL_TEXTURE_2D, Texture::getDefaultID());
	}
	for (size_t i = 0; i < _textures.size(); i++) {
		glActiveTexture(GL_TEXTURE0 + i);

		std::string name = _textures[i].getType();
		if (name == "texture_diffuse") {
			number = std::to_string(diffuseNum++);
			shader->setInt("material.diffuse" + number, i);
		}
		else if (name == "texture_specular") {
			number = std::to_string(specularNum++);
			shader->setInt("material.specular" + number, i);
		}
		else if (name == "texture_normal") {
			number = std::to_string(normalNum++);
			shader->setInt("material.normal" + number, i);
		}
		else if (name == "texture_height") {
			number = std::to_string(heightNum++);
			shader->setInt("material.height" + number, i);
		}

		std::string uniformName = name + number;
		glUniform1i(glGetUniformLocation(shader->getID(), uniformName.c_str()), i);
		glBindTexture(GL_TEXTURE_2D, _textures[i].getID());
	}
	if (_textures.size() == 0) {
		// bind default diffuse texture
		glActiveTexture(GL_TEXTURE0);
		glUniform1i(glGetUniformLocation(shader->getID(), "texture_diffuse1"), 0);
		glBindTexture(GL_TEXTURE_2D, Texture::getDefaultID());
	}
}