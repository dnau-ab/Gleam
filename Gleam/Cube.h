#pragma once
#include "Renderable.h"
#include "Material.h"

class Cube : public Renderable {
private:
	unsigned int _VAO;
	unsigned int _VBO;
	unsigned int _numVertices;

protected:
	void init() {
		float cubeVertices[] = {
			// positions         // normals         // texture Coords
			1, 1, -1, 1, 0, 0, 0, 0,
			1, -1, 1, 1, 0, 0, 1, 1,
			1, -1, -1, 1, 0, 0, 0, 1,
			1, 1, 1, 0, 0, 1, 0, 0,
			-1, -1, 1, 0, 0, 1, 1, 1,
			1, -1, 1, 0, 0, 1, 0, 1,
			-1, 1, 1, -1, 0, 0, 0, 0,
			-1, -1, -1, -1, 0, 0, -1, 1,
			-1, -1, 1, -1, 0, 0, 0, 1,
			-1, 1, -1, 0, 0, -1, 0, 0,
			1, -1, -1, 0, 0, -1, -1, 1,
			-1, -1, -1, 0, 0, -1, 0, 1,
			-1, -1, 1, 0, -1, 0, 1, 1,
			1, -1, -1, 0, -1, 0, 0, 2,
			1, -1, 1, 0, -1, 0, 0, 1,
			1, 1, 1, 0, 1, 0, -1, 1,
			-1, 1, -1, 0, 1, 0, 0, 2,
			-1, 1, 1, 0, 1, 0, 0, 1,
			1, 1, -1, 1, 0, 0, 0, 0,
			1, 1, 1, 1, 0, 0, 1, 0,
			1, -1, 1, 1, 0, 0, 1, 1,
			1, 1, 1, 0, 0, 1, 0, 0,
			-1, 1, 1, 0, 0, 1, 1, 0,
			-1, -1, 1, 0, 0, 1, 1, 1,
			-1, 1, 1, -1, 0, 0, 0, 0,
			-1, 1, -1, -1, 0, 0, -1, 0,
			-1, -1, -1, -1, 0, 0, -1, 1,
			-1, 1, -1, 0, 0, -1, 0, 0,
			1, 1, -1, 0, 0, -1, -1, 0,
			1, -1, -1, 0, 0, -1, -1, 1,
			-1, -1, 1, 0, -1, 0, 1, 1,
			-1, -1, -1, 0, -1, 0, 1, 2,
			1, -1, -1, 0, -1, 0, 0, 2,
			1, 1, 1, 0, 1, 0, -1, 1,
			1, 1, -1, 0, 1, 0, -1, 2,
			-1, 1, -1, 0, 1, 0, 0, 2,
		};

		_numVertices = 36;

		// setup plane VAO
		glGenVertexArrays(1, &_VAO);
		glGenBuffers(1, &_VBO);
		glBindVertexArray(_VAO);
		glBindBuffer(GL_ARRAY_BUFFER, _VBO);
		glBufferData(GL_ARRAY_BUFFER, sizeof(cubeVertices), &cubeVertices, GL_STATIC_DRAW);
		glEnableVertexAttribArray(0);
		glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 8 * sizeof(float), (void*)0);
		glEnableVertexAttribArray(1);
		glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 8 * sizeof(float), (void*)(3 * sizeof(float)));
		glEnableVertexAttribArray(2);
		glVertexAttribPointer(2, 2, GL_FLOAT, GL_FALSE, 8 * sizeof(float), (void*)(6 * sizeof(float)));
	}

public:
	Material material;

	Cube() : material() {
		init();
		_shader = Shader::getDefault();
	}

	Cube(Material material) : material(material) {
		init();
		_shader = Shader::getDefault();
	}

	Cube(Shader* shader) : material() {
		init();
		_shader = shader;
	}

	Cube(Material material, Shader* shader) : material(material) {
		init();
		_shader = shader;
	}

	~Cube() {
		glDeleteVertexArrays(1, &_VAO);
		glDeleteBuffers(1, &_VBO);
	}

	void render(const glm::mat4& projection, const glm::mat4& view) override {
		if (_shader != nullptr) {
			_shader->use();
			_shader->setMat4("model", transform.getTransformationMatrix());
			_shader->setMat4("view", view);
			_shader->setMat4("projection", projection);
			_shader->setMat3("normalMat", getNormalMatrix());
			material.bind(_shader);
		}
		glBindVertexArray(_VAO);
		glDrawArrays(GL_TRIANGLES, 0, _numVertices);
		glBindVertexArray(0);
	}

};