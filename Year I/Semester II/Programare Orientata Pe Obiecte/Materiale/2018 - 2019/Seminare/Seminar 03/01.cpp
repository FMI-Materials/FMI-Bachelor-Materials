#include <cstdlib>
#include <iostream>
using namespace std;
/// Partea I accesul la datele clasei de baza
class B
{private: int v;    // vizibil DOAR  din clasa B
 protected: int d; // pentru obiectele din B la fel ca si private, pentru obiectele din clasa derivata(D) vizibil doar din clasa
 public: int b; // vizibile din orice punct
 };
 class D :B // clasa D  ESTE ca  B (are toate datele si metodele lui B) si mai are alte date si metode suplimentare
// specificatorul ei de mostenire -implicit privat
 { public :
  void f()
   {//v=3;  este innaccesibil
    d=3;
    D d1;
     B b1;
  d1.d=3;// este accesibil 
 //b1.d=3; nu este accesibil - private si protected  pt ob bazei accesibile doar din metodele clasei de baza
    }

};

class C // clasa C  ARE doua date de tip B

{B m1,m2;
public: void g()
{
//m1.v=1;m1.d=1; //nu are acces la datele private sau protected ale datelor membre
m1.b=1; // are acces doar la datele publice  ale m1 si m2
}
};

class BC: public B, C{};// va mosteni public doar B si PRIVAT pe C

int main(int argc, char *argv[])
{
 system("PAUSE");
    return 0;
}





