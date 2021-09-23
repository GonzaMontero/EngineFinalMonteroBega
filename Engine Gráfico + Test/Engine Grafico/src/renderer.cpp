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

static ShaderProgramSource ParseShader(const string& filepath)
{
	ifstream stream(filepath);

	enum class ShaderType
	{
		NONE = -1, VERTEX = 0, FRAGMENT = 1
	};

	string line;
	stringstream ss[2];
	ShaderType type = ShaderType::NONE;
	while (getline(stream, line))
	{
		if (line.find("#shader") != string::npos)
		{
			if (line.find("vertex") != string::npos)
			{
				type = ShaderType::VERTEX;
			}
			else if (line.find("fragment") != string::npos)
			{
				type = ShaderType::FRAGMENT;
			}
		}
		else
		{
			ss[(int)type] << line << '\n';
		}
	}

	return { ss[VERTEX].str(), ss[FRAGMENT].str() };
}

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
	//glDeleteProgram(shader);
}

void Renderer::DrawTriangle(CVec4 pos1, CVec4 pos2, CVec4 pos3) {

	float vertexs[24] = {
		pos1.x, pos1.y, pos1.z, pos1.w, pos1.color.R, pos1.color.G , pos1.color.B , pos1.color.A, //1
		pos2.x, pos2.y, pos2.z, pos2.w, pos2.color.R, pos2.color.G , pos2.color.B , pos2.color.A, //2
		pos3.x, pos3.y, pos3.z, pos3.w, pos3.color.R, pos3.color.G , pos3.color.B , pos3.color.A //3
	};

	unsigned int indices[3] = {
		1,2,3
	};

	unsigned int ibo;
	glGenBuffers(1, &ibo);
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, buffer);
	glBufferData(GL_ARRAY_BUFFER, 7 * 3 * sizeof(float), vertexs, GL_STATIC_DRAW);

	glGenBuffers(1, &buffer); //Genera X (en este caso 1) cantidad de buffers Buffer y le da un ID (en este caso el id buffer)
	glBindBuffer(GL_ARRAY_BUFFER, buffer); // selecciona el buffer, el primer parametro dice que tipo de info va a haber en el buffer y el segundo es el ID
	glBufferData(GL_ARRAY_BUFFER, 3 * sizeof(unsigned int), indices, GL_STATIC_DRAW); // le dice al buffer, donde guardar, que tanto espacio tiene disponible, que tiene que guardar y para que se va a usar 

	glEnableVertexAttribArray(0);  //Habilita y deshabilita los attributos del array vertex
	// el glVertexAttribPointer es muy importante ya que espeficia como leer el buffer, como interpretar la data que ponemos adentro del mismo
	glVertexAttribPointer(0, 8, GL_FLOAT, GL_FALSE, sizeof(float) * 8, (void*)(4 * sizeof(float))); //index, tamaño del VERTEX , tipo de dato, si queremos que se normalice, stride (cuanto tiene que recorrer hasta el siguiente VERTEX, no al siguiente Attribute), stride al siguiente atributo

	ShaderProgramSource source = ParseShader("res/shader/BasicShader.shader");

	unsigned int shader = CreateShader(source.VertexSource, source.FragmentSource);

	//unsigned int shader = CreateShader("res/shader/vertex.shader", "res/shader/fragment.shader");   /// solo va a funcionar si hacemos los archivos .shader con el codigo correspondiente

	glUseProgram(shader);

	glDrawElements(GL_TRIANGLES, 3, GL_UNSIGNED_INT, nullptr); //se usa si no tenes un index buffer, Dibuja segun un buffer, los parametros son que tipo de primitiva queres dibujar, desde donde queres empezar a leer la data y cantidad de indices qeu se van a renderizar

	buffer = NULL;
}
