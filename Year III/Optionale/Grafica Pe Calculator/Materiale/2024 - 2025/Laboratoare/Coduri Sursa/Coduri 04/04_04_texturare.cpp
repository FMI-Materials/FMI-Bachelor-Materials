//
// ================================================
// | Grafica pe calculator                        |
// ================================================
// | Laboratorul IV - 04_04_texturare.cpp |
// ========================================
// 
//	Program ce deseneaza un patrat, caruia i se aplica o textura, folosindu-se tehnicile MODERN OpenGL;
//	ELEMENTE DE NOUTATE:
//	- utilizarea texturilor;
//	- folosirea unor functii de amestecare in shaderul de fragment;
//	- functii pentru reperul de vizualizare (glm::lookAt) si pentru proiectii.
//
//
//	Biblioteci

#include <windows.h>        //	Utilizarea functiilor de sistem Windows (crearea de ferestre, manipularea fisierelor si directoarelor);
#include <stdlib.h>         //  Biblioteci necesare pentru citirea shaderelor;
#include <stdio.h>
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
#include "SOIL.h"			//	Biblioteca pentru texturare;

//  Identificatorii obiectelor de tip OpenGL;
GLuint
	VaoId,
	VboId,
	EboId,
	ProgramId,
	myMatrixLocation,
	viewLocation,
	projLocation,
	matrRotlLocation,
	codColLocation;
GLuint 
	texture;
//	Dimensiunile ferestrei de afisare;
GLfloat
	winWidth = 1200, winHeight = 900;
//	Variabile catre matricile de transformare;
glm::mat4
	myMatrix, matrRot;

//	Variabila ce determina schimbarea culorii pixelilor in shader;
int codCol;						
//	Valaorea lui pi;
float PI = 3.141592;				
//	Elemente pentru matricea de vizualizare;
float obsX = 0.0, obsY = 0.0, obsZ = 800.f;
float refX = 0.0f, refY = 0.0f;
float vX = 0.0;
glm::mat4 view;
//	Elemente pentru matricea de proiectie;
float width = 800, height = 600, xMin = -800.f, xMax = 800, yMin = -600, yMax = 600, zNear = 0, zFar = 1000, fov = 45;
glm::mat4 projection;

void ProcessNormalKeys(unsigned char key, int x, int y)
{
	switch (key) 
	{
	case 'l':		//	Apasarea tastelor `l` si `r` modifica pozitia verticalei in planul de vizualizare;
		vX += 0.1;
		break;
	case 'r':
		vX -= 0.1;
		break;
	case '+':		//	Apasarea tastelor `+` si `-` schimba pozitia observatorului (se departeaza / aproprie);
		//zNear += 10;
		//zFar += 10;
		obsZ += 10;
		break;
	case '-':
		//zNear -= 10;
		//zFar -= 10;
		obsZ -= 10;
		break;
	}
	if (key == 27)
		exit(0);
}

void ProcessSpecialKeys(int key, int x, int y) {
	switch (key)			//	Procesarea tastelor 'LEFT', 'RIGHT', 'UP', 'DOWN';
	{						//	duce la deplasarea observatorului pe axele Ox si Oy;
	case GLUT_KEY_LEFT:
		obsX -= 20;
		break;
	case GLUT_KEY_RIGHT:
		obsX += 20;
		break;
	case GLUT_KEY_UP:
		obsY += 20;
		break;
	case GLUT_KEY_DOWN:
		obsY -= 20;
		break;
	}
}

//	Functia de incarcare a texturilor in program;
void LoadTexture(const char* texturePath)
{
	// Generarea unui obiect textura si legarea acestuia;
	glGenTextures(1, &texture);
	glBindTexture(GL_TEXTURE_2D, texture);

	//	Desfasurarea imaginii pe orizontala/verticala in functie de parametrii de texturare;
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);

	// Modul in care structura de texeli este aplicata pe cea de pixeli;
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);

	// Incarcarea texturii si transferul datelor in obiectul textura; 
	int width, height;
	unsigned char* image = SOIL_load_image(texturePath, &width, &height, 0, SOIL_LOAD_RGB);
	glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, width, height, 0, GL_RGB, GL_UNSIGNED_BYTE, image);
	glGenerateMipmap(GL_TEXTURE_2D);

	// Eliberarea resurselor
	SOIL_free_image_data(image);
	glBindTexture(GL_TEXTURE_2D, 0);
}

//  Crearea si compilarea obiectelor de tip shader;
//	Trebuie sa fie in acelasi director cu proiectul actual;
//  Shaderul de varfuri / Vertex shader - afecteaza geometria scenei;
//  Shaderul de fragment / Fragment shader - afecteaza culoarea pixelilor;
void CreateShaders(void)
{
	ProgramId = LoadShaders("04_04_Shader.vert", "04_04_Shader.frag");
	glUseProgram(ProgramId);
}

//  Se initializeaza un Vertex Buffer Object (VBO) pentru tranferul datelor spre memoria placii grafice (spre shadere);
//  In acesta se stocheaza date despre varfuri (coordonate, culori, indici, texturare etc.);
void CreateVBO(void)
{

	//	Atributele varfurilor -  COORDONATE, CULORI, COORDONATE DE TEXTURARE;
	GLfloat Vertices[] = {
	//	Coordonate;					Culori;				Coordonate de texturare;
	  -50.0f, -50.0f, 0.0f, 1.0f,	1.0f, 0.0f, 0.0f,	0.0f, 0.0f,	// Stanga jos;
	   50.0f, -50.0f, 0.0f, 1.0f,   0.0f, 1.0f, 0.0f,	1.0f, 0.0f, // Dreapta jos;
	   50.0f,  50.0f, 0.0f, 1.0f,   1.0f, 1.0f, 0.0f,	1.0f, 1.0f,	// Dreapta sus;
	  -50.0f,  50.0f, 0.0f, 1.0f,   0.0f, 1.0f, 1.0f,	0.0f, 1.0f  // Stanga sus;
	};

	//	Indicii care determina ordinea de parcurgere a varfurilor;
	GLuint Indices[] = {
	  0, 1, 2,  //	Primul triunghi;
	  0, 2, 3	//  Al doilea triunghi;
	};

	//  Transmiterea datelor prin buffere;
	
	//  Se creeaza / se leaga un VAO (Vertex Array Object);
	glGenVertexArrays(1, &VaoId);                                                   //  Generarea VAO si indexarea acestuia catre variabila VaoId;
	glBindVertexArray(VaoId);

	//  Se creeaza un buffer pentru VARFURI - COORDONATE, CULORI si TEXTURARE;
	glGenBuffers(1, &VboId);													//  Generarea bufferului si indexarea acestuia catre variabila VboId;
	glBindBuffer(GL_ARRAY_BUFFER, VboId);										//  Setarea tipului de buffer - atributele varfurilor;
	glBufferData(GL_ARRAY_BUFFER, sizeof(Vertices), Vertices, GL_STATIC_DRAW);

	//	Se creeaza un buffer pentru INDICI;
	glGenBuffers(1, &EboId);														//  Generarea bufferului si indexarea acestuia catre variabila EboId;
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EboId);									//  Setarea tipului de buffer - atributele varfurilor;
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(Indices), Indices, GL_STATIC_DRAW);

	//	Se activeaza lucrul cu atribute;
	//  Se asociaza atributul (0 = coordonate) pentru shader;
	glEnableVertexAttribArray(0);
	glVertexAttribPointer(0, 4, GL_FLOAT, GL_FALSE, 9 * sizeof(GLfloat), (GLvoid*)0);
	//  Se asociaza atributul (1 =  culoare) pentru shader;
	glEnableVertexAttribArray(1);
	glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 9 * sizeof(GLfloat), (GLvoid*)(4 * sizeof(GLfloat)));
	//  Se asociaza atributul (2 =  texturare) pentru shader;
	glEnableVertexAttribArray(2);
	glVertexAttribPointer(2, 2, GL_FLOAT, GL_FALSE, 9 * sizeof(GLfloat), (GLvoid*)(7 * sizeof(GLfloat)));
}

//  Elimina obiectele de tip shader dupa rulare;
void DestroyShaders(void)
{
	glDeleteProgram(ProgramId);
}

//  Eliminarea obiectelor de tip VBO dupa rulare;
void DestroyVBO(void)
{
	//  Eliberarea atributelor din shadere (pozitie, culoare, texturare etc.);
	glDisableVertexAttribArray(2);
	glDisableVertexAttribArray(1);
	glDisableVertexAttribArray(0);

	//  Stergerea bufferelor pentru VARFURI (Coordonate, Culori, Textura), INDICI;
	glBindBuffer(GL_ARRAY_BUFFER, 0);
	glDeleteBuffers(1, &VboId);
	glDeleteBuffers(1, &EboId);

	//  Eliberaea obiectelor de tip VAO;
	glBindVertexArray(0);
	glDeleteVertexArrays(1, &VaoId);
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
	glClearColor(1.0f, 1.0f, 1.0f, 1.0f);		//  Culoarea de fond a ecranului;

	//  Trecerea datelor de randare spre bufferul folosit de shadere;
	CreateVBO();

	//	Incarcarea texturii;
	LoadTexture("text_smiley_face.png");

	//  Initializarea shaderelor;
	CreateShaders();							

	//	Instantierea variabilelor uniforme pentru a "comunica" cu shaderele;
	myMatrixLocation = glGetUniformLocation(ProgramId, "myMatrix");
	viewLocation = glGetUniformLocation(ProgramId, "view");
	projLocation = glGetUniformLocation(ProgramId, "projection");
}

//  Functia de desenarea a graficii pe ecran;
void RenderFunction(void)
{
	glClear(GL_COLOR_BUFFER_BIT);			//  Se curata ecranul OpenGL pentru a fi desenat noul continut;

	//	Matrici pentru transformari;
	matrRot = glm::rotate(glm::mat4(1.0f), PI / 8, glm::vec3(0.0, 0.0, 1.0));
	
	//	TRANSFORMARI;
	// 
	//	Pozitia observatorului;
	glm::vec3 obs = glm::vec3(obsX, obsY, obsZ);
	//	Pozitia punctului de referinta;
	refX = obsX; refY = obsY;
	glm::vec3 refPoint = glm::vec3(refX, refY, -1.0f);
	//	Verticala din planul de vizualizare; 
	glm::vec3 vert = glm::vec3(vX, 1.0f, 0.0f);
	// Matricea de vizualizare
	view = glm::lookAt(obs, refPoint, vert);

	//	Realizarea proiectiei;
	projection = glm::perspective(fov, GLfloat(width) / GLfloat(height), zNear, zFar);

	// Matrice generica (initializata ca fiind matricea identica, se pot testa alte valori)
	myMatrix = glm::mat4(1.0f);
	//	myMatrix = matrRot;
 
	//	Transmiterea variabilelor uniforme pentru MATRICEA DE TRANSFORMARE, PERSPECTIVA si PROIECTIE spre shadere;
	glUniformMatrix4fv(myMatrixLocation, 1, GL_FALSE, &myMatrix[0][0]);
	glUniformMatrix4fv(viewLocation, 1, GL_FALSE, &view[0][0]);
	glUniformMatrix4fv(projLocation, 1, GL_FALSE, &projection[0][0]);

	// TEXTURARE
	// 
	// Activarea / legarea texturii active
	glActiveTexture(GL_TEXTURE0);
	glBindTexture(GL_TEXTURE_2D, texture);
	//	Transmiterea variabilei uniforme pentru texturare spre shaderul de fragmente;
	glUniform1i(glGetUniformLocation(ProgramId, "myTexture"), 0);

	//	Desenarea primitivelor;
	//	Functia glDrawElements primeste 4 argumente:
	//	 - arg1 = modul de desenare;
	//	 - arg2 = numarul de varfuri;
	//	 - arg3 = tipul de date al indicilor;
	//	 - arg4 = pointer spre indici (EBO): pozitia de start a indicilor;
	glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, 0);

	glutSwapBuffers();	//	Inlocuieste imaginea deseneata in fereastra cu cea randata; 
	glFlush();			//  Asigura rularea tuturor comenzilor OpenGL apelate anterior;
}

//	Punctul de intrare in program, se ruleaza rutina OpenGL;
int main(int argc, char* argv[])
{
	//  Se initializeaza GLUT si contextul OpenGL si se configureaza fereastra si modul de afisare;

	glutInit(&argc, argv);
	glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGB);					//	Se folosesc 2 buffere (unul pentru afisare si unul pentru randare => animatii cursive) si culori RGB;
	glutInitWindowSize(winWidth, winHeight);						//  Dimensiunea ferestrei;
	glutInitWindowPosition(100, 100);								//  Pozitia initiala a ferestrei;
	glutCreateWindow("Utilizarea texturarii - OpenGL <<nou>>");		//	Creeaza fereastra de vizualizare, indicand numele acesteia;

	//	Se initializeaza GLEW si se verifica suportul de extensii OpenGL modern disponibile pe sistemul gazda;
	//  Trebuie initializat inainte de desenare;

	glewInit();

	Initialize();							//  Setarea parametrilor necesari pentru fereastra de vizualizare; 
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

