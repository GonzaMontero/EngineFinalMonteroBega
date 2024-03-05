#version 330 core

layout(location = 0) in vec3 inPosition;
layout(location = 1) in vec4 inColor;
layout(location = 2) in vec2 inTexCoord;
out vec4 outColor;
out vec2 TexCoord;

uniform mat4 model;
uniform mat4 proj;
uniform mat4 view;
void main(){
    gl_Position = proj * view * model * vec4(inPosition, 1.0);
    outColor = inColor;
    TexCoord = inTexCoord;
}