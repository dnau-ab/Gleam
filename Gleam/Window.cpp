#include "Window.h"

bool Window::_backendReady = false;

std::vector<Window*> Window::_windows;

void Window::keyCallSwitch(GLFWwindow* window, int key, int scancode, int action, int mods) {
	//std::cout << "Meta-key handler called!" << std::endl;
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
			_windows[i]->_size.x = (unsigned) width;
			_windows[i]->_size.y = (unsigned) height;

			
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

void Window::initGBuffer() {

	if (_gBuffer > 0) {
		// delete and recreate buffer/textures
		glDeleteBuffers(1, &_gBuffer);
		glDeleteTextures(1, &_gPosition);
		glDeleteTextures(1, &_gNormal);
		glDeleteTextures(1, &_gColorSpec);
	}

	glm::vec<2, unsigned> size = glm::vec2(_resolution);

	glGenFramebuffers(1, &_gBuffer);
	glBindFramebuffer(GL_FRAMEBUFFER, _gBuffer);

	// position color buffer
	glGenTextures(1, &_gPosition);
	glBindTexture(GL_TEXTURE_2D, _gPosition);
	glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB16F, size.x, size.y, 0, GL_RGB, GL_FLOAT, NULL);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
	glFramebufferTexture2D(GL_FRAMEBUFFER, GL_COLOR_ATTACHMENT0, GL_TEXTURE_2D, _gPosition, 0);

	// normal color buffer
	glGenTextures(1, &_gNormal);
	glBindTexture(GL_TEXTURE_2D, _gNormal);
	glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB16F, size.x, size.y, 0, GL_RGB, GL_FLOAT, NULL);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
	glFramebufferTexture2D(GL_FRAMEBUFFER, GL_COLOR_ATTACHMENT1, GL_TEXTURE_2D, _gNormal, 0);

	// color + specular color buffer
	glGenTextures(1, &_gColorSpec);
	glBindTexture(GL_TEXTURE_2D, _gColorSpec);
	glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, size.x, size.y, 0, GL_RGBA, GL_UNSIGNED_BYTE, NULL);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
	glFramebufferTexture2D(GL_FRAMEBUFFER, GL_COLOR_ATTACHMENT2, GL_TEXTURE_2D, _gColorSpec, 0);

	// add attachments to framebuffer 
	unsigned int attachments[3] = { GL_COLOR_ATTACHMENT0, GL_COLOR_ATTACHMENT1, GL_COLOR_ATTACHMENT2 };
	glDrawBuffers(3, attachments);

	// create and attach depth buffer
	unsigned int rboDepth;
	glGenRenderbuffers(1, &rboDepth);
	glBindRenderbuffer(GL_RENDERBUFFER, rboDepth);
	glRenderbufferStorage(GL_RENDERBUFFER, GL_DEPTH_COMPONENT, size.x, size.y);
	glFramebufferRenderbuffer(GL_FRAMEBUFFER, GL_DEPTH_ATTACHMENT, GL_RENDERBUFFER, rboDepth);

	// check that framebuffer is complete
	if (glCheckFramebufferStatus(GL_FRAMEBUFFER) != GL_FRAMEBUFFER_COMPLETE) {
		std::cout << "VIEWPORT::Framebuffer not complete!" << std::endl;
	}
	glBindFramebuffer(GL_FRAMEBUFFER, 0);
}

Window::Window(std::string title, unsigned int width, unsigned int height, unsigned int renderWidth, unsigned int renderHeight) : _scale(1.0f, 1.0f) {
	_size.x = width;
	_size.y = height;
	_resolution.x = renderWidth;
	_resolution.y = renderHeight;
	_aspectRatio = renderWidth / (float)renderHeight;
	_title = title;

	_aspectMode = AspectMode::LOCK;

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

		// window options
		glfwSetWindowSizeLimits(_window, 800, 600, 10000, 10000);

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
		//glStencilOp(GL_KEEP, GL_KEEP, GL_REPLACE);

		_screenQuad = std::make_unique<Quad>();

		Window::_windows.push_back(this);
		framebufferSizeSwitch(_window, _size.x, _size.y);
		initGBuffer();
	}
}

Window::~Window() {
	close();
	if (_gBuffer > 0) {
		// delete and recreate buffer/textures
		glDeleteBuffers(1, &_gBuffer);
		glDeleteTextures(1, &_gPosition);
		glDeleteTextures(1, &_gNormal);
		glDeleteTextures(1, &_gColorSpec);
	}
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
		_windows.erase(std::find(_windows.begin(), _windows.end(), this));
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
	if (!shouldClose()) {
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

		// render
		glClearColor(0.0f, 0.0f, 0.0f, 1.0f);
		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

		// geometry pass
		glBindFramebuffer(GL_FRAMEBUFFER, _gBuffer);
		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

		glm::vec<2, int> vpPos;
		glm::vec<2, unsigned> vpSize;
		for (Viewport*& viewport : _viewports) {
			vpPos = viewport->getPosition();
			vpSize = viewport->getSize();
			glViewport(vpPos.x, vpPos.y, vpSize.x, vpSize.y);
			glScissor(vpPos.x, vpPos.y, vpSize.x, vpSize.y);
			viewport->renderGeometry();
		}
		glBindFramebuffer(GL_FRAMEBUFFER, 0);
		
		// lighting pass
		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
		glActiveTexture(GL_TEXTURE0);
		glBindTexture(GL_TEXTURE_2D, _gPosition);
		glActiveTexture(GL_TEXTURE1);
		glBindTexture(GL_TEXTURE_2D, _gNormal);
		glActiveTexture(GL_TEXTURE2);
		glBindTexture(GL_TEXTURE_2D, _gColorSpec);

		glm::vec<2, unsigned> size = glm::vec2(_resolution);
		if (_aspectMode == AspectMode::STRETCH || _aspectMode == AspectMode::FREE) {
			glViewport(0, 0, _size.x, _size.y);
			glScissor(0, 0, _size.x, _size.y);
		}
		else {
			float windowAspect = _size.x / (float) _size.y;
			unsigned int diff = 0;
			float viewportRatio = 0;
			if (_aspectRatio - windowAspect < 0.0) {
				// clamp x
				diff = glm::abs(_size.x - _size.y * _aspectRatio) / 2.0f;
				glViewport(0 + diff, 0, _size.x - diff * 2, _size.y);
				glScissor(0 + diff, 0, _size.x - diff * 2, _size.y);
				viewportRatio = (_size.x - 2 * diff) / (float)_size.y;
			}
			else {
				// clamp y
				diff = glm::abs(_size.y - _size.x * (1 / _aspectRatio)) / 2.0f;
				glViewport(0, 0 + diff, _size.x, _size.y - diff * 2);
				glScissor(0, 0 + diff, _size.x, _size.y - diff * 2);
				viewportRatio = (float)_size.x / (size.y - 2 * diff);
			}
			diff = 1 + 1;
		}

		for (Viewport*& viewport : _viewports) {
			viewport->renderLighting();
			// render quad
			_screenQuad->render(glm::mat4(1.0f), glm::mat4(1.0f));
		}
		// copy geometry's depth buffer to default framebuffer's depth buffer
		glBindFramebuffer(GL_READ_FRAMEBUFFER, _gBuffer);
		glBindFramebuffer(GL_DRAW_FRAMEBUFFER, 0); // write to default framebuffer
		// blit to default framebuffer
		glBlitFramebuffer(0, 0, size.x, size.y, 0, 0, _size.x, _size.y, GL_DEPTH_BUFFER_BIT, GL_NEAREST);
		glBindFramebuffer(GL_FRAMEBUFFER, 0);

		glViewport(0, 0, _size.x, _size.y);
		glScissor(0, 0, _size.x, _size.y);

		// forward rendered lights here vvv

		if (_window != nullptr) {
			glfwSwapBuffers(_window);
		}
		glfwPollEvents();
	}
	else {
		close();
	}
}

/*
	GLFW_CURSOR_DISABLED
	GLFW_CURSOR_NORMAL
	GLFW_CURSOR_HIDDEN
*/
void Window::setCursorMode(int type) {
	glfwSetInputMode(_window, GLFW_CURSOR, type);
}

void Window::setResolution(unsigned int width, unsigned int height) {
	setResolution(glm::vec<2, unsigned>(width, height));
}

void Window::setResolution(const glm::vec<2, unsigned>& resolution) {
	_resolution = resolution;
	_aspectRatio = resolution.x / (float)resolution.y;
}

glm::vec<2, unsigned> Window::getResolution() const {
	return _resolution;
}

void Window::setAspectMode(AspectMode mode) {
	_aspectMode = mode;
	initGBuffer();
}

AspectMode Window::getAspectMode() {
	return _aspectMode;
}
