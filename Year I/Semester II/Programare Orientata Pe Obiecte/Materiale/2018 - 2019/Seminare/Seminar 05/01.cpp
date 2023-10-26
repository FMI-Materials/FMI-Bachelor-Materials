#include <cstdlib>
#include <iostream>
#include<cstring>
using namespace std;
template <class T>
T maxim(T a, T b)
{  cout<<"template"<<endl;
    if (a>b) return a; // operatorul < trebuie sa fie definit pentru tipul T
 return b;
}
const char * maxim(const char* a,const char* b)
{  cout<<"supraincarcare const"<<endl;
 if (strcmp(a,b)>0) return a;
 return b;
}
// pot exista ambele variante cu const char * si char *
 template <> char * maxim<char *>( char* a, char* b)
{  cout<<"supraincarcare neconst"<<endl;
 if (strcmp(a,b)>0) return a;
 return b;
}


/* NU FACE CONVERSIA NICI (char *) spre (const char *) si nici  (const char *) spre (char *) - daca nu sunt ambele variante:*/
/* daca param formali sunt pointerii la const si param actuali sunt neconst -  nu se apeleaza supraincarcarea ci sablonul */
/* daca param formali nu sunt pointeri la const si param actuali sunt pointeri la const nu se apeleaza
supraincarcarea ci sablonul*/

int main(int argc, char *argv[])
{
 char v1[10]="abc",v2[10]="bcd";

 cout<<maxim(2,3)<<"\n";
 //  cout<<maxim(1,2.3)<<"\n"; // nu face conversia
  cout<<maxim<int>(2,3.5)<<"\n";

  cout<<maxim("ab","bc")<<"\n";
  cout<<maxim(v1,v2)<<endl;;


system("PAUSE");
    return 0;
}


