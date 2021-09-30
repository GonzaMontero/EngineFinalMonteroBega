#include "glew.h"
#include "Shape.h"
#include "glfw3.h"


float vertexs[18] = {
	//X     Y     Z     R      G    B
   -0.5f, -0.5f, 0.0f, 0.0f, 0.0f, 1.0f,
	0.5f, -0.5f, 0.0f, 0.0f, 0.0f, 1.0f,
	0.0f,  0.375f, 0.0f, 0.0f, 0.0f, 1.0f
};

unsigned int indices[3] = {
	0,1,2
};

Shape::Shape(Renderer* _renderer): Entity2D(_renderer)
{
}

void Shape::Init()
{
	glGenVertexArrays(1, &vao); // genera N arrays de vertices y guarda sus nombres en el segundo parametro
	glBindVertexArray(vao); // le dice al vertex array cual es su nombre en caso de que no haya un vertex array object con ese nombre crea el vinculo entre el array y el nombre, si ya lo hay entonces rompe el vinculo previo 

	glGenBuffers(1, &vbo); /// Genera N cantidad de buffers en el primer parametro, el segundo parametro es en donde se almacenan los nombres de dichos buffers
	glBindBuffer(GL_ARRAY_BUFFER, vbo); // especifica a que buffer está bindeando (primer parametro), segundo parametro es el nombre del buffer que estas bindeando
	//GL_ARRAY_BUFFER// ES PARA los vertices

	glGenBuffers(1, &ibo); //Genera X (en este caso 1) cantidad de buffers Buffer y le da un ID (en este caso el id buffer)
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, ibo); // selecciona el target (binding point buffer), el primer parametro dice a donde se va a conectar lo que determina que tipo de info tiene que haber en el buffer y el segundo es el ID
	//GL_ELEMENT_ARRAY_BUFFER es para los indices

	unsigned int verAttribute = glGetAttribLocation(renderer->shaderId, "position");	// devuelve la ubicacion de un atributo dentro de un programa y luego se lo asigna a una variable
	unsigned int colorAt = glGetAttribLocation(renderer->shaderId, "inColor");			//  Los parametros que se usan son el programa de donde estamos sacando el atribute, en estos casos los shaders, y el nombre del atributo

	// el glVertexAttribPointer es muy importante ya que espeficia como leer el buffer, como interpretar la data que ponemos adentro del mismo
	glVertexAttribPointer(verAttribute, 3, GL_FLOAT, GL_FALSE, sizeof(float) * 6, (void*)(0 * sizeof(float))); //index, tamaño del VERTEX , tipo de dato, si queremos que se normalice, stride (cuanto tiene que recorrer hasta el siguiente VERTEX, no al siguiente Attribute), stride al siguiente atributo
	glVertexAttribPointer(colorAt, 3, GL_FLOAT, GL_FALSE, sizeof(float) * 6, (void*)(3 * sizeof(float))); /// lee igual que el otro, pero arranca desde la pos 3 en lugar de la 0, ya que ahí empiezan los valores de RGB

	glEnableVertexAttribArray(verAttribute);  //Habilita y deshabilita los attributos del array vertex
	glEnableVertexAttribArray(colorAt);  //Habilita y deshabilita los attributos del array vertex

	renderer->BindBuffers(vao, vbo, ibo); /// preguntar porque los vuelve a bindear porque no entiendo
}

void Shape::Draw()
{
	//llamar al draw
	renderer->DrawTriangle(indices, vertexs, model);
	//actualizar buffers
}
