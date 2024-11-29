//
// ================================================
// | Grafica pe calculator                        |
// ================================================
// | Laboratorul IV - 04_03b_douaVBO.cpp |
// ======================================
// 
//	Program ce deseneaza un patrat, folosindu-se tehnicile MODERN OpenGL;
//	ELEMENTE DE NOUTATE:
//	 - folosirea a doua VBO ale unui singur VAO pentru a desena doua obiecte diferite (fiecare VAO contine informatiile referitoare la varfurile ce definesc un obiect);
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
	VaoId,                               // Identificator pentru VAO
	VboId1,VboId2,                       // Cate doua buffere pt. coordonate, culori, indici;
	ColorBufferId1, ColorBufferId2,
	EboId1,EboId2,
	ProgramId,
	myMatrixLocation;
//	Dimensiunile ferestrei de afisare;
GLfloat
	winWidth = 800, winHeight = 600;
//	Variabile catre matricile de transformare;
glm::mat4
	myMatrix, resizeMatrix;
//	Variabile pentru proiectia ortogonala;
float xMin = -80.f, xMax = 80.f, yMin = -60.f, yMax = 60.f;

//  Crearea si compilarea obiectelor de tip shader;
//	Trebuie sa fie in acelasi director cu proiectul actual;
//  Shaderul de varfuri / Vertex shader - afecteaza geometria scenei;
//  Shaderul de fragment / Fragment shader - afecteaza culoarea pixelilor;
void CreateShaders(void)
{
	ProgramId = LoadShaders("04_02_Shader.vert", "04_02_Shader.frag");
	glUseProgram(ProgramId);
}

//  Se initializeaza VAO-ul care contine cele doua VBO
//  In acesta se stocheaza date despre varfuri (coordonate, culori, indici, texturare etc.);
void CreateVBO(void)
{
 
	//  PRIMUL VBO - corespunde unui patrat cu nuante de albastru
	//  Coordonatele varfurilor;
	static const GLfloat Vertices1[] =
	{
		-55.0f, -35.0f,  0.0f,  1.0f,
		-25.0f, -35.0f,  0.0f,  1.0f,
		-25.0f,  -5.0f,  0.0f,  1.0f,
		-55.0f,  -5.0f,  0.0f,  1.0f
	};

	//	Culorile ca atribute ale varfurilor;
	static const GLfloat Colors1[] =
	{
		0.3f, 0.4f, 0.6f, 1.0f,
		0.3f, 0.4f, 0.8f, 1.0f,
		0.5f, 0.7f, 0.9f, 1.0f,
		0.7f, 0.7f, 0.9f, 1.0f
	};
	
	//	Indicii care determina ordinea de parcurgere a varfurilor;
	static const GLuint Indices1[] =
	{
		0, 1, 2, 3
	};

	//  AL DOILEA VBO - corespunde unui pentagon cu nuante de gri
	//  Coordonatele varfurilor;
	static const GLfloat Vertices2[] =
	{
		 30.0f, 40.0f,  0.0f,  1.0f,
		 10.0f, 20.0f,  0.0f,  1.0f,
		 15.0f, -5.0f,  0.0f,  1.0f,
		 45.0f, -5.0f,  0.0f,  1.0f,
		 50.0f, 20.0f,  0.0f,  1.0f

	};

	//	Culorile ca atribute ale varfurilor;
	static const GLfloat Colors2[] =
	{
		0.5f, 0.5f, 0.5f, 1.0f,
		0.6f, 0.6f, 0.6f, 1.0f,
		0.7f, 0.7f, 0.7f, 1.0f,
		0.9f, 0.9f, 0.9f, 1.0f,
		0.7f, 0.7f, 0.7f, 1.0f
	};

	//	Indicii care determina ordinea de parcurgere a varfurilor;
	static const GLuint Indices2[] =
	{
		3, 4, 0, 1, 2 
	};

	//  Se creeaza / se leaga un VAO (Vertex Array Object) - contine ambele VBO;
	glGenVertexArrays(1, &VaoId);         //  Generarea VAO si indexarea acestuia catre variabila VaoId;
	glBindVertexArray(VaoId);

	// Transmiterea datelor prin buffere
	//  Se creeaza primul buffer pentru VARFURI;
	glGenBuffers(1, &VboId1);                                                        //  Generarea bufferului si indexarea acestuia catre variabila VboId;
	glBindBuffer(GL_ARRAY_BUFFER, VboId1);                                           //  Setarea tipului de buffer - atributele varfurilor;
	glBufferData(GL_ARRAY_BUFFER, sizeof(Vertices1), Vertices1, GL_STATIC_DRAW);      //  Punctele sunt "copiate" in bufferul curent;
	//  Se asociaza atributul (0 = coordonate) pentru shader;
	glEnableVertexAttribArray(0);
	glVertexAttribPointer(0, 4, GL_FLOAT, GL_FALSE, 0, 0);
 
	//  Se creeaza al doilea buffer pentru VARFURI;
	glGenBuffers(1, &VboId2);                                                        //  Generarea bufferului si indexarea acestuia catre variabila VboId;
	glBindBuffer(GL_ARRAY_BUFFER, VboId2);                                           //  Setarea tipului de buffer - atributele varfurilor;
	glBufferData(GL_ARRAY_BUFFER, sizeof(Vertices2), Vertices2, GL_STATIC_DRAW);
	//  Se asociaza atributul (0 = coordonate) pentru shader;
	glEnableVertexAttribArray(0);
	glVertexAttribPointer(0, 4, GL_FLOAT, GL_FALSE, 0, 0);

	//  Se creeaza primul buffer pentru CULOARE;
	glGenBuffers(1, &ColorBufferId1);
	glBindBuffer(GL_ARRAY_BUFFER, ColorBufferId1);
	glBufferData(GL_ARRAY_BUFFER, sizeof(Colors1), Colors1, GL_STATIC_DRAW);
	//  Se asociaza atributul (1 =  culoare) pentru shader;
	glEnableVertexAttribArray(1);
	glVertexAttribPointer(1, 4, GL_FLOAT, GL_FALSE, 0, 0);
 
	//  Se creeaza al doilea buffer pentru CULOARE;
	glGenBuffers(1, &ColorBufferId2);
	glBindBuffer(GL_ARRAY_BUFFER, ColorBufferId2);
	glBufferData(GL_ARRAY_BUFFER, sizeof(Colors2), Colors2, GL_STATIC_DRAW);
	//  Se asociaza atributul (1 =  culoare) pentru shader;
	glEnableVertexAttribArray(1);
	glVertexAttribPointer(1, 4, GL_FLOAT, GL_FALSE, 0, 0);

	//	Se creeaza primul buffer pentru INDICI;
	glGenBuffers(1, &EboId1);														//  Generarea bufferului si indexarea acestuia catre variabila EboId;
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EboId1);
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(Indices1), Indices1, GL_STATIC_DRAW);

	//	Se creeaza al doilea buffer pentru INDICI;
	glGenBuffers(1, &EboId2);														//  Generarea bufferului si indexarea acestuia catre variabila EboId;
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EboId2);
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(Indices2), Indices2, GL_STATIC_DRAW);
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

	//  Stergerea bufferelor pentru VARFURI(Coordonate + Culori), INDICI;
	glBindBuffer(GL_ARRAY_BUFFER, 0);
	glDeleteBuffers(1, &VboId1);
	glDeleteBuffers(1, &ColorBufferId1);
	glDeleteBuffers(1, &EboId1);
	glDeleteBuffers(1, &VboId2);
	glDeleteBuffers(1, &ColorBufferId2);
	glDeleteBuffers(1, &EboId2);

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

	//  Initializarea shaderelor;
	CreateShaders();							
	//	Instantierea variabilelor uniforme pentru a "comunica" cu shaderele;
	myMatrixLocation = glGetUniformLocation(ProgramId, "myMatrix");
	//	Dreptunghiul "decupat"; 
	resizeMatrix = glm::ortho(xMin, xMax, yMin, yMax);
}

//  Functia de desenarea a graficii pe ecran;
void RenderFunction(void)
{
	glClear(GL_COLOR_BUFFER_BIT);			//  Se curata ecranul OpenGL pentru a fi desenat noul continut;
	//	Transmiterea variabilei uniforme pentru MATRICEA DE TRANSFORMARE spre shadere;
	myMatrix = resizeMatrix;
	glUniformMatrix4fv(myMatrixLocation, 1, GL_FALSE, &myMatrix[0][0]);
	//	Desenarea primitivelor
 

	// Prima primitiva (patratul cu nuante de albastru)
	// 
	// Sunt "legate" bufferele pentru primul VBO (coordonate, culori, indici). La coordonate si culori este asociat vertex attribute-ul corespunzator
	// Coordonate
	glBindBuffer(GL_ARRAY_BUFFER, VboId1);
	glVertexAttribPointer(0, 4, GL_FLOAT, GL_FALSE, 0, 0);
	// Culori
	glBindBuffer(GL_ARRAY_BUFFER, ColorBufferId1);
	glVertexAttribPointer(1, 4, GL_FLOAT, GL_FALSE, 0, 0);
	// Indici
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EboId1);
	// Functia de desenare propriu-zisa
	glDrawElements(GL_TRIANGLE_FAN, 4, GL_UNSIGNED_INT, (void*)(0));


	// A doua primitiva (pentagonul cu nuante de gri)
	// 
	// Sunt "legate" bufferele pentru al doilea VBO (coordonate, culori, indici). La coordonate si culori este asociat vertex attribute-ul corespunzator
	// Coordonate
	glBindBuffer(GL_ARRAY_BUFFER, VboId2);
	glVertexAttribPointer(0, 4, GL_FLOAT, GL_FALSE, 0, 0);
	// Culori
	glBindBuffer(GL_ARRAY_BUFFER, ColorBufferId2);
    glVertexAttribPointer(1, 4, GL_FLOAT, GL_FALSE, 0, 0);
	// Indici
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EboId2);
	// Functia de desenare propriu-zisa
	glDrawElements(GL_TRIANGLE_FAN, 5, GL_UNSIGNED_INT, (void*)(0));
	
	glFlush();								//  Asigura rularea tuturor comenzilor OpenGL apelate anterior;
}

//	Punctul de intrare in program, se ruleaza rutina OpenGL;
int main(int argc, char* argv[])
{
	//  Se initializeaza GLUT si contextul OpenGL si se configureaza fereastra si modul de afisare;

	glutInit(&argc, argv);
	glutInitDisplayMode(GLUT_SINGLE | GLUT_RGB);					//	Modul de afisare al ferestrei, se foloseste un singur buffer de afisare si culori RGB;
	glutInitWindowSize(winWidth, winHeight);						//  Dimensiunea ferestrei;
	glutInitWindowPosition(100, 100);								//  Pozitia initiala a ferestrei;
	glutCreateWindow("Utilizarea a doua VBO (Vertex Buffer Objects)");		//	Creeaza fereastra de vizualizare, indicand numele acesteia;

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


