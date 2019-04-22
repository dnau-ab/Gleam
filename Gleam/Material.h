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

public:
	void addTexture(const Texture& texture);
	void removeTexture(const Texture& texture);
	void bind(Shader* shader);
};
