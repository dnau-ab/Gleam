
#include "TestUtils.h"

int main() {
	Window w("Gleam", 800, 600);

	testWindow();
	testTransform();
	testTexture();
	testScene();

	return 0;
}