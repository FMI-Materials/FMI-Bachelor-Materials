//
// =================================================
// | Grafica pe calculator                          |
// =================================================
// | Laborator VIII - 08_01_stive_matrice.cpp       |
// =================================================
// 
//	Program ce deseneaza doua cuburi ce se deplaseaza.
//  Ambele cuburi se rotesc in jurul axei proprii, unul dintre cuburi se roteste in jurul celuilat
//	ELEMENTE DE NOUTATE:
//   - transformarile de modelare si cea de vizualizare sunt inglobate intr-o singura matrice;
//	 - folosirea stivelor de matrice;
//   - utilizarea timpului scurs de la initializare;
//   - in 08_01_Shader.frag: stabilirea culorii obiectului in functie de pozitia fragmentului
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
#include<stack>


//  Identificatorii obiectelor de tip OpenGL;
GLuint
	VaoId,
	VboId,
	EboId,
	ProgramId,
	viewModelLocation,
	projLocation,
	codColLocation;

//	Valaorea lui pi;
float PI = 3.141592;

//	Dimensiunile ferestrei de afisare;
GLfloat
	winWidth = 1400, winHeight = 600;

//	Variabila ce determina schimbarea culorii pixelilor in shader;
int codCol;

// Variabila pentru timpul scurs
float timeElapsed;

//	Elemente pentru matricea de vizualizare;
float obsX = 0.0, obsY = 0.0, obsZ = 300.f,
refX = 0.0f, refY = 0.0f, refZ = -100.f,
vX = 0.0;
//	Elemente pentru matricea de proiectie;
float xMin = -700.f, xMax = 700.f, yMin = -300.f, yMax = 300.f,
zNear = 100.f, zFar = 500.f,
width = 1400.f, height = 600.f, fov = 90.f * PI / 180;

//	Vectori pentru matricea de vizualizare;
glm::vec3
	obs, pctRef, vert;

//	Variabile catre matricile de transformare;
glm::mat4 
	view, projection,  
	translateSystem, 
	rotateSun, 
	scalePlanet, rotatePlanetAxis, rotatePlanet, translatePlanet;

// Stiva de matrice - inglobeaza matricea de modelare si cea de vizualizare
std::stack<glm::mat4> mvStack;

void ProcessNormalKeys(unsigned char key, int x, int y)
{
	switch (key)
	{
	case 'l':			//	Apasarea tastelor `l` si `r` modifica pozitia verticalei in planul de vizualizare;
		vX += 0.1;
		break;
	case 'r':
		vX -= 0.1;
		break;
	case '+':			//	Apasarea tastelor `+` si `-` schimba pozitia observatorului (se departeaza / aproprie);
		obsZ += 10;
		break;
	case '-':
		obsZ -= 10;
		break;
	}
	if (key == 27)
		exit(0);
}

void ProcessSpecialKeys(int key, int xx, int yy)
{
	switch (key)				//	Procesarea tastelor 'LEFT', 'RIGHT', 'UP', 'DOWN';
	{							//	duce la deplasarea observatorului pe axele Ox si Oy;
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

//  Crearea si compilarea obiectelor de tip shader;
void CreateShaders(void)
{
	ProgramId = LoadShaders("08_01_Shader.vert", "08_01_Shader.frag");
	glUseProgram(ProgramId);
}

//  Se initializeaza un vertex Buffer Object (VBO) pentru tranferul datelor spre memoria placii grafice (spre shadere);
//  In acesta se stocheaza date despre varfuri (coordonate, culori, indici, texturare etc.);
void CreateVBO(void)
{
	//	Atributele varfurilor -  COORDONATE si CULORI;
	GLfloat Vertices[] =
	{
		//	Varfurile VERZI din planul z = -20;  
		//	Coordonate;					Culori;			
		-20.0f, -20.0f, -20.0f,  1.0f,  0.0f, 1.0f, 0.0f,
		 20.0f, -20.0f, -20.0f,  1.0f,  0.0f, 0.9f, 0.0f,
		 20.0f,  20.0f, -20.0f,  1.0f,  0.0f, 0.6f, 0.0f,
		-20.0f,  20.0f, -20.0f,  1.0f,	0.0f, 0.2f, 0.0f,
		//	Varfurile ROSII din planul z = +20;
		//	Coordonate;					Culori;			
		-20.0f, -20.0f,  20.0f,  1.0f,  1.0f, 0.0f, 0.0f,
		 20.0f, -20.0f,  20.0f,  1.0f,  0.7f, 0.0f, 0.0f,
		 20.0f,  20.0f,  20.0f,  1.0f,  0.5f, 0.0f, 0.0f,
		-20.0f,  20.0f,  20.0f,  1.0f,	0.1f, 0.0f, 0.0f,
	};

	//  Indicii pentru varfuri;
	GLubyte Indices[] =
	{
		1, 0, 2,   2, 0, 3, //  Fata "de jos";
		2, 3, 6,   6, 3, 7, //	Lateral;
		7, 3, 4,   4, 3, 0, //	Lateral; 
		4, 0, 5,   5, 0, 1, //	Lateral; 
		1, 2, 5,   5, 2, 6, //	Lateral; 
		5, 6, 4,   4, 6, 7,	//  Fata "de sus";
		0, 1, 2, 3,			//	Contur fata de jos;
		4, 5, 6, 7,			//	Contur fata de sus;
		0, 4,				//	Muchie laterala;
		1, 5,				//	Muchie laterala;
		2, 6,				//	Muchie laterala;
		3, 7				//	Muchie laterala;
	};

	//  Transmiterea datelor prin buffere;

	//  Se creeaza / se leaga un VAO (Vertex Array Object) - util cand se utilizeaza mai multe VBO;
	glGenVertexArrays(1, &VaoId);                                                   //  Generarea VAO si indexarea acestuia catre variabila VaoId;
	glBindVertexArray(VaoId);

	//  Se creeaza un buffer pentru VARFURI - COORDONATE si CULORI;
	glGenBuffers(1, &VboId);														//  Generarea bufferului si indexarea acestuia catre variabila VboId;
	glBindBuffer(GL_ARRAY_BUFFER, VboId);											//  Setarea tipului de buffer - atributele varfurilor;
	glBufferData(GL_ARRAY_BUFFER, sizeof(Vertices), Vertices, GL_STATIC_DRAW);

	//	Se creeaza un buffer pentru INDICI;
	glGenBuffers(1, &EboId);														//  Generarea bufferului si indexarea acestuia catre variabila EboId;
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EboId);									//  Setarea tipului de buffer - atributele varfurilor;
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(Indices), Indices, GL_STATIC_DRAW);

	//	Se activeaza lucrul cu atribute;
	//  Se asociaza atributul (0 = coordonate) pentru shader;
	glEnableVertexAttribArray(0);
	glVertexAttribPointer(0, 4, GL_FLOAT, GL_FALSE, 7 * sizeof(GLfloat), (GLvoid*)0);
	//  Se asociaza atributul (1 =  culoare) pentru shader;
	glEnableVertexAttribArray(1);
	glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 7 * sizeof(GLfloat), (GLvoid*)(4 * sizeof(GLfloat)));
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
	glDisableVertexAttribArray(1);
	glDisableVertexAttribArray(0);

	//  Stergerea bufferelor pentru VARFURI (Coordonate, Culori), INDICI;
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
	CreateVBO();								//  Trecerea datelor de randare spre bufferul folosit de shadere;
	CreateShaders();							//  Initilizarea shaderelor;

	//	Instantierea variabilelor uniforme pentru a "comunica" cu shaderele;
	viewModelLocation = glGetUniformLocation(ProgramId, "viewModel");
	projLocation = glGetUniformLocation(ProgramId, "projection");
	codColLocation = glGetUniformLocation(ProgramId, "codCol");

	//	Realizarea proiectiei - pot fi utilizate si alte variante;
    projection = glm::ortho(xMin, xMax, yMin, yMax, zNear, zFar);
	//	projection = glm::frustum(xMin, xMax, yMin, yMax, zNear, zFar);
	//	projection = glm::perspective(fov, GLfloat(width) / GLfloat(height), zNear, zFar);
	// projection = glm::infinitePerspective(fov, GLfloat(width) / GLfloat(height), zNear); 
	glUniformMatrix4fv(projLocation, 1, GL_FALSE, &projection[0][0]);
}

//	Functia de desenare a graficii pe ecran;
void RenderFunction(void)
{
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);		//  Se curata ecranul OpenGL pentru a fi desenat noul continut (bufferul de culoare & adancime);
	glEnable(GL_DEPTH_TEST);                                //  Activarea testului de adancime

	// Variabila care indica timpul scurs de la initializare
	timeElapsed = glutGet(GLUT_ELAPSED_TIME);

	//	Matricea de vizualizare - actualizare
	//	Pozitia observatorului;
	obs = glm::vec3(obsX, obsY , obsZ);
	//	Pozitia punctului de referinta;
	refX = obsX; refY = obsY;
	pctRef = glm::vec3(refX, refY, refZ);
	//	Verticala din planul de vizualizare; 
	vert = glm::vec3(vX, 1.0f, 0.0f);
	view = glm::lookAt(obs, pctRef, vert);
 
	// Matrice pentru miscarea obiectelor din sistem
	// 
	// Intregul sistem se deplaseaza prin translatie
	translateSystem = glm::translate(glm::mat4(1.0f), glm::vec3(-600+0.01*timeElapsed, 0.0, 0.0));
	
	// Soarele se roteste in jurul propriei axe
	rotateSun = glm::rotate(glm::mat4(1.0f), -(float)0.0001 * timeElapsed, glm::vec3(0.0, 1.0, 0.0));
	
	// Planeta se obtine scaland cubul initial
	scalePlanet = glm::scale(glm::mat4(1.0f), glm::vec3(0.4, 0.4, 0.4));
	// Planeta se roteste in jurul propriei axe
	rotatePlanetAxis = glm::rotate(glm::mat4(1.0f), (float)0.001 * timeElapsed, glm::vec3(0.0, 1.0, 0.0));
	// Planeta se roteste in jurul astrului central
	rotatePlanet = glm::rotate(glm::mat4(1.0f), (float)0.0005 * timeElapsed, glm::vec3(-0.1, 1.0, 0.0));
	// Planeta este translatata in raport cu astrul central
	translatePlanet = glm::translate(glm::mat4(1.0f), glm::vec3(150.0, 0.0, 0.0));
	

	// Desenarea primitivelor + manevrarea stivei de matrice
	// 
	// Matricea de vizualizare este adaugata in varful stivei de matrice
	mvStack.push(view);                  // In varful stivei:   view 

	// 0) Pentru intregul sistem
	// Matrice de translatie pentru intregul sistem
	mvStack.top() *= translateSystem;	 // In varful stivei:  view * translateSystem 
	mvStack.push(mvStack.top());         // Pe poz 2 a stivei: view * translateSystem 

	// 1) Pentru Soare (astrul central)

	// Actualizare a matricei din varful stivei
	// Rotatie in jurul axei proprii
	mvStack.top() *= rotateSun;         // In varful stivei:  view * translateSystem * rotateSun          
	
	// Transmitere matrice de deplasare a Soarelui catre shader, apoi eliminare din varful stivei
	glUniformMatrix4fv(viewModelLocation, 1, GL_FALSE, glm::value_ptr(mvStack.top()));
	mvStack.pop();		                 // In varful stivei:   view * translateSystem 

	//	Desenarea propriu-zisa a obiectului 3D
	codCol = 0;														
	glUniform1i(codColLocation, codCol);								
	glDrawElements(GL_TRIANGLES, 36, GL_UNSIGNED_BYTE, (void*)(0));
	//  Desenarea muchiilor;
	codCol = 1;															
	glUniform1i(codColLocation, codCol);
	glLineWidth(3.5);
	glDrawElements(GL_LINE_LOOP, 4, GL_UNSIGNED_BYTE, (void*)(36));
	glDrawElements(GL_LINE_LOOP, 4, GL_UNSIGNED_BYTE, (void*)(40));
	glDrawElements(GL_LINES, 8, GL_UNSIGNED_BYTE, (void*)(44));


	// 2) Pentru planeta
	
	// Actualizare a matricei din varful stivei
	// Rotatie in jurul Soarelui
	mvStack.top() *= rotatePlanet;		// In varful stivei:  view * translateSystem * rPl
	// Deplasare fata de centrul Soarelui
	mvStack.top() *= translatePlanet;   // In varful stivei:  view * translateSystem * rPl * tPl
	// Rotatie in jurul axei proprii
	mvStack.top() *= rotatePlanetAxis;  // In varful stivei:  view * translateSystem * rPl * tPl * rPlAx
	// Scalare (redimensionare obiect 3D)
	mvStack.top() *= scalePlanet;       // In varful stivei:  view * translateSystem * rPl * tPl * rPlAx * scPl

	// Transmitere matrice de deplasare a planetei catre shader, apoi eliminare din varful stivei
	glUniformMatrix4fv(viewModelLocation, 1, GL_FALSE, glm::value_ptr(mvStack.top()));

	//	Desenarea propriu-zisa a obiectului 3D
	codCol = 2;  //	Regula de colorare este diferita;		 													
	glUniform1i(codColLocation, codCol);								
	glDrawElements(GL_TRIANGLES, 36, GL_UNSIGNED_BYTE, (void*)(0));

	glutSwapBuffers();	//	Inlocuieste imaginea deseneata in fereastra cu cea randata; 
	glFlush();			//  Asigura rularea tuturor comenzilor OpenGL apelate anterior;
}

//	Punctul de intrare in program, se ruleaza rutina OpenGL;
int main(int argc, char* argv[])
{
	//  Se initializeaza GLUT si contextul OpenGL si se configureaza fereastra si modul de afisare;

	glutInit(&argc, argv);
	glutInitDisplayMode(GLUT_RGB | GLUT_DEPTH | GLUT_DOUBLE);		//	Se folosesc 2 buffere pentru desen (unul pentru afisare si unul pentru randare => animatii cursive) si culori RGB + 1 buffer pentru adancime;
	glutInitWindowSize(winWidth, winHeight);						//  Dimensiunea ferestrei;
	glutInitWindowPosition(100, 100);								//  Pozitia initiala a ferestrei;
	glutCreateWindow("Miscare relativa. Utilizarea stivelor de matrice");		//	Creeaza fereastra de vizualizare, indicand numele acesteia;

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
