/*
Aplicarea modelului de iluminare in cazul unei sfere.
- Fiecare varf are asociata o culoare (eventual poate fi aceeasi). 
Coordonata z a fiecarui varf este "perturbata" (se adauga "zgomot").
Fiecare varf are asociata o normala.
- Sunt doua posibilitati, intrucat sunt testate variante pentru:
	(i) implementarea modelului de iluminare 
	(a. in shader-ul de fragment, b. in shader-ul de varfuri). 
	In acest scop sunt scrise shader-e diferite – 10_03f*, respectiv 10_03v*)
- Din programul principal sunt transferate in shader-ul de varfuri
toate informatiile geometrice
(coordonate, normale, pozitia observatorului, pozitia sursei de lumina).
- Din shader-ul de varfuri in sunt transferate shaderul de fragment informatii diferite,
in functie de shader-ul in care este implementat modelul de iluminare
(de exemplu, daca modelul de iluminare este implementat in shader-ul de varfuri,
in shader-ul de fragment este transferata culoarea varfului, a
ceasta poate fi apoi randata ca atare).
- In shader-ul de varfuri 10_03v* exista posibilitatea de a selecta
sa fie randata doar culoarea varfurilor, fara aplicarea iluminarii.
- Folosirea meniurilor glutMenu.
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

// identificatori 
GLuint
VaoId,
VboId,
EboId,
ProgramIdf,
ProgramIdv,
viewLocation,
projLocation,
lightColorLoc, lightPosLoc, viewPosLoc,
rendermode;

float const PI = 3.141592f;
// Elemente pentru reprezentarea suprafetei
// intervalele pentru parametrii considerati (u si v)
float const U_MIN = -PI / 2, U_MAX = PI / 2, V_MIN = 0, V_MAX = 2 * PI;
// numarul de paralele/meridiane, de fapt numarul de valori ptr parametri
int const NR_PARR = 30, NR_MERID = 30;
// pasul cu care vom incrementa u, respectiv v
float step_u = (U_MAX - U_MIN) / NR_PARR, step_v = (V_MAX - V_MIN) / NR_MERID;

// alte variabile
float radius = 50;
int index, index_aux;

// variabile pentru matricea de vizualizare
float Refx = 0.0f, Refy = 0.0f, Refz = 0.0f;
float alpha = 0.0f, beta = 0.0f, dist = 300.0f;
float Obsx, Obsy, Obsz;
float Vx = 0.0f, Vy = 0.0f, Vz = -1.0f;
float incr_alpha1 = 0.01f, incr_alpha2 = 0.01f;

// variabile pentru matricea de proiectie
float width = 800, height = 600, znear = 1, fov = 30;

// pentru fereastra de vizualizare 
GLint winWidth = 1000, winHeight = 600;

// vectori
glm::vec3 Obs, PctRef, Vert;

// matrice utilizate
glm::mat4 view, projection;

enum {
	Il_Frag, Il_Vert
};
void menu(int selection)
{
	rendermode = selection;
	glutPostRedisplay();
}void processNormalKeys(unsigned char key, int x, int y)
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
void CreateVBO(void)
{
	// varfurile 
	// Matricele pentru varfuri, culori, indici
	glm::vec4 Vertices[(NR_PARR + 1) * NR_MERID];
	glm::vec3 Colors[(NR_PARR + 1) * NR_MERID];
	glm::vec3 Normals[(NR_PARR + 1) * NR_MERID];
	GLushort Indices[2 * (NR_PARR + 1) * NR_MERID + 4 * (NR_PARR + 1) * NR_MERID];
	for (int merid = 0; merid < NR_MERID; merid++)
	{
		for (int parr = 0; parr < NR_PARR + 1; parr++)
		{
			// implementarea reprezentarii parametrice 
			float u = U_MIN + parr * step_u; // valori pentru u si v
			float v = V_MIN + merid * step_v;
			float x_vf = radius * cosf(u) * cosf(v); // coordonatele varfului corespunzator lui (u,v)
			float y_vf = radius * cosf(u) * sinf(v);
			float z_vf = radius * sinf(u) + 0.05 * radius * rand() / RAND_MAX;
			// identificator ptr varf; coordonate + culoare + indice la parcurgerea meridianelor
			index = merid * (NR_PARR + 1) + parr;
			Vertices[index] = glm::vec4(x_vf, y_vf, z_vf, 1.0);
			Colors[index] = glm::vec3(0.96 + 0.1f * sinf(u) * cosf(v), 0.71 + 0.1f * cosf(u) * sinf(v), 0.1);
			// Colors[index] = glm::vec3(0.1f + sinf(u), 0.1f + cosf(v), 0.1f + -1.5 * sinf(u));
			Normals[index] = glm::vec3(x_vf, y_vf, z_vf);
			Indices[index] = index;
			// indice ptr acelasi varf la parcurgerea paralelelor
			index_aux = parr * (NR_MERID)+merid;
			Indices[(NR_PARR + 1) * NR_MERID + index_aux] = index;
			// indicii pentru desenarea fetelor, pentru varful curent sunt definite 4 varfuri
			if ((parr + 1) % (NR_PARR + 1) != 0) // varful considerat sa nu fie Polul Nord
			{
				int AUX = 2 * (NR_PARR + 1) * NR_MERID;
				int index1 = index; // varful v considerat
				int index2 = index + (NR_PARR + 1); // dreapta lui v, pe meridianul urmator
				int index3 = index2 + 1;  // dreapta sus fata de v
				int index4 = index + 1;  // deasupra lui v, pe acelasi meridian
				if (merid == NR_MERID - 1)  // la ultimul meridian, trebuie revenit la meridianul initial
				{
					index2 = index2 % (NR_PARR + 1);
					index3 = index3 % (NR_PARR + 1);
				}
				Indices[AUX + 4 * index] = index1;  // unele valori ale lui Indices, corespunzatoare Polului Nord, au valori neadecvate
				Indices[AUX + 4 * index + 1] = index2;
				Indices[AUX + 4 * index + 2] = index3;
				Indices[AUX + 4 * index + 3] = index4;
			}
		}
	};

	// generare VAO/buffere
	glGenBuffers(1, &VboId); // atribute
	glGenBuffers(1, &EboId); // indici

	// legare+"incarcare" buffer
	glBindBuffer(GL_ARRAY_BUFFER, VboId);
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EboId);
	glBufferData(GL_ARRAY_BUFFER, sizeof(Vertices) + sizeof(Colors) + sizeof(Normals), NULL, GL_STATIC_DRAW);
	glBufferSubData(GL_ARRAY_BUFFER, 0, sizeof(Vertices), Vertices);
	glBufferSubData(GL_ARRAY_BUFFER, sizeof(Vertices), sizeof(Colors), Colors);
	glBufferSubData(GL_ARRAY_BUFFER, sizeof(Vertices) + sizeof(Colors), sizeof(Normals), Normals);
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(Indices), Indices, GL_STATIC_DRAW);

	// atributele; 
	glEnableVertexAttribArray(0); // atributul 0 = pozitie
	glVertexAttribPointer(0, 4, GL_FLOAT, GL_FALSE, 0, (GLvoid*)0);
	glEnableVertexAttribArray(1); // atributul 1 = culoare
	glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(GLfloat), (GLvoid*)sizeof(Vertices));
	glEnableVertexAttribArray(2); // atributul 2 = normala
	glVertexAttribPointer(2, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(GLfloat), (GLvoid*)(sizeof(Vertices) + sizeof(Colors)));
}
void DestroyVBO(void)
{
	glDisableVertexAttribArray(1);
	glDisableVertexAttribArray(0);
	glBindBuffer(GL_ARRAY_BUFFER, 0);
	glDeleteBuffers(1, &VboId);
	glDeleteBuffers(1, &EboId);
}
void CreateShadersVertex(void)
{
	ProgramIdv = LoadShaders("10_03v_Shader.vert", "10_03v_Shader.frag");
	glUseProgram(ProgramIdv);
}
void CreateShadersFragment(void)
{
	ProgramIdf = LoadShaders("10_03f_Shader.vert", "10_03f_Shader.frag");
	glUseProgram(ProgramIdf);
}
void DestroyShaders(void)
{
	glDeleteProgram(ProgramIdv);
	glDeleteProgram(ProgramIdf);
}
void Initialize(void)
{
	glClearColor(1.0f, 1.0f, 1.0f, 0.0f); // culoarea de fond a ecranului

	// Creare VBO+shader
	CreateVBO();

	CreateShadersFragment();
	// Locatii ptr shader
	lightColorLoc = glGetUniformLocation(ProgramIdv, "lightColor");
	lightPosLoc = glGetUniformLocation(ProgramIdv, "lightPos");
	viewPosLoc = glGetUniformLocation(ProgramIdv, "viewPos");
	viewLocation = glGetUniformLocation(ProgramIdv, "view");
	projLocation = glGetUniformLocation(ProgramIdv, "projection");

	CreateShadersVertex();
	// Locatii ptr shader
	lightColorLoc = glGetUniformLocation(ProgramIdv, "lightColor");
	lightPosLoc = glGetUniformLocation(ProgramIdv, "lightPos");
	viewPosLoc = glGetUniformLocation(ProgramIdv, "viewPos");
	viewLocation = glGetUniformLocation(ProgramIdv, "view");
	projLocation = glGetUniformLocation(ProgramIdv, "projection");

}
void reshapeFcn(GLint newWidth, GLint newHeight)
{
	glViewport(0, 0, newWidth, newHeight);
	winWidth = newWidth;
	winHeight = newHeight;
	width = winWidth / 10, height = winHeight / 10;
}
void RenderFunction(void)
{
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	glEnable(GL_DEPTH_TEST);

	// CreateVBO(); // decomentati acest rand daca este cazul 
	glBindVertexArray(VaoId);
	glBindBuffer(GL_ARRAY_BUFFER, VboId);
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EboId);

	//pozitia observatorului
	Obsx = Refx + dist * cos(alpha) * cos(beta);
	Obsy = Refy + dist * cos(alpha) * sin(beta);
	Obsz = Refz + dist * sin(alpha);

	// reperul de vizualizare + matricea de proiectie
	glm::vec3 Obs = glm::vec3(Obsx, Obsy, Obsz);   // se schimba pozitia observatorului	
	glm::vec3 PctRef = glm::vec3(Refx, Refy, Refz); // pozitia punctului de referinta
	glm::vec3 Vert = glm::vec3(Vx, Vy, Vz); // verticala din planul de vizualizare 
	view = glm::lookAt(Obs, PctRef, Vert);
	glUniformMatrix4fv(viewLocation, 1, GL_FALSE, &view[0][0]);
	projection = glm::infinitePerspective(fov, GLfloat(width) / GLfloat(height), znear);
	glUniformMatrix4fv(projLocation, 1, GL_FALSE, &projection[0][0]);

	// variable relevante pentru iluminare, de transferat in shader
	glUniform3f(lightColorLoc, 1.0f, 1.0f, 1.0f);
	glUniform3f(lightPosLoc, 0.f, 100.f, 100.f);
	glUniform3f(viewPosLoc, Obsx, Obsy, Obsz);

	switch (rendermode)
	{
	case Il_Frag:
		glUseProgram(ProgramIdf);
		break;
	case Il_Vert:
		glUseProgram(ProgramIdv);
		break;
	};

	// desenare
	for (int patr = 0; patr < (NR_PARR + 1) * NR_MERID; patr++)
	{
		if ((patr + 1) % (NR_PARR + 1) != 0) // nu sunt considerate fetele in care in stanga jos este Polul Nord
			glDrawElements(
				GL_QUADS,
				4,
				GL_UNSIGNED_SHORT,
				(GLvoid*)((2 * (NR_PARR + 1) * (NR_MERID)+4 * patr) * sizeof(GLushort)));
	}

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
	glutInitWindowSize(winWidth, winHeight);
	glutCreateWindow("Iluminarea unei sfere");
	glewInit();
	Initialize();
	glutDisplayFunc(RenderFunction);
	glutIdleFunc(RenderFunction);
	glutKeyboardFunc(processNormalKeys);
	glutSpecialFunc(processSpecialKeys);
	glutCreateMenu(menu);
	glutAddMenuEntry("Fragment", Il_Frag);
	glutAddMenuEntry("Varfuri", Il_Vert);
	glutAttachMenu(GLUT_RIGHT_BUTTON);
	glutReshapeFunc(reshapeFcn);
	glutCloseFunc(Cleanup);
	glutMainLoop();
}