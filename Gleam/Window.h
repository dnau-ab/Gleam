#pragma once

#include <glad/glad.h>

#include <string>
#include <vector>
#include <iostream>

#include <GLFW/glfw3.h>
#include <glm/vec2.hpp>

#include "Texture.h"
#include "Viewport.h"
#include "Quad.h"

enum class AspectMode {
	LOCK = 0,
	STRETCH,
	FREE
};

class Window {
private:
	static std::vector<Window*> _windows;
	
	static bool _backendReady;
	static void initBackend();

	static void keyCallSwitch(GLFWwindow* window, int key, int scancode, int action, int mods);
	static void mouseCallSwitch(GLFWwindow* window, double xPos, double yPos);
	static void scrollCallSwitch(GLFWwindow* window, double xOffset, double yOffset);
	static void framebufferSizeSwitch(GLFWwindow* window, int width, int height);

	unsigned int _gBuffer = 0;
	unsigned int _gPosition = 0;
	unsigned int _gNormal = 0;
	unsigned int _gColorSpec = 0;

	unsigned int _lBuffer = 0;
	unsigned int _lColor = 0;

	std::unique_ptr<Quad> _screenQuad = nullptr;

	void initLBuffer();
	void initGBuffer();

protected:
	std::string _title;
	glm::vec<2, unsigned> _windowSize;
	glm::vec<2, unsigned> _resolution;
	float _aspectRatio;

	GLFWwindow* _window;
	std::vector<Viewport*> _viewports;
	double _deltaTime;

	// options
	AspectMode _aspectMode;
	bool _remakeFrameBuffer;

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

	Window(std::string title, unsigned int width, unsigned int height, unsigned int renderWidth, unsigned int renderHeight);
	~Window();

	void addViewport(Viewport* viewport);
	void removeViewport(Viewport* viewport);
	void setCursorMode(int type);

	void setResolution(unsigned int width, unsigned int height);
	void setResolution(const glm::vec<2, unsigned>& resolution);
	glm::vec<2, unsigned> getResolution() const;

	void setAspectMode(AspectMode mode);
	AspectMode getAspectMode();

	bool shouldClose();
	void close();

	double getDeltaTime();
	
	void update();
};