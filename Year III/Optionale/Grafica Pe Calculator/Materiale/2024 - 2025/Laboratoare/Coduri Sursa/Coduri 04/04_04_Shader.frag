//
// ================================================
// | Grafica pe calculator                        |
// ================================================
// | Laboratorul IV - 04_04_Shader.frag |
// ======================================
// 
//  Shaderul de fragment / Fragment shader - afecteaza culoarea pixelilor;
//

#version 330 core

//	Variabile de intrare (dinspre Shader.vert);
in vec4 ex_Color;
in vec2 tex_Coord;		//	Coordonata de texturare;

//	Variabile de iesire	(spre programul principal);
out vec4 out_Color;		//	Culoarea actualizata;

//  Variabile uniforme;
uniform sampler2D myTexture;

//	Variabile pentru culori;
vec4 red = vec4(1.0,0.0,0.0,1.0);
vec4 green= vec4(0.0,1.0,0.0,1.0);

void main(void)
  {
  //  out_Color=ex_Color;                                           // Culoarea este cea asociata varfurilor;        
  //  out_Color=mix(red,green,0.9);                                 // Amestecarea a doua culori cu functia mix;
   out_Color = mix(texture(myTexture, tex_Coord), ex_Color, 0.2);	//	Amestecarea texturii si a culorii;
  }
 