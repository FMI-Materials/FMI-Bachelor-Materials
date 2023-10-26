#include <iostream>

using namespace std;

/// clase abstracte, dynamic_cast, downcast, etc...

class Baza
{protected:
    int x;
public:
    virtual void f(){x = 7; cout<<"Baza ";}
    friend ostream& operator<<(ostream& out, Baza& b){return out<<b.x<<endl;}

};

class A : public Baza
{
public:
    void f(){cout<<"Derivata A";}
    friend ostream& operator<<(ostream& out, A& ob){
///        out<<ob.x;
        out<<(Baza&)(ob);
        out<<"ceva"<<endl;

    }
};

class B : virtual public Baza
{
public:
    void f(){cout<<"Derivata B";}
};

int main()
{
    Baza* p = new A();
    cout<<*p;
    cout<<*(A*)(p);
    cout<<*dynamic_cast<A*>(p);
}
    /*
   /// A* q = new Baza();  /// downcast problematic
   Baza*p = new A();
   p->f();
   cout<<endl;
   A* q;
   q = (A*)p; /// downcast
   q->f();
   cout<<endl;
   B* r;
///   r = (B*)p;
    r = dynamic_cast<B*>(p);
    if (r!=NULL) r->f();
    else cout<<"nu merge conversia";
}
/*
class Produs
{
protected:
    string nume;
public:
    Produs(){cout<<"B\n";}
    virtual ~Produs() = 0;
    virtual void citire() = 0;
    virtual void afisare();
};

void Produs::citire(){cin>>nume;}
void Produs::afisare(){cout<<"Baza: "<<nume<<"\n";}
Produs::~Produs(){cout<<"~B\n";}

class Perisabil : public Produs
{
    string data;
public:
    Perisabil(){cout<<"D\n";}
    ~Perisabil(){cout<<"~D\n";}
    void citire(){ Produs::citire(); cin>>data;}
    void afisare(){cout<<"Deriv: "; Produs::afisare(); cout<<data<<endl;}
};

int main()
{
///    Produs ob1;    ob1.citire();    ob1.afisare();
///    Perisabil ob2;     ob2.citire();    ob2.afisare();

Produs* p = new Perisabil();

/// Perisabil* q;  q = p; --- nu se poate direct

delete p;

}
*/


/*
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
*/

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
