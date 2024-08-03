// Codul sursa este adaptat dupa OpenGLBook.com

#include <windows.h>  // biblioteci care urmeaza sa fie incluse
#include <stdlib.h> // necesare pentru citirea shader-elor
#include <stdio.h>
#include <GL/glew.h> // glew apare inainte de freeglut
#include <GL/freeglut.h> // nu trebuie uitat freeglut.h
  
//////////////////////////////////////

GLuint
  VaoId,
  VboId,
  ColorBufferId,
  VertexShaderId,
  FragmentShaderId,
  ProgramId;
  

///////////////////////////////////////////

// Shader-ul de varfuri / Vertex shader (este privit ca un sir de caractere)
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
// Shader-ul de fragment / Fragment shader (este privit ca un sir de caractere)
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
 
void CreateVBO(void)
{
  // varfurile 
  GLfloat Vertices[] = {
     // prima fata (ABCD)
    -0.8f, -1.0f, 0.0f, 1.0f, // A
    -0.2f, -1.0f, 0.0f, 1.0f, // B
    -0.2f, -0.4f, 0.0f, 1.0f, // C
    -0.8f, -0.4f, 0.0f, 1.0f, // D

    // a doua fata (CDEF)
    -0.6f, -0.2f, 0.0f, 1.0f, // E
     0.0f, -0.2f, 0.0f, 1.0f, // F

    // a treia fata (FCBG)
    -0.2f, -0.4f, 0.0f, 1.0f, // C
    -0.2f, -1.0f, 0.0f, 1.0f, // B
     0.0f, -0.8f, 0.0f, 1.0f, // G

     // T
    -0.8f,  0.4f, 0.0f, 1.0f,
    -0.6f,  0.4f, 0.0f, 1.0f,
    -0.7f,  0.4f, 0.0f, 1.0f,
    -0.7f,  0.2f, 0.0f, 1.0f,

    // E
    -0.5f,  0.4f, 0.0f, 1.0f,
    -0.3f,  0.4f, 0.0f, 1.0f,
    -0.5f,  0.3f, 0.0f, 1.0f,
    -0.3f,  0.3f, 0.0f, 1.0f,
    -0.5f,  0.2f, 0.0f, 1.0f,
    -0.3f,  0.2f, 0.0f, 1.0f,
    -0.5f,  0.4f, 0.0f, 1.0f,
    -0.5f,  0.2f, 0.0f, 1.0f,

    // O
    -0.2f,  0.4f, 0.0f, 1.0f,
    -0.2f,  0.2f, 0.0f, 1.0f,
     0.0f,  0.2f, 0.0f, 1.0f,
     0.0f,  0.4f, 0.0f, 1.0f,
    -0.2f,  0.4f, 0.0f, 1.0f,
  };

  // culorile, ca atribute ale varfurilor
  GLfloat Colors[] = {
    0.0f, 1.0f, 0.0f, 1.0f, // A
    1.0f, 1.0f, 0.0f, 1.0f, // B
    1.0f, 1.0f, 1.0f, 1.0f, // C
    0.0f, 1.0f, 1.0f, 1.0f, // D
    0.0f, 0.0f, 1.0f, 1.0f, // E
    1.0f, 0.0f, 1.0f, 1.0f, // F
    1.0f, 1.0f, 1.0f, 1.0f, // C
    1.0f, 1.0f, 0.0f, 1.0f, // B
    1.0f, 0.0f, 0.0f, 1.0f, // B

    1.0f, 0.0f, 0.0f, 1.0f,
    1.0f, 0.0f, 0.0f, 1.0f,
    1.0f, 0.0f, 0.0f, 1.0f,
    1.0f, 0.0f, 0.0f, 1.0f,

    1.0f, 0.0f, 1.0f, 1.0f,
    1.0f, 0.0f, 1.0f, 1.0f,
    1.0f, 0.0f, 1.0f, 1.0f,
    1.0f, 0.0f, 1.0f, 1.0f,
    1.0f, 0.0f, 1.0f, 1.0f,
    1.0f, 0.0f, 1.0f, 1.0f,
    1.0f, 0.0f, 1.0f, 1.0f,
    1.0f, 0.0f, 1.0f, 1.0f,

    0.0f, 0.0f, 1.0f, 1.0f,
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
  // 
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
void DestroyShaders(void)
{
   
  glUseProgram(0);

  glDetachShader(ProgramId, VertexShaderId);
  glDetachShader(ProgramId, FragmentShaderId);

  glDeleteShader(FragmentShaderId);
  glDeleteShader(VertexShaderId);

  glDeleteProgram(ProgramId);
 
}
 
void Initialize(void)
{
  glClearColor(1.0f, 1.0f, 1.0f, 0.0f); // culoarea de fond a ecranului
}
void RenderFunction(void)
{
  glClear(GL_COLOR_BUFFER_BIT);
  CreateVBO();
  CreateShaders();
  glDrawArrays(GL_POLYGON, 0, 4);
  glDrawArrays(GL_POLYGON, 2, 4);
  glDrawArrays(GL_POLYGON, 5, 4);

  glLineWidth(2.0);
  glDrawArrays(GL_LINES, 9, 2);
  glDrawArrays(GL_LINES, 11, 2);
  glDrawArrays(GL_LINES, 13, 2);
  glDrawArrays(GL_LINES, 15, 2);
  glDrawArrays(GL_LINES, 17, 2);
  glDrawArrays(GL_LINES, 19, 2);

  glDrawArrays(GL_LINES, 21, 2);
  glDrawArrays(GL_LINES, 22, 2);
  glDrawArrays(GL_LINES, 23, 2);
  glDrawArrays(GL_LINES, 24, 2);

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
  glutInitWindowPosition (0,0); // pozitia initiala a ferestrei
  glutInitWindowSize(600,600); //dimensiunile ferestrei
  glutCreateWindow("Primul triunghi - OpenGL <<nou>>"); // titlul ferestrei
  glewInit(); // nu uitati de initializare glew; trebuie initializat inainte de a a initializa desenarea
  Initialize( );
  glutDisplayFunc(RenderFunction);
  glutCloseFunc(Cleanup);
  glutMainLoop();
  
  
}