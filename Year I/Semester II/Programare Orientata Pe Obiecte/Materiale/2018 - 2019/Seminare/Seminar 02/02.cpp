#include <cstdlib>
#include <iostream>
using namespace std;

class Complex
{
         float re,im;
public: void f();
};
/* pentru orice clasa compilatorul asigura implicit
                    - un constructor de initializare -fara parametrii,
			        - un constructor de copiere
			        - un operator de atribuire
			        - un destructor

 -constructorul de initializare se apeleaza -cind se aloca zona de memorie pt un obiect
 -constructorul de copiere se apeleaza -cind se aloca zona de memorie pt un obiect si se initializeaza cu un obiect existent
 -operatorul de atribuire se apeleaza cind se face operatia de atribuire
 -destructorul se apeleaza cind se elibereaza zona de memorie  a unui obiect
*/

int main()
{ Complex C1; // se apeleaza constructorul de initializare
              // putem gandi doar C1.Complex()
   Complex *p;// nu se apeleaza constructorul de initializare -nu se aloca zona pt obiect
   p= new Complex; // se apeleaza constructorul de initializare -se aloca zona pt obiect
   Complex v[2];  // se apeleaza construtorul de initializare  de 2 ori

   Complex C2=C1; // se apeleaza constructorul de copiere
                  // putem gandi C2.Complex(C1);
   p=new Complex(C1);// se apeleaza constructorul de copiere

   C2=C1; // se apeleaza opereatorul de atribuire
	      // putem gandi C2.=(C1);

{Complex C3;}// se apeleaza mai intai constructorul  de initializare si mai apoi destructorul
	         // putem gandi C3.~Complex()
    delete p; // se apeleaza destructorul
    C2.~Complex();// destructorul se poate apela explicit
    C1=C2;//nu face verificarea-dar duce la erori
    C2=C1;//nu face verificarea-dar duce la erori
}

/* constructorul de copiere si operatorul de atribuire  impliciti copiaza BIT CU BIT datele obiectului sursa in datele obiectului destinatie


 daca scriem un constructor de initializare - nu mai exista constructor de initializare implicit

 daca scriem un constructor de copiere -nu mai exista -constructor de initializare implicit
                       				                  -constructor de copiere implicit

 constructorul de copiere se apeleaza
 1. la declararea cu initializare ex: Complex  C2=C1;
 2. la transmiterea unui obiect prin valoare intr-o functie:
     void f(Complex op){}
      f(C1);
 3. la intoarcerea unui obiect prin valoare dintr-o functie
   Complex f1(){ Complex ol; return ol;}
   f1();

 la transmiterea unui obiect prin referinta -nu se apeleaza constructorul de copiere
 la intoarcerea unui obiect prin referinta -nu se apeleaza constructorul de copiere
*/
