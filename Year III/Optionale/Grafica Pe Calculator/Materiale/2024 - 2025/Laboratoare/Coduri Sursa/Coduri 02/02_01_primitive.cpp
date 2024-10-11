//
// ================================================
// | Grafica pe calculator                        |
// ================================================
// | Laboratorul II - 02_01_primitive.cpp |
// ========================================
// 
//  Prezentul cod sursa este adaptat dupa OpenGLBook.com;
//  Program ce deseneaza 6 puncte unite de o linie poligonala, folosidu-se tehnicile MODERN OpenGL;
//
//
//  Biblioteci

#include <windows.h>        //	Utilizarea functiilor de sistem Windows (crearea de ferestre, manipularea fisierelor si directoarelor);
#include <stdlib.h>         //  Biblioteci necesare pentru citirea shaderelor;
#include <stdio.h>
#include <GL/glew.h>        //  Definește prototipurile functiilor OpenGL si constantele necesare pentru programarea OpenGL moderna; 
#include <GL/freeglut.h>    //	Include functii pentru: 
							//	- gestionarea ferestrelor si evenimentelor de tastatura si mouse, 
							//  - desenarea de primitive grafice precum dreptunghiuri, cercuri sau linii, 
							//  - crearea de meniuri si submeniuri;
#include "loadShaders.h"	//	Fisierul care face legatura intre program si shadere;

//  Identificatorii obiectelor de tip OpenGL;
GLuint
	VaoId,
	VboId,
	ColorBufferId,
	ProgramId,
	codColLocation;
//	Dimensiunea ferestrei de vizualizare;
GLint winWidth = 600, winHeight = 400;
//	Variabila ce determina schimbarea culorii pixelilor in shader;
int codCol;		

//  Se initializeaza un Vertex Buffer Object (VBO) pentru transferul datelor spre memoria placii grafice (spre shadere);
//  In acesta se stocheaza date despre varfuri (coordonate, culori, indici, texturare etc.);
void CreateVBO(void)
{
	//  Coordonatele varfurilor;
	GLfloat Vertices[] = {
		-0.2f, -0.2f, 0.0f, 1.0f,
		 0.0f,  0.2f, 0.0f, 1.0f,
		 0.2f, -0.2f, 0.0f, 1.0f,
		-0.8f, -0.8f, 0.0f, 1.0f,
		 0.0f,  0.8f, 0.0f, 1.0f,
		 0.8f, -0.8f, 0.0f, 1.0f
	};

	//  Culorile in spectrul RGB ca atribute ale varfurilor;
	GLfloat Colors[] = {
		1.0f, 0.0f, 0.0f, 1.0f,
		0.0f, 1.0f, 0.0f, 1.0f,
		0.0f, 0.0f, 1.0f, 1.0f,
		1.0f, 0.0f, 0.0f, 1.0f,
		0.0f, 1.0f, 0.0f, 1.0f,
		0.0f, 0.0f, 1.0f, 1.0f
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

//  Crearea si compilarea obiectelor de tip shader;
//	Trebuie sa fie in acelasi director cu proiectul actual;
//  Shaderul de varfuri / Vertex shader - afecteaza geometria scenei;
//  Shaderul de fragment / Fragment shader - afecteaza culoarea pixelilor;
void CreateShaders(void)
{
	ProgramId = LoadShaders("02_01_Shader.vert", "02_01_Shader.frag");
	glUseProgram(ProgramId);
}

//  Elimina obiectele de tip shader dupa rulare;
void DestroyShaders(void)
{
	glDeleteProgram(ProgramId);
}

//  Setarea parametrilor necesari pentru fereastra de vizualizare;
void Initialize(void)
{
	glClearColor(1.0f, 1.0f, 1.0f, 0.0f);   //  Culoarea de fond a ecranului;
	CreateVBO();                            //  Trecerea datelor de randare spre bufferul folosit de shadere;
	CreateShaders();                        //  Initializarea shaderelor;
	//	Variabilele uniforme sunt folosite pentru a "comunica" cu shaderele;
	codColLocation = glGetUniformLocation(ProgramId, "codColShader"); //	Instantierea variabilei;
}

//  Functia de desenarea a graficii pe ecran;
void RenderFunction(void)
{
	glClear(GL_COLOR_BUFFER_BIT);			//  Se curata ecranul OpenGL pentru a fi desenat noul continut;

	//	Desenarea segmentelor folosind modelul Gouraud (Gouraud shading);
	//
	//	In exemplul urmator, culoarea este schimbata prin setarea unui id codCol;
	codCol = 0;
	glUniform1i(codColLocation, codCol);							//	Schimbarea variabilei din shader cu valoarea codCol;
	glLineWidth(5.0);												//  Se seteaza dimensiunea liniilor;
	//  Functia de desenare primeste 3 argumente:
	//  - arg1 = tipul primitivei desenate,
	//  - arg2 = indicele primului punct de desenat din buffer,
	//  - arg3 = numarul de puncte consecutive de desenat;
	glDrawArrays(GL_LINE_STRIP, 0, 6);

	//	Desenarea punctelor cu o singura culoare;
	//
	//	Se atribuie o alta valoare variabilei uniforme;
	codCol = 1;
	glUniform1i(codColLocation, codCol);
	//	Activarea atributului GL_POINT_SMOOTH netezeste marginile punctelor;
	glEnable(GL_POINT_SMOOTH);
	glPointSize(20.0);				  //  Se seteaza dimensiunea punctelor;
	glDrawArrays(GL_POINTS, 0, 6);
	glDisable(GL_POINT_SMOOTH);

	glFlush();                        //  Asigura rularea tuturor comenzilor OpenGL apelate anterior;
}

//  Functia de eliberare a resurselor alocate de program;
void Cleanup(void)
{
	DestroyShaders();
	DestroyVBO();
}

//	Punctul de intrare in program, se ruleaza rutina OpenGL;
int main(int argc, char* argv[])
{
	//  Se initializeaza GLUT si contextul OpenGL si se configureaza fereastra si modul de afisare;

	glutInit(&argc, argv);
	glutInitDisplayMode(GLUT_SINGLE | GLUT_RGB);				//	Modul de afisare al ferestrei, se foloseste un singur buffer de afisare si culori RGB;
	glutInitWindowPosition(100, 100);							//  Pozitia initiala a ferestrei;
	glutInitWindowSize(winWidth, winHeight);					//  Dimensiunea ferestrei;
	glutCreateWindow("Primitive si culori - OpenGL <<nou>>");   //	Creeaza fereastra de vizualizare, indicand numele acesteia;
	
	//	Se initializeaza GLEW si se verifica suportul de extensii OpenGL modern disponibile pe sistemul gazda;
	//  Trebuie initializat inainte de desenare;

	glewInit();	
	
	Initialize();                       //  Setarea parametrilor necesari pentru afisare;
	glutDisplayFunc(RenderFunction);    //  Desenarea scenei in fereastra;
	glutCloseFunc(Cleanup);             //  Eliberarea resurselor alocate de program;

	//  Bucla principala de procesare a evenimentelor GLUT (functiile care incep cu glut: glutInit etc.) este pornita;
	//  Prelucreaza evenimentele si deseneaza fereastra OpenGL pana cand utilizatorul o inchide;

	glutMainLoop();

	return 0;
}

