
#include "TestUtils.h"
#include "Window.h"
#include "CameraFPS.h"

//#define TESTING

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
	Window window("Hello World!", 800, 600);
	Shader* shader = Shader::getDefault();
	Scene scene;
	for (int i = 0; i < 16; i++) {
		Model* varia = new Model("res/models/variasuit/DolBarriersuit.obj", shader);
		varia->transform.translate(glm::vec3(cos(i * (360.0f / 16.0f)), 0.0f, sin(i * (360.0f / 16.0f))));
		scene.addRenderable(varia);
	}
	CameraFPS camera(glm::vec3(0.0f, 0.0f, 0.0f));
	Viewport view(0, 0, 800, 600);
	view.scene = &scene;
	view.camera = &camera;

	window.addViewport(&view);

	while (!window.shouldClose()) {
		camera.transform.rotate(glm::vec3(window.getDeltaTime() * 30.0f, 0.0f, 0.0f));
		window.update();
	}
	window.close();
	return 0;
}