#pragma once

#include <glm/glm.hpp>
#include <vector>

#include "Texture.h"
#include "Shader.h"

class Material {
private:
	glm::vec3 _baseColor;
	float _shininess;
	std::vector<Texture> _textures;
	unsigned int _baseColorTextureID;

	static unsigned int _defaultSpecularTextureID;

public:
	Material();
	Material(std::vector<Texture> textures);

	float getShininess();
	void setShininess(float shininess);

	glm::vec3 getBaseColor();
	void setBaseColor(const glm::vec3& color);

	const std::vector<Texture> getTextures() const;
	void setTextures(const std::vector<Texture>& textures);

	void addTexture(const Texture& texture);
	void removeTexture(const Texture& texture);
	void bind(Shader* shader);
};
