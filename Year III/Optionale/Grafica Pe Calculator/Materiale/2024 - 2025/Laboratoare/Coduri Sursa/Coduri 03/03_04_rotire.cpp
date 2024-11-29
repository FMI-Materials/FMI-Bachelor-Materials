//
// ================================================
// | Grafica pe calculator                        |
// ================================================
// | Laboratorul III - 03_04_rotire.cpp |
// ======================================
// 
//	Program care utilizeaza compunerea transformarilor si rotatia cu un centru diferit de origine;
//	Se vor desena un patrat si rotatia sa, folosindu-se tehnicile MODERN OpenGL;
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

//  Identificatorii obiectelor de tip OpenGL;
GLuint
	VaoId,
	VboId,
	ColorBufferId,
	ProgramId,
	myMatrixLocation,
	matrRotlLocation,
	codColLocation;
//	Dimensiunile ferestrei de afisare;
GLfloat
	winWidth = 800, winHeight = 600;
//	Variabile catre matricile de transformare;
glm::mat4 
	myMatrix, resizeMatrix, matrTransl1, matrTransl2, matrRot;

int codCol;							//	Variabila ce determina schimbarea culorii pixelilor in shader;
float PI = 3.141592;				//	Valoarea lui PI;
float xMin = -400.f, xMax = 400.f, yMin = -300.f, yMax = 300.f;		//	Variabile pentru proiectia ortogonala;


//  Crearea si compilarea obiectelor de tip shader;
//	Trebuie sa fie in acelasi director cu proiectul actual;
//  Shaderul de varfuri / Vertex shader - afecteaza geometria scenei;
//  Shaderul de fragment / Fragment shader - afecteaza culoarea pixelilor;
void CreateShaders(void)
{
	ProgramId = LoadShaders("03_04_Shader.vert", "03_04_Shader.frag");
	glUseProgram(ProgramId);
}

//  Se initializeaza un Vertex Buffer Object (VBO) pentru tranferul datelor spre memoria placii grafice (spre shadere);
//  In acesta se stocheaza date despre varfuri (coordonate, culori, indici, texturare etc.);
void CreateVBO(void)
{
	//  Coordonatele varfurilor;
	GLfloat Vertices[] = {
		//  Varfuri pentru axe;
		-400.0f, 0.0f, 0.0f, 1.0f,
		400.0f,  0.0f, 0.0f, 1.0f,
		0.0f, -300.0f, 0.0f, 1.0f,
		0.0f, 300.0f, 0.0f, 1.0f,
	   //  Varfuri pentru dreptunghi;
		50.0f,  50.0f, 0.0f, 1.0f,
		50.0f, 150.0f, 0.0f, 1.0f,
		150.0f,  150.0f, 0.0f, 1.0f,
		150.0f,  50.0f, 0.0f, 1.0f,
	};

	//  Culorile axelor;
	GLfloat Colors[] = {
		1.0f, 0.0f, 0.0f, 1.0f,
		0.0f, 1.0f, 0.0f, 1.0f,
		0.0f, 0.0f, 1.0f, 1.0f,
		1.0f, 0.0f, 0.0f, 1.0f,
	};

	//  Transmiterea datelor prin buffere;

	//  Se creeaza / se leaga un VAO (Vertex Array Object) - util cand se utilizeaza mai multe VBO;
	glGenVertexArrays(1, &VaoId);                                                   //  Generarea VAO si indexarea acestuia catre variabila VaoId;
	glBindVertexArray(VaoId);

	//  Se creeaza un buffer pentru VARFURI;
	glGenBuffers(1, &VboId);                                                        //  Generarea bufferului si indexarea acestuia catre variabila VboId;
	glBindBuffer(GL_ARRAY_BUFFER, VboId);                                           //  Setarea tipului de buffer - atributele varfurilor;
	glBufferData(GL_ARRAY_BUFFER, sizeof(Vertices), Vertices, GL_STATIC_DRAW);      //  Punctele sunt "copiate" in bufferul curent;
	//  Se asociaza atributul (0 = coordonate) pentru shader;
	glEnableVertexAttribArray(0);
	glVertexAttribPointer(0, 4, GL_FLOAT, GL_FALSE, 0, 0);

	//  Se creeaza un buffer pentru CULOARE;
	glGenBuffers(1, &ColorBufferId);
	glBindBuffer(GL_ARRAY_BUFFER, ColorBufferId);
	glBufferData(GL_ARRAY_BUFFER, sizeof(Colors), Colors, GL_STATIC_DRAW);
	//  Se asociaza atributul (1 =  culoare) pentru shader;
	glEnableVertexAttribArray(1);
	glVertexAttribPointer(1, 4, GL_FLOAT, GL_FALSE, 0, 0);
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

	//  Stergerea bufferelor pentru varfuri, culori;
	glBindBuffer(GL_ARRAY_BUFFER, 0);
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
	codColLocation = glGetUniformLocation(ProgramId, "codCol");
	myMatrixLocation = glGetUniformLocation(ProgramId, "myMatrix");

	//	Dreptunghiul "decupat"; 
	resizeMatrix = glm::ortho(xMin, xMax, yMin, yMax);

	//	Matricele de rotatie si de translatie; 
	//	Rotatie cu unghiul angle
	GLfloat angle = PI / 8; 
	matrRot = glm::rotate(glm::mat4(1.0f), angle, glm::vec3(0.0, 0.0, 1.0));
	//	Translatia 1: centrul patratului este translatat in origine;
	matrTransl1 = glm::translate(glm::mat4(1.0f), glm::vec3(-100.f, -100.f, 0.0));
	//	Translatia 2: inversa/opusa translatiei T1;
	matrTransl2 = glm::translate(glm::mat4(1.0f), glm::vec3(100.f, 100.f, 0.0));
}

//  Functia de desenarea a graficii pe ecran;
void RenderFunction(void)
{
	glClear(GL_COLOR_BUFFER_BIT);			//  Se curata ecranul OpenGL pentru a fi desenat noul continut;

	//	Matrice pentru elemente "fixe" - axe;
	//	Transmiterea variabilei uniforme pentru MATRICEA DE TRANSFORMARE spre shadere;
	myMatrix = resizeMatrix;
	glUniformMatrix4fv(myMatrixLocation, 1, GL_FALSE, &myMatrix[0][0]);

	//	Desenarea axelor;
	codCol = 0;									//  Culoarea;
	glUniform1i(codColLocation, codCol);		//	Transmiterea variabilei uniforme pentru COLORARE spre shadere;
	glLineWidth(1.0);							//  Se seteaza dimensiunea liniilor;
	//  Functia de desenare primeste 3 argumente:
	//  - arg1 = tipul primitivei desenate,
	//  - arg2 = indicele primului punct de desenat din buffer,
	//  - arg3 = numarul de puncte consecutive de desenat;
	glDrawArrays(GL_LINES, 0, 4);

	//	Desenarea dreptunghiului initial;
	codCol = 1;									//	Culoare;
	glUniform1i(codColLocation, codCol);
	glLineWidth(2.0);
	glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);
	glDrawArrays(GL_QUADS, 4, 4);

	//	Desenarea dreptunghiului desenat;
	//	Matricea pentru rotire cand poligonul nu are centrul in origine:
	//	- se translateaza in origine,
	//	- se roteste,
	//	- se translateaza inapoi in pozitia initiala;
	//	Transmiterea variabilelor uniforme pentru MATRICEA DE TRANSFORMARE si COLORARE spre shadere;
	codCol = 2;
	myMatrix = resizeMatrix * matrTransl2 * matrRot * matrTransl1;
	glUniformMatrix4fv(myMatrixLocation, 1, GL_FALSE, &myMatrix[0][0]);
	glUniform1i(codColLocation, codCol);
	//	Desenarea primitivei;
	glLineWidth(4.0);
	glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);
	glDrawArrays(GL_QUADS, 4, 4);

	glFlush();	//  Asigura rularea tuturor comenzilor OpenGL apelate anterior;
}

//	Punctul de intrare in program, se ruleaza rutina OpenGL;
int main(int argc, char* argv[])
{
	//  Se initializeaza GLUT si contextul OpenGL si se configureaza fereastra si modul de afisare;

	glutInit(&argc, argv);
	glutInitDisplayMode(GLUT_SINGLE | GLUT_RGB);					//	Modul de afisare al ferestrei, se foloseste un singur buffer de afisare si culori RGB;
	glutInitWindowSize(winWidth, winHeight);						//  Dimensiunea ferestrei;
	glutInitWindowPosition(100, 100);								//  Pozitia initiala a ferestrei;
	glutCreateWindow("Rotirea unui patrat in jurul centrului sau - OpenGL <<nou>>");		//	Creeaza fereastra de vizualizare, indicand numele acesteia;

	//	Se initializeaza GLEW si se verifica suportul de extensii OpenGL modern disponibile pe sistemul gazda;
	//  Trebuie initializat inainte de desenare;

	glewInit();

	Initialize();						//  Setarea parametrilor necesari pentru fereastra de vizualizare; 
	glutDisplayFunc(RenderFunction);	//  Desenarea scenei in fereastra;
	glutCloseFunc(Cleanup);				//  Eliberarea resurselor alocate de program;

	//  Bucla principala de procesare a evenimentelor GLUT (functiile care incep cu glut: glutInit etc.) este pornita;
	//  Prelucreaza evenimentele si deseneaza fereastra OpenGL pana cand utilizatorul o inchide;

	glutMainLoop();

	return 0;
}


