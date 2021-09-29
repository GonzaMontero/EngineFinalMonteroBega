#include "glew.h"
#include "Shape.h"
#include "glfw3.h"


float vertexs[18] = {
	//X     Y     Z     R      G    B
   -0.5f, -0.5f, 0.0f, 0.0f, 0.0f, 1.0f,
	0.5f, -0.5f, 0.0f, 0.0f, 0.0f, 1.0f,
	0.0f,  0.5f, 0.0f, 0.0f, 0.0f, 1.0f
};

unsigned int indices[3] = {
	0,1,2
};

Shape::Shape(Renderer* _renderer): Entity2D(_renderer)
{
}

void Shape::Init()
{
	glGenVertexArrays(1, &vao);
	glBindVertexArray(vao);

	glGenBuffers(1, &vbo);
	glBindBuffer(GL_ARRAY_BUFFER, vbo);
	//GL_ARRAY_BUFFER// ES PARA los vertices

	glGenBuffers(1, &ibo); //Genera X (en este caso 1) cantidad de buffers Buffer y le da un ID (en este caso el id buffer)
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, ibo); // selecciona el buffer, el primer parametro dice que tipo de info va a haber en el buffer y el segundo es el ID
	//GL_ELEMENT_ARRAY_BUFFER es para los indices

	unsigned int verAttribute = glGetAttribLocation(renderer->shaderId, "position");
	unsigned int colorAt = glGetAttribLocation(renderer->shaderId, "inColor");

	cout << "Vertex atr " << verAttribute << endl;
	cout << "Color atr " << colorAt << endl;

	// el glVertexAttribPointer es muy importante ya que espeficia como leer el buffer, como interpretar la data que ponemos adentro del mismo
	glVertexAttribPointer(verAttribute, 3, GL_FLOAT, GL_FALSE, sizeof(float) * 6, (void*)(0 * sizeof(float))); //index, tamaño del VERTEX , tipo de dato, si queremos que se normalice, stride (cuanto tiene que recorrer hasta el siguiente VERTEX, no al siguiente Attribute), stride al siguiente atributo
	glVertexAttribPointer(colorAt, 3, GL_FLOAT, GL_FALSE, sizeof(float) * 6, (void*)(3 * sizeof(float)));

	glEnableVertexAttribArray(verAttribute);  //Habilita y deshabilita los attributos del array vertex
	glEnableVertexAttribArray(colorAt);  //Habilita y deshabilita los attributos del array vertex

	renderer->BindBuffers(vao, vbo, ibo);
}

void Shape::Draw()
{
	//llamar al draw
	renderer->DrawTriangle(indices, vertexs);
	//actualizar buffers
}
