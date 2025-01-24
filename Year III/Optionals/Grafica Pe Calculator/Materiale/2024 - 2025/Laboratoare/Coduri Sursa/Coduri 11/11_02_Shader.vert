//
// ================================================
// | Grafica pe calculator                        |
// ================================================
// | Laboratorul XI - 11_02_Shader.vert |
// ======================================
// 
//  Shaderul de varfuri / Vertex shader - afecteaza geometria scenei; 

#version 330 core

layout(location=0) in vec4 in_Position;
layout(location=1) in vec3 in_Color;
layout(location=2) in vec3 in_Normal;

out vec4 gl_Position; 
out vec4 ex_Color;

uniform mat4 matrUmbra;
uniform mat4 view;
uniform mat4 projection;
uniform vec3 lightPos;
uniform vec3 viewPos;
uniform vec3 objectColor;
uniform vec3 lightColor;
uniform int codCol;

void main(void)
  {
  	if ( codCol==0 )
    {
        // Elemente geometrice pentru iluminare
		gl_Position = projection*view*in_Position;
        vec3 Normal=mat3(projection*view)*in_Normal; 
        vec3 inLightPos= vec3(projection*view* vec4(lightPos, 1.0f));
        vec3 inViewPos=vec3(projection*view*vec4(viewPos, 1.0f));
        vec3 FragPos = vec3(gl_Position);
        
        // Implementarea modelului de iluminare
        // Ambient
        float ambientStrength = 0.2f;
        vec3 ambient = ambientStrength * lightColor;
  	
        // Diffuse 
        vec3 norm = normalize(Normal);
        vec3 lightDir = normalize(inLightPos - FragPos);
        // vec3 lightDir = normalize(-inLightPos); // pentru sursa directionala
        float diff = max(dot(norm, lightDir), 0.0);
        // vec3 diffuse = diff * lightColor;
        vec3 diffuse = pow(diff,0.2) * lightColor; // varianta de atenuare
    
        // Specular
        float specularStrength = 0.5f;
        vec3 viewDir = normalize(inViewPos - FragPos);
        vec3 reflectDir = reflect(-lightDir, norm);  
        float spec = pow(max(dot(viewDir, reflectDir), 0.0), 1);
        vec3 specular = specularStrength * spec * lightColor;  
        
        vec3 result = (ambient + diffuse ) * in_Color;
	    ex_Color = vec4(result, 1.0f);
    }
	if ( codCol==1 )
		gl_Position = projection*view*matrUmbra*in_Position;
   } 
 