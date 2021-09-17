#include "glew.h"
#include "glfw3.h"
#include "Window.h"

Window::Window() {

}
Window::~Window() {

}

int Window::Start(int width, int height, const char* windowName)
{
	//pregunta si la library est� inicializada
	if (!glfwInit())
		return -1;

	// Create a windowed mode window and its OpenGL context / con los parametros que pedimos
	window = glfwCreateWindow(width, height, windowName, NULL, NULL);
	if (!window) // si no hay ventana por la razon que sea, cierra el ciclo de glfw y hay que volver a llamar a glfwInit
	{
		glfwTerminate();
		return -1;
	}

	// Hace que el context en el que hagamos las cosas ahora sea la ventana que acabamos de crear (podemos tener varias ventanas en simultaneo)/
	glfwMakeContextCurrent(window);

	glewInit();   /// Crea el punto de entrada para las extenciones de glew (necesita un contexto precvio)

	std::cout << glGetString(GL_VERSION) << std::endl; // nos dice la version de gl
}

void Window::ClearBackground()
{
	// Swap front and back buffers 
	glClear(GL_COLOR_BUFFER_BIT);
}

int Window::WindowShouldClose()
{
	return glfwWindowShouldClose(window);
}

void Window::FinishWindowCycle()
{
	// Swap front and back buffers
	glfwSwapBuffers(window);

	// Poll for and process events 
	glfwPollEvents();
}

void Window::CloseWindow()
{
	glfwTerminate();
}
