//
// ================================================
// | Grafica pe calculator                        |
// ================================================
// | Cursul VI - 06_01_Shader.frag     |
// =====================================
// 
//  Shaderul de fragment / Fragment shader - afecteaza culoarea pixelilor;
//

 #version 330 core

in vec2 tex_Coord;
out vec4 out_Color;

uniform sampler2D myTexture;

void main(void)
  {
      out_Color = texture(myTexture, tex_Coord);
  }
 