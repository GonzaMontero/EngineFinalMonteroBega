#version 330 core

in vec3 outColor;
in vec2 outUv;

uniform sampler2D thisTexture;

void main()
{	
	gl_FragColor = texture(thisTexture, outUv) * vec4(outColor, 1.0);
};

