#include <iostream>
#include <vector>
using namespace std;
class Bilet{
protected:
    string plecare;
    string sosire;
    int zi, luna, an;
    int ora, minut;
    int cod_tren;
    int durata;
    int distanta;
    double pret;
    int clasa;
    static int id_bilet;
    string cod_bilet;
public:
    Bilet();
    Bilet(const Bilet& bilet);
    Bilet(const string &plecare, const string &sosire, int zi, int luna, int an, int ora, int minut, int codTren,
          int durata, int distanta, int clasa);
    Bilet& operator=(const Bilet& bilet);

    virtual ~Bilet();

    const string &getPlecare() const;
    void setPlecare(const string &plecare);

    const string &getSosire() const;
    void setSosire(const string &sosire);

    int getZi() const;
    void setZi(int zi);

    int getLuna() const;
    void setLuna(int luna);

    int getAn() const;
    void setAn(int an);

    int getOra() const;
    void setOra(int ora);

    int getMinut() const;
    void setMinut(int minut);

    int getCodTren() const;
    void setCodTren(int codTren);

    int getDurata() const;
    void setDurata(int durata);

    int getDistanta() const;
    void setDistanta(int distanta);

    double getPret() const;
    void setPret(double pret);

    int getClasa() const;
    void setClasa(int clasa);

    static int getIdBilet();
    static void setIdBilet(int idBilet);

    const string &getCodBilet() const;
    void setCodBilet(const string &codBilet);

    friend istream& operator>>(istream& is, Bilet& bilet);
    friend ostream& operator<<(ostream& os, Bilet& bilet);
    virtual double getPret() = 0;
    virtual string getCodBilet() = 0;


};
istream& operator>>(istream& is, Bilet& bilet){
    cout << "Introduceti statia de plecare:\n";
    getline(is, bilet.plecare);
    cout << "Introduceti statia de sosire:\n";
    getline(is, bilet.sosire);
    cout << "Introduceti data:\n";
    cout << "Introduceti an:\n";
    bool bisect = 0;
    int zile[]={0,31,28,31,30,31,30,31,31,30,31,30,31};
    int an;
    is >> an;
    is.get();
    if ((an % 4 == 0 && an % 100!=0) || an%400 == 0 )
        bisect = 1;
    bilet.an = an;
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
    bilet.luna = luna;
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
    bilet.zi = zi;

    cout << "Introduceti ora\n";
    int ora;
    while(true){
        try {
            is >> ora;
            is.get();
            if(ora < 0 || ora > 24)
                throw string("Ora invalida!");
            else break;
        }
        catch (string s){
            cout << s << '\n';
        }
    }
    bilet.ora = ora;
    cout << "Introduceti minutul\n";
    int minut;
    while(true){
        try {
            is >> minut;
            is.get();
            if(minut < 0 || minut > 59)
                throw string("Minut invalid!");
            else break;
        }
        catch (string s){
            cout << s << '\n';
        }
    }
    bilet.minut = minut;

    cout << "Introduceti codul trenului\n";
    is >> bilet.cod_tren;
    is.get();
    cout << "Introduceti durata\n";
    is >> bilet.durata;
    is.get();
    cout << "Introduceti distanta\n";
    is >> bilet.distanta;
    is.get();
    cout << "Introduceti clasa\n";
    is >> bilet.clasa;
    bilet.pret = bilet.getPret();
    bilet.cod_bilet = bilet.getCodBilet();
    is.get();
    return is;
}
ostream& operator<<(ostream& os, Bilet& bilet){
    os << "Id bilet: " << bilet.id_bilet << '\n';
    os << "Cod bilet: " << bilet.cod_bilet << '\n';
    os << "Statie plecare: " << bilet.plecare << '\n';
    os << "Statie sosire: " << bilet.sosire << '\n';
    os << "Data: " << bilet.zi << '/' << bilet.luna << '/' << bilet.an << '\n';
    os << "Ora: " << bilet.ora << ':' << bilet.minut << '\n';
    os << "Durata: " << bilet.durata << '\n';
    os << "Distanta: " << bilet.distanta << '\n';
    os << "Clasa: " << bilet.clasa << '\n';
    os << "Pret: " << bilet.pret << '\n';
    return os;
}

int Bilet::id_bilet = 0;
Bilet::Bilet() {
    plecare = sosire = cod_bilet = "";
    zi = luna = an = ora = minut = durata = distanta = clasa = 0;
    pret = 0;
    ++id_bilet;
}
Bilet & Bilet::operator=(const Bilet &bilet) {
    plecare = bilet.plecare;
    sosire = bilet.sosire;
    zi = bilet.zi;
    luna = bilet.luna;
    an = bilet.an;
    ora = bilet.ora;
    minut = bilet.minut;
    cod_tren = bilet.cod_tren;
    durata = bilet.durata;
    distanta = bilet.distanta;
    clasa = bilet.clasa;
    pret = bilet.pret;
    cod_bilet = bilet.cod_bilet;
    id_bilet = bilet.id_bilet;
    return *this;
}

Bilet::Bilet(const string &plecare, const string &sosire, int zi, int luna, int an, int ora, int minut, int codTren,
             int durata, int distanta, int clasa) : plecare(plecare), sosire(sosire), zi(zi), luna(luna),
                                                                 an(an), ora(ora), minut(minut), cod_tren(codTren),
                                                                 durata(durata), distanta(distanta),
                                                                 clasa(clasa) {
    ++id_bilet;

}
Bilet::Bilet(const Bilet &bilet): plecare(bilet.plecare), sosire(bilet.sosire), zi(bilet.zi), luna(bilet.luna),
an(bilet.an), ora(bilet.ora), minut(bilet.minut), cod_tren(bilet.cod_tren),
durata(bilet.durata), distanta(bilet.distanta),
clasa(bilet.clasa),pret(bilet.pret), cod_bilet(bilet.cod_bilet){
    id_bilet = bilet.id_bilet;
}

const string &Bilet::getPlecare() const {
    return plecare;
}

void Bilet::setPlecare(const string &plecare) {
    Bilet::plecare = plecare;
}

const string &Bilet::getSosire() const {
    return sosire;
}

void Bilet::setSosire(const string &sosire) {
    Bilet::sosire = sosire;
}

int Bilet::getZi() const {
    return zi;
}

void Bilet::setZi(int zi) {
    Bilet::zi = zi;
}

int Bilet::getLuna() const {
    return luna;
}

void Bilet::setLuna(int luna) {
    Bilet::luna = luna;
}

int Bilet::getAn() const {
    return an;
}

void Bilet::setAn(int an) {
    Bilet::an = an;
}

int Bilet::getOra() const {
    return ora;
}

void Bilet::setOra(int ora) {
    Bilet::ora = ora;
}

int Bilet::getMinut() const {
    return minut;
}

void Bilet::setMinut(int minut) {
    Bilet::minut = minut;
}

int Bilet::getCodTren() const {
    return cod_tren;
}

void Bilet::setCodTren(int codTren) {
    cod_tren = codTren;
}

int Bilet::getDurata() const {
    return durata;
}

void Bilet::setDurata(int durata) {
    Bilet::durata = durata;
}

int Bilet::getDistanta() const {
    return distanta;
}

void Bilet::setDistanta(int distanta) {
    Bilet::distanta = distanta;
}

double Bilet::getPret() const {
    return pret;
}

void Bilet::setPret(double pret) {
    Bilet::pret = pret;
}

int Bilet::getClasa() const {
    return clasa;
}

void Bilet::setClasa(int clasa) {
    Bilet::clasa = clasa;
}

int Bilet::getIdBilet() {
    return id_bilet;
}

void Bilet::setIdBilet(int idBilet) {
    id_bilet = idBilet;
}

const string &Bilet::getCodBilet() const {
    return cod_bilet;
}

void Bilet::setCodBilet(const string &codBilet) {
    cod_bilet = codBilet;
}

Bilet::~Bilet() {
    plecare = sosire = cod_bilet = "";
    zi = luna = an = ora = minut = durata = distanta = clasa = 0;
    pret = 0;
    --id_bilet;
}

class BiletRegio: virtual public Bilet{
public:
    BiletRegio():Bilet() {}
    BiletRegio(const string &plecare, const string &sosire, int zi, int luna, int an, int ora, int minut, int codTren,
               int durata, int distanta, int clasa) : Bilet(plecare, sosire, zi, luna, an, ora, minut, codTren, durata,
                                                            distanta, clasa) {
        pret = getPret();
        cod_bilet = getCodBilet();

    }
    BiletRegio(const BiletRegio &bilet);
    virtual ~BiletRegio();
    BiletRegio& operator=(const BiletRegio &bilet);

    friend istream& operator>>(istream& is, BiletRegio& bilet);
    friend ostream& operator<<(ostream& os, BiletRegio& bilet);

    double getPret() override ;
    string getCodBilet() override;
};
istream& operator>>(istream& is, BiletRegio& bilet){
    cout << "Introduceti statia de plecare:\n";
    getline(is, bilet.plecare);
    cout << "Introduceti statia de sosire:\n";
    getline(is, bilet.sosire);
    cout << "Introduceti data:\n";
    cout << "Introduceti an:\n";
    bool bisect = 0;
    int zile[]={0,31,28,31,30,31,30,31,31,30,31,30,31};
    int an;
    is >> an;
    is.get();
    if ((an % 4 == 0 && an % 100!=0) || an%400 == 0 )
        bisect = 1;
    bilet.an = an;
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
    bilet.luna = luna;
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
    bilet.zi = zi;

    cout << "Introduceti ora\n";
    int ora;
    while(true){
        try {
            is >> ora;
            is.get();
            if(ora < 0 || ora > 24)
                throw string("Ora invalida!");
            else break;
        }
        catch (string s){
            cout << s << '\n';
        }
    }
    bilet.ora = ora;
    cout << "Introduceti minutul\n";
    int minut;
    while(true){
        try {
            is >> minut;
            is.get();
            if(minut < 0 || minut > 59)
                throw string("Minut invalid!");
            else break;
        }
        catch (string s){
            cout << s << '\n';
        }
    }
    bilet.minut = minut;

    cout << "Introduceti codul trenului\n";
    is >> bilet.cod_tren;
    is.get();
    cout << "Introduceti durata\n";
    is >> bilet.durata;
    is.get();
    cout << "Introduceti distanta\n";
    is >> bilet.distanta;
    is.get();
    cout << "Introduceti clasa\n";
    is >> bilet.clasa;
    is.get();
    bilet.pret = bilet.getPret();
    bilet.cod_bilet = bilet.getCodBilet();
    return is;
}
ostream& operator<<(ostream& os, BiletRegio& bilet){
    os << "Id bilet: " << bilet.id_bilet << '\n';
    os << "Cod bilet: " << bilet.cod_bilet << '\n';
    os << "Statie plecare: " << bilet.plecare << '\n';
    os << "Statie sosire: " << bilet.sosire << '\n';
    os << "Data: " << bilet.zi << '/' << bilet.luna << '/' << bilet.an << '\n';
    os << "Ora: " << bilet.ora << ':' << bilet.minut << '\n';
    os << "Durata: " << bilet.durata << '\n';
    os << "Distanta: " << bilet.distanta << '\n';
    os << "Clasa: " << bilet.clasa << '\n';
    os << "Pret: " << bilet.pret << '\n';
    return os;
}
BiletRegio & BiletRegio::operator=(const BiletRegio &bilet) {
    plecare = bilet.plecare;
    sosire = bilet.sosire;
    zi = bilet.zi;
    luna = bilet.luna;
    an = bilet.an;
    ora = bilet.ora;
    minut = bilet.minut;
    cod_tren = bilet.cod_tren;
    durata = bilet.durata;
    distanta = bilet.distanta;
    clasa = bilet.clasa;
    pret = bilet.pret;
    cod_bilet = bilet.cod_bilet;
    id_bilet = bilet.id_bilet;

    return *this;
}
double BiletRegio::getPret() {
    double val = (double) distanta * 0.39;
    if(clasa == 1)
        val += 0.2*val;
    return val;
}
string BiletRegio::getCodBilet() {
    string rez = "R";
    if(clasa == 1)
        rez += "I-";
    else rez += "II-";
    rez += to_string(id_bilet);
    return rez;

}

BiletRegio::BiletRegio(const BiletRegio &bilet) : Bilet(bilet) {}

BiletRegio::~BiletRegio() {}


class BiletInterRegio:virtual public Bilet{
protected:
    int nr_loc;
public:
    BiletInterRegio();
    BiletInterRegio(const string &plecare, const string &sosire, int zi, int luna, int an, int ora, int minut, int codTren,
                    int durata, int distanta, int clasa,int nrLoc):Bilet(plecare, sosire, zi, luna, an, ora, minut, codTren, durata,
                                                                         distanta, clasa),nr_loc(nrLoc) {
        pret = getPret();
        cod_bilet = getCodBilet();

    }
    BiletInterRegio(const BiletInterRegio& bilet);
    BiletInterRegio& operator=(const BiletInterRegio& bilet);

    virtual ~BiletInterRegio();

    double getPret() override ;
    string getCodBilet() override;

    friend istream& operator>>(istream& is, BiletInterRegio& bilet);
    friend ostream& operator<<(ostream& os, BiletInterRegio& bilet);

};

istream& operator>>(istream& is, BiletInterRegio& bilet){
    cout << "Introduceti statia de plecare:\n";
    getline(is, bilet.plecare);
    cout << "Introduceti statia de sosire:\n";
    getline(is, bilet.sosire);
    cout << "Introduceti data:\n";
    cout << "Introduceti an:\n";
    bool bisect = 0;
    int zile[]={0,31,28,31,30,31,30,31,31,30,31,30,31};
    int an;
    is >> an;
    is.get();
    if ((an % 4 == 0 && an % 100!=0) || an%400 == 0 )
        bisect = 1;
    bilet.an = an;
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
    bilet.luna = luna;
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
    bilet.zi = zi;

    cout << "Introduceti ora\n";
    int ora;
    while(true){
        try {
            is >> ora;
            is.get();
            if(ora < 0 || ora > 24)
                throw string("Ora invalida!");
            else break;
        }
        catch (string s){
            cout << s << '\n';
        }
    }
    bilet.ora = ora;
    cout << "Introduceti minutul\n";
    int minut;
    while(true){
        try {
            is >> minut;
            is.get();
            if(minut < 0 || minut > 59)
                throw string("Minut invalid!");
            else break;
        }
        catch (string s){
            cout << s << '\n';
        }
    }
    bilet.minut = minut;

    cout << "Introduceti codul trenului\n";
    is >> bilet.cod_tren;
    is.get();
    cout << "Introduceti durata\n";
    is >> bilet.durata;
    is.get();
    cout << "Introduceti distanta\n";
    is >> bilet.distanta;
    is.get();
    cout << "Introduceti clasa\n";
    is >> bilet.clasa;
    is.get();
    cout << "Introduceti nr loc:\n";
    is >> bilet.nr_loc;
    is.get();
    bilet.pret = bilet.getPret();
    bilet.cod_bilet = bilet.getCodBilet();
    return is;
}
ostream& operator<<(ostream& os, BiletInterRegio& bilet){
    os << "Id bilet: " << bilet.id_bilet << '\n';
    os << "Cod bilet: " << bilet.cod_bilet << '\n';
    os << "Statie plecare: " << bilet.plecare << '\n';
    os << "Statie sosire: " << bilet.sosire << '\n';
    os << "Data: " << bilet.zi << '/' << bilet.luna << '/' << bilet.an << '\n';
    os << "Ora: " << bilet.ora << ':' << bilet.minut << '\n';
    os << "Durata: " << bilet.durata << '\n';
    os << "Distanta: " << bilet.distanta << '\n';
    os << "Clasa: " << bilet.clasa << '\n';
    os << "Pret: " << bilet.pret << '\n';
    os << "Nr Loc: " << bilet.nr_loc << '\n';
    return os;
}
BiletInterRegio::BiletInterRegio(const BiletInterRegio &bilet) : Bilet(bilet) {
    nr_loc = bilet.nr_loc;
    pret = getPret();
    cod_bilet = getCodBilet();
}
double BiletInterRegio::getPret() {
    double val = (double) distanta * 0.7;
    if(clasa == 1)
        val += 0.2*val;
    return val;
}
string BiletInterRegio::getCodBilet() {
    string rez = "IR";
    if(clasa == 1)
        rez += "I-";
    else rez += "II-";
    rez += to_string(id_bilet);
    return rez;

}

BiletInterRegio & BiletInterRegio::operator=(const BiletInterRegio &bilet) {
    plecare = bilet.plecare;
    sosire = bilet.sosire;
    zi = bilet.zi;
    luna = bilet.luna;
    an = bilet.an;
    ora = bilet.ora;
    minut = bilet.minut;
    cod_tren = bilet.cod_tren;
    durata = bilet.durata;
    distanta = bilet.distanta;
    clasa = bilet.clasa;
    pret = bilet.pret;
    cod_bilet = bilet.cod_bilet;
    id_bilet = bilet.id_bilet;
    nr_loc = bilet.nr_loc;
    return *this;
}
BiletInterRegio::BiletInterRegio() :Bilet() ,nr_loc(0) {}

BiletInterRegio::~BiletInterRegio() {
    nr_loc = 0;
}
//class BiletDiamant:  public BiletInterRegio, public BiletRegio{
//public:
//    double getPret() override;
//    string getCodBilet() override;
//};


class Manager{
private:
    vector <Bilet*> bilete;


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
        for(int i = 0;i < bilete.size();++i)
            delete bilete[i];
        bilete.clear();
    }
    void deleteInstanta(){
        if(instanta!= nullptr)
            delete instanta;
        instanta = nullptr;
    }
    void demo(){
        cout << "demo";
    }
    void adaugaBilet(){
        string tip;
        Bilet *b = nullptr;
        while(true){
            try {
                cout << "Introduceti tipul biletului - regio sau inter\n";
                getline(cin, tip);
                if (tip == "regio") {
                    b = new BiletRegio;
                    break;
                } else if (tip == "inter") {
                    b = new BiletInterRegio;
                    break;
                } else throw string("Tip invalid!");
            }
            catch (string s){
                cout << s << '\n';
            }
        }
        cin >> *b;
        bilete.push_back(b);
    }
    void bileteTren(int codTren){
        bool ok = false;
        for(int i = 0;i < bilete.size();++i)
            if(bilete[i]->getCodTren() == codTren){
                ok = true;
                cout << *bilete[i] << '\n';
            }
        if(ok == false)
            cout << "Nu exista bilete!\n";
    }
    void calatoriiDistanta(int distanta){
        bool ok = false;
        for(int i = 0;i < bilete.size();++i)
            if(bilete[i]->getDistanta() >= distanta){
                ok = true;
                cout << *bilete[i] << '\n';
            }
        if(ok == false)
            cout << "Nu exista bilete!\n";
    }
    void anulareBilet(string cod){
        bool ok = false;
        for(int i = 0;i < bilete.size();++i)
            if(bilete[i]->getCodBilet() == cod){
                ok = true;
                Bilet *b = bilete[i];
                delete b;
                bilete.erase(bilete.begin()+i);
                break;
            }
        if(ok == false)
            cout << "Nu exista bilete!\n";
    }

};
Manager* Manager::instanta = nullptr;

int main() {
    int optiune;
    Manager* m = m->getInstanta();
    while(1){
        cout << "0.Demo\n";
        cout << "1.Adauga bilet\n";
        cout << "2.Bilete pentru un tren\n";
        cout << "3.Bilete pentru o distanta\n";
        cout << "4.Anulare bilet\n";
        cout << "5.inchide\n";
        try{
            cin >> optiune;
            cin.get();
            if(optiune < 0 || optiune > 11)
                throw string("Optiune gresita!");
            else{ if(optiune == 0) m->demo();
                if (optiune == 1) m->adaugaBilet();
                else if (optiune == 2) {
                    cout << "Introduceti codul trenului:\n";
                    int cod;
                    cin >> cod;
                    cin.get();
                    m->bileteTren(cod);
                }
                else if (optiune == 3) {
                    int dist;
                    cout << "Introduceti distanta:\n";
                    cin >> dist;
                    cin.get();
                    m->calatoriiDistanta(dist);
                }
                else if (optiune == 4) {
                    string cod;
                    cout << "Introduceti codul biletului\n";
                    getline(cin,cod);
                    m->anulareBilet(cod);
                }
                else if(optiune == 5) break;

            }
        }
        catch (string s){
            cout << s << '\n';
        }


    }
    return 0;
}