#shader vertex
#version 330 core

layout(location = 0) in vec4 position;
layout(location = 1) in vec4 customColor;
out vec4 color;

void main()
{
	gl_Position = position;
	color = customColor;
};


#shader fragment
#version 330 core

in vec4 color;
out vec4 outColor;

void main()
{
	outColor = color;
};