// Shader-ul de fragment / Fragment shader  
 #version 330

in vec4 ex_Color;
in vec2 tex_Coord;
out vec4 out_Color;

vec4 red = vec4(1.0,0.0,0.0,1.0);
vec4 green= vec4(0.0,1.0,0.0,1.0);

uniform sampler2D myTexture;

void main(void)
  {
  // out_Color=ex_Color;
  // out_Color=mix(red,green,0.5);
   out_Color = mix(texture(myTexture, tex_Coord), ex_Color, 0.2);
  }
 