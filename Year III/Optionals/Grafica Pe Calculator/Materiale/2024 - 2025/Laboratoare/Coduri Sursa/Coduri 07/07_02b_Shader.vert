//
// ================================================
// | Grafica pe calculator                        |
// ================================================
// | Curs VII - 07_02b_Shader.vert       |
// =======================================
// 
//  Shaderul de varfuri / Vertex shader - afecteaza geometria scenei; 
//

#version 330    //  Versiunea GLSL;

//  Variabile de intrare (dinspre programul principal);
layout (location = 0) in vec4 in_Position;		//  Se preia din buffer de pe prima pozitie (0) atributul care contine coordonatele;

//  Variabile de iesire;
out vec4 gl_Position;   //  Transmite pozitia actualizata spre programul principal;
out vec4 ex_Color;      //  Transmite culoarea (de modificat in Shader.frag); 

//  Variabile uniforme;
uniform mat4 viewMatrix;
uniform mat4 projectionMatrix;

// Constante si variabile utilizate
const float PI = 3.141592;
int instID;

mat4 matrTransl, matrRot;

// Functie pentru generararea matricei 4x4 a translatiei de vector (Tx, Ty, Tz)
mat4 translate(float Tx, float Ty, float Tz)
{
mat4 mTransl = mat4
				(1.0, 0.0, 0.0, 0.0,
				 0.0, 1.0, 0.0, 0.0,
				 0.0, 0.0, 1.0, 0.0,
				  Tx,  Ty,  Tz, 1.0);
return mTransl;
}

// Functie pentru generararea matricei 4x4 a rotatiei de unghi theta in jurul axei Ox
mat4 rotateX(float theta)
{
mat4 mrotX = mat4
				(1.0,        0.0,         0.0,  0.0,
				 0.0,  cos(theta), sin(theta),  0.0,
				 0.0, -sin(theta), cos(theta),  0.0,
				 0.0,        0.0,         0.0,  1.0);
return mrotX;
}

// Functie pentru generararea matricei 4x4 a rotatiei de unghi theta in jurul axei Oy
mat4 rotateY(float theta)
{
mat4 mrotY = mat4
				( cos(theta),   0.0, sin(theta), 0.0,
				         0.0,   1.0,        0.0, 0.0,
				 -sin(theta),   0.0, cos(theta), 0.0,
				         0.0,   0.0,        0.0, 1.0);
return mrotY;
}

// Functie pentru generararea matricei 4x4 a rotatiei de unghi theta in jurul axei Oz
mat4 rotateZ(float theta)
{
mat4 mrotZ = mat4
				(cos(theta), sin(theta), 0.0,  0.0,
				-sin(theta), cos(theta), 0.0,  0.0,
				        0.0,        0.0, 1.0,  0.0,
				        0.0,        0.0, 0.0,  1.0);      
return mrotZ;
}

void main(void)
  {

	// Este folosita variabila gl_InstanceID pentru extragerea ID-ului instantei curente
	float instID = float(gl_InstanceID);

	// Generarea matricei de translatie
	matrTransl=translate
	(90 * instID * cos(instID), 90 * instID *  sin(instID), 0.0);
    
	// Matricea de rotatie este produsul a trei rotatii
	matrRot = rotateX((instID + 1) * PI / 10) 
			* rotateY(instID  * PI / 6) 
			* rotateZ(3 * instID * PI / 2);
	
	// Pozitia finala a varfului corespunzator instantei procesate
	gl_Position = projectionMatrix * viewMatrix * matrTransl * matrRot * in_Position;
	
	// Stabilirea culorii varfului (varfurile unei instante au aceeasi culoare)

	ex_Color=vec4(0.35f + 0.30f * (sin(instID / 4.0f + 2.0f) + 1.0f), 
				  0.25f + 0.25f * (sin(instID / 5.0f + 3.0f) + 1.0f),
				  0.25f + 0.35f * (sin(instID / 6.0f + 4.0f) + 1.0f), 
				  1.0f);
   } 
