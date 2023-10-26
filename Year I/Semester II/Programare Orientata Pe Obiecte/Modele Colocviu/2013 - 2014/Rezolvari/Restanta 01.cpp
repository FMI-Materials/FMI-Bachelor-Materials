#include <iostream>
#include <vector>
#include <string>

using namespace std;


//-----------------------------------------------------------ANGAJAT------------------------------------------------
class Angajat{
protected:
    string nume;
    string prenume;
    string tip;
    int zi, luna, an;
    string activitate;
public:
    const string &getNume() const;
    void setNume(const string &nume);

    const string &getPrenume() const;
    void setPrenume(const string &prenume);

    const string &getTip() const;
    void setTip(const string &tip);

    int getZi() const;
    void setZi(int zi);

    int getLuna() const;
    void setLuna(int luna);

    int getAn() const;
    void setAn(int an);

    const string &getActivitate() const;
    void setActivitate(const string &activitate);

    Angajat();
    Angajat(const Angajat& angajat);
    Angajat(const string &nume, const string &prenume, const string &tip, int zi, int luna, int an,const string &activitate);
    Angajat& operator=(const Angajat& angajat);
    virtual ~Angajat();

    virtual istream& readAngajat(istream& is) = 0;
    virtual ostream& printAngajat(ostream& os) = 0;

    friend istream& operator>>(istream& is, Angajat& angajat) {
        return angajat.readAngajat(is);
    }
    friend ostream& operator<<(ostream& os, Angajat& angajat){
        return angajat.printAngajat(os);
    }

    virtual double calculeazaPrima(double number) = 0;

};
Angajat::Angajat() {
    nume = prenume = tip = activitate = "";
    zi = luna = an = 0;
}
Angajat::Angajat(const Angajat &angajat) {
    nume = angajat.nume;
    prenume = angajat.prenume;
    tip = angajat.tip;
    activitate = angajat.activitate;
    zi = angajat.zi;
    luna = angajat.luna;
    an = angajat.an;
}
Angajat & Angajat::operator=(const Angajat &angajat) {
    nume = angajat.nume;
    prenume = angajat.prenume;
    tip = angajat.tip;
    activitate = angajat.activitate;
    zi = angajat.zi;
    luna = angajat.luna;
    an = angajat.an;
    return *this;
}
Angajat::~Angajat() {
    nume.clear();
    prenume.clear();
    tip.clear();
    activitate.clear();
    zi = luna = an = 0;
}


Angajat::Angajat(const string &nume, const string &prenume, const string &tip, int zi, int luna, int an,
                 const string &activitate) : nume(nume), prenume(prenume), tip(tip), zi(zi), luna(luna), an(an),
                                             activitate(activitate) {}

const string &Angajat::getNume() const {
    return nume;
}

void Angajat::setNume(const string &nume) {
    Angajat::nume = nume;
}

const string &Angajat::getPrenume() const {
    return prenume;
}

void Angajat::setPrenume(const string &prenume) {
    Angajat::prenume = prenume;
}

const string &Angajat::getTip() const {
    return tip;
}

void Angajat::setTip(const string &tip) {
    Angajat::tip = tip;
}

int Angajat::getZi() const {
    return zi;
}

void Angajat::setZi(int zi) {
    Angajat::zi = zi;
}

int Angajat::getLuna() const {
    return luna;
}

void Angajat::setLuna(int luna) {
    Angajat::luna = luna;
}

int Angajat::getAn() const {
    return an;
}

void Angajat::setAn(int an) {
    Angajat::an = an;
}

const string &Angajat::getActivitate() const {
    return activitate;
}

void Angajat::setActivitate(const string &activitate) {
    Angajat::activitate = activitate;
}

//-----------------------------------------------------------ANGAJAT PERMANENT------------------------------------------------

class AngajatPermanent: public Angajat{
private:
    int weekend;
    int nrCopii;
public:
    int getWeekend() const;
    void setWeekend(int weekend);

    int getNrCopii() const;
    void setNrCopii(int nrCopii);

    AngajatPermanent();
    AngajatPermanent(const AngajatPermanent& angajat);
    AngajatPermanent(const string &nume, const string &prenume, const string &tip, int zi, int luna, int an,const string &activitate, int weekend, int nrCopii);
    AngajatPermanent& operator=(const AngajatPermanent& angajat);
    ~AngajatPermanent();

    istream& readAngajat(istream& is);
    ostream& printAngajat(ostream& os);

    double calculeazaPrima(double number){
        double prima = number;
        if(activitate == "TESA")
            return prima;
        else {
            double nrAni = 2021 - an;
            prima = prima + nrAni * 0.01 * prima;
            return prima;
        }
    }


};
istream & AngajatPermanent::readAngajat(istream &is) {
    cout << "Nume:\n";
    getline(is, nume);
    cout << "Prenume:\n";
    getline(is, prenume);
    tip = "permanent";
    cout << "Introduceti data:\n";
    cout << "Introduceti an:\n";
    bool bisect = 0;
    int zile[]={0,31,28,31,30,31,30,31,31,30,31,30,31};
    int an;
    is >> an;
    is.get();
    if ((an % 4 == 0 && an % 100!=0) || an%400 == 0 )
        bisect = 1;
    this->an = an;
    cout << "Introduceti luna:\n";
    int luna;
    while(true){
        try{
            is >> luna;
            is.get();
            if(luna < 1 || luna > 12)
                throw string("Luna invalida!");
            else break;
        }
        catch (string s){
            cout << s << '\n';
        }
    }
    this->luna = luna;
    cout << "Introduceti ziua\n";
    int zi;
    while(true){
        try{
            is >> zi;
            is.get();
            if(zi < 1 || (luna == 2 && bisect == 1 && zi > 29) || zi > zile[luna])
                throw string("Zi invalida!");
            else break;
        }
        catch (string s){
            cout << s << '\n';
        }
    }
    cout << "Tipul activitatii (lucrativ sau TESA)\n";
    getline(is, activitate);
    this->zi = zi;
    if(activitate == "TESA"){
        cout << "Weekend:\n";
        is >> weekend;
        is.get();
    }
    else{
        cout << "Nr copii:\n";
        is >> nrCopii;
        is.get();
    }
    return is;

}
ostream & AngajatPermanent::printAngajat(ostream &os) {
    os << "Nume: " << nume << '\n';
    os << "Prenume: " << prenume << '\n';
    os << "Tip: permanent\n";
    os << "Data: " << zi << '/' << luna << '/' << an << '\n';
    os << "Activitate: " << activitate << '\n';
    if(activitate == "TESA")
        os << "Weekend: " << weekend << '\n';
    else
        os << "Nr Copii: " << nrCopii << '\n';
    return os;
}
AngajatPermanent::AngajatPermanent(const AngajatPermanent &angajat) {
    nume = angajat.nume;
    prenume = angajat.prenume;
    tip = angajat.tip;
    activitate = angajat.activitate;
    zi = angajat.zi;
    luna = angajat.luna;
    an = angajat.an;
    weekend = angajat.weekend;
    nrCopii = angajat.weekend;
}
AngajatPermanent & AngajatPermanent::operator=(const AngajatPermanent &angajat) {
    nume = angajat.nume;
    prenume = angajat.prenume;
    tip = angajat.tip;
    activitate = angajat.activitate;
    zi = angajat.zi;
    luna = angajat.luna;
    an = angajat.an;
    weekend = angajat.weekend;
    nrCopii = angajat.weekend;
    return *this;
}
AngajatPermanent::~AngajatPermanent(){
    weekend = nrCopii = 0;
}
AngajatPermanent::AngajatPermanent():Angajat() {
    weekend = nrCopii = 0;
}

AngajatPermanent::AngajatPermanent(const string &nume, const string &prenume, const string &tip, int zi, int luna,
                                   int an, const string &activitate, int weekend, int nrCopii) : Angajat(nume, prenume,
                                                                                                         tip, zi, luna,
                                                                                                         an,
                                                                                                         activitate),
                                                                                                 weekend(weekend),
                                                                                                 nrCopii(nrCopii) {}

int AngajatPermanent::getWeekend() const {
    return weekend;
}

void AngajatPermanent::setWeekend(int weekend) {
    AngajatPermanent::weekend = weekend;
}

int AngajatPermanent::getNrCopii() const {
    return nrCopii;
}

void AngajatPermanent::setNrCopii(int nrCopii) {
    AngajatPermanent::nrCopii = nrCopii;
}



//----------------------------------------------------------ANGAJAT TEMPORAR-------------------------------------------------------

class AngajatTemporar: public Angajat{
private:
    int zi_incheiere, luna_incheiere, an_incheiere;
public:
    int getZiIncheiere() const;
    void setZiIncheiere(int ziIncheiere);

    int getLunaIncheiere() const;
    void setLunaIncheiere(int lunaIncheiere);

    int getAnIncheiere() const;
    void setAnIncheiere(int anIncheiere);

    AngajatTemporar();
    AngajatTemporar(const AngajatTemporar& angajat);
    AngajatTemporar(const string &nume, const string &prenume, const string &tip, int zi, int luna, int an,
                    const string &activitate, int ziIncheiere, int lunaIncheiere, int anIncheiere);
    AngajatTemporar& operator=(AngajatTemporar& angajat);
    ~AngajatTemporar();

    istream& readAngajat(istream& is);
    ostream& printAngajat(ostream& os);

    double calculeazaPrima(double number){
        double prima = number;
        if(an == 2015)
            return prima;
        else {
            prima = 0.5 * prima;
            return prima;
        }
    }

};
istream & AngajatTemporar::readAngajat(istream &is) {
    cout << "Nume:\n";
    getline(is, nume);
    cout << "Prenume:\n";
    getline(is, prenume);
    tip = "plata cu ora";
    cout << "Introduceti data:\n";
    cout << "Introduceti an:\n";
    bool bisect = 0;
    int zile[]={0,31,28,31,30,31,30,31,31,30,31,30,31};
    int an;
    is >> an;
    is.get();
    if ((an % 4 == 0 && an % 100!=0) || an%400 == 0 )
        bisect = 1;
    this->an = an;
    cout << "Introduceti luna:\n";
    int luna;
    while(true){
        try{
            is >> luna;
            is.get();
            if(luna < 1 || luna > 12)
                throw string("Luna invalida!");
            else break;
        }
        catch (string s){
            cout << s << '\n';
        }
    }
    this->luna = luna;
    cout << "Introduceti ziua\n";
    int zi;
    while(true){
        try{
            is >> zi;
            is.get();
            if(zi < 1 || (luna == 2 && bisect == 1 && zi > 29) || zi > zile[luna])
                throw string("Zi invalida!");
            else break;
        }
        catch (string s){
            cout << s << '\n';
        }
    }
    this->zi = zi;
    activitate = "";
    cout << "Introduceti data incheierii:\n";
    cout << "Introduceti an:\n";
    is >> an;
    is.get();
    if ((an % 4 == 0 && an % 100!=0) || an%400 == 0 )
        bisect = 1;
    this->an_incheiere = an;
    cout << "Introduceti luna:\n";
    while(true){
        try{
            is >> luna;
            is.get();
            if(luna < 1 || luna > 12)
                throw string("Luna invalida!");
            else break;
        }
        catch (string s){
            cout << s << '\n';
        }
    }
    this->luna_incheiere = luna;
    cout << "Introduceti ziua\n";
    while(true){
        try{
            is >> zi;
            is.get();
            if(zi < 1 || (luna == 2 && bisect == 1 && zi > 29) || zi > zile[luna])
                throw string("Zi invalida!");
            else break;
        }
        catch (string s){
            cout << s << '\n';
        }
    }
    this->zi_incheiere = zi;
    return is;

}

ostream & AngajatTemporar::printAngajat(ostream &os) {
    os << "Nume: " << nume << '\n';
    os << "Prenume: " << prenume << '\n';
    os << "Tip: permanent\n";
    os << "Data: " << zi << '/' << luna << '/' << an << '\n';
    os << "Data incheiere: " << zi_incheiere << '/' << luna_incheiere << '/' << an_incheiere << '\n';
    return os;
}
AngajatTemporar::AngajatTemporar() : Angajat(){
    zi_incheiere = luna_incheiere = an_incheiere = 0;
}
AngajatTemporar::AngajatTemporar(const AngajatTemporar &angajat) {
    nume = angajat.nume;
    prenume = angajat.prenume;
    tip = angajat.tip;
    activitate = angajat.activitate;
    zi = angajat.zi;
    luna = angajat.luna;
    an = angajat.an;
    zi_incheiere = angajat.zi_incheiere;
    luna_incheiere = angajat.luna_incheiere;
    an_incheiere = angajat.an_incheiere;
}
AngajatTemporar & AngajatTemporar::operator=(AngajatTemporar &angajat) {
    nume = angajat.nume;
    prenume = angajat.prenume;
    tip = angajat.tip;
    activitate = angajat.activitate;
    zi = angajat.zi;
    luna = angajat.luna;
    an = angajat.an;
    zi_incheiere = angajat.zi_incheiere;
    luna_incheiere = angajat.luna_incheiere;
    an_incheiere = angajat.an_incheiere;
    return *this;
}
AngajatTemporar::~AngajatTemporar() {
    zi_incheiere = luna_incheiere = an_incheiere = 0;
}

int AngajatTemporar::getZiIncheiere() const {
    return zi_incheiere;
}

void AngajatTemporar::setZiIncheiere(int ziIncheiere) {
    zi_incheiere = ziIncheiere;
}

int AngajatTemporar::getLunaIncheiere() const {
    return luna_incheiere;
}

void AngajatTemporar::setLunaIncheiere(int lunaIncheiere) {
    luna_incheiere = lunaIncheiere;
}

int AngajatTemporar::getAnIncheiere() const {
    return an_incheiere;
}

void AngajatTemporar::setAnIncheiere(int anIncheiere) {
    an_incheiere = anIncheiere;
}

AngajatTemporar::AngajatTemporar(const string &nume, const string &prenume, const string &tip, int zi, int luna, int an,
                                 const string &activitate, int ziIncheiere, int lunaIncheiere, int anIncheiere)
        : Angajat(nume, prenume, tip, zi, luna, an, activitate), zi_incheiere(ziIncheiere),
          luna_incheiere(lunaIncheiere), an_incheiere(anIncheiere) {}


          //--------------------------------------------------------------MENIU--------------------------------
class Manager{
private:

    vector < Angajat* > angajati;
    double prima;

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
        for(int i = 0;i < angajati.size(); ++i)
            delete angajati[i];
        angajati.clear();
    }
    void seteazaPrima();
    void adaugaAngajat();
    void afisAngajati();
    void afisAngajatiCuCopii();
    void afisAngajatiWeekend2();
    void afisAngajatiPlataCuOra();


};

void Manager::seteazaPrima() {
    cout << "Introduceti prima:\n";
    cin >> prima;
    cin.get();
}
void Manager::adaugaAngajat() {
    while(true) {
        try {
            cout << "Introduceti tipul angajatului: perm sau zi\n";
            string tip;
            getline(cin, tip);
            if(tip == "perm"){
                AngajatPermanent *a = new AngajatPermanent;
                cin >> *a;
                angajati.push_back(a);
                break;;
            }
            else if(tip == "zi"){
                AngajatTemporar *a = new AngajatTemporar;
                cin >> *a;
                angajati.push_back(a);
                break;
            }
            else throw string("Tip invalid!");
        }
        catch (string s){
            cout << s << '\n';
        }

    }
}
void Manager::afisAngajati() {
    for(int i = 0; i < angajati.size(); ++i)
        cout << *angajati[i] << "\nPrima: " << angajati[i]->calculeazaPrima(prima)<< '\n';
    cout << '\n';
}
void Manager::afisAngajatiCuCopii() {
    bool ok = false;
    for(int i = 0;i < angajati.size(); ++i)
        if(AngajatPermanent *a = dynamic_cast<AngajatPermanent*>(angajati[i]))
            if(a->getNrCopii()) {
                cout << *a << "Prima: "<< a->calculeazaPrima(prima)<< '\n';
                ok = true;
            }
    if(ok == false)
        cout << "Nu exista\n";
}
void Manager::afisAngajatiWeekend2() {
    bool ok = false;
    for(int i = 0;i < angajati.size(); ++i)
        if(AngajatPermanent *a = dynamic_cast<AngajatPermanent*>(angajati[i]))
            if(a->getWeekend() == 2) {
                cout << *a << "Prima: "<< a->calculeazaPrima(prima)<< '\n';
                ok = true;
            }
    if(ok == false)
        cout << "Nu exista\n";
}
void Manager::afisAngajatiPlataCuOra() {
    bool ok = false;
    for(int i = 0;i < angajati.size(); ++i)
        if(AngajatTemporar *a = dynamic_cast<AngajatTemporar*>(angajati[i]))
            if(a->getAnIncheiere() > 2015 || (a->getAnIncheiere() == 2015 && a->getLunaIncheiere()>=3)) {
                cout << *a << "Prima: "<< a->calculeazaPrima(prima)<< '\n';
                ok = true;
            }
    if(ok == false)
        cout << "Nu exista\n";
}
Manager* Manager::instanta = nullptr;

int main() {
    int optiune;
    Manager* m = m->getInstanta();
    while(1){
        cout << "0.Demo\n";
        cout << "1.Seteaza Prima\n";
        cout << "2.Adauga Angajat\n";
        cout << "3.Afis Angajati\n";
        cout << "4.Afis Angajati Cu Copii\n";
        cout << "5.Afis Angajati Weekend2\n";
        cout << "6.Afis Angajati plata cu ora\n";
        cout << "7.inchide\n";
        try{
            cin >> optiune;
            cin.get();
            if(optiune < 0 || optiune > 11)
                throw string("Optiune gresita!");
            else{
                if (optiune == 1) m->seteazaPrima();
                else if (optiune == 2) m->adaugaAngajat();
                else if (optiune == 3) m->afisAngajati();
                else if (optiune == 4) m->afisAngajatiCuCopii();
                else if (optiune == 5) m->afisAngajatiWeekend2();
                else if(optiune == 6) m->afisAngajatiPlataCuOra();
                else if (optiune == 7)  break;

            }
        }
        catch (string s){
            cout << s << '\n';
        }


    }
    m->deleteInstanta();

    return 0;
}
