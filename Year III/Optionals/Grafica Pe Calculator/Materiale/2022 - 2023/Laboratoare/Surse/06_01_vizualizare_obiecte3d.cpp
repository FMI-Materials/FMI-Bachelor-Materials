#include <windows.h>
#include <gl/freeglut.h>

GLint winWidth = 600, winHeight = 600;
GLfloat x0 = 6.0, y0 = 9.0, z0 = 10.0;
GLfloat xref = 0.0, yref = 0.0, zref = 0.0;
GLfloat Vx = 0.0, Vy = 0.0, Vz = 1.0;

GLfloat xwMin = -20.0, ywMin = -20.0, xwMax = 20.0, ywMax = 20.0;

GLfloat dnear = 1.0, dfar = 40.0;

void init (void)
{
	glClearColor (1.0, 1.0, 1.0, 0.0);

	glMatrixMode (GL_MODELVIEW);
	gluLookAt (x0, y0, z0, xref, yref, zref, Vx, Vy, Vz);

	glMatrixMode (GL_PROJECTION);
	glOrtho (xwMin, xwMax, ywMin, ywMax, dnear, dfar);
}

void displayFcn (void)
{
	glClear (GL_COLOR_BUFFER_BIT);
    // SFERA
	glColor3f (0.0, 0.0, 1.0);
    glutWireSphere (8.0, 100, 10);
	// CON
	glColor3f (1.0, 0.0, 0.0);
	glPushMatrix ( );
	 glTranslatef (-15.0, 4.0, -20.0);
	//glScaled (2.2, 2.2, 2.2);
	glutWireCone (5.0, 10.0, 50, 70);
	glPopMatrix ( );
    // TOR
	glColor3f (0.0, 1.0, 0.0);
	glPushMatrix ( );
    glTranslatef (-5.0, -10.0, -15.0);
    glutWireTorus (3.0, 7.0, 40, 60);
	glPopMatrix ( );
	// CEAINIC
	glColor3f (1.0, 0.0, 1.0);
	glPushMatrix ( );
	glTranslatef (-5.0, 0.0, 0.0);
	glutWireTeapot (2.0);
	glPopMatrix ( );
    // CILINDRU
	glColor3d (0.2, 0.0, 0.6);
	GLUquadricObj *cylinder;
	glPushMatrix ( );
	glTranslatef (-15.0, 10.0, -18.0);
	cylinder = gluNewQuadric ( );
	gluQuadricDrawStyle (cylinder, GLU_SILHOUETTE);
	gluCylinder (cylinder, 3.0, 3.0, 5.0, 40, 20);
	glPopMatrix ( );
	// AXELE
	glColor3f (0.0, 0.0, 0.0);
	// glLineWidth (1.5);
	glBegin (GL_LINES);
		glVertex3i (0, 0, 0);
		glVertex3i (20, 0, 0);
		glVertex3i (0, 0, 0);
		glVertex3i (0, 20, 0);
		glVertex3i (0, 0, 0);
		glVertex3i (0, 0, 20);
	glEnd ( );

	glFlush ( );
}

void reshapeFcn (GLint newWidth, GLint newHeight)
{
	glViewport (0, 0, newWidth,newHeight);

	winWidth = newWidth;
	winHeight = newHeight;
}
void main (int argc, char** argv)
{
	glutInit (&argc, argv);
	glutInitDisplayMode (GLUT_SINGLE | GLUT_RGB);
	glutInitWindowPosition (50, 50);
	glutInitWindowSize (winWidth, winHeight);
	glutCreateWindow ("Obiecte 3D");

	init ( );
	glutDisplayFunc (displayFcn);
	glutReshapeFunc (reshapeFcn);
	glutMainLoop ( );
}

