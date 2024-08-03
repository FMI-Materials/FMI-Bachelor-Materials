#include <cstdlib>
#include <iostream>
#include <cstring>
using namespace std;
//Didactic push e metoda iar pop e friend
template <class T> class stiva
{ T v[10];
  int n;
  public:
  stiva(){n=0;};
  void push(T);
//pot declara si defiini friend in clasa -se creaza odata cu clasa -dar nu sunt vizibili ca template in exterior
friend T pop(stiva<T> &o){cout<<"friend sablon"<<endl;o.n--;return (o.v)[o.n];}
friend istream& operator >> (istream& is, stiva<T> &o){is>> o.n;for(int j=0;j<o.n; j++) is>>o.v[j] ;return is;}

};


template <class T> void stiva<T>::push(T o)
  {cout<<"metoda sablon"<<endl;
   v[n]=o;n++;
  }

template <> void stiva<char*>::push(char* o)
  {cout<<"metoda specializata"<<endl;
   v[n]=new char[strlen(o)+1];
   strcpy(v[n],o);
   n++;
   }



template <> class stiva<char> //se poate modifica componenta  intregii clase
{char v[10];
  int n;
  public:
  stiva(){n=0;}
friend char top(stiva<char> o){return (o.v)[o.n];cout<<"friend din clasa specializata"<<endl;}
friend istream& operator >> (istream& is, stiva<char> &o){is>> o.n;for(int j=0;j<o.n; j++) is>>o.v[j] ;return is;}
//nu vede operatorul >> definit in interiorul sablonului general
//trebuie REDECLARAT friend si REDEFINIT  operatorul >> in clasa NOUA
};




int main(int argc, char *argv[])
{ stiva<int> si;
   si.push(2);
   pop(si);
   cin>>si;

 stiva<char> sc;
// sc.push('c');// NU ARE METODELE CLASEI SABLON GENERALE
 top(sc);
 cin>>sc; //trebuie REDEFINIT operatorul >> pt clasa NOUA


 char v[10]="ab";
 stiva<char *>sp;
 sp.push(v);
 pop(sp);
 cin>>sp;
system("PAUSE");
    return 0;
}


