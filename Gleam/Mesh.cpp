#include "Mesh.h"

std::vector<std::weak_ptr<Mesh> > Mesh::_loaded;

void Mesh::addLoadedMesh(std::weak_ptr<Mesh> mesh) {
	_loaded.push_back(mesh);
}

Mesh::Mesh(const std::vector<SubMesh>& meshes)
	: _meshes(meshes) {

}

SubMesh* Mesh::getSubMesh(unsigned index) {
	if (index >= _meshes.size()) {
		return nullptr;
	}
	return &_meshes[index];
}

void Mesh::render(Shader* shader) {
	// render all submeshes
	for (SubMesh& mesh : _meshes) {
		mesh.render(shader);
	}
}