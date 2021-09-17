#ifndef WINDOW_H
#define WINDOW_H

#include "export.h"

#include <stdlib.h>
#include <string>
#include <iostream>

class GLFWwindow;

class ENGINE_API Window {
public:
	Window();
	~Window();
	GLFWwindow* window;
	int Start(int width, int height, const char* windowName);
	static void ClearBackground();
	int WindowShouldClose();
	void FinishWindowCycle();
	void CloseWindow();

};
#endif // !WINDOW_H
