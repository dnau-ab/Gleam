#include "TestUtils.h"

void testScene() {
	Scene scene;
	assert(scene.getRenderables().size() == 0);
	assert(scene.getLights().size() == 0);

	// Make light objects
	//Light l(glm::vec3(), glm::vec3(), glm::vec3());
	PointLight pl(glm::vec3(1.0f, 1.0f, 1.0f), glm::vec3(1.0f, 1.0f, 1.0f), glm::vec3(1.0f, 1.0f, 1.0f), glm::vec3(1.0f, 1.0f, 1.0f));
	DirectionalLight dl(glm::vec3(1.0f, 1.0f, 1.0f), glm::vec3(1.0f, 1.0f, 1.0f), glm::vec3(1.0f, 1.0f, 1.0f), glm::vec3(1.0f, 1.0f, 1.0f));
	SpotLight sl(glm::vec3(1.0f, 1.0f, 1.0f), glm::vec3(1.0f, 1.0f, 1.0f), glm::vec3(1.0f, 1.0f, 1.0f), glm::vec3(1.0f, 1.0f, 1.0f), glm::vec3(1.0f, 1.0f, 1.0f), 1.0f);
	
	// add lights
	scene.addLight(&pl);
	scene.addLight(&dl);
	scene.addLight(&sl);
	assert(scene.getLights().size() == 3);

	// remove lights
	scene.removeLight(&pl);
	scene.removeLight(&dl);
	scene.removeLight(&sl);
	assert(scene.getLights().size() == 0);

	// Make renderable objects

	// add renderables

	// remove renderables

}