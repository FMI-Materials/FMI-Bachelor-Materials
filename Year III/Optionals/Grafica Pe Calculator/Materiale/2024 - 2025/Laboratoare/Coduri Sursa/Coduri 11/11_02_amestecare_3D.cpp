//
// ================================================
// | Grafica pe calculator                        |
// ================================================
// | Laboratorul XI - 11_02_amestecare3D.cpp |
// ===========================================
// 
//	Program ce deseneaza o piramida ce se intrepatrunde cu un cub, folosindu-se tehnicile MODERN OpenGL;
//	Elemente de NOUTATE:
//	 - folosirea celei de-a 4-a componente din codul RGBA;
//   - utilizarea functiilor specifice pentru amestecare: 
//		* glEnable(GL_BLEND); 
//		* glBlendFunc(GL_SRC_ALPHA, GL_SRC_ALPHA);
//	 - combinarea: 
//		* ordinii de desenare a obiectelor;
//		* testului de adancime;
//		* efectelor de amestecare;
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


using namespace std;
float PI = 3.141592;

GLuint
	VaoId,
	VboId1, VboId2,
	EboId1, EboId2,
	ProgramId,
	myMatrixLocation,
	matrUmbraLocation,
	viewLocation,
	projLocation,
	matrRotlLocation,
	codColLocation,
	lightColorLoc,
	lightPosLoc,
	viewPosLoc,
	codCol;

// elemente pentru matricea de vizualizare si matricea de proiectie
float Obsx, Obsy, Obsz;
float Refx = 0.0f, Refy = 0.0f, Refz = 100.0f;
float Vx = 0.0, Vy = 0.0, Vz = 1.0;
float alpha = 0.0f, beta = 0.0f, dist = 600.0f;
float incr_alpha1 = 0.01f, incr_alpha2 = 0.01f;
float width = 800, height = 600, znear = 0.1, fov = 45;

// sursa de lumina
float xL = 500.f, yL = 0.f, zL = 400.f;

// matrice
glm::mat4 view, projection, matrUmbra;

void processNormalKeys(unsigned char key, int x, int y)
{
	switch (key) {
	case '-':
		dist -= 5.0;
		break;
	case '+':
		dist += 5.0;
		break;
	}
	if (key == 27)
		exit(0);
}
void processSpecialKeys(int key, int xx, int yy)
{
	switch (key)
	{
	case GLUT_KEY_LEFT:
		beta -= 0.01f;
		break;
	case GLUT_KEY_RIGHT:
		beta += 0.01f;
		break;
	case GLUT_KEY_UP:
		alpha += incr_alpha1;
		if (abs(alpha - PI / 2) < 0.05)
		{
			incr_alpha1 = 0.f;
		}
		else
		{
			incr_alpha1 = 0.01f;
		}
		break;
	case GLUT_KEY_DOWN:
		alpha -= incr_alpha2;
		if (abs(alpha + PI / 2) < 0.05)
		{
			incr_alpha2 = 0.f;
		}
		else
		{
			incr_alpha2 = 0.01f;
		}
		break;
	}
}
void CreateVBO(void) // sunt folosite doua buffere
{
	// varfurile pentru cub si "ground" 
	GLfloat Vertices1[] =
	{
		// coordonate                   // culori			    // normale
		-50.0f,  -50.0f, 50.0f, 1.0f,  0.0f, 0.5f, 0.9f, 0.5f,  -1.0f, -1.0f, -1.0f,
		50.0f,  -50.0f,  50.0f, 1.0f,  0.0f, 0.5f, 0.9f, 0.5f,  1.0f, -1.0f, -1.0f,
		50.0f,  50.0f,  50.0f, 1.0f,   0.0f, 0.5f, 0.9f, 0.5f, 1.0f, 1.0f, -1.0f,
		-50.0f,  50.0f, 50.0f, 1.0f,   0.0f, 0.5f, 0.9f, 0.5f, -1.0f, 1.0f, -1.0f,
		-50.0f,  -50.0f, 150.0f, 1.0f,  0.0f, 0.5f, 0.9f, 0.5f, -1.0f, -1.0f, 1.0f,
		50.0f,  -50.0f,  150.0f, 1.0f,  0.0f, 0.5f, 0.9f, 0.5f, 1.0f, -1.0f, 1.0f,
		50.0f,  50.0f,  150.0f, 1.0f,   0.0f, 0.5f, 0.9f, 0.5f, 1.0f, 1.0f, 1.0f,
		-50.0f,  50.0f, 150.0f, 1.0f,   0.0f, 0.5f, 0.9f, 0.5f, -1.0f, 1.0f, 1.0f,
		// 
	   -1000.0f,  -1000.0f, 0.0f, 1.0f,  1.0f, 1.0f, 0.5f, 1.0f,  0.0f, 0.0f, 1.0f,
		1000.0f,  -1000.0f, 0.0f, 1.0f,  1.0f, 1.0f, 0.5f, 1.0f, 0.0f, 0.0f, 1.0f,
		1000.0f,  1000.0f,  0.0f, 1.0f,  1.0f, 1.0f, 0.5f, 1.0f,0.0f, 0.0f, 1.0f,
	   -1000.0f,  1000.0f,  0.0f, 1.0f,  1.0f, 1.0f, 0.5f, 1.0f, 0.0f, 0.0f, 1.0f,
	};
	// indicii pentru varfuri
	GLubyte Indices1[] =
	{
	  1, 2, 0,   2, 0, 3,
	  2, 3, 6,   6, 3, 7,
	  7, 3, 4,   4, 3, 0,
	  4, 0, 5,   5, 0, 1,
	  1, 2, 5,   5, 2, 6,
	  5, 6, 4,   4, 6, 7,
	  9, 10, 8, 10, 8, 11
	};

	// varfurile pentru piramida
	GLfloat Vertices2[] =
	{
		// coordonate                   // culori			     // normale
		-40.0f, -69.28f, 70.0f, 1.0f,    0.1f, 1.0f, 0.2f, 1.0f,  -40.0f, -69.28f, 80.0f,
		40.0f, -69.28f, 70.0f, 1.0f,     0.1f, 1.0f, 0.2f, 1.0f,  40.0f, -69.28f, 80.0f,
		80.0f, 0.0f, 70.0f, 1.0f,        0.1f, 1.0f, 0.2f, 1.0f,  80.0f, 0.0f, 80.0f,
		40.0f, 69.28f, 70.0f, 1.0f,      0.1f, 1.0f, 0.2f, 1.0f,  40.0f, 69.28f, 80.0f,
		-40.0f, 69.28f, 70.0f, 1.0f,     0.1f, 1.0f, 0.2f, 1.0f, -40.0f, 69.28f, 80.0f,
		-80.0f, 0.0f,  70.0f, 1.0f,      0.1f, 1.0f, 0.2f, 1.0f, -80.0f, 0.0f, 80.0f,
		 0.0f, 0.0f, 170.0f, 1.0f,      0.3f, 1.0f, 0.2f, 1.0f,  0.0f, 0.0f, 1.0f,
	};
	// indicii pentru piramida
	GLubyte Indices2[] =
	{
	   0, 1, 6,
	   1, 2, 6,
	   2, 3, 6,
	   3, 4, 6,
	   4, 5, 6,
	   5, 0, 6
	};

	// se creeaza un VAO (Vertex Array Object) - util cand se utilizeaza mai multe VBO
	glGenVertexArrays(1, &VaoId);
	glBindVertexArray(VaoId);
	glGenBuffers(1, &VboId1);
	glGenBuffers(1, &EboId1);
	glGenBuffers(1, &VboId2);
	glGenBuffers(1, &EboId2);

	glBindBuffer(GL_ARRAY_BUFFER, VboId1);
	glBufferData(GL_ARRAY_BUFFER, sizeof(Vertices1), Vertices1, GL_STATIC_DRAW);
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EboId1);
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(Indices1), Indices1, GL_STATIC_DRAW);

	glBindBuffer(GL_ARRAY_BUFFER, VboId2);
	glBufferData(GL_ARRAY_BUFFER, sizeof(Vertices2), Vertices2, GL_STATIC_DRAW);
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EboId2);
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(Indices2), Indices2, GL_STATIC_DRAW);

	// se activeaza atributele
	glEnableVertexAttribArray(0); // atributul 0 = pozitie
	glEnableVertexAttribArray(1); // atributul 1 = culoare
	glEnableVertexAttribArray(2); // atributul 2 = normale
}
void AssociateAttributePointers()
{
	glVertexAttribPointer(0, 4, GL_FLOAT, GL_FALSE, 11 * sizeof(GLfloat), (GLvoid*)0);
	glVertexAttribPointer(1, 4, GL_FLOAT, GL_FALSE, 11 * sizeof(GLfloat), (GLvoid*)(4 * sizeof(GLfloat)));
	glVertexAttribPointer(2, 3, GL_FLOAT, GL_FALSE, 11 * sizeof(GLfloat), (GLvoid*)(8 * sizeof(GLfloat)));
}
void DestroyVBO(void)
{
	glDisableVertexAttribArray(2);
	glDisableVertexAttribArray(1);
	glDisableVertexAttribArray(0);
	glBindBuffer(GL_ARRAY_BUFFER, 0);
	glDeleteBuffers(1, &VboId1);
	glDeleteBuffers(1, &EboId1);
	glDeleteBuffers(1, &VboId2);
	glDeleteBuffers(1, &EboId2);
	glBindVertexArray(0);
	glDeleteVertexArrays(1, &VaoId);
}
void CreateShaders(void)
{
	ProgramId = LoadShaders("11_02_Shader.vert", "11_02_Shader.frag");
	glUseProgram(ProgramId);
}
void DestroyShaders(void)
{
	glDeleteProgram(ProgramId);
}
void Initialize(void)
{
	glClearColor(0.0f, 0.0f, 0.0f, 0.0f); // culoarea de fond a ecranului
	CreateShaders();
	CreateVBO();
	viewLocation = glGetUniformLocation(ProgramId, "view");
	projLocation = glGetUniformLocation(ProgramId, "projection");
	matrUmbraLocation = glGetUniformLocation(ProgramId, "matrUmbra");
	lightColorLoc = glGetUniformLocation(ProgramId, "lightColor");
	lightPosLoc = glGetUniformLocation(ProgramId, "lightPos");
	viewPosLoc = glGetUniformLocation(ProgramId, "viewPos");
	codColLocation = glGetUniformLocation(ProgramId, "codCol");
}
void RenderFunction(void)
{
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	glEnable(GL_DEPTH_TEST);

	// reperul de vizualizare + proiectie
	Obsx = Refx + dist * cos(alpha) * cos(beta);
	Obsy = Refy + dist * cos(alpha) * sin(beta);
	Obsz = Refz + dist * sin(alpha);
	glm::vec3 Obs = glm::vec3(Obsx, Obsy, Obsz);
	glm::vec3 PctRef = glm::vec3(Refx, Refy, Refz);
	glm::vec3 Vert = glm::vec3(Vx, Vy, Vz);
	view = glm::lookAt(Obs, PctRef, Vert);
	glUniformMatrix4fv(viewLocation, 1, GL_FALSE, &view[0][0]);
	projection = glm::infinitePerspective(fov, GLfloat(width) / GLfloat(height), znear);
	glUniformMatrix4fv(projLocation, 1, GL_FALSE, &projection[0][0]);

	// Variabile uniforme pentru iluminare
	glUniform3f(lightColorLoc, 1.0f, 1.0f, 1.0f);
	glUniform3f(lightPosLoc, xL, yL, zL);
	glUniform3f(viewPosLoc, Obsx, Obsy, Obsz);
	// matricea pentru umbra
	float D = -5.f;
	matrUmbra[0][0] = zL + D; matrUmbra[0][1] = 0; matrUmbra[0][2] = 0; matrUmbra[0][3] = 0;
	matrUmbra[1][0] = 0; matrUmbra[1][1] = zL + D; matrUmbra[1][2] = 0; matrUmbra[1][3] = 0;
	matrUmbra[2][0] = -xL; matrUmbra[2][1] = -yL; matrUmbra[2][2] = D; matrUmbra[2][3] = -1;
	matrUmbra[3][0] = -D * xL; matrUmbra[3][1] = -D * yL; matrUmbra[3][2] = -D * zL; matrUmbra[3][3] = zL;
	glUniformMatrix4fv(matrUmbraLocation, 1, GL_FALSE, &matrUmbra[0][0]);

	// desenare obiecte opace
	codCol = 0;
	glUniform1i(codColLocation, codCol);
	// buffer 2
	glBindBuffer(GL_ARRAY_BUFFER, VboId2);
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EboId2);
	AssociateAttributePointers();
	glDrawElements(GL_TRIANGLES, 18, GL_UNSIGNED_BYTE, 0); // piramida
	// buffer 1
	glBindBuffer(GL_ARRAY_BUFFER, VboId1);
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EboId1);
	AssociateAttributePointers();
	glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_BYTE, (void*)(36)); // "ground" 
	codCol = 1;
	glUniform1i(codColLocation, codCol);
	glDrawElements(GL_TRIANGLES, 36, GL_UNSIGNED_BYTE, 0); // umbra 

	// desenare obiecte transparente
	glEnable(GL_BLEND);
	//glDepthMask(GL_FALSE);
	glBlendFunc(GL_SRC_ALPHA, GL_SRC_ALPHA); // de testat alte variante https://www.khronos.org/registry/OpenGL-Refpages/gl4/html/glBlendFunc.xhtml si factori-destinatie: GL_ONE, GL_DST_ALPHA, GL_ONE_MINUS_SRC_ALPHA
	codCol = 0;
	glUniform1i(codColLocation, codCol);
	glDrawElements(GL_TRIANGLES, 36, GL_UNSIGNED_BYTE, 0);  // cubul
	glDepthMask(GL_TRUE);
	glDisable(GL_BLEND);

	glutSwapBuffers();
	glFlush();
}
void Cleanup(void)
{
	DestroyShaders();
	DestroyVBO();
}
int main(int argc, char* argv[])
{
	glutInit(&argc, argv);
	glutInitDisplayMode(GLUT_RGB | GLUT_DEPTH | GLUT_DOUBLE);
	glutInitWindowPosition(100, 100);
	glutInitWindowSize(1200, 900);
	glutCreateWindow("Amestecare in context 3D");
	glewInit();
	Initialize();
	glutIdleFunc(RenderFunction);
	glutDisplayFunc(RenderFunction);
	glutKeyboardFunc(processNormalKeys);
	glutSpecialFunc(processSpecialKeys);
	glutCloseFunc(Cleanup);
	glutMainLoop();
}