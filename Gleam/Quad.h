#include "Renderable.h"
#include "SubMesh.h"

class Quad : Renderable {
private:
	unsigned int _VAO;
	unsigned int _VBO;
	std::vector<float> _vertices;

protected:

public:
	Quad(float width = 2.0f, float height = 2.0f, glm::vec3 center = glm::vec3(0.0f, 0.0f, 0.0f)) {
		float quadVertices[] = {
			// positions                                                     // texture Coords
			-width / 2.0f + center.x / 2.0f,  height / 2.0f + center.y / 2.0f, center.z, 0.0f, 1.0f,
			-width / 2.0f + center.x / 2.0f, -height / 2.0f + center.y / 2.0f, center.z, 0.0f, 0.0f,
			 width / 2.0f + center.x / 2.0f,  height / 2.0f + center.y / 2.0f, center.z, 1.0f, 1.0f,
			 width / 2.0f + center.x / 2.0f, -height / 2.0f + center.y / 2.0f, center.z, 1.0f, 0.0f,
		};
		// setup plane VAO
		glGenVertexArrays(1, &_VAO);
		glGenBuffers(1, &_VBO);
		glBindVertexArray(_VAO);
		glBindBuffer(GL_ARRAY_BUFFER, _VBO);
		glBufferData(GL_ARRAY_BUFFER, sizeof(quadVertices), &quadVertices, GL_STATIC_DRAW);
		glEnableVertexAttribArray(0);
		glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 5 * sizeof(float), (void*)0);
		glEnableVertexAttribArray(1);
		glVertexAttribPointer(1, 2, GL_FLOAT, GL_FALSE, 5 * sizeof(float), (void*)(3 * sizeof(float)));
	}

	void render(const glm::mat4& projection, const glm::mat4& view) override {
		glBindVertexArray(_VAO);
		glDrawArrays(GL_TRIANGLE_STRIP, 0, 4);
		glBindVertexArray(0);
	}

};