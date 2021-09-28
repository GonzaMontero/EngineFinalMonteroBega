#include "glew.h"
#include "glfw3.h"
#include "renderer.h"
#pragma region shaders like cherno

/*
static unsigned int CompileShader(unsigned int type, const std::string& source)
{
	unsigned int id = glCreateShader(type);
	const char* src = source.c_str();
	glShaderSource(id, 1, &src, nullptr);
	glCompileShader(id);
	int result;
	glGetShaderiv(id, GL_COMPILE_STATUS, &result);
	if (!result)
	{
		int length;
		glGetShaderiv(id, GL_INFO_LOG_LENGTH, &length);
		char* message = (char*)alloca(length * sizeof(char));
		glGetShaderInfoLog(id, length, &length, message);
		std::cout << "failed to compile " << (type == GL_VERTEX_SHADER ? "vertex" : "fragment") << " shader" << std::endl;
		glDeleteShader(id);
		return 0;
	}

	return id;
}
static unsigned int CreateShader(const std::string& vertexShader, const std::string& fragmentSader)
{
	unsigned int program = glCreateProgram();
	unsigned int vs = CompileShader(GL_VERTEX_SHADER, vertexShader );
	unsigned int fs = CompileShader(GL_FRAGMENT_SHADER, vertexShader);

	glAttachShader(program, vs);
	glAttachShader(program, fs);
	glLinkProgram(program);
	glValidateProgram(program);

	glDeleteShader(vs);
	glDeleteShader(fs);

	return program;
}
*/

#pragma endregion

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

void Renderer::DrawTriangle(CVec3 pos1, CVec3 pos2, CVec3 pos3) 
{	
	glUseProgram(shaderId);
	glBufferData(GL_ARRAY_BUFFER, sizeof(vertexs), vertexs, GL_STATIC_DRAW);
	glDrawElements(GL_TRIANGLES, 3, GL_UNSIGNED_INT, 0); //se usa si no tenes un index buffer, Dibuja segun un buffer, los parametros son que tipo de primitiva queres dibujar, desde donde queres empezar a leer la data y cantidad de indices qeu se van a renderizar
}

void Renderer::BindBuffers()
{
	glBindVertexArray(vao);
	glBindBuffer(GL_ARRAY_BUFFER, vbo);
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, ibo);
}

void Renderer::initRender()
{
	shaderId = CreateShader("../res/shader/Vertex.shader", "../res/shader/Fragment.shader");

	glGenVertexArrays(1, &vao);
	glBindVertexArray(vao);

	glGenBuffers(1, &vbo);
	glBindBuffer(GL_ARRAY_BUFFER, vbo);	
	//GL_ARRAY_BUFFER// ES PARA los vertices

	glGenBuffers(1, &ibo); //Genera X (en este caso 1) cantidad de buffers Buffer y le da un ID (en este caso el id buffer)
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, ibo); // selecciona el buffer, el primer parametro dice que tipo de info va a haber en el buffer y el segundo es el ID
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(indices), indices, GL_STATIC_DRAW); // le dice al buffer, donde guardar, que tanto espacio tiene disponible, que tiene que guardar y para que se va a usar 
	//GL_ELEMENT_ARRAY_BUFFER es para los indices

	unsigned int verAttribute = glGetAttribLocation(shaderId, "position");
	unsigned int colorAt = glGetAttribLocation(shaderId, "inColor");

	cout << "Vertex atr " << verAttribute << endl;
	cout << "Color atr " << colorAt << endl;

		// el glVertexAttribPointer es muy importante ya que espeficia como leer el buffer, como interpretar la data que ponemos adentro del mismo
	glVertexAttribPointer(verAttribute, 3, GL_FLOAT, GL_FALSE, sizeof(float) * 6, (void*)(0 * sizeof(float))); //index, tamaño del VERTEX , tipo de dato, si queremos que se normalice, stride (cuanto tiene que recorrer hasta el siguiente VERTEX, no al siguiente Attribute), stride al siguiente atributo
	glVertexAttribPointer(colorAt, 3, GL_FLOAT, GL_FALSE, sizeof(float) * 6, (void*)(3 * sizeof(float)));

	glEnableVertexAttribArray(verAttribute);  //Habilita y deshabilita los attributos del array vertex
	glEnableVertexAttribArray(colorAt);  //Habilita y deshabilita los attributos del array vertex
}
