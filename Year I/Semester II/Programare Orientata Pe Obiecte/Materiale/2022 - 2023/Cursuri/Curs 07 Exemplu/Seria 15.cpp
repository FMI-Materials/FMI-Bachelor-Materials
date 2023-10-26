#include <iostream>

using namespace std;

/// atentie la supraincarcarea functiilor virtuale in context mostenire in diamant
/*
class Baza
{
protected:
    int x;
public:
    virtual void f(){ x = 1;}
};

class A : virtual public Baza
{
public:
    void f(){ x = 2;}
};

class B : public virtual Baza
{
public:
    void f(){ x = 3;}
};

class C : public A, public B
{
public:

};

int main()
{

}
*/
/*
class Baza
{
public:
    virtual void f(){cout<<"Baza\n";}
};

class A : public Baza
{
public:
    void f(){cout<<"A\n";}
    void g(){}
};

int main()
{
    Baza b; b.f();
    A a; a.f();
    Baza*p = new A(); /// upcasting
    p->f();
    Baza& r = a; /// upcasting
    r.f();
///    p->g();
}
*/
/********* probleme mostenire in diamant ****************/
/**
- datele membre din clasa Baza sunt dublate in clasa C; 2 rezolvari posibile:
   - daca e nevoie mentinerea ambelor copii, se poate utiliza operatorul de scop; expl A::x; B::x, Baza::x
   - daca e nevoie doar de o singura copie---> toate clasele participante in mostenirea lui C trebuie sa fie,
   A PRIORI mostenite virtual din clasa initiala
**/
/*
class Baza
{
protected:
    int x;
public:
    void f(){ x = 1;}
};

class A : virtual public Baza
{
public:
    void f(){ x = 2;}
};

class B : public virtual Baza
{
public:
    void f(){ x = 3;}
};

class C : public A, public B
{
public:
    void f(){x = 4; /// ambiguitate; rezolvare cu utilizarea scope-ului A::x = 4;
    }
};

int main()
{
    C ob;
    ob.f();
}
*/

/********* probleme la mostenire (din baza) multipla - ambiguitate functie membra parinti *************/
/*
class A
{
public:
    void f(){}
};

class B
{
public:
    void f(){}
};

class C : public A, public B
{

};

int main()
{
    C ob;
    ob.f();
    return 0;
}
*/
