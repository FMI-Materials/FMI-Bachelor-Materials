/* INDEXARE
Elemente de noutate:
   - folosirea indexarii varfurilor: elemente asociate (matrice, buffer)
   - desenarea se face folosind functia glDrawElements()
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
#include "SOIL.h"

using namespace std;

//////////////////////////////////////

GLuint
	VaoId,
	VboId,
	EboId,
	ColorBufferId,
	ProgramId,
	myMatrixLocation,
	viewLocation,
	projLocation,
	matrRotlLocation,
	codColLocation;;

float width = 80.f, height = 60.f;
GLuint texture;

// elemente pentru matricea de vizualizare
float Obsx = 0.0, Obsy = 0.0, Obsz = 800.f;
float Refx = 0.0f, Refy = 0.0f;
float Vx = 0.0;
glm::mat4 view;

// elemente pentru matricea de proiectie
float width = 800, height = 600, xwmin = -800.f, xwmax = 800, ywmin = -600, ywmax = 600, znear = 0, zfar = 1000, fov = 45;
glm::mat4 projection;

glm::mat4 
	myMatrix, resizeMatrix = glm::ortho(-width, width, -height, height),
	matrTransl, matrScale;

void CreateVBO(void)
{
	// varfurile 
	GLfloat Vertices[] = {
		-5.0f, -5.0f, 0.0f, 1.0f, 1.0f, 0.0f, 0.0f, 1.0f,	0.0f, 0.0f,
		5.0f,  -5.0f, 0.0f, 1.0f, 0.0f, 1.0f, 0.0f, 1.0f,	1.0f, 0.0f,
		5.0f,  5.0f, 0.0f, 1.0f, 0.0f, 0.0f, 1.0f, 1.0f,	1.0f, 1.0f,
		-5.0f,  5.0f, 0.0f, 1.0f, 1.0f, 0.0f, 1.0f, 1.0f,	0.0f, 1.0f
	};

	// indicii pentru varfuri
	GLuint Indices[] = {
	  0, 1, 2, 3, 0, 2
	};

	// se creeaza un VAO (Vertex Array Object) - util cand se utilizeaza mai multe VBO
	glGenVertexArrays(1, &VaoId);
	// se creeaza un buffer nou (atribute)
	glGenBuffers(1, &VboId);
	// se creeaza un buffer nou (indici)
	glGenBuffers(1, &EboId);

	// legarea VAO 
	glBindVertexArray(VaoId);

	// legarea buffer-ului "Array"
	glBindBuffer(GL_ARRAY_BUFFER, VboId);
	// punctele sunt "copiate" in bufferul curent
	glBufferData(GL_ARRAY_BUFFER, sizeof(Vertices), Vertices, GL_STATIC_DRAW);

	// legarea buffer-ului "Element" (indicii)
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EboId);
	// indicii sunt "copiati" in bufferul curent
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(Indices), Indices, GL_STATIC_DRAW);

	// se activeaza lucrul cu atribute; atributul 0 = pozitie
	glEnableVertexAttribArray(0);
	glVertexAttribPointer(0, 4, GL_FLOAT, GL_FALSE, 9 * sizeof(GLfloat), (GLvoid*)0);

	// se activeaza lucrul cu atribute; atributul 1 = culoare
	glEnableVertexAttribArray(1);
	glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 9 * sizeof(GLfloat), (GLvoid*)(4 * sizeof(GLfloat)));

	// se activeaza lucrul cu atribute; atributul 2 = coordonate de texturare
	glEnableVertexAttribArray(2);
	glVertexAttribPointer(2, 2, GL_FLOAT, GL_FALSE, 9 * sizeof(GLfloat), (GLvoid*)(7 * sizeof(GLfloat)));

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

void LoadTexture(void)
{
	glGenTextures(1, &texture);
	glBindTexture(GL_TEXTURE_2D, texture);

	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);

	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);

	int width, height;
	unsigned char* image = SOIL_load_image("text_smiley_face.png", &width, &height, 0, SOIL_LOAD_RGB);
	glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, width, height, 0, GL_RGB, GL_UNSIGNED_BYTE, image);
	glGenerateMipmap(GL_TEXTURE_2D);

	SOIL_free_image_data(image);
	glBindTexture(GL_TEXTURE_2D, 0);
}

void CreateShaders(void)
{
	ProgramId = LoadShaders("06_02_Shader.vert", "06_02_Shader.frag");
	glUseProgram(ProgramId);
}

void DestroyShaders(void)
{
	glDeleteProgram(ProgramId);
}

void Initialize(void)
{
	glClearColor(1.0f, 1.0f, 1.0f, 0.0f);
	CreateVBO();
	CreateShaders();
	// Pentru shaderul de varfuri
	myMatrixLocation = glGetUniformLocation(ProgramId, "myMatrix");
	viewLocation = glGetUniformLocation(ProgramId, "view");
	projLocation = glGetUniformLocation(ProgramId, "projection");
	// Pentru shaderul de fragmente
	glUniform1i(glGetUniformLocation(ProgramId, "myTexture"), 0);
	glClearColor(1.0f, 1.0f, 1.0f, 0.0f);
}
void RenderFunction(void)
{
	glClear(GL_COLOR_BUFFER_BIT);

	// se schimba pozitia observatorului
	glm::vec3 Obs = glm::vec3(Obsx, Obsy, Obsz);
	// pozitia punctului de referinta
	Refx = Obsx; Refy = Obsy;
	glm::vec3 PctRef = glm::vec3(Refx, Refy, -1.0f);
	// verticala din planul de vizualizare 
	glm::vec3 Vert = glm::vec3(Vx, 1.0f, 0.0f);
	view = glm::lookAt(Obs, PctRef, Vert);

	// Functie pentru realizarea proiectiei
	projection = glm::perspective(fov, GLfloat(width) / GLfloat(height), znear, zfar);
	myMatrix = glm::mat4(1.0f);
	//myMatrix = matrRot;
	CreateVBO();
	// Functii pentru texturi
	LoadTexture();
	glActiveTexture(GL_TEXTURE0);
	glBindTexture(GL_TEXTURE_2D, texture);
	// transmitere variabile uniforme pentru shaderul de varfuri
	glUniformMatrix4fv(myMatrixLocation, 1, GL_FALSE, &myMatrix[0][0]);
	glUniformMatrix4fv(viewLocation, 1, GL_FALSE, &view[0][0]);
	glUniformMatrix4fv(projLocation, 1, GL_FALSE, &projection[0][0]);
	// transmitere variabile uniforme pentru shaderul de fragmente
	glUniform1i(glGetUniformLocation(ProgramId, "myTexture"), 0);

	matrTransl = glm::translate(glm::mat4(1.0f), glm::vec3(30, 30, 0.0));
	matrScale = glm::scale(glm::mat4(1.0f), glm::vec3(2.0, 0.5, 0.0));

	// punctul 1
	myMatrix = resizeMatrix * matrTransl * matrScale;
	glUniformMatrix4fv(myMatrixLocation, 1, GL_FALSE, &myMatrix[0][0]);
	glDrawElements(GL_POLYGON, 6, GL_UNSIGNED_INT, (void*)(0));

	// punctul 2
	myMatrix = resizeMatrix * matrScale * matrTransl;
	glUniformMatrix4fv(myMatrixLocation, 1, GL_FALSE, &myMatrix[0][0]);
	glDrawElements(GL_LINE_STRIP, 6, GL_UNSIGNED_INT, (void*)(0));
	// De realizat desenul folosind segmente de dreapta
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
	glutCreateWindow("Utilizarea indexarii varfurilor");
	glewInit();
	Initialize();
	glutDisplayFunc(RenderFunction);
	glutIdleFunc(RenderFunction);
	glutCloseFunc(Cleanup);
	glutMainLoop();
}

