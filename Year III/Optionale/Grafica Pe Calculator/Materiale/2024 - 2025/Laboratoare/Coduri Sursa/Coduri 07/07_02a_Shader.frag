//
// ================================================
// | Grafica pe calculator                        |
// ================================================
// | Curs VII - 07_02a_Shader.frag       |
// =======================================
// 
//  Shaderul de fragment / Fragment shader - afecteaza culoarea pixelilor;
//

#version 330	//  Versiunea GLSL;

//	Variabile de intrare (dinspre Shader.vert);
in vec4 ex_Color;

//	Variabile de iesire	(spre programul principal);
out vec4 out_Color;

//  Variabile uniforme;
uniform int codColShader;

void main(void)
  {
    switch (codColShader)
    {
        case 1: 
            out_Color=vec4(0.0, 0.0, 0.0,0.0); 
            break;
        default: 
            out_Color=ex_Color;
    }
  }