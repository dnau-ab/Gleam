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

	static std::vector<Window*> _windows;
	
	static bool _backendReady;
	static bool initBackend();

	static void keyCallSwitch(GLFWwindow* window, int key, int scancode, int action, int mods);
	static void mouseCallSwitch(GLFWwindow* window, double xPos, double yPos);
	static void scrollCallSwitch(GLFWwindow* window, double xOffset, double yOffset);
	static void framebufferSizeCallback(GLFWwindow* window, int width, int height);

	std::string _title;
	GLFWwindow* _window;
	std::vector<Viewport*> _viewports;
	double _deltaTime;

	/*TODO **Destructor** */
public:
	typedef void(*KeyCallback)(Window* window, int key, int scancode, int action, int mods);
	typedef void(*MouseCallback)(Window* window, double xPos, double yPos);
	typedef void(*ScrollCallback)(Window* window, double xOffset, double yOffset);

	KeyCallback keyCallback = nullptr;
	MouseCallback mouseCallback = nullptr;
	ScrollCallback scrollCallback = nullptr;

	void addViewport(Viewport* viewport);
	void removeViewport(Viewport* viewport);

	bool shouldClose();
	void close();

	double getDeltaTime();
	
	void update();
};