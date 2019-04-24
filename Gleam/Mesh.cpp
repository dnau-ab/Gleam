#include "Mesh.h"

std::vector<std::weak_ptr<Mesh> > Mesh::_loaded;

void Mesh::addLoadedMesh(std::weak_ptr<Mesh> mesh) {
	_loaded.push_back(mesh);
}

Mesh::Mesh(const std::vector<SubMesh>& meshes) {

}

void Mesh::render(Shader* shader) {

}