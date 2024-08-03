// Shader-ul de fragment / Fragment shader  
 #version 330

in vec3 FragPos;  
in vec3 Normal; 
in vec3 inLightPos;
in vec3 inViewPos;

out vec4 out_Color;

uniform vec3 objectColor;
uniform vec3 lightColor;
uniform int codCol;

void main(void)
  {
        if (codCol == 0)
        {
            // Ambient
            float ambientStrength = 0.2f;
            vec3 ambient_light = ambientStrength * lightColor;  // ambient_light=ambientStrength*lightColor 
            vec3 ambient_term= ambient_light * objectColor; // ambient_material=objectColor
  	
            // Diffuse 
            vec3 norm = normalize(Normal); // vectorul s 
            vec3 lightDir = normalize(inLightPos - FragPos); // vectorul L
            float diff = max(dot(norm, lightDir), 0.0); // 
            vec3 diffuse_light = lightColor; // diffuse_light=lightColor;
            vec3 diffuse_term = diff * diffuse_light * objectColor; // diffuse_material=objectColor
    
            // Specular
            float specularStrength = 0.5f;
            float shininess = 100.0f;
            vec3 viewDir = normalize(inViewPos - FragPos); // versorul catre observator
            vec3 reflectDir = normalize(reflect(-lightDir, norm));  // versorul vectorului R 
            float spec = pow(max(dot(viewDir, reflectDir), 0.0), shininess); 
            vec3 specular_light = specularStrength  * lightColor; // specular_light=specularStrength  * lightColor
            vec3 specular_term = spec * specular_light * objectColor;   // specular_material=objectColor
       
            // Culoarea finala 
                vec3 emission=vec3(0.0, 0.0, 0.0);
            //vec3 emission=vec3(1.0,0.8,0.4);
            vec3 result = emission + (ambient_term + diffuse_term + specular_term);
            out_Color = vec4(result, 1.0f);
        }
        if (codCol == 1)
        {
            vec3 black = vec3(0.0, 0.0, 0.0);
            out_Color = vec4(black, 1.0);
        }
    }