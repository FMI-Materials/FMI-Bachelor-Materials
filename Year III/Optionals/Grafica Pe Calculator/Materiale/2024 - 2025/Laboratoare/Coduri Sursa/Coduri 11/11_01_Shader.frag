//
// ================================================
// | Grafica pe calculator                        |
// ================================================
// | Laboratorul XI - 11_01_Shader.frag |
// ======================================
// 
//  Shaderul de fragment / Fragment shader - afecteaza culoarea pixelilor;
//

#version 330 core


in vec4 ex_Color;
out vec4 out_Color;

void main(void)
  {
	out_Color = ex_Color;
  }
 