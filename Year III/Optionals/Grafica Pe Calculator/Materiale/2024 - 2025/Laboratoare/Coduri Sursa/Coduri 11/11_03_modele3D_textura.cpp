//
// ================================================
// | Grafica pe calculator                        |
// ================================================
// | Laboratorul XI - 10_03_modele3D_textura.cpp |
// ===============================================
//
// Program care deseneaza un model 3D importat

// Biblioteci
#include <windows.h>  // biblioteci care urmeaza sa fie incluse
#include <stdio.h>
#include <stdlib.h> // necesare pentru citirea shader-elor
#include <cstdlib>
#include <vector>
#include <math.h>
#include <iostream>
#include <GL/glew.h> // glew apare inainte de freeglut
#include <GL/freeglut.h> // nu trebuie uitat freeglut.h

#include "loadShaders.h"

#include "glm/glm.hpp"
#include "glm/gtc/matrix_transform.hpp"
#include "glm/gtx/transform.hpp"
#include "glm/gtc/type_ptr.hpp"
#include "objloader.hpp"  
#include "SOIL.h"

//  Identificatorii obiectelor de tip OpenGL;
GLuint
  VaoId,
  VboId,
  ProgramId,
  nrVertLocation,
  myMatrixLocation,
  viewLocation,
  projLocation,
  texture;

// Valoarea lui pi
float PI = 3.141592;

// Variabila pentru numarul de varfuri
int nrVertices;

// Vectori pentru varfuri, coordonate de texturare, normale
std::vector<glm::vec3> vertices;
std::vector<glm::vec2> uvs;
std::vector<glm::vec3> normals;

// Matrice utilizate
glm::mat4 myMatrix;
glm::mat4 view;
glm::mat4 projection;

//	Elemente pentru matricea de vizualizare;
float refX = 0.0f, refY = 0.0f, refZ = 0.0f,
obsX, obsY, obsZ,
vX = 0.0f, vY = 0.0f, vZ = 1.0f;
//	Elemente pentru deplasarea pe sfera;
float alpha = 0.0f, beta = 0.0f, dist = 6.0f,
incrAlpha1 = 0.01, incrAlpha2 = 0.01;
//	Elemente pentru matricea de proiectie;
float width = 800, height = 600, dNear = 4.f, fov = 60.f * PI / 180;


void processNormalKeys(unsigned char key, int x, int y)
{
	switch (key) {
	case '-':
		dist -= 0.25;	//	apasarea tastelor `+` si `-` schimba pozitia observatorului (se departeaza / aproprie);
		break;
	case '+':
		dist += 0.25;
		break;
	}
	if (key == 27)
		exit(0);
}

void processSpecialKeys(int key, int xx, int yy)
{
	switch (key)				//	Procesarea tastelor 'LEFT', 'RIGHT', 'UP', 'DOWN';
	{							//	duce la deplasarea observatorului pe suprafata sferica in jurul cubului;
	case GLUT_KEY_LEFT:
		beta -= 0.01;
		break;
	case GLUT_KEY_RIGHT:
		beta += 0.01;
		break;
	case GLUT_KEY_UP:
		alpha += incrAlpha1;
		if (abs(alpha - PI / 2) < 0.05)
		{
			incrAlpha1 = 0.f;
		}
		else
		{
			incrAlpha1 = 0.01f;
		}
		break;
	case GLUT_KEY_DOWN:
		alpha -= incrAlpha2;
		if (abs(alpha + PI / 2) < 0.05)
		{
			incrAlpha2 = 0.f;
		}
		else
		{
			incrAlpha2 = 0.01f;
		}
		break;
	}
}

// Se initializeaza un vertex Buffer Object(VBO) pentru transferul datelor spre memoria placii grafice(spre shadere);
// In acesta se stocheaza date despre varfuri;
void CreateVBO(void)
{

// Generare VAO;
  glGenVertexArrays(1, &VaoId);
  glBindVertexArray(VaoId);

 // Generare VBO - varfurile si normalele sunt memorate in sub-buffere;
  glGenBuffers(1, &VboId);
  glBindBuffer(GL_ARRAY_BUFFER, VboId);
  glBufferData(GL_ARRAY_BUFFER, vertices.size() * sizeof(glm::vec3) + normals.size() * sizeof(glm::vec3) + uvs.size() * sizeof(glm::vec2), NULL, GL_STATIC_DRAW);
  glBufferSubData(GL_ARRAY_BUFFER, 0, vertices.size() * sizeof(glm::vec3), &vertices[0]);
  glBufferSubData(GL_ARRAY_BUFFER, vertices.size() * sizeof(glm::vec3), normals.size() * sizeof(glm::vec3), &normals[0]);
  glBufferSubData(GL_ARRAY_BUFFER, vertices.size() * sizeof(glm::vec3) + normals.size() * sizeof(glm::vec3), uvs.size() * sizeof(glm::vec2), &uvs[0]);

  // Atributele;
  glEnableVertexAttribArray(0); // atributul 0 = pozitie
  glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 0, (GLvoid*)0);
  glEnableVertexAttribArray(1); // atributul 1 = normale
  glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 0, (GLvoid*)(vertices.size() * sizeof(glm::vec3)));
  glEnableVertexAttribArray(2); // atributul 1 = coordonate de texturare
  glVertexAttribPointer(2, 2, GL_FLOAT, GL_FALSE, 0, (GLvoid*)(vertices.size() * sizeof(glm::vec3) + normals.size() * sizeof(glm::vec3)));
}

//  Eliminarea obiectelor de tip VBO dupa rulare;
void DestroyVBO(void)
{
  glDisableVertexAttribArray(0);
  glDisableVertexAttribArray(1);
  glBindBuffer(GL_ARRAY_BUFFER, 0);
  glBindVertexArray(0);
  glDeleteVertexArrays(1, &VaoId);
}

//	Functia de incarcare a texturilor in program;
void LoadTexture(const char* texturePath)
{
	// Generarea unui obiect textura si legarea acestuia;
	glGenTextures(1, &texture);
	glBindTexture(GL_TEXTURE_2D, texture);

	//	Desfasurarea imaginii pe orizontala/verticala in functie de parametrii de texturare;
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);

	// Modul in care structura de texeli este aplicata pe cea de pixeli;
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);

	// Incarcarea texturii si transferul datelor in obiectul textura;
	int width, height;
	unsigned char* image = SOIL_load_image(texturePath, &width, &height, 0, SOIL_LOAD_RGB);
	glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, width, height, 0, GL_RGB, GL_UNSIGNED_BYTE, image);
	glGenerateMipmap(GL_TEXTURE_2D);

	// Eliberarea resurselor
	SOIL_free_image_data(image);
	glBindTexture(GL_TEXTURE_2D, 0);
}

//  Crearea si compilarea obiectelor de tip shader;
void CreateShaders(void)
{
  ProgramId=LoadShaders("11_03_Shader.vert", "11_03_Shader.frag");
  glUseProgram(ProgramId);
}

// Elimina obiectele de tip shader dupa rulare;
void DestroyShaders(void)
{
  glDeleteProgram(ProgramId);
}

//  Functia de eliberare a resurselor alocate de program;
void Cleanup(void)
{
	DestroyShaders();
	DestroyVBO();
};

//  Setarea parametrilor necesari pentru fereastra de vizualizare;
void Initialize(void)
{
	glClearColor(0.95f, 0.82f, 0.4f, 1.0f); // culoarea de fond a ecranului

	// Incarcarea modelului 3D in format OBJ, trebuie sa fie in acelasi director cu proiectul actual;
	bool model = loadOBJ("tor.obj", vertices, uvs, normals);
	nrVertices = vertices.size();

	//	Incarcarea texturii;
	LoadTexture("texture_doughnut.jpg");

	// Crearea VBO / shadere-lor
	CreateVBO();
	CreateShaders();

	// Locatii ptr shader
	nrVertLocation = glGetUniformLocation(ProgramId, "nrVertices");
	myMatrixLocation = glGetUniformLocation(ProgramId, "myMatrix");
	viewLocation = glGetUniformLocation(ProgramId, "view");
	projLocation = glGetUniformLocation(ProgramId, "projection");

	// Variabile ce pot fi transmise catre shader
	glUniform1i(ProgramId, nrVertices);
}

//	Functia de desenare a graficii pe ecran;
void RenderFunction(void)
{
   // Initializare ecran + test de adancime;
   glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
   glEnable(GL_DEPTH_TEST);

   // Matricea de modelare
   myMatrix = glm::rotate(glm::mat4(1.0f), PI / 2, glm::vec3(0.0, 1.0, 0.0))
	   * glm::rotate(glm::mat4(1.0f), PI / 2, glm::vec3(0.0, 0.0, 1.0));
   glUniformMatrix4fv(myMatrixLocation, 1, GL_FALSE, &myMatrix[0][0]);

   //	Vizualizare;
   //	Pozitia observatorului - se deplaseaza pe sfera;
   obsX = refX + dist * cos(alpha) * cos(beta);
   obsY = refY + dist * cos(alpha) * sin(beta);
   obsZ = refZ + dist * sin(alpha);
   //	Vectori pentru matricea de vizualizare;
   glm::vec3 obs = glm::vec3(obsX, obsY, obsZ);		//	Pozitia observatorului;
   glm::vec3 pctRef = glm::vec3(refX, refY, refZ); 	//	Pozitia punctului de referinta;
   glm::vec3 vert = glm::vec3(vX, vY, vZ);			//	Verticala din planul de vizualizare;
   // Matricea de vizualizare, transmitere catre shader
   view = glm::lookAt(obs, pctRef, vert);
   glUniformMatrix4fv(viewLocation, 1, GL_FALSE, &view[0][0]);

   //	Proiectie;
   projection = glm::infinitePerspective(GLfloat(fov), GLfloat(width) / GLfloat(height), dNear);
   glUniformMatrix4fv(projLocation, 1, GL_FALSE, &projection[0][0]);

   // "Legarea"VAO, desenare;
   glBindVertexArray(VaoId);
   glEnableVertexAttribArray(0); // atributul 0 = pozitie
   glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 0, (GLvoid*)0);
   glEnableVertexAttribArray(1); // atributul 1 = normale
   glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 0, (GLvoid*)(vertices.size() * sizeof(glm::vec3)));
   glEnableVertexAttribArray(2); // atributul 1 = coordonate de texturare
   glVertexAttribPointer(2, 2, GL_FLOAT, GL_FALSE, 0, (GLvoid*)(vertices.size() * sizeof(glm::vec3) + normals.size() * sizeof(glm::vec3)));

   // TEXTURARE
   //
   // Activarea / legarea texturii active
   glActiveTexture(GL_TEXTURE0);
   glBindTexture(GL_TEXTURE_2D, texture);
   //	Transmiterea variabilei uniforme pentru texturare spre shaderul de fragmente;
   glUniform1i(glGetUniformLocation(ProgramId, "myTexture"), 0);


   glDrawArrays(GL_TRIANGLES, 0, vertices.size());

   glutSwapBuffers();
   glFlush ( );
}

//	Punctul de intrare in program, se ruleaza rutina OpenGL;
int main(int argc, char* argv[])
{
  glutInit(&argc, argv);
  glutInitDisplayMode(GLUT_RGBA|GLUT_DEPTH|GLUT_DOUBLE);
  glutInitWindowPosition (100,100);
  glutInitWindowSize(1200,900);
  glutCreateWindow("Utilizarea unui model predefinit in format OBJ");
  glewInit();
  Initialize( );
  glutIdleFunc(RenderFunction);
  glutDisplayFunc(RenderFunction);
  glutKeyboardFunc(processNormalKeys);
  glutSpecialFunc(processSpecialKeys);
  glutCloseFunc(Cleanup);
  glutMainLoop();
}

