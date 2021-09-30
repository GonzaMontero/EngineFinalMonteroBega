#include "glew.h"
#include "Shape.h"
#include "glfw3.h"



Shape::Shape(Renderer* _renderer): Entity2D(_renderer)
{
}

void Shape::Init(Color newColor)
{
	color = newColor;
	vertexs[3] = color.R;
	vertexs[4] = color.G;
	vertexs[5] = color.B;
	vertexs[9] = color.R;
	vertexs[10] = color.G;
	vertexs[11] = color.B;
	vertexs[15] = color.R;
	vertexs[16] = color.G;
	vertexs[17] = color.B;

	renderer->initRender(vao, vbo, ibo);
}

void Shape::Draw()
{

	//llamar al draw
	renderer->DrawTriangle(indices, vertexs, model);
	//actualizar buffers
}
