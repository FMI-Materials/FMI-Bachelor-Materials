//
// ================================================
// | Grafica pe calculator                        |
// ================================================
// | Laboratorul III - 03_01_animatie_OLD.cpp |
// ============================================
//
//	Program ce deseneaza un dreptunghi ce se deplaseaza stanga-dreapta si are un patrat ce orbiteaza in jurul sau, folosindu-se tehnicile OLD OpenGL;
//  ELEMENTE DE NOUTATE:
//	- gluOrtho2D (indica dreptunghiul care este decupat) - DEPRECATED
//	- glTranslate, glRotate, glPushMatrix, glPopMatrix (pentru transformari; DEPRECATED)
//	- glutSwapBuffers (v. GLUT_DOUBLE); glutPostRedisplay; glutIdleFunc (animatie)
//
//
//	Biblioteci

#include <windows.h>        //	utilizarea functiilor de sistem Windows (crearea de ferestre, manipularea fisierelor si directoarelor);
#include <GL/freeglut.h>    //	include functii pentru: 
							//	- gestionarea ferestrelor si evenimentelor de tastatura si mouse, 
							//  - desenarea de primitive grafice precum dreptunghiuri, cercuri sau linii, 
							//  - crearea de meniuri si submeniuri;

static GLdouble i = 0.0;		//	coordonata de deplasare pe Ox a dreptunghiurilor;
static GLdouble j = 0.0;		//	unghiul de rotatie al dreptunghului rosu;
static GLdouble alpha = 1.0;	//	reda sensul de deplasare pe axa Ox a dreptunghiurilor (stanga/dreapta);
//	Dimensiunea ferestrei de vizualizare;
GLint winWidth = 800, winHeight = 600;
//	Parametri pentru glOrtho2D() - decupare;
GLfloat xMin = 0, yMin = 0, xMax = 800.0, yMax = 600.0;

//  Setarea parametrilor necesari pentru fereastra de vizualizare
void Initialize(void)
{
	glClearColor(1.0, 1.0, 1.0, 0.0);			//  Culoarea de fond a ecranului;
	gluOrtho2D(xMin, xMax, yMin, yMax);			//  Sunt indicate coordonatele extreme ale ferestrei de vizualizare;
}

// Functia de desenarea a graficii pe ecran;
void RenderFunction(void)
{
	glClear(GL_COLOR_BUFFER_BIT);		//  Se curata ecranul de vizualizare pentru a fi desenat noul continut;
	
	//  Dreptunghiul ROSU asupra caruia se aplica tranformari: rotatie si translatie;
	//  Se translateaza dreptunghiul - se adauga in matricea de transformare;
	glPushMatrix();
	glTranslated(i, 200.0, 0.0);	
	//  Se roteste dreptunghiul - se adauga in matricea de transformare;
	glPushMatrix();
	glRotated(j, 0.0, 0.0, 1.0);
	//	Se deseneaza dreptunghiul;
	glColor3f(1.0, 0.0, 0.0);
	glRecti(-5, 30, 5, 40);		
	//	Se curata matricea pentru transformarile ulterioare - se elimina fiecare transformare in parte;
	glPopMatrix();
	glPopMatrix();
	

	//	Dreptunghiul ALBASTRU asupra caruia se aplica tranformari: translatie;
	//  Se translateaza dreptunghiul - se adauga in matricea de transformare;
	glPushMatrix();
	glTranslated (i, 200.0, 0.0);
	//	Se deseneaza dreptunghiul;
	glColor3f(0.0, 0.0, 1.0);
	glRecti(-20, -12, 20, 12);		
	glPopMatrix();

	glutSwapBuffers();	//	Inlocuieste imaginea deseneata in fereastra cu cea randata; 
	glFlush();			//  Asigura rularea tuturor comenzilor OpenGL apelate anterior;
}

//	Schimba sensul animatiei spre dreapta;
void MoveRight(void)
{
	i = i + alpha;
	if (i > xMax - 20)		//	Se asigura deplasarea stanga-dreapta pe Ox in limitele ecranului,
		alpha = -0.1;		//	mai intai efectuandu-se deplasarea spre DREAPTA;
	else if (i < xMin + 20)
		alpha = 0.1;
	j = j + 0.1;			//	Se actualizeaza unghiul de rotatie constant (mentine orbitarea);
	glutPostRedisplay();	//	Forteza redesenarea scenei;
}

//	Schimba sensul animatiei spre stanga;
void MoveLeft(void)
{
	i = i + alpha;
	if (i < xMin + 20)		//	Se asigura deplasarea stanga-dreapta pe Ox in limitele ecranului,
		alpha = 0.1;		//	mai intai efectuandu-se deplasarea spre STANGA;
	else if (i > xMax - 20)
		alpha = -0.1;
	j = j + 0.1;			//	Se actualizeaza unghiul de rotatie constant (mentine orbitarea);
	glutPostRedisplay();	//	Forteza redesenarea scenei;
}

//	Functie ce modifica deplasarea dreptunghiurilor in functie de apasarea butoanelor de pe mouse;
void UseMouse(int button, int state, int x, int y)
{
	switch (button) {
	case GLUT_LEFT_BUTTON:			//	CLICK stanga => dreptunghiurile se misca spre stanga;
		if (state == GLUT_DOWN)
			alpha = -0.1;			
		glutIdleFunc(MoveLeft);		
		break;
	case GLUT_RIGHT_BUTTON:			//	CLICK dreapta => dreptunghiurile se misca spre drepta;
		if (state == GLUT_DOWN)
			alpha = 0.1; 
		glutIdleFunc(MoveRight);
		break;
	default:
		break;
	}
}

//	Punctul de intrare in program, se ruleaza rutina OpenGL;
int main(int argc, char** argv)
{
	//  Se initializeaza GLUT si contextul OpenGL si se configureaza fereastra si modul de afisare;

	glutInit(&argc, argv);
	glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGB);					//	Se folosesc 2 buffere (unul pentru afisare si unul pentru randare => animatii cursive) si culori RGB;
	glutInitWindowPosition(100, 100);								//  Pozitia initiala a ferestrei;
	glutInitWindowSize(winWidth, winHeight);						//  Dimensiunea ferestrei;
	glutCreateWindow("Dreptunghi cu satelit - OpenGL <<vechi>>");	//	Creeaza fereastra de vizualizare, indicand numele acesteia;

	Initialize();						//  Setarea parametrilor necesari pentru fereastra de vizualizare; 
	
	glutDisplayFunc(RenderFunction);	//  Desenarea scenei in fereastra;
	glutMouseFunc(UseMouse);			//	Activarea utilizarii mouseului;

	//  Bucla principala de procesare a evenimentelor GLUT (functiile care incep cu glut: glutInit etc.) este pornita;
	//  Prelucreaza evenimentele si deseneaza fereastra de vizualizare pana cand utilizatorul o inchide;

	glutMainLoop();

	return 0;
}