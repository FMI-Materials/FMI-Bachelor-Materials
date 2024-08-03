// Shader-ul de fragment / Fragment shader  
#version 400

in vec3 ex_Color; 
out vec3 out_Color;
uniform int codColShader;

void main(void)
{
    switch (codColShader)
    {
        case 1: 
            out_Color=vec3(0.0, 0.0, 0.0); 
            break;
        default: 
            out_Color=ex_Color;
    }
}