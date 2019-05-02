#include "Window.h"

bool Window::_backendReady = false;

std::vector<Window*> Window::_windows;

void Window::keyCallSwitch(GLFWwindow* window, int key, int scancode, int action, int mods) {
	for (size_t i = 0; i < _windows.size(); i++) {
		if (window == _windows[i]->_window) {
			if (_windows[i]->keyCallback != nullptr) {
				_windows[i]->keyCallback(_windows[i], key, scancode, action, mods);
				break;
			}
		}
	}
}

void Window::mouseCallSwitch(GLFWwindow* window, double xPos, double yPos) {
	for (size_t i = 0; i < _windows.size(); i++) {
		if (window == _windows[i]->_window) {
			if (_windows[i]->mouseCallback != nullptr) {
				_windows[i]->mouseCallback(_windows[i], xPos, yPos);
				break;
			}
		}
	}
}

void Window::scrollCallSwitch(GLFWwindow* window, double xOffset, double yOffset) {
	for (size_t i = 0; i < _windows.size(); i++) {
		if (window == _windows[i]->_window) {
			if (_windows[i]->scrollCallback != nullptr) {
				_windows[i]->scrollCallback(_windows[i], xOffset, yOffset);
				break;
			}
		}
	}
}

void Window::framebufferSizeSwitch(GLFWwindow* window, int width, int height) {
	for (size_t i = 0; i < _windows.size(); i++) {
		if (window == _windows[i]->_window) {
			// always update window scale
			_windows[i]->_scale.x = (float)width / _windows[i]->_size.x;
			_windows[i]->_scale.y = (float)height / _windows[i]->_size.y;
			// call callback if it exists
			if (_windows[i]->framebufferSizeCallback != nullptr) {
				_windows[i]->framebufferSizeCallback(_windows[i], width, height);
				break;
			}
		}
	}
}

void Window::initBackend() {
	_backendReady = glfwInit();
	glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
	glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
	glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
#ifdef __APPLE__
	glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE); // needed for Mac
#endif
}

Window::Window(std::string title, unsigned int width, unsigned int height) {
	_size.x = width;
	_size.y = height;
	_title = title;

	if (!_backendReady) {
		initBackend();
	}
	if (_backendReady) {
		_window = glfwCreateWindow(_size.x, _size.y, _title.c_str(), nullptr, nullptr);
		if (!_window) {
			std::cout << "Failed to create GLFW window" << std::endl;
			glfwTerminate();
			exit(1);
		}
		glfwMakeContextCurrent(_window);

		// set callbacks
		glfwSetFramebufferSizeCallback(_window, framebufferSizeSwitch);
		glfwSetKeyCallback(_window, keyCallSwitch);
		glfwSetCursorPosCallback(_window, mouseCallSwitch);
		glfwSetScrollCallback(_window, scrollCallSwitch);
		//glfwSetInputMode(_window, GLFW_CURSOR, GLFW_CURSOR_DISABLED);

		// initialize GLAD
		// load all OpenGL function pointers
		if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress)) {
			std::cout << "Failed to initialize GLAD" << std::endl;
			exit(1);
		}
		glEnable(GL_DEPTH_TEST);
		glEnable(GL_SCISSOR_TEST);
		glEnable(GL_STENCIL_TEST);
		glStencilOp(GL_KEEP, GL_KEEP, GL_REPLACE);

		Window::_windows.push_back(this);
		framebufferSizeSwitch(_window, _size.x, _size.y);
	}
}

Window::~Window() {
	close();
}

void Window::addViewport(Viewport* viewport) {
	if (viewport != nullptr) {
		_viewports.push_back(viewport);
	}
}

void Window::removeViewport(Viewport* viewport) {
	auto itr = std::find(_viewports.begin(), _viewports.end(), viewport);
	if (itr != _viewports.end()) {
		_viewports.erase(itr);
	}
}

bool Window::shouldClose() {
	return (_window ? glfwWindowShouldClose(_window) : true);
}

void Window::close() {
	if (_window != nullptr) {
		glfwSetWindowShouldClose(_window, GLFW_TRUE);
		glfwDestroyWindow(_window);
		_window = nullptr;
	}
}

double Window::getDeltaTime() {
	return _deltaTime;
}

void Window::update() {
	static double lastTime = glfwGetTime();
	static double lastCheck = glfwGetTime();
	static int numFrames = 0;
	if (!glfwWindowShouldClose(_window)) {
		// calculate draw time
		numFrames++;
		_deltaTime = glfwGetTime() - lastCheck;
		lastCheck = glfwGetTime();
		if (glfwGetTime() - lastTime >= 1.0) {
			// update title
			glfwSetWindowTitle(_window, (_title + " " + std::to_string(1000.0 / double(numFrames)) + "ms").c_str());
			numFrames = 0;
			lastTime += 1.0;
		}

		// input
		//processInput(window);

		// render
		glm::vec<2, int> vpPos;
		glm::vec<2, unsigned> vpSize;
		for (Viewport*& viewport : _viewports) {
			vpPos = viewport->getPosition() * _scale;
			vpSize = viewport->getSize() * _scale;
			glViewport(vpPos.x, vpPos.y, vpSize.x, vpSize.y);
			glScissor(vpPos.x, vpPos.y, vpSize.x, vpSize.y);
			glClearColor(0.3f, 0.3f, 0.31f, 1.0f);
			glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT | GL_STENCIL_BUFFER_BIT);

			viewport->render();
		}

		glfwPollEvents();
		glfwSwapBuffers(_window);
	}
}