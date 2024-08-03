/* TRANSFORMARI.
   - compunerea transformarilor, realizarea unei rotatii cu centrul diferit de origine
   - utilizarea GL_QUADS pentru desenarea unui dreptunghi
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

glm::mat4 
	myMatrix, resizeMatrix, matrTransl, matrTransl1, matrTransl2, matrScale, matrRot, mTest;

int codCol;
float PI = 3.141592;

float width = 400, height = 300;
 
void CreateVBO(void)
{
	// varfurile 
	GLfloat Vertices[] = {
	   // varfuri pentru axe
		-400.0f, 0.0f, 0.0f, 1.0f,
		400.0f,  0.0f, 0.0f, 1.0f,
		0.0f, -300.0f, 0.0f, 1.0f,
		0.0f, 300.0f, 0.0f, 1.0f,
	   // varfuri pentru dreptunghi
	   50.0f,  50.0f, 0.0f, 1.0f,
	   50.0f, 150.0f, 0.0f, 1.0f,
	   150.0f,  150.0f, 0.0f, 1.0f,
	   150.0f,  50.0f, 0.0f, 1.0f,
	};

	// culorile extremitatilor axelor
	GLfloat Colors[] = {
	  1.0f, 0.0f, 0.0f, 1.0f,
	  0.0f, 1.0f, 0.0f, 1.0f,
	  0.0f, 0.0f, 1.0f, 1.0f,
	  1.0f, 0.0f, 0.0f, 1.0f,
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
	glClearColor(1.0f, 1.0f, 1.0f, 1.0f); // culoarea de fond a ecranului
	CreateVBO();
	CreateShaders();
	codColLocation = glGetUniformLocation(ProgramId, "codCuloare");
	myMatrixLocation = glGetUniformLocation(ProgramId, "myMatrix");

	// Dreptunghiul "decupat" 
	resizeMatrix = glm::ortho(-width, width,-height, height);

	// Matricele de rotatie si de translatie 
	// Rotatie cu unghiul angle
	GLfloat angle = PI / 8; 
	matrRot = glm::rotate(glm::mat4(1.0f), angle, glm::vec3(0.0, 0.0, 1.0));
	// Translatia 1: centrul patratului este translatat in origine
	matrTransl1 = glm::translate(glm::mat4(1.0f), glm::vec3(-100.f, -100.f, 0.0));
	// Translatia 2: inversa/opusa translatiei T1
	matrTransl2 = glm::translate(glm::mat4(1.0f), glm::vec3(100.f, 100.f, 0.0));
}
void RenderFunction(void)
{
	glClear(GL_COLOR_BUFFER_BIT);

	// Matrice pentru elemente "fixe" - axe
	myMatrix = resizeMatrix;
	glUniformMatrix4fv(myMatrixLocation, 1, GL_FALSE, &myMatrix[0][0]);

	// Axe: culoare + desenare
	codCol = 0;
	glUniform1i(codColLocation, codCol);
	glLineWidth(1.0);
	glDrawArrays(GL_LINES, 0, 4);

	// Dreptunghiul initial: culoare + desenare
	codCol = 1;
	glUniform1i(codColLocation, codCol);
	glLineWidth(2.0);
	glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);
	glDrawArrays(GL_QUADS, 4, 4);

	// Dreptunghiul transformat
	// Matricea pentru stabilirea pozitiei
	myMatrix = resizeMatrix * matrTransl2 * matrRot * matrTransl1;
	glUniformMatrix4fv(myMatrixLocation, 1, GL_FALSE, &myMatrix[0][0]);
	// Culoarea
	codCol = 2;
	glUniform1i(codColLocation, codCol);
	// Desenarea primitivei
	glLineWidth(4.0);
	glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);
	glDrawArrays(GL_QUADS, 4, 4);

	glutPostRedisplay();
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
	glutInitDisplayMode(GLUT_SINGLE | GLUT_RGB);
	glutInitWindowPosition(100, 100);
	glutInitWindowSize(800, 600);
	glutCreateWindow("Rotirea unui patrat in jurul centrului sau");
	glewInit();
	Initialize();
	glutDisplayFunc(RenderFunction);
	glutCloseFunc(Cleanup);
	glutMainLoop();
}

