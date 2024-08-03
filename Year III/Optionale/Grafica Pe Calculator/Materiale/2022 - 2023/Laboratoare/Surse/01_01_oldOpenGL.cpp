// Codul sursa este adaptat dupa OpenGLBook.com

#include <windows.h>  // biblioteci care urmeaza sa fie incluse
#include <GL/freeglut.h> // nu trebuie uitat freeglut.h
  
 
void Initialize(void)
{
  glClearColor(0.0f, 0.0f, 0.0f, 0.0f); // culoarea de fond a ecranului
}
void RenderFunction(void)
{
  glClear(GL_COLOR_BUFFER_BIT);

  glPointSize(20.0);
  glBegin(GL_TRIANGLES);
	  // primul varf
	  glColor4f( 1.0f, 0.0f, 0.0f, 1.0f);
	  glVertex4f(-0.8f, -0.8f, 0.0f, 1.0f);
	  // al doilea varf
	  glColor4f(0.0f, 1.0f, 0.0f, 1.0f);
	  glVertex4f(0.0f,  0.8f, 0.0f, 1.0f);
	  // al treilea varf
	  glColor4f(0.0f, 0.0f, 1.0f, 1.0f);
	  glVertex4f(0.8f, -0.8f, 0.0f, 1.0f);
  glEnd( );
  glFlush ( );
}


int main(int argc, char* argv[])
{

  glutInit(&argc, argv);
  glutInitDisplayMode(GLUT_SINGLE|GLUT_RGB);
  glutInitWindowPosition (100,100); // pozitia initiala a ferestrei
  glutInitWindowSize(500,350); //dimensiunile ferestrei
  glutCreateWindow("Primul triunghi - OpenGL <<vechi>>"); // titlul ferestrei
  Initialize( );
  glutDisplayFunc(RenderFunction);
  glutMainLoop();
  
  
}