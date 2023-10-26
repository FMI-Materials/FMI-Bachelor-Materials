#include <iostream>

using namespace std;

/***************************      date si functii membre statice     ****************************/

class Test
{
    static int x;
    int y;
public:
    void functie_nestatica(){}
    static void f1(){cout<<x<<endl;}
static void f2(){
    ///cout<<y<<endl;
    /// functie_nestatica();
}
    static void f3(Test o){cout<<o.x<<" "<<o.y<<endl;} /// ok cu accesarea pt ca Test o este parametru formal, deci pe stiva lui f3
    static void f4(){Test o; cout<<o.x<<" "<<o.y<<endl;}
///    static void f5() {cout<< this->x <<endl;} /// nu exista pointerul this in functii statice
};

int Test::x;

int main()
{
    Test::f1(); /// functiile membre statice au acces la datele statice
    Test ob;
    ob.f1(); /// se pot apela si ca functiile nestatice obiect.functie

   /// Test::f2(); /// functiile membre statice NU pot accesa datele nestatice sau functiile nestatice

    Test::f3(ob);  /// functiile statice pot accesa var locale/param locali, chiar daca acestea au in componenta date statice sau nu
    Test::f4();

 ///   Test::f5();
    return 0;
}


/*
class Test
{
    public:    /// EXCEPTIE DIDACTICA - a nu se folosi des
static int nrobiecte;

public:
    Test(){nrobiecte++;}
    ~Test(){nrobiecte--;}
};

int Test::nrobiecte; /// nu se mai creeaza copii pt fiecare obiect ci se partajeaza aceeasi zona de memorie; echivalent global

void f()
{Test X;}

int main()
{
    Test A,B;
    cout<<Test::nrobiecte<<" "<<A.nrobiecte<<" "<<B.nrobiecte<<endl;
    {
        Test C;
        cout<<Test::nrobiecte;
        Test D;
        cout<<Test::nrobiecte;
    }
    f();
    cout<<X;??????? X e deja distrus la finalul apelului de functie
    cout<<Test::nrobiecte;
    return 0;
}
*/

/*
/// est ok exemplul dpv al POO? Relativ ok; a se evita variabile publice in POO; Rezolvare? STATIC

class Test
{

};

int nrobiecte; /// MAI BINE NU; Global = public; datele tb sa fie private <=> doar functiile sa fie publice

int main()
{
    Test A;
    nrobiecte++;
    cout<<nrobiecte;
    return 0;
}
*/
