// Shader-ul de fragment / Fragment shader  
#version 330

in vec4 ex_Color;
out vec4 out_Color;
uniform int codCol;

void main(void)
  {
	switch (codCol) {
  case 0:
    out_Color = ex_Color;
    break;
  case 1:
    out_Color = vec4 (1.0, 0.0, 1.0, 0.0);
    break;
  case 2:
  out_Color = vec4 (1.0, 1.0, 0.0, 0.0);
    break;
  case 3:
  out_Color = vec4 (0.0, 1.0, 1.0, 0.0);
    break;
  case 4:
  out_Color = vec4 (1.0, 0.0, 1.0, 0.0);
    break;
 }
  }
 