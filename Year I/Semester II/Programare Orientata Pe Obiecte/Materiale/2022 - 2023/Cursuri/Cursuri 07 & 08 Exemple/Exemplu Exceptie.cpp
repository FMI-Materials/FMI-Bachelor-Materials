#include <iostream>

using namespace std;

void g()
{
    cout<<"inainte in g\n";
        throw 100;
    cout<<"dupa in g\n";
}

void f()
{
    cout<<"inainte in f\n";
        g();
    cout<<"dupa in f\n";
}

int main()
{
    try
    {
        cout<<"inainte in main\n";
        f();
        cout<<"dupa in main\n";
    }
    catch(int x)
    {
        cout<<"prins in main\n";
    }
    cout<<"rest in main\n";
}

/*
/// nu e apel de functie
void g(int x)
{
    cout<<"in g\n";
    throw 1;
    cout<<"in g dupa throw\n";
}

void f(int x)
{
    try{
    cout<<"in f\n";
    g(x);
    cout<<"in f dupa apel g(x)\n";
    }
    catch(int x){cout<<"catch nou"; throw;}
}

int main()
{
    int x;
    try
    {
        x = -10;
        if (x < 0) f(x);
        cout<<"dupa try in main\n";
    }
    catch(int x)
    {
        cout<<"prins in f(g)\n";
    }
    cout<<"in main\n";
    return 0;
}
*/

