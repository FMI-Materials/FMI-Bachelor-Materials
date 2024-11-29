//
// ================================================
// | Grafica pe calculator                        |
// ================================================
// | Laboratorul IX - 09_02_modele_iluminare.cpp |
// ==============================================
// 
//	Program ce deseneaza un cub care este iluminat de o sursa de lumina, folosindu - se tehnicile MODERN OpenGL;// 
//	Elemente de NOUTATE (modelul de iluminare):
//	 - modul de calcul al normalelor la nivelul:
//		* FETELEOR
//			sau
//		* VARFURILOR
//	 - implementarea modelului de iluminare  se va face in:
//		* in shaderul de FRAGMENT (se utilizeaza shaderele 09_02f*)
//			sau
//		* in shaderul de VARFURI (se utilizeaza shaderele 09_02v*)
//	 - folosirea meniului glutMenu (alegerea dintre cele 4 optiuni mentionate mai sus);
//   - din programul principal sunt transferate in shaderul de varfuri toate informatiile geometrice (coordonate, normale, pozitia observatorului, pozitia sursei de lumina)
//   - are loc trasferul dinspre shderul de varfuri inspre shaderul de fragmente (ulterior efectuarii transformarilor) urmatoarele variabile:
//		* FragPos -> pozitia fragmentului;
//		* Normal -> normala;
//	    * inLightPos -> pozitia sursei de lumina;
//		* inViewPos -> pozitia observatorului;
//   - modelul de iluminare este implementat in shaderul de fragment; 
//
// 
//  
//	Biblioteci
#include <windows.h>        //	Utilizarea functiilor de sistem Windows (crearea de ferestre, manipularea fisierelor si directoarelor);
#include <stdlib.h>         //  Biblioteci necesare pentru citirea shaderelor;
#include <stdio.h>
#include <math.h>			//	Biblioteca pentru calcule matematice;
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
	ProgramIdv,
	ProgramIdf,
	viewLocation,
	projLocation,
	codColLocation,
	depthLocation,
	rendermode,
	l1, l2,
	codCol;
GLint objectColorLoc, lightColorLoc, lightPosLoc, viewPosLoc;

// pentru fereastra de vizualizare 
GLint winWidth = 1200, winHeight = 900;

//	Variabile pentru matricea de vizualizare;
float Obsx = 0.0, Obsy = -600.0, Obsz = 0.f;
float Refx = 0.0f, Refy = 1000.0f, Refz = 0.0f;
float Vx = 0.0, Vy = 0.0, Vz = 1.0;

//	Variabile pentru matricea de proiectie;
float width = 800, height = 600, znear = 0.1, fov = 45;

//	Matrice utilizate;
glm::mat4 view, projection;

//	Identificatori optiuni meniu;
enum {
	Il_Frag, Il_Frag_Av, Il_Vert, Il_Vert_Av
};

//	Meniu pentru selectia optiunilor;
void Menu(int selection)
{
	rendermode = selection;
	glutPostRedisplay();
}

void ProcessNormalKeys(unsigned char key, int x, int y)
{
	switch (key) {			//	Apasarea tastelor `l` si `r` modifica pozitia verticalei in planul de vizualizare;
	case 'l':
		Vx -= 0.1;
		break;
	case 'r':
		Vx += 0.1;
		break;
	case '+':				//	Apasarea tastelor `+` si `-` schimba pozitia observatorului (se departeaza / aproprie);
		Obsy += 10;
		break;
	case '-':
		Obsy -= 10;
		break;
	}
	if (key == 27)
		exit(0);
}

void ProcessSpecialKeys(int key, int xx, int yy)
{
	switch (key)						//	Procesarea tastelor 'LEFT', 'RIGHT', 'UP', 'DOWN';
	{									//	duce la deplasarea observatorului pe axele Ox si Oy;
	case GLUT_KEY_LEFT:
		Obsx -= 20;
		break;
	case GLUT_KEY_RIGHT:
		Obsx += 20;
		break;
	case GLUT_KEY_UP:
		Obsz += 20;
		break;
	case GLUT_KEY_DOWN:
		Obsz -= 20;
		break;
	}
}

//  Crearea si compilarea obiectelor de tip shader;
//	Trebuie sa fie in acelasi director cu proiectul actual;
//  Shaderul de varfuri / vertex shader - afecteaza geometria scenei;
//  Shaderul de fragment / Fragment shader - afecteaza culoarea pixelilor;
void CreateShadersVertex(void)
{
	ProgramIdv = LoadShaders("09_02v_Shader.vert", "09_02v_Shader.frag");
	glUseProgram(ProgramIdv);
}

void CreateShadersFragment(void)
{
	ProgramIdf = LoadShaders("09_02f_Shader.vert", "09_02f_Shader.frag");
	glUseProgram(ProgramIdf);
}

//  Se initializeaza un vertex Buffer Object (VBO) pentru tranferul datelor spre memoria placii grafice (spre shadere);
//  In acesta se stocheaza date despre varfuri (coordonate, culori, indici, texturare etc.);
void CreateVBO(void)
{
	// varfurile 
	GLfloat Vertices[] =
	{
		// inspre Oz'
		  -50.f, -50.f, -50.f,  0.0f,  0.0f, -1.0f,
		   50.f, -50.f, -50.f,  0.0f,  0.0f, -1.0f,
		   50.f,  50.f, -50.f,  0.0f,  0.0f, -1.0f,
		   50.f,  50.f, -50.f,  0.0f,  0.0f, -1.0f,
		  -50.f,  50.f, -50.f,  0.0f,  0.0f, -1.0f,
		  -50.f, -50.f, -50.f,  0.0f,  0.0f, -1.0f,

		  // inspre Oz
		  -50.f, -50.f,  50.f,  0.0f,  0.0f,  1.0f,
		   50.f, -50.f,  50.f,  0.0f,  0.0f,  1.0f,
		   50.f,  50.f,  50.f,  0.0f,  0.0f,  1.0f,
		   50.f,  50.f,  50.f,  0.0f,  0.0f,  1.0f,
		  -50.f,  50.f,  50.f,  0.0f,  0.0f,  1.0f,
		  -50.f, -50.f,  50.f,  0.0f,  0.0f,  1.0f,

		  // inspre Ox'
		  -50.f,  50.f,  50.f, -1.0f,  0.0f,  0.0f,
		  -50.f,  50.f, -50.f, -1.0f,  0.0f,  0.0f,
		  -50.f, -50.f, -50.f, -1.0f,  0.0f,  0.0f,
		  -50.f, -50.f, -50.f, -1.0f,  0.0f,  0.0f,
		  -50.f, -50.f,  50.f, -1.0f,  0.0f,  0.0f,
		  -50.f,  50.f,  50.f, -1.0f,  0.0f,  0.0f,

		  // inspre Ox
		   50.f,  50.f,  50.f,  1.0f,  0.0f,  0.0f,
		   50.f,  50.f, -50.f,  1.0f,  0.0f,  0.0f,
		   50.f, -50.f, -50.f,  1.0f,  0.0f,  0.0f,
		   50.f, -50.f, -50.f,  1.0f,  0.0f,  0.0f,
		   50.f, -50.f,  50.f,  1.0f,  0.0f,  0.0f,
		   50.f,  50.f,  50.f,  1.0f,  0.0f,  0.0f,

		   // inspre Oy'
		  -50.f, -50.f, -50.f,  0.0f, -1.0f,  0.0f,
		   50.f, -50.f, -50.f,  0.0f, -1.0f,  0.0f,
		   50.f, -50.f,  50.f,  0.0f, -1.0f,  0.0f,
		   50.f, -50.f,  50.f,  0.0f, -1.0f,  0.0f,
		  -50.f, -50.f,  50.f,  0.0f, -1.0f,  0.0f,
		  -50.f, -50.f, -50.f,  0.0f, -1.0f,  0.0f,

		  // inspre Oy
		  -50.f,  50.f, -50.f,  0.0f,  1.0f,  0.0f,
		   50.f,  50.f, -50.f,  0.0f,  1.0f,  0.0f,
		   50.f,  50.f,  50.f,  0.0f,  1.0f,  0.0f,
		   50.f,  50.f,  50.f,  0.0f,  1.0f,  0.0f,
		  -50.f,  50.f,  50.f,  0.0f,  1.0f,  0.0f,
		  -50.f,  50.f, -50.f,  0.0f,  1.0f,  0.0f,

		  // Fiecare varf cu normala lui

		  // inspre Oz'
			-50.f, -50.f, -50.f,  -1.0f,  -1.0f, -1.0f,
			 50.f, -50.f, -50.f,  1.0f,  -1.0f, -1.0f,
			 50.f,  50.f, -50.f,  1.0f,  1.0f, -1.0f,
			 50.f,  50.f, -50.f,  1.0f,  1.0f, -1.0f,
			-50.f,  50.f, -50.f,  -1.0f,  1.0f, -1.0f,
			-50.f, -50.f, -50.f,  -1.0f,  -1.0f, -1.0f,

			// inspre Oz
			-50.f, -50.f,  50.f,  -1.0f,  -1.0f,  1.0f,
			 50.f, -50.f,  50.f,  1.0f,  -1.0f,  1.0f,
			 50.f,  50.f,  50.f,  1.0f,  1.0f,  1.0f,
			 50.f,  50.f,  50.f,  1.0f,  1.0f,  1.0f,
			-50.f,  50.f,  50.f,  -1.0f,  1.0f,  1.0f,
			-50.f, -50.f,  50.f,  -1.0f,  -1.0f,  1.0f,

			// inspre Ox'
			-50.f,  50.f,  50.f, -1.0f,  1.0f,  1.0f,
			-50.f,  50.f, -50.f, -1.0f,  1.0f,  -1.0f,
			-50.f, -50.f, -50.f, -1.0f,  -1.0f,  -1.0f,
			-50.f, -50.f, -50.f, -1.0f,  -1.0f,  -1.0f,
			-50.f, -50.f,  50.f, -1.0f,  -1.0f,  1.0f,
			-50.f,  50.f,  50.f, -1.0f,  1.0f,  1.0f,

			// inspre Ox
			 50.f,  50.f,  50.f,  1.0f,  1.0f,  1.0f,
			 50.f,  50.f, -50.f,  1.0f,  1.0f,  -1.0f,
			 50.f, -50.f, -50.f,  1.0f,  -1.0f,  -1.0f,
			 50.f, -50.f, -50.f,  1.0f,  -1.0f,  -1.0f,
			 50.f, -50.f,  50.f,  1.0f,  -1.0f,  1.0f,
			 50.f,  50.f,  50.f,  1.0f,  1.0f,  1.0f,

			 // inspre Oy'
			-50.f, -50.f, -50.f,  -1.0f, -1.0f,  -1.0f,
			 50.f, -50.f, -50.f,  1.0f, -1.0f,  -1.0f,
			 50.f, -50.f,  50.f,  1.0f, -1.0f,  1.0f,
			 50.f, -50.f,  50.f,  1.0f, -1.0f,  1.0f,
			-50.f, -50.f,  50.f,  -1.0f, -1.0f,  1.0f,
			-50.f, -50.f, -50.f,  -1.0f, -1.0f,  -1.0f,

			// inspre Oy
			-50.f,  50.f, -50.f,  -1.0f,  1.0f,  -1.0f,
			 50.f,  50.f, -50.f,  1.0f,  1.0f,  -1.0f,
			 50.f,  50.f,  50.f,  1.0f,  1.0f,  1.0f,
			 50.f,  50.f,  50.f,  1.0f,  1.0f,  1.0f,
			-50.f,  50.f,  50.f,  -1.0f,  1.0f,  1.0f,
			-50.f,  50.f, -50.f,  -1.0f,  1.0f,  -1.0f
	};

	glGenVertexArrays(1, &VaoId);
	glGenBuffers(1, &VboId);
	glBindVertexArray(VaoId);
	glBindBuffer(GL_ARRAY_BUFFER, VboId);
	glBufferData(GL_ARRAY_BUFFER, sizeof(Vertices), Vertices, GL_STATIC_DRAW);

	glEnableVertexAttribArray(0); // atributul 0 = pozitie
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 6 * sizeof(GLfloat), (GLvoid*)0);
	glEnableVertexAttribArray(1); // atributul 1 = normale
	glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 6 * sizeof(GLfloat), (GLvoid*)(3 * sizeof(GLfloat)));
}

//	Schimba inaltimea/latimea scenei in functie de modificarile facute de utilizator ferestrei (redimensionari);
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
	glDeleteProgram(ProgramIdv);
	glDeleteProgram(ProgramIdf);
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
	glClearColor(1.0f, 1.0f, 1.0f, 0.0f); // culoarea de fond a ecranului
	CreateVBO();
	CreateShadersFragment();
	objectColorLoc = glGetUniformLocation(ProgramIdf, "objectColor");
	lightColorLoc = glGetUniformLocation(ProgramIdf, "lightColor");
	lightPosLoc = glGetUniformLocation(ProgramIdf, "lightPos");
	viewPosLoc = glGetUniformLocation(ProgramIdf, "viewPos");
	viewLocation = glGetUniformLocation(ProgramIdf, "view");
	projLocation = glGetUniformLocation(ProgramIdf, "projection");
	CreateShadersVertex();
	objectColorLoc = glGetUniformLocation(ProgramIdv, "objectColor");
	lightColorLoc = glGetUniformLocation(ProgramIdv, "lightColor");
	lightPosLoc = glGetUniformLocation(ProgramIdv, "lightPos");
	viewPosLoc = glGetUniformLocation(ProgramIdv, "viewPos");
	viewLocation = glGetUniformLocation(ProgramIdv, "view");
	projLocation = glGetUniformLocation(ProgramIdv, "projection");
}

//	Functia de desenare a graficii pe ecran;
void RenderFunction(void)
{
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	glEnable(GL_DEPTH_TEST);

	// vizualizare + proiectie
	glm::vec3 Obs = glm::vec3(Obsx, Obsy, Obsz);
	glm::vec3 PctRef = glm::vec3(Refx, Refy, Refz);
	glm::vec3 Vert = glm::vec3(Vx, Vy, Vz);
	view = glm::lookAt(Obs, PctRef, Vert);
	glUniformMatrix4fv(viewLocation, 1, GL_FALSE, &view[0][0]);
	projection = glm::infinitePerspective(fov, GLfloat(width) / GLfloat(height), znear);
	glUniformMatrix4fv(projLocation, 1, GL_FALSE, &projection[0][0]);

	// variabile uniforme pentru iluminare
	glUniform3f(objectColorLoc, 1.0f, 0.5f, 0.4f);
	glUniform3f(lightColorLoc, 1.0f, 1.0f, 1.0f);
	glUniform3f(lightPosLoc, 400.f, -400.f, 400.f);
	glUniform3f(viewPosLoc, Obsx, Obsy, Obsz);
	switch (rendermode)
	{
	// modelul de iluminare implementat in shader-ul de fragment
	case Il_Frag: 
		glUseProgram(ProgramIdf);
		l1 = 0; l2 = 36; // normale pentru fete, sunt folosite varfurile 0-35
		break;
	case Il_Frag_Av: // normale pentru varfuri (mediere), sunt folosite varfurile 36-71
		glUseProgram(ProgramIdf);
		l1 = 36; l2 = 36;
		break;

	// modelul de iluminare implementat in shader-ul de varfuri
	case Il_Vert:
		glUseProgram(ProgramIdv);
		l1 = 0; l2 = 36; // normale pentru fete, sunt folosite varfurile 0-35
		break;
	case Il_Vert_Av:
		glUseProgram(ProgramIdv);
		l1 = 36; l2 = 36; // normale pentru varfuri (mediere), sunt folosite varfurile 36-71
		break;
	};

	// desenare
	glDrawArrays(GL_TRIANGLES, l1, l2);

	glutSwapBuffers();
	glFlush();
}

//	Punctul de intrare in program, se ruleaza rutina OpenGL;
int main(int argc, char* argv[])
{
	//  Se initializeaza GLUT si contextul OpenGL si se configureaza fereastra si modul de afisare;

	glutInit(&argc, argv);
	glutInitDisplayMode(GLUT_RGB | GLUT_DEPTH | GLUT_DOUBLE);		//	Se folosesc 2 buffere pentru desen (unul pentru afisare si unul pentru randare => animatii cursive) si culori RGB + 1 buffer pentru adancime;
	glutInitWindowSize(winWidth, winHeight);						//  Dimensiunea ferestrei;
	glutInitWindowPosition(100, 100);								//  Pozitia initiala a ferestrei;
	glutCreateWindow("Variante model de iluminare - OpenGL <<nou>>");		//	Creeaza fereastra de vizualizare, indicand numele acesteia;

	//	Se initializeaza GLEW si se verifica suportul de extensii OpenGL modern disponibile pe sistemul gazda;
	//  Trebuie initializat inainte de desenare;

	glewInit();

	Initialize();							//  Setarea parametrilor necesari pentru fereastra de vizualizare; 
	glutReshapeFunc(ReshapeFunction);		//	Schimba inaltimea/latimea scenei in functie de modificarile facute de utilizator ferestrei (redimensionari);
	glutDisplayFunc(RenderFunction);		//  Desenarea scenei in fereastra;
	glutIdleFunc(RenderFunction);			//	Asigura rularea continua a randarii;
	glutKeyboardFunc(ProcessNormalKeys);	//	Functii ce proceseaza inputul de la tastatura utilizatorului;
	glutSpecialFunc(ProcessSpecialKeys);
	glutCloseFunc(Cleanup);					//  Eliberarea resurselor alocate de program;

	//	Initializarea meniului - activat prin click dreapta in aplicatie;
	glutCreateMenu(Menu);
	glutAddMenuEntry("Fragment", Il_Frag);
	glutAddMenuEntry("Fragment+Mediere_Normale", Il_Frag_Av);
	glutAddMenuEntry("Varfuri", Il_Vert);
	glutAddMenuEntry("Varfuri+Mediere_Normale", Il_Vert_Av);
	glutAttachMenu(GLUT_RIGHT_BUTTON);


	//  Bucla principala de procesare a evenimentelor GLUT (functiile care incep cu glut: glutInit etc.) este pornita;
	//  Prelucreaza evenimentele si deseneaza fereastra OpenGL pana cand utilizatorul o inchide;

	glutMainLoop();

	return 0;
}
