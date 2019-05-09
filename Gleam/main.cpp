
//#define TESTING

#ifdef TESTING
	#include "TestUtils.h"
#endif
#include "Window.h"
#include "CameraFPS.h"

void keyHandler (Window* window, int key, int scancode, int action, int mods);
void mouseHandler (Window* window, double xPos, double yPos);
void scrollHandler(Window* window, double xOffset, double yOffset);

CameraFPS camera;
bool cameraEnabled;
uint8_t movement = Camera_Movement::NONE;

constexpr unsigned HEIGHT = 1080;
constexpr unsigned WIDTH = (unsigned)(HEIGHT * 16 / 9.0);
float SCALE = 1.0f;

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
	
	Window window("Hello World!", WIDTH, HEIGHT, (unsigned)(WIDTH / SCALE), (unsigned)(HEIGHT / SCALE));
	window.keyCallback = keyHandler;
	window.mouseCallback = mouseHandler;
	window.scrollCallback = scrollHandler;

	std::shared_ptr<Mesh> variaMesh = MeshLoader::loadMesh("res/models/variasuit/", "DolBarriersuit.obj", true);
	Shader* shader = Shader::getDefault();
	Scene scene;
	Scene aScene;
	unsigned radius = 30;
	unsigned numSami = 24;
	for (int i = 0; i < numSami; i++) {
		Model* varia = new Model(variaMesh, shader);
		varia->transform.translate(glm::vec3(radius * glm::cos(glm::radians(i * (360.0f / numSami))), 0.0f, radius * glm::sin(glm::radians(i * (360.0f / numSami)))));
		varia->transform.rotate(glm::vec3(0.0f, -i * (360.0f / numSami) + 90.0f, 0.0f));
		scene.addRenderable(varia);
	}
	camera = CameraFPS(glm::vec3(0.0f, 10.0f, 80.0f));
	Viewport view(0, 0, WIDTH / SCALE, HEIGHT / SCALE);
	view.scene = &scene;
	view.camera = &camera;

	constexpr float numHorz = 1;
	constexpr float numVert = 1;
	const float vWidth = 1.0f / numHorz;
	const float vHeight = 1.0f / numVert;
	std::vector<std::unique_ptr<Viewport> > viewports;
	for (size_t i = 0; i < numHorz; i++) {
		for (size_t j = 0; j < numVert; j++) {
			float posX = i*vWidth;
			float posY = j*vHeight;
			viewports.emplace_back(std::make_unique<Viewport>(posX, posY, vWidth, vHeight));
		}
	}
	
	for (auto& viewport : viewports) {
		viewport->scene = &scene;
		viewport->camera = &camera;
		window.addViewport(viewport.get());
	}


	//window.addViewport(&view);

	DirectionalLight dLight({ 0.2f, 0.2f, 0.2f }, { 0.5f, 0.5f, 0.5f }, { 1.0f, 1.0f, 1.0f }, { 5, 5, 5 });
	scene.addLight(&dLight);

	PointLight pLight({ 0.1, 0.1, 0.1 }, { 1, 0.5, 0.2 }, { 0.2, 0.2, 0.2 }, 0, 0, 0, { 5, 5, 5 });
	scene.addLight(&pLight);

	aScene = scene;
	scene.removeLight(&pLight);
	scene.removeLight(&dLight);
	viewports[0]->scene = &aScene;

	while (!window.shouldClose()) {
		float deltaTime = (float)window.getDeltaTime();
		float time = (float)glfwGetTime();

		if (movement) {
			if (movement & Camera_Movement::FORWARD) {
				camera.processKeyboard(Camera_Movement::FORWARD, deltaTime);
			}
			if (movement & Camera_Movement::BACKWARD) {
				camera.processKeyboard(Camera_Movement::BACKWARD, deltaTime);
			}
			if (movement & Camera_Movement::LEFT) {
				camera.processKeyboard(Camera_Movement::LEFT, deltaTime);
			}
			if (movement & Camera_Movement::RIGHT) {
				camera.processKeyboard(Camera_Movement::RIGHT, deltaTime);
			}
			if (movement & Camera_Movement::UP) {
				camera.processKeyboard(Camera_Movement::UP, deltaTime);
			}
			if (movement & Camera_Movement::DOWN) {
				camera.processKeyboard(Camera_Movement::DOWN, deltaTime);
			}
		}

		pLight.position = glm::vec3(sin(time) * (radius+5), 5, cos(time) * (radius+5));

		window.update();
	}
	window.close();

	return 0;
}

void keyHandler(Window* window, int key, int scancode, int action, int mods) {
	if (action == GLFW_PRESS) {
		switch (key) {
		case GLFW_KEY_3:
			glPolygonMode(GL_FRONT_AND_BACK, GL_FILL); // fill mode
			break;
		case GLFW_KEY_4:
			glPolygonMode(GL_FRONT_AND_BACK, GL_LINE); // wireframe mode
			break;
		case GLFW_KEY_5:
			glPolygonMode(GL_FRONT_AND_BACK, GL_POINT); // point mode
			break;
		case GLFW_KEY_W:
			movement |= Camera_Movement::FORWARD;
			break;
		case GLFW_KEY_S:
			movement |= Camera_Movement::BACKWARD;
			break;
		case GLFW_KEY_A:
			movement |= Camera_Movement::LEFT;
			break;
		case GLFW_KEY_D:
			movement |= Camera_Movement::RIGHT;
			break;
		case GLFW_KEY_SPACE:
			movement |= Camera_Movement::UP;
			break;
		case GLFW_KEY_LEFT_SHIFT:
			movement |= Camera_Movement::DOWN;
			break;
		case GLFW_KEY_1:
			window->setCursorMode(GLFW_CURSOR_DISABLED);
			cameraEnabled = true;
			break;
		case GLFW_KEY_2:
			window->setCursorMode(GLFW_CURSOR_NORMAL);
			cameraEnabled = false;
			break;
		case GLFW_KEY_6:
			window->setAspectMode(AspectMode::LOCK);
			break;
		case GLFW_KEY_7:
			window->setAspectMode(AspectMode::STRETCH);
			break;
		case GLFW_KEY_8:
			window->setAspectMode(AspectMode::FREE);
			break;
		case GLFW_KEY_ESCAPE:
			window->close();
			break;
		default:
			break;
		}
	}
	else if (action == GLFW_RELEASE) {
		switch (key) {
		case GLFW_KEY_W:
			movement &= ~Camera_Movement::FORWARD;
			break;
		case GLFW_KEY_S:
			movement &= ~Camera_Movement::BACKWARD;
			break;
		case GLFW_KEY_A:
			movement &= ~Camera_Movement::LEFT;
			break;
		case GLFW_KEY_D:
			movement &= ~Camera_Movement::RIGHT;
			break;
		case GLFW_KEY_SPACE:
			movement &= ~Camera_Movement::UP;
			break;
		case GLFW_KEY_LEFT_SHIFT:
			movement &= ~Camera_Movement::DOWN;
		}
	}
}

void mouseHandler(Window* window, double xPos, double yPos) {
	static double lastX = xPos, lastY = yPos;

	if (!cameraEnabled) return;
	printf("X: %f\nY: %f\n\n", xPos - lastX, yPos - lastY);
	camera.processMouseMovement((float)(xPos - lastX), (float)(lastY - yPos));

	lastX = xPos;
	lastY = yPos;
}

void scrollHandler(Window* window, double xOffset, double yOffset) {
	float deltaResolution = 0.1f * SCALE * yOffset;
	SCALE += deltaResolution;

	window->setResolution(WIDTH / SCALE, HEIGHT / SCALE);
}