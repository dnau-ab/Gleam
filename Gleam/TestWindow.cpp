#include "TestUtils.h"

void testWindow() {
	Window window1("Test Window", 600, 400);
	double dt;
	assert(window1.shouldClose() == false);
	if (!window1.shouldClose()) {
		window1.update();
	}
	for (size_t i = 1; i < 6; i++) {
		unsigned long delay = i * 125;
		Sleep(delay);
		window1.update();
		dt = window1.getDeltaTime();
		cout << dt << endl;
		assert(_approxEqual(dt, delay/1000.0));
	}

	window1.close();
	assert(window1.shouldClose() == true);
}