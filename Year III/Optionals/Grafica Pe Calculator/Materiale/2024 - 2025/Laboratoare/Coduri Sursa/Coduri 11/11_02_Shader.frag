//
// ================================================
// | Grafica pe calculator                        |
// ================================================
// | Laboratorul XI - 11_02_Shader.frag |
// =====================================
// 
//  Shaderul de fragment / Fragment shader - afecteaza culoarea pixelilor;
//

#version 330 core

in vec4 ex_Color;
out vec4 out_Color;
uniform int codCol;

void main(void)
  {
    switch (codCol)
    {
        case 1: 
            out_Color=vec4(0.0, 0.0, 0.0,0.0); 
            break;
        default: 
            out_Color=ex_Color;
    }
  }
 