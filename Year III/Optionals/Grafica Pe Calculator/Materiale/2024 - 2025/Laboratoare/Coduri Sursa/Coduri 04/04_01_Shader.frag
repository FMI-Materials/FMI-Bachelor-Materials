//
// ================================================
// | Grafica pe calculator                        |
// ================================================
// | Cursul IV - 04_01_Shader.frag     |
// =====================================
// 
//  Shaderul de fragment / Fragment shader - afecteaza culoarea pixelilor;
//

#version 330 core

//	Variabile de intrare (dinspre Shader.vert);
in vec4 ex_Color;

//	Variabile de iesire	(spre programul principal);
out vec4 out_Color;		//	Culoarea actualizata;

void main(void)
  {
    out_Color = ex_Color;
  }
 