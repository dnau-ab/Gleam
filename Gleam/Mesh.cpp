#include "Mesh.h"

std::vector<std::weak_ptr<Mesh> > Mesh::_loaded;

void Mesh::addLoadedMesh(std::weak_ptr<Mesh> mesh) {
	_loaded.push_back(mesh);
}

Mesh::Mesh(const std::vector<SubMesh>& meshes, const std::string& path)
	: _meshes(meshes), _path(path) {

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
	for (auto itr = _loaded.begin(); itr != _loaded.end(); itr++) {
		if (itr->expired()) {
			itr = _loaded.erase(itr);
		}
		if (itr->lock()->_path.compare(path) == 0) {
			return itr->lock();
		}
	}
}