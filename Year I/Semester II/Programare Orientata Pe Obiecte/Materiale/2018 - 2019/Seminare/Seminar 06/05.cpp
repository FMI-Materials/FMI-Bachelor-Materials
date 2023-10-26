#include <cstdlib>
#include <iostream>
#include <fstream>
using namespace std;
class C
{ int n;
  public:  
    C(int p=0){n=p;};
  /*int & fc1()const{return n;} */  /* metoda e constanta cand const apare DUPA lista param
    									nu va putea modifica datele obiectului implicit
	                                  !!! this e transmis ca pointer spre zona const -deci n devine const int
                                      nu pot initializa referinta cu o zona const -o pot modifica */
    const int & fc2()const{/*n=1;*/ /*nu se pot modifica datele obiectului -
									transmis prin this pointer care nu modifica zona*/
							C c1; c1.n=1;// poate modifica datele altui obiect		
	                        return n;} // da- intoarce o zona care nu va putea fi modificata
    void fnc(){}// metoda neconstanta- nu poate fi apelata de obiecte const
};


int main()
{
const C oc;
//oc.fnc(); //nu poate apela decat met const

C on; // poate apela met const si neconst
on.fc2();
on.fnc();

const C *p; // prin pointer nu se poate modifica zona
 p=&on;
 p->fc2();
// p->fnc(); //prin pointer care nu modifica zona nu pot apela decat functii const

}

