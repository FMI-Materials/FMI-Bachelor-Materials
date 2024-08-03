/* COORDONATE OMOGENE
 - ilustrarea coordonatelor omogene
*/
#include <windows.h>
#include <stdlib.h>
#include <stdio.h>
#include <GL/glew.h>
#include <GL/freeglut.h>
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
  matrLocation;
float xmin = -400.f, xmax = 400.f, ymin = -400.f, ymax = 400.f;
glm::mat4 matr;

void CreateVBO(void)
{
  // varfurile 
  GLfloat Vertices[] = {
    -100, -100, 0, 1, // primele 4 varfuri (0..3): a 4a coordonata 1
    100, -100, 0, 1,
    100, 100, 0, 1,
    -100, 100, 0, 1,
    //
    -100, -100, 0, 0.0, // al 5-lea varf (4) (stanga jos): a 4a coordonata 0
    //
    -100, -100, 0, 0.5,  // urmatoarele 4 varfuri(5..8): a 4a coordonata 0.5
    100, -100, 0, 0.5,
    100, 100, 0, 0.5,
    -100, 100, 0, 0.5,
  };

  // culorile, ca atribute ale varfurilor
  GLfloat Colors[] = {
    1.0f, 0.0f, 0.0f, 1.0f,
    1.0f, 0.0f, 0.0f, 1.0f,
    1.0f, 0.0f, 0.0f, 1.0f,
    1.0f, 0.0f, 0.0f, 1.0f,
    //
    1.0f, 0.0f, 0.0f, 1.0f,
    //
    0.0f, 0.0f, 1.0f, 1.0f,
    0.0f, 0.0f, 1.0f, 1.0f,
    0.0f, 0.0f, 1.0f, 1.0f,
    0.0f, 0.0f, 1.0f, 1.0f,
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
  ProgramId=LoadShaders("05_01_Shader.vert", "05_01_Shader.frag");
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
  matrLocation = glGetUniformLocation(ProgramId, "myMatrix");
}
void RenderFunction(void)
{
  glClear(GL_COLOR_BUFFER_BIT);
  matr = glm::ortho(xmin, xmax, ymin, ymax);
  glUniformMatrix4fv(matrLocation, 1, GL_FALSE, &matr[0][0]);
  glLineWidth(5.0);
  glPolygonMode(GL_FRONT_AND_BACK,GL_LINE);
  // varfurile rosii
  glDrawArrays(GL_LINE_LOOP, 1, 4);
  // varfurile albastre
  glDrawArrays(GL_LINE_LOOP, 5, 4);
  glFlush ( );
}
void Cleanup(void)
{
  DestroyShaders();
  DestroyVBO();
}

int main(int argc, char* argv[])
{
  glutInit(&argc, argv);
  glutInitDisplayMode(GLUT_SINGLE|GLUT_RGB);
  glutInitWindowPosition (100,100); 
  glutInitWindowSize(600,600); 
  glutCreateWindow("Coordonate omogene"); 
  glewInit(); 
  Initialize( );
  glutDisplayFunc(RenderFunction);
  glutCloseFunc(Cleanup);
  glutMainLoop();
}

