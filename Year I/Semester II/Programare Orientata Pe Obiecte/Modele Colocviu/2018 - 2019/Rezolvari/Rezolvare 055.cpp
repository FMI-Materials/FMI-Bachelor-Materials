#include <iostream>
#include <vector>
#include <string>
using namespace std;

//------------------------------------------------------STATIE-----------------------------------------

class Statie{
private:
    string strada;
    int number;
    int sector;
    vector <string> masini;
    static int id;
    int cod;
    string denumire;
    string tip;
    string cod_statie;
    bool important;

public:
    const string &getStrada() const;
    void setStrada(const string &strada);

    int getNumber() const;
    void setNumber(int number);

    int getSector() const;
    void setSector(int sector);

    const vector<string> &getMasini() const;
    void setMasini(const vector<string> &masini);

    static int getId();
    static void setId(int id);

    int getCod() const;
    void setCod(int cod);

    const string &getDenumire() const;
    void setDenumire(const string &denumire);

    const string &getTip() const;
    void setTip(const string &tip);

    const string &getCodStatie() const;
    void setCodStatie(const string &codStatie);

    bool isImportant() const;
    void setImportant(bool important);

    Statie();
    Statie(const Statie& statie);
    Statie& operator=(const Statie& statie);
    Statie(const string &strada, int number, int sector, const vector<string> &masini, const string &denumire,
           const string &tip, bool important);

    friend istream& operator>>(istream& is, Statie& statie);
    friend ostream& operator<<(ostream& os, Statie& statie);
};
istream& operator>>(istream& is, Statie& statie){
    cout << "Denumire:\n";
    getline(is,statie.denumire);
    cout << "Strada:\n";
    getline(is,statie.strada);
    cout << "Numar:\n";
    is >> statie.number;
    is.get();
    cout << "Sector:\n";
    is >> statie.sector;
    is.get();
    cout << "Masini:\n";
    cout << "Nr masini:\n";
    int nr;
    is >> nr;
    is.get();
    for(int i = 0; i < nr; ++i){
        cout << "Introduceti ingredient:\n";
        string x;
        getline(is, x);
        statie.masini.push_back(x);
    }
    cout << "Tip:\n";
    getline(is,statie.tip);
    cout << "Statie importanta: 1 - da sau 0 - nu\n";
    is >> statie.important;
    is.get();
    if(statie.tip == "urbana")
        statie.cod_statie = string("SU ")  + to_string(statie.cod);
    else
        statie.cod_statie = string("SE ")  + to_string(statie.cod);
    return is;
}
ostream& operator<<(ostream& os, Statie& statie){
    os << "Denumire:" << statie.denumire << '\n';
    os << "Strada: " << statie.strada << '\n';
    os << "Numar: " << statie.number << '\n';
    os << "Sector: " << statie.sector << '\n';
    os << "Masini:\n";
    for(int i = 0;i < statie.masini.size(); ++i){
        os << statie.masini[i] << '\n';
    }
    os << "Statie importanta: " << statie.important << '\n';
    os << "Cod statie: " << statie.cod_statie << '\n';
    return os;

}
int Statie::id = 0;
Statie::Statie():masini() {
    strada = denumire = tip = cod_statie = "";
    number = sector = 0;
    ++id;
    cod = id;
    important = false;
}
Statie::Statie(const Statie &statie) {
    strada = statie.strada;
    denumire = statie.denumire;
    tip = statie.tip;
    cod_statie = statie.cod_statie;
    number = statie.number;
    sector = statie.sector;
    cod = statie.cod;
    important = statie.important;
    masini.clear();
    masini = statie.masini;
}
Statie & Statie::operator=(const Statie &statie) {
    strada = statie.strada;
    denumire = statie.denumire;
    tip = statie.tip;
    cod_statie = statie.cod_statie;
    number = statie.number;
    sector = statie.sector;
    cod = statie.cod;
    important = statie.important;
    masini.clear();
    masini = statie.masini;
    return *this;
}
Statie::Statie(const string &strada, int number, int sector, const vector<string> &masini, const string &denumire,
               const string &tip, bool important) : strada(strada), number(number), sector(sector), masini(masini),
                                                    denumire(denumire), tip(tip), important(important) {
    ++id;
    cod = id;
    if(tip == "urbana")
        cod_statie = string("SU ")  + to_string(cod);
    else
        cod_statie = string("SE ")  + to_string(cod);
}

const string &Statie::getStrada() const {
    return strada;
}

void Statie::setStrada(const string &strada) {
    Statie::strada = strada;
}

int Statie::getNumber() const {
    return number;
}

void Statie::setNumber(int number) {
    Statie::number = number;
}

int Statie::getSector() const {
    return sector;
}

void Statie::setSector(int sector) {
    Statie::sector = sector;
}

const vector<string> &Statie::getMasini() const {
    return masini;
}

void Statie::setMasini(const vector<string> &masini) {
    Statie::masini = masini;
}

int Statie::getId() {
    return id;
}

void Statie::setId(int id) {
    Statie::id = id;
}

int Statie::getCod() const {
    return cod;
}

void Statie::setCod(int cod) {
    Statie::cod = cod;
}

const string &Statie::getDenumire() const {
    return denumire;
}

void Statie::setDenumire(const string &denumire) {
    Statie::denumire = denumire;
}

const string &Statie::getTip() const {
    return tip;
}

void Statie::setTip(const string &tip) {
    Statie::tip = tip;
}

const string &Statie::getCodStatie() const {
    return cod_statie;
}

void Statie::setCodStatie(const string &codStatie) {
    cod_statie = codStatie;
}

bool Statie::isImportant() const {
    return important;
}

void Statie::setImportant(bool important) {
    Statie::important = important;
}


//-------------------------------------------------------MANAGER-------------------------------------------------------
class Manager{
private:
    vector<Statie> statii;

    static Manager* instanta;
    Manager(){}
    Manager(const Manager& m) = default;
    Manager(Manager& m) noexcept = default;
    Manager& operator=(const Manager& m) = default;
    Manager& operator=(Manager& ob) = default;

public:
    static Manager* getInstanta(){
        if(instanta == nullptr)
            instanta = new Manager();
        return instanta;
    }
    void deleteInstanta(){
        if(instanta!= nullptr)
            delete instanta;
        instanta = nullptr;
    }
    ~Manager(){

    }

    void demo();
    void adaugaStatie();
    void afisStatii();
    void afisStatiiAutobuz();
    void calculeazaPret();

};
void Manager::adaugaStatie() {
    Statie s;
    cout << "Introduceti statie:\n";
    cin >> s;
    statii.push_back(s);
}
void Manager::afisStatii() {
    for(int i = 0;i < statii.size(); ++i)
        cout << statii[i] << '\n';
}
void Manager::afisStatiiAutobuz() {
    cout << "Autobuz:\n";
    string bus;
    getline(cin,bus);
    for(int i = 0;i < statii.size(); ++i) {
        for (int j = 0; j < statii[i].getMasini().size(); ++j)
            if (statii[i].getMasini()[j] == bus) {
                cout << statii[i] << '\n';
                break;
            }
    }
}
void Manager::calculeazaPret() {
    string den1, den2;
    cout << "Statie1:\n";
    getline(cin,den1);
    cout << "Statie2:\n";
    getline(cin,den2);
    int poz1, poz2;
    for(int i = 0; i < statii.size(); ++i)
        if(statii[i].getDenumire() == den1){
            poz1 = i;
            break;
        }
    for(int i = 0; i < statii.size(); ++i)
        if(statii[i].getDenumire() == den2){
            poz2 = i;
            break;
        }

    string tip1 = statii[poz1].getCodStatie().substr(0,2);
    string tip2 = statii[poz2].getCodStatie().substr(0,2);
    double pret = 2;
    bool ok = false;
    for(int i = 0; i < statii[poz1].getMasini().size() && !ok; ++i)
        for(int j = 0; j< statii[poz2].getMasini().size() && !ok; ++j)
            if(statii[poz1].getMasini()[i] == statii[poz2].getMasini()[j])\
                        ok = true;
    if(tip1 == tip2 && tip1 == "RU")
        if(ok == false)
            pret = pret + 0.15 * pret;
        else
            pret = 2;
    else
        if(tip1 == tip2 && tip1 == "RE")
            if(ok == true)
                pret = pret + 0.2 * pret;
            else
                pret = pret + 0.25 * pret;
        else
            if(tip1 != tip2)
                if(ok == true)
                    pret = pret + 0.3 * pret;
                else
                    pret = pret + 0.4 * pret;

    cout << "Pret: " << pret << '\n';
}
void Manager::demo() {

}
Manager* Manager::instanta = nullptr;

int main() {
    int optiune;
    Manager* m = m->getInstanta();
    while(1){
        cout << "0.Demo\n";
        cout << "1.adaugaStatie\n";
        cout << "2.afisStatii\n";
        cout << "3.afisStatiiAutobuz\n";
        cout << "4.calculeazaPret\n";
        cout << "5.inchide\n";

        try{
            cin >> optiune;
            cin.get();
            if(optiune < 0 || optiune > 11)
                throw string("Optiune gresita!");
            else{ if(optiune == 0) m->demo();
                if (optiune == 1) m->adaugaStatie();
                else if (optiune == 2) m->afisStatii();
                else if (optiune == 3) m->afisStatiiAutobuz();
                else if (optiune == 4) m->calculeazaPret();
                else if (optiune == 5)  break;

            }
        }
        catch (string s){
            cout << s << '\n';
        }


    }
    m->deleteInstanta();

    return 0;
}