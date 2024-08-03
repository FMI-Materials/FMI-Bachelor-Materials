/*
- Trasarea unui cerc si a unui disc folosind reprezentarea parametrica.
- Folosirea functiei reshapeFcn (relevanta pentru pastrarea proportiilor)
*/
#include <windows.h>  
#include <stdlib.h>  
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

const int NR_POINTS = 20;
const float PI = 3.141592f;

GLuint
	VaoId,
	VboId,
	EboId,
	ColorBufferId,
	ProgramId,
	myMatrixLocation,
	codColLocation;
int codCol;

GLint winWidth = 1000, winHeight = 600; // dimensiune initiala fereastra 
float width = winWidth / 10, height = winHeight / 10; // parametri pentru pastrarea proportiilor
float cx = 10.0f, cy = 5.0f, radius = 20.0; // elemente pentru cerc: centru, raza
glm::mat4 myMatrix;

void CreateVBO(void)
{
	//coordonatele varfurilor
	glm::vec4 vf_coord[NR_POINTS];
	for (int i = 0; i < NR_POINTS; i++) // sunt NR_POINTS varfuri
	{
		// se foloseste reprezentarea parametrica pentru a genera varfurile (puncte situate pe cerc)
		vf_coord[i] =
			glm::vec4(
				cx + radius * cos(2 * PI * i / NR_POINTS),
				cy + radius * sin(2 * PI * i / NR_POINTS),
				0.0f, 1.0f);
	};

	// culorile varfurilor
	glm::vec4 vf_col[NR_POINTS];
	for (int i = 0; i < NR_POINTS; i++)
	{
		vf_col[i] = glm::vec4(
			abs(0.4 + 0.3 * i / NR_POINTS + cos(0.1 * i)),
			abs(0.6 + 0.4 * i / NR_POINTS + sin(0.1 * i)),
			abs(0.4 + 0.5 * i / NR_POINTS - sin(0.1 * i)), 1.0f);
	};

	// indicii
	GLuint vf_ind[NR_POINTS + 3 * (NR_POINTS - 2)]; // NR_POINTS(contur) + 3 * (NR_POINTS - 2)(triunghiuri)
	// indexare pentru trasarea conturului
	for (int i = 0; i < NR_POINTS; i++) // primii NR_POINTS(=N) indici corespund varfurilor
		vf_ind[i] = i;
	// indexare pentru desenarea interiorului; grupuri de cate trei, 
	// pentru triunghiul i sunt folosite varfurile (0, i+1, i+2) sunt alocati indicii N+3*i, N+3*i+1, N+3*i+2
	for (int i = 0; i < NR_POINTS - 2; i++)
	{
		vf_ind[NR_POINTS + 3 * i] = 0;
		vf_ind[NR_POINTS + 3 * i + 1] = i + 1;
		vf_ind[NR_POINTS + 3 * i + 2] = i + 2;
	}

	// se creeaza un buffer nou pentru varfuri
	glGenBuffers(1, &VboId);
	// buffer pentru indici
	glGenBuffers(1, &EboId);
	// se creeaza / se leaga un VAO (Vertex Array Object)
	glGenVertexArrays(1, &VaoId);

	// legare VAO
	glBindVertexArray(VaoId);

	// buffer-ul este setat ca buffer curent
	glBindBuffer(GL_ARRAY_BUFFER, VboId);

	// buffer-ul va contine atat coordonatele varfurilor, cat si datele de culoare
	glBufferData(GL_ARRAY_BUFFER, sizeof(vf_coord) + sizeof(vf_col), NULL, GL_STATIC_DRAW);
	glBufferSubData(GL_ARRAY_BUFFER, 0, sizeof(vf_coord), vf_coord);
	glBufferSubData(GL_ARRAY_BUFFER, sizeof(vf_coord), sizeof(vf_col), vf_col);

	// buffer-ul pentru indici
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EboId);
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(vf_ind), vf_ind, GL_STATIC_DRAW);

	// se activeaza lucrul cu atribute; atributul 0 = pozitie, atributul 1 = culoare, acestea sunt indicate corect in VBO
	glVertexAttribPointer(0, 4, GL_FLOAT, GL_FALSE, 0, NULL);
	glVertexAttribPointer(1, 4, GL_FLOAT, GL_FALSE, 0, (const GLvoid*)sizeof(vf_coord));
	glEnableVertexAttribArray(0);
	glEnableVertexAttribArray(1);
}
void DestroyVBO(void)
{
	glDisableVertexAttribArray(1);
	glDisableVertexAttribArray(0);
	glBindBuffer(GL_ARRAY_BUFFER, 0);
	glDeleteBuffers(1, &EboId);
	glDeleteBuffers(1, &ColorBufferId);
	glDeleteBuffers(1, &VboId);
	glBindVertexArray(0);
	glDeleteVertexArrays(1, &VaoId);
}
void CreateShaders(void)
{
	ProgramId = LoadShaders("09_01_Shader.vert", "09_01_Shader.frag");
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
	myMatrixLocation = glGetUniformLocation(ProgramId, "myMatrix");
	codColLocation = glGetUniformLocation(ProgramId, "codCol");
}
void reshapeFcn(GLint newWidth, GLint newHeight)
{
	glViewport(0, 0, newWidth, newHeight);
	width = newWidth / 10, height = newHeight / 10;
}
void RenderFunction(void)
{
	glClear(GL_COLOR_BUFFER_BIT);
	myMatrix = glm::ortho(-width, width, -height, height);
	glUniformMatrix4fv(myMatrixLocation, 1, GL_FALSE, &myMatrix[0][0]);

	// conturul
	codCol = 1;
	glUniform1i(codColLocation, codCol);
	glLineWidth(2.0f);
	glDrawElements(GL_LINE_LOOP, NR_POINTS, GL_UNSIGNED_INT, (GLvoid*)(0));

	// interiorul (discul)
	codCol = 0;
	glUniform1i(codColLocation, codCol);
	glDrawElements(GL_TRIANGLES,
		3 * (NR_POINTS - 2),
		GL_UNSIGNED_INT,
		(GLvoid*)((NR_POINTS) * sizeof(GLuint)));
	// acelasi efect poate fi obtinut cu GL_TRIANGLE_FAN, utilizand multimea initiala de indici
	// glDrawElements(GL_TRIANGLE_FAN, NR_POINTS, GL_UNSIGNED_INT, (GLvoid*)(0));

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
	glutInitWindowSize(winWidth, winHeight);
	glutCreateWindow("Desenarea unui disc");
	glewInit();
	Initialize();
	glutReshapeFunc(reshapeFcn);
	glutDisplayFunc(RenderFunction);
	glutCloseFunc(Cleanup);
	glutMainLoop();
}
