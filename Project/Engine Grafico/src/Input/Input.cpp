#include "glew.h"
#include "glfw3.h"
#include "../Window/Window.h"

#include <algorithm>

#include "input.h"

namespace Engine {

	void KeyCallback(GLFWwindow* window, int key, int scanCode, int action, int mods);
	void MouseCallback(GLFWwindow* window, double xPos, double yPos);

	std::list<int> currentKeysDown;
	glm::vec2 mousePos;

	Engine::Input::Input(Window* window)
	{
		glfwSetKeyCallback(window->GetWindow(), KeyCallback);
		glfwSetCursorPosCallback(window->GetWindow(), MouseCallback);
	}

	Engine::Input::~Input()
	{

	}

	bool Engine::Input::IsKeyPressed(int keyCode, Window* window)
	{
		int keyPressed = glfwGetKey(window->GetWindow(), keyCode);
		return keyPressed == GLFW_PRESS;
	}

	bool Engine::Input::IsKeyDown(int keyCode, Window* window)
	{
		std::list<int>::iterator it = find(currentKeysDown.begin(), currentKeysDown.end(), keyCode);

		if (it != currentKeysDown.end())
		{
			currentKeysDown.remove(keyCode);
			return true;
		}

		return false;
	}

	glm::vec2 Engine::Input::GetMousePosition()
	{
		return mousePos;
	}

	void KeyCallback(GLFWwindow* window, int key, int scanCode, int action, int mods)
	{
		if (action == GLFW_PRESS)
			currentKeysDown.push_front(key);
		else if (action == GLFW_RELEASE)
			currentKeysDown.remove(key);
	}

	void MouseCallback(GLFWwindow* window, double xPos, double yPos)
	{
		mousePos = glm::vec2(xPos, yPos);
	}
}