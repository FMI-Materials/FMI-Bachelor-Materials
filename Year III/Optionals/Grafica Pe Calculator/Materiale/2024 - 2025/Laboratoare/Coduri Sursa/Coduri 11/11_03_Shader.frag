//
// ================================================
// | Grafica pe calculator                        |
// ================================================
// | Laboratorul XI - 11_03_Shader.frag |
// ======================================
// 
//  Shaderul de fragment / Fragment shader - afecteaza culoarea pixelilor;
//


#version 330 core

in vec3 FragPos;  
in vec3 Normal; 
in vec3 inLightPos;
in vec3 inViewPos;
in vec4 ex_Color;
in vec2 tex_Coord;	

uniform sampler2D myTexture;

out vec4 out_Color;

 
vec3 lightColor = vec3 (0.7, 0.9, 0.6);
vec3 objectColor = ex_Color.xyz;

void main(void)
  {
    //  Ambient;
    float ambientStrength = 0.8f;
    vec3 ambient_light = ambientStrength * lightColor;          //  ambient_light=ambientStrength*lightColor; 
    vec3 ambient_term= ambient_light * objectColor;             //  ambient_material=objectColor;
  	
    //  Diffuse; 
    vec3 norm = normalize(Normal);                              //  vectorul s;
    vec3 lightDir = normalize(inLightPos - FragPos);            //  vectorul L;
    float diff = max(dot(norm, lightDir), 0.0); 
    vec3 diffuse_light = lightColor;                            //  diffuse_light=lightColor;
    vec3 diffuse_term = diff * diffuse_light * objectColor;     //  diffuse_material=objectColor;
    
    //  Specular;
    float specularStrength = 0.8f;
    float shininess = 40.0f;
    vec3 viewDir = normalize(inViewPos - FragPos);              //  versorul catre observator;
    vec3 reflectDir = normalize(reflect(-lightDir, norm));      //  versorul vectorului R;
    float spec = pow(max(dot(viewDir, reflectDir), 0.0), shininess); 
    vec3 specular_light = specularStrength  * lightColor;       //  specular_light=specularStrength  * lightColor;
    vec3 specular_term = spec * specular_light * objectColor;   //  specular_material=objectColor;
       
    //  Culoarea finala; 
    vec3 emission=vec3(1.0, 0.0, 0.0);
    vec3 result = emission + (ambient_term + diffuse_term + specular_term);
	vec4 result4 = vec4(result, 1.0f);

    out_Color = mix(texture(myTexture, tex_Coord), result4, 0.0);
    }