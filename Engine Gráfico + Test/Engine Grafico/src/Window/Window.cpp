#include "glew.h"
#include "glfw3.h"
#include "Window.h"

Window::Window() {

}
Window::~Window() {

}

int Window::Start(int width, int height, const char* windowName)
{
	//pregunta si la library está inicializada
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


	glewExperimental = GL_TRUE;
	glewInit();   /// Crea el punto de entrada para las extenciones de glew (necesita un contexto previo)

	std::cout << glGetString(GL_VERSION) << std::endl; // nos dice la version de gl


}

void Window::ClearBackground()
{
	glClearColor(1.0f, 1.0f, 1.0f, 1.0f); // especifica los valores RGBA con los que se va a limpiar los buffers  
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);  // limpia los buffers con los valores que seleccionamos en el glClearColor en la funcion de arriba
}

bool Window::WindowShouldClose()
{
	// devuelve true si la ventan no tiene que cerrarse
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
	// cierra la ventana
	glfwTerminate();
}
