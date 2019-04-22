#pragma once

#include <vector>

#include "Vertex.h"
#include "Material.h"

class SubMesh {
private:
	unsigned int _VAO;
	unsigned int _VBO;
	unsigned int _EBO;

	std::vector<Vertex> _vertices;
	std::vector<unsigned> _indices;

	void init();
public:
	Material material;

	SubMesh(const std::vector<Vertex>& vertices, const std::vector<unsigned>& indices, const std::vector<Texture>& textures);
	SubMesh(const std::vector<Vertex>& vertices, const std::vector<unsigned>& indices, const Material& material);

	void render(Shader* shader);
};
