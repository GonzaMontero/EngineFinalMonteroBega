#include "glew.h"
#include "glfw3.h"

#include "Window.h"
#include <iostream>

namespace Engine {
	Window::Window(int width, int height, const char* name)
	{
		_height = height;
		_width = width;

		_window = glfwCreateWindow(_width, _height, name, NULL, NULL);
	}

	Window::~Window() {

	}

	void Window::InitWindow()
	{
		glfwMakeContextCurrent(_window);
	}

	GLFWwindow* Window::GetWindow() {
		return _window;
	}

	int Window::GetWidth() {
		return _width;
	}

	int Window::GetHeight() {
		return _height;
	}
}