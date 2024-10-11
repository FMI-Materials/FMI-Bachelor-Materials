//
// ================================================
// | Grafica pe calculator                        |
// ================================================
// | Laboratorul I - 01_00_test_version.cpp |
// ==========================================
//	
// Program de verificare a versiunii de OpenGL si a GLSL;
//
//
//	Biblioteci

#include <windows.h>        //	Utilizarea functiilor de sistem Windows (crearea de ferestre, manipularea fisierelor si directoarelor);
#include <cstdio>			//  Functii pentru manipularea fisierelor + functiile: printf() + scanf();
#include <GL/glew.h>        //	Definește prototipurile functiilor OpenGL si constantele necesare pentru programarea OpenGL moderna; 
#include <GL/freeglut.h>    //	Include functii pentru: 
							//	- gestionarea ferestrelor si evenimentelor de tastatura si mouse, 
							//  - desenarea de primitive grafice precum dreptunghiuri, cercuri sau linii, 
							//  - crearea de meniuri si submeniuri;


//	Punctul de intrare in program, se ruleaza rutina OpenGL;
int main (int argc, char** argv) 

{ 
	//	Se initializeaza GLUT si contextul OpenGL si se configureaza fereastra si modul de afisare;
	//	In acest program, se va realiza doar contextul fara afisarea ferestrei propriu-zise, scopul fiind obtinerea versiunii de OpenGL si GLSL;

	glutInit (&argc, argv); 
	glutInitDisplayMode (GLUT_SINGLE | GLUT_RGB);   //	Modul de afisare al ferestrei, se foloseste un singur buffer de afisare si culori RGB;
	glutInitWindowPosition (1100, 100);				//	Pozitia initiala a ferestrei;
	glutInitWindowSize (600, 400);					//	Dimensiunea ferestrei;
	int winID = glutCreateWindow ("GL_VERSION");	//	Creeaza fereastra de vizualizare, indicand numele acesteia;
	glutDestroyWindow(winID);

	//	Se initializeaza GLEW si se verifica suportul de extensii OpenGL modern disponibile pe sistemul gazda;
	//  Trebuie initializat inainte de desenare;

	GLenum err = glewInit();
	if (err != GLEW_OK)
	{
		fprintf(stderr, "Error: %s\n", glewGetErrorString(err));
		exit(-1);
	}

	//	Afisarea versiunilor de OpenGL si GLSL in consola;

	printf("OpenGL version supported by this platform: (%s) \n", glGetString(GL_VERSION)); 
	printf("GLSL version supported by this platform: (%s) \n", glGetString(GL_SHADING_LANGUAGE_VERSION)); 

	return 0;
}
