#include "Model.h"

void Model::setPath(const std::string& path) {
	size_t i = path.find_last_of("/");
	if (i != std::string::npos) {
		_fileName = path.substr(i + 1);
		_directory = path.substr(0, i + 1);
	}
	else {
		_fileName = path;
		_directory = "";
	}
}

Model::Model(std::string path, bool loadTextures) {
	setPath(path);
	_mesh = MeshLoader::loadMesh(_directory, _fileName, loadTextures);
	_shader = Shader::getDefault();
}

Model::Model(std::string path, Shader* shader, bool loadTextures) {
	setPath(path);
	_mesh = MeshLoader::loadMesh(_directory, _fileName, loadTextures);
	_shader = shader;
}

Model::Model(std::shared_ptr<Mesh> mesh, Shader* shader) {
	_mesh = mesh;
	_shader = shader;
}

Model::Model(std::shared_ptr<Mesh> mesh) {
	_mesh = mesh;
	_shader = Shader::getDefault();
}

void Model::render(const Camera& camera) {
	if (_mesh != nullptr) {
		_mesh->render(_shader);
	}
}