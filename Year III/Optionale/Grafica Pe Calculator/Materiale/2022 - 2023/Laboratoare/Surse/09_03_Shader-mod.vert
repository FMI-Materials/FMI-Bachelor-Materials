// Shader-ul de varfuri  
#version 330
layout(location=0) in vec4 in_Position;
layout(location=1) in vec3 in_Color;
layout(location=2) in vec3 in_Normal;
 
out vec3 FragPos;
out vec3 Normal;
out vec3 inLightPos;
out vec3 inViewPos;
out vec3 ex_Color;
out vec3 dir;
out vec4 gl_Position; // comentati daca este cazul!

uniform mat4 viewShader;
uniform mat4 projectionShader;
uniform mat4 myMatrix;
uniform vec3 lightPos;
uniform vec3 viewPos;
uniform vec3 lightColor;
uniform int codCol;

void main(void)
{
    ex_Color=in_Color;
   	if (codCol==0)
    {
		gl_Position = projectionShader*viewShader*in_Position;
        Normal =mat3(projectionShader*viewShader)*in_Normal; 
        inLightPos = vec3(projectionShader*viewShader* vec4(lightPos, 1.0f));
        inViewPos =vec3(projectionShader*viewShader*vec4(viewPos, 1.0f));
        dir = mat3(projectionShader*viewShader) * vec3(0.0,100.0,200.0); // pentru sursa directionala
        FragPos = vec3(gl_Position);
        ex_Color = in_Color;
    }
} 
 