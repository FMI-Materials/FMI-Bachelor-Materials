//
// =================================================
// | Grafica pe calculator                         |
// =================================================
// | Laboratorul I - 01_01_contur_triunghi_OLD.cpp |
// =================================================
//	
//  Prezentul cod sursa este adaptat dupa OpenGLBook.com;
//  Program ce deseneaza conturul unui triunghi, folosidu-se tehnicile OLD OpenGL;
//
//
//  Biblioteci

#include <windows.h>        //	Utilizarea functiilor de sistem Windows (crearea de ferestre, manipularea fisierelor si directoarelor);
#include <GL/freeglut.h>    //	Include functii pentru: 
                            //	- gestionarea ferestrelor si evenimentelor de tastatura si mouse, 
                            //  - desenarea de primitive grafice precum dreptunghiuri, cercuri sau linii, 
                            //  - crearea de meniuri si submeniuri;
  

//  Setarea parametrilor necesari pentru fereastra de vizualizare - culoare fundal;
void Initialize(void)
{
    glClearColor(0.0f, 0.0f, 0.0f, 0.0f);   //  Culoarea de fond a ecranului;
}

//  Functia de desenarea a graficii pe ecran;
void RenderFunction(void)
{
    glClear(GL_COLOR_BUFFER_BIT);   //  Se curata ecranul de vizualizare pentru a fi desenat noul continut;
    glPointSize(20.0);              //  Se seteaza dimensiunea punctelor;

    //  Definirea primitivei geometrice si desenarea acesteia - conturul unui triunghi;
    //  Functia glBegin(arg) primeste un argument care specifica tipul primitivei desenate - linie;
    //  Finalizarea desenarii primitivei este marcata de glEnd;

    glBegin(GL_POINTS);
    // Primul varf
        glColor4f( 1.0f, 0.0f, 0.0f, 1.0f);     //  Culoarea punctului in sistemul RGB;
        glVertex4f(-0.8f, -0.8f, 0.0f, 1.0f);   //  Coordonatele punctului;
        
    // Al doilea varf
        glColor4f(0.0f, 1.0f, 0.0f, 1.0f);
        glVertex4f(0.0f,  0.8f, 0.0f, 1.0f);
        
    // Al treilea varf
        glColor4f(0.0f, 0.0f, 1.0f, 1.0f);
        glVertex4f(0.8f, -0.8f, 0.0f, 1.0f);
    glEnd( );

    glFlush ( );    //  Asigura rularea tuturor comenzilor OpenGL apelate anterior;
}

//	Punctul de intrare in program, se ruleaza rutina OpenGL;
int main(int argc, char* argv[])
{
    //  Se initializeaza GLUT si contextul OpenGL si se configureaza fereastra si modul de afisare;

    glutInit(&argc, argv);
    glutInitDisplayMode(GLUT_SINGLE|GLUT_RGB);              //	Modul de afisare al ferestrei, se foloseste un singur buffer de afisare si culori RGB;
    glutInitWindowPosition (100,100);                       //  Pozitia initiala a ferestrei;
    glutInitWindowSize(700,500);                            //  Dimensiunea ferestrei;
    glutCreateWindow("Varfuri triunghi - OpenGL <<vechi>>"); //	Creeaza fereastra de vizualizare, indicand numele acesteia;

    Initialize( );                      //  Setarea parametrilor necesari pentru fereastra de vizualizare - culoare fundal; 
    glutDisplayFunc(RenderFunction);    //  Desenarea scenei in fereastra;    

    //  Bucla principala de procesare a evenimentelor GLUT (functiile care incep cu glut: glutInit etc.) este pornita;
    //  Prelucreaza evenimentele si deseneaza fereastra de vizualizare pana cand utilizatorul o inchide;
    
    glutMainLoop();
  
    return 0;
}