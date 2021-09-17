#include "glew.h"
#include "glfw3.h"
#include "renderer.h"

static unsigned int CompileShader(unsigned int type, const string& source)
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

static unsigned int CreateShader(const string& vertexShader, const string& fragmentShader)
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
	i = 0;
}
Renderer::~Renderer() {

}

void Renderer::DrawTriangle(CVec4 pos1, CVec4 pos2, CVec4 pos3) {

	float vertexs[24] = {
		pos1.x, pos1.y, pos1.z, pos1.w, pos1.color.R, pos1.color.G , pos1.color.B , pos1.color.A,
		pos2.x, pos2.y, pos2.z, pos2.w, pos2.color.R, pos2.color.G , pos2.color.B , pos2.color.A,
		pos3.x, pos3.y, pos3.z, pos3.w, pos3.color.R, pos3.color.G , pos3.color.B , pos3.color.A
	};

	glGenBuffers(1, &buffer); //Genera X (en este caso 1) cantidad de buffers Buffer y le da un ID (en este caso el id buffer)
	glBindBuffer(GL_ARRAY_BUFFER, buffer); // selecciona el buffer, el primer parametro dice que tipo de info va a haber en el buffer y el segundo es el ID
	glBufferData(GL_ARRAY_BUFFER, 24 * sizeof(float), vertexs, GL_STATIC_DRAW); // le dice al buffer, donde guardar, que tanto espacio tiene disponible, que tiene que guardar y para que se va a usar 

	glEnableVertexAttribArray(0);  //Habilita y deshabilita los attributos del array vertex
	// el glVertexAttribPointer es muy importante ya que espeficia como leer el buffer, como interpretar la data que ponemos adentro del mismo
	glVertexAttribPointer(0, 8, GL_FLOAT, GL_FALSE, sizeof(float) * 8, (void*)(4 * sizeof(float))); //index, tamaño del VERTEX , tipo de dato, si queremos que se normalice, stride (cuanto tiene que recorrer hasta el siguiente VERTEX, no al siguiente Attribute), stride al siguiente atributo

	unsigned int shader = CreateShader("res/shader/vertex.shader", "res/shader/fragment.shader");

	glUseProgram(shader);

	glDrawArrays(GL_TRIANGLES, 0, 3); //se usa si no tenes un index buffer, Dibuja segun un buffer, los parametros son que tipo de primitiva queres dibujar, desde donde queres empezar a leer la data y cantidad de indices qeu se van a renderizar

	buffer = NULL;
}