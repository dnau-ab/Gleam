
//#define TESTING

#ifdef TESTING
	#include "TestUtils.h"
#endif
#include "Window.h"
#include "CameraFree.h"
#include "Cube.h"
#include "Sphere.h"
#include "Cone.h"
#include "Cylinder.h"

void keyHandler (Window* window, int key, int scancode, int action, int mods);
void mouseHandler (Window* window, double xPos, double yPos);
void scrollHandler(Window* window, double xOffset, double yOffset);

CameraFree camera(glm::vec3(0.0f, 10.0f, 80.0f));
bool cameraEnabled;
uint8_t movement = Camera_Movement::NONE;

constexpr unsigned HEIGHT = 720;
constexpr unsigned WIDTH = (unsigned)(HEIGHT * 16 / 9.0);
float SCALE = 1.0f;

int main() {
#ifdef TESTING
	Window w("Gleam", 800, 600, 800, 600);
	Window w2("Taxes", 600, 400, 600, 400);
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
	w.close();
	w2.close();
#endif

	Window window("Hello World!", WIDTH, HEIGHT, (unsigned)(WIDTH / SCALE), (unsigned)(HEIGHT / SCALE));
	window.keyCallback = keyHandler;
	window.mouseCallback = mouseHandler;
	window.scrollCallback = scrollHandler;

	std::shared_ptr<Mesh> variaMesh = MeshLoader::loadMesh("res/models/variasuit/", "DolBarriersuit.obj", true);
	//std::shared_ptr<Mesh> variaMesh = MeshLoader::loadMesh("res/models/bulbasaur/", "Pokemon.obj", true);
	if (variaMesh) {
		std::cout << variaMesh.get()->numOfSubMeshes() << std::endl;
	}
	Shader* shader = Shader::getDefault();
	Scene scene;
	Scene aScene;
	unsigned radius = 30;
	unsigned numSami = 6;
	for (int i = 0; i < (int)numSami; i++) {
		Model* varia = new Model(variaMesh, shader);
		//varia->transform.scale({ 20.1f, 20.1f, 20.1f });
		varia->transform.translate(glm::vec3(radius * glm::cos(glm::radians(i * (360.0f / numSami))), 0.0f, radius * glm::sin(glm::radians(i * (360.0f / numSami)))));
		varia->transform.rotate(glm::vec3(0.0f, -i * (360.0f / numSami) + 90.0f, 0.0f));
		scene.addRenderable(varia);
	}

	Model samus(variaMesh);
	samus.transform.scale({ 0.25, 0.25, 0.25 });
	samus.transform.translate({ 0, 15, 0 });
	scene.addRenderable(&samus);

	// add floor quad
	Quad* quad = new Quad(Shader::getDefault());
	quad->transform.translate({ 0, -0.1, 0 });
	quad->transform.scale({ 100000, 100000, 1 });
	quad->transform.rotate({ -90, 0, 0 });
	scene.addRenderable(quad);

	Cube cube;
	cube.transform.translate({ 0, 2.5, 0 });
	cube.material.addTexture(Texture("res/desert.png", "diffuse"));
	scene.addRenderable(&cube);
	
	Sphere sphere;
	sphere.transform.translate({ 0, 5, 0 });
	sphere.material.addTexture(Texture("res/desert.png", "diffuse"));
	scene.addRenderable(&sphere);
	
	Cone cone;
	cone.transform.translate({ 0, 8, 0 });
	scene.addRenderable(&cone);

	Cylinder cylinder;
	cylinder.transform.translate({ 0, 11, 0 });
	scene.addRenderable(&cylinder);
	
	Viewport view(0, 0, 1.0f, 1.0f);
	view.scene = &scene;
	view.camera = &camera;

	Shader skyboxShader("res/shaders/gleam_default_skybox_shader.vert", "res/shaders/gleam_default_skybox_shader.frag");
	std::vector<std::string> faces{
			"res/arrakisday_rt.tga",
			"res/arrakisday_lf.tga",
			"res/arrakisday_up.tga",
			"res/arrakisday_dn.tga",
			"res/arrakisday_ft.tga",
			"res/arrakisday_bk.tga"
	};
	Skybox skybox(faces, &skyboxShader);
	view.setSkybox(&skybox);

	/*
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
	*/
	window.addViewport(&view);

	DirectionalLight dLight({ 0.2f, 0.2f, 0.2f }, { 0.5f, 0.5f, 0.5f }, { 1.0f, 1.0f, 1.0f }, { 5, 5, 5 });
	scene.addLight(&dLight);

	PointLight pLight({ 0.1, 0.1, 0.1 }, { 1, 0.5, 0.2 }, { 0.2, 0.2, 0.2 }, 0, 0, 0, { 5, 5, 5 });
	scene.addLight(&pLight);

	while (!window.shouldClose()) {
		float deltaTime = (float)window.getDeltaTime();
		float time = (float)glfwGetTime();

		camera.update(deltaTime);

		pLight.position = glm::vec3(sin(time) * (radius+5), 6 + 5 * sin(time), cos(time) * (radius+5));

		cube.transform.rotate({ 0, 50 * window.getDeltaTime(), 0 });
		sphere.transform.rotate({ 0, 60 * window.getDeltaTime(), 0 });
		cone.transform.rotate({ 0, 70 * window.getDeltaTime(), 0 });
		cylinder.transform.rotate({ 0, 90 * window.getDeltaTime(), 0 });

		samus.transform.rotate({ 0, 100 * window.getDeltaTime(), 0 });
		
		float scale = 1 + sin(time) * 0.5f;
		cube.transform.setScale({ scale, scale, scale });

		dLight.direction = glm::normalize(glm::vec3(5*cos(time), 0, 5 * sin(time)));
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
			camera.setMovement(Camera_Movement::FORWARD);
			break;
		case GLFW_KEY_S:
			camera.setMovement(Camera_Movement::BACKWARD);
			break;
		case GLFW_KEY_A:
			camera.setMovement(Camera_Movement::LEFT);
			break;
		case GLFW_KEY_D:
			camera.setMovement(Camera_Movement::RIGHT);
			break;
		case GLFW_KEY_SPACE:
			camera.setMovement(Camera_Movement::UP);
			break;
		case GLFW_KEY_LEFT_SHIFT:
			camera.setMovement(Camera_Movement::DOWN);
			break;
		case GLFW_KEY_Q:
			camera.setMovement(Camera_Movement::ROLL_LEFT);
			break;
		case GLFW_KEY_E:
			camera.setMovement(Camera_Movement::ROLL_RIGHT);
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
			camera.unsetMovement(Camera_Movement::FORWARD);
			break;
		case GLFW_KEY_S:
			camera.unsetMovement(Camera_Movement::BACKWARD);
			break;
		case GLFW_KEY_A:
			camera.unsetMovement(Camera_Movement::LEFT);
			break;
		case GLFW_KEY_D:
			camera.unsetMovement(Camera_Movement::RIGHT);
			break;
		case GLFW_KEY_SPACE:
			camera.unsetMovement(Camera_Movement::UP);
			break;
		case GLFW_KEY_LEFT_SHIFT:
			camera.unsetMovement(Camera_Movement::DOWN);
			break;
		case GLFW_KEY_Q:
			camera.unsetMovement(Camera_Movement::ROLL_LEFT);
			break;
		case GLFW_KEY_E:
			camera.unsetMovement(Camera_Movement::ROLL_RIGHT);
			break;
		}
	}
}

void mouseHandler(Window* window, double xPos, double yPos) {
	static double lastX = xPos, lastY = yPos;

	if (!cameraEnabled) return;
	camera.processMouseMovement((float)(xPos - lastX), (float)(yPos - lastY));

	lastX = xPos;
	lastY = yPos;
}

void scrollHandler(Window* window, double xOffset, double yOffset) {
	float deltaResolution = 0.1f * SCALE * (float)yOffset;
	SCALE += deltaResolution;

	window->setResolution((unsigned int)(WIDTH / SCALE), (unsigned int)(HEIGHT / SCALE));
}