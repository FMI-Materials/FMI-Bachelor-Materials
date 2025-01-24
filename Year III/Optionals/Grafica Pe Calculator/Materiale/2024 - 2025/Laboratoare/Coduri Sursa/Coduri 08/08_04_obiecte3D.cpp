//
// ================================================
// | Grafica pe calculator                        |
// ================================================
// | Laboratorul VIII - 08_04_obiecte3D.cpp|
// ========================================
// 
//	Program ce deseneaza cu ajutorul de buffere diferite (pentru varfuri, culori, indici) 2 obiecte 3D (un cub si o sfera), folosindu-se tehnicile MODERN OpenGL;
// 
// 
// 
//	Biblioteci
#include <windows.h>        //	Utilizarea functiilor de sistem Windows (crearea de ferestre, manipularea fisierelor si directoarelor);
#include <stdlib.h>         //  Biblioteci necesare pentru citirea shaderelor;
#include <stdio.h>
#include <math.h>			//	Biblioteca pentru calcule matematice;
#include <GL/glew.h>        //  Definește prototipurile functiilor OpenGL si constantele necesare pentru programarea OpenGL moderna; 
#include <GL/freeglut.h>    //	Include functii pentru: 
							//	- gestionarea ferestrelor si evenimentelor de tastatura si mouse, 
							//  - desenarea de primitive grafice precum dreptunghiuri, cercuri sau linii, 
							//  - crearea de meniuri si submeniuri;
#include "loadShaders.h"	//	Fisierul care face legatura intre program si shadere;
#include "glm/glm.hpp"		//	Bibloteci utilizate pentru transformari grafice;
#include "glm/gtc/matrix_transform.hpp"
#include "glm/gtx/transform.hpp"
#include "glm/gtc/type_ptr.hpp"


//  Identificatorii obiectelor de tip OpenGL;
GLuint
	VaoId1, VaoId2,
	VboId1, VboId2,
	EboId1, EboId2,
	ProgramId,
	viewLocation,
	projLocation,
	codColLocation;

float const PI = 3.141592f;
float const U_MIN = -PI / 2, U_MAX = PI / 2, V_MIN = 0, V_MAX = 2 * PI;
int const NR_PARR = 10, NR_MERID = 20;
float step_u = (U_MAX - U_MIN) / NR_PARR, step_v = (V_MAX - V_MIN) / NR_MERID;

// alte variabile
int codCol;
float radius = 50;
int index, index_aux;

// variabile pentru matricea de vizualizare
float Refx = 0.0f, Refy = 0.0f, Refz = 0.0f;
float alpha = 0.0f, beta = 0.0f, dist = 300.0f;
float Obsx, Obsy, Obsz;
float Vx = 0.0f, Vy = 0.0f, Vz = -1.0f;
float incr_alpha1 = 0.01f, incr_alpha2 = 0.01f;

// variabile pentru matricea de proiectie
float width = 800, height = 600, znear = 1, fov = 30;

// pentru fereastra de vizualizare 
GLint winWidth = 1000, winHeight = 600;

// vectori
glm::vec3 Obs, PctRef, Vert;

// matrice utilizate
glm::mat4 view, projection;

void ProcessNormalKeys(unsigned char key, int x, int y)
{
	switch (key) {			//	Apasarea tastelor `+` si `-` schimba pozitia observatorului (se departeaza / aproprie);
	case '-':
		dist -= 5.0;
		break;
	case '+':
		dist += 5.0;
		break;
	}
	if (key == 27)
		exit(0);
}
void ProcessSpecialKeys(int key, int xx, int yy)
{
	switch (key)						//	Procesarea tastelor 'LEFT', 'RIGHT', 'UP', 'DOWN';
	{									//	duce la deplasarea observatorului pe axele Ox si Oy;
	case GLUT_KEY_LEFT:
		beta -= 0.01f;
		break;
	case GLUT_KEY_RIGHT:
		beta += 0.01f;
		break;
	case GLUT_KEY_UP:
		alpha += incr_alpha1;
		if (abs(alpha - PI / 2) < 0.05)
		{
			incr_alpha1 = 0.f;
		}
		else
		{
			incr_alpha1 = 0.01f;
		}
		break;
	case GLUT_KEY_DOWN:
		alpha -= incr_alpha2;
		if (abs(alpha + PI / 2) < 0.05)
		{
			incr_alpha2 = 0.f;
		}
		else
		{
			incr_alpha2 = 0.01f;
		}
		break;
	}
}

//  Crearea si compilarea obiectelor de tip shader;
//	Trebuie sa fie in acelasi director cu proiectul actual;
//  Shaderul de varfuri / vertex shader - afecteaza geometria scenei;
//  Shaderul de fragment / Fragment shader - afecteaza culoarea pixelilor;
void CreateShaders(void)
{
	ProgramId = LoadShaders("08_04_Shader.vert", "08_04_Shader.frag");
	glUseProgram(ProgramId);
}

void CreateVAO1(void)
{
	// SFERA
	// Matricele pentru varfuri, culori, indici
	glm::vec4 Vertices1[(NR_PARR + 1) * NR_MERID];
	glm::vec3 Colors1[(NR_PARR + 1) * NR_MERID];
	GLushort Indices1[2 * (NR_PARR + 1) * NR_MERID + 4 * (NR_PARR + 1) * NR_MERID];
	for (int merid = 0; merid < NR_MERID; merid++)
	{
		for (int parr = 0; parr < NR_PARR + 1; parr++)
		{
			// implementarea reprezentarii parametrice 
			float u = U_MIN + parr * step_u; // valori pentru u si v
			float v = V_MIN + merid * step_v;
			float x_vf = radius * cosf(u) * cosf(v); // coordonatele varfului corespunzator lui (u,v)
			float y_vf = radius * cosf(u) * sinf(v);
			float z_vf = radius * sinf(u);

			// identificator ptr varf; coordonate + culoare + indice la parcurgerea meridianelor
			index = merid * (NR_PARR + 1) + parr;
			Vertices1[index] = glm::vec4(x_vf, y_vf, z_vf, 1.0);
			Colors1[index] = glm::vec3(0.1f + sinf(u), 0.1f + cosf(v), 0.1f + -1.5 * sinf(u));
			Indices1[index] = index;

			// indice ptr acelasi varf la parcurgerea paralelelor
			index_aux = parr * (NR_MERID)+merid;
			Indices1[(NR_PARR + 1) * NR_MERID + index_aux] = index;

			// indicii pentru desenarea fetelor, pentru varful curent sunt definite 4 varfuri
			if ((parr + 1) % (NR_PARR + 1) != 0) // varful considerat sa nu fie Polul Nord
			{
				int AUX = 2 * (NR_PARR + 1) * NR_MERID;
				int index1 = index; // varful v considerat
				int index2 = index + (NR_PARR + 1); // dreapta lui v, pe meridianul urmator
				int index3 = index2 + 1;  // dreapta sus fata de v
				int index4 = index + 1;  // deasupra lui v, pe acelasi meridian
				if (merid == NR_MERID - 1)  // la ultimul meridian, trebuie revenit la meridianul initial
				{
					index2 = index2 % (NR_PARR + 1);
					index3 = index3 % (NR_PARR + 1);
				}
				Indices1[AUX + 4 * index] = index1;  // unele valori ale lui Indices, corespunzatoare Polului Nord, au valori neadecvate
				Indices1[AUX + 4 * index + 1] = index2;
				Indices1[AUX + 4 * index + 2] = index3;
				Indices1[AUX + 4 * index + 3] = index4;
			}
		}
	};

	// generare VAO/buffere
	glGenVertexArrays(1, &VaoId1);
	glBindVertexArray(VaoId1);
	glGenBuffers(1, &VboId1); // atribute
	glGenBuffers(1, &EboId1); // indici

	// legare+"incarcare" buffer
	glBindBuffer(GL_ARRAY_BUFFER, VboId1);
	glBufferData(GL_ARRAY_BUFFER, sizeof(Vertices1) + sizeof(Colors1), NULL, GL_STATIC_DRAW);
	glBufferSubData(GL_ARRAY_BUFFER, 0, sizeof(Vertices1), Vertices1);
	glBufferSubData(GL_ARRAY_BUFFER, sizeof(Vertices1), sizeof(Colors1), Colors1);
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EboId1);
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(Indices1), Indices1, GL_STATIC_DRAW);

	// atributele; 
	glEnableVertexAttribArray(0); // atributul 0 = pozitie
	glVertexAttribPointer(0, 4, GL_FLOAT, GL_FALSE, 0, (GLvoid*)(0));
	glEnableVertexAttribArray(1); // atributul 1 = culoare
	glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(GLfloat), (GLvoid*)(sizeof(Vertices1)));
}

void CreateVAO2(void)
{
	// CUBUL 
	// 
	GLfloat Vertices2[] =
	{
		-20.0f, -20.0f, 50.0f, 1.0f,
		 20.0f, -20.0f, 50.0f, 1.0f,
		 20.0f,  20.0f, 50.0f, 1.0f,
		-20.0f,  20.0f, 50.0f, 1.0f,
		-20.0f, -20.0f, 90.0f, 1.0f,
		 20.0f, -20.0f, 90.0f, 1.0f,
		 20.0f,  20.0f, 90.0f, 1.0f,
		-20.0f,  20.0f, 90.0f, 1.0f
	};

	GLfloat Colors2[] =
	{
		0.8f, 0.8f, 0.8f,
		0.7f, 0.7f, 0.7f,
		0.6f, 0.6f, 0.6f,
		0.5f, 0.5f, 0.5f,
		0.4f, 0.4f, 0.4f,
		0.3f, 0.3f, 0.3f,
		0.2f, 0.2f, 0.2f,
		0.1f, 0.1f, 0.1f
	};

	GLushort Indices2[] =
	{
	  1, 2, 0,   2, 0, 3,
	  2, 3, 6,   6, 3, 7,
	  7, 3, 4,   4, 3, 0,
	  4, 0, 5,   5, 0, 1,
	  1, 2, 5,   5, 2, 6,
	  5, 6, 4,   4, 6, 7,
	};

	// generare VAO/buffere
	glGenVertexArrays(1, &VaoId2);
	glBindVertexArray(VaoId2);
	glGenBuffers(1, &VboId2); // atribute
	glGenBuffers(1, &EboId2); // indici

	// legare+"incarcare" buffer
	glBindBuffer(GL_ARRAY_BUFFER, VboId2);
	glBufferData(GL_ARRAY_BUFFER, sizeof(Vertices2) + sizeof(Colors2), NULL, GL_STATIC_DRAW);
	glBufferSubData(GL_ARRAY_BUFFER, 0, sizeof(Vertices2), Vertices2);
	glBufferSubData(GL_ARRAY_BUFFER, sizeof(Vertices2), sizeof(Colors2), Colors2);
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EboId2);
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(Indices2), Indices2, GL_STATIC_DRAW);

	// atributele; 
	glEnableVertexAttribArray(0); // atributul 0 = pozitie
	glVertexAttribPointer(0, 4, GL_FLOAT, GL_FALSE, 0, (GLvoid*)(0));
	glEnableVertexAttribArray(1); // atributul 1 = culoare
	glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(GLfloat), (GLvoid*)(sizeof(Vertices2)));
}

//	Schimba inaltimea/latimea scenei in functie de modificarile facute de utilizator ferestrei (redimensionari);
void ReshapeFunction(GLint newWidth, GLint newHeight)
{
	glViewport(0, 0, newWidth, newHeight);
	winWidth = newWidth;
	winHeight = newHeight;
	width = winWidth / 10, height = winHeight / 10;
}

// Elimina obiectele de tip shader dupa rulare;
void DestroyShaders(void)
{
	glDeleteProgram(ProgramId);
}

//  Eliminarea obiectelor de tip VBO dupa rulare;
void DestroyVBO(void)
{
	//  Eliberarea atributelor din shadere (pozitie, culoare, texturare etc.);
	glDisableVertexAttribArray(1);
	glDisableVertexAttribArray(0);

	//  Stergerea bufferelor pentru VARFURI (Coordonate, Culori), INDICI;
	glBindBuffer(GL_ARRAY_BUFFER, 0);
	glDeleteBuffers(1, &VboId1);
	glDeleteBuffers(1, &EboId1);
	glDeleteBuffers(1, &VboId2);
	glDeleteBuffers(1, &EboId2);
}

//  Functia de eliberare a resurselor alocate de program;
void Cleanup(void)
{
	DestroyShaders();
	DestroyVBO();
}

//  Setarea parametrilor necesari pentru fereastra de vizualizare;
void Initialize(void)
{
	glClearColor(1.0f, 1.0f, 1.0f, 0.0f);
	CreateVAO1();
	CreateVAO2();
	CreateShaders();
	viewLocation = glGetUniformLocation(ProgramId, "viewShader");
	projLocation = glGetUniformLocation(ProgramId, "projectionShader");
	codColLocation = glGetUniformLocation(ProgramId, "codCol");
}

//	Functie utilizata in setarea matricelor de vizualizare si proiectie;
void SetMVP(void)
{
	//pozitia observatorului
	Obsx = Refx + dist * cos(alpha) * cos(beta);
	Obsy = Refy + dist * cos(alpha) * sin(beta);
	Obsz = Refz + dist * sin(alpha);

	// reperul de vizualizare
	glm::vec3 Obs = glm::vec3(Obsx, Obsy, Obsz);   // se schimba pozitia observatorului	
	glm::vec3 PctRef = glm::vec3(Refx, Refy, Refz); // pozitia punctului de referinta
	glm::vec3 Vert = glm::vec3(Vx, Vy, Vz); // verticala din planul de vizualizare 
	view = glm::lookAt(Obs, PctRef, Vert);
	glUniformMatrix4fv(viewLocation, 1, GL_FALSE, &view[0][0]);

	// matricea de proiectie 
	projection = glm::infinitePerspective(fov, GLfloat(width) / GLfloat(height), znear);
	glUniformMatrix4fv(projLocation, 1, GL_FALSE, &projection[0][0]);
}

//	Functia de desenare a graficii pe ecran;
void RenderFunction(void)
{
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	glEnable(GL_DEPTH_TEST);
	SetMVP();

	// SFERA
	glBindVertexArray(VaoId1);
	codCol = 0;
	glUniform1i(codColLocation, codCol);
	for (int patr = 0; patr < (NR_PARR + 1) * NR_MERID; patr++)
	{
		if ((patr + 1) % (NR_PARR + 1) != 0) // nu sunt considerate fetele in care in stanga jos este Polul Nord
			glDrawElements(
				GL_QUADS,
				4,
				GL_UNSIGNED_SHORT,
				(GLvoid*)((2 * (NR_PARR + 1) * (NR_MERID)+4 * patr) * sizeof(GLushort)));
	}
	
	// CUBUL
	glBindVertexArray(VaoId2);
	codCol = 0;
	glUniform1i(codColLocation, codCol);
	glDrawElements(GL_TRIANGLES, 36, GL_UNSIGNED_SHORT, (GLvoid*)(0));

	glutSwapBuffers();
	glFlush();
}

//	Punctul de intrare in program, se ruleaza rutina OpenGL;
int main(int argc, char* argv[])
{
	//  Se initializeaza GLUT si contextul OpenGL si se configureaza fereastra si modul de afisare;

	glutInit(&argc, argv);
	glutInitDisplayMode(GLUT_RGB | GLUT_DEPTH | GLUT_DOUBLE);							//	Se folosesc 2 buffere pentru desen (unul pentru afisare si unul pentru randare => animatii cursive) si culori RGB + 1 buffer pentru adancime;
	glutInitWindowSize(winWidth, winHeight);											//  Dimensiunea ferestrei;
	glutInitWindowPosition(100, 100);													//  Pozitia initiala a ferestrei;
	glutCreateWindow("Desenarea si survolarea a 2 obiecte 3D - OpenGL <<nou>>");		//	Creeaza fereastra de vizualizare, indicand numele acesteia;

	//	Se initializeaza GLEW si se verifica suportul de extensii OpenGL modern disponibile pe sistemul gazda;
	//  Trebuie initializat inainte de desenare;

	glewInit();

	Initialize();							//  Setarea parametrilor necesari pentru fereastra de vizualizare; 
	glutReshapeFunc(ReshapeFunction);		//	Schimba inaltimea/latimea scenei in functie de modificarile facute de utilizator ferestrei (redimensionari);
	glutDisplayFunc(RenderFunction);		//  Desenarea scenei in fereastra;
	glutIdleFunc(RenderFunction);			//	Asigura rularea continua a randarii;
	glutKeyboardFunc(ProcessNormalKeys);	//	Functii ce proceseaza inputul de la tastatura utilizatorului;
	glutSpecialFunc(ProcessSpecialKeys);
	glutCloseFunc(Cleanup);					//  Eliberarea resurselor alocate de program;

	//  Bucla principala de procesare a evenimentelor GLUT (functiile care incep cu glut: glutInit etc.) este pornita;
	//  Prelucreaza evenimentele si deseneaza fereastra OpenGL pana cand utilizatorul o inchide;

	glutMainLoop();

	return 0;
}