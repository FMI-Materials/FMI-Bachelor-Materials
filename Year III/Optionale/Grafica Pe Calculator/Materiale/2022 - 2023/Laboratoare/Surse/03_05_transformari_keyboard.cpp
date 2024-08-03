/* TRANSFORMARI.
Realizarea unei scene 2D in care obiectele se misca
   - unele primitive raman fixe, altele isi schimba pozitia
   - functii pentru tastatura: processNormalKeys, processSpecialKeys
   - pentru animatie: glutIdleFunc
*/
#include <windows.h>  // biblioteci care urmeaza sa fie incluse
#include <stdlib.h> // necesare pentru citirea shader-elor
#include <stdio.h>
#include <math.h>
#include <iostream>
#include <GL/glew.h> // glew apare inainte de freeglut
#include <GL/freeglut.h> // nu trebuie uitat freeglut.h

#include "loadShaders.h"

#include "glm/glm.hpp"  
#include "glm/gtc/matrix_transform.hpp"
#include "glm/gtx/transform.hpp"
#include "glm/gtc/type_ptr.hpp"

using namespace std;

//////////////////////////////////////

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

int codCol;
float PI = 3.141592, angle = 0;
float tx = 0; float ty = 0;
float width = 400, height = 300;
glm::mat4 
	myMatrix, resizeMatrix, matrTransl, matrScale, matrRot;

void processNormalKeys(unsigned char key, int x, int y)
{
	switch (key) {
	case 'l':
		angle += 0.2f;
		break;
	case 'r':
		angle -= 0.2f;
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
		tx -= 10;
		break;
	case GLUT_KEY_RIGHT:
		tx += 10;
		break;
	case GLUT_KEY_UP:
		ty += 10;
		break;
	case GLUT_KEY_DOWN:
		ty -= 10;
		break;
	}
}

void CreateVBO(void)
{
	// varfurile 
	GLfloat Vertices[] = {
		// cele 4 varfuri din colturi 
	  -390.0f, -290.0f, 0.0f, 1.0f,
	   390.0f,  -290.0f, 0.0f, 1.0f,
	   390.0f, 290.0f, 0.0f, 1.0f,
	   -390.0f, 290.0f, 0.0f, 1.0f,
	   // varfuri pentru axe
		-400.0f, 0.0f, 0.0f, 1.0f,
		400.0f,  0.0f, 0.0f, 1.0f,
		0.0f, -300.0f, 0.0f, 1.0f,
		0.0f, 300.0f, 0.0f, 1.0f,
		// varfuri pentru dreptunghi
	   -50.0f,  -50.0f, 0.0f, 1.0f,
	   50.0f, -50.0f, 0.0f, 1.0f,
	   50.0f,  50.0f, 0.0f, 1.0f,
	   -50.0f,  50.0f, 0.0f, 1.0f,
	   // originea
	   0.0f, 0.0f, 0.0f, 1.0f
	};

	// culorile varfurilor din colturi
	GLfloat Colors[] = {
	  1.0f, 1.0f, 0.0f, 1.0f,
	  0.0f, 1.0f, 1.0f, 1.0f,
	  1.0f, 0.0f, 1.0f, 1.0f,
	  0.5f, 0.5f, 0.1f, 1.0f,
	};

	// se creeaza un buffer nou
	glGenBuffers(1, &VboId);
	// este setat ca buffer curent
	glBindBuffer(GL_ARRAY_BUFFER, VboId);
	// punctele sunt "copiate" in bufferul curent
	glBufferData(GL_ARRAY_BUFFER, sizeof(Vertices), Vertices, GL_STATIC_DRAW);
	// se creeaza / se leaga un VAO (Vertex Array Object) - util cand se utilizeaza mai multe VBO
	glGenVertexArrays(1, &VaoId);
	glBindVertexArray(VaoId);
	// se activeaza lucrul cu atribute; atributul 0 = pozitie
	glEnableVertexAttribArray(0);
	// 
	glVertexAttribPointer(0, 4, GL_FLOAT, GL_FALSE, 0, 0);
	// un nou buffer, pentru culoare
	glGenBuffers(1, &ColorBufferId);
	glBindBuffer(GL_ARRAY_BUFFER, ColorBufferId);
	glBufferData(GL_ARRAY_BUFFER, sizeof(Colors), Colors, GL_STATIC_DRAW);
	// atributul 1 =  culoare
	glEnableVertexAttribArray(1);
	glVertexAttribPointer(1, 4, GL_FLOAT, GL_FALSE, 0, 0);
}
void DestroyVBO(void)
{
	glDisableVertexAttribArray(1);
	glDisableVertexAttribArray(0);
	glBindBuffer(GL_ARRAY_BUFFER, 0);
	glDeleteBuffers(1, &ColorBufferId);
	glDeleteBuffers(1, &VboId);
	glBindVertexArray(0);
	glDeleteVertexArrays(1, &VaoId);
}

void CreateShaders(void)
{
	ProgramId = LoadShaders("03_04_Shader.vert", "03_04_Shader.frag");
	glUseProgram(ProgramId);
}
void DestroyShaders(void)
{
	glDeleteProgram(ProgramId);
}

void Initialize(void)
{
	glClearColor(1.0f, 1.0f, 1.0f, 1.0f); 
	CreateVBO();
	CreateShaders();
	codColLocation = glGetUniformLocation(ProgramId, "codCuloare");
	myMatrixLocation = glGetUniformLocation(ProgramId, "myMatrix");
	resizeMatrix = glm::ortho(-width, width, -height, height);
}
void RenderFunction(void)
{

	
	matrTransl = glm::translate(glm::mat4(1.0f), glm::vec3(tx, ty, 0.0));
	matrRot = glm::rotate(glm::mat4(1.0f), angle, glm::vec3(0.0, 0.0, 1.0));

	glClear(GL_COLOR_BUFFER_BIT);
	myMatrix = resizeMatrix;


	// Matricea de redimensionare (pentru elementele "fixe")
	myMatrixLocation = glGetUniformLocation(ProgramId, "myMatrix");
	glUniformMatrix4fv(myMatrixLocation, 1, GL_FALSE, &myMatrix[0][0]);
	// Desenare puncte din colturi si axe
	codCol = 0;
	glUniform1i(codColLocation, codCol);
	glPointSize(10.0);
	glDrawArrays(GL_POINTS, 0, 4);
	glDrawArrays(GL_LINES, 4, 4);

	// Matricea pentru elementele care isi schimba pozitia
	myMatrix = resizeMatrix * matrTransl * matrRot;
	glUniformMatrix4fv(myMatrixLocation, 1, GL_FALSE, &myMatrix[0][0]);
	// Desenare patrat si punct mobil
	codCol = 1;
	glUniform1i(codColLocation, codCol);
	glDrawArrays(GL_POLYGON, 8, 4);
	codCol = 2;
	glUniform1i(codColLocation, codCol);
	glEnable(GL_POINT_SMOOTH);
	glDrawArrays(GL_POINTS, 12, 1);
	glDisable(GL_POINT_SMOOTH);
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
	glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGB);
	glutInitWindowPosition(100, 100);
	glutInitWindowSize(800, 600);
	glutCreateWindow("Compunerea transformarilor. Utilizarea tastaturii");
	glewInit();
	Initialize();
	glutDisplayFunc(RenderFunction);
	glutIdleFunc(RenderFunction);
	glutKeyboardFunc(processNormalKeys);
	glutSpecialFunc(processSpecialKeys);
	glutCloseFunc(Cleanup);
	glutMainLoop();
}

