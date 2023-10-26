#include <iostream>
#include <array>
#include <typeinfo>
#include <tuple>

using namespace std;

class gestionareFarmacii
{
private:
    static int index; // indexul pentru contorizarea tuturor farmaciilor
    const int id = 1000; // id-ul lantului de farmacii
public:
    gestionareFarmacii(); // constructor fara parametrii
    gestionareFarmacii(const gestionareFarmacii &f); // constructor de copiere
    gestionareFarmacii& operator= (const gestionareFarmacii &f); // operatorul =
    virtual ~gestionareFarmacii(); // destructor virtual

    friend istream& operator>> (istream& in, gestionareFarmacii& f); //operatorul de citire
    friend ostream& operator<< (ostream& out, const gestionareFarmacii& f); // operatorul de afisare
    virtual istream& citireVirtuala (istream& in); // functie de citire virtuala
    virtual ostream& afisareVirtuala (ostream& out) const; // functie de afisare virtuala

    static int getIndex() { return index; }
    const int getId() const { return id; }
};
gestionareFarmacii::gestionareFarmacii()
{
    index++;
}
gestionareFarmacii::gestionareFarmacii(const gestionareFarmacii &f)
{
    index++;
}
gestionareFarmacii& gestionareFarmacii::operator= (const gestionareFarmacii &f)
{

}
gestionareFarmacii::~gestionareFarmacii()
{
    index--;
}
istream& operator>> (istream& in, gestionareFarmacii& f)
{
    return f.citireVirtuala(in);
}
ostream& operator<< (ostream& out, const gestionareFarmacii& f)
{
    return f.afisareVirtuala(out);
}
istream& gestionareFarmacii::citireVirtuala (istream& in)
{
    return in;
}
ostream& gestionareFarmacii::afisareVirtuala (ostream& out) const
{
    return out;
}

class farmacie : public gestionareFarmacii
{
private:
    string denumire;
    int nrAngajati;
    array<int,12> profituri;
public:
    farmacie(); // constructor fara parametrii
    farmacie(string denumire, int nrAngajati, array<int,12> profituri); // constructor cu parametrii
    farmacie(const farmacie &f); // constructor de copiere
    farmacie& operator= (const farmacie &f); // operatorul =
    ~farmacie(); // destructor

    virtual istream& citireVirtuala (istream& in); // functie de citire virtuala
    virtual ostream& afisareVirtuala (ostream& out) const; // functie de afisare virtuala
};

farmacie::farmacie() : gestionareFarmacii()
{
    denumire = "anonim";
    nrAngajati = 0;
    profituri = {0};
}
farmacie::farmacie(string denumire, int nrAngajati, array<int,12>profituri) : gestionareFarmacii()
{
    this->denumire = denumire;
    this->nrAngajati = nrAngajati;
    for (int i = 0; i < profituri.size(); i++)
        this->profituri[i] = profituri[i];
}
farmacie::farmacie (const farmacie &f) : gestionareFarmacii(f)
{
    this->denumire = f.denumire;
    this->nrAngajati = f.nrAngajati;
    for (int i = 0; i < profituri.size(); i++)
        this->profituri[i] = f.profituri[i];
}
farmacie& farmacie::operator= (const farmacie &f)
{
    gestionareFarmacii::operator =(f);
    this->denumire = f.denumire;
    this->nrAngajati = f.nrAngajati;
    for (int i = 0; i < profituri.size(); i++)
        this->profituri[i] = f.profituri[i];

    return *this;
}
farmacie::~farmacie()
{
    denumire = "anonim";
    nrAngajati = 0;
    profituri = {0};
}
istream& farmacie::citireVirtuala(istream& in)
{
    gestionareFarmacii::citireVirtuala(in);
    cout<< "Denumire farmacie: ";
    in>> denumire;
    cout<< "Numarul de angajati: ";
    in>> nrAngajati;
    cout<< "Profituri per luna: ";
    for (int i = 0; i < profituri.size(); i++)
        in>> profituri[i];
    cout<<endl;

    return in;
}
ostream& farmacie::afisareVirtuala(ostream& out) const
{
    gestionareFarmacii::afisareVirtuala(out);
    out<< "Denumire farmacie: ";
    out<< denumire;
    out<< "\nNumarul de angajati: ";
    out<< nrAngajati;
    out<< "\nProfituri per luna: ";
    out<< profituri[0];
    for (int i = 1; i < profituri.size(); i++)
        out<<", "<< profituri[i];
    out<<endl;

    return out;
}


class farmacieOnline : public gestionareFarmacii
{
private:
    tuple<string, int, int> tuplu;
public:
    farmacieOnline(); // constructor fara parametrii
    farmacieOnline(string adresaWeb, int nrVizitatori, int discount); // constructor cu parametrii
    farmacieOnline(const farmacieOnline &f); // constructor de copiere
    farmacieOnline& operator= (const farmacieOnline &f); // operatorul =
    ~farmacieOnline(); // destructor

    virtual istream& citireVirtuala (istream& in); // functie de citire virtuala
    virtual ostream& afisareVirtuala (ostream& out) const; // functie de afisare virtuala
};

farmacieOnline::farmacieOnline() : gestionareFarmacii()
{
    tuplu = make_tuple("anonima", 0, 0);
}
farmacieOnline::farmacieOnline(string adresaWeb, int nrVizitatori, int discount) : gestionareFarmacii()
{
    this->tuplu = make_tuple(adresaWeb, nrVizitatori, discount);
}
farmacieOnline::farmacieOnline (const farmacieOnline &f) : gestionareFarmacii(f)
{
    this->tuplu = f.tuplu;
}
farmacieOnline& farmacieOnline::operator= (const farmacieOnline &f)
{
    gestionareFarmacii::operator =(f);
    this->tuplu = f.tuplu;

    return *this;
}
farmacieOnline::~farmacieOnline()
{
    tuplu = make_tuple("anonima", 0, 0);
}

istream& farmacieOnline::citireVirtuala(istream& in)
{
    gestionareFarmacii::citireVirtuala(in);
    cout<< "Adresa web farmacie online: ";
    in>> get<0>(tuplu);
    cout<< "Numarul de vizitatori: ";
    in>> get<1>(tuplu);
    cout<< "Discount: ";
    in>> get<2>(tuplu);
    cout<<endl;

    return in;
}
ostream& farmacieOnline::afisareVirtuala(ostream& out) const
{
    gestionareFarmacii::afisareVirtuala(out);
    out<< "Adresa web farmacie online: ";
    out<< get<0>(tuplu);
    out<< "\nNumarul de vizitatori: ";
    out<< get<1>(tuplu);
    out<< "\nDiscount: ";
    out<< get<2>(tuplu);
    out<<endl;

    return out;
}

class menu // clasa singleton
{
private:
    static menu* m;

    menu() { } // constructor privat
    menu(const menu &m) = delete; // stergem constructorul de copiere
    menu& operator= (const menu &m) = delete; // stergem operatorul =
public:
    static menu* getMenu(); // returneaza meniul
    void runMenu(); // ruleaza meniul
    void deleteMenu(); // dezaloca memoria atribuita meniului
};


menu* menu::getMenu()
{
    if(!m) m = new menu(); // daca nu exista deja un obiect, il creeaza

    return m;
}
void menu::runMenu()
{
    gestionareFarmacii *listaFarmacii[100];

    int k = 1;

    while (k == 1) // meniu interactiv
    {
        cout<<"-------------------------------------------------------\n";
        cout<<"Tasteaza 1 pentru a citi o farmacie\n";
        cout<<"Tasteaza 2 pentru a citi o farmacie online\n";
        cout<<"Tasteaza 3 pentru a afisare toate farmaciile\n";
        cout<<"Tasteaza 4 pentru a afisa farmaciile fizice\n";
        cout<<"Tasteaza 5 pentru a afisa farmaciile online\n";
        cout<<"Tasteaza 6 pentru a afisa farmacia de ordin n\n";
        cout<<"Tasteaza 7 pentru a afisa id-ul lantului de farmacii\n";
        cout<<"Tasteaza 8 pentru a afisa numarul total de farmacii\n";
        cout<<"Tasteaza 0 pentru a iesi din program\n";
        cout<<"-------------------------------------------------------\n";

        int comanda;
        static int ctr;

        cin >> comanda;

        switch(comanda)
        {
            case 1: // citire farmacie
            {
                ctr = gestionareFarmacii::getIndex();

                listaFarmacii[ctr] = new farmacie();
                cin>>*listaFarmacii[ctr];
                break;
            }
            case 2: // citire farmacie online
            {
                ctr = gestionareFarmacii::getIndex();

                listaFarmacii[ctr] = new farmacieOnline();
                cin>>*listaFarmacii[ctr];

                break;
            }
            case 3: // afisare toate farmaciile
            {
                ctr = gestionareFarmacii::getIndex();

                for (int i = 0; i < ctr; i++)
                    cout<<*listaFarmacii[i]<<endl;
                break;
            }
            case 4: // afisare farmacii fizice
            {
                ctr = gestionareFarmacii::getIndex();

                for (int i = 0; i < ctr; i++)
                    if(typeid(*listaFarmacii[i]) == typeid(farmacie))
                       cout<<*listaFarmacii[i]<<endl;
                break;
            }
            case 5: // afisare farmacii online
            {
                ctr = gestionareFarmacii::getIndex();

                for (int i = 0; i < ctr; i++)
                    if(typeid(*listaFarmacii[i]) == typeid(farmacieOnline))
                       cout<<*listaFarmacii[i]<<endl;
                break;
            }
            case 6: // afisare farmacie de ordin n
            {
                int n;
                cout<<"n = ";
                cin>>n;

                ctr = gestionareFarmacii::getIndex();

                try
                {
                    if (n <= ctr) cout<<*listaFarmacii[n-1];
                    else throw n;
                }
                catch(int n)
                {
                    cout<<"Nu exista "<<n<<" farmacii";
                }

                cout<<endl;
                break;
            }
            case 7: // afisare id
            {
                cout<<"Id: "<<listaFarmacii[0]->getId();
                cout<<endl;
                break;
            }
            case 8: // afisare numarul total de farmacii
            {
                cout<<"Numar total de farmacii: ";
                cout<<listaFarmacii[0]->getIndex();
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

    if (listaFarmacii != NULL) delete listaFarmacii;
}
void menu::deleteMenu()
{
    if (m != NULL) delete m;
}

menu* menu::m = 0;

int gestionareFarmacii::index = 0; // indexarea farmaciilor se incepe de la 0

int main()
{
    menu* meniuFarmacii = meniuFarmacii->getMenu();
    meniuFarmacii->runMenu();
    meniuFarmacii->deleteMenu();
}
