#include "Window.h"

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

void Window::framebufferSizeCallback(GLFWwindow* window, int width, int height) {
	_scale.x = width / _size.x;
	_scale.y = height / _size.y;
}

bool Window::initBackend() {
	bool backendReady = glfwInit();
	glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
	glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
	glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
#ifdef __APPLE__
	glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE); // needed for Mac
#endif
	return Window::_backendReady;
}

void Window::addViewport(Viewport* viewport) {
	_viewports.push_back(viewport);
}

void Window::removeViewport(Viewport* viewport) {
	auto itr = std::find(_viewports.begin(), _viewports.end(), viewport);
	if (itr != _viewports.end()) {
		_viewports.erase(itr);
	}
}

bool Window::shouldClose() {
	return glfwWindowShouldClose(_window);
}

void Window::close() {
	glfwSetWindowShouldClose(_window, true);
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
		glm::vec2 vpPos;
		glm::vec2 vpSize;
		for (Viewport*& viewport : _viewports) {
			vpPos = viewport->getPosition() * _scale;
			vpSize = viewport->getSize() * _scale;
			glViewport(vpPos.x, vpPos.y, vpSize.x, vpSize.y);
			glScissor(vpPos.x, vpPos.y, vpSize.x, vpSize.y);
			glClearColor(0.3, 0.3, 0.31, 1.0);
			glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT | GL_STENCIL_BUFFER_BIT);

			viewport->render();
		}

		glfwPollEvents();
		glfwSwapBuffers(_window);
	}
}