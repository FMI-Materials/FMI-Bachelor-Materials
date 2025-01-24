// Shader-ul de varfuri  
#version 330

layout(location=0) in vec4 in_Position;
layout(location=1) in vec4 in_Color;
layout(location=2) in vec2 texCoord;

out vec4 gl_Position; 
out vec4 ex_Color;
out vec2 tex_Coord;
uniform mat4 myMatrix;
uniform mat4 view;
uniform mat4 projection;

void main(void)
  {
    gl_Position = projection*view*myMatrix*in_Position;
	ex_Color=in_Color;
    tex_Coord = vec2(texCoord.x, 1-texCoord.y);
   } 
 