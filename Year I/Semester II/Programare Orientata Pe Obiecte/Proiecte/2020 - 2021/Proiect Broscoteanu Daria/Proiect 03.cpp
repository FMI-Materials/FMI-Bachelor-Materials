#include <iostream>
#include <vector>
#include <unordered_map>
#include <string>

//Tema 13
//Se dorește implementarea unei aplicații OOP care să permită gestionarea rezervărilor la sălile de spectacol apartinand proprietarului Y.
//Pentru fiecare sală de spectacol se cunoaște cel puțin tipul spectacolului care se desfășoară (e.g. opera, teatru),
//numele spectacolului, genul acestuia (de ex: comedie, drama, etc.) și prețul biletului. Cunoaștem despre toate spectacolele
//cel puțin faptul că au o durata și un nume, durata fiind variabila.
//Piesele de teatru au un singur act. Unele piese de teatru sunt interactive (presupun participarea publicului).
//Despre spectacolele de operă se cunoaște faptul că au un solist principal. Solistul principal are un nume și poate fi tenor, bariton sau bass.
//Unele opere pot avea mai multe acte (2-7), cu durate diferite, specificate pentru fiecare act în parte.
//Între acte se ia o pauza fixă specifică operei ce se va adăuga la durata totală a piesei, pentru a putea să îi estimăm durata totală.
//Să se construiască clasa template GestionareRezervariSpectacole care sa conțină informații despre diversele tipuri de spectacole
//        și să permită efectuarea unor rezervări pentru acestea. Clasa conține indexul rezervarii
//        (incrementat automat la adaugarea unei noi rezervări), și o structura de obiecte, alocată dinamic care sa gestioneze rezervările care se pot face la un anumit spectacol.
//Structura de date: unordered_map sau unordered_set <id_rezervare, structura care reține datele spectacolului rezervat>
//- Să se adauge toate câmpurile relevante pentru modelarea acestei probleme.
//Cerința suplimentară:
//Dat fiind că la sălile de spectacol au început să fie prezentate și spectacole de stand-up,
//să se construiască o specializare aferentă acestui tip de spectacol ce ne va permite să aflăm veniturile obținute de proprietarul Y
//pe baza biletelor vândute la stand-up.

using namespace std;

//--------------------------------------------------------------------------------------------------------------------------

class Solist{
protected:
    string nume;
    string solistType;
public:
    const string getNume();
    void setNume(const string& nume);

    string getSolistType() const;
    void setSolistType(string type);

    Solist();
    Solist(const Solist& solist);
    Solist(const string &nume,const string &type) : nume(nume),solistType(type) {}
    ~Solist();
    Solist& operator=(const Solist& solist);

    bool operator==(const Solist &solist) const;
    bool operator!=(const Solist &solist) const;

    friend istream& operator>>(istream& is, Solist& solist);
    friend ostream& operator<<(ostream&os, Solist& solist);
};
Solist::~Solist() {
    nume.clear();
    solistType.clear();
}

const string Solist::getNume() {
    return nume;
}
void Solist::setNume(const string &nume) {
    this->nume = nume;
}
istream & operator >> (istream & is, Solist & solist) {
    cout << "Introduceti tipul solistului (Tenor/Bass/Bariton):\n";

    while(true) {
        try {
            getline(is, solist.solistType);
            if (solist.solistType == "Tenor") {
                cout << "Introduceti un Solist Tenor: \n";
                try{
                    getline(is, solist.nume);
                    if(islower(solist.nume[0]))
                        throw "Prima litera a numelui trebuie sa fie mare!";
                    else
                        break;
                }
                catch (string s){
                    cout << s << '\n';
                }

            } else if (solist.solistType == "Bass") {
                cout << "Introduceti un Solist Bass: \n";
                getline(is, solist.nume);
                break;
            } else if (solist.solistType == "Bariton") {
                cout << "Introduceti un Solist Bariton: \n";
                getline(is, solist.nume);
                break;
            } else {
                throw "Ati introdus un tip gresit de solist!\nMai introduceti inca o data - cu majuscula!\n";
            }
        }
        catch (string s) {
            cout << s << '\n';
        }
    }


//    cout << "Introduceti numele solistului:\n";
//    getline(is, solist.nume);

    return is;
}
ostream& operator<<(ostream&os, Solist& solist){
    if(solist.solistType == "Tenor"){
        os << "Numele Solistului Tenor: " << solist.nume <<"\n";
    }
    else if (solist.solistType == "Bass"){
        os << "Numele Solistului Bass: " << solist.nume <<"\n";
    }
    else if(solist.solistType == "Bariton"){
        os << "Numele Solistului Bariton: " << solist.nume <<"\n";
    }
    return os;
}

Solist::Solist() {
    nume = "";
    solistType = "";
}
Solist::Solist(const Solist &solist) {
    this->nume = solist.nume;
    this->solistType = solist.solistType;
}
Solist & Solist::operator=(const Solist &solist) {
    this->nume = solist.nume;
    this->solistType = solist.solistType;
    return *this;
}

string Solist::getSolistType() const {
    return solistType;
}

void Solist::setSolistType(string type) {
    solistType = type;
}

bool Solist::operator==(const Solist &solist) const {
    return nume == solist.nume &&
           solistType == solist.solistType;
}

bool Solist::operator!=(const Solist &solist) const {
    return !(solist == *this);
}

//--------------------------------------------------------------------------------------------------------------------------

class Spectacol{

protected:
    int durataTotala;
    string numeSpectacol;
    int nrActe;
    string genSpectacol;
    double pretBilet;

public:
    const int get_durataTotala();
    const string get_numeSpectacol();
    const int get_nrActe();
    const double get_pretBilet();
    const string get_genSpetacol();

    void set_durataTotala(int durata);
    void set_numeSpectacol(string nume);
    void set_nrActe(int numar);
    void set_pretBilet(double pret);
    void set_genSpectacol(string gen);

    Spectacol();
    Spectacol(const Spectacol& spectacol);
    Spectacol(int durata, const string& denumire, int nrActe, const string& gen, double pret);
    virtual ~Spectacol();
    Spectacol& operator=(const Spectacol& spectacol);

    friend istream& operator>>(istream& is, Spectacol& spectacol);
    friend ostream& operator<<(ostream& os, Spectacol& spectacol);

    virtual istream& readSpectacol(istream& is) = 0;
    virtual ostream& printSpectacol(ostream& os) = 0;




    bool operator==(const Spectacol &spectacol) const;
    bool operator!=(const Spectacol &spectacol) const;

};

istream& operator>>(istream& is, Spectacol& spectacol){
    return spectacol.readSpectacol(is);
}
ostream& operator<<(ostream& os, Spectacol& spectacol){
    return spectacol.printSpectacol(os);
}

const double Spectacol::get_pretBilet() {
    return pretBilet;
}
const string Spectacol::get_genSpetacol() {
    return genSpectacol;
}
const int Spectacol::get_durataTotala() {
    return durataTotala;
}
const int Spectacol::get_nrActe() {
    return nrActe;
}
const string Spectacol::get_numeSpectacol() {
    return numeSpectacol;
}
void Spectacol::set_genSpectacol(string gen) {
    genSpectacol = gen;
}
void Spectacol::set_pretBilet(double pret) {
    pretBilet = pret;
}
void Spectacol::set_durataTotala(int durata) {
    durataTotala = durata;
}
void Spectacol::set_nrActe(int numar) {
    nrActe = numar;
}
void Spectacol::set_numeSpectacol(string nume) {
    numeSpectacol = nume;
}

Spectacol::Spectacol() {
    durataTotala = 0;
    numeSpectacol = "";
    nrActe = 0;
    genSpectacol = "";
    pretBilet = 0.0;
}
Spectacol::Spectacol(const Spectacol &spectacol) {
    durataTotala = spectacol.durataTotala;
    numeSpectacol = spectacol.numeSpectacol;
    nrActe = spectacol.nrActe;
    genSpectacol = spectacol.genSpectacol;
    pretBilet = spectacol.pretBilet;

}
Spectacol::Spectacol(int durata, const string &denumire, int nrActe,const string& gen, double pret) {
    this->durataTotala = durata;
    this->numeSpectacol = denumire;
    this->nrActe = nrActe;
    this->genSpectacol = gen;
    this->pretBilet = pret;
}
Spectacol::~Spectacol() {
    durataTotala = 0;
    numeSpectacol = "";
    nrActe = 0;
    genSpectacol = "";
    pretBilet = 0.0;
}
Spectacol & Spectacol::operator=(const Spectacol &spectacol) {
    this->durataTotala = spectacol.durataTotala;
    this->numeSpectacol = spectacol.numeSpectacol;
    this->nrActe = spectacol.nrActe;
    this->genSpectacol = spectacol.genSpectacol;
    this->pretBilet = spectacol.pretBilet;
    return *this;
}

bool Spectacol::operator==(const Spectacol &spectacol) const {
    return durataTotala == spectacol.durataTotala &&
           numeSpectacol == spectacol.numeSpectacol &&
           nrActe == spectacol.nrActe && pretBilet == spectacol.pretBilet && genSpectacol == spectacol.genSpectacol;

}

bool Spectacol::operator!=(const Spectacol &spectacol) const {
    return !(spectacol == *this);
}


//--------------------------------------------------------------------------------------------------------------------------------


class SpectacolTeatru : public Spectacol{

private:
    bool interactiv;

public:

    const bool get_interactiv();
    void set_interactiv(bool ok);

    SpectacolTeatru():Spectacol(),interactiv(false){}
    SpectacolTeatru(const SpectacolTeatru& spectacolTeatru);
    SpectacolTeatru(int durataTotala, const string numeSpectacol,const string gen, double pret, bool interactiv):Spectacol(durataTotala,numeSpectacol, 1,gen,pret),interactiv(interactiv){}
    ~SpectacolTeatru();
    SpectacolTeatru& operator=(const SpectacolTeatru& spectacolTeatru);

    bool operator==(const SpectacolTeatru &spectacol) const;
    bool operator!=(const SpectacolTeatru &spectacol) const;

    istream& readSpectacol(istream& is);
    ostream& printSpectacol(ostream& os);

};

istream & SpectacolTeatru::readSpectacol(istream &is) {
    cout << "Introduceti denumirea spectacolului de teatru:\n";
    string nume;
    while(true){
        try{
            getline(is,nume);
            if(islower(nume[0]))
                throw "Prima litera trebuie sa fie mare!";
            else
                break;
        }
        catch (string s){
            cout << s << '\n';
        }

    }
    this->numeSpectacol = nume;
    cout << "Introduceti durata spectacolului de teatru:\n";
    try{
        is >> this->durataTotala;
        is.get();
        if(this->durataTotala < 0)
            throw "Nu exista durate negative!";
    }
    catch (string s){
        cout << s << '\n';
    }

    cout << "Introduceti genul spectacolului de teatru:\n";
    while(true){
        try{
            getline(is,nume);
            if(islower(nume[0]))
                throw "Prima litera trebuie sa fie mare!";
            else
                break;
        }
        catch (string s){
            cout << s << '\n';
        }

    }
    this->genSpectacol = nume;
    cout << "Introduceti pretul biletului:\n";
    try{
        is >> this->pretBilet;
        is.get();
        if(this->pretBilet < 0)
            throw "Nu exista preturi negative!";
    }
    catch (string s){
        cout << s << '\n';
    }
    this->nrActe = 1;
    cout << "Introduceti 1 daca spectacolul de teatru este interactiv, 0 altfel:\n";
    int in;
    while(true){
        try{

            is >> in;
            is.get();
            if(in!=1 && in!=0)
                throw "Trebuie introdus 1 sau 0!";
            else
                break;
        }
        catch (string s){
            cout << s << '\n';
        }
    }

    this->interactiv = in;
    return is;
}
ostream & SpectacolTeatru::printSpectacol(ostream &os) {
    os << "Denumirea spectacolului de teatru: " << numeSpectacol << '\n';
    os << "Durata spectacolului de teatru: " << durataTotala<< '\n';
    os << "Numarul de acte: " << nrActe << '\n';
    os << "Genul spectacolului de teatru: " << genSpectacol <<'\n';
    os << "Pretul biletului: " << pretBilet <<'\n';
    os << "Este spectacolul de teatru interactiv? " << interactiv<<'\n';
    os << '\n';
    return os;
}

const bool SpectacolTeatru::get_interactiv() {
    return interactiv;
}
void SpectacolTeatru::set_interactiv(bool ok) {
    interactiv = ok;
}


SpectacolTeatru::SpectacolTeatru(const SpectacolTeatru &spectacolTeatru): Spectacol(spectacolTeatru) {
    this->interactiv = spectacolTeatru.interactiv;
}
SpectacolTeatru::~SpectacolTeatru(){
    interactiv = "";
}
SpectacolTeatru & SpectacolTeatru::operator=(const SpectacolTeatru &spectacolTeatru) {
    Spectacol::operator=(spectacolTeatru);
    this->interactiv = spectacolTeatru.interactiv;
    return *this;
}

bool SpectacolTeatru::operator==(const SpectacolTeatru &spectacol) const {
    return spectacol.numeSpectacol == numeSpectacol && spectacol.pretBilet == pretBilet && spectacol.nrActe == nrActe  && spectacol.genSpectacol == genSpectacol
           && interactiv == spectacol.interactiv && spectacol.durataTotala == durataTotala;
}

bool SpectacolTeatru::operator!=(const SpectacolTeatru &spectacol) const {
    return !(spectacol == *this);
}


//-------------------------------------------------------------------------------------------------------------------------------------------

class SpectacolOpera : public Spectacol {

private:
    Solist solist;
    vector<int> durataActe;
    int durataPauza;

public:

    SpectacolOpera();
    SpectacolOpera(const SpectacolOpera& spectacolOpera);
    SpectacolOpera(const string& denumire, int nrActe, const string& gen, double pret, Solist solist, vector<int>durataActe, int durataPauza);
    ~SpectacolOpera();
    SpectacolOpera& operator=(const SpectacolOpera& spectacolOpera);

    bool operator==(const SpectacolOpera &spectacol) const;

    bool operator!=(const SpectacolOpera &spectacol) const;

    istream& readSpectacol(istream& is);
    ostream& printSpectacol(ostream& os);
};

SpectacolOpera::SpectacolOpera():Spectacol() {
    Solist s;
    solist = s;
    durataPauza = 0;
}
SpectacolOpera::SpectacolOpera(const SpectacolOpera &spectacolOpera):Spectacol(spectacolOpera) {
    this->solist = spectacolOpera.solist;
    this->durataActe = spectacolOpera.durataActe;
    this->durataPauza = spectacolOpera.durataPauza;
}
SpectacolOpera::SpectacolOpera(const string &denumire, int nrActe,const string& gen, double pret, Solist solist, vector<int> durataActe, int durataPauza):Spectacol(0,denumire,nrActe,gen,pret) {
    int durataTot = durataPauza;
    for(int i = 0; i < durataActe.size(); ++i)
        durataTot += durataActe[i];
    this->durataTotala = durataTot;
    this->solist = solist;
    this->durataActe = durataActe;
    this->durataPauza = durataPauza;
}
SpectacolOpera::~SpectacolOpera() {
    durataPauza = 0;
}
SpectacolOpera & SpectacolOpera::operator=(const SpectacolOpera &spectacolOpera) {
    Spectacol::operator=(spectacolOpera);
    this->solist = spectacolOpera.solist;
    this->durataActe = spectacolOpera.durataActe;
    this->durataPauza = spectacolOpera.durataPauza;
    this->genSpectacol = spectacolOpera.genSpectacol;
    this->pretBilet = spectacolOpera.pretBilet;
    return *this;
}

istream & SpectacolOpera::readSpectacol(istream &is) {
    cout << "Introduceti denumirea spectacolului de opera:\n";
    string nume;
    while(true){
        try{
            getline(is,nume);
            if(islower(nume[0]))
                throw "Prima litera trebuie sa fie mare!";
            else
                break;
        }
        catch (string s){
            cout << s << '\n';
        }

    }
    this->numeSpectacol = nume;

    cout << "Introduceti solistul: \n";
    is >> solist;
    cout << "Introduceti genul spectacolului de opera:\n";
    while(true){
        try{
            getline(is,nume);
            if(islower(nume[0]))
                throw "Prima litera trebuie sa fie mare!";
            else
                break;
        }
        catch (string s){
            cout << s << '\n';
        }

    }

    this->genSpectacol = nume;
    cout << "Introduceti pretul biletului:\n";
    try{
        is >> this->pretBilet;
        is.get();
        if(this->pretBilet < 0)
            throw "Nu exista preturi negative!";
    }
    catch (string s){
        cout << s << '\n';
    }
    cout << "Introduceti numarul de acte:\n";
    try{
        is >> this->nrActe;
        is.get();
        if(this->nrActe<0)
            throw "Nu exista numar neagtiv de acte!";
        else
        if(this->nrActe<2 || this->nrActe>7)
            throw "Numarul de acte nu este corespunzator!";
    }
    catch (string s){
        cout << s << '\n';
    }
    int durataTot = 0;
    cout << "Introduceti duratele actelor:\n";
    for(int i=0; i<this->nrActe ;++i){
        cout <<"Introduceti Durata Actului " << i+1 << ":\n";
        int durata;
        try{
            is >> durata;
            is.get();
            if(durata<0)
                throw "Nu exista durate negative!";
        }
        catch (string s){
            cout << s << '\n';
        }
        durataTot +=  durata;
        durataActe.push_back(durata);
    }
    cout << "Introduceti durata Pauzei:\n";
    try{
        is >> durataPauza;
        is.get();
        if(durataPauza<0)
            throw "Nu exista durate negative!";
    }
    catch (string s){
        cout << s << '\n';
    }
    durataTot += durataPauza;
    durataTotala = durataTot;
    return is;
}
ostream & SpectacolOpera::printSpectacol(ostream &os) {
    os << "Denumirea spectacolului de opera: " << numeSpectacol << '\n';
    os << solist;
    os << "Genul spectacolului de opera: " << genSpectacol <<'\n';
    os << "Pretul biletului: " << pretBilet <<'\n';
    os << "Durata spectacolului de opera: " << durataTotala<< '\n';
    os << "Numarul de acte: " << nrActe << '\n';
    for(int i = 0; i < nrActe; ++i){
        cout <<"Durata Actului " << i+1 << " : " << durataActe[i] << '\n';
    }
    os << "Durata Pauzei : " << durataPauza << '\n';
    os << '\n';
    return os;
}

bool SpectacolOpera::operator==(const SpectacolOpera &spectacol) const {
    return spectacol.numeSpectacol == numeSpectacol && spectacol.pretBilet == pretBilet && spectacol.nrActe == nrActe  && spectacol.genSpectacol == genSpectacol
           && spectacol.durataTotala == durataTotala &&
           solist == spectacol.solist &&
           durataActe == spectacol.durataActe &&
           durataPauza == spectacol.durataPauza;
}

bool SpectacolOpera::operator!=(const SpectacolOpera &spectacol) const {
    return !(spectacol == *this);
}

//--------------------------------------------------------------------------------------------------------

class SpectacolStandup : public Spectacol{

private:
    string numeHeadliner;

public:

    string get_numeHeadliner();
    void set_numeHeadliner(const string& nume);

    SpectacolStandup();
    SpectacolStandup(const SpectacolStandup& spectacolStandup);
    SpectacolStandup(int durata, const string& denumire, const string& gen, double pret, const string& nume);
    ~SpectacolStandup();
    SpectacolStandup& operator=(const SpectacolStandup& spectacolStandup);

    bool operator==(const SpectacolStandup &spectacol) const;

    bool operator!=(const SpectacolStandup &spectacol) const;

    istream& readSpectacol(istream& is);
    ostream& printSpectacol(ostream& os);

};

string SpectacolStandup::get_numeHeadliner() {
    return numeHeadliner;
}
void SpectacolStandup::set_numeHeadliner(const string& nume) {
    numeHeadliner = nume;
}

SpectacolStandup::SpectacolStandup():Spectacol() {
    numeHeadliner = "";
}
SpectacolStandup::SpectacolStandup(const SpectacolStandup& spectacolStandup) : Spectacol(spectacolStandup){
    numeHeadliner = spectacolStandup.numeHeadliner;
}
SpectacolStandup::SpectacolStandup(int durata, const string &denumire, const string& gen, double pret, const string &nume) :Spectacol(durata,denumire,1,gen,pret),numeHeadliner(nume){}
SpectacolStandup::~SpectacolStandup() {
    numeHeadliner = "";
}
SpectacolStandup & SpectacolStandup::operator=(const SpectacolStandup &spectacolStandup) {
    Spectacol::operator=(spectacolStandup);
    this->numeHeadliner = spectacolStandup.numeHeadliner;
    return *this;
}

istream & SpectacolStandup::readSpectacol(istream &is) {
    cout << "Introduceti denumirea spectacolului de standup:\n";
    string nume;
    while(true){
        try{
            getline(is,nume);
            if(islower(nume[0]))
                throw "Prima litera trebuie sa fie mare!";
            else
                break;
        }
        catch (string s){
            cout << s << '\n';
        }

    }
    this->numeSpectacol = nume;
    this->nrActe = 1;
    cout << "Introduceti durata spectacolului:\n";
    try{
        is >> this->durataTotala;
        is.get();
        if(this->durataTotala < 0)
            throw "Nu exista durate negative!";
    }
    catch (string s){
        cout << s << '\n';
    }
    cout << "Introduceti pretul biletului:\n";
    try{
        is >> this->pretBilet;
        is.get();
        if(this->pretBilet < 0)
            throw "Nu exista preturi negative!";
    }
    catch (string s){
        cout << s << '\n';
    }
    this->genSpectacol = "Comedie";
    cout << "Introduceti numele Headliner-ului:\n";
    while(true){
        try{
            getline(is,nume);
            if(islower(nume[0]))
                throw "Prima litera trebuie sa fie mare!";
            else
                break;
        }
        catch (string s){
            cout << s << '\n';
        }

    }
    this->numeHeadliner = nume;
    return is;
}
ostream & SpectacolStandup::printSpectacol(ostream &os) {
    os << "Denumirea spectacolului de standup: " << numeSpectacol << '\n';
    os << "Durata spectacolului de standup: " << durataTotala<< '\n';
    os << "Pretul biletului: " << pretBilet <<'\n';
    os << "Numarul de acte: " << nrActe << '\n';
    os << "Numele Headliner-ului : " << numeHeadliner << '\n';
    os << '\n';
    return os;
}

bool SpectacolStandup::operator==(const SpectacolStandup &spectacol) const {
    return  spectacol.numeSpectacol == numeSpectacol && spectacol.pretBilet == pretBilet && spectacol.nrActe == nrActe  && spectacol.genSpectacol == genSpectacol
            && spectacol.durataTotala == durataTotala &&
            numeHeadliner == spectacol.numeHeadliner;
}

bool SpectacolStandup::operator!=(const SpectacolStandup &spectacol) const {
    return !(spectacol == *this);
}

//----------------------------------------------------------------------

class Factory{
public:
    Spectacol* CreateSpectacol(string SpectacolType) {
        if(SpectacolType == "Teatru")
            return new SpectacolTeatru();
        else if (SpectacolType == "Opera")
            return new SpectacolOpera();
        else if(SpectacolType == "Standup")
            return new SpectacolStandup();
        else return nullptr;
    }
};

//--------------------------------------------------------------------------------------------------------------------------------------


template <typename T>
class GestionareRezervariSpectacole{

private:
    int nr;
    static int idRezervare;
    unordered_map <int, pair<T*, int>> myMap;
    vector <pair<T,int>> spectacole;
public:
    int getNr() const;

    void setNr(int nr);

    static int getIdRezervare();

    static void setIdRezervare(int idRezervare);

    const unordered_map<int, pair<T *, int>> &getMyMap() const;

    void setMyMap(const unordered_map<int, pair<T *, int>> &myMap);

    const vector<pair<T, int>> &getSpectacole() const;

    void setSpectacole(const vector<pair<T, int>> &spectacole);

    GestionareRezervariSpectacole();

    GestionareRezervariSpectacole(const GestionareRezervariSpectacole& obiect);

    GestionareRezervariSpectacole(int nr, const unordered_map<int, pair<T *, int>> &myMap,
                                  const vector<pair<T, int>> &spectacole);

    ~GestionareRezervariSpectacole();
    GestionareRezervariSpectacole& operator=(const GestionareRezervariSpectacole& obiect);

    void eliminaRezervare( int index){
        int nrRezervare = 0;
        try{
            if(myMap.size()==0)
                throw "Nu exista rezervari!";
        }
        catch (string s){
            cout << s << '\n';
        }
        for (auto it = myMap.begin();it!=myMap.end();++it) {
            if(nrRezervare == index){
                if(SpectacolTeatru *teatru = dynamic_cast<SpectacolTeatru *>(it->second.first)) {
                    int number = it->second.second;
                    for (auto itt = spectacole.begin();itt!=spectacole.end();++itt){
                        SpectacolTeatru *tea = dynamic_cast<SpectacolTeatru*>(&itt->first);
                            if(*tea == *teatru){
                                itt->second += number;
                                myMap.erase(it);
                                cout << "A fost eliminat cu succes!\n";
                                break;
                            }


                    }
                }
                else{
                    if(SpectacolOpera *opera = dynamic_cast<SpectacolOpera *>(it->second.first)) {
                        int number = it->second.second;
                        for (auto itt = spectacole.begin();itt!=spectacole.end();++itt){
                            SpectacolOpera *op = dynamic_cast<SpectacolOpera*>(&itt->first);
                                if(*op == *opera){
                                    itt->second += number;
                                    myMap.erase(it);
                                    cout << "A fost eliminat cu succes!\n";
                                    break;;
                                }


                        }
                    }
                    else
                    if (SpectacolStandup *standup = dynamic_cast<SpectacolStandup *>(it->second.first)) {
                        int number = it->second.second;
                        for (auto itt = spectacole.begin(); itt != spectacole.end(); ++itt) {
                            SpectacolStandup *sta = dynamic_cast<SpectacolStandup *>(&itt->first);
                            if (*sta == *standup) {
                                itt->second += number;
                                myMap.erase(it);
                                cout << "A fost eliminat cu succes!\n";
                                break;
                            }


                        }
                    }
                }
                break;
            }

            ++ nrRezervare;
        }
    }



    void adaugaRezervare(T* spect, int nrLocuri){
        bool ok = false;
        int i = 0;
        for( i = 0; i < spectacole.size() && ok == false; ++i)
            if(*spect == spectacole[i].first)
            {
                ok = true;
                try{
                    if(spectacole[i].second < nrLocuri)
                        throw string("Nu mai sunt suficiente locuri!");
                    else{
                        myMap[idRezervare] = make_pair(spect, nrLocuri);
                        spectacole[i].second-=nrLocuri;
                        idRezervare++;
                    }
                }
                catch (string s){
                    cout << s << '\n';
                }
                break;
            }

        if( ok == false) {

            cout << "Numarul de locuri este:\n";
            int number;
            try{
                cin >> number;
                if(number < 0)
                    throw "Nu poti rezerva un numar negativ de locuri!";
            }
            catch (string s){
                cout << s << '\n';
            }

            cin.get();
            spectacole.push_back(make_pair(*spect, number));
            try{
                if (number < nrLocuri)
                    throw string("Nu mai sunt suficiente locuri!");
                else {
                    myMap[idRezervare] = make_pair(spect, nrLocuri);
                    spectacole[i].second -= nrLocuri;
                    idRezervare++;
                }
            }
            catch (string s){
                cout << s << '\n';
            }

        }

    }
    template<typename U>
    friend ostream& operator<<(ostream& os, GestionareRezervariSpectacole<U> &obiect);

    template<typename U>
    friend istream& operator>>(istream& is, GestionareRezervariSpectacole<U> &obiect);

};
template <class T>
GestionareRezervariSpectacole<T>::GestionareRezervariSpectacole() :nr(0),myMap(),spectacole(){
}
template <class T>
GestionareRezervariSpectacole<T>::GestionareRezervariSpectacole(const GestionareRezervariSpectacole<T> &obiect) : myMap(obiect.myMap), spectacole(obiect.spectacole){
    this->nr = obiect.nr;
}
template <class T>
GestionareRezervariSpectacole<T> & GestionareRezervariSpectacole<T>::operator=(
        const GestionareRezervariSpectacole<T> &obiect) {
    this->nr = obiect.nr;
    for (auto &pair : myMap){
        delete pair.second.first;
        pair.second.first = nullptr;
    }
    this->myMap.clear();
    this->myMap.template insert(obiect.myMap.begin(),obiect.myMap.end());
    this->spectacole.clear();
    this->spectacole.insert(obiect.spectacole.begin(),obiect.spectacole.end());
    return *this;
}
template <class T>
GestionareRezervariSpectacole<T>::~GestionareRezervariSpectacole<T>() {
    nr = 0;
    for (auto &pair : myMap){
        delete pair.second.first;
        pair.second.first = nullptr;
    }
    myMap.clear();
    this->spectacole.clear();
}

template <typename T>
int GestionareRezervariSpectacole<T>::idRezervare = 0;


template<typename U>
ostream& operator<<(ostream& os, GestionareRezervariSpectacole<U> &obiect){

    if(GestionareRezervariSpectacole<U>::idRezervare == 0)
        os << "Nu s-au facut rezervari\n";
    else{

        int nrRezervareTeatru = 0;


        int nrSpectacol = 0 ;
        for (auto it = obiect.spectacole.begin();it!=obiect.spectacole.end();++it){
                if (nrSpectacol == 0){
                    os << "\n~~~~~~~~~~~~~~~~~~~~Spectacolele introduse sunt:~~~~~~~~~~~~~~~~~~~~~~\n";
                }

                os << "Spectacolul " << nrSpectacol << " mai are " << it->second << " locuri\n";
                ++nrSpectacol;

        }
        int nrRezervareOpera = 0;

        for (auto it = obiect.myMap.begin();it!=obiect.myMap.end();++it) {
            if (SpectacolTeatru *teatru = dynamic_cast<SpectacolTeatru *>(it->second.first)) {
                os << "~~~~~~~Rezervarea " << nrRezervareTeatru << "~~~~~~~~~\n";
                os << *teatru << '\n';
                os << "Numarul de locuri rezervate: " << it->second.second << '\n';
                cout << '\n';
                ++nrRezervareTeatru;
            }
            else
            if(SpectacolOpera *opera = dynamic_cast<SpectacolOpera*>(it->second.first)){
                os << "~~~~~~~Rezervarea " << nrRezervareOpera << "~~~~~~~~~\n";
                os << *opera <<'\n';
                os << "Numarul de locuri rezervate: " << it->second.second << '\n';
                cout << '\n';
                ++nrRezervareOpera;
            }
        }
        os << "\n----------------------------------------------------------------------------------------\n";


        os << "\n----------------------------------------------------------------------------------------\n";
    }


    return os;
}

template<typename U>
istream& operator>>(istream& is, GestionareRezervariSpectacole<U> &obiect){
    cout << "Introduceti numarul de rezervari:\n";
    int number;
    try{

        is >> number;
        is.get();
        if(number < 0)
            throw "Nu poti face un nr negativ de rezervari!";
        else
            obiect.nr += number;
    }
    catch (string s){
        cout << s << '\n';
    }
    int nrRez = number;
    cout << "Introduceti datele rezervarilor:\n";
    for(int i = 0; i<nrRez; ++i){
        cout << "Introduceti Spectacolul:\n";
        U *ob = new U;
        cin >> *ob;
        cout << "Introduceti nr de locuri rezervate:\n";
        int number;
        try{
            is >> number;
            is.get();
            if(number < 0)
                throw "Nu poti rezerva un numar negativ de locuri!";
        }
        catch (string s){
            cout << s << '\n';
        }
        obiect.adaugaRezervare(ob, number);
        cout <<'\n';
    }

    return is;
}

//------------------------------------------------------------------------------------------------------------

template<> class GestionareRezervariSpectacole<SpectacolStandup>{
private:
    int nr;
    static int idRezervare;
    unordered_map <int, pair<SpectacolStandup*, int>> myMap;
    vector <pair<SpectacolStandup,int>> spectacole;

public:
    int getNr() const;
    void setNr(int nr);

    static int getIdRezervare();
    static void setIdRezervare(int idRezervare);

    const unordered_map<int, pair<SpectacolStandup *, int>> &getMyMap() const;
    void setMyMap(const unordered_map<int, pair<SpectacolStandup *, int>> &myMap);

    const vector<pair<SpectacolStandup, int>> &getSpectacole() const;
    void setSpectacole(const vector<pair<SpectacolStandup, int>> &spectacole);

    GestionareRezervariSpectacole();
    GestionareRezervariSpectacole(int nr,unordered_map<int,pair<SpectacolStandup*,int>> myMap, vector<pair<SpectacolStandup,int>> spectacole );
    GestionareRezervariSpectacole(const GestionareRezervariSpectacole<SpectacolStandup> &obiect);
    ~GestionareRezervariSpectacole();
    GestionareRezervariSpectacole& operator=(const GestionareRezervariSpectacole<SpectacolStandup> &obiect);

    void eliminaRezervare(int index){
        try{
            if(myMap.size()==0)
                throw "Nu exista rezervari!";
        }
        catch (string s){
            cout << s << '\n';
        }
        try{
            if(index < 0 || index>=myMap.size())
                throw "Index invalid!";
        }
        catch (string s){
            cout << s << '\n';
        }
        int nrRezervare = 0;
        for (auto it = myMap.begin();it!=myMap.end();++it) {
            if (nrRezervare == index) {
                if (SpectacolStandup *standup = dynamic_cast<SpectacolStandup *>(it->second.first)) {
                    int number = it->second.second;
                    for (auto itt = spectacole.begin(); itt != spectacole.end(); ++itt) {
                        SpectacolStandup *sta = dynamic_cast<SpectacolStandup *>(&itt->first);
                        if (*sta == *standup) {
                            itt->second += number;
                            myMap.erase(it);
                            cout << "A fost eliminat cu succes!\n";
                            break;
                        }


                    }
                }
                break;
            }
            ++ nrRezervare;
        }

    }

    void adaugaRezervare(SpectacolStandup* spect, int nrLocuri){
        bool ok = false;
        int i = 0;
        for( i = 0; i < spectacole.size() && ok == false; ++i)
            if(*spect == spectacole[i].first)
            {
                ok = true;
                try{
                    if(spectacole[i].second < nrLocuri)
                        cout<< "Nu mai sunt suficiente locuri!\n";
                    else{
                        myMap[idRezervare] = make_pair(spect, nrLocuri);
                        spectacole[i].second-=nrLocuri;
                        idRezervare++;
                    }
                }
                catch (string s){
                    cout << s << '\n';
                }
                break;
            }

        if( ok == false) {

            cout << "Numarul de locuri este:\n";
            int number;
            try{
                cin >> number;
                if(number<0)
                    throw "Nu poti rezolva un numar negativ de locuri!";
            }
            catch (string s){
                cout << s << '\n';
            }

            cin.get();
            spectacole.push_back(make_pair(*spect, number));
            try{
                if (number < nrLocuri)
                    throw string("Nu mai sunt suficiente locuri!");
                else {
                    myMap[idRezervare] = make_pair(spect, nrLocuri);
                    spectacole[i].second -= nrLocuri;
                    idRezervare++;
                }
            }
            catch (string s){
                cout << s << '\n';
            }

        }

    }

    double venituri(){
        double sum = 0;
        for (auto it = myMap.begin(); it != myMap.end(); ++it) {
//            if (SpectacolStandup *standup = dynamic_cast<SpectacolStandup *>(it->second.first)) {
                sum += it->second.second * it->second.first->get_pretBilet();
           // }
        }
        return sum;
    }
    friend ostream& operator<<(ostream& os, GestionareRezervariSpectacole<SpectacolStandup> &obiect);
    friend istream& operator>>(istream& is, GestionareRezervariSpectacole<SpectacolStandup> &obiect);

};
istream& operator>>(istream& is, GestionareRezervariSpectacole<SpectacolStandup> &obiect){
    cout << "Introduceti numarul de rezervari:\n";
    int number;
    try{

        is >> number;
        is.get();
        if(number < 0)
            throw "Nu poti face un nr negativ de rezervari!";
        else
            obiect.nr += number;
    }
    catch (string s){
        cout << s << '\n';
    }
    int nrRez = number;
    cout << "Introduceti datele rezervarilor:\n";
    for(int i = 0; i<nrRez; ++i){
        cout << "Introduceti Spectacolul:\n";
        Spectacol *ob = new SpectacolStandup;
        cin >> *ob;
        cout << "Introduceti nr de locuri rezervate:\n";
        int number;
        try{
            is >> number;
            is.get();
            if(number < 0)
                throw "Nu poti rezerva un numar negativ de locuri!";
        }
        catch (string s){
            cout << s << '\n';
        }

        obiect.adaugaRezervare(dynamic_cast<SpectacolStandup *>(ob), number);
        cout <<'\n';
    }
    return is;
}
ostream& operator<<(ostream& os, GestionareRezervariSpectacole<SpectacolStandup> &obiect) {
    if (GestionareRezervariSpectacole<SpectacolStandup>::idRezervare == 0)
        os << "Nu s-au facut rezervari\n";
    else {
        int nrRezervareStandUp = 0;



        cout << "\n~~~~~~~~~~~~~~~~~~~~Spectacolele introduse sunt:~~~~~~~~~~~~~~~~~~~~~~\n";
        int nrSpectacol = 0;

        for (auto it = obiect.spectacole.begin();it!=obiect.spectacole.end();++it){{
                os << "Spectacolul " << nrSpectacol << " mai are " << it->second << " locuri\n";
                ++nrSpectacol;
            }
        }


        for (auto it = obiect.myMap.begin();it!=obiect.myMap.end();++it) {
//            if (SpectacolStandup *standup = dynamic_cast<SpectacolStandup *>(it->second.first)) {
                os << "~~~~~~~Rezervarea " << nrRezervareStandUp << "~~~~~~~~~\n";
                os << *it->second.first << '\n';
                os << "Numarul de locuri rezervate: " << it->second.second << '\n';
                cout << '\n';
                ++nrRezervareStandUp;
           // }
        }
        if (nrRezervareStandUp == 0)
            os << "Nu s-au facut rezervari de acest fel\n";

        os << "\n----------------------------------------------------------------------------------------\n";


    }
    return os;
}
GestionareRezervariSpectacole<SpectacolStandup>::GestionareRezervariSpectacole():nr(0),myMap(),spectacole() {
}
GestionareRezervariSpectacole<SpectacolStandup>::GestionareRezervariSpectacole(int nr,
                                                                               unordered_map<int, pair<SpectacolStandup *, int>> myMap,
                                                                               vector<pair<SpectacolStandup , int>> spectacole):nr(nr),myMap(myMap),spectacole(spectacole) {

}
GestionareRezervariSpectacole<SpectacolStandup>::GestionareRezervariSpectacole(
        const GestionareRezervariSpectacole<SpectacolStandup> &obiect) : myMap(obiect.myMap), spectacole(obiect.spectacole){
    this->nr = obiect.nr;
}
GestionareRezervariSpectacole<SpectacolStandup>::~GestionareRezervariSpectacole() {
    this->nr = 0;
    for (auto &pair : myMap){
        delete pair.second.first;
        pair.second.first = nullptr;
    }
    this->myMap.clear();
    this->spectacole.clear();
}
int GestionareRezervariSpectacole<SpectacolStandup>::idRezervare = 0;

int GestionareRezervariSpectacole<SpectacolStandup>::getNr() const {
    return nr;
}

void GestionareRezervariSpectacole<SpectacolStandup>::setNr(int nr) {
    GestionareRezervariSpectacole::nr = nr;
}

int GestionareRezervariSpectacole<SpectacolStandup>::getIdRezervare() {
    return idRezervare;
}

void GestionareRezervariSpectacole<SpectacolStandup>::setIdRezervare(int idRezervare) {
    GestionareRezervariSpectacole::idRezervare = idRezervare;
}

const unordered_map<int, pair<SpectacolStandup *, int>> &
GestionareRezervariSpectacole<SpectacolStandup>::getMyMap() const {
    return myMap;
}

void GestionareRezervariSpectacole<SpectacolStandup>::setMyMap(
        const unordered_map<int, pair<SpectacolStandup *, int>> &myMap) {
    GestionareRezervariSpectacole::myMap = myMap;
}

const vector<pair<SpectacolStandup, int>> &GestionareRezervariSpectacole<SpectacolStandup>::getSpectacole() const {
    return spectacole;
}

void
GestionareRezervariSpectacole<SpectacolStandup>::setSpectacole(const vector<pair<SpectacolStandup, int>> &spectacole) {
    GestionareRezervariSpectacole::spectacole = spectacole;
}

template<typename T>
int GestionareRezervariSpectacole<T>::getNr() const {
    return nr;
}


//----------------------------------------------------------------------------------------------------------

class Singleton {
    static Singleton *instanta;

    Singleton() {}
    Singleton(const Singleton& ) = default;
    Singleton& operator=(const Singleton&) = default;

public:
    static Singleton *getInstanta() {
        if (instanta == NULL)
            instanta = new Singleton;
        return instanta;
    }
    static void delete_instata(){
        delete instanta;
        instanta = nullptr;
    }

    void citire(GestionareRezervariSpectacole<SpectacolTeatru> &teatru, GestionareRezervariSpectacole<SpectacolOpera> &opera,GestionareRezervariSpectacole<SpectacolStandup> &standup){
        cout << "Ati ales sa faceti rezervari\n\n";
        cout << "La ce fel de spectacole doriti sa rezervati?\n";
        cout << "1-teatru, 2-opera, 3-standup\n";

        try {
            int optiune;
            cout << "Dati numarul optiunii: ";
            cin >> optiune;
            cin.get();
            if (optiune <= 0 || optiune >= 4)
                throw "Nu ai ales corect!! mai alege o data ";
            if(optiune==1)
            {//teatru
                cin >> teatru;

            } else
            if(optiune==2)
            {
                //opera
                cin >> opera;

            } else
            if(optiune==3)
            {
                //standup
                cin >> standup;
            }

        }
        catch (string s) {
            cout << s << '\n';
        }
    }
    void afisareProfitStandup(GestionareRezervariSpectacole<SpectacolStandup> &standup){
        cout << "Profitul obtinut la spectacolele de standup este:\n";
        cout << standup.venituri();
        cout << '\n';
    }
    void afisare(GestionareRezervariSpectacole<SpectacolTeatru> &teatru, GestionareRezervariSpectacole<SpectacolOpera> &opera,GestionareRezervariSpectacole<SpectacolStandup> &standup) {
        cout << "Ati ales sa vedeti gestiunile\n";
        cout << "Ce gestiune doriti sa vedeti?\n";
        cout << '\n';
        cout << "1-Gestiunea pentru teatru\n";
        cout << "2-Gestiunea pentru opera\n";
        cout << "3-Gestiunea pentru standup\n";
        cout << "4-Toate cele 3 gestiuni\n\n";

        cout << "Introduceti optiunea:\n";
        int optiune;
        try{
            cin >> optiune;
            cin.get();
            if(optiune < 1 || optiune > 4 )
                throw "Nu ati ales optiune valida! Mai alegeti odata!";
            if(optiune == 1){
                cout << "Teatru:\n";
                cout << teatru;
            }
            else if(optiune == 2) {
                cout << "Opera:\n";
                cout << opera << '\n';
            }
            else if(optiune == 3) {
                cout << "StandUp:\n";
                cout << standup << '\n';
            }
            else if(optiune == 4){
                cout << "Teatru:\n";
                cout << teatru << '\n';
                cout << "Opera:\n";
                cout << opera << '\n';
                cout << "StandUp:\n";
                cout << standup << '\n';
            }
        }
        catch (string s){
            cout << s << '\n';
        }
    }

    void eliminTeatru(GestionareRezervariSpectacole<SpectacolTeatru> &teatru,  int index) {
        teatru.eliminaRezervare(index);
    }

    void eliminOpera(GestionareRezervariSpectacole<SpectacolOpera> &opera,  int index) {
        opera.eliminaRezervare(index);
    }

    void eliminStandup(GestionareRezervariSpectacole<SpectacolStandup> &standup,  int index) {
        standup.eliminaRezervare(index);
    }

    void op6() {

    }

    void op7() {

    }
};

Singleton * Singleton :: instanta;

int main() {
    Singleton *s;
    s->getInstanta();
    GestionareRezervariSpectacole<SpectacolStandup>standup;
    GestionareRezervariSpectacole<SpectacolOpera> opera ;
    GestionareRezervariSpectacole<SpectacolTeatru> teatru;
    while (true)
    {

        try {
            int optiune;
            cout << "Ce doriti sa faceti?\n";
            cout << "1-adaugare de un numar de rezevari\n";
            cout << "2-afisarea gestiunilor\n";
            cout << "3-afisarea veniturilor la standup\n";
            cout << "4-elimina o rezervare\n";
            cin >> optiune;
            cin.get();
            if (optiune <= 0 || optiune > 4)
                throw
                        "Nu ati ales corect! Mai alegeti o data! \n";
            else if(optiune==1)
            {
                s->citire(teatru,opera,standup);
            }
            else if(optiune == 2){
                s->afisare(teatru,opera,standup);
            }
            else if(optiune == 3){
                s->afisareProfitStandup(standup);
            }
            else if(optiune == 4){
                int index;
                cout << "Ati ales sa eliminati o rezervare!\n";
                cout << "Introduceti indicele rezervarii de eliminat:\n";

                try{
                    cin >> index;
                    if(index < 0)
                        throw "Nu exista indici negativi!";
                }
                catch (string s){
                    cout << s << '\n';
                }
                cin.get();
                cout << "La ce tip de spectacol doriti sa eliminati rezervarea?\n";
                cout << "1-teatru\n";
                cout << "2-opera\n";
                cout << "3-standup\n";
                try{
                    int tip;
                    cin >> tip;
                    cin.get();
                    if (tip < 1 || tip > 3)
                        throw string("Ati introdus un tip gresit de spectacol!\n");
                    if(tip == 1)
                        s->eliminTeatru(teatru,index);
                    else if(tip == 2)
                        s->eliminOpera(opera, index);
                    else if(tip == 3)
                        s->eliminStandup(standup,index);
                }
                catch (string s){
                    cout << s <<'\n';
                }
            }

        }
        catch (const char *s)
        {
            cout << s<<endl;

        }
        cout<<"Doriti sa continuati? (da/nu):\n ";
        string rasp;
        //cin.get();
        getline(cin,rasp);
        if(rasp=="nu")
            break;

    }
    s->delete_instata();

    return 0;
}
