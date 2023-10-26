#include <iostream>

using namespace std;

/// ********************************        clase imbricate (nested)

/******* functiile membre trebuie declarate si definite in clasa interioara sau in afara clasei exterioare **************/
/******* ok si date statice definite ca mai sus *************************/
/******* ok variabile globale *********/

int global = 300;

class X{
    public: /// doar didactic - pt a avea acces la x
    class Test
    {
    static int A;
    int x;
public:
    void set(int i);   /// set(i) declarat in clasa si INCERCAT definire in afara clasei interioare = fail, dar exterioare ok
    int get(){return A + x + global;}  /// get() e declarata + definita in clasa locala, deci ok
    }ob2;
//    void Test::set(int i){ x = i;}   /// in clase nested nu se pot defini functiile in afara clasei interioare, dar exterior ok
};
    int X::Test::A = 90;
    void X::Test::set(int i){ x = i;}   /// in clase nested nu se pot defini functiile in afara clasei interioare, dar exterior ok

int main()
{
    X ob;
    ob.ob2.set(100);
    cout<<ob.ob2.get();
    return 0;
}

/*****************************************************************************************************************/
/// ********************************        clase in functii

/*************** clasele locale nu pot avea date membre statice dar pot folosi functii membre statice **********/
/*
void f()
{
    class Test
    {
///        static int incercare;   /// nu pot exista date statice in clasele locale
        int x;
    public:
        static void afis(){cout<<"Incercare functie membra statica\n";}   /// pot avea functii statice
    };
///    int Test::incercare;   /// declaratie gresita - nu pot exista date statice in clasele locale
    Test::afis();
}

int main()
{
    f();
    return 0;
}
*/

/*************** clasele locale pot accesa alte clase locale din aceeasi functie ******************/
/*
void f()
{
    class Test
    {
        int x;
    public:
        int get()
        {
            x = 1000; return x;
        }
    };

    class Test2
    {
        Test ob;
    public:
        void afis() { cout<<ob.get() + 2000; }
    };

    Test2 ob;
    ob.afis();
}

int main()
{
    f();
    return 0;
}
*/

/*************** clasele locale pot accesa variabilele locale statice din functie si variabile globale **********/
/*
int global = 2000;
void f()
{
    static int xlocal = 1000;
    class Test
    {
        int x;
    public:
        void afis()
        {
            x = 4000;
            cout<<x + xlocal + global;   /// functiile membre din clasa locala pot accesa variabilele locale statice din f()
        }
    };
    Test ob;
    ob.afis();
}

int main()
{
    f();
    return 0;
}
*/

/*************** clasele locale nu pot accesa variabilele locale din functie **********/
/*
void f()
{
    int xlocal;
    class Test
    {
        int x;
    public:
        int get()
        {
///            cout<<xlocal;   /// functiile membre din clasa locala nu pot accesa variabilele locale din f()
            return x;
        }
    };
}

int main()
{
    f();
    return 0;
}
*/

/******* functiile membre trebuie declarate si definite in clasa *******************************/
/*
void f()
{
    class Test
    {
    int x;
public:
    void set(int i);   /// set(i) declarat in clasa si INCERCAT definire in afara clasei = fail
    int get(){return x;}  /// get() e declarata + definita in clasa locala, deci ok
    };
    void Test::set(int i){ x = i;}   /// in clase locale nu se pot defini functiile in afara clasei
}

int main()
{
    f();
    return 0;
}
*/

