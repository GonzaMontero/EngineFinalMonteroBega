#include "Shape.h"

Shape::Shape() : Entity2D()
{
	myType = ShapeType::Triangle;
}
Shape::Shape(ShapeType type) : Entity2D()
{
	myType = type;
}
void Shape::SetColor(float R,float G, float B)
{
	switch (myType)
	{
	case ShapeType::Triangle:
	default:

		VertexTriangle[3] = R;
		VertexTriangle[4] = G;
		VertexTriangle[5] = B;

		VertexTriangle[9] = R;
		VertexTriangle[10] = G;
		VertexTriangle[11] = B;

		VertexTriangle[15] = R;
		VertexTriangle[16] = G;
		VertexTriangle[17] = B;
		break;
	case ShapeType::Square:
		VertexSquare[3] = R;
		VertexSquare[4] = G;
		VertexSquare[5] = B;

		VertexSquare[9] = R;
		VertexSquare[10] = G;
		VertexSquare[11] = B;

		VertexSquare[15] = R;
		VertexSquare[16] = G;
		VertexSquare[17] = B;

		VertexSquare[21] = R;
		VertexSquare[22] = G;
		VertexSquare[23] = B;
		break;
	}
}
void Shape::Draw()
{
	switch (myType)
	{
	case ShapeType::Triangle:
		renderer->Draw(VertexTriangle,vertexTriangleLength, IndexTriangle,indexTriangleLength, model);
		break;
	case ShapeType::Square:
		renderer->Draw(VertexSquare,vertexSquareLength, IndexSquare,indexSquareLength, model);
		break;
	}
}

