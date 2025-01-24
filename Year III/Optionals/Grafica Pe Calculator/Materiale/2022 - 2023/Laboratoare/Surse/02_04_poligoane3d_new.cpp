/* 
- Acest cod sursa este un "echivalent" 2D al codului 02_03_poligoane_3d_old.cpp
- Patratele sunt desenate folosind GL_TRIANGLE_FAN, varfurile au culori diferite
- Este realizat cu OpenGL "nou" 
- Nu sunt indicati parametri pentru vizualizare / decupare, fiind selectate valorile implicite
*/

#include <windows.h>  // biblioteci care urmeaza sa fie incluse
#include <stdlib.h> // necesare pentru citirea shader-elor
#include <stdio.h>
#include <GL/glew.h> // glew apare inainte de freeglut
#include <GL/freeglut.h> // nu trebuie uitat freeglut.h
#include "loadShaders.h"

//////////////////////////////////////
GLuint
VaoId,
VboId,
ColorBufferId,
ProgramId;

void CreateVBO(void)
{
	// varfurile 
	GLfloat Vertices[] = {
	  0.5f, -0.5f, 0.0f, 1.0f,
	  -0.5f, -0.5f, 0.0f, 1.0f,
	  -0.5f, 0.5f, 0.0f, 1.0f,
	   0.5f, 0.5f, 0.0f, 1.0f,
	   //
	   0.3f, 0.3f, 0.0f, 1.0f,
	   -0.3f, 0.3f, 0.0f, 1.0f,
	   -0.3f, -0.3f, 0.0f, 1.0f,
	   0.3f, -0.3f, 0.0f, 1.0f
	};

	// culorile, ca atribute ale varfurilor
	GLfloat Colors[] = {
	  1.0f, 0.0f, 0.0f, 1.0f,
	  0.0f, 1.0f, 0.0f, 1.0f,
	  0.0f, 0.0f, 1.0f, 1.0f,
	  1.0f, 1.0f, 0.0f, 1.0f,
	  //
	  1.0f, 1.0f, 0.0f, 1.0f,
	  0.0f, 0.0f, 1.0f, 1.0f,
	  0.0f, 1.0f, 0.0f, 1.0f,
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

	glLineWidth(10.0);
	glPolygonMode(GL_FRONT, GL_FILL);
	glPolygonMode(GL_BACK, GL_LINE);
	glDrawArrays(GL_TRIANGLE_FAN, 0, 4);
	glDrawArrays(GL_TRIANGLE_FAN, 4, 4);
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
	glutInitWindowSize(600, 600); //dimensiunile ferestrei
	glutCreateWindow("Poligoane 3D cu OpenGL <<nou>>"); // titlul ferestrei
	glewInit(); // nu uitati de initializare glew; trebuie initializat inainte de a a initializa desenarea
	Initialize();
	glutDisplayFunc(RenderFunction);
	glutCloseFunc(Cleanup);
	glutMainLoop();
}

