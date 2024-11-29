//
// ================================================
// | Grafica pe calculator                        |
// ================================================
// | Cursul VI - 06_02_poligoane3D_exemplu2.cpp   |
// ================================================
//
//	Program ce deseneaza patrulatere din spatiul 3D. 
//	
//
//
//  Biblioteci

#include <windows.h>        //	Utilizarea functiilor de sistem Windows (crearea de ferestre, manipularea fisierelor si directoarelor);
#include <stdlib.h>         //  Biblioteci necesare pentru citirea shaderelor;
#include <stdio.h>
#include <math.h>
#include<iostream>
#include <GL/glew.h>        //  Definește prototipurile functiilor OpenGL si constantele necesare pentru programarea OpenGL moderna; 
#include <GL/freeglut.h>    //	Include functii pentru: 
							//	- gestionarea ferestrelor si evenimentelor de tastatura si mouse, 
							//  - desenarea de primitive grafice precum dreptunghiuri, cercuri sau linii, 
							//  - crearea de meniuri si submeniuri;
#include "loadShaders.h"	//	Fisierul care face legatura intre program si shadere

#include "glm/glm.hpp"		//	Bibloteci utilizate pentru transformari grafice;
#include "glm/gtc/matrix_transform.hpp"
#include "glm/gtx/transform.hpp"
#include "glm/gtc/type_ptr.hpp"


//  Identificatorii obiectelor de tip OpenGL;
GLuint
	VaoId,
	VboId,
	EboId,
	ColorBufferId,
	viewLocation,
	projLocation,
	ProgramId;
//	Dimensiunea ferestrei de afisare;
GLint winWidth = 600, winHeight = 600;


//	Parametri pentru matricea glm::lookAt() - vizualizare;
// Observatorul
// (i) Observatorul este situat in fata poligonului
GLfloat Obsx = 13.0, Obsy = 11.0, Obsz = 14.0;      
// (ii) Observatorul este situat in spatele poligonului
// GLfloat Obsx = -7.0, Obsy = -9.0, Obsz = -6.0;     
 
// Punctul de referinta
GLfloat Refx = 3.0, Refy = 1.0, Refz = 4.0;

// Verticala din planul de vizualizare
GLfloat Vx = 8.0, Vy = 0.0, Vz = -8.0;

// Vectori pentru matricea glm::lookAt - vizualizare;
glm::vec3 Obs = glm::vec3(Obsx, Obsy, Obsz);      // Pozitia observatorului
glm::vec3 PctRef = glm::vec3(Refx, Refy, Refz);   // Punctul de referinta (spre care se uita observatorul)
glm::vec3 Vert = glm::vec3(Vx, Vy, Vz);           // Verticala din planul de vizualizare

//	Parametri pentru matricea glm::ortho() - proiectie;
GLfloat xMin = -10.0, yMin = -10.0, xMax = 10.0, yMax = 10.0, dNear = 0.0, dFar = 20.0;

// Matrice de vizualizare / proiectie
glm::mat4 view, projection;

//  Se initializeaza un Vertex Buffer Object (VBO) pentru tranferul datelor spre memoria placii grafice (spre shadere);
//  In acesta se stocheaza date despre varfuri (coordonate, culori, indici, texturare etc.);
void CreateVBO(void)
{
	//  Coordonatele varfurilor;
	GLfloat Vertices[] = {

		 6.0f,  2.0f, 0.0f, 1.0f, // P1
		-4.0f,  4.0f, 8.0f, 1.0f, // P2
		 0.0f,  0.0f, 8.0f, 1.0f, // P3
		 2.0f,  2.0f, 4.0f, 1.0f, // P4
		10.0f, -2.0f, 0.0f, 1.0f  // P5
	};
  
	//  Culorile in spectrul RGB ca atribute ale varfurilor;
	GLfloat Colors[] = {

		1.0f, 0.0f, 0.0f, 1.0f,
		0.0f, 1.0f, 0.0f, 1.0f,
		0.0f, 0.0f, 1.0f, 1.0f,
		1.0f, 1.0f, 0.0f, 1.0f,
		1.0f, 1.0f, 0.0f, 1.0f,
	};

	GLuint Indices[] = {
	  0, 1, 2, 3,  //	Primul patrulater;
	  0, 1, 2, 4   //  Al doilea patrulater;
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

	//	Se creeaza un buffer pentru INDICI;
	glGenBuffers(1, &EboId);														//  Generarea bufferului si indexarea acestuia catre variabila EboId;
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EboId);									//  Setarea tipului de buffer - atributele varfurilor;
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(Indices), Indices, GL_STATIC_DRAW);
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
	glDeleteBuffers(1, &EboId);

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
	ProgramId = LoadShaders("06_01_Shader.vert", "06_01_Shader.frag");
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

	//	Variabilele uniforme (aici matrice) sunt folosite pentru a "comunica" cu shaderele. Indicarea locatiilor
	viewLocation = glGetUniformLocation(ProgramId, "viewShader"); 
	projLocation = glGetUniformLocation(ProgramId, "projShader");

	// Matricele de vizualizare si proiectie sunt de tip variabile uniforme, transmise la shader
	// In acest exemplu pot fi apelate in functia de initializare
	view = glm::lookAt(Obs, PctRef, Vert);
	glUniformMatrix4fv(viewLocation, 1, GL_FALSE, &view[0][0]);
	projection = glm::ortho(xMin, xMax, yMin, yMax, dNear, dFar);
	glUniformMatrix4fv(projLocation, 1, GL_FALSE, &projection[0][0]);
}

void RenderFunction(void)
{

	glClear(GL_COLOR_BUFFER_BIT);			//  Se curata ecranul OpenGL pentru a fi desenat noul continut;
	
	//	Setarea parametrilor privind fata/spatele poligoanelor;
	glPolygonMode(GL_FRONT, GL_FILL);	//	Poligon cu fata => umplere;
	glPolygonMode(GL_BACK, GL_LINE);	//	Poligon cu spatele => contur;
	glLineWidth(6.0);					//  Se seteaza dimensiunea liniilor;
 
	// Desenarea patrulaterului P1P2P3P4 (concav)
	// glDrawElements(GL_QUADS, 4, GL_UNSIGNED_INT, (GLvoid*)(0));
	
	// Desenarea patrulaterului P1P2P3P5 (convex)
	 glDrawElements(GL_QUADS, 4, GL_UNSIGNED_INT, (GLvoid*)(4 * sizeof(GLuint)));
	
	 glutSwapBuffers();
	
	glFlush();       //  Asigura rularea tuturor comenzilor OpenGL apelate anterior;
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
	glutInit(&argc, argv);
	glutInitDisplayMode(GLUT_SINGLE | GLUT_RGB);  //	Modul de afisare al ferestrei, se foloseste un singur buffer de afisare si culori RGB;
	glutInitWindowPosition(100, 100);			  //  Pozitia initiala a ferestrei;
	glutInitWindowSize(winWidth, winHeight);	  //  Dimensiunea ferestrei;
	glutCreateWindow("Fata si spatele poligoanelor in context 3D - curs 6, exemplul 2");			  //	Creeaza fereastra de vizualizare, indicand numele acesteia;

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

