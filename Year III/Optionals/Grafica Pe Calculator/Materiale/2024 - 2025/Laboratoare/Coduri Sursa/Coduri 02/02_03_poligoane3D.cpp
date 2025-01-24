//
// ================================================
// | Grafica pe calculator                        |
// ================================================
// | Laboratorul II - 02_03_poligoane3D.cpp |
// ==========================================
//
//	Program ce desenaza 2 patrate din spatiul 3D, unul vazut din fata, iar altul din spate, folosindu-se tehnicile MODERN OpenGL;
//	Utilizarea mouse-ului.
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
#include <iostream>
//  Identificatorii obiectelor de tip OpenGL;
GLuint
	VaoId,
	VboId,
	ColorBufferId,
	ProgramId,
	codColLocation;
//	Dimensiunea ferestrei de afisare;
GLint winWidth = 600, winHeight = 600;
int codCol;

//  Se initializeaza un Vertex Buffer Object (VBO) pentru tranferul datelor spre memoria placii grafice (spre shadere);
//  In acesta se stocheaza date despre varfuri (coordonate, culori, indici, texturare etc.);
void CreateVBO(void)
{
	//  Coordonatele varfurilor;
	GLfloat Vertices[] = {
		//	Patrat "mare"
		 0.5f, -0.5f, 0.0f, 1.0f,
		-0.5f, -0.5f, 0.0f, 1.0f,
		-0.5f, 0.5f, 0.0f, 1.0f,
		 0.5f, 0.5f, 0.0f, 1.0f,
	   //	Patrat "mic"
		 0.3f, 0.3f, 0.0f, 1.0f,
		-0.3f, 0.3f, 0.0f, 1.0f,
		-0.3f, -0.3f, 0.0f, 1.0f,
		 0.3f, -0.3f, 0.0f, 1.0f
	};

	//  Culorile in spectrul RGB ca atribute ale varfurilor;
	GLfloat Colors[] = {
		//	Patrat "mare"
		1.0f, 0.0f, 0.0f, 1.0f,
		0.0f, 1.0f, 0.0f, 1.0f,
		0.0f, 0.0f, 1.0f, 1.0f,
		1.0f, 1.0f, 0.0f, 1.0f,
		//	Patrat "mic"
		1.0f, 1.0f, 0.0f, 1.0f,
		0.0f, 0.0f, 1.0f, 1.0f,
		0.0f, 1.0f, 0.0f, 1.0f,
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
	ProgramId = LoadShaders("02_03_Shader.vert", "02_03_Shader.frag");
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
	CreateShaders();                        //  Initilizarea shaderelor;
	//	Variabilele uniforme sunt folosite pentru a "comunica" cu shaderele;
	codColLocation = glGetUniformLocation(ProgramId, "codColShader"); //	Instantierea variabilei;
	codCol = 0;
	glUniform1i(codColLocation, codCol);
}

void RenderFunction(void)
{
	glClear(GL_COLOR_BUFFER_BIT);			//  Se curata ecranul OpenGL pentru a fi desenat noul continut;
	glLineWidth(10.0);						//  Se seteaza dimensiunea liniilor;

	//	Setarea parametrilor privind fata/spatele poligoanelor
	glPolygonMode(GL_FRONT, GL_FILL);		//	Poligon cu fata => umplere;
	glPolygonMode(GL_BACK, GL_LINE);		//	Poligon cu spatele => contur;
	//  Functia de desenare primeste 3 argumente:
	//  - arg1 = tipul primitivei desenate,
	//  - arg2 = indicele primului punct de desenat din buffer,
	//  - arg3 = numarul de puncte consecutive de desenat;
	// 
 
	//	Patratele sunt desenate folosind GL_TRIANGLE_FAN si GL_QUADS, varfurile au culori diferite
	//  De testat si alte optiuni: GL_POLYGON
	glDrawArrays(GL_TRIANGLE_FAN, 0, 4);
	glDrawArrays(GL_QUADS, 4, 4);
	
	glFlush();       //  Asigura rularea tuturor comenzilor OpenGL apelate anterior;
}

//	Functie ce modifica valoarea unei variabile uniforme in functie de apasarea butoanelor de pe mouse;
void UseMouse(int button, int state, int x, int y)
{
	switch (button) {
	case GLUT_LEFT_BUTTON:			//	CLICK stanga => variabila codCol este 1;
		if (state == GLUT_DOWN)
		{
			codCol = 1;
			glUniform1i(codColLocation, codCol);
		}
		break;
	case GLUT_RIGHT_BUTTON:			//	CLICK dreapta => variabila codCol este 0;
		if (state == GLUT_DOWN)
		{
			codCol = 0;
			glUniform1i(codColLocation, codCol);
		}
		break;
	default:
		break;
	}
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
	glutInitDisplayMode(GLUT_SINGLE | GLUT_RGB);				//	Modul de afisare al ferestrei, se foloseste un singur buffer de afisare si culori RGB;
	glutInitWindowPosition(100, 100);							//  Pozitia initiala a ferestrei;
	glutInitWindowSize(winWidth, winHeight);					//  Dimensiunea ferestrei;
	glutCreateWindow("Poligoane 3D. Functii pentru mouse");			//	Creeaza fereastra de vizualizare, indicand numele acesteia;

	//	Se initializeaza GLEW si se verifica suportul de extensii OpenGL modern disponibile pe sistemul gazda;
	//  Trebuie initializat inainte de desenare;
	glewInit();

	Initialize();                       //  Setarea parametrilor necesari pentru afisare;
	glutDisplayFunc(RenderFunction);    //  Desenarea scenei in fereastra;
	glutMouseFunc(UseMouse);            //  Utilizarea functiei de mouse
	glutCloseFunc(Cleanup);             //  Eliberarea resurselor alocate de program;

	//  Bucla principala de procesare a evenimentelor GLUT (functiile care incep cu glut: glutInit etc.) este pornita;
	//  Prelucreaza evenimentele si deseneaza fereastra OpenGL pana cand utilizatorul o inchide;
	glutMainLoop();

	return 0;
}

