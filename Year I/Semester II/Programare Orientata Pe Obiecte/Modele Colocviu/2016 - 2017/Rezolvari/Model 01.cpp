#include <iostream>
#include <string>
#include <vector>

using namespace std;
//----------------------------------------------------------------PROPRIETATE------------------------------------------------

class Proprietate{
protected:
    string adresa;
    double suprafata;
    double pret_pe_mp;

public:
    const string &getAdresa() const;
    void setAdresa(const string &adresa);

    double getSuprafata() const;
    void setSuprafata(double suprafata);

    double getPretPeMp() const;
    void setPretPeMp(double pretPeMp);

    Proprietate();
    Proprietate(const Proprietate& proprietate);
    Proprietate& operator=(const Proprietate& proprietate);
    Proprietate(const string &adresa, double suprafata, double pretPeMp);\
    virtual ~Proprietate();

    friend istream& operator>>(istream& is, Proprietate& proprietate){
        return proprietate.readProprietate(is);
    }
    friend ostream& operator<<(ostream& os, Proprietate& proprietate){
        return proprietate.printProprietate(os);
    }

    bool operator==(const Proprietate &rhs) const;

    bool operator!=(const Proprietate &rhs) const;

    virtual istream& readProprietate(istream& is) = 0;
    virtual ostream& printProprietate(ostream& os) = 0;
};
Proprietate::Proprietate() {
    adresa = "";
    suprafata = pret_pe_mp = 0;

}
Proprietate::Proprietate(const Proprietate &proprietate) {
    adresa = proprietate.adresa;
    suprafata = proprietate.suprafata;
    pret_pe_mp = proprietate.pret_pe_mp;
}
Proprietate & Proprietate::operator=(const Proprietate &proprietate) {
    adresa = proprietate.adresa;
    suprafata = proprietate.suprafata;
    pret_pe_mp = proprietate.pret_pe_mp;
    return *this;
}
Proprietate::Proprietate(const string &adresa, double suprafata, double pretPeMp) : adresa(adresa),
                                                                                    suprafata(suprafata),
                                                                                    pret_pe_mp(pretPeMp) {}

Proprietate::~Proprietate() {
    adresa.clear();
    suprafata = pret_pe_mp = 0;
}

const string &Proprietate::getAdresa() const {
    return adresa;
}

void Proprietate::setAdresa(const string &adresa) {
    Proprietate::adresa = adresa;
}

double Proprietate::getSuprafata() const {
    return suprafata;
}

void Proprietate::setSuprafata(double suprafata) {
    Proprietate::suprafata = suprafata;
}

double Proprietate::getPretPeMp() const {
    return pret_pe_mp;
}

void Proprietate::setPretPeMp(double pretPeMp) {
    pret_pe_mp = pretPeMp;
}

bool Proprietate::operator==(const Proprietate &rhs) const {
    return adresa == rhs.adresa &&
           suprafata == rhs.suprafata &&
           pret_pe_mp == rhs.pret_pe_mp;
}

bool Proprietate::operator!=(const Proprietate &rhs) const {
    return !(rhs == *this);
}


//------------------------------------------------------------------------CASA------------------------------------------------------
class Casa: public Proprietate{
private:
    int nr_niveluri;
    double suprafata_curte;

public:
    int getNrNiveluri() const;
    void setNrNiveluri(int nrNiveluri);

    double getSuprafataCurte() const;
    void setSuprafataCurte(double suprafataCurte);

    Casa();
    Casa(const Casa& casa);
    Casa& operator=(const Casa& casa);
    Casa(const string &adresa, double suprafata, double pretPeMp, int nrNiveluri, double suprafataCurte);
    ~Casa();

    bool operator==(const Casa &rhs) const;

    bool operator!=(const Casa &rhs) const;

    istream& readProprietate(istream& is);
    ostream& printProprietate(ostream& os);
};
istream & Casa::readProprietate(istream &is) {
    cout << "Adresa:\n";
    getline(is, adresa);
    cout << "Suprafata:\n";
    is >> suprafata;
    is.get();
    cout << "Pret pe mp:\n";
    is >> pret_pe_mp;
    is.get();
    cout << "Nr niveluri:\n";
    is >> nr_niveluri;
    is.get();
    cout << "Suprafata curtii:\n";
    is >> suprafata_curte;
    is.get();

    return is;
}
ostream & Casa::printProprietate(ostream &os) {
    os << "Adresa: " << adresa << '\n';
    os << "Suprafata: " << suprafata << '\n';
    os << "Pret pe mp: " << pret_pe_mp << '\n';
    os << "Nr niveluri: " << nr_niveluri << '\n';
    os << "Suprafata curtii: " << suprafata_curte << '\n';
    os << '\n';
    return os;

}
Casa::Casa(const Casa &casa):Proprietate(casa) {
    nr_niveluri = casa.nr_niveluri;
    suprafata_curte = casa. suprafata_curte;
}
Casa & Casa::operator=(const Casa &casa) {
    adresa = casa.adresa;
    suprafata = casa.suprafata;
    pret_pe_mp = casa.pret_pe_mp;
    nr_niveluri = casa.nr_niveluri;
    suprafata_curte = casa. suprafata_curte;
    return *this;
}
Casa::~Casa(){
    nr_niveluri = 0;
    suprafata_curte = 0;
}
Casa::Casa(const string &adresa, double suprafata, double pretPeMp, int nrNiveluri, double suprafataCurte)
        : Proprietate(adresa, suprafata, pretPeMp), nr_niveluri(nrNiveluri), suprafata_curte(suprafataCurte) {}

Casa::Casa():Proprietate() {
    nr_niveluri = 0;
    suprafata_curte = 0;
}

int Casa::getNrNiveluri() const {
    return nr_niveluri;
}

void Casa::setNrNiveluri(int nrNiveluri) {
    nr_niveluri = nrNiveluri;
}

double Casa::getSuprafataCurte() const {
    return suprafata_curte;
}

void Casa::setSuprafataCurte(double suprafataCurte) {
    suprafata_curte = suprafataCurte;
}

bool Casa::operator==(const Casa &rhs) const {
    return static_cast<const Proprietate &>(*this) == static_cast<const Proprietate &>(rhs) &&
           nr_niveluri == rhs.nr_niveluri &&
           suprafata_curte == rhs.suprafata_curte;
}

bool Casa::operator!=(const Casa &rhs) const {
    return !(rhs == *this);
}


//-----------------------------------------------------------------------APARTAMENT------------------------------------------------

class Apartament: public Proprietate{
private:
    int etaj;
    int nr_camere;

public:
    int getEtaj() const;
    void setEtaj(int etaj);

    int getNrCamere() const;
    void setNrCamere(int nrCamere);

    Apartament();
    Apartament(const Apartament& apartament);
    Apartament& operator=(const Apartament& apartament);
    Apartament(const string &adresa, double suprafata, double pretPeMp, int etaj, int nrCamere);
    ~Apartament();

    bool operator==(const Apartament &rhs) const;

    bool operator!=(const Apartament &rhs) const;

    istream& readProprietate(istream& is);
    ostream& printProprietate(ostream& os);
};
Apartament::Apartament():Proprietate() {
    etaj = nr_camere = 0;
}
Apartament::Apartament(const Apartament &apartament) : Proprietate(apartament){
    etaj = apartament.etaj;
    nr_camere = apartament.nr_camere;
}
Apartament & Apartament::operator=(const Apartament &apartament) {
    adresa = apartament.adresa;
    suprafata = apartament.suprafata;
    pret_pe_mp = apartament.pret_pe_mp;
    nr_camere = apartament.nr_camere;
    etaj = apartament.etaj;
    return *this;
}
Apartament::~Apartament() {
    nr_camere = 0;
    etaj = 0;
}

istream & Apartament::readProprietate(istream &is) {
    cout << "Adresa:\n";
    getline(is, adresa);
    cout << "Suprafata:\n";
    is >> suprafata;
    is.get();
    cout << "Pret pe mp:\n";
    is >> pret_pe_mp;
    is.get();
    cout << "Etaj:\n";
    is >> etaj;
    is.get();
    cout << "Nr camere:\n";
    is >> nr_camere;
    is.get();
    return is;
}
ostream & Apartament::printProprietate(ostream &os) {
    os << "Adresa: " << adresa << '\n';
    os << "Suprafata: " << suprafata << '\n';
    os << "Pret pe mp: " << pret_pe_mp << '\n';
    os << "Etaj: " << etaj << '\n';
    os << "Nr camere: " << nr_camere << '\n';
    os << '\n';
    return os;
}
Apartament::Apartament(const string &adresa, double suprafata, double pretPeMp, int etaj, int nrCamere) : Proprietate(
        adresa, suprafata, pretPeMp), etaj(etaj), nr_camere(nrCamere) {}

int Apartament::getEtaj() const {
    return etaj;
}

void Apartament::setEtaj(int etaj) {
    Apartament::etaj = etaj;
}

int Apartament::getNrCamere() const {
    return nr_camere;
}

void Apartament::setNrCamere(int nrCamere) {
    nr_camere = nrCamere;
}

bool Apartament::operator==(const Apartament &rhs) const {
    return static_cast<const Proprietate &>(*this) == static_cast<const Proprietate &>(rhs) &&
           etaj == rhs.etaj &&
           nr_camere == rhs.nr_camere;
}

bool Apartament::operator!=(const Apartament &rhs) const {
    return !(rhs == *this);
}


//---------------------------------------------------------------CONTRACT------------------------------------------------------------

class Contract{
protected:
    string nume_client;
    Proprietate *proprietate;
public:
    const string &getNumeClient() const;
    void setNumeClient(const string &numeClient);

    Proprietate *getProprietate() const;
    void setProprietate(Proprietate *proprietate);

    Contract();
    Contract(const Contract& contract);
    Contract(const string &numeClient, Proprietate *proprietate);
    Contract& operator=(const Contract& contract);
    virtual ~Contract();

    friend istream& operator>>(istream& is, Contract& contract){
        return contract.readContract(is);
    }
    friend ostream& operator<<(ostream& os, Contract& contract){
        return contract.printContract(os);
    }

    virtual istream& readContract(istream &is) = 0;
    virtual ostream& printContract(ostream& os) = 0;
    virtual double calculeazaCost() = 0;
};
Contract & Contract::operator=(const Contract &contract) {
    nume_client = contract.nume_client;
    if(this->proprietate != nullptr) {
        delete this->proprietate;
        this->proprietate = nullptr;
    }
    if(Casa *c = dynamic_cast<Casa*>(contract.proprietate)){
        this->proprietate = new Casa(*c);
    }
    else if(Apartament *c = dynamic_cast<Apartament*>(contract.proprietate)){
        this->proprietate = new Apartament(*c);
    }
    return *this;
}
Contract::~Contract() {
    nume_client.clear();
    if(this->proprietate != nullptr) {
        delete this->proprietate;
        this->proprietate = nullptr;
    }
}
Contract::Contract() {
    nume_client = "";
    proprietate = nullptr;
}
Contract::Contract(const Contract &contract){
    nume_client = contract.nume_client;
    if(this->proprietate != nullptr) {
        delete this->proprietate;
        this->proprietate = nullptr;
    }
    if(Casa *c = dynamic_cast<Casa*>(contract.proprietate)){
        this->proprietate = new Casa(*c);
    }
    else if(Apartament *c = dynamic_cast<Apartament*>(contract.proprietate)){
        this->proprietate = new Apartament(*c);
    }
}

const string &Contract::getNumeClient() const {
    return nume_client;
}

void Contract::setNumeClient(const string &numeClient) {
    nume_client = numeClient;
}

Proprietate *Contract::getProprietate() const {
    return proprietate;
}

void Contract::setProprietate(Proprietate *proprietate) {
    Contract::proprietate = proprietate;
}

Contract::Contract(const string &numeClient, Proprietate *proprietate) : nume_client(numeClient){
    if(this->proprietate != nullptr) {
        delete this->proprietate;
        this->proprietate = nullptr;
    }
    if(Casa *c = dynamic_cast<Casa*>(proprietate)){
        this->proprietate = new Casa(*c);
    }
    else if(Apartament *c = dynamic_cast<Apartament*>(proprietate)){
        this->proprietate = new Apartament(*c);
    }
}


//----------------------------------------------------------------------CONTRACT INCHIRIERE---------------------------------------------------

class ContractInchiriere: public Contract{
private:
    int an_inceput, luna_inceput;
    int an_sfarsit, luna_sfarsit;

public:
    int getAnInceput() const;
    void setAnInceput(int anInceput);

    int getLunaInceput() const;
    void setLunaInceput(int lunaInceput);

    int getAnSfarsit() const;
    void setAnSfarsit(int anSfarsit);

    int getLunaSfarsit() const;
    void setLunaSfarsit(int lunaSfarsit);

    ContractInchiriere();
    ContractInchiriere(const ContractInchiriere& contract);
    ContractInchiriere& operator=(const ContractInchiriere& contract);
    ContractInchiriere(const string &numeClient, Proprietate *proprietate, int anInceput, int lunaInceput, int anSfarsit, int lunaSfarsit);
    ~ContractInchiriere();

    istream& readContract(istream &is);
    ostream& printContract(ostream& os);
    double calculeazaCost();

    int nrAni() {
        int luni = 12 - luna_inceput;
        if (an_sfarsit - an_inceput == 1)
            luni = luni + luna_sfarsit;
        else
            luni = luni + luna_sfarsit + (an_sfarsit - an_inceput - 1) * 12;

        return luni/12;
    }
    int nrluni() {
        int luni = 12 - luna_inceput;
        if (an_sfarsit - an_inceput == 1)
            luni = luni + luna_sfarsit;
        else
            luni = luni + luna_sfarsit + (an_sfarsit - an_inceput - 1) * 12;

        return luni;
    }
    double discount(){
        if(nrAni()>=2)
            return 0.1;
        else
            return 0.05;
    }


};
istream & ContractInchiriere::readContract(istream &is) {
    cout << "Nume client:\n";
    getline(is, nume_client);
    cout << "Proprietate:\n";
    while(true){
        try {
            string tip;
            cout << "Tip proprietate - casa sau ap\n";
            getline(is, tip);
            if (tip == "casa") {
                proprietate = new Casa;
                is >> *proprietate;
                break;
            } else if(tip == "ap"){
                proprietate = new Apartament;
                is >> *proprietate;
                break;
            }
            else throw string("Tip gresit!");

        }
        catch (string s){
            cout << s << '\n';
        }
    }
    cout << "Data inceput:\n";
    cout << "An inceput:\n";
    bool bisect = 0;
    int zile[]={0,31,28,31,30,31,30,31,31,30,31,30,31};
    int an;
    is >> an;
    is.get();
    if ((an % 4 == 0 && an % 100!=0) || an%400 == 0 )
        bisect = 1;
    an_inceput = an;
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
    luna_inceput = luna;
    cout << "Data sfarsit:\n";
    cout << "An sfarsit:\n";
    bisect = 0;
    is >> an;
    is.get();
    if ((an % 4 == 0 && an % 100!=0) || an%400 == 0 )
        bisect = 1;
    an_sfarsit = an;
    cout << "Luna sfarsit:\n";
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
    luna_sfarsit = luna;
    return is;

}
ostream & ContractInchiriere::printContract(ostream &os) {
    os << "Nume client: " << nume_client << '\n';
    os << "Proprietate: " << *proprietate << '\n';
    os << "Data inceput: " << luna_inceput << '/' << an_inceput << '\n';
    os << "Data sfarsit: " << luna_sfarsit << '/' << an_sfarsit << '\n';
    return os;
}
double ContractInchiriere::calculeazaCost() {
    double chirie = 0;
    if(Casa *c = dynamic_cast<Casa*>(proprietate)){
        chirie = c->getPretPeMp() * (c->getSuprafata() + 0.2 * c->getSuprafataCurte()) * (1 - discount());
    }
    else if(Apartament *c = dynamic_cast<Apartament*>(proprietate)){
        chirie = c->getPretPeMp() * c->getSuprafata()  * (1 - discount());
    }
    return chirie;

}
ContractInchiriere::ContractInchiriere() {
    an_inceput = an_sfarsit = luna_inceput = luna_sfarsit = 0;
}
ContractInchiriere::ContractInchiriere(const ContractInchiriere &contract) {
    nume_client = contract.nume_client;
    if(this->proprietate != nullptr) {
        delete this->proprietate;
        this->proprietate = nullptr;
    }
    if(Casa *c = dynamic_cast<Casa*>(contract.proprietate)){
        this->proprietate = new Casa(*c);
    }
    else if(Apartament *c = dynamic_cast<Apartament*>(contract.proprietate)){
        this->proprietate = new Apartament(*c);
    }
    an_sfarsit = contract.an_sfarsit;
    an_inceput = contract.an_inceput;
    luna_inceput = contract.luna_inceput;
    luna_sfarsit = contract.luna_sfarsit;

}
ContractInchiriere & ContractInchiriere::operator=(const ContractInchiriere &contract) {
    nume_client = contract.nume_client;
    if(this->proprietate != nullptr) {
        delete this->proprietate;
        this->proprietate = nullptr;
    }
    if(Casa *c = dynamic_cast<Casa*>(contract.proprietate)){
        this->proprietate = new Casa(*c);
    }
    else if(Apartament *c = dynamic_cast<Apartament*>(contract.proprietate)){
        this->proprietate = new Apartament(*c);
    }
    an_sfarsit = contract.an_sfarsit;
    an_inceput = contract.an_inceput;
    luna_inceput = contract.luna_inceput;
    luna_sfarsit = contract.luna_sfarsit;
    return *this;
}
ContractInchiriere::~ContractInchiriere(){
    an_inceput = an_sfarsit = luna_inceput = luna_sfarsit = 0;
}
int ContractInchiriere::getAnInceput() const {
    return an_inceput;
}

void ContractInchiriere::setAnInceput(int anInceput) {
    an_inceput = anInceput;
}

int ContractInchiriere::getLunaInceput() const {
    return luna_inceput;
}

void ContractInchiriere::setLunaInceput(int lunaInceput) {
    luna_inceput = lunaInceput;
}

int ContractInchiriere::getAnSfarsit() const {
    return an_sfarsit;
}

void ContractInchiriere::setAnSfarsit(int anSfarsit) {
    an_sfarsit = anSfarsit;
}

int ContractInchiriere::getLunaSfarsit() const {
    return luna_sfarsit;
}

void ContractInchiriere::setLunaSfarsit(int lunaSfarsit) {
    luna_sfarsit = lunaSfarsit;
}

ContractInchiriere::ContractInchiriere(const string &numeClient, Proprietate *proprietate, int anInceput,
                                       int lunaInceput, int anSfarsit, int lunaSfarsit) : Contract(numeClient,
                                                                                                   proprietate),
                                                                                          an_inceput(anInceput),
                                                                                          luna_inceput(lunaInceput),
                                                                                          an_sfarsit(anSfarsit),
                                                                                          luna_sfarsit(lunaSfarsit) {}
//----------------------------------------------------CONTRACT VANZARE-----------------------------------------

class ContractVanzare: public Contract{
private:
    int an_inceput, luna_inceput;
    int an_sfarsit, luna_sfarsit;

public:
    int getAnInceput() const;

    void setAnInceput(int anInceput);

    int getLunaInceput() const;

    void setLunaInceput(int lunaInceput);

    int getAnSfarsit() const;

    void setAnSfarsit(int anSfarsit);

    int getLunaSfarsit() const;

    void setLunaSfarsit(int lunaSfarsit);

    ContractVanzare();
    ContractVanzare(const ContractVanzare& contract);
    ContractVanzare& operator=(const ContractVanzare& contract);
    ContractVanzare(const string &numeClient, Proprietate *proprietate, int anInceput, int lunaInceput, int anSfarsit, int lunaSfarsit);
    ~ContractVanzare();

    istream& readContract(istream &is);
    ostream& printContract(ostream& os);
    double calculeazaCost();

    int nrluni() {
        int luni = 12 - luna_inceput;
        if (an_sfarsit - an_inceput == 1)
            luni = luni + luna_sfarsit;
        else
            luni = luni + luna_sfarsit + (an_sfarsit - an_inceput - 1) * 12;

        return luni;
    }
    double discount(){
        if(luna_sfarsit == luna_inceput && an_inceput == an_sfarsit)
            return 0.1;
        else
            if(nrluni()<=60)
                return 0.07;
            else
                return 0.05;
    }



};
double ContractVanzare::calculeazaCost() {
    double chirie = 0;
    if(Casa *c = dynamic_cast<Casa*>(proprietate)){
        chirie = 240.0 * c->getPretPeMp() * (c->getSuprafata() + 0.2 * c->getSuprafataCurte()) *(1 - discount());
    }
    else if(Apartament *c = dynamic_cast<Apartament*>(proprietate)){
        chirie = 240.0 * c->getPretPeMp() * c->getSuprafata()  * (1 - discount());
    }
    return chirie;

}
ContractVanzare::ContractVanzare() {
    an_inceput = an_sfarsit = luna_inceput = luna_sfarsit = 0;
}
ContractVanzare::ContractVanzare(const ContractVanzare &contract) {
    nume_client = contract.nume_client;
    if(this->proprietate != nullptr) {
        delete this->proprietate;
        this->proprietate = nullptr;
    }
    if(Casa *c = dynamic_cast<Casa*>(contract.proprietate)){
        this->proprietate = new Casa(*c);
    }
    else if(Apartament *c = dynamic_cast<Apartament*>(contract.proprietate)){
        this->proprietate = new Apartament(*c);
    }
    an_sfarsit = contract.an_sfarsit;
    an_inceput = contract.an_inceput;
    luna_inceput = contract.luna_inceput;
    luna_sfarsit = contract.luna_sfarsit;

}
ContractVanzare & ContractVanzare::operator=(const ContractVanzare &contract) {
    nume_client = contract.nume_client;
    if(this->proprietate != nullptr) {
        delete this->proprietate;
        this->proprietate = nullptr;
    }
    if(Casa *c = dynamic_cast<Casa*>(contract.proprietate)){
        this->proprietate = new Casa(*c);
    }
    else if(Apartament *c = dynamic_cast<Apartament*>(contract.proprietate)){
        this->proprietate = new Apartament(*c);
    }
    an_sfarsit = contract.an_sfarsit;
    an_inceput = contract.an_inceput;
    luna_inceput = contract.luna_inceput;
    luna_sfarsit = contract.luna_sfarsit;
    return *this;
}
ContractVanzare::~ContractVanzare(){
    an_inceput = an_sfarsit = luna_inceput = luna_sfarsit = 0;
}
ContractVanzare::ContractVanzare(const string &numeClient, Proprietate *proprietate, int anInceput,
                                       int lunaInceput, int anSfarsit, int lunaSfarsit) : Contract(numeClient,
                                                                                                   proprietate),
                                                                                          an_inceput(anInceput),
                                                                                          luna_inceput(lunaInceput),
                                                                                          an_sfarsit(anSfarsit),
                                                                                          luna_sfarsit(lunaSfarsit) {}
istream & ContractVanzare::readContract(istream &is) {
    cout << "Nume client:\n";
    getline(is, nume_client);
    cout << "Proprietate:\n";
    while(true){
        try {
            string tip;
            cout << "Tip proprietate - casa sau ap\n";
            getline(is, tip);
            if (tip == "casa") {
                proprietate = new Casa;
                is >> *proprietate;
                break;
            } else if(tip == "ap"){
                proprietate = new Apartament;
                is >> *proprietate;
                break;
            }
            else throw string("Tip gresit!");

        }
        catch (string s){
            cout << s << '\n';
        }
    }
    cout << "Data inceput:\n";
    cout << "An inceput:\n";
    bool bisect = 0;
    int zile[]={0,31,28,31,30,31,30,31,31,30,31,30,31};
    int an;
    is >> an;
    is.get();
    if ((an % 4 == 0 && an % 100!=0) || an%400 == 0 )
        bisect = 1;
    an_inceput = an;
    cout << "Luna inceput:\n";
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
    luna_inceput = luna;
    cout << "Data sfarsit:\n";
    cout << "An sfarsit:\n";
    bisect = 0;
    is >> an;
    is.get();
    if ((an % 4 == 0 && an % 100!=0) || an%400 == 0 )
        bisect = 1;
    an_sfarsit = an;
    cout << "Luna sfarsit:\n";
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
    luna_sfarsit = luna;
    return is;

}
ostream & ContractVanzare::printContract(ostream &os) {
    os << "Nume client: " << nume_client << '\n';
    os << "Proprietate: " << *proprietate << '\n';
    os << "Data inceput: " << luna_inceput << '/' << an_inceput << '\n';
    os << "Data sfarsit: " << luna_sfarsit << '/' << an_sfarsit << '\n';
    return os;
}

int ContractVanzare::getAnInceput() const {
    return an_inceput;
}

void ContractVanzare::setAnInceput(int anInceput) {
    an_inceput = anInceput;
}

int ContractVanzare::getLunaInceput() const {
    return luna_inceput;
}

void ContractVanzare::setLunaInceput(int lunaInceput) {
    luna_inceput = lunaInceput;
}

int ContractVanzare::getAnSfarsit() const {
    return an_sfarsit;
}

void ContractVanzare::setAnSfarsit(int anSfarsit) {
    an_sfarsit = anSfarsit;
}

int ContractVanzare::getLunaSfarsit() const {
    return luna_sfarsit;
}

void ContractVanzare::setLunaSfarsit(int lunaSfarsit) {
    luna_sfarsit = lunaSfarsit;
}

class Manager{
private:
    vector <Proprietate*> proprietati;
    vector <Contract*> contracte;

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
        for(int i = 0;i < contracte.size(); ++i)
            delete contracte[i];
        contracte.clear();
        for(int i = 0;i< proprietati.size(); ++i)
            delete proprietati[i];
        proprietati.clear();
    }

    void adaugaProprietate();
    void adaugaContract();
    void adaugaProprietati();
    void adaugaContracte();
    void afisProprietati();
    void afisContracte();
    void afisProprieatiSituatie();
    void afisSuma();


};
void Manager::adaugaContract() {
    while(true){
        try {
            string tip;
            cout << "Introceti tip - inch sau vanz\n";
            getline(cin, tip);
            if(tip == "inch"){
                ContractInchiriere *c = new ContractInchiriere;
                cin >> *c;
                contracte.push_back(new ContractInchiriere(*c));
                break;
            }
            else if(tip == "vanz"){
                ContractVanzare *c = new ContractVanzare;
                cin >> *c;
                contracte.push_back(new ContractVanzare(*c));
                break;
            }
            else throw string("Tip invalid!");
        }
        catch (string s){
            cout << s << '\n';
        }
    }
}
void Manager::adaugaProprietate() {
    while(true){
        try {
            string tip;
            cout << "Introceti tip - casa sau ap\n";
            getline(cin, tip);
            if(tip == "casa"){
                Casa *c = new Casa;
                cin >> *c;
                proprietati.push_back(new Casa(*c));
                break;
            }
            else if(tip == "ap"){
                Apartament *c = new Apartament;
                cin >> *c;
                proprietati.push_back(new Apartament(*c));
                break;
            }
            else throw string("Tip invalid!");
        }
        catch (string s){
            cout << s << '\n';
        }
    }
}
void Manager::adaugaContracte() {
    cout << "Nr de contracte:\n";
    int nr;
    cin >> nr;
    cin.get();
    for(int i = 0;i < nr; ++i)
        adaugaContract();
}
void Manager::adaugaProprietati() {
    cout << "Nr de proprietati:\n";
    int nr;
    cin >> nr;
    cin.get();
    for(int i = 0;i < nr; ++i)
        adaugaProprietate();
}

void Manager::afisProprietati() {
    cout << "Case:\n";
    for(int i = 0;i < proprietati.size(); ++i)
        if(Casa *c = dynamic_cast<Casa*>(proprietati[i]))
            cout << *c << '\n';
    cout << '\n';
    cout << "Apartamente:\n";
    for(int i = 0;i < proprietati.size(); ++i)
        if(Apartament *c = dynamic_cast<Apartament*>(proprietati[i]))
            cout << *c << '\n';
}
void Manager::afisContracte() {
    cout << "Inchiriere:\n";
    for(int i = 0;i < proprietati.size(); ++i)
        if(ContractInchiriere *c = dynamic_cast<ContractInchiriere*>(contracte[i]))
            cout << *c << '\n';
    cout << '\n';
    cout << "Vanzare:\n";
    for(int i = 0;i < proprietati.size(); ++i)
        if(ContractVanzare *c = dynamic_cast<ContractVanzare*>(contracte[i]))
            cout << *c << '\n';
}
void Manager::afisProprieatiSituatie() {
    int an;
    cout << "An:\n";
    cin >> an;
    cin.get();
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
    cout << "Libere:\n";
    for(int i = 0;i < proprietati.size();++i) {
        bool ok = true;
        for (int j = 0; j < contracte.size() && ok; ++j)
            if (*proprietati[i] == *contracte[i]->getProprietate())
                ok = false;
        if(ok)
            cout << *proprietati[i] << '\n';
    }
    for(int i = 0; i < contracte.size(); ++i) {
        if (ContractInchiriere *c = dynamic_cast<ContractInchiriere *>(contracte[i]))
            if (c->getAnSfarsit() < an || (c->getAnSfarsit() == an && c->getLunaSfarsit() < luna))
                cout << *c->getProprietate() << '\n';
    }

    cout << "Inchiriate: \n";
    for(int i = 0; i < contracte.size(); ++i) {
        if (ContractInchiriere *c = dynamic_cast<ContractInchiriere *>(contracte[i]))
            if (c->getAnSfarsit() > an || (c->getAnSfarsit() == an && c->getLunaSfarsit() >= luna))
                cout << *c->getProprietate() << '\n';
    }
    cout << "Vandute:\n";
    for(int i = 0; i < contracte.size(); ++i) {
        if (ContractVanzare *c = dynamic_cast<ContractVanzare *>(contracte[i]))
            cout << *c->getProprietate() << '\n';
    }

}
void Manager::afisSuma() {
    int an;
    cout << "An:\n";
    cin >> an;
    cin.get();
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
    double suma = 0;
    for(int i = 0; i < contracte.size(); ++i) {
        if (ContractInchiriere *c = dynamic_cast<ContractInchiriere *>(contracte[i])) {
            if (c->getAnSfarsit() == an && c->getLunaSfarsit() == luna)
                suma += c->calculeazaCost();
        }
        else if (ContractVanzare *t = dynamic_cast<ContractVanzare *>(contracte[i]))
            if (t->getAnInceput() <= an || (t->getAnInceput() == an && t->getLunaSfarsit() <= luna))
                suma += t->calculeazaCost()/t->nrluni();
    }
    cout << "Suma: " << suma  << '\n';
}

Manager* Manager::instanta = nullptr;

int main() {

    int optiune;
    Manager* m = m->getInstanta();
    while(1){
        cout << "0.Demo\n";
        cout << "1.Adauga Proprietati\n";
        cout << "2.Adauga Contracte\n";
        cout << "3.Afis Proprietati\n";
        cout << "4.Afis Contracte\n";
        cout << "5.Afis Proprietati Situatie\n";
        cout << "6.Afis Suma\n";
        cout << "7.inchide\n";
        try{
            cin >> optiune;
            cin.get();
            if(optiune < 0 || optiune > 11)
                throw string("Optiune gresita!");
            else{
                if (optiune == 1) m->adaugaProprietati();
                else if (optiune == 2) m->adaugaContracte();
                else if (optiune == 3) m->afisProprietati();
                else if (optiune == 4) m->afisContracte();
                else if (optiune == 5) m->afisProprieatiSituatie();
                else if(optiune == 6) m->afisSuma();
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