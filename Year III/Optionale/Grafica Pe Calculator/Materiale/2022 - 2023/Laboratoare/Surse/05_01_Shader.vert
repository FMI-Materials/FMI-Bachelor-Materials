// Shader-ul de varfuri  
#version 330

layout (location = 0) in vec4 in_Position;
layout (location = 1) in vec4 in_Color;

out vec4 gl_Position; 
out vec4 ex_Color;
uniform mat4 myMatrix;

void main(void)
  {
    gl_Position = myMatrix*in_Position;
    ex_Color = in_Color;
   } 
 