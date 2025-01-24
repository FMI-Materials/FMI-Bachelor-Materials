#include <windows.h>
#include <gl/freeglut.h>

void init (void)  // initializare fereastra de vizualizare
{
	glClearColor (1.0, 1.0, 1.0, 0.0); // precizeaza culoarea de fond a ferestrei de vizualizare

    glMatrixMode (GL_PROJECTION);  // se precizeaza este vorba de o reprezentare 2D, realizata prin proiectie ortogonala
	gluOrtho2D (0, 800.0, 0.0, 700.0); // sunt indicate coordonatele extreme ale ferestrei de vizualizare
}

void desen (void) // procedura desenare  
{
	// dreptunghi: desenare directa
	glColor3f (0.0, 0.0, 1.0);
	glRecti (20, 130, 140, 310); 
	 
 
    //poligon convex
   glColor3f (1.0, 0.0, 0.0);  
   glBegin (GL_POLYGON);  
       glVertex2i (0,0);
	   glVertex2i (100, 10);
	   glVertex2i (200, 120);
	   glVertex2i (155, 290);
   glEnd ( );

   


    // evantai de triunghiuri
   glColor3d (1.0, 0.0, 0.25);  
       glBegin (GL_TRIANGLE_FAN);
	   glVertex2i (250, 300);
       glVertex2i (50, 300);
	   glVertex2i (200, 350);
	   glVertex2i (250, 500);
	   glVertex2i (350, 200);
   glEnd ( );

   // reuniune de triunghiuri
   glColor3d (1.0, 0.75, 0.25);  
       glBegin (GL_TRIANGLE_STRIP);
	   glVertex2i (650, 300);
       glVertex2i (450, 300);
	   glVertex2i (600, 350);
	   glVertex2i (650, 500);
	   glVertex2i (750, 200);
   glEnd ( );

   glFlush ( ); // proceseaza procedurile OpenGL cat mai rapid
}

void desen2 (void)
{

	glColor3f (1,0,0);
	glRecti (-30, 20, 40, 10);
	// 
	glColor3f (1,1,0);
	glMatrixMode (GL_MODELVIEW);
	glPushMatrix();
	glTranslatef (-10.0, -20.0, 0.0);
	glScalef (0.5, 2.0, 0.0);
	glRecti (-30, 20, 40, 10);
	glPopMatrix();

	glPointSize (4.0);
	glColor3f(0,0,0);
	glBegin(GL_POINTS);
	glVertex3f(40,20,0);
	glEnd();

	glPointSize (8.0);
	glColor3f(0,0,0);
	glBegin(GL_POINTS);
	glVertex3f(10,20,0);
	glEnd();

	glFlush ( ); 

}
void main (int argc, char** argv)
{
	glutInit (&argc, argv); // initializare GLUT
	glutInitDisplayMode (GLUT_SINGLE | GLUT_RGB); // se utilizeaza un singur buffer | modul de colorare RedGreenBlue (= default)
	glutInitWindowPosition (100, 100); // pozitia initiala a ferestrei de vizualizare (in coordonate ecran)
	glutInitWindowSize (800, 600); // dimensiunile ferestrei 
	glutCreateWindow ("Poligoane"); // creeaza fereastra, indicand numele ferestrei de vizualizare - apare in partea superioara

	init (); // executa procedura de initializare
	glClear (GL_COLOR_BUFFER_BIT); // reprezentare si colorare fereastra de vizualizare
	glutDisplayFunc (desen); // procedura desen este invocata ori de cate ori este nevoie
	glutMainLoop ( ); // ultima instructiune a programului, asteapta (eventuale) noi date de intrare
}