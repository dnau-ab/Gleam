#pragma once

#include <memory>

#include "SubMesh.h"

class Mesh {
private:
	std::string _path;

protected:
	std::vector<SubMesh> _meshes;
	static std::vector<std::weak_ptr<Mesh> > _loaded;

public:
	static void addLoadedMesh(std::weak_ptr<Mesh> mesh);
	static std::shared_ptr<Mesh> getLoaded(std::string path);

	Mesh(const std::vector<SubMesh>& meshes, const std::string& path);
	Mesh(const Mesh& mesh);

	std::shared_ptr<Mesh> getCopy() {
		return std::make_shared<Mesh>(Mesh(*this));
	}

	unsigned int numOfSubMeshes();

	SubMesh* getSubMesh(unsigned index);

	void render(Shader* shader);
};
