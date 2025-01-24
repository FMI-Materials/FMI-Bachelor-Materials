//
// ================================================
// | Grafica pe calculator                        |
// ================================================
// | Laboratorul X - 10_02_Shader.vert |
// =====================================
// 
//  Shaderul de varfuri / Vertex shader - afecteaza geometria scenei; 

#version 330 core

layout(location=0) in vec4 in_Position;
layout(location=1) in vec3 in_Color;
layout(location=2) in vec3 in_Normal;
 
out vec3 FragPos;
out vec3 Normal;
out vec3 inLightPos;
out vec3 inViewPos;
out vec3 ex_Color;
out vec3 dir;
 
uniform mat4 matrUmbra;
uniform mat4 myMatrix;
uniform mat4 view;
uniform mat4 projection;
uniform vec3 lightPos;
uniform vec3 viewPos;
uniform vec3 lightColor;
uniform int codCol;

void main(void)
  {
    ex_Color=in_Color;
   	if (codCol==0)
    {
		gl_Position = projection*view*myMatrix*in_Position;
        Normal =mat3(projection*view*myMatrix)*in_Normal; 
        inLightPos = vec3(projection*view*myMatrix* vec4(lightPos, 1.0f));
        inViewPos =vec3(projection*view*myMatrix*vec4(viewPos, 1.0f));
        dir = mat3(projection*view*myMatrix) * vec3(0.0,100.0,200.0); // pentru sursa directionala
        FragPos = vec3(gl_Position);
    }
	if (codCol==1)
		gl_Position = projection*view*matrUmbra*myMatrix*in_Position;
        FragPos = vec3(gl_Position);
   } 