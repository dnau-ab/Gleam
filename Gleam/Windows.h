#pragma once

#include <string>
#include <vector>
#include <iostream>

#include <GLFW/glfw3.h>
#include <glm/vec2.hpp>

#include "Viewport.h"

class Window {
private:
	static glm::vec2 _size;
	static glm::vec2 _scale;
	std::string _title;
	GLFWwindow* _window;
	std::vector<Viewport*> _viewports;
	double _deltaTime;

	void initBackend();
	/*TODO handle callbacks. Static reference table? **Destructor** */
public:
	void addViewport(Viewport* viewport);
	void removeViewport(Viewport* viewport);

	bool shouldClose();
	void close();

	double getDeltaTime();
	
	void update();
};