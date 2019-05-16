#include "Material.h"

Material::Material()
	: _shininess(32.0f), _baseColor(1.0f, 1.0f, 1.0f), _textures() {
	_baseColorTextureID = Texture::getColorTextureID(_baseColor);
}

Material::Material(std::vector<Texture> textures) 
	: _shininess(32.0f), _baseColor(1.0f, 1.0f, 1.0f), _textures(textures) {
	_baseColorTextureID = Texture::getColorTextureID(_baseColor);
}

float Material::getShininess() {
	return _shininess;
}

void Material::setShininess(float shininess) {
	_shininess = shininess;
}

glm::vec3 Material::getBaseColor() {
	return _baseColor;
}

void Material::setBaseColor(const glm::vec3& color) {
	_baseColor = color;
	// set texture color
	GLubyte data[] = { (GLubyte)(color.r * 255), (GLubyte)(color.g * 255), (GLubyte)(color.b * 255), 255 };
	glBindTexture(GL_TEXTURE_2D, _baseColorTextureID);
	glTexSubImage2D(GL_TEXTURE_2D, 0, 0, 0, 1, 1, GL_RGBA, GL_UNSIGNED_BYTE, data);
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

	// set texture uniforms
	unsigned diffuseNum = 1;
	unsigned specularNum = 1;
	unsigned normalNum = 1;
	unsigned heightNum = 1;
	std::string number;

	for (size_t i = 0; i < _textures.size(); i++) {
		glActiveTexture(GL_TEXTURE0 + i);

		std::string name = _textures[i].getType();
		if (name == "diffuse") {
			number = std::to_string(diffuseNum++);
			shader->setInt("material.diffuse" + number, i);
		}
		else if (name == "specular") {
			number = std::to_string(specularNum++);
			shader->setInt("material.specular" + number, i);
		}
		else if (name == "normal") {
			number = std::to_string(normalNum++);
			shader->setInt("material.normal" + number, i);
		}
		else if (name == "height") {
			number = std::to_string(heightNum++);
			shader->setInt("material.height" + number, i);
		}

		glBindTexture(GL_TEXTURE_2D, _textures[i].getID());
	}
	if (diffuseNum == 1) {
		// bind default diffuse texture
		glActiveTexture(GL_TEXTURE0);
		shader->setInt("material.diffuse1", 0);
		glBindTexture(GL_TEXTURE_2D, _baseColorTextureID);
	}
	if (specularNum == 1) {
		if (_defaultSpecularTextureID == 0) {
			// initialize
			_defaultSpecularTextureID = Texture::getColorTextureID({ 0.0f, 0.0f, 0.0f });
		}
		// bind default specular texture
		glActiveTexture(GL_TEXTURE1);
		shader->setInt("material.specular1", 1);
		glBindTexture(GL_TEXTURE_2D, _defaultSpecularTextureID);
	}
}

unsigned int Material::_defaultSpecularTextureID = 0;