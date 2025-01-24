//
// ================================================
// | Grafica pe calculator                        |
// ================================================
// | Cursul IV - 04_01_coord_omogene.cpp      |
// ===========================================
// 
//	Program ce deseneaza 2 patrate concentrice, folosindu-se tehnicile MODERN OpenGL;
//	ELEMENTE DE NOUTATE:
//	- coordonate omogene;
//
//
// 
//	Biblioteci

#include <windows.h>        //	Utilizarea functiilor de sistem Windows (crearea de ferestre, manipularea fisierelor si directoarelor);
#include <stdlib.h>         //  Biblioteci necesare pentru citirea shaderelor;
#include <stdio.h>
#include <GL/glew.h>        //  Defineste prototipurile functiilor OpenGL si constantele necesare pentru programarea OpenGL moderna; 
#include <GL/freeglut.h>    //	Include functii pentru: 
                            //	- gestionarea ferestrelor si evenimentelor de tastatura si mouse, 
                            //  - desenarea de primitive grafice precum dreptunghiuri, cercuri sau linii, 
                            //  - crearea de meniuri si submeniuri;
#include "loadShaders.h"	//	Fisierul care face legatura intre program si shadere;
#include "glm/glm.hpp"		//	Bibloteci utilizate pentru transformari grafice;
#include "glm/gtc/matrix_transform.hpp"
#include "glm/gtx/transform.hpp"
#include "glm/gtc/type_ptr.hpp"

//  Identificatorii obiectelor de tip OpenGL;
GLuint
    VaoId, 
    VboId,
    ColorBufferId,
    ProgramId,
    myMatrixLocation;
//	Dimensiunile ferestrei de afisare;
GLfloat
    winWidth = 600, winHeight = 600;
//	Variabile catre matricile de transformare;
glm::mat4 
    myMatrix, resizeMatrix;
//	Variabile pentru proiectia ortogonala;
float xMin = -400.f, xMax = 400.f, yMin = -400.f, yMax = 400.f;

//  Crearea si compilarea obiectelor de tip shader;
//	Trebuie sa fie in acelasi director cu proiectul actual;
//  Shaderul de varfuri / Vertex shader - afecteaza geometria scenei;
//  Shaderul de fragment / Fragment shader - afecteaza culoarea pixelilor;
void CreateShaders(void)
{
    ProgramId = LoadShaders("04_01_Shader.vert", "04_01_Shader.frag");
    glUseProgram(ProgramId);
}

//  Se initializeaza un Vertex Buffer Object (VBO) pentru transferul datelor spre memoria placii grafice (spre shadere);
//  In acesta se stocheaza date despre varfuri (coordonate, culori, indici, texturare etc.);
void CreateVBO(void)
{
    //  Coordonatele varfurilor;
    GLfloat Vertices[] = {
        -100, -100, 0, 1.0,       //  Primele 4 varfuri (0...3) au a 4a coordonata 1;
         100, -100, 0, 1.0,
         100,  100, 0, 1.0,
        -100,  100, 0, 1.0,
    //
        -100, -100, 0, 0.0,     //  Al 5lea varf (4) are a 4a coordonata 0;
    //
        -100, -100, 0, 0.5,     //  Urmatoarele 4 varfuri (5...8) au a 4a coordonata 0.5;
         100, -100, 0, 0.5,
         100,  100, 0, 0.5,
        -100,  100, 0, 0.5,
  };

    //    Culorile ca atribute ale varfurilor;
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

    //  Transmiterea datelor prin buffere;

    //  Se creeaza / se leaga un VAO (Vertex Array Object) - util cand se utilizeaza mai multe VBO;
    glGenVertexArrays(1, &VaoId);                                                   //  Generarea VAO si indexarea acestuia catre variabila VaoId;
    glBindVertexArray(VaoId);

    //  Se creeaza un buffer pentru VARFURI;
    glGenBuffers(1, &VboId);                                                        //  Generarea bufferului si indexarea acestuia catre variabila VboId;
    glBindBuffer(GL_ARRAY_BUFFER, VboId);                                           //  Setarea tipului de buffer - atributele varfurilor;
    glBufferData(GL_ARRAY_BUFFER, sizeof(Vertices), Vertices, GL_STATIC_DRAW);      //  Punctele sunt "copiate" in bufferul curent;
    //  Se asociaza atributul (0 = coordonate) pentru shader;
    glEnableVertexAttribArray(0);
    glVertexAttribPointer(0, 4, GL_FLOAT, GL_FALSE, 0, 0);

    //  Se creeaza un buffer pentru CULOARE;
    glGenBuffers(1, &ColorBufferId);
    glBindBuffer(GL_ARRAY_BUFFER, ColorBufferId);
    glBufferData(GL_ARRAY_BUFFER, sizeof(Colors), Colors, GL_STATIC_DRAW);
    //  Se asociaza atributul (1 =  culoare) pentru shader;
    glEnableVertexAttribArray(1);
    glVertexAttribPointer(1, 4, GL_FLOAT, GL_FALSE, 0, 0);
}

//  Elimina obiectele de tip shader dupa rulare;
void DestroyShaders(void)
{
    glDeleteProgram(ProgramId);
}

//  Eliminarea obiectelor de tip VBO dupa rulare;
void DestroyVBO(void)
{
    //  Eliberarea atributelor din shadere (pozitie, culoare, texturare etc.);
    glDisableVertexAttribArray(1);
    glDisableVertexAttribArray(0);

    //  Stergerea bufferelor pentru varfuri, culori;
    glBindBuffer(GL_ARRAY_BUFFER, 0);
    glDeleteBuffers(1, &ColorBufferId);
    glDeleteBuffers(1, &VboId);

    //  Eliberaea obiectelor de tip VAO;
    glBindVertexArray(0);
    glDeleteVertexArrays(1, &VaoId);
}

//  Functia de eliberare a resurselor alocate de program;
void Cleanup(void)
{
    DestroyShaders();
    DestroyVBO();
}

//  Setarea parametrilor necesari pentru fereastra de vizualizare;
void Initialize(void)
{
    glClearColor(1.0f, 1.0f, 1.0f, 1.0f);		//  Culoarea de fond a ecranului;
    CreateVBO();								//  Trecerea datelor de randare spre bufferul folosit de shadere;
    CreateShaders();							//  Initializarea shaderelor;
    //	Instantierea variabilelor uniforme pentru a "comunica" cu shaderele;
    myMatrixLocation = glGetUniformLocation(ProgramId, "myMatrix");
    //	Dreptunghiul "decupat"; 
    resizeMatrix = glm::ortho(xMin, xMax, yMin, yMax);  
}

//  Functia de desenarea a graficii pe ecran;
void RenderFunction(void)
{
    glClear(GL_COLOR_BUFFER_BIT);			//  Se curata ecranul OpenGL pentru a fi desenat noul continut;
    
    //	Transmiterea variabilei uniforme pentru MATRICEA DE TRANSFORMARE spre shadere;
    myMatrix = resizeMatrix;
    glUniformMatrix4fv(myMatrixLocation, 1, GL_FALSE, &myMatrix[0][0]);

    glLineWidth(5.0);                         //  Se seteaza dimensiunea liniilor;
  
    //  Functia de desenare primeste 3 argumente:
    //  - arg1 = tipul primitivei desenate,
    //  - arg2 = indicele primului punct de desenat din buffer,
    //  - arg3 = numarul de puncte consecutive de desenat;
    
    //  Desenarea varfurilor rosii;
    glDrawArrays(GL_LINE_LOOP, 0, 4);

    //  Desenarea varfurilor albastre;
    glDrawArrays(GL_LINE_LOOP, 5, 4);

    glFlush();			//  Asigura rularea tuturor comenzilor OpenGL apelate anterior;
}

//	Punctul de intrare in program, se ruleaza rutina OpenGL;
int main(int argc, char* argv[])
{
    //  Se initializeaza GLUT si contextul OpenGL si se configureaza fereastra si modul de afisare;

    glutInit(&argc, argv);
    glutInitDisplayMode(GLUT_SINGLE | GLUT_RGB);					//	Modul de afisare al ferestrei, se foloseste un singur buffer de afisare si culori RGB;
    glutInitWindowSize(winWidth, winHeight);						//  Dimensiunea ferestrei;
    glutInitWindowPosition(100, 100);								//  Pozitia initiala a ferestrei;
    glutCreateWindow("Coordonate omogene - OpenGL <<nou>>");		//	Creeaza fereastra de vizualizare, indicand numele acesteia;

    //	Se initializeaza GLEW si se verifica suportul de extensii OpenGL modern disponibile pe sistemul gazda;
    //  Trebuie initializat inainte de desenare;

    glewInit();

    Initialize();						//  Setarea parametrilor necesari pentru fereastra de vizualizare; 
    glutDisplayFunc(RenderFunction);	//  Desenarea scenei in fereastra;
    glutCloseFunc(Cleanup);				//  Eliberarea resurselor alocate de program;

    //  Bucla principala de procesare a evenimentelor GLUT (functiile care incep cu glut: glutInit etc.) este pornita;
    //  Prelucreaza evenimentele si deseneaza fereastra OpenGL pana cand utilizatorul o inchide;

    glutMainLoop();

    return 0;
}