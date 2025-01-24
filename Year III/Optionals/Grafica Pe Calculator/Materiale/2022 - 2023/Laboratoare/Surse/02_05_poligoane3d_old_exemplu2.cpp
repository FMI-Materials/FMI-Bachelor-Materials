/* ELEMENTE DE NOUTATE
- indicarea varfurilor in vectori
- utilizarea functiei de "mouse" glutMouseFunc
*/

#include <windows.h>
#include <gl/freeglut.h>


GLint winWidth = 600, winHeight = 600;
GLfloat xx0 = 13.0, yy0 = 11.0, zz0 = 14.0;
GLfloat xref = 3.0, yref = 1.0, zref = 4.0;
GLfloat Vx = 8.0, Vy = 0.0, Vz = -8.0;

int p1[] = { 6, 2, 0 };
int p2[] = { -4, 4, 8 };
int p3[] = { 0, 0, 8 };
int p4[] = { 2, 2, 4 };
int p5[] = { 10, -2, 0 };

GLfloat xwMin = -10.0, ywMin = -10.0, xwMax = 10.0, ywMax = 10.0;

GLfloat dnear = 0.0, dfar = 20.0;

void init(void)
{
	glClearColor(1.0, 1.0, 1.0, 0.0);

	// vizualizare
	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();
	gluLookAt(xx0, yy0, zz0, xref, yref, zref, Vx, Vy, Vz);

	// proiectie
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	glOrtho(xwMin, xwMax, ywMin, ywMax, dnear, dfar);
}

// poligonul p1p2p3p4
void desen1(void)
{
	glClear(GL_COLOR_BUFFER_BIT);

	glPolygonMode(GL_FRONT, GL_FILL);
	glPolygonMode(GL_BACK, GL_LINE);
	glLineWidth(6.0);
	glBegin(GL_POLYGON);
		glColor3f(1.0, 0.0, 0.0);
		glVertex3iv(p1);
		glColor3f(0.0, 1.0, 0.0);
		glVertex3iv(p2);
		glColor3f(0.0, 0.0, 1.0);
		glVertex3iv(p4);
		glColor3f(1.0, 1.0, 0.0);
		glVertex3iv(p3);
	glEnd();
	// SCHIMBA ODRINEA INTRE p3 SI p4!
	glFlush();
}

// POLIGONUL p1p2p3p5
void desen2(void)
{
	glClear(GL_COLOR_BUFFER_BIT);

	glPolygonMode(GL_FRONT, GL_FILL);
	glPolygonMode(GL_BACK, GL_LINE);
	glLineWidth(6.0);
	glBegin(GL_POLYGON);
		glColor3f(1.0, 0.0, 0.0);
		glVertex3iv(p1);
		glColor3f(0.0, 1.0, 0.0);
		glVertex3iv(p2);
		glColor3f(0.0, 0.0, 1.0);
		glVertex3iv(p3);
		glColor3f(1.0, 1.0, 0.0);
		glVertex3iv(p5);
	glEnd();
	glFlush();
}

void mouse2(int button, int state, int x, int y)
{
	switch (button) {
	case GLUT_LEFT_BUTTON:
		if (state == GLUT_DOWN)
			xx0 = 13.0, yy0 = 11.0, zz0 = 14.0;
		init();
		break;
	case GLUT_RIGHT_BUTTON:
		if (state == GLUT_DOWN)
			xx0 = -7.0, yy0 = -9.0, zz0 = -6.0;
		init();
		break;
	}
}
void reshapeFcn(GLint newWidth, GLint newHeight)
{
	glViewport(0, 0, newWidth, newHeight);

	winWidth = newWidth;
	winHeight = newHeight;
}
void main(int argc, char** argv)
{
	glutInit(&argc, argv);
	glutInitDisplayMode(GLUT_SINGLE | GLUT_RGB);
	glutInitWindowPosition(50, 50);
	glutInitWindowSize(winWidth, winHeight);
	glutCreateWindow("Poligoane in context 3D. Fata si spatele unui poligon");
	init();
	glutDisplayFunc (desen1);
	// De comentat linia anterioara si de executat urmatoarele doua linii
	// glutDisplayFunc(desen2);
	// glutMouseFunc(mouse2);
	glutMainLoop();
}
