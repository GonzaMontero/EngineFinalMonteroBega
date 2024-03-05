#include "Input.h"
#include <glfw3.h>
Input::Input()
{
}

Input::~Input()
{
}

bool Input::GetKey(int keycode, GLFWwindow* window)
{
	int state = glfwGetKey(window, keycode);
	if (state == GLFW_PRESS)
	{
		return true;
	}
	return false;
}
