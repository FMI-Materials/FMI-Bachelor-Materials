#include <cstdlib>
#include <iostream>
#include <fstream>
using namespace std;
class C
{public:
    int n;
    const int c; /* se initializeaza doar in lista de initializare a construct si nu se mai modifica ulterior
                 pt fiecare obiect poate avea o alta valoare primita la initializare prin param constructorului*/
    C(int p=0):c(p),n(p){n=p;
	                    /*c=p;*/ // nu se mai poate modifica -se apeleaza operatorul= nu pseudoconstructorul
	                     };
    int f1(){return c;} // da - intorc o copie
    //int & f2(){return c;}//nu -pot modifica campul const prin ref
    int & f3(){return n;} // da - pot modifica
    const int & f4(){return c;} // da -nu pot modifica const
};

int main()
{

}

