//
// ================================================
// | Grafica pe calculator                        |
// ================================================
// | Curs VII - 07_02a_Shader.vert       |
// =======================================
// 
//  Shaderul de varfuri / Vertex shader - afecteaza geometria scenei; 
//

#version 330    //  Versiunea GLSL;

//  Variabile de intrare (dinspre programul principal);
layout (location = 0) in vec4 in_Position;		//  Se preia din buffer de pe prima pozitie (0) atributul care contine coordonatele;
layout (location = 1) in vec4 in_Color;			//  Se preia din buffer de pe a doua pozitie (1) atributul care contine culoarea;
layout (location = 2) in mat4 modelMatrix;		//  Se preia din buffer de pe a treia pozitie (2) atributul care contine atributul instantiat;

//  Variabile de iesire;
out vec4 gl_Position;   //  Transmite pozitia actualizata spre programul principal;
out vec4 ex_Color;      //  Transmite culoarea (de modificat in Shader.frag); 

//  Variabile uniforme;
uniform mat4 viewMatrix;
uniform mat4 projectionMatrix;
 
void main(void)
  {
    gl_Position = projectionMatrix*viewMatrix*modelMatrix*in_Position;
	ex_Color=in_Color;
   } 
 