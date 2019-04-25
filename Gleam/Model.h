#pragma once

#include "Material.h"
#include "Mesh.h"
#include "Renderable.h"
#include "MeshLoader.h"

class Model : public Renderable {
private:
	void setPath(const std::string& path);

protected:
	std::shared_ptr<Mesh> _mesh;
	std::string _fileName;
	std::string _directory;

public:
	Model(std::string path, bool loadTextures = true);
	Model(std::string path, Shader* shader, bool loadTextures = true);
	Model(std::shared_ptr<Mesh> mesh, Shader* shader);
	Model(std::shared_ptr<Mesh> mesh);

	void render(const Camera& camera) override;
};