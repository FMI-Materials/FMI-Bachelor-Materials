#include <iostream>
#include <memory>

using namespace std;

class Baza
{
public:
    Baza(int n=99){cout<<"B\n";}
    ~Baza(){cout<<"~B\n";}
};

class Derivata: public Baza
{
public:
    Derivata(){cout<<"D\n";}
    ~Derivata(){cout<<"~D\n";}
};

int main()
{
    /*
    Baza *ob = new Derivata();
    delete ob;
*/
    shared_ptr<Baza> ob2 = make_shared<Derivata>();
    shared_ptr<Derivata> ob3 = static_pointer_cast<Derivata> (ob2);
    cout<<endl<<ob2.use_count()<<endl;
}

/////////////////////////////////////////////////////////////////////////////

#include <iostream>
#include <vector>
#include <typeinfo>
#include <ctime>
#include <cstdlib>
#include <memory>

using namespace std;

class Poveste
{
protected:
    string nume;
public:
    virtual void citire();
    virtual void afisare();
};

class Basm : public Poveste
{
    bool popular;
public:
    void citire();
    void afisare();
};

class Legenda : public Poveste
{
    string autor;
public:
    void citire();
    void afisare();
};

int main()
{
    srand(time(0));
    /*
    vector<Poveste*> v;
    int n; /// nr obiecte
    ///cin>>n;
    n = 10;
    for(int i = 0; i<n; i++)
        {
            if (rand()%2 == 1) v.push_back(new Basm());
        else v.push_back(new Legenda());
        }
    for(auto& p : v)
        if (typeid(*p) == typeid(Basm)) cout<<"Basm\n";
    else cout<<"Legenda\n";
    */

    vector<shared_ptr<Poveste>> v;
    int n; /// nr obiecte
    ///cin>>n;
    n = 10;
    for(int i = 0; i<n; i++)
        {
            if (rand()%2 == 1) v.push_back(make_shared<Basm>());
        else v.push_back(make_shared<Legenda>());
        }

    for(auto& p : v)
        if (typeid(*p) == typeid(Basm)) cout<<"Basm\n";
    else cout<<"Legenda\n";
    }



//nume_cls(const nume_cls& ob){/* copy-constructor */}
//nume_cls(const nume_cls&& ob) {/* move-constructor */}

/*
int main()
{
    /*
    /// varianta fara STL
    Poveste **v;
    int n; /// nr obiecte
    cin>>n;
    v = new Poveste* [n]; /// v are n locatii de memorie care contine adrese
    for(int i = 0 ; i<n; i++)
    {
        int optiune;
        cout<<"Tip element: 1 - Basm; 2 - Legenda: ";
        cin>>optiune;
        if (optiune == 1) v[i] = new Basm();
        else if (optiune == 2) v[i] = new Legenda();
        v[i] -> citire();
    }
    for(int i = 0; i<n; i++)
        v[i]-> afisare();
        */
    /// ce se intampla daca vreau sa adaug mai mult de n elemente? trebuie o realocare --- complicat/mai multa munca
    /// varianta cu STL
/*
    vector<Poveste*> v;
    int n; /// nr obiecte
    cin>>n;
    for(int i = 0 ; i<n; i++)
    {
        int optiune;
        cout<<"Tip element: 1 - Basm; 2 - Legenda: ";
        cin>>optiune;
        if (optiune == 1) v.push_back(new Basm());
        else if (optiune == 2) v.push_back(new Legenda());
    }

    for(auto p = v.begin(); p != v.end(); p++)  /// in loc de auto p... vector<Poveste*>::iterator p
        (**p).citire();  /// (*p)->citire();

        /*
    for (auto p = v.begin(); p != v.end(); p++)
        (*p)->afisare();
        */

/*    for (auto p : v)   /// varianta for(auto& p : v) pentru a evita copierea efectiva in p a elem din v; evitam constr de copiere
        p->afisare();*/
/// posibila problema: in clase datem membre de tip pointeri; alocati in contr de init/param; dezalocati in destr si "uit"
/// sa rescriu si constr de copiere/operator de atribuire --> se foloseste CC default, bit cu bit

/// RTTI - identificarea tipului la executie --- 1) typeid 2) dynamic_cast sau extra 3) smart_pointer

/*
    Poveste* aa, bb;
    aa = new Poveste();
    cout<<typeid(aa).name();

    if (typeid(aa) == typeid(Poveste*)) cout<<"\nda";
    else cout<<"\nnu";

    if (typeid(*aa) == typeid(bb)) cout<<"\nda";
    else cout<<"\nnu";

    aa = new Basm();
    if (typeid(*aa) == typeid(bb)) cout<<"\nda";
    else cout<<"\nnu";

    /// cu dynamic_cast
cout<<endl;
    Poveste *cc = dynamic_cast<Poveste*>(aa);
    if (cc) cout<<"Posibil\n";
    else cout<<"Imposibil\n";



    return 0;
}

*/
void Poveste::citire() { cin>>nume; }
void Poveste::afisare() { cout<<nume<<"   ";}

void Basm :: citire() { cout<<"Citeste basm: "; Poveste :: citire(); cin>>popular; }
void Basm :: afisare() { cout<<"Afisare basm: "; Poveste :: afisare(); cout<<popular<<"\n";}

void Legenda :: citire() { cout<<"Citeste legenda: "; Poveste :: citire(); cin>>autor; }
void Legenda :: afisare() { cout<<"Afisare legenda: "; Poveste :: afisare(); cout<<autor<<"\n";}
