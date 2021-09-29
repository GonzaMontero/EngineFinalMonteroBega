 // computa la info que llega de afuera, entra la info de cada vertice que está en los buffers
#version 330 core

/*layout(location = 0)*/ in vec3 position;
/*layout(location = 1)*/ in vec3 inColor;

out vec3 outColor;
uniform mat4 trsmatrix = mat4(1.0);

void main()
{
	gl_Position = trsmatrix * vec4(position, 1.0);
	outColor = inColor;
};