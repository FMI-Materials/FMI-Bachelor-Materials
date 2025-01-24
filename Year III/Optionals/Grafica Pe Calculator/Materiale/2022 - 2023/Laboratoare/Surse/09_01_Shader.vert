// Shader-ul de varfuri  
#version 400

layout(location=0) in vec4 in_Position;
layout(location=1) in vec3 in_Color;
out vec4 gl_Position; // comentati daca este cazul!
out vec3 ex_Color;
uniform mat4 myMatrix;

void main(void)
{
    gl_Position = myMatrix*in_Position;
    ex_Color=in_Color;
} 
 