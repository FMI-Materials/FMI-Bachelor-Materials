#include <iostream>

using namespace std;

class Baza
{
    string nume; int x;
public:
    virtual void citire() = 0; /// functie virtuala pura
};

void Baza::citire(){cin>>nume>>x;}

class Derivata: public Baza
{
public:
    void citire(){ Baza::citire(); }
};

int main()
{
///    Baza b;
    Derivata d;
    d.citire();
}

/***** mostenire din baza multipla *****/
/*
class Baza
{
public:
    Baza(){cout<<"Baza ";}
    ~Baza(){cout<<"~Baza ";}
    void f(){cout<<"Baza ";}
};

class A : virtual public Baza
{
public:
    A(){cout<<"A ";}
    ~A(){cout<<"~A ";}
};

class B : virtual public Baza
{
public:
    B(){cout<<"B ";}
    ~B(){cout<<"~B ";}
};

class C : public A, public B
{
public:
    C(){cout<<"C ";}
    ~C(){cout<<"~C ";}
};

int main()
{
    C ob;
///    ob.f(); /// ambiguitate; rezolvare 1 - operatorul de rezolutie de scop ob.A::f(); ob.Baza::f()

}
*/

/*******/
/*
class Baza
{
public:
    Baza(){cout<<"B ";}
  /// virtual ~Baza(){cout<<"DB ";}
};

class Derivata : public Baza
{
public:
    Derivata(){cout<<"D ";}
    ~Derivata(){cout<<"DD ";}
};

int main()
{
    /*Baza ob1;
    Derivata ob2;*/
/*    Baza *p = new Baza(); /// atentie la Memory Leak; doar se aloca si nu se mai dezaloca
    delete p;*/
/*    Derivata* q = new Derivata();
    delete q;
    /// Baza *p = new Derivata(); /// atentie la Memory Leak; upcasting fara destructor virtual; nu se elibereaza
    /// zona de memorie pentru datele din derivata
    /// delete p;
    return 0;
}
*/
