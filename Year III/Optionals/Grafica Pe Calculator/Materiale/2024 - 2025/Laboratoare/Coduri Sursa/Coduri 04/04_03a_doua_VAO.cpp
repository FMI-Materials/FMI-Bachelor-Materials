//
// ================================================
// | Grafica pe calculator                        |
// ================================================
// | Laboratorul IV - 04_03a_douaVAO.cpp |
// ======================================
// 
//	Program ce deseneaza un patrat, folosindu-se tehnicile MODERN OpenGL;
//	ELEMENTE DE NOUTATE:
//	 - folosirea a doua VAO pentru a desena doua obiecte diferite (fiecare VAO contine informatiile referitoare la varfurile ce definesc un obiect);
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
	VaoId1,VaoId2,                       // Identificatori pentru cele doua VAO;
	VboId1,VboId2,                       // Fiecare VAO va contine propriile buffere pt. coordonate, culori, indici;
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

//  Se initializeaza Vertex Buffer Objects (VBOs) pentru tranferul datelor spre memoria placii grafice (spre shadere);
//  In acestea se stocheaza date despre varfuri (coordonate, culori, indici, texturare etc.);

// Este creat primul VAO - desenarea unui patrat cu nuante de albastru
void CreateVAO1(void)
{
 
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

	//  Se creeaza / se leaga primul VAO (Vertex Array Object);
	glGenVertexArrays(1, &VaoId1);         //  Generarea VAO si indexarea acestuia catre variabila VaoId1;
	glBindVertexArray(VaoId1);

	// Transmiterea datelor prin buffere
	//  Se creeaza un buffer pentru VARFURI;
	glGenBuffers(1, &VboId1);                                                        //  Generarea bufferului si indexarea acestuia catre variabila VboId1;
	glBindBuffer(GL_ARRAY_BUFFER, VboId1);                                           //  Setarea tipului de buffer - atributele varfurilor;
	glBufferData(GL_ARRAY_BUFFER, sizeof(Vertices1), Vertices1, GL_STATIC_DRAW);      //  Punctele sunt "copiate" in bufferul curent;
	//  Se asociaza atributul (0 = coordonate) pentru shader;
	glEnableVertexAttribArray(0);
	glVertexAttribPointer(0, 4, GL_FLOAT, GL_FALSE, 0, 0);
  
	//  Se creeaza un buffer pentru CULOARE;
	glGenBuffers(1, &ColorBufferId1);
	glBindBuffer(GL_ARRAY_BUFFER, ColorBufferId1);
	glBufferData(GL_ARRAY_BUFFER, sizeof(Colors1), Colors1, GL_STATIC_DRAW);
	//  Se asociaza atributul (1 =  culoare) pentru shader;
	glEnableVertexAttribArray(1);
	glVertexAttribPointer(1, 4, GL_FLOAT, GL_FALSE, 0, 0);
  
	//	Se creeaza un buffer pentru INDICI;
	glGenBuffers(1, &EboId1);														//  Generarea bufferului si indexarea acestuia catre variabila EboId1;
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EboId1);
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(Indices1), Indices1, GL_STATIC_DRAW);
 
}

// Este creat celui de-al doilea VAO - desenarea unui pentagon cu nuante de gri
void CreateVAO2(void)
{

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

	//  Se creeaza / se leaga al doilea VAO (Vertex Array Object);
	glGenVertexArrays(1, &VaoId2);         //  Generarea VAO si indexarea acestuia catre variabila VaoId2;
	glBindVertexArray(VaoId2);
 
	//  Se creeaza un buffer pentru VARFURI;
	glGenBuffers(1, &VboId2);                                                        //  Generarea bufferului si indexarea acestuia catre variabila VboId2;
	glBindBuffer(GL_ARRAY_BUFFER, VboId2);                                           //  Setarea tipului de buffer - atributele varfurilor;
	glBufferData(GL_ARRAY_BUFFER, sizeof(Vertices2), Vertices2, GL_STATIC_DRAW);
	//  Se asociaza atributul (0 = coordonate) pentru shader;
	glEnableVertexAttribArray(0);
	glVertexAttribPointer(0, 4, GL_FLOAT, GL_FALSE, 0, 0);

	//  Se creeaza un buffer pentru CULOARE;
	glGenBuffers(1, &ColorBufferId2);
	glBindBuffer(GL_ARRAY_BUFFER, ColorBufferId2);
	glBufferData(GL_ARRAY_BUFFER, sizeof(Colors2), Colors2, GL_STATIC_DRAW);
	//  Se asociaza atributul (1 =  culoare) pentru shader;
	glEnableVertexAttribArray(1);
	glVertexAttribPointer(1, 4, GL_FLOAT, GL_FALSE, 0, 0);

	//	Se creeaza un buffer pentru INDICI;
	glGenBuffers(1, &EboId2);														//  Generarea bufferului si indexarea acestuia catre variabila EboId2;
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
	glDeleteVertexArrays(1, &VaoId1);
	glDeleteVertexArrays(1, &VaoId2);
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
	CreateVAO1();								
	CreateVAO2();

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
 
	glPointSize(20.0);
	// Prima primitiva (patratul cu nuante de albastru)
	glBindVertexArray(VaoId1);                                             // Este folosit primul VAO;
	glDrawElements(GL_TRIANGLE_FAN, 4, GL_UNSIGNED_INT, (void*)(0));       // Functia de desenare;
	// glDrawElements(GL_POINTS, 5, GL_UNSIGNED_INT, (void*)(0));    
	

	// A doua primitiva (pentagonul cu nuante de gri)
	glBindVertexArray(VaoId2);                                             // Este folosit al doilea VAO;
	glDrawElements(GL_TRIANGLE_FAN, 5, GL_UNSIGNED_INT, (void*)(0));       // Functia de desenare;
	// glDrawElements(GL_LINE_LOOP, 5, GL_UNSIGNED_INT, (void*)(0)); 
	
	// Exercitii: 
	// (i) comentati, pe rand liniile in care este apelat glBindVertexArray() 
	//		si desenati prima primitiva cu tipul de primitiva GL_POINT, iar a doua cu GL_LINE_LOOP
	// (ii) desenati patratul folosind ca tipuri de primitiva GL_TRIANGLES si GL_TRIANGLE_STRIP - matricea Indices1 trebuie modificata in mod adecvat!

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
	glutCreateWindow("Utilizarea a doua VAO (Vertex Array Objects)");		//	Creeaza fereastra de vizualizare, indicand numele acesteia;

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


