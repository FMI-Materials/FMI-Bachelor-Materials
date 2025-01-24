//
// ================================================
// | Grafica pe calculator                        |
// ================================================
// | Laboratorul I - 01_02_varfuri_triunghi.cpp |
// ==============================================
//
//  Prezentul cod sursa este adaptat dupa OpenGLBook.com;
//  Program ce deseneaza 3 puncte colorate diferit care reprezinta varfurile unui triunghi, folosidu-se tehnicile MODERN OpenGL;
//
//
//  Biblioteci

#include <windows.h>        //	Utilizarea functiilor de sistem Windows (crearea de ferestre, manipularea fisierelor si directoarelor);
#include <stdlib.h>         //  Biblioteci necesare pentru citirea shaderelor;
#include <stdio.h>
#include <GL/glew.h>        //  Definește prototipurile functiilor OpenGL si constantele necesare pentru programarea OpenGL moderna; 
#include <GL/freeglut.h>    //	Include functii pentru: 
                            //	- gestionarea ferestrelor si evenimentelor de tastatura si mouse, 
                            //  - desenarea de primitive grafice precum dreptunghiuri, cercuri sau linii, 
                            //  - crearea de meniuri si submeniuri;
  
//  Identificatorii obiectelor de tip OpenGL;
GLuint
  VaoId,
  VboId,
  ColorBufferId,
  VertexShaderId,
  FragmentShaderId,
  ProgramId;

//  Accesarea shaderelor - definite ca siruri de caractere;
//  Pentru moment shaderele nu efectueaza schimbari, pastreaza coordonatele si culorile definite in program;

//  Shaderul de varfuri / Vertex shader - afecteaza geometria scenei;
const GLchar* VertexShader =
{
      "#version 400\n"\

      "layout(location=0) in vec4 in_Position;\n"\
      "layout(location=1) in vec4 in_Color;\n"\
      "out vec4 ex_Color;\n"\

      "void main(void)\n"\
      "{\n"\
      "  gl_Position = in_Position;\n"\
      "  ex_Color = in_Color;\n"\
      "}\n"
};

//  Shaderul de fragment / Fragment shader - afecteaza culoarea pixelilor;
const GLchar* FragmentShader =
{
      "#version 400\n"\

      "in vec4 ex_Color;\n"\
      "out vec4 out_Color;\n"\

      "void main(void)\n"\
      "{\n"\
      "  out_Color = ex_Color;\n"\
      "}\n"
};
 
//  Se initializeaza un Vertex Buffer Object (VBO) pentru transferul datelor spre memoria placii grafice (spre shadere);
//  In acesta se stocheaza date despre varfuri (coordonate, culori, indici, texturare etc.);
void CreateVBO(void)
{
    //  Coordonatele varfurilor; Fiecare varf are 4 coordonate. Momentan: a 3-a este 0, a 4-a este 1
    GLfloat Vertices[] = {
        -0.8f, -0.8f, 0.0f, 1.0f,
         0.0f,  0.8f, 0.0f, 1.0f,
         0.8f, -0.8f, 0.0f, 1.0f,
        // De explorat cu mai multe varfuri. Coordonatele sunt (momentan) in intervalul [-1,1]
        // 0.3f, -0.3f, 0.0f, 1.0f, 
        // 0.3f, 0.3f, 0.0f, 1.0f
    };

    //  Culorile in spectrul RGB(A) ca atribute ale varfurilor;
    GLfloat Colors[] = {
        1.0f, 0.0f, 0.0f, 1.0f,
        0.0f, 1.0f, 0.0f, 1.0f,
        0.0f, 0.0f, 1.0f, 1.0f,
        //0.0f, 1.0f, 1.0f, 1.0f,
       // 1.0f, 0.0f, 1.0f, 1.0f
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

//  Crearea si compilarea obiectelor de tip shader;
void CreateShaders(void)
{
    VertexShaderId = glCreateShader(GL_VERTEX_SHADER);
    glShaderSource(VertexShaderId, 1, &VertexShader, NULL);
    glCompileShader(VertexShaderId);

    FragmentShaderId = glCreateShader(GL_FRAGMENT_SHADER);
    glShaderSource(FragmentShaderId, 1, &FragmentShader, NULL);
    glCompileShader(FragmentShaderId);

    ProgramId = glCreateProgram();
    glAttachShader(ProgramId, VertexShaderId);
    glAttachShader(ProgramId, FragmentShaderId);
    glLinkProgram(ProgramId);
    glUseProgram(ProgramId);
}

//  Elimina obiectele de tip shader dupa rulare;
void DestroyShaders(void)
{  
    glUseProgram(0);

    glDetachShader(ProgramId, VertexShaderId);
    glDetachShader(ProgramId, FragmentShaderId);

    glDeleteShader(FragmentShaderId);
    glDeleteShader(VertexShaderId);

    glDeleteProgram(ProgramId);
}
 
//  Setarea parametrilor necesari pentru fereastra de vizualizare;
void Initialize(void)
{
    glClearColor(0.0f, 0.0f, 0.0f, 0.0f);   //  Culoarea de fond a ecranului;
    CreateVBO();                            //  Trecerea datelor de randare spre bufferul folosit de shadere;
    CreateShaders();                        //  Initilizarea shaderelor;
}

//  Functia de desenarea a graficii pe ecran;
void RenderFunction(void)
{
    glClear(GL_COLOR_BUFFER_BIT);       //  Se curata ecranul OpenGL pentru a fi desenat noul continut;
    glPointSize(20.0);                  //  Se seteaza dimensiunea punctelor;
    
    //  Desenarea primitivelor geometrice - varfurile unui triunghi, utilizand datele din VBO
    //  Functia primeste 3 argumente:
    //  - arg1 = tipul primitivei desenate,
    //  - arg2 = indicele primului punct de desenat din buffer,
    //  - arg3 = numarul de puncte consecutive de desenat;

    glDrawArrays(GL_POINTS, 0, 3);  // De explorat si alte variante de primitive
 
    glFlush ( );    //  Asigura rularea tuturor comenzilor OpenGL apelate anterior;
}

//  Functia de eliberare a resurselor alocate de program;
void Cleanup(void)
{
    DestroyShaders();
    DestroyVBO();
}

//	Punctul de intrare in program, se ruleaza rutina OpenGL;
int main(int argc, char* argv[])
{
    //  Se initializeaza GLUT si contextul OpenGL si se configureaza fereastra si modul de afisare;

    glutInit(&argc, argv);
    glutInitDisplayMode(GLUT_SINGLE | GLUT_RGB);             //	 Modul de afisare al ferestrei, se foloseste un singur buffer de afisare si culori RGB;
    glutInitWindowPosition(100, 100);                        //  Pozitia initiala a ferestrei;
    glutInitWindowSize(700, 500);                            //  Dimensiunea ferestrei;
    glutCreateWindow("Varfuri triunghi - OpenGL <<nou>>");   //	 Creeaza fereastra de vizualizare, indicand numele acesteia;

    //	Se initializeaza GLEW si se verifica suportul de extensii OpenGL modern disponibile pe sistemul gazda;
    //  Trebuie initializat inainte de desenare;

    glewInit();
    
    Initialize( );                      //  Setarea parametrilor necesari pentru afisare;
    glutDisplayFunc(RenderFunction);    //  Desenarea scenei in fereastra;
    glutCloseFunc(Cleanup);             //  Eliberarea resurselor alocate de program;
  
    //  Bucla principala de procesare a evenimentelor GLUT (functiile care incep cu glut: glutInit etc.) este pornita;
    //  Prelucreaza evenimentele si deseneaza fereastra OpenGL pana cand utilizatorul o inchide;
  
    glutMainLoop();

    return 0;
}