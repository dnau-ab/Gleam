#include "Model.h"

Model::Model(std::shared_ptr<Mesh> mesh, Shader* shader) {
	_mesh = mesh;
	_shader = shader;
}

Model::Model(std::shared_ptr<Mesh> mesh) {
	_mesh = mesh;
	_shader = Shader::getDefault();
}

void Model::render(const glm::mat4& projection, const glm::mat4& view) {
	if (_mesh != nullptr) {
		_shader->use();
		_shader->setMat4("projection", projection);
		_shader->setMat4("view", view);
		_shader->setMat4("model", transform.getTransformationMatrix());
		_shader->setMat3("normalMat", getNormalMatrix());
		_mesh->render(_shader);
	}
}