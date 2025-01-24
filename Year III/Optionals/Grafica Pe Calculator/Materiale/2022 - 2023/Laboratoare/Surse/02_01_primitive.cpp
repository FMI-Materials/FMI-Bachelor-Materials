// Codul sursa este adaptat dupa OpenGLBook.com

#include <windows.h>  // biblioteci care urmeaza sa fie incluse
#include <stdlib.h> // necesare pentru citirea shader-elor
#include <stdio.h>
#include <cstdlib>
#include <GL/glew.h> // glew apare inainte de freeglut
#include <GL/freeglut.h> // nu trebuie uitat freeglut.h
#include "loadShaders.h"

//////////////////////////////////////

GLuint
VaoId,
VboId,
ColorBufferId,
ProgramId,
codColLocation;

int codCol;

void CreateVBO(void)
{
	// varfurile 
	GLfloat Vertices[] = {
	  -0.2f, -0.2f, 0.0f, 1.0f,
	   0.0f,  0.2f, 0.0f, 1.0f,
	   0.2f, -0.2f, 0.0f, 1.0f,
	  -0.8f, -0.8f, 0.0f, 1.0f,
	   0.0f,  0.8f, 0.0f, 1.0f,
	   0.8f, -0.8f, 0.0f, 1.0f
	};

	// culorile, ca atribute ale varfurilor
	GLfloat Colors[] = {
	  1.0f, 0.0f, 0.0f, 1.0f,
	  0.0f, 1.0f, 0.0f, 1.0f,
	  0.0f, 0.0f, 1.0f, 1.0f,
	  1.0f, 0.0f, 0.0f, 1.0f,
	  0.0f, 1.0f, 0.0f, 1.0f,
	  0.0f, 0.0f, 1.0f, 1.0f
	};

	// se creeaza un buffer nou
	glGenBuffers(1, &VboId);
	// este setat ca buffer curent
	glBindBuffer(GL_ARRAY_BUFFER, VboId);
	// varfurile sunt "copiate" in bufferul curent
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
	ProgramId = LoadShaders("02_01_Shader.vert", "02_01_Shader.frag");
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
}
void RenderFunction(void)
{
	glClear(GL_COLOR_BUFFER_BIT);

	// Variabilele uniforme sunt folosite pentru a "comunica" cu shader-ele
	codColLocation = glGetUniformLocation(ProgramId, "codCol");
	codCol = 0;
	glUniform1i(codColLocation, codCol);
	// Desenarea segmentelor folosind modelul Gouraud (Gouraud shading)
	glLineWidth(5.0);
	glDrawArrays(GL_LINE_STRIP, 0, 6);

	// Se atribuie o alta valoare variabilei uniforme
	codCol = 1;
	glUniform1i(codColLocation, codCol);
	// Punctele cu o singura culoare 
	glEnable(GL_POINT_SMOOTH);
	glPointSize(20.0);
	codCol = rand() % 4 + 1;
	glUniform1i(codColLocation, codCol);
	glDrawArrays(GL_POINTS, 0, 6);
	glDisable(GL_POINT_SMOOTH);
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
	glutInitWindowPosition(100, 100); // pozitia initiala a ferestrei
	glutInitWindowSize(600, 400); //dimensiunile ferestrei
	glutCreateWindow("Primitive si culori"); // titlul ferestrei
	glewInit(); // nu uitati de initializare glew; trebuie initializat inainte de a a initializa desenarea
	Initialize();
	glutDisplayFunc(RenderFunction);
	glutCloseFunc(Cleanup);
	glutMainLoop();
}

