#include <iostream>
#include <vector>
#include <string>
using namespace std;


//--------------------------------------------------------PRODUS---------------------------------------

class Produs{
protected:
    string denumire;
    string unitate;

public:
    const string &getDenumire() const;
    void setDenumire(const string &denumire);

    const string &getUnitate() const;
    void setUnitate(const string &unitate);

    Produs();
    Produs(const Produs& produs);
    Produs& operator= (const Produs& produs);
    Produs(const string &denumire, const string &unitate);
    virtual ~Produs();

    bool operator==(const Produs &rhs) const;
    bool operator!=(const Produs &rhs) const;

    friend istream& operator>>(istream& is, Produs& produs){
        return produs.readProdus(is);
    }
    friend ostream& operator<<(ostream& os, Produs& produs){
        return produs.printProdus(os);
    }

    virtual istream& readProdus(istream& is) = 0;
    virtual ostream& printProdus(ostream& os) = 0;


};
Produs::Produs() {
    denumire = unitate = "";

}
Produs::Produs(const Produs &produs) {
    denumire = produs.denumire;
    unitate = produs.unitate;
}
Produs & Produs::operator=(const Produs &produs) {
    denumire = produs.denumire;
    unitate = produs.unitate;
    return *this;
}
Produs::~Produs() {
    denumire.clear();
    unitate.clear();
}

Produs::Produs(const string &denumire, const string &unitate) : denumire(denumire), unitate(unitate) {}

const string &Produs::getDenumire() const {
    return denumire;
}

void Produs::setDenumire(const string &denumire) {
    Produs::denumire = denumire;
}

const string &Produs::getUnitate() const {
    return unitate;
}

void Produs::setUnitate(const string &unitate) {
    Produs::unitate = unitate;
}

bool Produs::operator==(const Produs &rhs) const {
    return denumire == rhs.denumire &&
           unitate == rhs.unitate;
}

bool Produs::operator!=(const Produs &rhs) const {
    return !(rhs == *this);
}

//--------------------------------------------------------PRODUS PERISABIL---------------------------------------

class ProdusPerisabil:virtual public Produs{
protected:
    int perioada;

public:
    int getPerioada() const;
    void setPerioada(int perioada);

    ProdusPerisabil();
    ProdusPerisabil(const ProdusPerisabil& produs);
    ProdusPerisabil& operator=(const ProdusPerisabil& produs);
    virtual ~ProdusPerisabil();
    ProdusPerisabil(const string &denumire, const string &unitate, int perioada);

    bool operator==(const ProdusPerisabil &rhs) const;
    bool operator!=(const ProdusPerisabil &rhs) const;

    virtual istream& readProdus(istream& is);
    virtual ostream& printProdus(ostream& os);


};
istream & ProdusPerisabil::readProdus(istream &is) {
    cout << "Denumire:\n";
    getline(is, denumire);
    cout << "Unitate:\n";
    getline(is, unitate);
    cout << "Perioada:\n";
    is >> perioada;
    is.get();
    return is;
}

ostream & ProdusPerisabil::printProdus(ostream &os) {
    os << "Denumire: " << denumire << '\n';
    os << "Unitate: " << unitate << '\n';
    os << "Perioada: " << perioada << '\n';
    return os;
}

ProdusPerisabil::ProdusPerisabil() {
    perioada = 0;
}
ProdusPerisabil::ProdusPerisabil(const ProdusPerisabil &produs) {
    denumire = produs.denumire;
    unitate = produs.unitate;
    perioada = produs.perioada;
}
ProdusPerisabil & ProdusPerisabil::operator=(const ProdusPerisabil &produs) {
    denumire = produs.denumire;
    unitate = produs.unitate;
    perioada = produs.perioada;
    return *this;
}
ProdusPerisabil::~ProdusPerisabil()  {
    perioada = 0;
}
ProdusPerisabil::ProdusPerisabil(const string &denumire, const string &unitate, int perioada) : Produs(denumire,
                                                                                                       unitate),
                                                                                                perioada(perioada) {}

int ProdusPerisabil::getPerioada() const {
    return perioada;
}

void ProdusPerisabil::setPerioada(int perioada) {
    ProdusPerisabil::perioada = perioada;
}

bool ProdusPerisabil::operator==(const ProdusPerisabil &rhs) const {
    return static_cast<const Produs &>(*this) == static_cast<const Produs &>(rhs) &&
           perioada == rhs.perioada;
}

bool ProdusPerisabil::operator!=(const ProdusPerisabil &rhs) const {
    return !(rhs == *this);
}


//--------------------------------------------------------PRODUS PROMOTIE---------------------------------------


class ProdusPromotie: virtual public Produs{
protected:
    double discount;

public:
    double getDiscount() const;
    void setDiscount(double discount);

    ProdusPromotie();
    ProdusPromotie(const ProdusPromotie& produs);
    ProdusPromotie& operator=(const ProdusPromotie& produs);
    virtual ~ProdusPromotie();
    ProdusPromotie(const string &denumire, const string &unitate, double discount);

    bool operator==(const ProdusPromotie &rhs) const;
    bool operator!=(const ProdusPromotie &rhs) const;

    virtual istream& readProdus(istream& is);
    virtual ostream& printProdus(ostream& os);


};
istream & ProdusPromotie::readProdus(istream &is) {
    cout << "Denumire:\n";
    getline(is, denumire);
    cout << "Unitate:\n";
    getline(is, unitate);
    cout << "Discount:\n";
    is >> discount;
    is.get();
    return is;
}

ostream & ProdusPromotie::printProdus(ostream &os) {
    os << "Denumire: " << denumire << '\n';
    os << "Unitate: " << unitate << '\n';
    os << "Discount: " << discount << '\n';
    return os;
}

ProdusPromotie::ProdusPromotie() {
    discount = 0;
}
ProdusPromotie::ProdusPromotie(const ProdusPromotie &produs) {
    denumire = produs.denumire;
    unitate = produs.unitate;
    discount = produs.discount;
}
ProdusPromotie & ProdusPromotie::operator=(const ProdusPromotie &produs) {
    denumire = produs.denumire;
    unitate = produs.unitate;
    discount = produs.discount;
    return *this;
}
ProdusPromotie::~ProdusPromotie()  {
    discount = 0;
}
double ProdusPromotie::getDiscount() const {
    return discount;
}

void ProdusPromotie::setDiscount(double discount) {
    ProdusPromotie::discount = discount;
}

ProdusPromotie::ProdusPromotie(const string &denumire, const string &unitate, double discount) : Produs(denumire,
                                                                                                        unitate),
                                                                                                 discount(discount) {}

bool ProdusPromotie::operator==(const ProdusPromotie &rhs) const {
    return static_cast<const Produs &>(*this) == static_cast<const Produs &>(rhs) &&
           discount == rhs.discount;
}

bool ProdusPromotie::operator!=(const ProdusPromotie &rhs) const {
    return !(rhs == *this);
}

//--------------------------------------------------------PRODUS DIAMANT---------------------------------------

class ProdusDiamant: public ProdusPromotie, public ProdusPerisabil{
public:
    ProdusDiamant();
    ProdusDiamant(const ProdusDiamant& produs);
    ProdusDiamant& operator=(const ProdusDiamant& produs);
    ~ProdusDiamant();
    ProdusDiamant(const string &denumire, const string &unitate, double discount, int perioada);

    istream& readProdus(istream& is);
    ostream& printProdus(ostream& os);
};
istream & ProdusDiamant::readProdus(istream &is) {
    cout << "Denumire:\n";
    getline(is, denumire);
    cout << "Unitate:\n";
    getline(is, unitate);
    cout << "Perioada:\n";
    is >> perioada;
    is.get();
    cout << "Discount:\n";
    is >> discount;
    is.get();
    return is;
}

ostream & ProdusDiamant::printProdus(ostream &os) {
    os << "Denumire: " << denumire << '\n';
    os << "Unitate: " << unitate << '\n';
    os << "Perioada: " << perioada << '\n';
    os << "Discount: " << discount << '\n';
    return os;
}
ProdusDiamant::ProdusDiamant() :Produs(){
    discount = 0;
    perioada = 0;
}
ProdusDiamant::ProdusDiamant(const ProdusDiamant &produs) {
    denumire = produs.denumire;
    unitate = produs.unitate;
    discount = produs.discount;
    perioada = produs.perioada;
}
ProdusDiamant & ProdusDiamant::operator=(const ProdusDiamant &produs) {
    denumire = produs.denumire;
    unitate = produs.unitate;
    discount = produs.discount;
    perioada = produs.perioada;
    return *this;
}
ProdusDiamant::~ProdusDiamant() {}

ProdusDiamant::ProdusDiamant(const string &denumire, const string &unitate, double discount, int perioada)  {
    this->denumire = denumire;
    this->unitate = unitate;
    this->discount = discount;
    this->perioada = perioada;
}


//-------------------------------------------------------------------LOT-------------------------------------------

class Lot{
private:
    Produs *produs;
    double pret_bucata;
    double cantitate;
    int zi_intrare,luna_intrare, an_intrare;

public:
    Produs *getProdus() const;
    void setProdus(Produs *produs);

    double getPretBucata() const;
    void setPretBucata(double pretBucata);

    double getCantitate() const;
    void setCantitate(double cantitate);

    int getZiIntrare() const;
    void setZiIntrare(int ziIntrare);

    int getLunaIntrare() const;
    void setLunaIntrare(int lunaIntrare);

    int getAnIntrare() const;
    void setAnIntrare(int anIntrare);

    Lot();
    Lot(const Lot& lot);
    Lot& operator=(const Lot& lot);
    Lot(Produs *produs, double pretBucata, double cantitate, int ziIntrare, int lunaIntrare, int anIntrare);
    ~Lot();

    friend istream& operator>>(istream& is, Lot& lot);
    friend ostream& operator<<(ostream& os, Lot& lot);
};
istream& operator>>(istream& is, Lot& lot){
    while(true) {
        try {
            string tip;
            cout << "Tip produs: per - prom - diam\n";
            getline(is, tip);
            if(tip == "per"){
                cout << "Produs:\n";
                lot.produs = new ProdusPerisabil;
                is >> *lot.produs;
                break;
            } else if(tip == "prom"){
                cout << "Produs:\n";
                lot.produs = new ProdusPromotie;
                is >> *lot.produs;
                break;
            }
            else if(tip == "diam"){
                cout << "Produs:\n";
                lot.produs = new ProdusDiamant;
                is >> *lot.produs;
                break;
            }
            else throw string("Tip invalid!");

        }
        catch (string s){
            cout << s << '\n';
        }
    }
    cout << "Pret:\n";
    is >> lot.pret_bucata;
    is.get();
    cout << "Cantitate:\n";
    is >> lot.cantitate;
    is.get();
    cout << "Data:\n";
    cout << "An:\n";
    bool bisect = 0;
    int zile[]={0,31,28,31,30,31,30,31,31,30,31,30,31};
    int an;
    is >> an;
    is.get();
    if ((an % 4 == 0 && an % 100!=0) || an%400 == 0 )
        bisect = 1;
    lot.an_intrare = an;
    cout << "Luna:\n";
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
    lot.luna_intrare = luna;
    cout << "Ziua\n";
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
    lot.zi_intrare = zi;

    return is;

}

ostream& operator<<(ostream& os, Lot& lot){
    os << "Produs:\n";
    os << *lot.produs << '\n';
    os << "Pret: " << lot.pret_bucata << '\n';
    os << "Cantitate: " << lot.cantitate << '\n';
    os << "Data: " << lot.zi_intrare << '/' << lot.luna_intrare << '/' << lot.an_intrare << '\n';
    return os;
}

Lot::Lot() {
    produs = nullptr;
    pret_bucata = 0;
    cantitate = 0;
    zi_intrare = luna_intrare = an_intrare = 0;
}
Lot::Lot(const Lot &lot) {
    zi_intrare = lot.zi_intrare;
    luna_intrare = lot.luna_intrare;
    an_intrare = lot.an_intrare;
    cantitate = lot.cantitate;
    pret_bucata = lot.pret_bucata;
    if(Lot::produs!= nullptr)
        delete Lot::produs;
    if(ProdusDiamant *p = dynamic_cast<ProdusDiamant*> (lot.produs))
        Lot::produs = new ProdusDiamant;
    else if(ProdusPromotie *p = dynamic_cast<ProdusPromotie*> (lot.produs))
        Lot::produs = new ProdusPerisabil;
    else if(ProdusPerisabil *p = dynamic_cast<ProdusPerisabil*> (lot.produs))
        Lot::produs = new ProdusPerisabil;
    Lot::produs = lot.produs;
}
Lot & Lot::operator=(const Lot &lot) {
    zi_intrare = lot.zi_intrare;
    luna_intrare = lot.luna_intrare;
    an_intrare = lot.an_intrare;
    cantitate = lot.cantitate;
    pret_bucata = lot.pret_bucata;
    if(Lot::produs!= nullptr)
        delete Lot::produs;
    if(ProdusDiamant *p = dynamic_cast<ProdusDiamant*> (lot.produs))
        Lot::produs = new ProdusDiamant;
    else if(ProdusPromotie *p = dynamic_cast<ProdusPromotie*> (lot.produs))
        Lot::produs = new ProdusPerisabil;
    else if(ProdusPerisabil *p = dynamic_cast<ProdusPerisabil*> (lot.produs))
        Lot::produs = new ProdusPerisabil;
    Lot::produs = lot.produs;
    return *this;
}
Lot::~Lot() {
    if(produs!= nullptr)
        delete produs;
    produs = nullptr;
    pret_bucata = 0;
    cantitate = 0;
    zi_intrare = luna_intrare = an_intrare = 0;

}
Produs *Lot::getProdus() const {
    return produs;
}

void Lot::setProdus(Produs *produs) {
    if(Lot::produs!= nullptr)
        delete Lot::produs;
    if(ProdusDiamant *p = dynamic_cast<ProdusDiamant*> (produs))
        Lot::produs = new ProdusDiamant;
    else if(ProdusPromotie *p = dynamic_cast<ProdusPromotie*> (produs))
        Lot::produs = new ProdusPerisabil;
    else if(ProdusPerisabil *p = dynamic_cast<ProdusPerisabil*> (produs))
        Lot::produs = new ProdusPerisabil;
    Lot::produs = produs;
}

double Lot::getPretBucata() const {
    return pret_bucata;
}

void Lot::setPretBucata(double pretBucata) {
    pret_bucata = pretBucata;
}

double Lot::getCantitate() const {
    return cantitate;
}

void Lot::setCantitate(double cantitate) {
    Lot::cantitate = cantitate;
}

int Lot::getZiIntrare() const {
    return zi_intrare;
}

void Lot::setZiIntrare(int ziIntrare) {
    zi_intrare = ziIntrare;
}

int Lot::getLunaIntrare() const {
    return luna_intrare;
}

void Lot::setLunaIntrare(int lunaIntrare) {
    luna_intrare = lunaIntrare;
}

int Lot::getAnIntrare() const {
    return an_intrare;
}

void Lot::setAnIntrare(int anIntrare) {
    an_intrare = anIntrare;
}

Lot::Lot(Produs *produs, double pretBucata, double cantitate, int ziIntrare, int lunaIntrare, int anIntrare) :
pret_bucata(pretBucata), cantitate(cantitate), zi_intrare(ziIntrare), luna_intrare(lunaIntrare),
an_intrare(anIntrare) {
    if(Lot::produs!= nullptr)
        delete Lot::produs;
    if(ProdusDiamant *p = dynamic_cast<ProdusDiamant*> (produs))
        Lot::produs = new ProdusDiamant;
    else if(ProdusPromotie *p = dynamic_cast<ProdusPromotie*> (produs))
        Lot::produs = new ProdusPerisabil;
    else if(ProdusPerisabil *p = dynamic_cast<ProdusPerisabil*> (produs))
        Lot::produs = new ProdusPerisabil;
    Lot::produs = produs;
}


//------------------------------------------------------------MANAGER------------------------------------------------

class Manager{
private:
    vector <Produs*> produse;
    vector <Lot*> loturi;


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
        for(int i = 0;i < loturi.size(); ++i)
            delete loturi[i];
        loturi.clear();
    }

    void demo();
    void adaugaProdus();
    void afisProduse();
    void adaugaLot();
    void afisLoturiIntreDate();
    void afisLoturiDataCurenta();
    void vindeProdus();
};
void Manager::vindeProdus() {
    cout << "Denumire Produs:\n";
    string den;
    getline(cin, den);
    cout << "Cantitate:\n";
    double cant;
    cin >> cant;
    cin.get();
    bool ok;
    int zi, luna, an;
    bool bisect = 0;
    int zile[]={0,31,28,31,30,31,30,31,31,30,31,30,31};
    int zi_curenta = 27, luna_curenta = 5, an_curent = 2021;
    double minim = 999999999;
    int poz = 0;
    vector <int> pozitii;
    for(int i = 0;i < loturi.size(); ++i){
        Produs *p = loturi[i]->getProdus();
        zi = loturi[i]->getZiIntrare();
        luna = loturi[i]->getLunaIntrare();
        an = loturi[i]->getAnIntrare();
        if(p->getDenumire() == den){
                if(ProdusPerisabil *prod = dynamic_cast<ProdusPerisabil*> (p)){
                    int per = prod->getPerioada();
                    zi = zi + per;
                    if(zi > zile[luna]){
                        zi = zi % zile[luna];
                        ++luna;
                    }
                    if(luna > 12){
                        luna = luna % 12;
                        an ++;
                    }
                    if(an < an_curent || (an == an_curent && luna < luna_curenta) || (an == an_curent && luna == luna_curenta && zi <= zi_curenta)){
                        if(loturi[i]->getCantitate()>cant){
                            if(minim > loturi[i]->getPretBucata() * cant){
                                poz = i;
                                minim = loturi[i]->getPretBucata() * cant;
                            }
                        }
                        else{
                            pozitii.push_back(i);
                        }
                    }
                }
                else if(ProdusDiamant *prod = dynamic_cast<ProdusDiamant*> (p)){
                    int per = prod->getPerioada();
                    zi = zi + per;
                    if(zi > zile[luna]){
                        zi = zi % zile[luna];
                        ++luna;
                    }
                    if(luna > 12){
                        luna = luna % 12;
                        an ++;
                    }
                    if(an < an_curent || (an == an_curent && luna < luna_curenta) || (an == an_curent && luna == luna_curenta && zi <= zi_curenta)){
                        cout << *prod << '\n';
                        ok = true;
                    }
                }
                else if(ProdusPromotie *prod = dynamic_cast<ProdusPromotie*> (p)){
                    cout << *prod << '\n';
                    ok = true;
                }

        }
    }
    if(minim!=999999999){
        loturi[poz]->setCantitate(loturi[poz]->getCantitate()-cant);
        cout << "Pret: ";
        cout << minim << '\n';
    }
    else{
        for(int i = 0;i < pozitii.size(); ++i){
            cout << *loturi[i] << '\n';
            cout << "Pret: ";
            cout << loturi[i]->getPretBucata() * cant << '\n';
        }
    }
    pozitii.clear();
}
void Manager::afisLoturiIntreDate() {
    bool ok = false;
    cout << "Date:\n";
    cout << "Data inceput:\n";
    cout << "An:\n";
    bool bisect = 0;
    int zile[]={0,31,28,31,30,31,30,31,31,30,31,30,31};
    int an;
    cin >> an;
    cin.get();
    if ((an % 4 == 0 && an % 100!=0) || an%400 == 0 )
        bisect = 1;
    int an_data1 = an;
    cout << "Luna:\n";
    int luna;
    while(true){
        try{
            cin >> luna;
            cin.get();
            if(luna < 1 || luna > 12)
                throw string("Luna invalida!");
            else break;
        }
        catch (string s){
            cout << s << '\n';
        }
    }
    int luna_data1 = luna;
    cout << "Ziua\n";
    int zi;
    while(true){
        try{
            cin >> zi;
            cin.get();
            if(zi < 1 || (luna == 2 && bisect == 1 && zi > 29) || zi > zile[luna])
                throw string("Zi invalida!");
            else break;
        }
        catch (string s){
            cout << s << '\n';
        }
    }
    int zi_data1 = zi;
    cout << "Data final:\n";
    cin >> an;
    cin.get();
    if ((an % 4 == 0 && an % 100!=0) || an%400 == 0 )
        bisect = 1;
    int an_data2 = an;
    cout << "Luna:\n";
    while(true){
        try{
            cin >> luna;
            cin.get();
            if(luna < 1 || luna > 12)
                throw string("Luna invalida!");
            else break;
        }
        catch (string s){
            cout << s << '\n';
        }
    }
    int luna_data2 = luna;
    cout << "Ziua\n";
    while(true){
        try{
            cin >> zi;
            cin.get();
            if(zi < 1 || (luna == 2 && bisect == 1 && zi > 29) || zi > zile[luna])
                throw string("Zi invalida!");
            else break;
        }
        catch (string s){
            cout << s << '\n';
        }
    }
    int zi_data2 = zi;

    for(int i = 0;i < loturi.size(); ++i){
        zi = loturi[i]->getZiIntrare();
        luna = loturi[i]->getLunaIntrare();
        an = loturi[i]->getAnIntrare();
        if(an < an_data1 || (an == an_data1 && luna < luna_data1) || (an == an_data1 && luna == luna_data1 && zi < zi_data1) || an > an_data2
        || (an == an_data2 && luna > luna_data1)  || (an == an_data2 && luna == luna_data2 && zi > zi_data2))
            continue;
        else {
            cout << *loturi[i] << '\n';
            ok = true;
        }
    }
    if(ok == false)
        cout << "Nu exista\n";

}

void Manager::afisLoturiDataCurenta() {
    bool ok = false;
    int zi, luna, an;
    bool bisect = 0;
    int zile[]={0,31,28,31,30,31,30,31,31,30,31,30,31};
    int zi_curenta = 27, luna_curenta = 5, an_curent = 2021;
    for(int i = 0;i < loturi.size(); ++i){
        Produs *p = loturi[i]->getProdus();
        zi = loturi[i]->getZiIntrare();
        luna = loturi[i]->getLunaIntrare();
        an = loturi[i]->getAnIntrare();
        if(loturi[i]->getCantitate()>0)
            if(ProdusPerisabil *prod = dynamic_cast<ProdusPerisabil*> (p)){
                int per = prod->getPerioada();
                zi = zi + per;
                if(zi > zile[luna]){
                    zi = zi % zile[luna];
                    ++luna;
                }
                if(luna > 12){
                    luna = luna % 12;
                    an ++;
                }
                if(an < an_curent || (an == an_curent && luna < luna_curenta) || (an == an_curent && luna == luna_curenta && zi <= zi_curenta)){
                    cout << *prod << '\n';
                    ok = true;
                }
            }
            else if(ProdusDiamant *prod = dynamic_cast<ProdusDiamant*> (p)){
                int per = prod->getPerioada();
                zi = zi + per;
                if(zi > zile[luna]){
                    zi = zi % zile[luna];
                    ++luna;
                }
                if(luna > 12){
                    luna = luna % 12;
                    an ++;
                }
                if(an < an_curent || (an == an_curent && luna < luna_curenta) || (an == an_curent && luna == luna_curenta && zi <= zi_curenta)){
                    cout << *prod << '\n';
                    ok = true;
                }
            }
            else if(ProdusPromotie *prod = dynamic_cast<ProdusPromotie*> (p)){
                cout << *prod << '\n';
                ok = true;
            }

    }
    if(ok == false)
        cout << "Nu exista\n";

}
void Manager::adaugaLot() {
    Lot *l = new Lot;
    cin >> *l;
    loturi.push_back(l);
}
void Manager::afisProduse() {
    for(int i = 0;i < produse.size(); ++i)
        cout << *produse[i] << '\n';
    cout << '\n';
}
void Manager::adaugaProdus() {
    while(true) {
        try {
            string tip;
            cout << "Tip produs: per - prom - diam\n";
            getline(cin, tip);
            if(tip == "per"){
                cout << "Produs:\n";
                ProdusPerisabil *produs = new ProdusPerisabil;
                cin >> *produs;
                produse.push_back(produs);
                break;
            } else if(tip == "prom"){
                cout << "Produs:\n";
                ProdusPromotie *produs = new ProdusPromotie;
                cin >> *produs;
                produse.push_back(produs);
                break;
            }
            else if(tip == "diam"){
                cout << "Produs:\n";
                ProdusDiamant *produs = new ProdusDiamant;
                cin >> *produs;
                produse.push_back(produs);
                break;
            }
            else throw string("Tip invalid!");

        }
        catch (string s){
            cout << s << '\n';
        }
    }
}
void Manager::demo() {

}
Manager* Manager::instanta = nullptr;

int main() {
    int optiune;
    Manager* m = m->getInstanta();
    while(1){
        cout << "0.Demo\n";
        cout << "1.Adauga Produs\n";
        cout << "2.afisProdus\n";
        cout << "3.adaugaLot\n";
        cout << "4.afisLoturiIntreDate\n";
        cout << "5.afisLoturiDataCurenta\n";
        cout << "6.vindeProdus\n";
        cout << "7.inchide\n";

        try{
            cin >> optiune;
            cin.get();
            if(optiune < 0 || optiune > 11)
                throw string("Optiune gresita!");
            else{ if(optiune == 0) m->demo();
                if (optiune == 1) m->adaugaProdus();
                else if (optiune == 2) m->afisProduse();
                else if (optiune == 3) m->adaugaLot();
                else if (optiune == 4) m->afisLoturiIntreDate();
                else if (optiune == 5) m->afisLoturiDataCurenta();
                else if(optiune == 6) m->vindeProdus();
                else if (optiune == 7) break;

            }
        }
        catch (string s){
            cout << s << '\n';
        }


    }
    m->deleteInstanta();

    return 0;
}