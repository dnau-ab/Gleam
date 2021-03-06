#pragma once

#include <glad/glad.h>

#include <string>
#include <vector>
#include <iostream>

#include <GLFW/glfw3.h>
#include <glm/vec2.hpp>

#include "Texture.h"
#include "Viewport.h"

class Window {
private:
	static std::vector<Window*> _windows;
	
	static bool _backendReady;
	static void initBackend();

	static void keyCallSwitch(GLFWwindow* window, int key, int scancode, int action, int mods);
	static void mouseCallSwitch(GLFWwindow* window, double xPos, double yPos);
	static void scrollCallSwitch(GLFWwindow* window, double xOffset, double yOffset);
	static void framebufferSizeSwitch(GLFWwindow* window, int width, int height);

protected:
	std::string _title;
	glm::vec<2, unsigned> _size;
	glm::vec2 _scale;

	GLFWwindow* _window;
	std::vector<Viewport*> _viewports;
	double _deltaTime;

	/*TODO **Destructor** */
public:
	typedef void(*KeyCallback)(Window* window, int key, int scancode, int action, int mods);
	typedef void(*MouseCallback)(Window* window, double xPos, double yPos);
	typedef void(*ScrollCallback)(Window* window, double xOffset, double yOffset);
	typedef void (*FramebufferSizeCallback)(Window* window, int width, int height);

	KeyCallback keyCallback = nullptr;
	MouseCallback mouseCallback = nullptr;
	ScrollCallback scrollCallback = nullptr;
	FramebufferSizeCallback framebufferSizeCallback = nullptr;

	Window(std::string title, unsigned int width, unsigned int height);
	~Window();

	void addViewport(Viewport* viewport);
	void removeViewport(Viewport* viewport);
	void setCursorMode(int type);

	bool shouldClose();
	void close();

	double getDeltaTime();
	
	void update();
};