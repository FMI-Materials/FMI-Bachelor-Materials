//
// ================================================
// | Grafica pe calculator                        |
// ================================================
// | Laboratorul VIII - 08_02a_cerc.cpp |
// =====================================
// 
//	Program ce deseneaza un cerc cu ajutorul reprezentarii parametrice, folosindu-se tehnicile MODERN OpenGL;
//  ELEMENTE DE NOUTATE:
//	 - folosirea functiei ReshapeFunction (relevanta pentru pastrarea proportiilor);
// 
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


const int NR_POINTS = 20;

//  Identificatorii obiectelor de tip OpenGL;
GLuint
	VaoId,
	VboId,
	EboId,
	ColorBufferId,
	ProgramId,
	myMatrixLocation,
	codColLocation;
//	Dimensiunile ferestrei de afisare;
GLint 
	winWidth = 1000, winHeight = 600;
//	Variabile catre matricile de transformare;
glm::mat4
	myMatrix;

//	Variabila ce determina schimbarea culorii pixelilor in shader;
int codCol;
//	Valaorea lui pi;
float const PI = 3.141592;
//	Parametri utilizati pentru pastrarea proportiilor in ReshapeFunction;
float width = winWidth / 10, height = winHeight / 10;
//	Elemente pentru cerc: centru, raza;
float cx = 10.f, cy = 5.f, radius = 20.0;


//  Crearea si compilarea obiectelor de tip shader;
//	Trebuie sa fie in acelasi director cu proiectul actual;
//  Shaderul de varfuri / vertex shader - afecteaza geometria scenei;
//  Shaderul de fragment / Fragment shader - afecteaza culoarea pixelilor;
void CreateShaders(void)
{
	ProgramId = LoadShaders("08_02a_Shader.vert", "08_02a_Shader.frag");
	glUseProgram(ProgramId);
}

//  Se initializeaza un vertex Buffer Object (VBO) pentru tranferul datelor spre memoria placii grafice (spre shadere);
//  In acesta se stocheaza date despre varfuri (coordonate, culori, indici, texturare etc.);
void CreateVBO(void)
{
	glm::vec4 vf_coord[NR_POINTS];
	for (int i = 0; i < NR_POINTS; i++)
	{
		//	Se foloseste reprezentarea parametrica pentru a genera varfurile (puncte situate pe cerc)
		vf_coord[i] =
			glm::vec4(cx + radius * cos(2 * PI * i / NR_POINTS),
				cy + radius * sin(2 * PI * i / NR_POINTS),
				0.0f, 1.0f);
	};
	// Culorile varfurilor
	glm::vec4 vf_col[NR_POINTS];
	for (int i = 0; i < NR_POINTS; i++)
	{
		vf_col[i] = glm::vec4(abs(0.3 * i / NR_POINTS + cos(0.1 * i)), abs(0.4 * i / NR_POINTS + sin(0.01 * i)), abs(0.5 * i / NR_POINTS - sin(0.1 * i)), 1.0f);
	};
	// Indicii
	GLuint vf_ind[NR_POINTS + 1];
	for (int i = 0; i <= NR_POINTS; i++)
		vf_ind[i] = i % NR_POINTS;
	// Se creeaza un buffer nou pentru varfuri
	glGenBuffers(1, &VboId);
	// Buffer pentru indici
	glGenBuffers(1, &EboId);
	// Se creeaza / se leaga un VAO (Vertex Array Object)
	glGenVertexArrays(1, &VaoId);

	// Legare VAO
	glBindVertexArray(VaoId);

	// Buffer-ul este setat ca buffer curent
	glBindBuffer(GL_ARRAY_BUFFER, VboId);

	// Buffer-ul va contine atat coordonatele varfurilor, cat si datele de culoare
	glBufferData(GL_ARRAY_BUFFER, sizeof(vf_coord) + sizeof(vf_col), NULL, GL_STATIC_DRAW);
	glBufferSubData(GL_ARRAY_BUFFER, 0, sizeof(vf_coord), vf_coord);
	glBufferSubData(GL_ARRAY_BUFFER, sizeof(vf_coord), sizeof(vf_col), vf_col);

	// Buffer-ul pentru indici
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EboId);
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(vf_ind), vf_ind, GL_STATIC_DRAW);

	// Se activeaza lucrul cu atribute; atributul 0 = pozitie, atributul 1 = culoare, acestea sunt indicate corect in VBO
	glVertexAttribPointer(0, 4, GL_FLOAT, GL_FALSE, 0, NULL);
	glVertexAttribPointer(1, 4, GL_FLOAT, GL_FALSE, 0, (const GLvoid*)sizeof(vf_coord));
	glEnableVertexAttribArray(0);
	glEnableVertexAttribArray(1);
}

//	Schima inaltimea/latimea scenei in functie de modificarile facute de utilizator ferestrei (redimensionari);
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
	glDeleteBuffers(1, &EboId);
	glDeleteBuffers(1, &ColorBufferId);
	glDeleteBuffers(1, &VboId);

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
	myMatrixLocation = glGetUniformLocation(ProgramId, "myMatrix");
	codColLocation = glGetUniformLocation(ProgramId, "codCol");
}

//	Functia de desenare a graficii pe ecran;
void RenderFunction(void)
{
	glClear(GL_COLOR_BUFFER_BIT);
	myMatrix = glm::ortho(-width, width, -height, height);
	glUniformMatrix4fv(myMatrixLocation, 1, GL_FALSE, &myMatrix[0][0]);
	// Segmentele care unesc punctele
	codCol = 1;
	glUniform1i(codColLocation, codCol);
	glLineWidth(0.8f);
	glDrawElements(GL_LINE_LOOP, NR_POINTS, GL_UNSIGNED_INT, (void*)(0));
	// Desenarea punctelor
	codCol = 0;
	glUniform1i(codColLocation, codCol);
	glPointSize(6.0f);
	glEnable(GL_POINT_SMOOTH);
	glDrawElements(GL_POINTS, NR_POINTS, GL_UNSIGNED_INT, (void*)(0));
	glFlush();
}

//	Punctul de intrare in program, se ruleaza rutina OpenGL;
int main(int argc, char* argv[])
{
	//  Se initializeaza GLUT si contextul OpenGL si se configureaza fereastra si modul de afisare;

	glutInit(&argc, argv);
	glutInitDisplayMode(GLUT_SINGLE | GLUT_RGB);								//	Se foloseste 1 buffere pentru desen si unul culori RGB;
	glutInitWindowSize(winWidth, winHeight);									//  Dimensiunea ferestrei;
	glutInitWindowPosition(100, 100);											//  Pozitia initiala a ferestrei;
	glutCreateWindow("Cerc - reprezentare parametrica - OpenGL <<nou>>");		//	Creeaza fereastra de vizualizare, indicand numele acesteia;

	//	Se initializeaza GLEW si se verifica suportul de extensii OpenGL modern disponibile pe sistemul gazda;
	//  Trebuie initializat inainte de desenare;

	glewInit();

	Initialize();							//  Setarea parametrilor necesari pentru fereastra de vizualizare; 
	glutReshapeFunc(ReshapeFunction);			//	Schima inaltimea/latimea scenei in functie de modificarile facute de utilizator ferestrei (redimensionari);
	glutDisplayFunc(RenderFunction);		//  Desenarea scenei in fereastra;
	glutCloseFunc(Cleanup);					//  Eliberarea resurselor alocate de program;

	//  Bucla principala de procesare a evenimentelor GLUT (functiile care incep cu glut: glutInit etc.) este pornita;
	//  Prelucreaza evenimentele si deseneaza fereastra OpenGL pana cand utilizatorul o inchide;

	glutMainLoop();

	return 0;
}
