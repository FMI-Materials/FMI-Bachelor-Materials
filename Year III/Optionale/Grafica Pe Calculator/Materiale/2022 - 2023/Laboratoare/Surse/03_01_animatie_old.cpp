/* DREPTUNGHI CU SATELIT -- o prima animatie
Elemente de noutate:
	- gluOrtho2D (indica dreptunghiul care este decupat) - DEPRECATED
	- glTranslate, glRotate, glPushMatrix, glPopMatrix (ptr. transformari; DEPRECATED)
	- glutSwapBuffers (v. GLUT_DOUBLE); glutPostRedisplay; glutIdleFunc (animatie)
*/
#include<windows.h>
#include <GL/freeglut.h>
#include <stdlib.h>
#include <math.h>

static GLdouble i = 0.0;
static GLdouble j = 0.0;
static GLdouble alpha = 1.0;
void init(void)
{
	glClearColor(1.0, 1.0, 1.0, 0.0);
	gluOrtho2D(0.0, 800.0, 0.0, 600.0);
}
void dreptunghi(void)
{
	glClear(GL_COLOR_BUFFER_BIT);
	glPushMatrix();
	// dreptunghiul rosu
	glTranslated(i, 200.0, 0.0);
	glPushMatrix();
	glRotated(j, 0.0, 0.0, 1.0);
	glColor3f(1.0, 0.0, 0.0);
	glRecti(-5, 30, 5, 40);
	glPopMatrix ( );
	glPopMatrix();
	glPushMatrix();
	// dreptunghiul albastru
	glTranslated (i, 200.0, 0.0);
	glColor3f(0.0, 0.0, 1.0);
	glRecti(-20, -12, 20, 12);
	glPopMatrix();
	glutSwapBuffers();
	glFlush();
}

void miscad(void)
{
	i = i + alpha;
	if (i > 750.0)
		alpha = -0.1;
	else if (i < 0.0)
		alpha = 0.1;
	j = j + 0.1;
	glutPostRedisplay();
}

void miscas(void)
{
	i = i + alpha;
	if (i < 0.0)
		alpha = 0.1;
	else if (i > 750.0)
		alpha = -0.1;
	j = j + 0.1;
	glutPostRedisplay();
}
void mouse(int button, int state, int x, int y)
{
	switch (button) {
	case GLUT_LEFT_BUTTON:
		if (state == GLUT_DOWN)
			alpha = -0.1; glutIdleFunc(miscas);
		break;
	case GLUT_RIGHT_BUTTON:
		if (state == GLUT_DOWN)
			alpha = 0.1; glutIdleFunc(miscad);
		break;
	default:
		break;
	}
}

void main(int argc, char** argv)
{
	glutInit(&argc, argv);
	glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGB);
	glutInitWindowSize(800, 600);
	glutInitWindowPosition(100, 100);
	glutCreateWindow("Dreptunghi cu satelit - OpenGL <<vechi>>");
	init();
	glutDisplayFunc(dreptunghi);
	glutMouseFunc(mouse);
	glutMainLoop();
}