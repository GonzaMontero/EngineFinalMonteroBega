#include "glew.h"
#include "glfw3.h"

#include "Window.h"
#include <iostream>

using namespace Engine;



Window::Window() {
	_window = NULL;
	_width = 800;
	_height = 600;
}

Engine::Window::Window(int width, int height, std::string name)
{
	_height = height;
	_width = width;

	_window = glfwCreateWindow(_width, _height, &name[0], NULL, NULL);
	if (_window == NULL)
	{
		std::cout << "Failed to create GLFW window" << std::endl;
		glfwTerminate();
	}
}

Window::~Window() {

}

void Engine::Window::InitWindow()
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