#include <cstdlib>
#include <iostream>
#include<cstring>
using namespace std;
template <class T> T maxim( T  a, T  b)
{  cout<<"template"<<endl;
    if (a>b) return a; // operatorul < trebuie sa fie definit pentru tipul T
 return b;
}
template <> const char * maxim(const char* a,const char* b)
{  cout<<"supraincarcare const"<<endl;
 if (strcmp(a,b)>0) return a;
 return b;
}

 template <> char * maxim ( char* a, char* b)
{cout<<"supraincarcare neconst"<<endl;
 if (strcmp(a,b)>0) return a;
 return b;
}

// pot exista ambele variante
//daca nu exista template<> const char* -pt "ab" se alege sablonul general
//daca nu exista template<> char* -pt v1 se alege sablonul general
/* NU FACE CONVERSIA NICI (char *) --> (const char *) si nici  (const char *) --> (char *) */


int main(int argc, char *argv[])
{
 char v1[10]="abc",v2[10]="bcd";
  cout<<maxim("ab","bc")<<endl;
  cout<<maxim(v1,v2)<<endl;
  cout<<maxim<char *>(v1,"ab")<<endl;


system("PAUSE");
    return 0;
}


