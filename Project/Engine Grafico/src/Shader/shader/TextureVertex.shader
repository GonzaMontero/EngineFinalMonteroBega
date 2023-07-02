// computa la info que llega de afuera, entra la info de cada vertice que está en los buffers
#version 330 core

in vec3 position;
in vec3 inColor;
in vec2 uv;

out vec3 outColor;
out vec2 uvOut;
uniform mat4 trsmatrix;
uniform mat4 view;
uniform mat4 proj;


void main()
{
	gl_Position = proj * view * trsmatrix * vec4(position, 1.0);
	outColor = inColor;
	uvOut = uv;
};