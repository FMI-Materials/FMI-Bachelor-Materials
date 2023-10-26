#include <cstdlib>
#include <iostream>
using namespace std;
 
class lista
{ int v[100];
  protected: int l; // necesar accesul la l din clasele derivate
public:
lista(){l=0;} // va fi apelat de constructorul claselor derivate
bool insera(int val, int pos){}

bool sterge(int &val, int pos){}

};

class stiva : protected lista // nu e permis public pentru a ascunde inserare si stergere -nepotrivite pt stiva
{public:                               // se apeleaza constructorul clasei de baza
  bool push(int val){return insera(val,l);};
  bool pop (int &val){return sterge(val,l-1);};
};

class coada : protected lista // functiile sterge si insera vor fi suprscrise dar  esunt accesibile  si
{ public:                        // variantele din lista  lista::sterge()
 bool insera(int val) {return lista::insera(val,l);};
 bool sterge(int & val) {return lista::sterge(val,0);};
};


int main()
{
}
