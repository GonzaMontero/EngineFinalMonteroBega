#include "glew.h"
#include "glfw3.h"
#include "renderer.h"

struct ShaderProgramSource
{
	string VertexSource;
	string FragmentSource;
};

unsigned int CompileShader(unsigned int type, const char* source)
{
	unsigned int id = glCreateShader(type);

	
	string sourceShaderCode;
	ifstream sourceShaderFile;
	sourceShaderFile.exceptions(ifstream::failbit | ifstream::badbit);
	try
	{
		sourceShaderFile.open(source);
		stringstream sourceShaderStream;

		sourceShaderStream << sourceShaderFile.rdbuf();
		sourceShaderFile.close();

		sourceShaderCode = sourceShaderStream.str();
	}
	catch (ifstream::failure & e)
	{
		cout << "Error de lectura del shader" << endl;
	}

	const char* src = sourceShaderCode.c_str();

	glShaderSource(id, 1, &src, nullptr);
	glCompileShader(id);

	return (id);

	//leer las funciones que empiezan con gl y hacer comentario de que hacen para tener a mano
}

unsigned int  Renderer::CreateShader(const char* vertexShader, const char* fragmentShader)
{
	unsigned int program = glCreateProgram();
	unsigned int vs = CompileShader(GL_VERTEX_SHADER, vertexShader);
	unsigned int fs = CompileShader(GL_FRAGMENT_SHADER, fragmentShader);

	glAttachShader(program, vs);
	glAttachShader(program, fs);
	glLinkProgram(program);
	glValidateProgram(program);
	

	glDeleteShader(vs);  // borra el shader para que no se haga un obj
	glDeleteShader(fs);	 // borra el shader para que no se haga un obj

	return program;
	//leer las funciones que empiezan con gl y hacer comentario de que hacen para tener a mano
}

Renderer::Renderer() {

}

Renderer::~Renderer() {
	//glDeleteProgram(shader);
}

void Renderer::DrawTriangle(unsigned int *indices, float *vertices, glm::mat4 _trsmatrix)
{	
/*	unsigned int verAttribute = glGetAttribLocation(shaderId, "position"); // devuelve la ubicacion de un atributo dentro de un programa y luego se lo asigna a una variable
	unsigned int colorAt = glGetAttribLocation(shaderId, "inColor");	   //  Los parametros que se usan son el programa de donde estamos sacando el atribute, en estos casos los shaders, y el nombre del atributo

	// el glVertexAttribPointer es muy importante ya que espeficia como leer el buffer, como interpretar la data que ponemos adentro del mismo
	glVertexAttribPointer(verAttribute, 3, GL_FLOAT, GL_FALSE, sizeof(float) * 6, (void*)(0 * sizeof(float))); //index, tamaño del VERTEX , tipo de dato, si queremos que se normalice, stride (cuanto tiene que recorrer hasta el siguiente VERTEX, no al siguiente Attribute), stride al siguiente atributo
	glVertexAttribPointer(colorAt, 3, GL_FLOAT, GL_FALSE, sizeof(float) * 6, (void*)(3 * sizeof(float))); /// lee igual que el otro, pero arranca desde la pos 3 en lugar de la 0, ya que ahí empiezan los valores de RGB

	glEnableVertexAttribArray(verAttribute);  //Habilita y deshabilita los attributos del array vertex
	glEnableVertexAttribArray(colorAt);  //Habilita y deshabilita los attributos del array vertex*/

	unsigned int model = glGetUniformLocation(shaderId,"trsmatrix");
	glUseProgram(shaderId);
	glUniformMatrix4fv(model, 1, GL_FALSE, glm::value_ptr(_trsmatrix));

	glBufferData(GL_ARRAY_BUFFER, sizeof(vertices) * 18, vertices, GL_STATIC_DRAW);
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(indices) * 3, indices, GL_STATIC_DRAW); // le dice al buffer, donde guardar, que tanto espacio tiene disponible, que tiene que guardar y para que se va a usar 
	
	glDrawElements(GL_TRIANGLES, 3, GL_UNSIGNED_INT, 0); //se usa si no tenes un index buffer, Dibuja segun un buffer, los parametros son que tipo de primitiva queres dibujar, desde donde queres empezar a leer la data y cantidad de indices qeu se van a renderizar
}

void Renderer::DrawSquare(unsigned int* indices, float* vertices, glm::mat4 _trsmatrix)
{
	/*	unsigned int verAttribute = glGetAttribLocation(shaderId, "position"); // devuelve la ubicacion de un atributo dentro de un programa y luego se lo asigna a una variable
		unsigned int colorAt = glGetAttribLocation(shaderId, "inColor");	   //  Los parametros que se usan son el programa de donde estamos sacando el atribute, en estos casos los shaders, y el nombre del atributo

		// el glVertexAttribPointer es muy importante ya que espeficia como leer el buffer, como interpretar la data que ponemos adentro del mismo
		glVertexAttribPointer(verAttribute, 3, GL_FLOAT, GL_FALSE, sizeof(float) * 6, (void*)(0 * sizeof(float))); //index, tamaño del VERTEX , tipo de dato, si queremos que se normalice, stride (cuanto tiene que recorrer hasta el siguiente VERTEX, no al siguiente Attribute), stride al siguiente atributo
		glVertexAttribPointer(colorAt, 3, GL_FLOAT, GL_FALSE, sizeof(float) * 6, (void*)(3 * sizeof(float))); /// lee igual que el otro, pero arranca desde la pos 3 en lugar de la 0, ya que ahí empiezan los valores de RGB

		glEnableVertexAttribArray(verAttribute);  //Habilita y deshabilita los attributos del array vertex
		glEnableVertexAttribArray(colorAt);  //Habilita y deshabilita los attributos del array vertex*/

	unsigned int model = glGetUniformLocation(shaderId, "trsmatrix");
	glUseProgram(shaderId);
	glUniformMatrix4fv(model, 1, GL_FALSE, glm::value_ptr(_trsmatrix));

	glBufferData(GL_ARRAY_BUFFER, sizeof(vertices) * 18, vertices, GL_STATIC_DRAW);
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(indices) * 3, indices, GL_STATIC_DRAW); // le dice al buffer, donde guardar, que tanto espacio tiene disponible, que tiene que guardar y para que se va a usar 

	glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, 0); //se usa si no tenes un index buffer, Dibuja segun un buffer, los parametros son que tipo de primitiva queres dibujar, desde donde queres empezar a leer la data y cantidad de indices qeu se van a renderizar
}


void Renderer::CreateShader()
{
	shaderId = CreateShader("../res/shader/Vertex.shader", "../res/shader/Fragment.shader");

}

void Renderer::initRender(unsigned int vao, unsigned int vbo, unsigned int ibo)
{
	glGenVertexArrays(1, &vao); // genera N arrays de vertices y guarda sus nombres en el segundo parametro
	glBindVertexArray(vao); // le dice al vertex array cual es su nombre en caso de que no haya un vertex array object con ese nombre crea el vinculo entre el array y el nombre, si ya lo hay entonces rompe el vinculo previo 

	glGenBuffers(1, &vbo); /// Genera N cantidad de buffers en el primer parametro, el segundo parametro es en donde se almacenan los nombres de dichos buffers
	glBindBuffer(GL_ARRAY_BUFFER, vbo); // especifica a que buffer está bindeando (primer parametro), segundo parametro es el nombre del buffer que estas bindeando
	//GL_ARRAY_BUFFER// ES PARA los vertices

	glGenBuffers(1, &ibo); //Genera X (en este caso 1) cantidad de buffers Buffer y le da un ID (en este caso el id buffer)
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, ibo); // selecciona el target (binding point buffer), el primer parametro dice a donde se va a conectar lo que determina que tipo de info tiene que haber en el buffer y el segundo es el ID
	//GL_ELEMENT_ARRAY_BUFFER es para los indices

	unsigned int verAttribute = glGetAttribLocation(shaderId, "position");	// devuelve la ubicacion de un atributo dentro de un programa y luego se lo asigna a una variable
	unsigned int colorAt = glGetAttribLocation(shaderId, "inColor");			//  Los parametros que se usan son el programa de donde estamos sacando el atribute, en estos casos los shaders, y el nombre del atributo

	// el glVertexAttribPointer es muy importante ya que espeficia como leer el buffer, como interpretar la data que ponemos adentro del mismo
	glVertexAttribPointer(verAttribute, 3, GL_FLOAT, GL_FALSE, sizeof(float) * 6, (void*)(0 * sizeof(float))); //index, tamaño del VERTEX , tipo de dato, si queremos que se normalice, stride (cuanto tiene que recorrer hasta el siguiente VERTEX, no al siguiente Attribute), stride al siguiente atributo
	glVertexAttribPointer(colorAt, 3, GL_FLOAT, GL_FALSE, sizeof(float) * 6, (void*)(3 * sizeof(float))); /// lee igual que el otro, pero arranca desde la pos 3 en lugar de la 0, ya que ahí empiezan los valores de RGB

	glEnableVertexAttribArray(verAttribute);  //Habilita y deshabilita los attributos del array vertex
	glEnableVertexAttribArray(colorAt);  //Habilita y deshabilita los attributos del array vertex


}
