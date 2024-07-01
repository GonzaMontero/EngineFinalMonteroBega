#ifndef RENDERER_H
#define RENDERER_H

#include "../Utils/Export.h"
#include "../Shader/Shader.h"
#include "../Window/Window.h"
#include <mat4x4.hpp>

struct GLFWwindow;

namespace Engine {
	class ENGINE_API Renderer {
	public:
		//Constructor and Destructor
		Renderer();
		Renderer(Window* window);
		~Renderer();

		void SetWindow(Window* window);
		Window* GetWindow();

		//These functions allow us to create the first and additional buffers, while also binding them and deleting them
		//A buffer in OpenGL is, at its core, an object that manages a certain piece of GPU memory and nothing more
		void CreateBufferInitial(unsigned int& VAO, unsigned int& VBO, unsigned int& EBO);
		void CreateBufferAdditional(unsigned int& buffer, int size);
		void BindBufferInitial(unsigned int VAO, unsigned int VBO, unsigned int EBO, float* vertices, unsigned int sizeOfVertices,
			unsigned int* indices, unsigned int sizeOfIndices);
		void BindBufferAdditional(unsigned int buffer, float* data, unsigned int sizeOfData, unsigned int bufferType);
		void DeleteBufferInitial(unsigned int& VAO, unsigned int& VBO, unsigned int& EBO);
		void DeleteBufferAdditional(unsigned int& buffer, int size);

		//Draw Functions which will allow us to draw specific objects and bunch the draw calls in an "event"
		void Draw(glm::mat4 modelMatrix, unsigned int VAO, unsigned int vertices, unsigned int shaderID);
		void StartDraw();
		void EndDraw();

		//Base Setters for the Engine, with color for the window, and view/projection matrixes
		void SetColor(glm::vec4 color);
		void SetViewMatrix(glm::mat4 viewMatrix);
		void SetProjectionMatrix(glm::mat4 projectionMatrix);
	private:
		float lastTime = 0;
		Window* currentWindow;
		glm::vec4 currentColor;
		glm::mat4 viewMatrix;
		glm::mat4 projectionMatrix;
	};
}
#endif // !RENDERER_H