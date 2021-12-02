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


bool Input::GetKeyDown(KeyCode key) {
	if (glfwGetKey(_window, static_cast<int>(key)) == GLFW_PRESS)
	{
		lastPressedKeys[key] = actualPressedKeys[key];
		actualPressedKeys[key] = true;
		
		if (actualPressedKeys[key] != lastPressedKeys[key])
		{
			return true;
		}
		else
			return false;		
	}
	else return false;
}

bool Input::GetKeyUp(KeyCode key) {
	if (glfwGetKey(_window, static_cast<int>(key)) == GLFW_RELEASE) 
	{
		lastPressedKeys[key] = actualPressedKeys[key];
		actualPressedKeys[key] = false;

		if (actualPressedKeys[key] != lastPressedKeys[key])
		{
			return true;
		}
		else
			return false;
	}
	else return false;
}


void Input::InitKeys()
{
	actualPressedKeys[KeyCode::SPACE] = false;
	actualPressedKeys[KeyCode::A] = false;
	actualPressedKeys[KeyCode::B] = false;
	actualPressedKeys[KeyCode::C] = false;
	actualPressedKeys[KeyCode::D] = false;
	actualPressedKeys[KeyCode::E] = false;
	actualPressedKeys[KeyCode::F] = false;
	actualPressedKeys[KeyCode::G] = false;
	actualPressedKeys[KeyCode::H] = false;
	actualPressedKeys[KeyCode::I] = false;
	actualPressedKeys[KeyCode::J] = false;
	actualPressedKeys[KeyCode::K] = false;
	actualPressedKeys[KeyCode::L] = false;
	actualPressedKeys[KeyCode::M] = false;
	actualPressedKeys[KeyCode::N] = false;
	actualPressedKeys[KeyCode::O] = false;
	actualPressedKeys[KeyCode::P] = false;
	actualPressedKeys[KeyCode::Q] = false;
	actualPressedKeys[KeyCode::R] = false;
	actualPressedKeys[KeyCode::S] = false;
	actualPressedKeys[KeyCode::T] = false;
	actualPressedKeys[KeyCode::U] = false;
	actualPressedKeys[KeyCode::V] = false;
	actualPressedKeys[KeyCode::W] = false;
	actualPressedKeys[KeyCode::X] = false;
	actualPressedKeys[KeyCode::Y] = false;
	actualPressedKeys[KeyCode::Z] = false;
	actualPressedKeys[KeyCode::ESCAPE] = false;
	actualPressedKeys[KeyCode::ENTER] = false;
	actualPressedKeys[KeyCode::TAB] = false;
	actualPressedKeys[KeyCode::RIGHT] = false;
	actualPressedKeys[KeyCode::LEFT] = false;
	actualPressedKeys[KeyCode::DOWN] = false;
	actualPressedKeys[KeyCode::UP] = false;
		
	lastPressedKeys[KeyCode::SPACE] = false;
	lastPressedKeys[KeyCode::A] = false;
	lastPressedKeys[KeyCode::B] = false;
	lastPressedKeys[KeyCode::C] = false;
	lastPressedKeys[KeyCode::D] = false;
	lastPressedKeys[KeyCode::E] = false;
	lastPressedKeys[KeyCode::F] = false;
	lastPressedKeys[KeyCode::G] = false;
	lastPressedKeys[KeyCode::H] = false;
	lastPressedKeys[KeyCode::I] = false;
	lastPressedKeys[KeyCode::J] = false;
	lastPressedKeys[KeyCode::K] = false;
	lastPressedKeys[KeyCode::L] = false;
	lastPressedKeys[KeyCode::M] = false;
	lastPressedKeys[KeyCode::N] = false;
	lastPressedKeys[KeyCode::O] = false;
	lastPressedKeys[KeyCode::P] = false;
	lastPressedKeys[KeyCode::Q] = false;
	lastPressedKeys[KeyCode::R] = false;
	lastPressedKeys[KeyCode::S] = false;
	lastPressedKeys[KeyCode::T] = false;
	lastPressedKeys[KeyCode::U] = false;
	lastPressedKeys[KeyCode::V] = false;
	lastPressedKeys[KeyCode::W] = false;
	lastPressedKeys[KeyCode::X] = false;
	lastPressedKeys[KeyCode::Y] = false;
	lastPressedKeys[KeyCode::Z] = false;
	lastPressedKeys[KeyCode::ESCAPE] = false;
	lastPressedKeys[KeyCode::ENTER] = false;
	lastPressedKeys[KeyCode::TAB] = false;
	lastPressedKeys[KeyCode::RIGHT] = false;
	lastPressedKeys[KeyCode::LEFT] = false;
	lastPressedKeys[KeyCode::DOWN] = false;
	lastPressedKeys[KeyCode::UP] = false;

}