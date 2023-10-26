#include <iostream>
#include <typeinfo>

using namespace std;

class avocat
{
    int cod;
    string nume;
    int nrProcese; // lungimea vectorului de procese
    int *vectorProcese; // suma primita pentru fiecare proces
    static int index; // counter pentru numarul total de avocati creati

public:
    avocat(); // constructor neparametrizat
    avocat(int cod, string nume, int nrProcese, int*vectorProcese); // constructor parametrizat
    avocat(const avocat &a); // constructor de copiere
    virtual ~avocat(); // destructor virtual
    avocat& operator=(const avocat &a); // operatorul =

    friend istream& operator>> (istream& in, avocat& a); // operatorul de citire
    friend ostream& operator<< (ostream& out, const avocat& a); // operatorul de afisare
    virtual ostream& afisareVirtuala (ostream& out) const; // afisarea prin functie virtuala

    static int getIndex() { return index; } // inline pentru o executare mai rapida
    static void crestereIndex() { index++; }

    bool operator> (const avocat &a); // supraincarcarea operatorilor de comparare
    bool operator< (const avocat &a);
};

avocat::avocat() // constructor neparametrizat
{
    cod = 0;
    nume = "anonim";
    nrProcese = 0;
    vectorProcese = new int[100];
    *vectorProcese = 0;
}

avocat::avocat(int cod, string nume, int nrProcese, int* vectorProcese) // constructor parametrizat
{
    this->cod = cod;
    this->nume = nume;
    this->nrProcese = nrProcese;
    this->vectorProcese = new int[100];
    this->vectorProcese = vectorProcese;
}

avocat::avocat(const avocat &a) // constructor de copiere
{
    this->cod = a.cod;
    this->nume = a.nume;
    this->nrProcese = a.nrProcese;
    this->vectorProcese = new int[100];
    this->vectorProcese = a.vectorProcese;
}

avocat::~avocat() // destructor virtual
{
    cod = 0;
    nume = "anonim";
    nrProcese = 0;
    if (vectorProcese != NULL) delete[] vectorProcese;
}

avocat& avocat::operator= (const avocat &a) // operatorul =
{
    if (vectorProcese != NULL) delete[] vectorProcese;
    if(this != &a)
    {
        this->cod = a.cod;
        this->nume = a.nume;
        this->nrProcese = a.nrProcese;
        this->vectorProcese = a.vectorProcese;
    }

    return *this;
}

istream& operator>> (istream& in, avocat& a) // operatorul de citire
{
    cout<<"Cod avocat: ";
    in>> a.cod;
    cout<<"Nume avocat: ";
    in>>a.nume;
    cout<<"Numar procese: ";
    in>>a.nrProcese;
    cout<<"Suma primita pentru fiecare proces: ";
    for (int i = 0; i < a.nrProcese; i++)
        in>>a.vectorProcese[i];

    return in;
}

ostream& operator<< (ostream& out, const avocat& a) // operatorul de afisare
{
    return a.afisareVirtuala(out);
}

ostream& avocat::afisareVirtuala(ostream& out) const // afisarea virtuala
{
    out<<"Cod avocat: "<<cod;
    out<<"\nNume avocat: "<<nume;
    out<<"\nNumar procese: "<<nrProcese;
    out<<"\nSuma primita pentru fiecare proces: ";
    for (int i = 0; i < nrProcese; i++)
        out<<vectorProcese[i]<<" ";

    return out;
}

bool avocat::operator> (const avocat &a) // operatorul >
{
    return nrProcese > a.nrProcese;
}

bool avocat::operator< (const avocat &a) // operatorul <
{
    return nrProcese < a.nrProcese;
}

class avocatOficiu : public avocat
{
    string numeClient;
    int durata;

public:
    avocatOficiu(); // constructor neparametrizat
    avocatOficiu(int cod, string nume, int nrProcese, int*vectorProcese, string numeClient, int durata); // constructor parametrizat
    avocatOficiu(const avocatOficiu &a); // constructor de copiere
    ~avocatOficiu(); // destructor
    avocatOficiu& operator=(const avocatOficiu &a); // operatorul =

    friend istream& operator>> (istream& in, avocatOficiu& a); // operatorul de citire
    virtual ostream& afisareVirtuala(ostream& out) const; // afisarea virtuala

    avocatOficiu maximClient (avocatOficiu* lista[100], int c); // metoda ce returneaza avocatul din oficiu cu durata maxima
};

avocatOficiu::avocatOficiu() : avocat() // constructor neparametrizat
{
    numeClient = "anonim";
    durata = 0;
}

avocatOficiu::avocatOficiu(int cod, string nume, int nrProcese, int*vectorProcese, string numeClient, int durata) : avocat(cod, nume, nrProcese, vectorProcese)
{
    this->numeClient = numeClient;
    this->durata = durata;
}

avocatOficiu::avocatOficiu(const avocatOficiu &a) : avocat(a) // constructor de copiere
{
    numeClient = a.numeClient;
    durata = a.durata;
}

avocatOficiu::~avocatOficiu() // destructor
{
    numeClient = "anonim";
    durata = 0;
}

avocatOficiu& avocatOficiu::operator=(const avocatOficiu &a) // operatorul =
{
    if(this != &a)
    {
        avocat :: operator =(a);
        numeClient = a.numeClient;
        durata = a.durata;
    }
    return *this;
}

istream& operator>> (istream& in, avocatOficiu& a) // operatorul de citire
{
    in>> (avocat&)a; // upcasting
    cout<<"Nume client: ";
    in>>a.numeClient;
    cout<<"Durata petrecuta cu clientul: ";
    in>>a.durata;

    return in;
}

ostream& avocatOficiu::afisareVirtuala(ostream& out) const // afisarea virtuala
{
    avocat::afisareVirtuala(out);
    out<<"\nNume client: "<<numeClient;
    out<<"\nDurata petrecuta cu clientul: "<<durata;

    return out;
}

avocatOficiu avocatOficiu::maximClient (avocatOficiu* lista[100], int c) // metoda ce returneaza avocatul din oficiu cu durata maxima
{
    int maxim = 0;
    avocatOficiu av;
    for (int i = 0; i < c; i++)
    {
        if (lista[i]->durata > maxim)
        {
            maxim = lista[i]->durata;
            av = *lista[i];
        }
    }
    return av;
}

int avocat::index = 0; // indexarea avocatilor se face de la 0

int main()
{
    avocat* listaAvocati[100];
    avocatOficiu* listaOficiu[100];
    int c = 0;

    int k = 1;

    while (k == 1) // meniu interactiv
    {
        cout<<"-------------------------------------------------------\n";
        cout<<"Tasteaza 1 pentru a citi un avocat\n";
        cout<<"Tasteaza 2 pentru a citi un avocat din oficiu\n";
        cout<<"Tasteaza 3 pentru a afisare avocatul cu numarul n\n";
        cout<<"Tasteaza 4 pentru a afisa toti avocatii\n";
        cout<<"Tasteaza 5 pentru a afisa avocatii din oficiu\n";
        cout<<"Tasteaza 6 pentru a sorta crescator avocatii dupa numarul de procese\n";
        cout<<"Tasteaza 7 pentru a sorta descrescator avocatii dupa numarul de procese\n";
        cout<<"Tasteaza 8 pentru a afisa avocatul din oficiu care a petrecut timpul maxim cu un client\n";
        cout<<"Tasteaza 0 pentru a iesi din program\n";
        cout<<"-------------------------------------------------------\n";

        int comanda;
        static int ctr;

        cin >> comanda;

        switch(comanda)
        {
            case 1: // citire avocat
            {
                ctr = avocat::getIndex();
                listaAvocati[ctr] = new avocat();
                cin>>*listaAvocati[ctr];
                listaAvocati[ctr]->crestereIndex();
                break;
            }
            case 2: // citire avocat oficiu
            {
                ctr = avocat::getIndex();

                listaAvocati[ctr] = new avocatOficiu();
                cin>>static_cast<avocatOficiu&>(*listaAvocati[ctr]); // downcasting
                listaAvocati[ctr]->crestereIndex();

                listaOficiu[c] = new avocatOficiu();
                *listaOficiu[c] = static_cast<avocatOficiu&>(*listaAvocati[ctr]);
                c++;

                break;
            }
            case 3: // afisarea obiectului n
            {
                ctr = avocat::getIndex();
                int n;
                cout<<"n = ";
                cin>>n;
                if (n <= ctr) cout<<*listaAvocati[n-1];
                else cout<<"nu exista";
                cout<<endl;
                break;
            }
            case 4: // afisare toti avocatii
            {
                ctr = avocat::getIndex();
                for (int i = 0; i < ctr; i++)
                    cout<<*listaAvocati[i]<<endl<<endl;
                break;
            }
            case 5: // afisare avocati oficiu
            {
                for (int i = 0; i < c; i++)
                     cout<<*listaOficiu[i]<<endl<<endl;
                break;
            }
            case 6: // sortare crescator
            {
                avocat aux;
                for (int i = 0; i < ctr - 1; i++)
                    for (int j = i + 1; j < ctr; j++)
                    if (*listaAvocati[i] > *listaAvocati[j])
                {
                    aux = *listaAvocati[i];
                    *listaAvocati[i] = *listaAvocati[j];
                    *listaAvocati[j] = aux;
                }
                cout<< "sortat crescator\n";
                break;
            }
            case 7: // sortare descrescator
            {
                avocat aux;
                for (int i = 0; i < ctr - 1; i++)
                    for (int j = i + 1; j < ctr; j++)
                    if (*listaAvocati[i] < *listaAvocati[j])
                {
                    aux = *listaAvocati[i];
                    *listaAvocati[i] = *listaAvocati[j];
                    *listaAvocati[j] = aux;
                }
                cout<< "sortat descrescator\n";
                break;
            }
            case 8: // avocat durata maxima
            {
                cout<<listaOficiu[0]->maximClient(listaOficiu, c);
                cout<<endl;
                break;
            }
            case 0:
            {
                cout<<"program incheiat\n";
                k = 0;
                break;
            }
            default:
            {
                cout<<"incorect\n";
                break;
            }
        }
    }

    if (listaAvocati != NULL) delete listaAvocati;
    if (listaOficiu != NULL) delete listaOficiu;

    return 0;
}
