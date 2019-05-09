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
	Model(std::shared_ptr<Mesh> mesh, Shader* shader);
	Model(std::shared_ptr<Mesh> mesh);

	void render(const glm::mat4& projection, const glm::mat4& view) override;
};