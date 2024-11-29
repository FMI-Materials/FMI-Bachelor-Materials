//
// ================================================
// | Grafica pe calculator                        |
// ================================================
// | Cursul VII - 07_01_Shader.frag      |
// =======================================
// 
//  Shaderul de fragment / Fragment shader - afecteaza culoarea pixelilor;
//

#version 330

//	Variabile de intrare (dinspre Shader.vert);
in vec3 ex_Color; 

//	Variabile de iesire	(spre programul principal);
out vec3 out_Color;

//  Variabile uniforme;
uniform int codCol;

void main(void)
{
    switch (codCol)
    {
        case 1: 
            out_Color=vec3(0.0, 0.0, 0.0); 
            break;
        default: 
            out_Color=ex_Color;
    }
}