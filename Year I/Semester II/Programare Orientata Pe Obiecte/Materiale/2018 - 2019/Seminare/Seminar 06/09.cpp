#include <cstdlib>
#include <iostream>
#include <fstream>
using namespace std;
void f()
{int i;
 cin>>i;
 if (i) throw 2;
 cout<<"dupa if"; // nu se mai executa daca se arunca exceptia
 return;
}

int main()
{
try{
    f();
    cout<<"dupa f"; // nu se mai executa daca se arunca exceptia
   }
catch(double a){cout<<"catch "<<a;} // nu face conversie
catch(int a){cout<<"catch "<<a;}
catch(...){cout<<" toate tipurile";}
 cout<<"dupa catch" ; // dupa tratare sau daca nu s-a aruncat exceptia

}
