
//#define TESTING

#ifdef TESTING
	#include "TestUtils.h"
#endif
#include "Window.h"
#include "CameraFPS.h"

void keyHandler (Window* window, int key, int scancode, int action, int mods);
void mouseHandler (Window* window, double xPos, double yPos);

CameraFPS camera;
bool cameraEnabled;
uint8_t movement = Camera_Movement::NONE;

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
	window.keyCallback = keyHandler;
	window.mouseCallback = mouseHandler;

	Shader* shader = Shader::getDefault();
	Scene scene;
	unsigned radius = 30;
	unsigned numSami = 32;
	for (int i = 0; i < numSami; i++) {
		Model* varia = new Model("res/models/variasuit/DolBarriersuit.obj", shader);
		varia->transform.translate(glm::vec3(radius * glm::cos(glm::radians(i * (360.0f / numSami))), 0.0f, radius * glm::sin(glm::radians(i * (360.0f / numSami)))));
		varia->transform.rotate(glm::vec3(0.0f, -i * (360.0f / numSami) + 90.0f, 0.0f));
		scene.addRenderable(varia);
	}
	camera = CameraFPS(glm::vec3(0.0f, 10.0f, 80.0f));
	Viewport view(0, 0, WIDTH, HEIGHT);
	view.scene = &scene;
	view.camera = &camera;

	window.addViewport(&view);

	while (!window.shouldClose()) {
		float deltaTime = window.getDeltaTime();

		if (movement) {
			if (movement & Camera_Movement::FORWARD) {
				camera.processKeyboard(Camera_Movement::FORWARD, window.getDeltaTime());
			}
			if (movement & Camera_Movement::BACKWARD) {
				camera.processKeyboard(Camera_Movement::BACKWARD, window.getDeltaTime());
			}
			if (movement & Camera_Movement::LEFT) {
				camera.processKeyboard(Camera_Movement::LEFT, window.getDeltaTime());
			}
			if (movement & Camera_Movement::RIGHT) {
				camera.processKeyboard(Camera_Movement::RIGHT, window.getDeltaTime());
			}
			if (movement & Camera_Movement::UP) {
				camera.processKeyboard(Camera_Movement::UP, window.getDeltaTime());
			}
			if (movement & Camera_Movement::DOWN) {
				camera.processKeyboard(Camera_Movement::DOWN, window.getDeltaTime());
			}
			
		}
		window.update();
	}
	window.close();
	return 0;
}

void keyHandler(Window* window, int key, int scancode, int action, int mods) {
	if (action == GLFW_PRESS) {
		switch (key) {
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
	camera.processMouseMovement(xPos - lastX, lastY - yPos);

	lastX = xPos;
	lastY = yPos;
}