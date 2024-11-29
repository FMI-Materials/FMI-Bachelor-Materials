//
// ================================================
// | Grafica pe calculator                        |
// ================================================
// | Laboratorul IX - 09_03v_Shader.frag |
// =======================================
// 
//  Shaderul de fragment;
//

#version 330 core

 
in vec4 ex_Color; 
out vec4 out_Color;

void main(void)
  { 
	out_Color = ex_Color;
  }
 