#include "glew.h"
#include "glfw3.h"

#include "renderer.h"
#include "../Shader/Shader.h"

#include <iostream>

using namespace Engine;

Renderer::Renderer() 
{
	currentWindow = NULL;
	viewMatrix = glm::mat4();
	projectionMatrix = glm::mat4();
	currentColor = glm::vec4(0, 0, 0, 1);
}

Engine::Renderer::Renderer(Window* window)
{
	currentColor = glm::vec4(0, 0, 0, 1);

	currentWindow = window;

	viewMatrix = glm::mat4(1.0f);
	projectionMatrix = glm::mat4(1.0f);

	glEnable(GL_BLEND);
	glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
}

Renderer::~Renderer() 
{

}

void Engine::Renderer::SetWindow(Window* window)
{
	currentWindow = window;
}

Window* Engine::Renderer::GetWindow()
{
	return currentWindow;
}

void Engine::Renderer::CreateBufferInitial(unsigned int& VAO, unsigned int& VBO, unsigned int& EBO)
{
	glGenVertexArrays(1, &VAO);
	glGenBuffers(1, &VBO);
	glGenBuffers(1, &EBO);
}

void Engine::Renderer::CreateBufferAdditional(unsigned int& buffer, int size)
{
	glGenBuffers(size, &buffer);
}

void Engine::Renderer::BindBufferInitial(unsigned int VAO, unsigned int VBO, unsigned int EBO, float* vertices, unsigned int sizeOfVertices, unsigned int* indices, unsigned int sizeOfIndices)
{
	glBindVertexArray(VAO);

	glBindBuffer(GL_ARRAY_BUFFER, VBO);
	glBufferData(GL_ARRAY_BUFFER, sizeOfVertices, vertices, GL_STATIC_DRAW);

	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBO);
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeOfIndices, indices, GL_STATIC_DRAW);
}

void Engine::Renderer::BindBufferAdditional(unsigned int buffer, float* data, unsigned int sizeOfData, unsigned int bufferType)
{
	glBindBuffer(GL_ARRAY_BUFFER, buffer);
	glBufferData(GL_ARRAY_BUFFER, sizeOfData, data, bufferType);
}

void Engine::Renderer::DeleteBufferInitial(unsigned int& VAO, unsigned int& VBO, unsigned int& EBO)
{
	glDeleteVertexArrays(1, &VAO);
	glDeleteBuffers(1, &VBO);
	glDeleteBuffers(1, &EBO);
}

void Engine::Renderer::DeleteBufferAdditional(unsigned int& buffer, int size)
{
	glDeleteBuffers(size, &buffer);
}

void Engine::Renderer::Draw(glm::mat4 modelMatrix, unsigned int VAO, unsigned int vertices, unsigned int shaderID)
{
	unsigned int modelLoc = glGetUniformLocation(shaderID, "model");
	glUniformMatrix4fv(modelLoc, 1, GL_FALSE, glm::value_ptr(modelMatrix));

	unsigned int viewLoc = glGetUniformLocation(shaderID, "view");
	glUniformMatrix4fv(viewLoc, 1, GL_FALSE, glm::value_ptr(viewMatrix));

	unsigned int projectionLoc = glGetUniformLocation(shaderID, "projection");
	glUniformMatrix4fv(projectionLoc, 1, GL_FALSE, glm::value_ptr(projectionMatrix));

	glBindVertexArray(VAO);
	glDrawElements(GL_TRIANGLES, vertices, GL_UNSIGNED_INT, 0);
}

void Engine::Renderer::StartDraw()
{
	glClearColor(currentColor.r, currentColor.g, currentColor.b, currentColor.a);
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
}

void Engine::Renderer::EndDraw()
{
	glfwSwapBuffers(currentWindow->GetGLFWindow());
}

void Engine::Renderer::SetColor(glm::vec4 color)
{
	currentColor = color;
}

void Engine::Renderer::SetViewMatrix(glm::mat4 viewMatrix)
{
	this->viewMatrix = viewMatrix;
}

void Engine::Renderer::SetProjectionMatrix(glm::mat4 projectionMatrix)
{
	this->projectionMatrix = projectionMatrix;
}