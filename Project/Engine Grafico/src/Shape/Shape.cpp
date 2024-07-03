#include "Shape.h"
#include "../Renderer/renderer.h"
#include "glew.h"
#include "glfw3.h"

using namespace Engine;

Engine::Shape::Shape(Renderer* renderer, unsigned int vertices)
{
	VAO = 0;
	VBO = 0;
	EBO = 0;

	_vertices = 0;
	_renderer = renderer;

	float* vertex;
	unsigned int* indices;

	if (vertices == 3)
	{
		vertex = new float[18]
		{
			-0.5f, -0.5f, 0.0f, 1.0f, 1.0f, 1.0f,
			0.5f, -0.5f, 0.0f, 1.0f, 1.0f, 1.0f,
			0.0f,  0.5f, 0.0f, 1.0f, 1.0f, 1.0f
		};

		indices = new unsigned int[3]
		{
			0,1,2
		};

		_renderer->CreateBufferInitial(VAO, VBO, EBO);
		_renderer->BindBufferInitial(VAO, VBO, EBO, vertex, sizeof(vertex) * 18, indices, sizeof(indices) * 3);
		_vertices = 3;

		delete[] vertex;
		delete[] indices;
	}
	else if (vertices == 4)
	{
		vertex = new float[24]
		{
			 0.5f,  0.5f, 0.0f, 1.0f, 1.0f, 1.0f,
			 0.5f, -0.5f, 0.0f, 1.0f, 1.0f, 1.0f,
			-0.5f, -0.5f, 0.0f, 1.0f, 1.0f, 1.0f,
			-0.5f,  0.5f, 0.0f, 1.0f, 1.0f, 1.0f
		};
		indices = new unsigned int[6]
		{
			0, 1, 3,
			1, 2, 3
		};
		_renderer->CreateBufferInitial(VAO, VBO, EBO);
		_renderer->BindBufferInitial(VAO, VBO, EBO, vertex, sizeof(vertex) * 24, indices, sizeof(indices) * 6);
		_vertices = 6;

		delete[] vertex;
		delete[] indices;
	}
	else
	{
		std::cout << vertices << " Vertices amount not implemented." << std::endl;
		return;
	}

	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 6 * sizeof(float), (void*)0);
	glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 6 * sizeof(float), (void*)(3 * sizeof(float)));

	glEnableVertexAttribArray(0);
	glEnableVertexAttribArray(1);
}

Engine::Shape::~Shape()
{
	_renderer->DeleteBufferInitial(VAO, VBO, EBO);
}

void Engine::Shape::Draw()
{
	_renderer->solidShader.Use();
	SetShader();
	_renderer->Draw(_model.trs, VAO, _vertices, _renderer->solidShader.GetID());
}

void Engine::Shape::SetShader()
{
	glm::vec3 newColor = glm::vec3(_color.r, _color.g, _color.b);
	unsigned int colorLoc = glGetUniformLocation(_renderer->solidShader.GetID(), "color");
	glUniform3fv(colorLoc, 1, glm::value_ptr(newColor));

	unsigned int alphaLoc = glGetUniformLocation(_renderer->solidShader.GetID(), "a");
	glUniform1fv(alphaLoc, 1, &(_color.a));
}
