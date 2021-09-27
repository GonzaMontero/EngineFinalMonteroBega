#shader fragment
#version 330 core

in vec3 outColor;

void main()
{
	gl_FragColor = vec3(outColor, 1.0);
};