#include <cstdlib>
#include <iostream>
using namespace std;
template <class T> class stiva; // trebuie declarata ca sa fie vazuta de op >>
template <class T> istream& operator >> (istream& i, stiva<T> &o); // trebuie sa fie declarata ca sa fie vazuta din clasa

template <class T> class stiva
{ T v[10];
  int n;
  public:
  stiva(){n=0;}
  void push(T);
//template <class T1>  friend void f( stiva<T1> ov);
/* nu e corect am functie de un tip prietena cu toate clasele sablon */

friend istream& operator >> <> (istream& i, stiva<T> &o); // sau posibil de definit in clasa -se construieste odata cu clasa 
// si nu mai necesita declaratii anterioare
};

template <class T> istream& operator >> (istream& i, stiva<T> &o){i>> o.n; return i;}


template <class T> void stiva<T>::push(T o){cout<<"metoda sablon"<<endl;}


/* specializari */
template <> void stiva<int>::push(int o){cout<<"metoda specializata"<<endl;}

template <> class stiva<char>
{char v[10];
  int n;
  public:
   stiva(){n=0;}
  void push(char o){cout<<"metoda din clasa specializata";};
friend istream& operator >> <> (istream& i, stiva<char> &o);
};

int main(int argc, char *argv[])
{ stiva<int> ovi1;
  ovi1.push(2);
  cin>>ovi1;

 stiva<char> ovc1;
 ovc1.push('a');   
 cin>>ovc1;
system("PAUSE");
    return 0;
}


