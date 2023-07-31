#include "glew.h"
#include "glfw3.h"

#include "renderer.h"
#include "../Shader/Shader.h"

#include <iostream>

using namespace Engine;

Renderer::Renderer() {
}

Renderer::~Renderer() {
}

bool Renderer::InitializeGlew() {
	glewExperimental = GL_TRUE;
	glewInit();
	if (glewInit() != GLEW_OK) {
		std::cout << "Error in GLEW INIT" << std::endl;
		std::cout << glewGetErrorString(glewInit()) << std::endl;
		return false;
	}
	return true;
}

void Renderer::BeginFrame(float r, float g, float b) {
	glClearColor(r, g, b, 1.0f);
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
}
void Renderer::EndFrame(GLFWwindow* window) {
	glfwSwapBuffers(window);
	glfwPollEvents();
}
void Renderer::GenerateVAO(unsigned int& vao) {
	glGenVertexArrays(1, &vao); //devuelve N (en este caso 1) nombres de arrays objects, dentro del array &vao  
	glBindVertexArray(vao); //bindea el array devuelto por glGenVertexArrays a vao
}	//VAO = Vertex array object
void Renderer::BindVAO(unsigned int& vao) {
	glBindVertexArray(vao);
}	//VAO = Vertex array object
void Renderer::BindVBO(unsigned int& vbo, float* vertices, int verticesAmmount) {
	glGenBuffers(1, &vbo);
	glBindBuffer(GL_ARRAY_BUFFER, vbo);
	glBufferData(GL_ARRAY_BUFFER, sizeof(vertices) * verticesAmmount, vertices, GL_STATIC_DRAW);
}//VBO = Vertex buffer object
void Renderer::BindEBO(unsigned int& ebo, unsigned int* indices, int indicesAmmount) {
	glGenBuffers(1, &ebo);
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, ebo);
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(indices) * indicesAmmount, indices, GL_STATIC_DRAW);
}//EBO = Index buffer object
void Engine::Renderer::UpdateBuffers(unsigned int& vbo, float* vertices, int verticesAmmount)
{
	glBindBuffer(GL_ARRAY_BUFFER, vbo);
	glBufferData(GL_ARRAY_BUFFER, sizeof(vertices) * verticesAmmount, vertices, GL_STATIC_DRAW);
}
void Renderer::UnbindBuffers() {
	glBindVertexArray(0);
	glBindBuffer(GL_ARRAY_BUFFER, 0);
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);
	glUseProgram(0);
}
void Renderer::DeleteBuffers(unsigned int& vao, unsigned int& vbo, unsigned int& ebo) {
	glDeleteVertexArrays(1, &vao);
	glDeleteBuffers(1, &vbo);
	glDeleteBuffers(1, &ebo);
}

void Renderer::CreateAtribPointers(unsigned int shaderAttribIndex, int dataAmmount, int dataSize, int dataPosition) {
	glVertexAttribPointer(shaderAttribIndex, dataAmmount, GL_FLOAT, GL_FALSE, sizeof(float) * dataSize, (void*)(sizeof(float) * dataPosition));
	glEnableVertexAttribArray(shaderAttribIndex);
}//Define un array de vertex attribute data y lo habilita

void Renderer::SetTexAttribPointer(unsigned int shaderID) {
	GLuint posAttrib = glGetAttribLocation(shaderID, "aPos");
	GLuint colorAttrib = glGetAttribLocation(shaderID, "aColor"); // no daba el valor correcto porque no usaba la variable en el main
	GLuint texAttrib = glGetAttribLocation(shaderID, "aTexCoord");
	glUniform1i((glGetUniformLocation(shaderID, "mainTexture")), 0);
	CreateAtribPointers(posAttrib, 3, 8, 0);
	CreateAtribPointers(colorAttrib, 3, 8, 3);
	CreateAtribPointers(texAttrib, 2, 8, 6);
}//Setea los atributos que va a usar el shader utilizando IDs y nombres de variables que hay dentro del shader

void Renderer::Draw(Shader& shader, glm::mat4 model, unsigned int& vao, unsigned int& vbo, float* vertices, int verticesAmount, unsigned int* indices, int indicesAmmount) {
	BindVAO(vao);
	UpdateBuffers(vbo, vertices, verticesAmount);
	shader.SetVertexAttributes("position", 6); //especificamos como leer los datos del vertice y se lo pasamos al shader
	shader.SetColorAttributes("color", 6);
	shader.Use(model);
	glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, 0);
	UnbindBuffers();
} // Se actualizan los buffers, se pasa data al shader para que aplique, se llama a draw elements y se desbindea el buffer, esta funcion es para dibujar cosas sin textura, solo formas con colores
void Renderer::DrawSprite(Shader& shader, unsigned int& vao, unsigned int& vbo, float* vertices, int verticesAmount, unsigned int* indices, int indicesAmmount, glm::mat4 model) {
	BindVAO(vao);
	UpdateBuffers(vbo, vertices, verticesAmount);
	SetTexAttribPointer(shader.GetID());
	shader.Use(model);
	glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, 0);
	UnbindBuffers();
} //igual que Draw, pero al usar SetTexAttribPointer puede dibujar texturas y no solo formas geometricas con colores planos (o colores interpolados)

void Renderer::DrawCamera(Shader& shader, glm::mat4 model, glm::mat4 view) {
	shader.Use();

	unsigned int transformLoc = glGetUniformLocation(shader.GetID(), "model");
	unsigned int viewLoc = glGetUniformLocation(shader.GetID(), "view");

	glUniformMatrix4fv(transformLoc, 1, GL_FALSE, glm::value_ptr(model));
	glUniformMatrix4fv(viewLoc, 1, GL_FALSE, glm::value_ptr(view));
}