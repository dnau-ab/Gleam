#pragma once

#include <memory>

#include "SubMesh.h"

class Mesh {
private:
	std::vector<SubMesh> meshes;
	static std::vector<std::weak_ptr<Mesh> > loaded;

public:
	Mesh(const std::vector<SubMesh>& meshes);

	void render(Shader* shader);
};
