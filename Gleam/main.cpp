
//#define TESTING

#ifdef TESTING
	#include "TestUtils.h"
#endif
#include "Window.h"
#include "CameraFPS.h"

int main() {
#ifdef TESTING
	Window w("Gleam", 800, 600);
	Window w2("Taxes", 600, 400);
	testShaderResource();
	testWindow();
	testTransform();
	testTexture();
	testScene();
	testMeshLoader();
	testModel();
	/*
	while (!w.shouldClose() || !w2.shouldClose()) {
		if (!w.shouldClose()) {
			w.update();
		}
		else {
			w.close();
		}

		if (!w2.shouldClose()) {
			w2.update();
		}
		else {
			w2.close();
		}
	}
	*/
#endif
	const unsigned WIDTH = 800;
	const unsigned HEIGHT = 600;

	Window window("Hello World!", WIDTH, HEIGHT);
	Shader* shader = Shader::getDefault();
	Scene scene;
	unsigned radius = 5;
	unsigned numSami = 2;
	for (int i = 0; i < numSami; i++) {
		Model* varia = new Model("res/models/variasuit/DolBarriersuit.obj", shader);
		varia->transform.translate(glm::vec3(radius * glm::cos(glm::radians(i * (360.0f / numSami))), 0.0f, radius * glm::sin(glm::radians(i * (360.0f / numSami)))));
		scene.addRenderable(varia);
	}
	CameraFPS camera(glm::vec3(0.0f, 5.0f, 32.0f));
	Viewport view(0, 0, WIDTH, HEIGHT);
	view.scene = &scene;
	view.camera = &camera;

	window.addViewport(&view);

	while (!window.shouldClose()) {
		window.update();
	}
	window.close();
	return 0;
}