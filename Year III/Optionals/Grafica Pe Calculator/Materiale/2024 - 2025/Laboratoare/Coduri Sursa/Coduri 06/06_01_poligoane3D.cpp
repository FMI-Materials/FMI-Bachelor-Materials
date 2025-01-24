//
// ================================================
// | Grafica pe calculator                        |
// ================================================
// | Cursul VI - 06_01_poligoane3D.cpp       |
// ==========================================
//
//	Program ce deseneaza 2 patrate din spatiul 3D, unul vazut din fata, iar altul din spate, folosindu-se tehnicile MODERN OpenGL;
//	
//
//
//  Biblioteci

#include <windows.h>        //	Utilizarea functiilor de sistem Windows (crearea de ferestre, manipularea fisierelor si directoarelor);
#include <stdlib.h>         //  Biblioteci necesare pentru citirea shaderelor;
#include <stdio.h>
#include <math.h>

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
	ColorBufferId,
	viewLocation,
	projLocation,
	ProgramId;
//	Dimensiunea ferestrei de afisare;
GLint winWidth = 600, winHeight = 600;


//	Parametri pentru matricea glm::lookAt() - vizualizare;
GLfloat Obsx = 0.0, Obsy = 0.0, Obsz = 0.0;
GLfloat Refx = 0.0, Refy = 0.0, Refz = 40.0;
GLfloat Vx = 0.0, Vy = 1.0, Vz = 0.0;

// Vectori pentru matricea glm::lookAt - vizualizare;
glm::vec3 Obs = glm::vec3(Obsx, Obsy, Obsz);      // Pozitia observatorului
glm::vec3 PctRef = glm::vec3(Refx, Refy, Refz);   // Punctul de referinta (spre care se uita observatorul)
glm::vec3 Vert = glm::vec3(Vx, Vy, Vz);           // Verticala din planul de vizualizare

//	Parametri pentru matricea glm::ortho() - proiectie;
GLfloat xMin = -20.0, yMin = -20.0, xMax = 20.0, yMax = 20.0, dNear = 0.0, dFar = 60.0;

// Matrice de vizualizare / proiectie
glm::mat4 view, projection;

//  Se initializeaza un Vertex Buffer Object (VBO) pentru tranferul datelor spre memoria placii grafice (spre shadere);
//  In acesta se stocheaza date despre varfuri (coordonate, culori, indici, texturare etc.);
void CreateVBO(void)
{
	//  Coordonatele varfurilor;
	GLfloat Vertices[] = {

		//	Patrat "mare" situat in planul z=5
		 5.0f, -5.0f, 5.0f, 1.0f,
		-5.0f, -5.0f, 5.0f, 1.0f,
		-5.0f,  5.0f, 5.0f, 1.0f,
		 5.0f,  5.0f, 5.0f, 1.0f,

	   //	Patrat "mic" situat in planul z=10
		 3.0f,  3.0f, 10.0f, 1.0f,
		-3.0f,  3.0f, 10.0f, 1.0f,
		-3.0f, -3.0f, 10.0f, 1.0f,
		 3.0f, -3.0f, 10.0f, 1.0f
	};
  
	//  Culorile in spectrul RGB ca atribute ale varfurilor;
	GLfloat Colors[] = {
		//	Patratul "mare" din planul z=5 este rosu
		1.0f, 0.0f, 0.0f, 1.0f,
		1.0f, 0.0f, 0.0f, 1.0f,
		1.0f, 0.0f, 0.0f, 1.0f,
		1.0f, 0.0f, 0.0f, 1.0f,

		//	Patratul "mic" din planul z=10 este albastru
		0.0f, 0.0f, 1.0f, 1.0f,
		0.0f, 0.0f, 1.0f, 1.0f,
		0.0f, 0.0f, 1.0f, 1.0f,
		0.0f, 0.0f, 1.0f, 1.0f,
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
	ProgramId = LoadShaders("06_01_Shader.vert", "06_01_Shader.frag");
	glUseProgram(ProgramId);
}

//  Elimina obiectele de tip shader dupa rulare;
void DestroyShaders(void)
{
	glDeleteProgram(ProgramId);
}

//  Setarea parametrilor necesari pentru fereastra de vizualizare;
//	Nu sunt indicati parametri pentru vizualizare / decupare, fiind selectate valorile implicite;
void Initialize(void)
{
	glClearColor(1.0f, 1.0f, 1.0f, 0.0f);   //  Culoarea de fond a ecranului;
	CreateVBO();                            //  Trecerea datelor de randare spre bufferul folosit de shadere;
	CreateShaders();                        //  Initializarea shaderelor;

	//	Variabilele uniforme (aici matrice) sunt folosite pentru a "comunica" cu shaderele. Indicarea locatiilor
	viewLocation = glGetUniformLocation(ProgramId, "viewShader"); 
	projLocation = glGetUniformLocation(ProgramId, "projShader");
}

void RenderFunction(void)
{

	glClear(GL_COLOR_BUFFER_BIT);			//  Se curata ecranul OpenGL pentru a fi desenat noul continut;
	glLineWidth(4.0);						//  Se seteaza dimensiunea liniilor;

	// Matricele de vizualizare si proiectie sunt de tip variabile uniforme, transmise la shader
	view = glm::lookAt(Obs, PctRef, Vert);
	glUniformMatrix4fv(viewLocation, 1, GL_FALSE, &view[0][0]);
	projection = glm::ortho(xMin, xMax, yMin, yMax, dNear, dFar);
	glUniformMatrix4fv(projLocation, 1, GL_FALSE, &projection[0][0]);
 
	//	Setarea parametrilor privind fata/spatele poligoanelor
	glPolygonMode(GL_FRONT, GL_FILL);		//	Poligon cu fata => umplere;
	glPolygonMode(GL_BACK, GL_LINE);		//	Poligon cu spatele => contur;
	//  Functia de desenare primeste 3 argumente:
	//  - arg1 = tipul primitivei desenate,
	//  - arg2 = indicele primului punct de desenat din buffer,
	//  - arg3 = numarul de puncte consecutive de desenat;
	 
	//	Desenarea patratului rosu (cu latura 10) la z = 5; Acest patrat este vazut din fata
	glDrawArrays(GL_QUADS, 0, 4);

	//	Desenarea patratului albastru (cu latura 5) la z = 10; Acest patrat este vazut din spate
	glDrawArrays(GL_QUADS, 4, 4);
	
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
	glutCreateWindow("Fata si spatele poligoanelor in context 3D - curs 6, exemplul 1");			  //	Creeaza fereastra de vizualizare, indicand numele acesteia;

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

