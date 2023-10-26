#include <cstdlib>
#include <iostream>
#include <fstream>
using namespace std;

void f(const int i){/*i=1;*/} // nu pot modifica parametrul formal - copia parametrului actual -

void f1(int i){i=1;} // modifica copia parametrului actual

void f2(int *pi){*pi=1;}// modifica variabila adresata de parametrul actual
void f3(const int *pi){}// nu pot modifica  prin parametrul actual variabila adresata (de parametrul actual)

void f4(int &ri){ri=1;} // modific zona parametrului actual prin parametrul formal (alt nume pentru zona parametrului actual)
void f5(const int &ri){}// nu pot modifica parametrul actual prin parametrul formal

int f6(){return 2;}
int & f7(){int *p=new int (2); return *p;
//const int & rlc=*p;return rlc; /*nu-pot modifica referinta constanta prin referinta intoarsa*/
}
const int & f8(){int *p=new int (2); return *p;} /* corect -nu pot modifica zona intoarsa*/

void f(int *pi){cout<<"pointer ";}
void f(const int *pi){cout<<"pointer spre const";}
/* NU e ambiguitate !! daca prima varianta lipseste varianta a doua face si conversie de la int * la const int *  */
int main()
{
const int c=1;
int i;
//f4(c); //nu - initializez referinta cu o constanta -o pot modifica
f5(c);// da -initializez referinta constanta cu o constanta -nu pot modifica
//f6()=2;//nu se poate modifica temporarul- este constant
f7()=2;
//f8()=2;// nu se poate modifica prin referinta zona constanta
int *p;
int*pc;
f(p);
f(pc);
}

