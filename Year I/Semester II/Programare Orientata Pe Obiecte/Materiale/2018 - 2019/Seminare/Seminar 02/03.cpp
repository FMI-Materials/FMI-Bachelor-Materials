#include <cstdlib>
#include <iostream>
using namespace std;

class Complex
{
      float re,im;
public:
     Complex(){im=0; cout << "constructor de initializare fara parametrii "<<endl;}
     Complex(int r){re=r;im=0;cout<<"constructor de initializare  cu un parametru"<<endl;}
     Complex(int r,int i){re=r;im=i;cout<<"constructor de initializare cu parametrii"<<endl;}
     Complex(const Complex & o)  {re=o.re; im=o.im; cout<< "constructor de copiere"<<endl;} //important referinta constanta
    ~Complex (){cout<<"destructor"<<endl;}
};

void fpv(Complex op){cout<<"functie cu parametru transmis prin valoare"<<endl;}
void fpr(Complex & op){cout<<"functie cu parametru transmis prin referinta"<<endl;}
Complex frv(){Complex ol; cout<<"functie cu rezultat intors ca valoare"<<endl; return ol;}
Complex & frr(){Complex *p=new Complex ; cout<<"functie cu rezultat intors ca referinta"<<endl; return (*p);}


int main()
{ cout<<"INITIALIZARE"<<endl;
  Complex C1;
   Complex C2(1),C3=2;
   Complex C4(1,2);
   Complex *p;
   cout<<"ALOCARE DINAMICA"<<endl;
   p= new Complex;
   p=new Complex(1);
   p=new Complex(1,2);
  cout<<"ALOCARE VECTOR"<<endl;
  Complex v[2];
  Complex v1[2]={Complex(1),Complex(2)};
  Complex v2[2]={Complex(1,2),Complex(2,3)};
  cout<<"CONSTRUCTORUL DE COPIERE"<<endl;
   Complex C5=C1, C6(C1),v3[2]={Complex(C1),Complex(C1)};
   p=new Complex(C1);
  cout<<"OPERATOR ATRIBUIRE"<<endl;
   C2=C1;
  cout<<"DESTRUCTOR"<<endl;
   {Complex C6;}
    delete p;

  cout<<"APEL PRIN VALOARE"<<endl;
    fpv(C1);
    cout<<"APEL PRIN REFERINTA"<<endl;
    fpr(C1);
    cout<<"APEL INTOARCERE VALOARE"<<endl;
    frv(); // ar trebui sa afiseze apelul constructorului de copiere
    cout<<"APEL INTOARCERE REFERINTA"<<endl;
    frr();
    cout<<"ADRESA  OBIECTULUI TEMPORAR"<<endl;
    p=&(frv());
    *p=C1;
    cout<<"ADRESA INTOARCERII  REFERINTA"<<endl;
    p=&(frr());
    return 0;
}


