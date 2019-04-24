#pragma once

#include <memory>

#include "SubMesh.h"

class Mesh {
private:
	std::vector<SubMesh> _meshes;
	static std::vector<std::weak_ptr<Mesh> > _loaded;

public:
	static void addLoadedMesh(std::weak_ptr<Mesh> mesh);

	Mesh(const std::vector<SubMesh>& meshes);

	void render(Shader* shader);
};
