
#include "TestUtils.h"

int main() {
	Window w("Gleam", 800, 600);

	testShaderResource();
	testWindow();
	testTransform();
	testTexture();
	testScene();
	testMeshLoader();
	testModel();

	return 0;
}