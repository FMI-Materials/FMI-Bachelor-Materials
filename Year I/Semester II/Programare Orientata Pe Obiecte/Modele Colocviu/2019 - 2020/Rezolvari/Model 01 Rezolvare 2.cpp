#include <iostream>
#include <string>
#include <vector>
#include <exception>
using namespace std;
class Data{
private:
    int zi;
    int luna;
    int an;
    static int zile[13];
public:
    Data();
    Data(int zi, int luna, int an);
    Data(const Data &data);
    ~Data();
    Data(long zile);
    Data& operator=(const Data& data);

    int getZi() const;
    void setZi(int zi);

    int getLuna() const;
    void setLuna(int luna);

    int getAn() const;
    void setAn(int an);

    static int getZileLuna(int luna, int an);
    static int getZileAn(int an);

    friend istream& operator>>(istream& is,Data& data);
    friend ostream& operator<<(ostream& os, Data& data);
    friend bool operator>(const Data& data1, const Data& data2);

    int getZileInceput();
    int getZileSfarsit();

};
Data & Data::operator=(const Data &data) {
    zi = data.zi;
    luna = data.luna;
    an = data.an;
    return *this;
}
bool operator>(const Data& data1, const Data& data2){
    if( data1. an > data2.an)
        return 1;
    else if(data1.an == data2. an && data1.luna > data2.luna)
        return 1;
    else if(data1.an == data2. an && data1.luna == data2.luna && data1.zi > data2.zi)
        return 1;
    return 0;
}
istream& operator>>(istream& is,Data& data){
    cout << "Introduceti an - nr intreg:\n";
    while(true){
        try{
            is >> data.an;
            is.get();
            if (data.an < 1900)
                throw string("Introduceti un an mai mare de 1900!");
            else
                break;
        }
        catch ( string s){
            cout << s << '\n';
        }
    }
    cout << "Introduceti luna - nr intreg:\n";
    while(true){
        try{
            is >> data.luna;
            is.get();
            if (data.luna < 1 || data.luna > 12)
                throw string("Introduceti o luna intre 1 si 12!");
            else break;
        }
        catch (string s){
            cout << s << '\n';
        }
    }

    cout << "Introduceti ziua - nr intreg:\n";
    while(true){
        try{
            is >> data.zi;
            is.get();
            if (data.zi < 1 || data.zi > data.getZileLuna(data.luna,data.an))
                throw string("Introduceti un numar valid de zile!");
            else break;
        }
        catch (string s){
            cout << s << '\n';
        }
    }
    return is;
}
ostream& operator<<(ostream& os, Data& data){
    os << "Ziua: " << data.zi   << '\n';
    os << "Luna: " << data.luna << '\n';
    os << "An: "   << data.an   << '\n';
    return os;
}
Data::Data(long zile) {
    an = 1900;
    while( zile > getZileAn(an)){
        zile -= getZileAn(an);
        an ++;
    }
    luna = 1;
    while(zile > getZileLuna(luna,an)){
        zile -= getZileAn(an);
        luna ++;
    }
    zi = zile;
}
int Data::getZileInceput() {
    int nrZile = zi;
    for( int i = 1; i < luna; ++i)
        nrZile += getZileLuna(i,an);
    return nrZile;
}
int Data::getZileSfarsit() {
    int nrZile = zile[luna] - zi;
    for( int i = luna + 1; i <= 12; ++i )
        nrZile += getZileLuna(i,an);
    return nrZile;
}
int Data::zile[]={0,31,28,31,30,31,30,31,31,30,31,30,31};
int Data::getZileAn(int an) {
    if( (an % 4 == 0 && an % 100 != 0) || an % 400 == 0)
        return 366;
    return 365;
}
int Data::getZileLuna(int luna, int an) {
    if(getZileAn(an) == 366 &&  luna == 2)
        return zile[luna]+1;
    return zile[luna];
}

Data::Data() {
    zi = 1;
    luna = 1;
    an = 1900;
}

Data::Data(int zi, int luna, int an) : zi(zi), luna(luna), an(an) {}

Data::Data(const Data &data) : zi(data.zi), luna(data.luna), an(data.an) {}

Data::~Data() {
    zi = 1;
    luna = 1;
    an = 1900;
}

int Data::getZi() const {
    return zi;
}

void Data::setZi(int zi) {
    Data::zi = zi;
}

int Data::getLuna() const {
    return luna;
}

void Data::setLuna(int luna) {
    Data::luna = luna;
}

int Data::getAn() const {
    return an;
}

void Data::setAn(int an) {
    Data::an = an;
}


//-------------------------------------------------------------------------------------------------------

class Masca{
protected:
    string tipProtectie;
public:
    const string &getTipProtectie() const;
    void setTipProtectie(const string &tipProtectie);

    Masca();
    Masca(const Masca& masca);
    Masca(const string &tipProtectie);
    Masca& operator=(const Masca& masca);
    virtual ~Masca();

    friend istream& operator>> (istream&is, Masca& masca){return masca.readMasca(is);}
    friend ostream& operator<< (ostream&os, Masca& masca){return masca.printMasca(os);}

    virtual istream& readMasca(istream& is) = 0;
    virtual ostream& printMasca(ostream& os) = 0;
};


Masca::Masca() {tipProtectie = "";}
Masca::Masca(const Masca &masca) : tipProtectie(masca.tipProtectie) {}
Masca::Masca(const string &tipProtectie): tipProtectie(tipProtectie){}
Masca::~Masca() {tipProtectie = "";}
Masca & Masca::operator=(const Masca &masca) {
    tipProtectie = masca.tipProtectie;
    return *this;
}

const string &Masca::getTipProtectie() const {
    return tipProtectie;
}
void Masca::setTipProtectie(const string &tipProtectie) {
    Masca::tipProtectie = tipProtectie;
}

class MascaChirugicala: public Masca{
private:
    string culoare;
    int nrPliuri;
    bool modelSpecial;
public:
    const string &getCuloare() const;
    void setCuloare(const string &culoare);

    int getNrPliuri() const;
    void setNrPliuri(int nrPliuri);

    bool isModelSpecial() const;
    void setModelSpecial(bool modelSpecial);

    MascaChirugicala();
    MascaChirugicala(const MascaChirugicala& mascaChirugicala);
    MascaChirugicala(const string &tipProtectie, const string &culoare, int nrPliuri, bool modelSpecial);
    ~MascaChirugicala();
    MascaChirugicala& operator=(const MascaChirugicala& mascaChirugicala);

    istream& readMasca(istream& is);
    ostream& printMasca(ostream& os);

};
istream & MascaChirugicala::readMasca(istream &is) {
    cout << "Introduceti tipul de protectie:\n";
    getline(is, tipProtectie);
    cout << "Introduceti culoare:\n";
    getline(is, culoare);
    cout << "Introduceti nr pliuri:\n";
    is >> nrPliuri;
    is.get();
    cout << "Introduceti 1 daca masca are un model special, 0 altfel:\n";
    is >> modelSpecial;
    is.get();
    return is;
}
ostream & MascaChirugicala::printMasca(ostream &os) {
    os << "Tip protectie: " << tipProtectie << '\n';
    os << "Culoare: " << culoare << '\n';
    os << "Nr Pliuri: " << nrPliuri << '\n';
    os << "Model Special: " << modelSpecial << '\n';
    return os;
}
const string &MascaChirugicala::getCuloare() const {
    return culoare;
}
void MascaChirugicala::setCuloare(const string &culoare) {
    MascaChirugicala::culoare = culoare;
}

int MascaChirugicala::getNrPliuri() const {
    return nrPliuri;
}
void MascaChirugicala::setNrPliuri(int nrPliuri) {
    MascaChirugicala::nrPliuri = nrPliuri;
}

bool MascaChirugicala::isModelSpecial() const {
    return modelSpecial;
}
void MascaChirugicala::setModelSpecial(bool modelSpecial) {
    MascaChirugicala::modelSpecial = modelSpecial;
}
MascaChirugicala::MascaChirugicala() {
    culoare = "";
    nrPliuri = 0;
    modelSpecial = 0;
    tipProtectie = "";
}
MascaChirugicala & MascaChirugicala::operator=(const MascaChirugicala &mascaChirugicala) {
    culoare = mascaChirugicala.culoare;
    nrPliuri = mascaChirugicala.nrPliuri;
    modelSpecial = mascaChirugicala.modelSpecial;
    tipProtectie = mascaChirugicala.tipProtectie;
    return *this;
}
MascaChirugicala::MascaChirugicala(const MascaChirugicala &mascaChirugicala):Masca(mascaChirugicala) {
    culoare = mascaChirugicala.culoare;
    nrPliuri = mascaChirugicala.nrPliuri;
    modelSpecial = mascaChirugicala.modelSpecial;
}
MascaChirugicala::MascaChirugicala(const string &tipProtectie, const string &culoare, int nrPliuri, bool modelSpecial)
        : Masca(tipProtectie), culoare(culoare), nrPliuri(nrPliuri), modelSpecial(modelSpecial) {}

MascaChirugicala::~MascaChirugicala() {
    culoare = "";
    nrPliuri = 0;
    modelSpecial = 0;
}

//------------------------------------------------------------------------------------

class MascaPolicarbonat :  public Masca{
private:
    string tipPrindere;
public:
    const string &getTipPrindere() const;
    void setTipPrindere(const string &tipPrindere);

    MascaPolicarbonat();
    MascaPolicarbonat(const string &tipProtectie, const string &tipPrindere);
    MascaPolicarbonat(const MascaPolicarbonat& mascaPolicarbonat);
    MascaPolicarbonat& operator=(const MascaPolicarbonat& mascaPolicarbonat);
    ~MascaPolicarbonat();

    istream& readMasca(istream& is);
    ostream& printMasca(ostream& os);
};
istream & MascaPolicarbonat::readMasca(istream &is) {
    cout << "Introduceti tipul de protectie:\n";
    getline(is, tipProtectie);
    cout << "Introduceti tipul de prindere:\n";
    getline(is, tipPrindere);
    return is;
}
ostream & MascaPolicarbonat::printMasca(ostream &os) {
    os << "Tip protectie: " << tipProtectie << '\n';
    os << "Tip prindere: " << tipPrindere << '\n';
    return os;
}

MascaPolicarbonat::MascaPolicarbonat(const MascaPolicarbonat &mascaPolicarbonat) : Masca(mascaPolicarbonat){
    tipPrindere = mascaPolicarbonat.tipPrindere;
}
MascaPolicarbonat::MascaPolicarbonat() {
    tipPrindere = "";
}

MascaPolicarbonat::MascaPolicarbonat(const string &tipProtectie, const string &tipPrindere) : Masca(tipProtectie), tipPrindere(tipPrindere) {}

MascaPolicarbonat::~MascaPolicarbonat() {
    tipPrindere = "";
}
MascaPolicarbonat & MascaPolicarbonat::operator=(const MascaPolicarbonat &mascaPolicarbonat) {
    tipPrindere = mascaPolicarbonat.tipPrindere;
    tipProtectie = mascaPolicarbonat.tipProtectie;
    return *this;
}

const string &MascaPolicarbonat::getTipPrindere() const {
    return tipPrindere;
}

void MascaPolicarbonat::setTipPrindere(const string &tipPrindere) {
    MascaPolicarbonat::tipPrindere = tipPrindere;
}


//--------------------------------------------------------------------------------------------------
class Dezinfectant {
protected:
    int nrSpecii;
    vector <string> ingrediente;
    vector <string> suprafete;
    double eficienta;



public:
    Dezinfectant();
    Dezinfectant(const Dezinfectant& dezinfectant);
    Dezinfectant(int nrSpecii, const vector<string> &ingrediente, const vector<string> &suprafete);
    Dezinfectant& operator=(const Dezinfectant& dezinfectant);

    int getNrSpecii() const;
    void setNrSpecii(int nrSpecii);

    const vector<string> &getIngrediente() const;
    void setIngrediente(const vector<string> &ingrediente);

    const vector<string> &getSuprafete() const;
    void setSuprafete(const vector<string> &suprafete);

    double getEficienta() const;
    void setEficienta(double eficienta);

    friend istream& operator>>(istream& is,Dezinfectant& dezinfectantBacterii);
    friend ostream& operator<<(ostream& os,Dezinfectant& dezinfectantBacterii);


    virtual double calculeazaEficienta() = 0;

    virtual ~Dezinfectant() = 0;
};

istream& operator>>(istream& is,Dezinfectant& dezinfectantBacterii) {

    cout << "Introduceti nr specii:\n";
    is >> dezinfectantBacterii.nrSpecii;
    is.get();
    cout << "Introduceti nr de ingrediente:\n";
    int nr;
    is >> nr;
    is.get();
    for(int i = 0; i < nr; ++i){
        cout << "Introduceti ingredient:\n";
        string x;
        getline(is, x);
        dezinfectantBacterii.ingrediente.push_back(x);
    }
    cout << "Introduceti nr de suprafete:\n";
    is >> nr;
    is.get();
    for(int i = 0; i < nr; ++i){
        cout << "Introduceti suprafete:\n";
        string x;
        getline(is, x);
        dezinfectantBacterii.suprafete.push_back(x);
    }
    dezinfectantBacterii.calculeazaEficienta();
    return is;
}
ostream& operator<<(ostream& os,Dezinfectant& dezinfectantBacterii) {
    os << "Nr specii: " << dezinfectantBacterii.nrSpecii << '\n';
    os << "Ingrediente:\n";
    for(int i = 0; i < dezinfectantBacterii.ingrediente.size(); ++i){
        os <<" - " << dezinfectantBacterii.ingrediente[i] <<"\n";
    }
    os << "Suprafete:\n";
    for(int i = 0; i < dezinfectantBacterii.suprafete.size(); ++i){
        os <<" - " << dezinfectantBacterii.suprafete[i] <<"\n";
    }
    os << "Eficienta: " << dezinfectantBacterii.eficienta << '\n';
    return os;
}

int Dezinfectant::getNrSpecii() const {
    return nrSpecii;
}

void Dezinfectant::setNrSpecii(int nrSpecii) {
    Dezinfectant::nrSpecii = nrSpecii;
}

const vector<string> &Dezinfectant::getIngrediente() const {
    return ingrediente;
}

void Dezinfectant::setIngrediente(const vector<string> &ingrediente) {
    Dezinfectant::ingrediente = ingrediente;
}

const vector<string> &Dezinfectant::getSuprafete() const {
    return suprafete;
}

void Dezinfectant::setSuprafete(const vector<string> &suprafete) {
    Dezinfectant::suprafete = suprafete;
}

double Dezinfectant::getEficienta() const {
    return eficienta;
}

void Dezinfectant::setEficienta(double eficienta) {
    Dezinfectant::eficienta = eficienta;
}
Dezinfectant & Dezinfectant::operator=(const Dezinfectant &dezinfectant) {
    nrSpecii = dezinfectant.nrSpecii;
    ingrediente = dezinfectant.ingrediente;
    suprafete = dezinfectant.suprafete;
    eficienta = dezinfectant.eficienta;
    return *this;
}
Dezinfectant::Dezinfectant(const Dezinfectant &dezinfectant) {
    nrSpecii = dezinfectant.nrSpecii;
    ingrediente = dezinfectant.ingrediente;
    suprafete = dezinfectant.suprafete;
    eficienta = dezinfectant.eficienta;
}
Dezinfectant::Dezinfectant() {
    nrSpecii = 0;
    ingrediente = {};
    suprafete = {};
    eficienta = 0;
}

Dezinfectant::Dezinfectant(int nrSpecii, const vector<string> &ingrediente, const vector<string> &suprafete) : nrSpecii(nrSpecii), ingrediente(ingrediente), suprafete(suprafete){}

Dezinfectant::~Dezinfectant() {
    nrSpecii = 0;
    ingrediente.clear();
    suprafete.clear();
    eficienta = 0;
}


//--------------------------------------------------------------------------------------------------------------------------------
class DezinfectantBacterii: virtual public Dezinfectant{
protected:

public:
    DezinfectantBacterii();
    DezinfectantBacterii(const DezinfectantBacterii &dezinfectant);
    DezinfectantBacterii(int nrSpecii, const vector<string> &ingrediente, const vector<string> &suprafete);
    DezinfectantBacterii& operator=(const DezinfectantBacterii& dezinfectantBacterii);
    virtual ~DezinfectantBacterii();


    friend istream& operator>>(istream& is,DezinfectantBacterii& dezinfectantBacterii);
    friend ostream& operator<<(ostream& os,DezinfectantBacterii& dezinfectantBacterii);
    double calculeazaEficienta();

};
istream& operator>>(istream& is,DezinfectantBacterii& dezinfectantBacterii) {
    cout << "Dezinfectant Bacterii\n";
    cout << "Introduceti nr specii:\n";
    is >> dezinfectantBacterii.nrSpecii;
    is.get();
    cout << "Introduceti nr de ingrediente:\n";
    int nr;
    is >> nr;
    is.get();
    for(int i = 0; i < nr; ++i){
        cout << "Introduceti ingredient:\n";
        string x;
        getline(is, x);
        dezinfectantBacterii.ingrediente.push_back(x);
    }
    cout << "Introduceti nr de suprafete:\n";
    is >> nr;
    is.get();
    for(int i = 0; i < nr; ++i){
        cout << "Introduceti suprafete:\n";
        string x;
        getline(is, x);
        dezinfectantBacterii.suprafete.push_back(x);
    }
    dezinfectantBacterii.calculeazaEficienta();
    return is;
}
ostream& operator<<(ostream& os,DezinfectantBacterii& dezinfectantBacterii) {
    os << "Dezinfectant Bacterii\n";
    os << "Nr specii: " << dezinfectantBacterii.nrSpecii << '\n';
    os << "Ingrediente:\n";
    for(int i = 0; i < dezinfectantBacterii.ingrediente.size(); ++i){
        os <<" - " << dezinfectantBacterii.ingrediente[i] <<"\n";
    }
    os << "Suprafete:\n";
    for(int i = 0; i < dezinfectantBacterii.suprafete.size(); ++i){
        os <<" - " << dezinfectantBacterii.suprafete[i] <<"\n";
    }
    os << "Eficienta: " << dezinfectantBacterii.eficienta << '\n';
    return os;
}

double DezinfectantBacterii::calculeazaEficienta() {
    eficienta = (double)nrSpecii / ( 1000000000.0);
    return eficienta;
}
DezinfectantBacterii & DezinfectantBacterii::operator=(const DezinfectantBacterii &dezinfectantBacterii) {
    Dezinfectant::operator=(dezinfectantBacterii);
    return *this;
}
DezinfectantBacterii::DezinfectantBacterii():Dezinfectant() {}

DezinfectantBacterii::DezinfectantBacterii(const DezinfectantBacterii &dezinfectant) : Dezinfectant(dezinfectant) {}

DezinfectantBacterii::DezinfectantBacterii(int nrSpecii, const vector<string> &ingrediente,
                                           const vector<string> &suprafete) : Dezinfectant(nrSpecii,
                                                                                                             ingrediente,
                                                                                                             suprafete) {
    eficienta = calculeazaEficienta();
}

DezinfectantBacterii::~DezinfectantBacterii() {}

class DezinfectantFungi : virtual public Dezinfectant{
protected:

public:
    DezinfectantFungi();
    DezinfectantFungi(const DezinfectantFungi &dezinfectant);
    DezinfectantFungi(int nrSpecii, const vector<string> &ingrediente, const vector<string> &suprafete);
    DezinfectantFungi& operator=(const DezinfectantFungi& dezinfectantFungi);
    virtual ~DezinfectantFungi();


    friend istream& operator>>(istream& is,DezinfectantFungi& dezinfectantFungi);
    friend ostream& operator<<(ostream& os,DezinfectantFungi& dezinfectantFungi);
    double calculeazaEficienta();
};

istream& operator>>(istream& is,DezinfectantFungi& dezinfectantFungi) {
    cout << "Dezinfectant Fungi\n";
    cout << "Introduceti nr specii:\n";
    is >> dezinfectantFungi.nrSpecii;
    is.get();
    cout << "Introduceti nr de ingrediente:\n";
    int nr;
    is >> nr;
    is.get();
    for(int i = 0; i < nr; ++i){
        cout << "Introduceti ingredient:\n";
        string x;
        getline(is, x);
        dezinfectantFungi.ingrediente.push_back(x);
    }
    cout << "Introduceti nr de suprafete:\n";
    is >> nr;
    is.get();
    for(int i = 0; i < nr; ++i){
        cout << "Introduceti suprafete:\n";
        string x;
        getline(is, x);
        dezinfectantFungi.suprafete.push_back(x);
    }
    dezinfectantFungi.calculeazaEficienta();
    return is;
}
ostream& operator<<(ostream& os,DezinfectantFungi& dezinfectantFungi) {
    os << "Dezinfectant Fungi\n";
    os << "Nr specii: " << dezinfectantFungi.nrSpecii << '\n';
    os << "Ingrediente:\n";
    for(int i = 0; i < dezinfectantFungi.ingrediente.size(); ++i){
        os <<" - " << dezinfectantFungi.ingrediente[i] <<"\n";
    }
    os << "Suprafete:\n";
    for(int i = 0; i < dezinfectantFungi.suprafete.size(); ++i){
        os <<" - " << dezinfectantFungi.suprafete[i] <<"\n";
    }
    os << "Eficienta: " << dezinfectantFungi.eficienta << '\n';
    return os;
}
DezinfectantFungi & DezinfectantFungi::operator=(const DezinfectantFungi &dezinfectantFungi) {
    Dezinfectant::operator=(dezinfectantFungi);
    return *this;
}
DezinfectantFungi::DezinfectantFungi():Dezinfectant() {}

DezinfectantFungi::DezinfectantFungi(const DezinfectantFungi &dezinfectant) : Dezinfectant(dezinfectant) {}

DezinfectantFungi::DezinfectantFungi(int nrSpecii, const vector<string> &ingrediente,
                                           const vector<string> &suprafete) : Dezinfectant(nrSpecii,
                                                                                                             ingrediente,
                                                                                                             suprafete) {
    eficienta = calculeazaEficienta();
}

DezinfectantFungi::~DezinfectantFungi() {}

double DezinfectantFungi::calculeazaEficienta() {
    eficienta = (double)nrSpecii / (1.5 * 1000000.0);
    return  eficienta;
}
//------------------------------------------------------------------------------------------------------------------------------------------
class DezinfectantVirusuri : virtual public Dezinfectant{
protected:

public:
    DezinfectantVirusuri();
    DezinfectantVirusuri(const DezinfectantVirusuri &dezinfectant);
    DezinfectantVirusuri(int nrSpecii, const vector<string> &ingrediente, const vector<string> &suprafete);
    DezinfectantVirusuri& operator=(const DezinfectantVirusuri& dezinfectantFungi);
    virtual ~DezinfectantVirusuri();


    friend istream& operator>>(istream& is,DezinfectantVirusuri& dezinfectantVirusuri);
    friend ostream& operator<<(ostream& os,DezinfectantVirusuri& dezinfectantVirusuri);

    double calculeazaEficienta();
};
istream& operator>>(istream& is,DezinfectantVirusuri& dezinfectantVirusuri) {
    cout << "Dezinfectant Virusuri\n";
    cout << "Introduceti nr specii:\n";
    is >> dezinfectantVirusuri.nrSpecii;
    is.get();
    cout << "Introduceti nr de ingrediente:\n";
    int nr;
    is >> nr;
    is.get();
    for(int i = 0; i < nr; ++i){
        cout << "Introduceti ingredient:\n";
        string x;
        getline(is, x);
        dezinfectantVirusuri.ingrediente.push_back(x);
    }
    cout << "Introduceti nr de suprafete:\n";
    is >> nr;
    is.get();
    for(int i = 0; i < nr; ++i){
        cout << "Introduceti suprafete:\n";
        string x;
        getline(is, x);
        dezinfectantVirusuri.suprafete.push_back(x);
    }
    dezinfectantVirusuri.calculeazaEficienta();
    return is;
}
ostream& operator<<(ostream& os,DezinfectantVirusuri& dezinfectantVirusuri){
    os << "Dezinfectant Fungi\n";
    os << "Nr specii: " << dezinfectantVirusuri.nrSpecii << '\n';
    os << "Ingrediente:\n";
    for(int i = 0; i < dezinfectantVirusuri.ingrediente.size(); ++i){
        os <<" - " << dezinfectantVirusuri.ingrediente[i] <<"\n";
    }
    os << "Suprafete:\n";
    for(int i = 0; i < dezinfectantVirusuri.suprafete.size(); ++i){
        os <<" - " << dezinfectantVirusuri.suprafete[i] <<"\n";
    }
    os << "Eficienta: " << dezinfectantVirusuri.eficienta << '\n';
    return os;
}
DezinfectantVirusuri & DezinfectantVirusuri::operator=(const DezinfectantVirusuri &dezinfectantVirusuri) {
    Dezinfectant::operator=(dezinfectantVirusuri);
    return *this;
}
DezinfectantVirusuri::DezinfectantVirusuri():Dezinfectant() {}

DezinfectantVirusuri::DezinfectantVirusuri(const DezinfectantVirusuri &dezinfectant) : Dezinfectant(dezinfectant) {}

DezinfectantVirusuri::DezinfectantVirusuri(int nrSpecii, const vector<string> &ingrediente,
                                     const vector<string> &suprafete) : Dezinfectant(nrSpecii,
                                                                                                       ingrediente,
                                                                                                       suprafete) {
    eficienta = calculeazaEficienta();
}

DezinfectantVirusuri::~DezinfectantVirusuri() {}

double DezinfectantVirusuri::calculeazaEficienta() {
    eficienta = (double)nrSpecii / (100000000.0);
    return eficienta;
}

//--------------------------------------------------------------------------------------------------------------------
class DezinfectantKIller:  public DezinfectantBacterii, public DezinfectantVirusuri, public DezinfectantFungi{
public:
    DezinfectantKIller(): DezinfectantBacterii(), DezinfectantFungi(), DezinfectantVirusuri(){};
    DezinfectantKIller(const DezinfectantKIller &dezinfectant):DezinfectantBacterii(dezinfectant){};
    DezinfectantKIller(int nrSpecii, const vector<string> &ingrediente, const vector<string> &suprafete,double eficienta):DezinfectantBacterii(nrSpecii,ingrediente,suprafete){eficienta = calculeazaEficienta();};
    DezinfectantKIller& operator=(const DezinfectantKIller& dezinfectant){
        nrSpecii = dezinfectant.nrSpecii;
        ingrediente = dezinfectant.ingrediente;
        suprafete = dezinfectant.suprafete;
        eficienta = dezinfectant.eficienta;
        return *this;};
    virtual ~DezinfectantKIller(){};


    friend istream& operator>>(istream& is,DezinfectantKIller& dezinfectantKIller);
    friend ostream& operator<<(ostream& os,DezinfectantKIller& dezinfectantKIller);

    double calculeazaEficienta();

};
istream& operator>>(istream& is,DezinfectantKIller& dezinfectantKIller) {
    cout << "Dezinfectant Virusuri\n";
    cout << "Introduceti nr specii:\n";
    is >> dezinfectantKIller.nrSpecii;
    is.get();
    cout << "Introduceti nr de ingrediente:\n";
    int nr;
    is >> nr;
    is.get();
    for(int i = 0; i < nr; ++i){
        cout << "Introduceti ingredient:\n";
        string x;
        getline(is, x);
        dezinfectantKIller.ingrediente.push_back(x);
    }
    cout << "Introduceti nr de suprafete:\n";
    is >> nr;
    is.get();
    for(int i = 0; i < nr; ++i){
        cout << "Introduceti suprafete:\n";
        string x;
        getline(is, x);
        dezinfectantKIller.suprafete.push_back(x);
    }
    dezinfectantKIller.calculeazaEficienta();
    return is;
}
ostream& operator<<(ostream& os,DezinfectantKIller& dezinfectantKIller){
    os << "Dezinfectant Fungi\n";
    os << "Nr specii: " << dezinfectantKIller.nrSpecii << '\n';
    os << "Ingrediente:\n";
    for(int i = 0; i < dezinfectantKIller.ingrediente.size(); ++i){
        os <<" - " << dezinfectantKIller.ingrediente[i] <<"\n";
    }
    os << "Suprafete:\n";
    for(int i = 0; i < dezinfectantKIller.suprafete.size(); ++i){
        os <<" - " << dezinfectantKIller.suprafete[i] <<"\n";
    }
    os << "Eficienta: " << dezinfectantKIller.eficienta << '\n';
    return os;
}
double DezinfectantKIller::calculeazaEficienta() {
    eficienta = (double)nrSpecii / (100000000.0) + (double)nrSpecii / (1.5 * 1000000.0) + (double)nrSpecii / ( 1000000000.0);
    return eficienta;
}

//--------------------------------------------------------------------------------------------------------------------

class Client{
private:
    string nume;
    static int id;
public:
    const string &getNume() const;
    void setNume(const string &nume);

    static int getId();
    static void setId(int id);

    Client(const string &nume);
    Client();
    Client(const Client& client);
    Client& operator=(const Client& client);
    virtual ~Client();

    bool operator==(const Client &rhs) const;

    bool operator!=(const Client &rhs) const;

    friend istream& operator>>(istream& is, Client& client);
    friend ostream & operator<<(ostream& is, Client& client);

};
istream& operator>>(istream& is, Client& client){
    cout << "Introduceti numele clientului:\n";
    getline(is, client.nume);
    return is;
}
ostream & operator<<(ostream& os, Client& client){
    os << "Numele clientului: " << client.nume << '\n';
    os << "Id client: " << client.id << '\n';
    return os;
}
int Client::id = 0;
Client::Client() {
    nume = "";
    ++id;
}
Client::Client(const Client &client) {
    nume = client.nume;
    id = client.id;
}
Client & Client::operator=(const Client &client) {
    nume = client.nume;
    id = client.id;
    return *this;
}
Client::Client(const string &nume) : nume(nume) {++id;}

Client::~Client() {
    nume = "";
    --id;
}

const string &Client::getNume() const {
    return nume;
}

void Client::setNume(const string &nume) {
    Client::nume = nume;
}

int Client::getId() {
    return id;
}

void Client::setId(int id) {
    Client::id = id;
}

bool Client::operator==(const Client &rhs) const {
    return nume == rhs.nume;
}

bool Client::operator!=(const Client &rhs) const {
    return !(rhs == *this);
}

//-------------------------------------------------------------------------------------------------------------------------------
class Achizitie{
private:


    Data data;
    vector<Dezinfectant*> dezinfectanti;
    vector<Masca*> masti;
    double pret;
    Client client;
public:
    const Data &getData() const;
    void setData(const Data &data);

    const vector<Dezinfectant *> &getDezinfectanti() const;
    void setDezinfectanti(const vector<Dezinfectant *> &dezinfectanti);

    const vector<Masca *> &getMasti() const;
    void setMasti(const vector<Masca *> &masti);

    double getPret() const;
    void setPret(double pret);

    const Client &getClient() const;
    void setClient(const Client &client);

    Achizitie();
    Achizitie(int zi, int luna, int an, Client c);
    Achizitie(const Achizitie& achizitie);
    Achizitie(Data d, vector<Dezinfectant*> dezinf, vector<Masca*> mas, Client cl);
    ~Achizitie();
    Achizitie& operator=(const Achizitie& achizitie);

    void addDezinfectant(Dezinfectant* d){
        if(DezinfectantBacterii *dez = dynamic_cast<DezinfectantBacterii*>(d))
            dezinfectanti.push_back(new DezinfectantBacterii(*dez));
        else if(DezinfectantFungi *dez = dynamic_cast<DezinfectantFungi*>(d))
            dezinfectanti.push_back(new DezinfectantFungi(*dez));
        else if(DezinfectantVirusuri *dez = dynamic_cast<DezinfectantVirusuri*>(d))
            dezinfectanti.push_back(new DezinfectantVirusuri(*dez));
        else if(DezinfectantKIller *dez = dynamic_cast<DezinfectantKIller*>(d))
            dezinfectanti.push_back(new DezinfectantKIller(*dez));
    }
    void addMasca(Masca* m){
        if(MascaChirugicala *masca = dynamic_cast<MascaChirugicala*>(m))
            masti.push_back(new MascaChirugicala(*masca));
        else if(MascaPolicarbonat *masca = dynamic_cast<MascaPolicarbonat*>(m))
            masti.push_back(new MascaPolicarbonat(*masca));
    }
    Achizitie& operator+=(Dezinfectant *d){
        dezinfectanti.push_back(d);
        return  *this;
    }
    Achizitie& operator+=(Masca *m){
        masti.push_back(m);
        return  *this;
    }
    double getTotal(){
        double total = 0;
        for(int i = 0; i < masti.size(); ++i)
            if(MascaPolicarbonat *m = dynamic_cast<MascaPolicarbonat*>(masti[i]))
                total += 20;
            else if(MascaChirugicala *m = dynamic_cast<MascaChirugicala*>(masti[i])){
                if(m->getTipProtectie() == "ffp1")
                    total += 5;
                else if(m->getTipProtectie() == "ffp2")
                    total += 10;
                else if(m->getTipProtectie() == "ffp3")
                    total += 15;
            }
        for(int i = 0; i < dezinfectanti.size(); ++i){
            if(dezinfectanti[i]->getEficienta()<0.9)
                total += 10;
            else if(dezinfectanti[i]->getEficienta()<0.95)
                total += 20;
            else if(dezinfectanti[i]->getEficienta()<0.975)
                total += 30;
            else if(dezinfectanti[i]->getEficienta()<0.99)
                total += 40;
            else if(dezinfectanti[i]->getEficienta()<0.9999)
                total += 50;
        }
        return total;
    }

    friend istream& operator>>(istream& is,Achizitie& achizitie);
    friend ostream& operator<<(ostream& os,Achizitie& achizitie);

    bool operator< (Achizitie &a){
        if(getTotal()<a.getTotal())
            return 1;
        return 0;
    }
    bool operator==(Achizitie& a){
        if(getTotal()==a.getTotal())
            return 1;
        return 0;
    }

};
Achizitie::Achizitie(int zi, int luna, int an, Client c) : data(zi,luna,an), client(c){

}
istream& operator>>(istream& is,Achizitie& achizitie){
    int nrMasti;
    cout << "Introduceti numarul de masti:\n";
    is >> nrMasti;
    is.get();
    for(int i = 0 ;i< nrMasti;++i){
        string tip;
        Masca *p = nullptr;
        while(true){
            try{
                cout << "Introduceti tipul mastii - poli sau chir\n";
                getline(is, tip);
                if(tip == "poli"){
                    p = new MascaPolicarbonat;
                    break;;
                }

                else if(tip == "chir"){
                    p = new MascaChirugicala;
                    break;
                }
                else throw string("Tip invalid!");
            }
            catch(string s){
                cout << s << '\n';
            }
        }
        is >> *p;
        achizitie.masti.push_back(p);
    }
    int nrDez;
    cout << "Introduceti numarul de dezinfectanti:\n";
    is >> nrDez;
    is.get();
    for(int i = 0 ;i< nrDez;++i){
        string tip;
        Dezinfectant *p = nullptr;
        while(true){
            try{
                cout << "Introduceti tipul dezinfectantului - bacterii - virusuri- fungi- tot\n";
                getline(is, tip);
                if(tip == "bacterii"){
                    p = new DezinfectantBacterii;
                    break;
                }
                else if(tip == "virusuri") {
                    p = new DezinfectantVirusuri;
                    break;
                }
                else if(tip == "fungi") {
                    p = new DezinfectantFungi;
                    break;
                }
                else if(tip == "tot") {
                    p = new DezinfectantKIller;
                    break;
                }
                else throw string("Tip invalid!");
            }
            catch(string s){
                cout << s << '\n';
            }
        }
        is >> *p;
        achizitie.dezinfectanti.push_back(p);
    }
    cout << "Introduceti client:\n";
    is >> achizitie.client;
    cout << "Introduceti data:\n";
    is >> achizitie.data;
    return is;
}

ostream& operator<<(ostream& os,Achizitie& achizitie){
    os << "Client: " << achizitie.client << '\n';
    os << "Data: " << achizitie.data << '\n';
    os << "Masti:\n";
    for(int i = 0;i < achizitie.masti.size();++i)
        os << *achizitie.masti[i] << '\n';
    os << "Dezinfectanti:\n";
    for(int i = 0;i < achizitie.dezinfectanti.size();++i)
        os << *achizitie.dezinfectanti[i] << '\n';
    return os;
}
Achizitie::~Achizitie() {
    for(int i = 0;i < masti.size();++i)
        delete masti[i];
    masti.clear();
    for(int i = 0;i < dezinfectanti.size();++i)
        delete dezinfectanti[i];
    dezinfectanti.clear();
}
Achizitie::Achizitie() {
    Data d;
    data = d;
    pret = 0;
    Client c;
    client = c;
}
Achizitie::Achizitie(const Achizitie &achizitie) {
    data = achizitie.data;
    client = achizitie.client;
    pret = achizitie.pret;
    for(auto d: achizitie.dezinfectanti)
        addDezinfectant(d);
    for(auto m: achizitie.masti)
        addMasca(m);
}
Achizitie::Achizitie(Data d, vector<Dezinfectant *> dezinf, vector<Masca *> mas, Client cl) {
    data = d;
    client = cl;
    for(auto d: dezinf)
        addDezinfectant(d);
    for(auto m: mas)
        addMasca(m);
}
Achizitie & Achizitie::operator=(const Achizitie &achizitie) {
    if(this == &achizitie)
        return *this;
    for(int i = 0; i < dezinfectanti.size();++i)
        delete dezinfectanti[i];
    dezinfectanti.clear();
    for(auto d : achizitie.dezinfectanti)
        addDezinfectant(d);
    for(int i = 0; i < masti.size();++i)
        delete masti[i];
    masti.clear();
    for(auto m : achizitie.masti)
        addMasca(m);
    return *this;

}

const Data &Achizitie::getData() const {
    return data;
}

void Achizitie::setData(const Data &data) {
    Achizitie::data = data;
}

const vector<Dezinfectant *> &Achizitie::getDezinfectanti() const {
    return dezinfectanti;
}

void Achizitie::setDezinfectanti(const vector<Dezinfectant *> &dezinfectanti) {
    Achizitie::dezinfectanti = dezinfectanti;
}

const vector<Masca *> &Achizitie::getMasti() const {
    return masti;
}

void Achizitie::setMasti(const vector<Masca *> &masti) {
    Achizitie::masti = masti;
}

double Achizitie::getPret() const {
    return pret;
}

void Achizitie::setPret(double pret) {
    Achizitie::pret = pret;
}

const Client &Achizitie::getClient() const {
    return client;
}

void Achizitie::setClient(const Client &client) {
    Achizitie::client = client;
}


class Manager{
private:
    vector <Achizitie*> achizitii;
    vector <Dezinfectant*> dezinfectanti;
    vector <Masca*> masti;

    static Manager* instanta;
    Manager(){}
    Manager(const Manager& m) = delete;
    Manager(Manager& m) noexcept = delete;
    Manager& operator=(const Manager& m) = delete;
    Manager& operator=(Manager& ob) = delete;

public:
    static Manager* getInstanta(){
        if(instanta == nullptr)
            instanta = new Manager();
        return instanta;
    }
    ~Manager(){
        for(int i = 0;i < achizitii.size();++i)
            delete achizitii[i];
        achizitii.clear();
        for(int i = 0;i < dezinfectanti.size();++i)
            delete dezinfectanti[i];
        dezinfectanti.clear();
        for(int i = 0;i < masti.size();++i)
            delete masti[i];
        masti.clear();
    }
    void deleteInstanta(){
        if(instanta!= nullptr)
            delete instanta;
        instanta = nullptr;
    }
    void demo();
    void adaugaDezinfectant();
    void adaugaMasca();
    void adaugaAchizitie();
    void celMaiEficientDezinfectant();
    void venitLuna(int luna);
    void venitMastiCuModel();
    void modificaReteta();
    void celMaiFidelClient();
    void ziuaCuCeleMaiSlabeVenituri();
    void TVA(int an);


};
void Manager::adaugaDezinfectant() {
    string tip;
    Dezinfectant *p = nullptr;
    while(true){
        try{
            cout << "Introduceti tipul dezinfectantului - bacterii - virusuri- fungi- tot\n";
            getline(cin, tip);
            if(tip == "bacterii"){
                p = new DezinfectantBacterii;
                break;
            }
            else if(tip == "virusuri") {
                p = new DezinfectantVirusuri;
                break;
            }
            else if(tip == "fungi") {
                p = new DezinfectantFungi;
                break;
            }
            else if(tip == "tot") {
                p = new DezinfectantKIller;
                break;
            }
            else throw string("Tip invalid!");
        }
        catch(string s){
            cout << s << '\n';
        }
    }
    cin >> *p;
    dezinfectanti.push_back(p);
}
void Manager::adaugaMasca() {
    string tip;
    Masca *p = nullptr;
    while(true){
        try{
            cout << "Introduceti tipul mastii - poli sau chir\n";
            getline(cin, tip);
            if(tip == "poli"){
                p = new MascaPolicarbonat;
                break;;
            }

            else if(tip == "chir"){
                p = new MascaChirugicala;
                break;
            }
            else throw string("Tip invalid!");
        }
        catch(string s){
            cout << s << '\n';
        }
    }
    cin >> *p;
    masti.push_back(p);
}
void Manager::celMaiEficientDezinfectant() {
    double maxEf = 0;
    int pozMax =0;
    for(int i = 0;i < dezinfectanti.size();++i)
        if(dezinfectanti[i]->getEficienta()>maxEf){
            maxEf = dezinfectanti[i]->getEficienta();
            pozMax = i;
        }
    cout << *(dezinfectanti[pozMax]) << '\n';
}
void Manager::venitLuna(int luna) {
    double venit = 0;
    for(int i = 0;i < achizitii.size();++i)
        if(achizitii[i]->getData().getLuna() == luna)
            venit += achizitii[i]->getTotal();

    cout << venit << '\n';
}

void Manager::venitMastiCuModel() {
    double venit = 0;
    for(int i = 0;i < achizitii.size();++i){
        for (int j = 0;j < achizitii[i]->getMasti().size();++j)
            if(MascaChirugicala *m = dynamic_cast<MascaChirugicala*>(achizitii[i]->getMasti()[j]))
                if(m->isModelSpecial()){
                    if(m->getTipProtectie() == "ffp1")
                        venit += 7.5;
                    else  if(m->getTipProtectie() == "ffp2")
                        venit += 10;
                    else if(m->getTipProtectie() == "ffp3")
                        venit += 22.5;
                }
    }
    cout << venit << '\n';
}
void Manager::modificaReteta() {
    cout << "De implementat\n";
}
void Manager::celMaiFidelClient() {
    int poz = 0, ma =0;
    for(int i = 0;i < achizitii.size();++i){
        int nr = 0;
        for(int j = i+1;j< achizitii.size();++i)
            if(achizitii[i]->getClient() == achizitii[j]->getClient())
                ++nr;
        if(nr>ma){
            ma = nr;
            poz = i;
        }
    }
    cout << achizitii[poz]->getClient().getNume() << '\n';
}
void Manager::ziuaCuCeleMaiSlabeVenituri() {
    double venitMinim = achizitii[0]->getTotal();
    Data zi = achizitii[0]->getData();

    for(int i = 1;i < achizitii.size();++i){
        double venit = achizitii[i]->getTotal();
        if(venit < venitMinim){
            venitMinim = venit;
            zi = achizitii[i]->getData();
        }
    }
    cout << zi << '\n';
}
void Manager::TVA(int an) {
    double venit = 0;
    for(int i = 0;i < achizitii.size();++i)
        if(achizitii[i]->getData().getAn() == an)
            venit += achizitii[i]->getTotal();

    double tva = 0.19 * venit;
    cout << tva << '\n';
}
void Manager::demo() {
    MascaChirugicala mc1, mc2("ffp2", "verde brotăcel", 55,0), mc3(mc1), mc4, mc5;
    mc4 = mc2;
    std::cin >> mc5;
    std::cout << mc1 << mc2;
    MascaPolicarbonat* mp1=new MascaPolicarbonat(), * mp2=new MascaPolicarbonat();
    MascaPolicarbonat* mp3 = new MascaPolicarbonat("ffp2","elastic");
    std::cin >> *mp1 >> *mp2;
    std::cout <<*mp3;
    Dezinfectant* d1 = new DezinfectantBacterii(100000000, std::vector<string>({"sulfatinon-ionici", "sulfati cationici", "parfumuri", "Linalool", "Metilpropanol butilpentil"}),std::vector<string>({"lemn", "sticla", "metal", "ceramica", "marmura"}));
    Dezinfectant* d2 = new DezinfectantVirusuri(50000000, std::vector<string>({"AlkilDimetilm Benzil Crlorura de amoniu", "parfumuri", "Butilpentil metilpropinal"}), std::vector<string>({"lemn", "sticla", "ceramica", "marmura"}));
    Dezinfectant* d3 = new DezinfectantFungi(1400000, std::vector<string>({"Alkil EtilBenzil Crlorura de amoniu", "parfumuri", "Butilpentil metilpropinal"}), std::vector<string>({"sticla", "plastic"}));
    cout << d1->calculeazaEficienta() << " " << d2->calculeazaEficienta() << " " << d3->calculeazaEficienta() << "\n";
    Client c;
    c.setNume("PlushBio SRL");
    Achizitie* a1 = new Achizitie(26, 5, 2020, Client("PlushBio SRL"));
    *a1 += mp1; //se adauga masca de policarbonat mp1 in lista de masti achizitionate
    *a1 += (&mc1); //se adauga masca chirugicala mc1 in lista
    *a1 += d3; // se adauga dezinfectantu de fungi d3 in lista de dezinfectanti achizitionati
    Achizitie* a2 = new Achizitie(25, 5, 2020, Client("Gucci"));
    *a2 += d1;
    *a2 += d2;
    *a2 += d2;
    Achizitie a3, a4(*a1);
    a3 = *a2;
    if(*a1 < *a2) {
        std::cout << a1->getClient().getNume()<< " are valoarea facturii mai mica.\n";
    }else if (*a1 == *a2) {
        std::cout << a1->getClient().getNume() << " si " << a2->getClient().getNume() << " au aceasi valoare afacturii.\n";}
    else {
        std::cout << a2->getClient().getNume() << " are valoarea facturii mai mica.\n";
    }
}
void Manager::adaugaAchizitie() {
    Achizitie *a = new Achizitie();
    cin >> (*a);
    achizitii.push_back(a);
}
Manager* Manager::instanta = nullptr;

int main() {
    int optiune;
    Manager* m = m->getInstanta();
    while(1){
        cout << "0.Demo\n";
        cout << "1.Adauga dezinf\n";
        cout << "2.Adauga masca\n";
        cout << "3.Cel mai ef dezinf\n";
        cout << "4.Venit pe luna\n";
        cout << "5.Venit pe masti\n";
        cout << "6.Modif reteta\n";
        cout << "7.Cel mai fidel\n";
        cout << "8.Cea mai slaba zi\n";
        cout << "9.TVA\n";
        cout << "10.Adauga achizitie\n";
        cout << "11.inchide\n";
            try{
                cin >> optiune;
                cin.get();
                if(optiune < 0 || optiune > 11)
                    throw string("Optiune gresita!");
                else{ if(optiune == 0) m->demo();
                    if (optiune == 1) m->adaugaDezinfectant();
                    else if (optiune == 2) m->adaugaMasca();
                    else if (optiune == 3) m->celMaiEficientDezinfectant();
                    else if (optiune == 4) {
                        int luna;
                        cin >> luna;
                        cin.get();
                        m->venitLuna(luna);
                    }
                    else if (optiune == 5) m->venitMastiCuModel();
                    else if(optiune == 6) m->modificaReteta();
                    else if (optiune == 7) m->celMaiFidelClient();
                    else if(optiune == 8) m->ziuaCuCeleMaiSlabeVenituri();
                    else if(optiune == 9) {
                        int an;
                        cin >> an;
                        cin.get();
                        m->TVA(an);
                    }
                    else if(optiune == 10) m->adaugaAchizitie();
                    else if(optiune == 11) break;

                }
            }
            catch (string s){
                cout << s << '\n';
            }


    }
    return 0;
}
