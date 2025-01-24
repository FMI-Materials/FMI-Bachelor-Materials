/* DESCRIERE: DREPTUNGHI CU SATELIT -- varianta cu OpenGL "nou"
	- utilizeaza diverse transformari si compunerea acestora folosind biblioteca glm
	- functii pentru utilizarea mouse-ului
*/

#include <windows.h>  // biblioteci care urmeaza sa fie incluse
#include <stdlib.h> // necesare pentru citirea shader-elor
#include <stdio.h>
#include <math.h>
#include <iostream>
#include <GL/glew.h> // glew apare inainte de freeglut
#include <GL/freeglut.h> // nu trebuie uitat freeglut.h
#include "loadShaders.h"

// Din biblioteca glm
#include "glm/glm.hpp"  
#include "glm/gtc/matrix_transform.hpp"
#include "glm/gtx/transform.hpp"
#include "glm/gtc/type_ptr.hpp"

using namespace std;

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
float width = 450, height = 300;
float i = 0.0, alpha = 0.0, step=0.1, beta = 0.002;
glm::mat4
	myMatrix, resizeMatrix, matrTransl, matrScale1, matrScale2, matrRot, matrDepl;

void displayMatrix()
{
	for (int ii = 0; ii < 4; ii++)
	{
		for (int jj = 0; jj < 4; jj++)
			cout << myMatrix[ii][jj] << "  ";
		cout << endl;
	};
	cout << "\n";
};

void miscad(void)
{
	i = i + alpha;
	if (i > 350.0)
		alpha = -step;
	else if (i < -350.0)
		alpha = step;
	angle = angle - beta;
	glutPostRedisplay();
}

void miscas(void)
{
	i = i + alpha;
	if (i < -350.0)
		alpha = step;
	else if (i > 350.0)
		alpha = -step;
	angle = angle + beta;
	glutPostRedisplay();
}

void mouse(int button, int state, int x, int y)
{
	switch (button) {
	case GLUT_LEFT_BUTTON:
		if (state == GLUT_DOWN)
			alpha = -step; 
		glutIdleFunc(miscas);
		break;
	case GLUT_RIGHT_BUTTON:
		if (state == GLUT_DOWN)
			alpha = step; 
		glutIdleFunc(miscad);
		break;
	default:
		break;
	}
}

void CreateVBO(void)
{
	// varfurile 
	GLfloat Vertices[] = {
	// varfuri pentru axe
	-450.0f, -30.0f, 0.0f, 1.0f,
	450.0f,  -30.0f, 0.0f, 1.0f,
	0.0f, -300.0f, 0.0f, 1.0f,
	0.0f, 300.0f, 0.0f, 1.0f,
	// varfuri pentru dreptunghi
	-50.0f,  -50.0f, 0.0f, 1.0f,
	50.0f, -50.0f, 0.0f, 1.0f,
	50.0f,  50.0f, 0.0f, 1.0f,
	-50.0f,  50.0f, 0.0f, 1.0f,
	};

	// culorile varfurilor din colturi
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
	ProgramId = LoadShaders("03_02_Shader.vert", "03_02_Shader.frag");
	glUseProgram(ProgramId);
}
void DestroyShaders(void)
{
	glDeleteProgram(ProgramId);
}

void Initialize(void)
{
	glClearColor(1.0f, 1.0f, 1.0f, 0.0f); // culoarea de fond a ecranului
	CreateVBO();
	CreateShaders();
	codColLocation = glGetUniformLocation(ProgramId, "codCuloare");
	myMatrixLocation = glGetUniformLocation(ProgramId, "myMatrix");
}
void RenderFunction(void)
{
	glClear(GL_COLOR_BUFFER_BIT);

	// TO DO: schimbati transformarile (de exemplu deplasarea are loc pe axa Oy sau pe o alta dreapta)
	resizeMatrix = glm::ortho(-width, width, -height, height); // scalam, "aducem" scena la "patratul standard" [-1,1]x[-1,1]
	matrTransl = glm::translate(glm::mat4(1.0f), glm::vec3(i, 0.0, 0.0)); // controleaza translatia de-a lungul lui Ox
	matrDepl = glm::translate(glm::mat4(1.0f), glm::vec3(0, 80.0, 0.0)); // plaseaza patratul rosu
	matrScale1 = glm::scale(glm::mat4(1.0f), glm::vec3(0.5, 0.5, 0.0)); // folosita la desenarea dreptunghiului albastru
	matrScale2 = glm::scale(glm::mat4(1.0f), glm::vec3(0.25, 0.25, 0.0)); // folosita la desenarea patratului rosu
	matrRot = glm::rotate(glm::mat4(1.0f), angle, glm::vec3(0.0, 0.0, 1.0)); // rotatie folosita la deplasarea patratului rosu

	// Deseneaza liniile de coordonate
	// Matricea de redimensionare (pentru elementele "fixe") 
	myMatrix = resizeMatrix;
	// Culoarea
	codCol = 0;
	// Transmitere variabile uniforme
	glUniformMatrix4fv(myMatrixLocation, 1, GL_FALSE, &myMatrix[0][0]);
	glUniform1i(codColLocation, codCol);
	// Apelare DrawArrays
	glDrawArrays(GL_LINES, 0, 4);

	// Matricea pentru dreptunghiul albastru 
	myMatrix = resizeMatrix * matrTransl * matrScale1 * matrRot;
	// Culoarea
	codCol = 1;
	// Transmitere variabile uniforme
	glUniformMatrix4fv(myMatrixLocation, 1, GL_FALSE, &myMatrix[0][0]);
	glUniform1i(codColLocation, codCol);
	// Apelare DrawArrays
	glDrawArrays(GL_POLYGON, 4, 4);

	//// Matricea pentru dreptunghiul rosu 
	//myMatrix = resizeMatrix * matrTransl * matrRot * matrDepl * matrScale2;
	//// Culoarea
	//codCol = 2;
	//// Transmitere variabile uniforme
	//glUniformMatrix4fv(myMatrixLocation, 1, GL_FALSE, &myMatrix[0][0]);
	//glUniform1i(codColLocation, codCol);
	//// Apelare DrawArrays
	//glDrawArrays(GL_POLYGON, 4, 4);

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
	glutCreateWindow("Dreptunghi cu satelit - OpenGL <<nou>>");
	glewInit();
	Initialize();
	glutDisplayFunc(RenderFunction);
	glutMouseFunc(mouse);
	glutCloseFunc(Cleanup);
	glutMainLoop();
}

