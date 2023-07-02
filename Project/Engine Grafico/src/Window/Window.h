#ifndef WINDOW_H
#define WINDOW_H

#include "../Utils/Export.h"


class GLFWwindow;

namespace Engine {
	class ENGINE_API Window {
	private:
		GLFWwindow* _window;
		int _width;
		int _height;
	public:
		Window();
		Window(int width, int height);
		~Window();
		int CreateWindow(const char* name);
		GLFWwindow* GetWindow();
		void SetWidth(int width);
		int GetWidth();
		void SetHeight(int height);
		int GetHeight();
	};
}

#endif // !WINDOW_H
