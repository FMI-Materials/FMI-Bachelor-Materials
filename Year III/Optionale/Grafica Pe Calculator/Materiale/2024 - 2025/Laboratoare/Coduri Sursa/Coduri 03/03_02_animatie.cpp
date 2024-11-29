//
// ================================================
// | Grafica pe calculator                        |
// ================================================
// | Laboratorul III - 03_02_animatie.cpp |
// ============================================
//
//	Program ce deseneaza un dreptunghi ce se deplaseaza stanga-dreapta si are un patrat ce orbiteaza in jurul sau, folosindu-se tehnicile MODERN OpenGL;
//	ELEMENTE DE NOUTATE:
//	- utilizeaza diverse transformari si compunerea acestora folosind biblioteca glm,
//	- functii pentru utilizarea mouse-ului;
//
//
//	Biblioteci

#include <iostream>			//	Biblioteca necesara pentru afisarea in consola;
#include <windows.h>        //	Utilizarea functiilor de sistem Windows (crearea de ferestre, manipularea fisierelor si directoarelor);
#include <stdlib.h>         //  Biblioteci necesare pentru citirea shaderelor;
#include <stdio.h>
#include <GL/glew.h>        //  Define?te prototipurile functiilor OpenGL si constantele necesare pentru programarea OpenGL moderna; 
#include <GL/freeglut.h>    //	Include functii pentru: 
							//	- gestionarea ferestrelor si evenimentelor de tastatura si mouse, 
							//  - desenarea de primitive grafice precum dreptunghiuri, cercuri sau linii, 
							//  - crearea de meniuri si submeniuri;
#include "loadShaders.h"	//	Fisierul care face legatura intre program si shadere;
#include "glm/glm.hpp"		//	Bibloteci utilizate pentru transformari grafice;
#include "glm/gtc/matrix_transform.hpp"
#include "glm/gtx/transform.hpp"
#include "glm/gtc/type_ptr.hpp"

using namespace std;

//  Identificatorii obiectelor de tip OpenGL;
GLuint
	VaoId,
	VboId,
	ColorBufferId,
	ProgramId,
	myMatrixLocation,
	matrScaleLocation,
	matrTranslLocation,
	matrRotlLocation,
	codColLocation;
//	Dimensiunile ferestrei de afisare;
GLfloat
	winWidth = 800, winHeight = 600;
//	Variabile catre matricile de transformare;
glm::mat4
	myMatrix, resizeMatrix, matrTransl, matrScale1, matrScale2, matrRot, matrDepl;

//	Variabila ce determina schimbarea culorii pixelilor in shader;
int codCol;			
//	Variabile pentru proiectia ortogonala;
float xMin = -450.f, xMax = 450.f, yMin = -300.f, yMax = 300.f;
//	Variabile pentru deplasarea pe axa Ox si pentru rotatie;
float i = 0.0, alpha = 0.0, step=0.3, beta = 0.002, angle = 0;


//	Functie pentru afisarea matricei de transformare;
void DisplayMatrix()
{
	for (int i = 0; i < 4; i++)
	{
		for (int j = 0; j < 4; j++)
			cout << myMatrix[i][j] << "  ";
		cout << endl;
	};
	cout << "\n";
};

//	Schimba sensul animatiei spre dreapta;
void MoveRight(void)
{
	i = i + alpha;
	if (i > 350.0)			//	Se asigura deplasarea stanga-dreapta pe Ox in limitele ecranului,
		alpha = -step;		//	mai intai efectuandu-se deplasarea spre DREAPTA;
	else if (i < -350.0)
		alpha = step;
	angle = angle - beta;	//	Se actualizeaza unghiul de rotatie constant (mentine orbitarea);
	glutPostRedisplay();	//	Forteza redesenarea scenei;
}

//	Schimba sensul animatiei spre stanga;
void MoveLeft(void)
{
	i = i + alpha;
	if (i < -350.0)			//	Se asigura deplasarea stanga-dreapta pe Ox in limitele ecranului,
		alpha = step;		//	mai intai efectuandu-se deplasarea spre STANGA;
	else if (i > 350.0)
		alpha = -step;
	angle = angle + beta;	//	Se actualizeaza unghiul de rotatie constant (mentine orbitarea);
	glutPostRedisplay();	//	Forteza redesenarea scenei;
}

//	Functie ce modifica deplasarea dreptunghiurilor in functie de apasarea butoanelor de pe mouse;
void UseMouse(int button, int state, int x, int y)
{
	switch (button) {
	case GLUT_LEFT_BUTTON:			//	CLICK stanga => dreptunghiurile se misca spre stanga;
		if (state == GLUT_DOWN)
			alpha = -step;
		glutIdleFunc(MoveLeft);
		break;
	case GLUT_RIGHT_BUTTON:			//	CLICK dreapta => dreptunghiurile se misca spre drepta;
		if (state == GLUT_DOWN)
			alpha = step;
		glutIdleFunc(MoveRight);
		break;
	default:
		break;
	}
}

//  Crearea si compilarea obiectelor de tip shader;
//	Trebuie sa fie in acelasi director cu proiectul actual;
//  Shaderul de varfuri / Vertex shader - afecteaza geometria scenei;
//  Shaderul de fragment / Fragment shader - afecteaza culoarea pixelilor;
void CreateShaders(void)
{
	ProgramId = LoadShaders("03_02_Shader.vert", "03_02_Shader.frag");
	glUseProgram(ProgramId);
}

//  Se initializeaza un Vertex Buffer Object (VBO) pentru tranferul datelor spre memoria placii grafice (spre shadere);
//  In acesta se stocheaza date despre varfuri (coordonate, culori, indici, texturare etc.);
void CreateVBO(void)
{
	//  Coordonatele varfurilor;
	GLfloat Vertices[] = {
	//	Varfuri pentru axe;
		-450.0f, 0.0f, 0.0f, 1.0f,
		450.0f,  0.0f, 0.0f, 1.0f,
		0.0f, -300.0f, 0.0f, 1.0f,
		0.0f, 300.0f, 0.0f, 1.0f,
	//	Varfuri pentru dreptunghi;
		-50.0f,  -50.0f, 0.0f, 1.0f,
		50.0f, -50.0f, 0.0f, 1.0f,
		50.0f,  50.0f, 0.0f, 1.0f,
		-50.0f,  50.0f, 0.0f, 1.0f,
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
	glClearColor(1.0f, 1.0f, 1.0f, 0.0f);		//  Culoarea de fond a ecranului;
	CreateVBO();								//  Trecerea datelor de randare spre bufferul folosit de shadere;
	CreateShaders();							//  Initilizarea shaderelor;
	//	Instantierea variabilelor uniforme pentru a "comunica" cu shaderele;
	codColLocation = glGetUniformLocation(ProgramId, "codCol");
	myMatrixLocation = glGetUniformLocation(ProgramId, "myMatrix");
}

//  Functia de desenarea a graficii pe ecran;
void RenderFunction(void)
{
	glClear(GL_COLOR_BUFFER_BIT);			//  Se curata ecranul OpenGL pentru a fi desenat noul continut;
	
	// TO DO: schimbati transformarile (de exemplu deplasarea are loc pe axa Oy sau pe o alta dreapta);
	resizeMatrix = glm::ortho(xMin, xMax, yMin, yMax);							//	"Aducem" scena la "patratul standard" [-1,1]x[-1,1];
	matrTransl = glm::translate(glm::mat4(1.0f), glm::vec3(i, 0.0, 0.0));		//	Se translateaza de-a lungul axei Ox;
	matrDepl = glm::translate(glm::mat4(1.0f), glm::vec3(0, 80.0, 0.0));		//	Se translateaza patratul ROSU fata de patratul ALBASTRU;
	matrScale1 = glm::scale(glm::mat4(1.0f), glm::vec3(1.1, 0.3, 0.0));			//	Se scaleaza coordonatele initiale si se obtine dreptunghiul ALABSTRU;
	matrScale2 = glm::scale(glm::mat4(1.0f), glm::vec3(0.25, 0.25, 0.0));		//	Se scaleaza coordonatele initiale si se obtine patratul ROSU;
	matrRot = glm::rotate(glm::mat4(1.0f), angle, glm::vec3(0.0, 0.0, 1.0));	//	Roatie folosita la deplasarea patratului ROSU;

	//	Desenarea axelor;
	
	//	Matricea de redimensionare (pentru elementele "fixe" - axele);
	myMatrix = resizeMatrix;
	//	Culoarea;
	codCol = 0;
	//	Transmiterea variabilelor uniforme pentru MATRICE DE TRANSFORMARE si COLORARE spre shadere;
	glUniformMatrix4fv(myMatrixLocation, 1, GL_FALSE, &myMatrix[0][0]);
	glUniform1i(codColLocation, codCol);
	//  Functia de desenare primeste 3 argumente:
	//  - arg1 = tipul primitivei desenate,
	//  - arg2 = indicele primului punct de desenat din buffer,
	//  - arg3 = numarul de puncte consecutive de desenat;
	glDrawArrays(GL_LINES, 0, 4);

	//	Desenarea dreptunghiului ALBASTRU;
	
	//	Matricea de transformare pentru dreptunghiul ALBASTRU; 
	myMatrix = resizeMatrix * matrTransl * matrScale1;
	codCol = 1;
	//	Transmiterea variabilelor uniforme pentru MATRICEA DE TRANSFORMARE si COLORARE spre shadere;
	glUniformMatrix4fv(myMatrixLocation, 1, GL_FALSE, &myMatrix[0][0]);
	glUniform1i(codColLocation, codCol);
	glDrawArrays(GL_POLYGON, 4, 4);

	//	Desenarea dreptunghiului ROSU;
	
	//	Matricea de transformare pentru dreptunghiul ROSU; 
	myMatrix = resizeMatrix * matrTransl * matrRot * matrDepl * matrScale2;
	codCol = 2;
	//	Transmiterea variabilelor uniforme pentru MATRICE DE TRANSFORMARE si COLORARE spre shadere;
	glUniformMatrix4fv(myMatrixLocation, 1, GL_FALSE, &myMatrix[0][0]);
	glUniform1i(codColLocation, codCol);
	glDrawArrays(GL_POLYGON, 4, 4);

	glutSwapBuffers();	//	Inlocuieste imaginea deseneata in fereastra cu cea randata; 
	glFlush();	//  Asigura rularea tuturor comenzilor OpenGL apelate anterior;
}

//	Punctul de intrare in program, se ruleaza rutina OpenGL;
int main(int argc, char* argv[])
{
	//  Se initializeaza GLUT si contextul OpenGL si se configureaza fereastra si modul de afisare;

	glutInit(&argc, argv);
	glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGB);					//	Se folosesc 2 buffere (unul pentru afisare si unul pentru randare => animatii cursive) si culori RGB;
	glutInitWindowPosition(100, 100);								//  Pozitia initiala a ferestrei;
	glutInitWindowSize(winWidth, winHeight);									//  Dimensiunea ferestrei;
	glutCreateWindow("Dreptunghi cu satelit - OpenGL <<nou>>");		//	Creeaza fereastra de vizualizare, indicand numele acesteia;

	//	Se initializeaza GLEW si se verifica suportul de extensii OpenGL modern disponibile pe sistemul gazda;
	//  Trebuie initializat inainte de desenare;

	glewInit();
	
	Initialize();						//  Setarea parametrilor necesari pentru fereastra de vizualizare; 
	glutDisplayFunc(RenderFunction);	//  Desenarea scenei in fereastra;
	glutMouseFunc(UseMouse);			//	Activarea utilizarii mouseului;
	glutCloseFunc(Cleanup);				//  Eliberarea resurselor alocate de program;

	//  Bucla principala de procesare a evenimentelor GLUT (functiile care incep cu glut: glutInit etc.) este pornita;
	//  Prelucreaza evenimentele si deseneaza fereastra OpenGL pana cand utilizatorul o inchide;

	glutMainLoop();

	return 0;
}

