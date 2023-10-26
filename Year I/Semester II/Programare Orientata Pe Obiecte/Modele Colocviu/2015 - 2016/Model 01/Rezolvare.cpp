#include <iostream>
#include <vector>
#include <string>

using namespace std;



//-------------------------------------------------------PRODUS-----------------------------------------------------------
class Produs{
private:
    string denumire;
    double pret;
public:
    const string &getDenumire() const;
    void setDenumire(const string &denumire);

    double getPret() const;
    void setPret(double pret);

    Produs();
    Produs(const Produs& produs);
    Produs(const string &denumire, double pret);
    Produs& operator=(const Produs& produs);
    ~Produs();

    friend istream& operator>>(istream& is, Produs& produs);
    friend ostream& operator<<(ostream& os, Produs& produs);
};
istream& operator>>(istream& is, Produs& produs){
    cout << "Introduceti denumire produs:\n";
    getline(is, produs.denumire);
    cout << "Introduceti pret produs:\n";
    is >> produs.pret;
    is.get();
    return is;
}
ostream& operator<<(ostream& os, Produs& produs){
    os << "Denumire produs: " << produs.denumire << '\n';
    os << "Pret produs: " << produs.pret << '\n';
    return os;
}
Produs::Produs() {
    denumire = "";
    pret = 0;
}
Produs::Produs(const Produs &produs) {
    denumire = produs.denumire;
    pret = produs.pret;
}
Produs & Produs::operator=(const Produs &produs) {
    denumire = produs.denumire;
    pret = produs.pret;
    return *this;
}
Produs::~Produs() {
    denumire.clear();
    pret = 0;
}
Produs::Produs(const string &denumire, double pret) : denumire(denumire), pret(pret) {}

const string &Produs::getDenumire() const {
    return denumire;
}

void Produs::setDenumire(const string &denumire) {
    Produs::denumire = denumire;
}

double Produs::getPret() const {
    return pret;
}

void Produs::setPret(double pret) {
    Produs::pret = pret;
}


//-------------------------------------------------------COMANDA-------------------------------------------------

class Comanda{
protected:
    static int cod;
    Produs produs;
    int nrPortii;
    int zi, luna, an;

public:
    static int getCod();
    static void setCod(int cod);

    const Produs &getProdus() const;
    void setProdus(const Produs &produs);

    int getNrPortii() const;
    void setNrPortii(int nrPortii);

    int getZi() const;
    void setZi(int zi);

    int getLuna() const;
    void setLuna(int luna);

    int getAn() const;
    void setAn(int an);

    Comanda();
    Comanda(const Comanda& comanda);
    Comanda(const Produs &produs, int nrPortii, int zi, int luna, int an);
    Comanda& operator=(const Comanda& comanda);
    virtual ~Comanda();

    friend istream& operator>>(istream& is, Comanda& comanda);
    friend ostream& operator<<(ostream& os, Comanda& comanda);

    double calculeaza(){
        double val = nrPortii * produs.getPret();
        return val;
    }
};
istream& operator>>(istream& is, Comanda& comanda){
    cout << "Introduceti produs:\n";
    is >> comanda.produs;
    cout << "Introduceti nr de portii:\n";
    is >> comanda.nrPortii ;
    is.get();
    cout << "Introduceti data:\n";
    cout << "Introduceti an:\n";
    bool bisect = 0;
    int zile[]={0,31,28,31,30,31,30,31,31,30,31,30,31};
    int an;
    is >> an;
    is.get();
    if ((an % 4 == 0 && an % 100!=0) || an%400 == 0 )
        bisect = 1;
    comanda.an = an;
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
    comanda.luna = luna;
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
    comanda.zi = zi;
    return is;
}
ostream& operator<<(ostream& os, Comanda& comanda){
    os << "Cod comanda: " << comanda.cod << '\n';
    os << "Produs: " << comanda.produs << '\n';
    os << "Nr portii: " << comanda.nrPortii << '\n';
    os << "Data: " << comanda.zi << '/' << comanda.luna << '/' << comanda.an << '\n';
    os << '\n';
    return os;
}
Comanda::~Comanda() {
    zi = luna = an = 0;
    nrPortii = 0;
    --cod;
}
Comanda::Comanda(const Comanda &comanda) {
    cod = comanda.cod;
    produs = comanda.produs;
    nrPortii = comanda.nrPortii;
    zi = comanda.zi;
    luna = comanda.luna;
    an = comanda.an;
}
Comanda & Comanda::operator=(const Comanda &comanda) {
    cod = comanda.cod;
    produs = comanda.produs;
    nrPortii = comanda.nrPortii;
    zi = comanda.zi;
    luna = comanda.luna;
    an = comanda.an;
    return *this;
}
int Comanda::cod = 0;

int Comanda::getCod() {
    return cod;
}

void Comanda::setCod(int cod) {
    Comanda::cod = cod;
}

const Produs &Comanda::getProdus() const {
    return produs;
}

void Comanda::setProdus(const Produs &produs) {
    Comanda::produs = produs;
}

int Comanda::getNrPortii() const {
    return nrPortii;
}

void Comanda::setNrPortii(int nrPortii) {
    Comanda::nrPortii = nrPortii;
}

int Comanda::getZi() const {
    return zi;
}

void Comanda::setZi(int zi) {
    Comanda::zi = zi;
}

int Comanda::getLuna() const {
    return luna;
}

void Comanda::setLuna(int luna) {
    Comanda::luna = luna;
}

int Comanda::getAn() const {
    return an;
}

void Comanda::setAn(int an) {
    Comanda::an = an;
}

Comanda::Comanda() {
    ++cod;
    nrPortii = 0;
    zi = luna = an = 0;
}

Comanda::Comanda(const Produs &produs, int nrPortii, int zi, int luna, int an) : produs(produs), nrPortii(nrPortii),
                                                                                 zi(zi), luna(luna), an(an) {
    ++cod;
}

//-------------------------------------------------------------COMANDA SPECIALA-----------------------------------------------------

class ComandaSpeciala : virtual public Comanda{
protected:
    string observatii;
    double pretSuplimentar;
public:
    const string &getObservatii() const;
    void setObservatii(const string &observatii);

    double getPretSuplimentar() const;
    void setPretSuplimentar(double pretSuplimentar);

    ComandaSpeciala();
    ComandaSpeciala(const ComandaSpeciala& comanda);
    ComandaSpeciala(const Produs &produs, int nrPortii, int zi, int luna, int an, const string &observatii,
                    double pretSuplimentar);
    ComandaSpeciala& operator=(const ComandaSpeciala& comanda);
    virtual ~ComandaSpeciala();

    friend istream& operator>>(istream& is, ComandaSpeciala& comanda);
    friend ostream& operator<<(ostream& os, ComandaSpeciala& comanda);

    double calculeaza(){
        double val = nrPortii * produs.getPret() +pretSuplimentar;
        return val;
    }
};

istream& operator>>(istream& is, ComandaSpeciala& comanda){
    cout << "Introduceti produs:\n";
    is >> comanda.produs;
    cout << "Introduceti nr de portii:\n";
    is >> comanda.nrPortii ;
    is.get();
    cout << "Introduceti data:\n";
    cout << "Introduceti an:\n";
    bool bisect = 0;
    int zile[]={0,31,28,31,30,31,30,31,31,30,31,30,31};
    int an;
    is >> an;
    is.get();
    if ((an % 4 == 0 && an % 100!=0) || an%400 == 0 )
        bisect = 1;
    comanda.an = an;
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
    comanda.luna = luna;
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
    comanda.zi = zi;
    cout << "Introduceti observatii:\n";
    getline(is, comanda.observatii);
    cout << "Introduceti pretul suplimentar:\n";
    is >> comanda.pretSuplimentar;
    is.get();

    return is;
}
ostream& operator<<(ostream& os, ComandaSpeciala& comanda){
    os << "Cod comanda: " << comanda.cod << '\n';
    os << "Produs: " << comanda.produs << '\n';
    os << "Nr portii: " << comanda.nrPortii << '\n';
    os << "Data: " << comanda.zi << '/' << comanda.luna << '/' << comanda.an << '\n';
    os << "Observatii: " << comanda.observatii << '\n';
    os << "Pret suplimentar: " << comanda.pretSuplimentar << '\n';
    os << '\n';
    return os;
}

ComandaSpeciala::ComandaSpeciala():Comanda() {
    observatii = "";
    pretSuplimentar = 0;
}
ComandaSpeciala::ComandaSpeciala(const ComandaSpeciala &comanda){
    cod = comanda.cod;
    produs = comanda.produs;
    nrPortii = comanda.nrPortii;
    zi = comanda.zi;
    luna = comanda.luna;
    an = comanda.an;
    observatii = comanda.observatii;
    pretSuplimentar = comanda.pretSuplimentar;
}
ComandaSpeciala & ComandaSpeciala::operator=(const ComandaSpeciala &comanda) {
    cod = comanda.cod;
    produs = comanda.produs;
    nrPortii = comanda.nrPortii;
    zi = comanda.zi;
    luna = comanda.luna;
    an = comanda.an;
    observatii = comanda.observatii;
    pretSuplimentar = comanda.pretSuplimentar;
    return *this;
}
ComandaSpeciala::~ComandaSpeciala() {
    observatii.clear();
    pretSuplimentar = 0;
}
ComandaSpeciala::ComandaSpeciala(const Produs &produs, int nrPortii, int zi, int luna, int an, const string &observatii,
                                 double pretSuplimentar) : Comanda(produs, nrPortii, zi, luna, an),
                                                           observatii(observatii), pretSuplimentar(pretSuplimentar) {}

const string &ComandaSpeciala::getObservatii() const {
    return observatii;
}

void ComandaSpeciala::setObservatii(const string &observatii) {
    ComandaSpeciala::observatii = observatii;
}

double ComandaSpeciala::getPretSuplimentar() const {
    return pretSuplimentar;
}

void ComandaSpeciala::setPretSuplimentar(double pretSuplimentar) {
    ComandaSpeciala::pretSuplimentar = pretSuplimentar;
}


//---------------------------------------------------------------COMANDA ONLINE------------------------------------------------------

class ComandaOnline : virtual public  Comanda{
protected:
    string adresa;
    int comision;
public:
    const string &getAdresa() const;
    void setAdresa(const string &adresa);

    int getComision() const;
    void setComision(int comision);

    ComandaOnline();
    ComandaOnline(const ComandaOnline& comanda);
    ComandaOnline& operator=(const ComandaOnline& comanda);
    ComandaOnline(const Produs &produs, int nrPortii, int zi, int luna, int an, const string &adresa, int comision);
    virtual ~ComandaOnline();

    friend istream& operator>>(istream& is, ComandaOnline& comanda);
    friend ostream& operator<<(ostream& os, ComandaOnline& comanda);


    double calculeaza(){
        double val = nrPortii * produs.getPret();
        val = val + comision * val;
        return val;
    }
};
istream& operator>>(istream& is, ComandaOnline& comanda){
    cout << "Introduceti produs:\n";
    is >> comanda.produs;
    cout << "Introduceti nr de portii:\n";
    is >> comanda.nrPortii ;
    is.get();
    cout << "Introduceti data:\n";
    cout << "Introduceti an:\n";
    bool bisect = 0;
    int zile[]={0,31,28,31,30,31,30,31,31,30,31,30,31};
    int an;
    is >> an;
    is.get();
    if ((an % 4 == 0 && an % 100!=0) || an%400 == 0 )
        bisect = 1;
    comanda.an = an;
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
    comanda.luna = luna;
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
    comanda.zi = zi;
    cout << "Introduceti adreasa:\n";
    getline(is, comanda.adresa);
    cout << "Introduceti comision:\n";
    is >> comanda.comision;
    is.get();
    return is;
}
ostream& operator<<(ostream& os, ComandaOnline& comanda){
    os << "Cod comanda: " << comanda.cod << '\n';
    os << "Produs: " << comanda.produs << '\n';
    os << "Nr portii: " << comanda.nrPortii << '\n';
    os << "Data: " << comanda.zi << '/' << comanda.luna << '/' << comanda.an << '\n';
    os << "Adresa: " << comanda.adresa << '\n';
    os << "Comision: " << comanda.comision << '\n';
    os << '\n';
    return os;
}
ComandaOnline::ComandaOnline():Comanda() {
    adresa = "";
    comision = 0;
}
ComandaOnline::ComandaOnline(const ComandaOnline &comanda) {
    cod = comanda.cod;
    produs = comanda.produs;
    nrPortii = comanda.nrPortii;
    zi = comanda.zi;
    luna = comanda.luna;
    an = comanda.an;
    adresa = comanda.adresa;
    comision = comanda.comision;
}
ComandaOnline & ComandaOnline::operator=(const ComandaOnline &comanda) {
    cod = comanda.cod;
    produs = comanda.produs;
    nrPortii = comanda.nrPortii;
    zi = comanda.zi;
    luna = comanda.luna;
    an = comanda.an;
    adresa = comanda.adresa;
    comision = comanda.comision;
    return *this;
}
ComandaOnline::~ComandaOnline() {
    adresa.clear();
    comision = 0;
}
const string &ComandaOnline::getAdresa() const {
    return adresa;
}

void ComandaOnline::setAdresa(const string &adresa) {
    ComandaOnline::adresa = adresa;
}

int ComandaOnline::getComision() const {
    return comision;
}

void ComandaOnline::setComision(int comision) {
    ComandaOnline::comision = comision;
}

ComandaOnline::ComandaOnline(const Produs &produs, int nrPortii, int zi, int luna, int an, const string &adresa,
                             int comision) : Comanda(produs, nrPortii, zi, luna, an), adresa(adresa),
                                             comision(comision) {}

//---------------------------------------------------------------------COMANDA DIAMANT---------------------------------------------
class ComandaDiamant: public ComandaOnline, public ComandaSpeciala{
public:
    ComandaDiamant();
    ComandaDiamant(const ComandaDiamant& comanda);
    ComandaDiamant(const Produs &produs, int nrPortii, int zi, int luna, int an, const string &adresa, int comision,const string &observatii,
                   double pretSuplimentar) : Comanda(produs, nrPortii, zi, luna, an) {
        this->adresa = adresa;
        this->comision = comision;
        this->observatii = observatii;
        this->pretSuplimentar = pretSuplimentar;
    }
    ComandaDiamant& operator=(const ComandaDiamant& comanda);
    ~ComandaDiamant();

    friend istream& operator>>(istream& is, ComandaDiamant& comanda);
    friend ostream& operator<<(ostream& os, ComandaDiamant& comanda);

    double calculeaza(){
        double val = nrPortii * produs.getPret() + pretSuplimentar;
        val = val + comision * val;
        return val;
    }
};
istream& operator>>(istream& is, ComandaDiamant& comanda){
    cout << "Introduceti produs:\n";
    is >> comanda.produs;
    cout << "Introduceti nr de portii:\n";
    is >> comanda.nrPortii ;
    is.get();
    cout << "Introduceti data:\n";
    cout << "Introduceti an:\n";
    bool bisect = 0;
    int zile[]={0,31,28,31,30,31,30,31,31,30,31,30,31};
    int an;
    is >> an;
    is.get();
    if ((an % 4 == 0 && an % 100!=0) || an%400 == 0 )
        bisect = 1;
    comanda.an = an;
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
    comanda.luna = luna;
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
    comanda.zi = zi;
    cout << "Introduceti observatii:\n";
    getline(is, comanda.observatii);
    cout << "Introduceti pretul suplimentar:\n";
    is >> comanda.pretSuplimentar;
    is.get();
    cout << "Introduceti adreasa:\n";
    getline(is, comanda.adresa);
    cout << "Introduceti comision:\n";
    is >> comanda.comision;
    is.get();
    return is;
}
ostream& operator<<(ostream& os, ComandaDiamant& comanda){
    os << "Cod comanda: " << comanda.cod << '\n';
    os << "Produs: " << comanda.produs << '\n';
    os << "Nr portii: " << comanda.nrPortii << '\n';
    os << "Data: " << comanda.zi << '/' << comanda.luna << '/' << comanda.an << '\n';
    os << "Adresa: " << comanda.adresa << '\n';
    os << "Comision: " << comanda.comision << '\n';
    os << "Observatii: " << comanda.observatii << '\n';
    os << "Pret suplimentar: " << comanda.pretSuplimentar << '\n';
    os << '\n';
    return os;
}

ComandaDiamant::ComandaDiamant():Comanda() {
    this->adresa = "";
    this->comision = 0;
    this->observatii = "";
    this->pretSuplimentar = 0;
}
ComandaDiamant::ComandaDiamant(const ComandaDiamant &comanda) {
    cod = comanda.cod;
    produs = comanda.produs;
    nrPortii = comanda.nrPortii;
    zi = comanda.zi;
    luna = comanda.luna;
    an = comanda.an;
    adresa = comanda.adresa;
    comision = comanda.comision;
    observatii = comanda.observatii;
    pretSuplimentar = comanda.pretSuplimentar;
}
ComandaDiamant & ComandaDiamant::operator=(const ComandaDiamant &comanda) {
    cod = comanda.cod;
    produs = comanda.produs;
    nrPortii = comanda.nrPortii;
    zi = comanda.zi;
    luna = comanda.luna;
    an = comanda.an;
    adresa = comanda.adresa;
    comision = comanda.comision;
    observatii = comanda.observatii;
    pretSuplimentar = comanda.pretSuplimentar;
    return *this;
}
ComandaDiamant::~ComandaDiamant(){
}
//---------------------------------------------------------------------------OSPATAR--------------------------------------------------------------

class Ospatar{
private:
    string nume;
    vector <Comanda*> comenzi;
    int nrComenzi;
    string gen;
    int varsta;
public:
    const string &getNume() const;
    void setNume(const string &nume);

    const vector<Comanda *> &getComenzi() const;
    void setComenzi(const vector<Comanda *> &comenzi);

    int getNrComenzi() const;
    void setNrComenzi(int nrComenzi);

    const string &getGen() const;
    void setGen(const string &gen);

    int getVarsta() const;
    void setVarsta(int varsta);

    Ospatar();
    Ospatar(const Ospatar& ospatar);
    Ospatar(const string &nume, const vector<Comanda *> &comenzi, int nrComenzi, const string &gen, int varsta);
    Ospatar& operator=(const Ospatar& ospatar);
    ~Ospatar();
    void adaugaComanda(Comanda *c){
        if (ComandaSpeciala* ob = dynamic_cast<ComandaSpeciala*>(c))
            comenzi.push_back(new ComandaSpeciala(*ob));
        else if (ComandaOnline* ob = dynamic_cast<ComandaOnline*>(c))
            comenzi.push_back(new ComandaOnline(*ob));
        else if(ComandaDiamant *ob = dynamic_cast<ComandaDiamant*>(c))
            comenzi.push_back(new ComandaDiamant(*ob));
        else
            comenzi.push_back((new Comanda(*c)));
    }

    friend istream& operator>>(istream& is, Ospatar& ospatar);
    friend ostream& operator<<(ostream& os, Ospatar& ospatar);

    double calculeazaProfit(){
        double val = 0;
        for(int i = 0;i < nrComenzi; ++i)
            if(comenzi[i]->getAn() == 2016 || comenzi[i]->getAn() == 2017 || comenzi[i]->getAn() == 2018 || comenzi[i]->getAn() == 2019 || comenzi[i]->getAn() == 2020 || (comenzi[i]->getAn() == 2021 && comenzi[i]->getLuna()<=4) || (comenzi[i]->getAn() == 2021 && comenzi[i]->getLuna()==5 && comenzi[i]->getZi()<=25))
            val = val + comenzi[i]->calculeaza();
        return val;
    }
};
istream& operator>>(istream& is, Ospatar& ospatar){
    cout << "Introduceti nume:\n";
    getline(is, ospatar.nume);
    cout << "Introduceti gen:\n";
    getline(is, ospatar.gen);
    cout << "Introduceti varsta:\n";
    is >> ospatar.varsta;
    is.get();
    cout << "Introduceti nr de Comenzi:\n";
    is >> ospatar.nrComenzi;
    is.get();
    for(int i = 0;i < ospatar.nrComenzi; ++i){
        while(true){
            try {
                cout << "Introduceti tipul comenzii\n";
                cout << "clasic - spec - online - diamant";
                string tip;
                getline(cin, tip);
                if (tip == "clasic") {
                    Comanda *c = new Comanda;
                    cin >> *c;
                    ospatar.comenzi.push_back(c);
                    break;
                } else if (tip == "spec") {
                    ComandaSpeciala *c = new ComandaSpeciala;
                    cin >> *c;
                    ospatar.comenzi.push_back(c);
                    break;
                } else if (tip == "online") {
                    ComandaOnline *c = new ComandaOnline;
                    cin >> *c;
                    ospatar.comenzi.push_back(c);
                    break;
                } else if (tip == "diamant") {
                    ComandaDiamant *c = new ComandaDiamant;
                    cin >> *c;
                    ospatar.comenzi.push_back(c);
                    break;
                } else throw string("Tip invalid!");
            }
            catch (string s){
                cout << s << '\n';
            }
        }
    }
    return is;
}
ostream& operator<<(ostream& os, Ospatar& ospatar){
    os << "Nume: " << ospatar.nume << '\n';
    os << "Gen: " << ospatar.gen << '\n';
    os << "Varsta: " << ospatar.varsta << '\n';
    os << "Nr comenzi: " << ospatar.nrComenzi << '\n';
    os << "Comenzi:\n";
    for(int i = 0;i < ospatar.comenzi.size(); ++i)
        os << ospatar.comenzi[i] << '\n';
    return os;
}
Ospatar::Ospatar() :comenzi(){
    nume = "";
    nrComenzi = 0;
    gen = "";
    varsta = 0;
}
Ospatar & Ospatar::operator=(const Ospatar &ospatar) {
    nume = ospatar.nume;
    nrComenzi = ospatar.nrComenzi;
    gen = ospatar.gen;
    varsta = ospatar.varsta;
    for(int i = 0;i < this->nrComenzi; ++i)
        delete this->comenzi[i];
    this->comenzi.clear();
    for(int i = 0;i < ospatar.comenzi.size(); ++i)
        adaugaComanda(ospatar.comenzi[i]);
    return *this;
}
Ospatar::~Ospatar() {
    nume.clear();
    nrComenzi = 0;
    gen.clear();
    varsta = 0;
    for(int i = 0;i < this->nrComenzi; ++i)
        delete this->comenzi[i];
    this->comenzi.clear();
}
const string &Ospatar::getNume() const {
    return nume;
}

void Ospatar::setNume(const string &nume) {
    Ospatar::nume = nume;
}

const vector<Comanda *> &Ospatar::getComenzi() const {
    return comenzi;
}

void Ospatar::setComenzi(const vector<Comanda *> &comenzi) {
    Ospatar::comenzi = comenzi;
}

int Ospatar::getNrComenzi() const {
    return nrComenzi;
}

void Ospatar::setNrComenzi(int nrComenzi) {
    Ospatar::nrComenzi = nrComenzi;
}

const string &Ospatar::getGen() const {
    return gen;
}

void Ospatar::setGen(const string &gen) {
    Ospatar::gen = gen;
}

int Ospatar::getVarsta() const {
    return varsta;
}

void Ospatar::setVarsta(int varsta) {
    Ospatar::varsta = varsta;
}

Ospatar::Ospatar(const string &nume, const vector<Comanda *> &comenzi, int nrComenzi, const string &gen, int varsta)
        : nume(nume),  nrComenzi(nrComenzi), gen(gen), varsta(varsta) {
    for(int i = 0;i < this->nrComenzi; ++i)
        delete this->comenzi[i];
    this->comenzi.clear();
    for(int i = 0;i < comenzi.size(); ++i)
        adaugaComanda(comenzi[i]);
}
Ospatar::Ospatar(const Ospatar &ospatar) {
    nume = ospatar.nume;
    nrComenzi = ospatar.nrComenzi;
    gen = ospatar.gen;
    varsta = ospatar.varsta;
    for(int i = 0;i < this->nrComenzi; ++i)
        delete this->comenzi[i];
    this->comenzi.clear();
    for(int i = 0;i < ospatar.comenzi.size(); ++i)
        adaugaComanda(ospatar.comenzi[i]);
}
//------------------------------------------------------Meniu interactiv --------------------------------------
class Manager{
private:
    vector <Produs*> produse;
    vector <Comanda*> comenzi;
    vector <Ospatar*> ospatari;


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
        for(int i = 0;i < produse.size(); ++i)
            delete produse[i];
        produse.clear();
        for(int i = 0;i < comenzi.size(); ++i)
            delete comenzi[i];
        comenzi.clear();
        for(int i = 0;i < ospatari.size(); ++i)
            delete ospatari[i];
        ospatari.clear();
    }

    void demo();
    void adaugaProdus();
    void adaugaOspatar();
    void adaugaComanda();
    void afisComenziData();
    void afisPapanasi();
    void procent();
    void afisOspatar();

};

void Manager::demo() {

}
void Manager::adaugaProdus() {
    Produs *p = new Produs;
    cin >> *p;
    produse.push_back(p);
}
void Manager::adaugaComanda() {
    while(true){
        try {
            cout << "Introduceti tipul comenzii\n";
            cout << "clasic - spec - online - diamant";
            string tip;
            getline(cin, tip);
            if (tip == "clasic") {
                Comanda *c = new Comanda;
                cin >> *c;
                comenzi.push_back(c);
                break;
            } else if (tip == "spec") {
                ComandaSpeciala *c = new ComandaSpeciala;
                cin >> *c;
                comenzi.push_back(c);
                break;
            } else if (tip == "online") {
                ComandaOnline *c = new ComandaOnline;
                cin >> *c;
                comenzi.push_back(c);
                break;
            } else if (tip == "diamant") {
                ComandaDiamant *c = new ComandaDiamant;
                cin >> *c;
                comenzi.push_back(c);
                break;
            } else throw string("Tip invalid!");
        }
        catch (string s){
            cout << s << '\n';
        }
    }
}
void Manager::adaugaOspatar() {
    Ospatar *o = new Ospatar;
    cin >> *o;
    ospatari.push_back(o);
}
void Manager::afisComenziData() {
    bool ok = false;
    for (int i = 0; i < comenzi.size(); ++i) {
        Comanda *c = comenzi[i];
        if (c->getAn() == 2016 && c->getLuna() == 5 && c->getZi() == 31) {
            cout << *c << '\n';
            ok = true;
        }
    }
    for (int i = 0; i < ospatari.size(); ++i) {
        for (int j = 0; j < ospatari[i]->getNrComenzi(); ++i) {
            Comanda *c = ospatari[i]->getComenzi()[j];
            if (c->getAn() == 2016 && c->getLuna() == 5 && c->getZi() == 31){
                cout << *c << '\n';
                ok = true;
            }

        }

    }
    if(ok == false)
        cout << "Nu exista!\n";
}
void Manager::afisPapanasi() {
    int nrPapanasi = 0, nrPapanasiSpeciali = 0;
    for (int i = 0; i < comenzi.size(); ++i) {
        Comanda *c = comenzi[i];
        if (c->getAn() == 2016 && c->getLuna() == 5) {
            if (c->getProdus().getDenumire() == "papanasi")
                ++nrPapanasi;
            else if (c->getProdus().getDenumire() == "papanasi cu nuca de cocos")
                ++nrPapanasiSpeciali;
        }
    }
    for (int i = 0; i < ospatari.size(); ++i) {
        for (int j = 0; j < ospatari[i]->getNrComenzi(); ++i) {
            Comanda *c = ospatari[i]->getComenzi()[j];
            if (c->getAn() == 2016 && c->getLuna() == 5) {
                if (c->getProdus().getDenumire() == "papanasi")
                    ++nrPapanasi;
                else if (c->getProdus().getDenumire() == "papanasi cu nuca de cocos")
                    ++nrPapanasiSpeciali;
            }

        }

    }
    cout << "Papanasi standard: " << nrPapanasi << '\n';
    cout << "Papanasi cu nuca de cocos: " << nrPapanasiSpeciali << '\n';

}
void Manager::procent() {
    double procent = 0;
    double valTotala = 0;
    double valMai = 0;
    for (int i = 0; i < comenzi.size(); ++i) {
        valMai = valMai + comenzi[i]->calculeaza();
        if(ComandaOnline *c = dynamic_cast<ComandaOnline*>(comenzi[i])){
            if (c->getAn() == 2016 && c->getLuna() == 5)
                valTotala += c->calculeaza();
        }
        else if(ComandaDiamant *c = dynamic_cast<ComandaDiamant*> (comenzi[i])){
            if (c->getAn() == 2016 && c->getLuna() == 5)
                valTotala += c->calculeaza();
        }

    }
    for (int i = 0; i < ospatari.size(); ++i) {
        for (int j = 0; j < ospatari[i]->getNrComenzi(); ++i) {
            valMai = valMai + ospatari[i]->getComenzi()[j]->calculeaza();
            if(ComandaOnline *c = dynamic_cast<ComandaOnline*>(ospatari[i]->getComenzi()[j])){
                if (c->getAn() == 2016 && c->getLuna() == 5)
                    valTotala += c->calculeaza();
            }
            else if(ComandaDiamant *c = dynamic_cast<ComandaDiamant*> (ospatari[i]->getComenzi()[j])){
                if (c->getAn() == 2016 && c->getLuna() == 5)
                    valTotala += c->calculeaza();
            }

        }
    }
    if(valTotala!=0)
    procent = 100.0 * valMai / valTotala;
    cout << "Procent: " << procent << '\n';

}
void Manager::afisOspatar() {
    Ospatar *o = new Ospatar;
    double maxim = 0;
    for(int i = 0;i < ospatari.size(); ++i){
        double  val = ospatari[i]->calculeazaProfit();
        if(val > maxim){
            maxim = val;
            o = ospatari[i];
        }
    }
    if(maxim != 0) {
        cout << "Ospatar:\n";
        cout << *o << '\n';
    }
    else cout << "Nu exista!\n";

}
Manager* Manager::instanta = nullptr;

int main() {
    int optiune;
    Manager* m = m->getInstanta();
    while(1){
        cout << "0.Demo\n";
        cout << "1.Adauga Produs\n";
        cout << "2.Adauga Ospatar\n";
        cout << "3.Adauga Comanda\n";
        cout << "4.Afis Comenzi din 31.05.2016\n";
        cout << "5.Afis Papanasi\n";
        cout << "6.Procent\n";
        cout << "7.Afis Ospatar\n";
        cout << "8.inchide\n";
        try{
            cin >> optiune;
            cin.get();
            if(optiune < 0 || optiune > 11)
                throw string("Optiune gresita!");
            else{ if(optiune == 0) m->demo();
                if (optiune == 1) m->adaugaProdus();
                else if (optiune == 2) m->adaugaOspatar();
                else if (optiune == 3) m->adaugaComanda();
                else if (optiune == 4) m->afisComenziData();
                else if (optiune == 5) m->afisPapanasi();
                else if(optiune == 6) m->procent();
                else if (optiune == 7) m->afisOspatar();
                else if(optiune == 8) break;

            }
        }
        catch (string s){
            cout << s << '\n';
        }


    }
    m->deleteInstanta();

    return 0;
}
