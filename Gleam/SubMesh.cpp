#include "SubMesh.h"

void SubMesh::init() {
	// setup VAO, VBO, EBO
	glGenVertexArrays(1, &_VAO);
	glGenBuffers(1, &_VBO);
	glGenBuffers(1, &_EBO);

	// bind VAO
	glBindVertexArray(_VAO);
	glBindBuffer(GL_ARRAY_BUFFER, _VBO);

	// specify buffer data
	glBufferData(GL_ARRAY_BUFFER, _vertices.size() * sizeof(Vertex), &_vertices[0], GL_STATIC_DRAW);

	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, _EBO);
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, _indices.size() * sizeof(unsigned int), &_indices[0], GL_STATIC_DRAW);

	// specify layout of data:
	// setup position attribute
	glEnableVertexAttribArray(0);
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, sizeof(Vertex), (void*)0);
	// setup normal attribute
	glEnableVertexAttribArray(1);
	glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, sizeof(Vertex), (void*)offsetof(Vertex, normal));
	// setup tex coord attribute
	glEnableVertexAttribArray(2);
	glVertexAttribPointer(2, 2, GL_FLOAT, GL_FALSE, sizeof(Vertex), (void*)offsetof(Vertex, texCoord));
}

SubMesh::SubMesh(const std::vector<Vertex>& vertices, const std::vector<unsigned>& indices, const std::vector<Texture>& textures) 
	: _vertices(vertices), _indices(indices), material(textures) {
	init();
}

SubMesh::SubMesh(const std::vector<Vertex>& vertices, const std::vector<unsigned>& indices, const Material& material)
	: _vertices(vertices), _indices(indices), material(material) {
	init();
}

unsigned int SubMesh::numVertices() {
	return _vertices.size();
}

unsigned int SubMesh::numIndices() {
	return _indices.size();
}

void SubMesh::render(Shader* shader) {
	// bind the textures, material properties
	material.bind(shader);

	// draw mesh
	glBindVertexArray(_VAO);
	glDrawElements(GL_TRIANGLES, _indices.size(), GL_UNSIGNED_INT, 0);
	glBindVertexArray(0);

	glActiveTexture(GL_TEXTURE0);
}