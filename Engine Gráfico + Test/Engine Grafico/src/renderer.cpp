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

void Renderer::DrawTriangle(unsigned int *indices, float *vertices) 
{	
	glUseProgram(shaderId);
	glBufferData(GL_ARRAY_BUFFER, sizeof(vertices) * 18, vertices, GL_STATIC_DRAW);
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(indices) * 3, indices, GL_STATIC_DRAW); // le dice al buffer, donde guardar, que tanto espacio tiene disponible, que tiene que guardar y para que se va a usar 
	glDrawElements(GL_TRIANGLES, 3, GL_UNSIGNED_INT, 0); //se usa si no tenes un index buffer, Dibuja segun un buffer, los parametros son que tipo de primitiva queres dibujar, desde donde queres empezar a leer la data y cantidad de indices qeu se van a renderizar
}

void Renderer::BindBuffers(unsigned int &vao, unsigned int &vbo, unsigned int &ibo)
{
	glBindVertexArray(vao);
	glBindBuffer(GL_ARRAY_BUFFER, vbo);
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, ibo);
}

void Renderer::initRender()
{
	shaderId = CreateShader("../res/shader/Vertex.shader", "../res/shader/Fragment.shader");

	cout << shaderId;
}
