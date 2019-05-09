#include "Mesh.h"

std::vector<std::weak_ptr<Mesh> > Mesh::_loaded;

void Mesh::addLoadedMesh(std::weak_ptr<Mesh> mesh) {
	_loaded.push_back(mesh);
}

Mesh::Mesh(const std::vector<SubMesh>& meshes, const std::string& path)
	: _meshes(meshes), _path(path) {

}

Mesh::Mesh(const Mesh& mesh) {
	_meshes = mesh._meshes;
	_path = mesh._path;
}

unsigned int Mesh::numOfSubMeshes() {
	return _meshes.size();
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

std::shared_ptr<Mesh> Mesh::getLoaded(std::string path) {
	for (auto itr = _loaded.begin(); itr != _loaded.end(); ) {
		if (itr->expired()) {
			itr = _loaded.erase(itr);
			continue;
		}
		else if (itr->lock()->_path.compare(path) == 0) {
			return itr->lock();
		}
		itr++;
	}
	return nullptr;
}