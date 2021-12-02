#include "glew.h"
#include "glfw3.h"

#include "input.h"

Input::Input() {
    _window = NULL;
    mousePosition = glm::vec3(1.0f);
}
Input::Input(GLFWwindow* window) {
    _window = window;
    mousePosition = glm::vec3(1.0f);
}
Input::~Input() {
    if (_window) _window = NULL;
}

void Input::SetWindow(GLFWwindow* window) {
    _window = window;
}

bool Input::GetKey(KeyCode key) {
    return glfwGetKey(_window, static_cast<int>(key)) == GLFW_PRESS;
	
}

bool Input::GetKeyDown(KeyCode key) {
	if (GetKey(key))
	{
		for (size_t i = 0; i < 2; i++)
		{
			/*if (lastPressedKeys[i].pressed == false)
			{
				lastPressedKeys[i].key = key;
				lastPressedKeys[i].pressed = true;
			}*/
		}
	}
	return false;
}

bool Input::GetKeyUp(KeyCode key) {

	return glfwGetKey(_window, static_cast<int>(key)) == GLFW_RELEASE;
}

bool Input::GetKeyRelease(KeyCode key) {
    return glfwGetKey(_window, static_cast<int>(key)) == GLFW_RELEASE;
}

bool Input::GetMouseButton(MouseButtons mb) {
    return glfwGetMouseButton(_window, static_cast<int>(mb)) == GLFW_PRESS;
}

bool Input::GetMouseButtonUp(MouseButtons mb) {
    return glfwGetMouseButton(_window, static_cast<int>(mb)) == GLFW_RELEASE;
}

glm::vec2 Input::GetMousePosition2D() {
    double xPos, yPos;
    glfwGetCursorPos(_window, &xPos, &yPos);

    mousePosition = glm::vec3(xPos, yPos, 0.0f);

    return mousePosition;
}

glm::vec3 Input::GetMousePosition3D() {
    double xPos, yPos, zPos;
    zPos = 0;
    glfwGetCursorPos(_window, &xPos, &yPos);

    mousePosition = glm::vec3(xPos, yPos, zPos);

    return mousePosition;
}

void Input::UnloadWindow() {
	if (_window) _window = NULL;
}