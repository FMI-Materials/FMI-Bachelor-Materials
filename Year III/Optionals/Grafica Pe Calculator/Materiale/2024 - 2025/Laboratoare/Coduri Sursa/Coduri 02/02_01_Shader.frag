//
// ================================================
// | Grafica pe calculator                        |
// ================================================
// | Laboratorul II - 02_01_Shader.frag |
// ======================================
// 
//  Shaderul de fragment / Fragment shader - afecteaza culoarea pixelilor;
//

#version 330 core

in vec4 ex_Color;
out vec4 out_Color;

//	Variabilele uniforme;
uniform int codColShader;

//	Actualizeaza culoarea in functie de codColShader;
void main(void)
  {
	if ( codColShader == 0 )
		out_Color = ex_Color;
	else
		out_Color=vec4 (1.0, 0.0, 1.0, 0.0);
  }
 