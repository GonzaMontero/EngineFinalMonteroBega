#include "Utility.h"
#include <glew.h>
#include <glfw3.h>
#include <iostream>
float deltaTime = 0.0f;
float lastFrame = 0.0f;
void UpdateDeltaTime()
{
	float currentFrame = glfwGetTime();
	deltaTime = currentFrame - lastFrame;
	lastFrame = currentFrame;
}
float DeltaTime()
{
	return deltaTime;
}