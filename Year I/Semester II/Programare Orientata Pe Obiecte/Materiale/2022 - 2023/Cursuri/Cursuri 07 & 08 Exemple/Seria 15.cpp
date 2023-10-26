#include <iostream>

using namespace std;

/**** memory leak ***/

class Baza
{
public:
    Baza(){cout<<"B\n";}
    virtual void f() = 0;
    virtual ~Baza(){cout<<"~B\n";}
};

void Baza::f(){cout<<"elemente din baza";}

class Derivata : public Baza
{
public:
    Derivata(){cout<<"D\n";}
    ~Derivata(){cout<<"~D\n";}
    void f(){  Baza::f();}
};

int main()
{
///    Baza b;
///    Derivata d;
     Baza *p;
///     p = new Baza(); /// nu delete = nu destructor = nu dezalocare = memory leak = scazut nota
///    delete p;
    p = new Derivata();
    p->f();
    delete p; /// nu se dezaloca componentele din derivata
}

/****/
/*
class Baza
{
protected:

public:
    virtual void citire();
    virtual void afisare();
};

class Derivata1 : public Baza
{

public:
    void citire();
    void afisare();
    void f(){cout<<"Propriu\n";}
};

class Derivata2 : public Baza
{

public:
    void citire();
    void afisare();
};

class Derivata3 : public Derivata1
{
public:
    void citire();
    void afisare();
};
int main()
{
    Baza*p = new Derivata1();
    p->citire(); p->afisare();
    ///p->f();
    Derivata1* q;
    ///q = p;
    q = dynamic_cast<Derivata1*>(p);   /// necesar la downcasting
    q->f();

    /// in aceeasi ierarhie, atentie la nivelurile pe care se afla obiectele...

    Derivata3* t;
    t = dynamic_cast<Derivata3*>(p); /// downcast nereusit
    if (t == NULL) cout<<"nu merge";
    else t->afisare();

    Baza *p1;
    p1 = new Derivata3(); /// upcast
    Derivata1* q1;
    q1 = dynamic_cast<Derivata1*>(p1); ///downcast "reusit"
    q1->f();

    /// downcast nu merge daca nu sunt pe aceeasi "ramura din ierarhie"
/*
    Derivata2* t;
    t = dynamic_cast<Derivata2*>(p);
    if (t == NULL) cout<<"nu merge";
    else t->afisare();

    cout<<endl;


    Derivata2* t1;
    t1 = dynamic_cast<Derivata2*>(p);
    t1->afisare();


    Derivata2* t2;
    t2 = (Derivata2*)(p);
    t2->afisare();*/
///    return 0;
///}
/*
void Baza::citire(){cout<<"Baza ";}
void Derivata1::citire(){Baza::citire(); cout<<"si Deriv1  ";}
void Derivata2::citire(){Baza::citire(); cout<<"si Deriv2  ";}
void Derivata3::citire(){Derivata1::citire(); cout<<"si Deriv3  ";}

void Baza::afisare(){cout<<"Afis Baza ";}
void Derivata1::afisare(){Baza::afisare(); cout<<"si Deriv1\n";}
void Derivata2::afisare(){Baza::afisare(); cout<<"si Deriv2\n";}
void Derivata3::afisare(){Derivata1::afisare(); cout<<"si Deriv3\n";}
*/
/**************************/
/*
class Baza
{
protected:
    string x;
public:
    virtual void citire();
    friend ostream& operator<<(ostream&, Baza&);
};

class Derivata : public Baza
{
    int y;
public:
    void citire();
    friend ostream& operator<<(ostream&, Derivata&);
};

int main()
{
    /// Baza b; b.citire(); cout<<b;
    /// Derivata d; d.citire(); cout<<d;
    Baza* p = new Derivata();
    p->citire();
    /// cout<<*p; /// cout din baza
    cout<<*(Derivata*)p;
    cout<<*dynamic_cast<Derivata*>(p);
    return 0;
}

void Baza::citire(){cin>>x;}
void Derivata::citire(){Baza::citire(); cin>>y;}
ostream& operator<<(ostream& out, Baza& ob)
{
    out<<"Baza: "<<ob.x<<endl; return out;
}

ostream& operator<<(ostream& out, Derivata& ob)
{
    /// out<<"Derivata: "<<ob.x<<" "<<ob.y<<endl; return out;
    out<<(Baza&)ob << "Derivata: "<<ob.y<<endl; return out;
}
*/
