// Shader-ul de varfuri  
 #version 330

layout(location=0) in vec3 in_Position;
layout(location=1) in vec3 in_Normal;
layout(location=2) in vec3 in_Color;
 
out vec3 FragPos;
out vec3 Normal;
out vec3 inLightPos;
out vec3 inViewPos;
out vec3 ex_Color;
out vec3 dir;

uniform mat4 matrUmbra;
uniform mat4 view;
uniform mat4 projection;
uniform vec3 lightPos; 
uniform vec3 viewPos;
uniform int codCol;

void main(void)
  {
    ex_Color=in_Color;
    if (codCol==0)
    {
        gl_Position = projection*view*vec4(in_Position, 1.0);
        FragPos = vec3(gl_Position);
        Normal=vec3(projection*view*vec4(in_Normal,0.0));
        inLightPos= vec3(projection*view* vec4(lightPos, 1.0f));
        dir = mat3(projection*view) * vec3(0.0,100.0,200.0); // pentru sursa directionala
        inViewPos=vec3(projection*view*vec4(viewPos, 1.0f));
    }
    if (codCol==1)
    {
		gl_Position = projection*view*matrUmbra*vec4(in_Position, 1.0);
        FragPos = vec3(gl_Position);
    } 
   } 
 