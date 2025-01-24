//
// ================================================
// | Grafica pe calculator                        |
// ================================================
// | Laboratorul III - 03_02_Shader.frag |
// ======================================
// 
//  Shaderul de fragment / Fragment shader - afecteaza culoarea pixelilor;
//

#version 330 core

//	Variabile de intrare (dinspre Shader.vert);
in vec4 ex_Color;

//	Variabile de iesire	(spre programul principal);
out vec4 out_Color;		//	Culoarea actualizata;

//	Variabilele uniforme;
uniform int codCol;

//	Actualizeaza culoarea in functie de codCol;
void main(void)
{
  switch (codCol)
  {
	case 0: 
	  out_Color = ex_Color;
	  break;
	case 1: 
		out_Color=vec4 (0.0, 0.0, 1.0, 0.0);
		break;
	case 2:
		out_Color=vec4 (1.0, 0.0, 0.0, 0.0);
		break;
	default:
		break;
  };
}
 