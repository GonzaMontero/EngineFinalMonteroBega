#ifndef WINDOW_H
#define WINDOW_H

#include "../Utils/Export.h"

class GLFWwindow;

namespace Engine {
	class ENGINE_API Window {
	public:
		//Creator and Destructor for Window, using requested height, width and name
		Window();
		Window(int width, int height, std::string name);
		~Window();

		//Functions to not only initialize the window, but to also get window in itself + the data
		void InitWindow();
		GLFWwindow* GetWindow();
		int GetWidth();
		int GetHeight();

	private:
		GLFWwindow* _window;
		int _width;
		int _height;
	};
}

#endif // !WINDOW_H
