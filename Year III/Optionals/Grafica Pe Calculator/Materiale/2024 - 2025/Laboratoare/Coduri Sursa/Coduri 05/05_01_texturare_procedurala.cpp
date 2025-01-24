//
// ================================================
// | Grafica pe calculator                        |
// ================================================
// | Curs VI - 05_01_texturare_procedurala.cpp |
// ========================================
// 
//	Program ce deseneaza patrulatere, carora li se aplica o textura, folosindu-se tehnicile MODERN OpenGL;
//	ELEMENTE DE NOUTATE:
//	- utilizarea texturilor generate procedural;
//	- functii pentru reperul de vizualizare (glm::lookAt) si pentru proiectii.
//
//
#include <windows.h>        //	Utilizarea functiilor de sistem Windows (crearea de ferestre, manipularea fisierelor si directoarelor);
#include <stdlib.h>         //  Biblioteci necesare pentru citirea shaderelor;
#include <stdio.h>
#include <GL/glew.h>        //  Definește prototipurile functiilor OpenGL si constantele necesare pentru programarea OpenGL moderna; 
#include <GL/freeglut.h>    //	Include functii pentru: 
                            //	- gestionarea ferestrelor si evenimentelor de tastatura si mouse, 
                            //  - desenarea de primitive grafice precum dreptunghiuri, cercuri sau linii, 
                            //  - crearea de meniuri si submeniuri;
#include "loadShaders.h"	//	Fisierul care face legatura intre program si shadere;
#include "glm/glm.hpp"		//	Bibloteci utilizate pentru transformari grafice;
#include "glm/gtc/matrix_transform.hpp"
#include "glm/gtx/transform.hpp"
#include "glm/gtc/type_ptr.hpp"
#include "SOIL.h"			//	Biblioteca pentru texturare;

//  Identificatorii obiectelor de tip OpenGL;
GLuint
  VaoId,
  VboId,
  EboId,
  ProgramId,
  viewMatrixLocation,
  projectionMatrixLocation,
  codColLocation;

//	Variabile catre matricile de transformare;
glm::mat4 
    view, projection; 
 
//	Elemente pentru matricea de proiectie
GLfloat 
    fov=70.f, znear=1.0f, width = 1000, height = 800;

// Matrice pentru generarea procedurala a texturii
#define	checkImageWidth 64
#define	checkImageHeight 64
static GLubyte checkImage[checkImageHeight][checkImageWidth][4];
static GLuint texName;

// Functia de generare a texturii de tip tabla de sah
void makeCheckImage(void)
 {
     int i, j, c;

     for (i = 0; i < checkImageHeight; i++) {
         for (j = 0; j < checkImageWidth; j++) {
             c = ((((i & 0x8) == 0) ^ ((j & 0x8)) == 0)) * 255;

             checkImage[i][j][0] = (GLubyte)c;
             checkImage[i][j][1] = (GLubyte)c;
             checkImage[i][j][2] = (GLubyte)c;
             checkImage[i][j][3] = (GLubyte)255;
         }
     }
 }

//	Functia de incarcare a texturilor in program;
void LoadTexture()
{
    makeCheckImage();
    glPixelStorei(GL_UNPACK_ALIGNMENT, 1);
    glGenTextures(1, &texName);
    glBindTexture(GL_TEXTURE_2D, texName);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
    glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, checkImageWidth, checkImageHeight,
        0, GL_RGBA, GL_UNSIGNED_BYTE, checkImage);
}

//  Se initializeaza un Vertex Buffer Object (VBO) pentru tranferul datelor spre memoria placii grafice (spre shadere);
//  In acesta se stocheaza date despre varfuri (coordonate, culori, indici, texturare etc.);
void CreateVBO(void)
{
  // varfurile 
    GLfloat   Vertices[] = {
        // coordonate varfuri           // coord texturare
        -1.7f, -0.8f,      0.0f, 1.0f,  0.0f, 0.0f, // primul patrulater
        -0.1f, -0.8f,      0.0f, 1.0f,  0.0f, 1.0f,
        -0.1f,  0.8f,      0.0f, 1.0f,  1.0f, 1.0f,
        -1.7f,  0.8f,      0.0f, 1.0f,  1.0f, 0.0f,
         1.0f, -1.6f,     -3.0f, 1.0f,  0.0f, 0.0f, // al doilea patrulater
     2.41421f, -1.6f, -1.41421f, 1.0f,  1.0f, 0.0f,
     2.41421f,  1.6f, -1.41421f, 1.0f,  1.0f, 1.0f,
         1.0f,  1.6f,     -3.0f, 1.0f,  0.0f, 1.0f
  };
 
    GLuint Indices[] = {
      0, 1, 2,  
      0, 2, 3,  
      4, 5, 6,
      4, 6, 7
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
    // varfurile sunt "copiate" in bufferul curent
    glBufferData(GL_ARRAY_BUFFER, sizeof(Vertices), Vertices, GL_STATIC_DRAW);

    // legarea buffer-ului "Element" (indicii)
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EboId);
    // indicii sunt "copiati" in bufferul curent
    glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(Indices), Indices, GL_STATIC_DRAW);

     // se activeaza lucrul cu atribute; atributul 0 = pozitie
    glEnableVertexAttribArray(0);
    glVertexAttribPointer(0, 4, GL_FLOAT, GL_FALSE, 6 * sizeof(GLfloat), (GLvoid*)0);
 
    // se activeaza lucrul cu atribute; atributul 1 = coordonate de texturare
    glEnableVertexAttribArray(1);
    glVertexAttribPointer(1, 2, GL_FLOAT, GL_FALSE, 6 * sizeof(GLfloat), (GLvoid*)(4 * sizeof(GLfloat)));
 }

//  Eliminarea obiectelor de tip VBO dupa rulare;
void DestroyVBO(void)
{
  glDisableVertexAttribArray(1);
  glDisableVertexAttribArray(0);
  glBindBuffer(GL_ARRAY_BUFFER, 0);
  glDeleteBuffers(1, &VboId);
  glBindVertexArray(0);
  glDeleteVertexArrays(1, &VaoId);
  glDeleteBuffers(1, &EboId);
}

// Crearea si compilarea obiectelor de tip shader;
//	Trebuie sa fie in acelasi director cu proiectul actual;
//  Shaderul de varfuri / Vertex shader - afecteaza geometria scenei;
//  Shaderul de fragment / Fragment shader - afecteaza culoarea pixelilor;
void CreateShaders(void)
{
  ProgramId=LoadShaders("05_01_Shader.vert", "05_01_Shader.frag");
  glUseProgram(ProgramId);
}

//  Elimina obiectele de tip shader dupa rulare;
void DestroyShaders(void)
{
  glDeleteProgram(ProgramId);
}

//  Functia de eliberare a resurselor alocate de program;
void Cleanup(void)
{
    DestroyShaders();
    DestroyVBO();
    glDeleteTextures(1, &texName);
}

//  Setarea parametrilor necesari pentru fereastra de vizualizare;
void Initialize(void)
{
   glClearColor(0.0f, 0.1f, 9.0f, 0.0f); 
   CreateVBO();
   CreateShaders();
}

// Functie pentru crearea unui viewport - asigura pastrarea dimensiunilor din figura
void reshape(int w, int h)
{
    glViewport(0, 0, (GLsizei)w, (GLsizei)h);
    projection = glm::infinitePerspective(fov, (GLfloat)w / (GLfloat)h, znear);
    projectionMatrixLocation = glGetUniformLocation(ProgramId, "projectionMatrix");
    glUniformMatrix4fv(projectionMatrixLocation, 1, GL_FALSE, &projection[0][0]);
}

//  Functia de desenare a graficii pe ecran;
void RenderFunction(void)
{
    glClear(GL_COLOR_BUFFER_BIT);

    // Setarea parametrilor pentru vizaulizare
    view = glm::lookAt(glm::vec3(0.0f, 0.0f, 3.f), 
  		   glm::vec3(0.0f, 0.0f, -20.0f), 
  		   glm::vec3(0.0f, 1.0f, 0.0f));  
    viewMatrixLocation = glGetUniformLocation(ProgramId, "viewMatrix");
    glUniformMatrix4fv(viewMatrixLocation, 1, GL_FALSE,  &view[0][0]);
    
    // Incarcarea texturii si transmiterea catre shader
    LoadTexture();
    glUniform1i(glGetUniformLocation(ProgramId, "myTexture"), 0);

    // Desenarea primitivelor
    glDrawElements(GL_TRIANGLES, 12, GL_UNSIGNED_INT, 0);
 
    glutPostRedisplay();
    glFlush ( );
}

int main(int argc, char* argv[])
{
    glutInit(&argc, argv);
    glutInitDisplayMode(GLUT_SINGLE|GLUT_RGB);
    glutInitWindowPosition (100,100); 
    glutInitWindowSize(800,600); 
    glutCreateWindow("Texturare 2D procedurala"); 
    glewInit(); 
    Initialize( );
    glutDisplayFunc(RenderFunction);
    glutReshapeFunc(reshape);
    glutCloseFunc(Cleanup);
    glutMainLoop();
}
