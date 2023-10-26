#include <cstdlib>
#include <iostream>
#include <fstream>
using namespace std;

int main()
{
    int i;
try{
    cin>>i;
    if (i) throw 2;
    cout<<"dupa if"; // nu se mai executa daca se arunca exceptia
    }
catch(double a){cout<<a;} // nu face conversie - decat pointer la baza primeste pointer la derivata
catch(int a){cout<<a;}
catch(...){cout<<" toate tipurile"} // daca lipseste si un tip nu e prins -terminare anormala
 cout<<"dupa catch"; // dupa ce este tratata exceptia sau daca nu s-a aruncat exceptie dupa try

}
