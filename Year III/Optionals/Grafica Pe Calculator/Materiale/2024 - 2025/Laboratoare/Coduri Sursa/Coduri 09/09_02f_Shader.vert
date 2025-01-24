//
// ================================================
// | Grafica pe calculator                        |
// ================================================
// | Laboratorul IX - 09_02f_Shader.vert |
// =======================================
// 
//  Shaderul de varfuri; 

#version 330 core

//  Variabile de intrare (dinspre programul principal);
layout(location=0) in vec3 in_Position;                 //  Se preia din buffer de pe prima pozitie (0) atributul care contine coordonatele;
layout(location=1) in vec3 in_Normal;                   //  Se preia din buffer de pe a doua pozitie (1) atributul care contine normala;

//  Variabile de iesire;
out vec4 gl_Position; 
out vec3 Normal;
out vec3 FragPos;
out vec3 inLightPos;
out vec3 inViewPos;

//  Variabile uniforme;
uniform mat4 view;
uniform mat4 projection;
uniform vec3 lightPos;
uniform vec3 viewPos;

void main(void)
  {
    gl_Position = projection*view*vec4(in_Position, 1.0);
    Normal=vec3(projection*view*vec4(in_Normal,0.0));
    inLightPos= vec3(projection*view* vec4(lightPos, 1.0f));
    inViewPos=vec3(projection*view*vec4(viewPos, 1.0f));
    FragPos = vec3(gl_Position);
   } 
