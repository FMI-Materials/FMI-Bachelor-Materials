#include <cstdlib>
#include <iostream>
#include <fstream>
using namespace std;
class C
{static  int s;
 int ns;
public:
C(){s=-1;}
void f(){ns=2; (*this).ns=2; s=2; (*this).s=2;C::s=2;}
static int get_s(){ //ns=1;// nu au this deci nu pot accesa decat datele statice ale clasei
                    // f(); // nu au this deci nu pot apela o metoda nestatica
                    //este de fapt (*this).f() -se apeleaza de un obiect
                    return s;
                    C oc; oc.s=-1; // pot accesa datele nestatice ale unui Obiect al clasei
                    }
 } o1;
//int C::s;// trebuie redeclarat pt a aloca zona de memorie
            //daca nu se initializeaza are val 0 (ca variabilele globale)
            // se aloca inainte de creerea obiectelor
int C::s=1;// la declarare se poate si initializa desi nu este accesibil !!


int main()
{cout<<C::get_s();
 C o2;
 o2.get_s();
//C::s=2; eroare data privata -nu este accesibila


}


