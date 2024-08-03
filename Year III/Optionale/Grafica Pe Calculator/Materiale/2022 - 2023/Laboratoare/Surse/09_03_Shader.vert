// Shader-ul de varfuri  
#version 330

layout(location=0) in vec4 in_Position;
layout(location=1) in vec3 in_Color;
out vec4 gl_Position; // comentati daca este cazul!
out vec3 ex_Color;
uniform mat4 viewShader;
uniform mat4 projectionShader;

void main(void)
{
    gl_Position = projectionShader*viewShader*in_Position;
    ex_Color=in_Color;
} 
 