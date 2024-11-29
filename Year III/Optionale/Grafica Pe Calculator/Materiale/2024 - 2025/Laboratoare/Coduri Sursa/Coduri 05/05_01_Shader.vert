//
// ================================================
// | Grafica pe calculator                        |
// ================================================
// | Cursul VI - 06_01_Shader.vert     |
// =====================================
// 
//  Shaderul de varfuri / Vertex shader - afecteaza geometria scenei; 
// 

 #version 330 core


layout(location=0) in vec4 in_Position;
layout(location=1) in vec2 texCoord;

out vec4 gl_Position; 
out vec2 tex_Coord;

uniform mat4 viewMatrix;
uniform mat4 projectionMatrix;
 
void main(void)
  {
    gl_Position = projectionMatrix*viewMatrix*in_Position;
    tex_Coord = vec2(texCoord.x, 1-texCoord.y);	
   } 
 