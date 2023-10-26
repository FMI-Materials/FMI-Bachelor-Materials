#include <cstdlib>
#include <iostream>
using namespace std;

// Partea II -apelul constructorilor de initializare si copiere, al operatorilor= si destructorilor

class B
{
 public:
  B(int i=0){cout<<" c i baza \n";}
  B(const B& b){cout<<" c copiere baza \n ";}
  void operator=(const B &ob){cout<<" = baza\n";}
  ~B(){cout<<"destructor baza\n ";}
  };
 class D :B // specificatorul ei de mostenire -implicit privat
 { public :
 //  constructorul de initializare: fie explicit fie implicit  -se apeleaza automat intai constructorul pt  baza si apoi pentru derivata
  D(int i=0)//: B(i)
  {cout<<" c i derivata \n";}
 // prin apel explicit  se pot transmite parametrii catre constructorul clasei de baza
  // ordinea este cea din lista de derivare -indiferent de lista de apel explicit a constructorilor

    //constructorul  de copiere al derivatei dat de compilator apeleaza constructorul de COPIERE al bazei
    // daca constructorul de copiere al derivatei nu  apeleaza explicit  constructorul de copiere al bazei
    //atunci se va apela constructorul de INITIALIZARE al bazei
   D(const D &d)//:B(d)
   {cout<<" c copiere derivata \n";}

 void operator=(const D & od )
 { //(B)(*this)=od ;
 //apel explicit al operatorului = din baza (prin conversia catre B ) face sa nu se apeleze infinit  operatorul = din D
    cout<<"= derivata\n";
}
 //operatorul = implicit al derivatei  -apeleaza  implicit operatorul= al bazei
 //operatorul = definit al derivatei  NU apeleaza  implicit operatorul = al bazei

 ~D(){cout<<"destructor derivata \n ";}
 //destructorul implicit sau definit  apeleaza destructorul bazei
 // ordinea de executie este inversa fata de cea a constructorilor
       };


class C // are acces doar la datele publice  ale m1 si m2
{B m1,m2;
public:
 C(int i=0): m1(i) // se apelaza intai constructorul pt membrii si apoi constructorul pentru clasa C
  {cout<<"initializare C \n";}
  //prin apelul explicit se pot trimite si parametrii
    // ordinea -intai constructorul BAZEI (daca mosteneste o clasa) apoi constructorul MEMBRILOR si apoi constructorul clasei -indiferent
    // de ordinea din lista de apel explicit

    C(const C & oc):m1(oc.m1){cout<<"copiere C\n";}
   //constr copiere implicit (dat de compilator) al clasei compuse apeleaza constructorii de copiere ai claselor datelor membre
   // constr de copiere definit al clasei compuse  -apeleaza implicit constructorii de INITIALIZARE ai claselor datelor membre
     //-deci trebuie apelati  EXPLICIT  constructorii de copiere ai claselor datelor membre

   void operator =(const C & oc){cout<<"egal C\n ";}
// operatorul = implicit al clasei compuse apeleaza implicit operatorii = ai claselor membre
// operatorul = definit al clasei compuse  NU apeleaza implicit operatorii = ai claselor membre
 //deci  trebuie apelati explicit
};


int main(int argc, char *argv[])
{
    D d1,d2=d1; //apelul constructorilor
    d1=d2; // apelul operatorilor =
    C c1, c2=c1;
    c1=c2;
 system("PAUSE");
    return 0;
}





