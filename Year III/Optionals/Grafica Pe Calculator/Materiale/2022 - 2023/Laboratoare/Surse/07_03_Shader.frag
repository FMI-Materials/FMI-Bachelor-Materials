// Shader-ul de fragment / Fragment shader  
 #version 330

in vec4 ex_Color;
out vec4 out_Color;
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