#include <cstdlib>
#include <iostream>
#include <cmath>
using namespace std;

class Complex
{
      float re,im;
public:
     Complex(){im=0; }
     Complex (int r){re=r;im=0;}
     Complex(int r,int i){re=r;im=i;}
     Complex operator+(Complex p2); //primul operand devine obiectul care apeleaza metoda operator+
    	// doar al doilea operand ramane parametru
     friend Complex operator+(float i,Complex p2 ); // functie exterioara care primeste drepturi de acces la
					//datele private si protejate ale clasei
     Complex operator = (Complex p); // neaparat ca metoda a casei
     	// intoarce un obiect al clasei pentru a permite atribuire repetata ex: C1=C2=C3;
     friend istream & operator>>(istream & i, Complex &op); // parametrii transmisi prin referinta pentru ca ambii se modifica
 	//rezultat intors prin referinta pentru a putea fi apelat ca parametru de intrare pentru urmatorul operator in cazul citirii multiple
	 // exemplu  cin>>C1 >>C2; il gindim ca >>(>>(cin,C1), C2)
     friend ostream & operator<<(ostream & out, Complex op);
     float & operator[](int i); // intors prin referinta pentru a fi l-valoare (poate primi valori)
	     //operator float(){return sqrt(re*re+im*im);} // operatorul de conversie la tip- nu se scrie tipu intors
   	 // iar numele operatorului este tipul catre care se face conversia
};

Complex Complex :: operator + (Complex p2)
{ Complex ol;
   ol.re=re+p2.re; // ol.re=(*this).re +p2.re;
   ol.im=im+p2.im;
  return ol;
 }

Complex operator + (float r, Complex p2)
{Complex ol;
  ol.re=r+p2.re;
  ol.im=p2.im;
   return ol;
}
Complex Complex:: operator=(Complex p)
{re=p.re;
 im=p.im;
return (*this);}

istream & operator >>(istream & i, Complex &op)
{ i>>op.re>>op.im;
  return i;
}
ostream & operator <<(ostream & out, Complex op)
{ out<<op.re<<op.im;
  return out;
}

 float & Complex :: operator[](int i)
{if(i==0) return re;
  return im;}

int main()
{ Complex C1, C2(1,2), C3(2,3);
   C1+C2; // se poate gandi ca C1.+(C2)
   C1+2;
   2+C2; // se poate gandi ca +(2,C2)
   C1=C2=C3;
   cin>>C1;
   C1[0]=2;C1[1]=3;
   //int a=C1;
}


