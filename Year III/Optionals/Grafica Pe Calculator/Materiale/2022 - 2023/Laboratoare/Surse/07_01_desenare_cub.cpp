/* Desenarea unui cub
- Diverse tipuri de proiectii. 
- Folosirea indexarii pentru a trasa separat fetele si muchiile unui obiect 3D (cub)
- Rolul testului de adancime
*/
#include <windows.h>
#include <stdio.h>
#include <math.h>
#include <iostream>
#include <GL/glew.h>  
#include <GL/freeglut.h>  
#include "loadShaders.h"
#include "glm/glm.hpp"  
#include "glm/gtc/matrix_transform.hpp"
#include "glm/gtx/transform.hpp"
#include "glm/gtc/type_ptr.hpp"
using namespace std;
float const PI = 3.141592;

// identificatori 
GLuint
	VaoId,
	VboId,
	EboId,
	ProgramId,
	viewLocation,
	projLocation,
	codColLocation;

// variabile
int codCol;

// elemente pentru matricea de vizualizare
float Obsx = 0.0, Obsy = 0.0, Obsz = 300.f;
float Refx = 0.0f, Refy = 0.0f, Refz = -100.f;
float Vx = 0.0;

// elemente pentru matricea de proiectie
float
	xwmin = -200.f, xwmax = 200.f, ywmin = -200.f, ywmax = 200.f,
	dnear = 100.f, dfar = 500.f,
	width = 600.f, height = 600.f, fov = 90.f*PI/180;

// vectori
glm::vec3 Obs, PctRef, Vert;

// matrice utilizate
glm::mat4 view, projection;

void processNormalKeys(unsigned char key, int x, int y)
{
	switch (key)
	{
	case 'l':
		Vx += 0.1;
		break;
	case 'r':
		Vx -= 0.1;
		break;
	case '+':
		Obsz += 10;
		break;
	case '-':
		Obsz -= 10;
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
		Obsx -= 20;
		break;
	case GLUT_KEY_RIGHT:
		Obsx += 20;
		break;
	case GLUT_KEY_UP:
		Obsy += 20;
		break;
	case GLUT_KEY_DOWN:
		Obsy -= 20;
		break;
	}
}
void CreateVBO(void)
{
	// varfurile 
	GLfloat Vertices[] =
	{
		// varfurile (~verzi) din planul z=-50  
		// coordonate                   // culori			
		-50.0f,  -50.0f, -50.0f, 1.0f,  0.0f, 1.0f, 0.0f,
		50.0f,  -50.0f,  -50.0f, 1.0f,   0.0f, 0.9f, 0.0f,
		50.0f,  50.0f,  -50.0f, 1.0f,    0.0f, 0.6f, 0.0f,
		-50.0f,  50.0f, -50.0f, 1.0f,   0.0f, 0.2f, 0.0f,
		// varfurile (~rosii) din planul z=+50  
		// coordonate                   // culori			
		-50.0f,  -50.0f, 50.0f, 1.0f,  1.0f, 0.0f, 0.0f,
		50.0f,  -50.0f,  50.0f, 1.0f,   0.7f, 0.0f, 0.0f,
		50.0f,  50.0f,  50.0f, 1.0f,    0.5f, 0.0f, 0.0f,
		-50.0f,  50.0f, 50.0f, 1.0f,   0.1f, 0.0f, 0.0f,
	};

	// indicii pentru varfuri
	GLubyte Indices[] =
	{
		1, 0, 2,   2, 0, 3,  //  Fata "de jos"
		2, 3, 6,   6, 3, 7,  // Lateral 
		7, 3, 4,   4, 3, 0,  // Lateral 
		4, 0, 5,   5, 0, 1,  // Lateral 
		1, 2, 5,   5, 2, 6,  // Lateral 
		5, 6, 4,   4, 6, 7, //  Fata "de sus"
		0, 1, 2, 3,  // Contur fata de jos
		4, 5, 6, 7,  // Contur fata de sus
		0, 4, // Muchie laterala
		1, 5, // Muchie laterala
		2, 6, // Muchie laterala
		3, 7 // Muchie laterala
	};

	// generare VAO/buffere
	glGenBuffers(1, &VboId); // atribute
	glGenBuffers(1, &EboId); // indici

	// legare+"incarcare" buffer
	glBindBuffer(GL_ARRAY_BUFFER, VboId);
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EboId);
	glBufferData(GL_ARRAY_BUFFER, sizeof(Vertices), Vertices, GL_STATIC_DRAW); // "copiere" in bufferul curent
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(Indices), Indices, GL_STATIC_DRAW); // "copiere" indici in bufferul curent

	// se activeaza lucrul cu atribute; 
	glEnableVertexAttribArray(0); // atributul 0 = pozitie
	glVertexAttribPointer(0, 4, GL_FLOAT, GL_FALSE, 7 * sizeof(GLfloat), (GLvoid*)0);
	glEnableVertexAttribArray(1); // atributul 1 = culoare
	glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 7 * sizeof(GLfloat), (GLvoid*)(4 * sizeof(GLfloat)));
}
void DestroyVBO(void)
{
	glDisableVertexAttribArray(1);
	glDisableVertexAttribArray(0);
	glBindBuffer(GL_ARRAY_BUFFER, 0);
	glDeleteBuffers(1, &VboId);
	glDeleteBuffers(1, &EboId);
}
void CreateShaders(void)
{
	ProgramId = LoadShaders("07_01_Shader.vert", "07_01_Shader.frag");
	glUseProgram(ProgramId);
}
void DestroyShaders(void)
{
	glDeleteProgram(ProgramId);
}
void Initialize(void)
{
	glClearColor(1.0f, 1.0f, 1.0f, 0.0f);

	// Creare VBO+shader
	CreateVBO();
	CreateShaders();

	// Locatii ptr shader
	viewLocation = glGetUniformLocation(ProgramId, "viewShader");
	projLocation = glGetUniformLocation(ProgramId, "projectionShader");
	codColLocation = glGetUniformLocation(ProgramId, "codColShader");
}
void RenderFunction(void)
{
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	glEnable(GL_DEPTH_TEST);

	// CreateVBO(); // decomentati acest rand daca este cazul 
	glBindVertexArray(VaoId);
	glBindBuffer(GL_ARRAY_BUFFER, VboId);
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EboId);

	// matricea de vizualizare
	Obs = glm::vec3(Obsx, Obsy, Obsz); // pozitia observatorului	
	Refx = Obsx; Refy = Obsy;
	PctRef = glm::vec3(Refx, Refy, Refz); // pozitia punctului de referinta
	Vert = glm::vec3(Vx, 1.0f, 0.0f); // verticala din planul de vizualizare 
	view = glm::lookAt(Obs, PctRef, Vert);
	glUniformMatrix4fv(viewLocation, 1, GL_FALSE, &view[0][0]);

	// matricea de proiectie, pot fi testate si alte variante
	projection = glm::ortho(xwmin, xwmax, ywmin, ywmax, dnear, dfar);
	// projection = glm::frustum(xwmin, xwmax, ywmin, ywmax, dnear, dfar);
	// projection = glm::perspective(fov, GLfloat(width) / GLfloat(height), dnear, dfar);
	// projection = glm::infinitePerspective(fov, GLfloat(width) / GLfloat(height), dnear); 
	glUniformMatrix4fv(projLocation, 1, GL_FALSE, &projection[0][0]);

	// Fetele
	codCol = 0;
	glUniform1i(codColLocation, codCol);
	glDrawElements(GL_TRIANGLES, 36, GL_UNSIGNED_BYTE, (void*)(0));

	// Muchiile
	codCol = 1;
	glUniform1i(codColLocation, codCol);
	glLineWidth(3.5);
	glDrawElements(GL_LINE_LOOP, 4, GL_UNSIGNED_BYTE, (void*)(36));
	glDrawElements(GL_LINE_LOOP, 4, GL_UNSIGNED_BYTE, (void*)(40));
	glDrawElements(GL_LINES, 8, GL_UNSIGNED_BYTE, (void*)(44));

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
	glutInitWindowSize(600, 600);
	glutCreateWindow("Desenarea unui cub folosind testul de adancime");
	glewInit();
	Initialize();
	glutDisplayFunc(RenderFunction);
	glutIdleFunc(RenderFunction);
	glutKeyboardFunc(processNormalKeys);
	glutSpecialFunc(processSpecialKeys);
	glutCloseFunc(Cleanup);
	glutMainLoop();
}

