// Shader-ul de varfuri  
#version 330

layout(location=0) in vec4 in_Position;
layout(location=1) in vec3 in_Color;
layout(location=2) in vec3 in_Normal;

out vec4 gl_Position; 
out vec3 Normal;
out vec3 FragPos;
out vec3 inLightPos;
out vec3 inViewPos;
out vec4 ex_Color;
 
uniform mat4 view;
uniform mat4 projection;
uniform vec3 lightPos;
uniform vec3 viewPos;

void main(void)
  {
    gl_Position = projection*view*in_Position;
    FragPos = vec3(gl_Position);
    Normal=vec3(projection*view*vec4(in_Normal,0.0));
    inLightPos= vec3(projection*view* vec4(lightPos, 1.0f));
    inViewPos=vec3(projection*view*vec4(viewPos, 1.0f));
    ex_Color=vec4(in_Color,1.0);
   } 
