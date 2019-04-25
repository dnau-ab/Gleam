#include "TestUtils.h"

void testWindow() {
	Window w2("Taxes", 1, 1);
	Window window1("", 1, 1);
	float dt;
	assert(window1.shouldClose() == false);
	if (!window1.shouldClose()) {
		window1.update();
	}
	Sleep(100);
	window1.update();
	dt = window1.getDeltaTime();
	cout << dt << endl;
	assert(_approxEqual(dt, 0.1));
	Sleep(250);
	window1.update();
	dt = window1.getDeltaTime();
	cout << dt << endl;
	assert(_approxEqual(dt, 0.250));
	Sleep(500);
	window1.update();
	dt = window1.getDeltaTime();
	cout << dt << endl;
	assert(_approxEqual(dt, 0.5));

	window1.close();
	assert(window1.shouldClose() == true);
}