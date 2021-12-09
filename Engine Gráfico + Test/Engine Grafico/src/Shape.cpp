#include "glew.h"
#include "Shape.h"
#include "glfw3.h"
#include <stdlib.h>

Shape::Shape(Renderer* _renderer): Entity2D(_renderer)
{
}

void Shape::Init(Color newColor, ShapeType shape)
{
	color = newColor;
	switch (shape)
	{
	case TRI:
		vertexs[3] = color.R;
		vertexs[4] = color.G;
		vertexs[5] = color.B;
		vertexs[9] = color.R;
		vertexs[10] = color.G;
		vertexs[11] = color.B;
		vertexs[15] = color.R;
		vertexs[16] = color.G;
		vertexs[17] = color.B;
		break;
	case QUAD:
		vertexsQuad[3] = color.R;
		vertexsQuad[4] = color.G;
		vertexsQuad[5] = color.B;
		vertexsQuad[9] = color.R;
		vertexsQuad[10] = color.G;
		vertexsQuad[11] = color.B;
		vertexsQuad[15] = color.R;
		vertexsQuad[16] = color.G;
		vertexsQuad[17] = color.B;
		vertexsQuad[21] = color.R;
		vertexsQuad[22] = color.G;
		vertexsQuad[23] = color.B;
		break;
	default:
		break;
	}

	renderer->initRender(vao, vbo, ebo);
}

void Shape::UpdateColor(Color newColor)
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

	renderer->initRender(vao, vbo, ebo);
}

void Shape::EpilepsyMode()
{
	int number = rand() % 3;
	switch (number) {
	case 0:
		UpdateColor(BLUE);
		break;
	case 1:
		UpdateColor(RED);
		break;
	case 2:
		UpdateColor(GREEN);
		break;
	}
}

void Shape::Draw(ShapeType shape)
{
	//llamar al draw
	switch (shape)
	{
	case NONE:
		break;
	case TRI:
		renderer->Draw(indices, vertexs, model,0);
		break;
	case QUAD:
		renderer->Draw(indicesQuad, vertexsQuad, model,1);
		break;
	default:
		break;
	}
	//actualizar buffers
}
