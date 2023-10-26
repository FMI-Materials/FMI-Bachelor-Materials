// Broscoteanu Daria-Mihaela
// Grupa 143
// Rulat cu Clion
// g++.exe (x86_64-posix-seh-rev0, Built by MinGW-W64 project) 8.1.0
// C++ 20
// Tutore: Sumedrea Paul

#include <iostream>
#include <vector>
#include <string>

using namespace std;


//re.
//Prin malware înțelegem un software rău intenționat pentru care se reține ratingul
//impactului (număr real), data de infectare (zi, luna, an), numele acestuia (care poate să fie
//format din mai multe cuvinte), metoda de infectare (dacă se cunoaște, altfel se reține șirul
//“unknown”) și un vector cu registrii modificați (reținuți ca stringuri).
class Malware{
protected:
     double impact;
     int zi, luna, an;
     string denumire;
     string metoda_de_infectare;
     vector <string> registrii;


public:
    Malware();
    Malware(const Malware& ob);
    Malware& operator=(const Malware& ob);
    virtual ~Malware();
    Malware(double impact, int zi, int luna, int an, const string &denumire, const string &metodaDeInfectare,
            const vector<string> &registrii);

    double getImpact() const;
    void setImpact(double impact);

    int getZi() const;
    void setZi(int zi);

    int getLuna() const;
    void setLuna(int luna);

    int getAn() const;
    void setAn(int an);

    const string &getDenumire() const;
    void setDenumire(const string &denumire);

    const string &getMetodaDeInfectare() const;
    void setMetodaDeInfectare(const string &metodaDeInfectare);

    const vector<string> &getRegistrii() const;
    void setRegistrii(const vector<string> &registrii);

    friend istream& operator>>(istream& is, Malware& ob){
        return ob.readMalware(is);
    }
    friend ostream& operator<<(ostream& os, Malware& ob){
        return ob.printMalware(os);
    }

    virtual istream& readMalware(istream& is) = 0;
    virtual ostream& printMalware(ostream& os) = 0;
    virtual double calculeaza() = 0;
};
Malware::Malware():registrii() {
    impact = 0;
    zi = 0;
    luna = 0;
    an = 0;
    metoda_de_infectare = "";
    denumire = "";
}
Malware::Malware(const Malware &ob) {
    impact = ob.impact;
    zi = ob.zi;
    luna = ob.luna;
    an = ob.an;
    denumire = ob.denumire;
    metoda_de_infectare = ob.metoda_de_infectare;
    registrii = ob.registrii;
}
Malware & Malware::operator=(const Malware &ob) {
    impact = ob.impact;
    zi = ob.zi;
    luna = ob.luna;
    an = ob.an;
    denumire = ob.denumire;
    metoda_de_infectare = ob.metoda_de_infectare;
    registrii = ob.registrii;
    return *this;
}
Malware::~Malware() {
    impact = 0;
    zi = luna = an = 0;
    denumire.clear();
    metoda_de_infectare.clear();
    registrii.clear();
}

double Malware::getImpact() const {
    return impact;
}

void Malware::setImpact(double impact) {
    Malware::impact = impact;
}

int Malware::getZi() const {
    return zi;
}

void Malware::setZi(int zi) {
    Malware::zi = zi;
}

int Malware::getLuna() const {
    return luna;
}

void Malware::setLuna(int luna) {
    Malware::luna = luna;
}

int Malware::getAn() const {
    return an;
}

void Malware::setAn(int an) {
    Malware::an = an;
}

const string &Malware::getDenumire() const {
    return denumire;
}

void Malware::setDenumire(const string &denumire) {
    Malware::denumire = denumire;
}

const string &Malware::getMetodaDeInfectare() const {
    return metoda_de_infectare;
}

void Malware::setMetodaDeInfectare(const string &metodaDeInfectare) {
    metoda_de_infectare = metodaDeInfectare;
}

const vector<string> &Malware::getRegistrii() const {
    return registrii;
}

void Malware::setRegistrii(const vector<string> &registrii) {
    Malware::registrii = registrii;
}

Malware::Malware(double impact, int zi, int luna, int an, const string &denumire, const string &metodaDeInfectare,
                 const vector<string> &registrii) : impact(impact), zi(zi), luna(luna), an(an), denumire(denumire),
                                                    metoda_de_infectare(metodaDeInfectare), registrii(registrii) {}

//----------------------------------------------------------------------------------------------------------------------
//Prin rootkit înțelegem un tip de malware ce are drept scop obținerea drepturilor de
//administrator asupra dispozitivului infectat. Pentru rootkit se reține lista importurilor care
//poate fi unul și oricât de multe (importurile fac referire la numele fișierelor .dll folosite) și o
//listă de stringuri semnificative (anumite stringuri dintr-un binar pot fi un indice asupra faptului
//că fișierul este rău intenționat).

class Rootkit: virtual public Malware{
protected:
    vector <string> importuri;
    vector <string> semnificative;
public:
    const vector<string> &getImporturi() const;
    void setImporturi(const vector<string> &importuri);

    const vector<string> &getSemnificative() const;
    void setSemnificative(const vector<string> &semnificative);

    Rootkit();
    Rootkit(const Rootkit& ob);
    Rootkit& operator=(const Rootkit& ob);
    virtual ~Rootkit();
    Rootkit(double impact, int zi, int luna, int an, const string &denumire, const string &metodaDeInfectare,
            const vector<string> &registrii, const vector<string> &importuri, const vector<string> &semnificative);

    virtual istream& readMalware(istream& is);
    virtual ostream& printMalware(ostream& os);
    virtual double calculeaza();
};
//Pentru rootkit ratingul impactului crește cu 100 dacă se întâlnește unul din stringurile
//“System Service Descriptor Table”, “SSDT”, “NtCreateFile”. Dacă se regăsește importul
//“ntoskrnl.exe”, valoarea impactului se dublează (importurile se verifică după stringuri).
double Rootkit::calculeaza() {
    double val = impact;
    for(int i =0;i < registrii.size(); ++i)
        if(registrii[i] == "“HKLM-run" || registrii[i] == "HKCU-run"){
            val += 20;
            break;
        }

    for(int i = 0;i < semnificative.size(); ++i)
        if(semnificative[i] == "System Service Descriptor Table" || semnificative[i] == "SSDT" || semnificative[i] == "NtCreateFile" ){
            val += 100;
            break;
        }
    for(int i = 0;i < importuri.size(); ++i)
        if(importuri[i] == "ntoskrnl.exe"){
            val = val *2;
            break;
        }
    return val;
}
Rootkit::Rootkit():Malware(),  importuri(), semnificative(){

}
Rootkit::Rootkit(const Rootkit &ob) {
    impact = ob.impact;
    zi = ob.zi;
    luna = ob.luna;
    an = ob.an;
    denumire = ob.denumire;
    metoda_de_infectare = ob.metoda_de_infectare;
    registrii = ob.registrii;
    importuri = ob.importuri;
    semnificative = ob.semnificative;
}
Rootkit & Rootkit::operator=(const Rootkit &ob) {
    impact = ob.impact;
    zi = ob.zi;
    luna = ob.luna;
    an = ob.an;
    denumire = ob.denumire;
    metoda_de_infectare = ob.metoda_de_infectare;
    registrii = ob.registrii;
    importuri = ob.importuri;
    semnificative = ob.semnificative;
    return *this;
}
Rootkit::~Rootkit(){
    importuri.clear();
    semnificative.clear();
}

Rootkit::Rootkit(double impact, int zi, int luna, int an, const string &denumire, const string &metodaDeInfectare,
                 const vector<string> &registrii, const vector<string> &importuri, const vector<string> &semnificative)
        : Malware(impact, zi, luna, an, denumire, metodaDeInfectare, registrii), importuri(importuri),
          semnificative(semnificative) {}

const vector<string> &Rootkit::getImporturi() const {
    return importuri;
}

void Rootkit::setImporturi(const vector<string> &importuri) {
    Rootkit::importuri = importuri;
}

const vector<string> &Rootkit::getSemnificative() const {
    return semnificative;
}

void Rootkit::setSemnificative(const vector<string> &semnificative) {
    Rootkit::semnificative = semnificative;
}
istream & Rootkit::readMalware(istream &is) {
    cout << "Impact:\n";
    is >> impact;
    is.get();
    cout << "Data:\n";
    cout << "An:\n";
    bool bisect = 0;
    int zile[]={0,31,28,31,30,31,30,31,31,30,31,30,31};
    is >> an;
    is.get();
    if ((an % 4 == 0 && an % 100!=0) || an%400 == 0 )
        bisect = 1;
    cout << "Luna:\n";
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
    cout << "Ziua\n";
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
    cout << "Denumire:\n";
    getline(is, denumire);
    cout << "Metoda de infectare:\n";
    getline(is, metoda_de_infectare);
    int nr;

    while(true){
        try{

            cout << "Numar registrii:\n";
            is >> nr;
            is.get();
            if(nr < 0)
                throw string("Nr invalid!");
            else
                break;

        }
        catch (string s){
            cout << s << '\n';
        }
    }
    for(int i = 0;i < nr ; ++i){
        cout << "Registru:\n";
        string s;
        getline(is, s);
        registrii.push_back(s);
    }

    while(true){
        try{

            cout << "Numar importuri:\n";
            is >> nr;
            is.get();
            if(nr < 0)
                throw string("Nr invalid!");
            else
                break;

        }
        catch (string s){
            cout << s << '\n';
        }
    }
    for(int i = 0;i < nr ; ++i){
        cout << "Import:\n";
        string s;
        getline(is, s);
        importuri.push_back(s);
    }
    while(true){
        try{

            cout << "Numar semnificative:\n";
            is >> nr;
            is.get();
            if(nr < 0)
                throw string("Nr invalid!");
            else
                break;

        }
        catch (string s){
            cout << s << '\n';
        }
    }
    for(int i = 0;i < nr ; ++i){
        cout << "Semnificativ:\n";
        string s;
        getline(is, s);
        semnificative.push_back(s);
    }
    return is;

}
ostream & Rootkit::printMalware(ostream &os) {
    os << "Impact: " << impact << "\n";
    os << "Data: " << zi << '/' << luna << '/' << an << '\n';
    os << "Denumire: " << denumire << '\n';
    os << "Metoda de inf: " << metoda_de_infectare << '\n';
    os << "Registrii:\n";
    for(int i = 0;i < registrii.size() ; ++i){
        cout  << registrii[i] << '\n';
    }
    os  << "Importuri:\n";
    for(int i = 0;i < importuri.size() ; ++i){
        cout  << importuri[i] << '\n';
    }
    os << "Semnificative:\n";
    for(int i = 0;i < semnificative.size() ; ++i){
        os << semnificative[i] << '\n';
    }
    return os;
}
//----------------------------------------------------------------------------------------------------------------------
//șierul este rău intenționat).
//Prin keylogger înțelegem un malware care înregistrează acțiunile de la tastatură și le
//trimite mai departe. Pentru un keylogger se reține o listă cu funcțiile folosite și o listă cu
//tastele speciale definite.
class Keylogger: virtual public Malware{
protected:
    vector <string > functii;
    vector <string>  taste;

public:
    const vector<string> &getFunctii() const;
    void setFunctii(const vector<string> &functii);

    const vector<string> &getTaste() const;
    void setTaste(const vector<string> &taste);


    Keylogger() = default;
    Keylogger(double impact, int zi, int luna, int an, const string &denumire, const string &metodaDeInfectare,
              const vector<string> &registrii, const vector<string> &functii, const vector<string> &taste);

    Keylogger(const Keylogger& ob);
    Keylogger& operator=(const Keylogger& ob);
    virtual ~Keylogger();

    virtual istream& readMalware(istream& is);
    virtual ostream& printMalware(ostream& os);

    virtual double calculeaza();
};
//Pentru keylogger ratingul impactului crește cu 10 la întâlnirea stringurilor “[Up]”,
//“[Num Lock]”, “[Down]”, “[Right]”, “[UP]”, “[Left]”, “[PageDown]” și cu 30 la întâlnirea unei din
//funcțiile: “CreateFileW”, “OpenProcess”, “ReadFile”, “WriteFile”, “RegisterHotKey”,
//“SetWindowsHookEx”
double Keylogger::calculeaza() {
    double val = impact;
    for(int i =0;i < registrii.size(); ++i)
        if(registrii[i] == "“HKLM-run" || registrii[i] == "HKCU-run"){
            val += 20;
            break;
        }
    for(int i = 0;i < functii.size(); ++i)
        if(functii[i] == "CreateFileW" || functii[i] == "OpenProcess" || functii[i] == "ReadFile" || functii[i] =="WriteFile" || functii[i] == "RegisterHotKey"  || functii[i] == "SetWindowsHookEx" )
            val += 30;
    for(int i = 0;i < taste.size(); ++i)
        if(taste[i] == "Up" || taste[i] == "Num Lock" || taste[i] == "Down" || taste[i] =="Right" || taste[i] == "UP"  || taste[i] == "Left" || taste[i] == "PageDown" )
            val += 10;
    return val;
}
istream & Keylogger::readMalware(istream &is) {
    cout << "Impact:\n";
    is >> impact;
    is.get();
    cout << "Data:\n";
    cout << "An:\n";
    bool bisect = 0;
    int zile[]={0,31,28,31,30,31,30,31,31,30,31,30,31};
    is >> an;
    is.get();
    if ((an % 4 == 0 && an % 100!=0) || an%400 == 0 )
        bisect = 1;
    cout << "Luna:\n";
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
    cout << "Ziua\n";
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
    cout << "Denumire:\n";
    getline(is, denumire);
    cout << "Metoda de infectare:\n";
    getline(is, metoda_de_infectare);
    int nr;

    while(true){
        try{

            cout << "Numar registrii:\n";
            is >> nr;
            is.get();
            if(nr < 0)
                throw string("Nr invalid!");
            else
                break;

        }
        catch (string s){
            cout << s << '\n';
        }
    }
    for(int i = 0;i < nr ; ++i){
        cout << "Registru:\n";
        string s;
        getline(is, s);
        registrii.push_back(s);
    }

    while(true){
        try{

            cout << "Numar Functii:\n";
            is >> nr;
            is.get();
            if(nr < 0)
                throw string("Nr invalid!");
            else
                break;

        }
        catch (string s){
            cout << s << '\n';
        }
    }
    for(int i = 0;i < nr ; ++i){
        cout << "Import:\n";
        string s;
        getline(is, s);
        functii.push_back(s);
    }
    while(true){
        try{

            cout << "Numar taste:\n";
            is >> nr;
            is.get();
            if(nr < 0)
                throw string("Nr invalid!");
            else
                break;

        }
        catch (string s){
            cout << s << '\n';
        }
    }
    for(int i = 0;i < nr ; ++i){
        cout << "Taste:\n";
        string s;
        getline(is, s);
        taste.push_back(s);
    }
    return is;

}

ostream & Keylogger::printMalware(ostream &os) {
    os << "Impact: " << impact << "\n";
    os << "Data: " << zi << '/' << luna << '/' << an << '\n';
    os << "Denumire: " << denumire << '\n';
    os << "Metoda de inf: " << metoda_de_infectare << '\n';
    os << "Registrii:\n";
    for(int i = 0;i < registrii.size() ; ++i){
        cout  << registrii[i] << '\n';
    }
    os  << "Functii:\n";
    for(int i = 0;i < functii.size() ; ++i){
        cout  << functii[i] << '\n';
    }
    os << "Taste:\n";
    for(int i = 0;i < taste.size() ; ++i){
        os << taste[i] << '\n';
    }
    return os;

}


Keylogger::Keylogger(const Keylogger &ob) {
    impact = ob.impact;
    zi = ob.zi;
    luna = ob.luna;
    an = ob.an;
    denumire = ob.denumire;
    metoda_de_infectare = ob.metoda_de_infectare;
    registrii = ob.registrii;
    functii = ob.functii;
    taste = ob.taste;
}
Keylogger & Keylogger::operator=(const Keylogger &ob) {
    impact = ob.impact;
    zi = ob.zi;
    luna = ob.luna;
    an = ob.an;
    denumire = ob.denumire;
    metoda_de_infectare = ob.metoda_de_infectare;
    registrii = ob.registrii;
    functii = ob.functii;
    taste = ob.taste;
    return *this;
}
Keylogger::~Keylogger(){
    functii.clear();
    taste.clear();
}

Keylogger::Keylogger(double impact, int zi, int luna, int an, const string &denumire, const string &metodaDeInfectare,
                     const vector<string> &registrii, const vector<string> &functii, const vector<string> &taste)
        : Malware(impact, zi, luna, an, denumire, metodaDeInfectare, registrii), functii(functii), taste(taste) {}

const vector<string> &Keylogger::getFunctii() const {
    return functii;
}

void Keylogger::setFunctii(const vector<string> &functii) {
    Keylogger::functii = functii;
}

const vector<string> &Keylogger::getTaste() const {
    return taste;
}

void Keylogger::setTaste(const vector<string> &taste) {
    Keylogger::taste = taste;
}

//-------------------------------------------------------------------------------------------------------------------

//Prin kernel-keylogger înțelegem un keylogger ce rulează în kernel-mode (de obicei
//prin intermediul unui rootkit). Prin urmare, putem considera că este are atât proprietățile unui
//rootkit cât și ale unui keylogger. În plus, dorim să memorăm dacă ascunde fișiere și registrii.
class KernelKeylogger: public Rootkit, public Keylogger{
private:
    bool ascunde_fisiere;
    bool ascunde_registrii;

public:
    KernelKeylogger() = default;
    KernelKeylogger(const KernelKeylogger& ob);
    KernelKeylogger& operator=(const KernelKeylogger& ob);
    ~KernelKeylogger();

    KernelKeylogger(double impact, int zi, int luna, int an, const string &denumire, const string &metodaDeInfectare,
                    const vector<string> &registrii, const vector<string> &importuri,
                    const vector<string> &semnificative, const vector<string> &functii, const vector<string> &taste, bool ascundeFisiere, bool ascundeRegistrii);

    istream& readMalware(istream& is);
    ostream& printMalware(ostream& os);
    double calculeaza();
};

//Pentru kernel keylogger se respectă valorile de la rootkit și keylogger și se adaugă
//valoarea 20 dacă ascunde fișiere, respectiv valoarea 30 dacă ascunde registrii.
double KernelKeylogger::calculeaza() {
    double val = impact;
    for(int i =0;i < registrii.size(); ++i)
        if(registrii[i] == "“HKLM-run" || registrii[i] == "HKCU-run"){
            val += 20;
            break;
        }
    for(int i = 0;i < semnificative.size(); ++i)
        if(semnificative[i] == "System Service Descriptor Table" || semnificative[i] == "SSDT" || semnificative[i] == "NtCreateFile" ){
            val += 100;
            break;
        }
    for(int i = 0;i < importuri.size(); ++i)
        if(importuri[i] == "ntoskrnl.exe"){
            val = val *2;
            break;
        }
    for(int i = 0;i < functii.size(); ++i)
        if(functii[i] == "CreateFileW" || functii[i] == "OpenProcess" || functii[i] == "ReadFile" || functii[i] =="WriteFile" || functii[i] == "RegisterHotKey"  || functii[i] == "SetWindowsHookEx" )
            val += 30;
    for(int i = 0;i < taste.size(); ++i)
        if(taste[i] == "Up" || taste[i] == "Num Lock" || taste[i] == "Down" || taste[i] =="Right" || taste[i] == "UP"  || taste[i] == "Left" || taste[i] == "PageDown" )
            val += 10;
    if(ascunde_registrii)
        val += 30;
    if(ascunde_fisiere)
        val += 20;
    return val;
}
ostream & KernelKeylogger::printMalware(ostream &os) {
    os << "Impact: " << impact << "\n";
    os << "Data: " << zi << '/' << luna << '/' << an << '\n';
    os << "Denumire: " << denumire << '\n';
    os << "Metoda de inf: " << metoda_de_infectare << '\n';
    os << "Registrii:\n";
    for(int i = 0;i < registrii.size() ; ++i){
        cout  << registrii[i] << '\n';
    }
    os  << "Importuri:\n";
    for(int i = 0;i < importuri.size() ; ++i){
        cout  << importuri[i] << '\n';
    }
    os << "Semnificative:\n";
    for(int i = 0;i < semnificative.size() ; ++i){
        os << semnificative[i] << '\n';
    }
    os  << "Functii:\n";
    for(int i = 0;i < functii.size() ; ++i){
        cout  << functii[i] << '\n';
    }
    os << "Taste:\n";
    for(int i = 0;i < taste.size() ; ++i){
        os << taste[i] << '\n';
    }
    return os;
}
istream & KernelKeylogger::readMalware(istream &is) {
    cout << "Impact:\n";
    is >> impact;
    is.get();
    cout << "Data:\n";
    cout << "An:\n";
    bool bisect = 0;
    int zile[]={0,31,28,31,30,31,30,31,31,30,31,30,31};
    is >> an;
    is.get();
    if ((an % 4 == 0 && an % 100!=0) || an%400 == 0 )
        bisect = 1;
    cout << "Luna:\n";
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
    cout << "Ziua\n";
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
    cout << "Denumire:\n";
    getline(is, denumire);
    cout << "Metoda de infectare:\n";
    getline(is, metoda_de_infectare);
    int nr;

    while(true){
        try{

            cout << "Numar registrii:\n";
            is >> nr;
            is.get();
            if(nr < 0)
                throw string("Nr invalid!");
            else
                break;

        }
        catch (string s){
            cout << s << '\n';
        }
    }
    for(int i = 0;i < nr ; ++i){
        cout << "Registru:\n";
        string s;
        getline(is, s);
        registrii.push_back(s);
    }

    while(true){
        try{

            cout << "Numar Functii:\n";
            is >> nr;
            is.get();
            if(nr < 0)
                throw string("Nr invalid!");
            else
                break;

        }
        catch (string s){
            cout << s << '\n';
        }
    }
    for(int i = 0;i < nr ; ++i){
        cout << "Functii:\n";
        string s;
        getline(is, s);
        functii.push_back(s);
    }
    while(true){
        try{

            cout << "Numar taste:\n";
            is >> nr;
            is.get();
            if(nr < 0)
                throw string("Nr invalid!");
            else
                break;

        }
        catch (string s){
            cout << s << '\n';
        }
    }
    for(int i = 0;i < nr ; ++i){
        cout << "Taste:\n";
        string s;
        getline(is, s);
        taste.push_back(s);
    }
    while(true){
        try{

            cout << "Numar importuri:\n";
            is >> nr;
            is.get();
            if(nr < 0)
                throw string("Nr invalid!");
            else
                break;

        }
        catch (string s){
            cout << s << '\n';
        }
    }
    for(int i = 0;i < nr ; ++i){
        cout << "Import:\n";
        string s;
        getline(is, s);
        importuri.push_back(s);
    }
    while(true){
        try{

            cout << "Numar semnificative:\n";
            is >> nr;
            is.get();
            if(nr < 0)
                throw string("Nr invalid!");
            else
                break;

        }
        catch (string s){
            cout << s << '\n';
        }
    }
    for(int i = 0;i < nr ; ++i){
        cout << "Semnificativ:\n";
        string s;
        getline(is, s);
        semnificative.push_back(s);
    }
    return is;
}
KernelKeylogger::KernelKeylogger(const KernelKeylogger &ob) {
    impact = ob.impact;
    zi = ob.zi;
    luna = ob.luna;
    denumire = ob.denumire;
    an = ob.an;
    metoda_de_infectare = ob.metoda_de_infectare;
    registrii = ob.registrii;
    functii = ob.functii;
    taste = ob.taste;
    importuri = ob.importuri;
    semnificative = ob.semnificative;
}
KernelKeylogger & KernelKeylogger::operator=(const KernelKeylogger &ob) {
    impact = ob.impact;
    zi = ob.zi;
    luna = ob.luna;
    denumire = ob.denumire;
    an = ob.an;
    metoda_de_infectare = ob.metoda_de_infectare;
    registrii = ob.registrii;
    functii = ob.functii;
    taste = ob.taste;
    importuri = ob.importuri;
    semnificative = ob.semnificative;
    return *this;
}
KernelKeylogger::~KernelKeylogger(){
    ascunde_fisiere = ascunde_registrii = 0;
}

KernelKeylogger::KernelKeylogger(double impact, int zi, int luna, int an, const string &denumire,
                                 const string &metodaDeInfectare, const vector<string> &registrii,
                                 const vector<string> &importuri, const vector<string> &semnificative, const vector<string> &functii, const vector<string> &taste,
                                 bool ascundeFisiere, bool ascundeRegistrii) : Malware(impact, zi, luna, an, denumire,
                                                                                       metodaDeInfectare, registrii),
                                                                               ascunde_fisiere(ascundeFisiere),
                                                                               ascunde_registrii(ascundeRegistrii) {
    this->importuri = importuri;
    this->semnificative = semnificative;
    this->functii = functii;
    this->taste = taste;
}

//--------------------------------------------------------------------------------------------------------------------
//Prin ransomware înțelegem un malware care criptează fișiere de pe disk. Pentru
//acesta se reține ratingul de criptare (un număr de la 1 la 10) și un rating de obfuscare (un
//număr real ce reprezintă procentul de obfuscare (obfuscare = metodă de a
//ascunde/îngreuna intenția inițială a codului))

class Ransomware : public Malware{
private:
    double rating_criptare;
    double rating_obfuscare;

public:
    Ransomware();
    Ransomware(const Ransomware& ob);
    Ransomware& operator=(const Ransomware& ob);
    ~Ransomware();
    Ransomware(double impact, int zi, int luna, int an, const string &denumire, const string &metodaDeInfectare,
               const vector<string> &registrii, double ratingCriptare, double ratingObfuscare);

    void setRatingCriptare(double ratingCriptare);

    void setRatingObfuscare(double ratingObfuscare);

    istream& readMalware(istream& is);
    ostream& printMalware(ostream& os);
    double calculeaza();
};
double Ransomware::calculeaza() {
    double val = rating_obfuscare + rating_criptare;
    for(int i =0;i < registrii.size(); ++i)
        if(registrii[i] == "“HKLM-run" || registrii[i] == "HKCU-run"){
            val += 20;
            break;
        }
    return val;
}
istream & Ransomware::readMalware(istream &is) {
    cout << "Impact:\n";
    is >> impact;
    is.get();
    cout << "Data:\n";
    cout << "An:\n";
    bool bisect = 0;
    int zile[]={0,31,28,31,30,31,30,31,31,30,31,30,31};
    is >> an;
    is.get();
    if ((an % 4 == 0 && an % 100!=0) || an%400 == 0 )
        bisect = 1;
    cout << "Luna:\n";
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
    cout << "Ziua\n";
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
    cout << "Denumire:\n";
    getline(is, denumire);
    cout << "Metoda de infectare:\n";
    getline(is, metoda_de_infectare);
    int nr;

    while(true){
        try{

            cout << "Numar registrii:\n";
            is >> nr;
            is.get();
            if(nr < 0)
                throw string("Nr invalid!");
            else
                break;

        }
        catch (string s){
            cout << s << '\n';
        }
    }
    for(int i = 0;i < nr ; ++i){
        cout << "Registru:\n";
        string s;
        getline(is, s);
        registrii.push_back(s);
    }
    cout << "Rating criptare:\n";
    is >> rating_criptare;
    is.get();
    cout << "Rating obfuscare:\n";
    is >> rating_obfuscare;
    is.get();
    return is;
}
ostream & Ransomware::printMalware(ostream &os) {
    os << "Impact: " << impact << "\n";
    os << "Data: " << zi << '/' << luna << '/' << an << '\n';
    os << "Denumire: " << denumire << '\n';
    os << "Metoda de inf: " << metoda_de_infectare << '\n';
    os << "Registrii:\n";
    for(int i = 0;i < registrii.size() ; ++i){
        cout  << registrii[i] << '\n';
    }
    os <<  "Rating criptare: " << rating_criptare << '\n';
    os << "Rating obfuscare: " << rating_obfuscare << '\n';
    return os;
}
Ransomware::Ransomware() {
    impact = 0;
    zi = 0;
    luna = 0;
    an = 0;
    metoda_de_infectare = "";
    denumire = "";
    rating_criptare= 0;
    rating_obfuscare = 0;

}
Ransomware::Ransomware(const Ransomware &ob) {
    impact = ob.impact;
    zi = ob.zi;
    luna = ob.luna;
    denumire = ob.denumire;
    an = ob.an;
    metoda_de_infectare = ob.metoda_de_infectare;
    registrii = ob.registrii;
    rating_obfuscare = ob.rating_obfuscare;
    rating_criptare = ob.rating_criptare;
}
Ransomware & Ransomware::operator=(const Ransomware &ob) {
    impact = ob.impact;
    zi = ob.zi;
    luna = ob.luna;
    denumire = ob.denumire;
    an = ob.an;
    metoda_de_infectare = ob.metoda_de_infectare;
    registrii = ob.registrii;rating_obfuscare = ob.rating_obfuscare;
    rating_criptare = ob.rating_criptare;
    return *this;

}
Ransomware::~Ransomware() {
    rating_criptare = rating_obfuscare = 0;
}

Ransomware::Ransomware(double impact, int zi, int luna, int an, const string &denumire, const string &metodaDeInfectare,
                       const vector<string> &registrii, double ratingCriptare, double ratingObfuscare) : Malware(impact,
                                                                                                                 zi,
                                                                                                                 luna,
                                                                                                                 an,
                                                                                                                 denumire,
                                                                                                                 metodaDeInfectare,
                                                                                                                 registrii),
                                                                                                         rating_criptare(
                                                                                                                 ratingCriptare),
                                                                                                         rating_obfuscare(
                                                                                                                 ratingObfuscare) {}

void Ransomware::setRatingCriptare(double ratingCriptare) {
    rating_criptare = ratingCriptare;
}

void Ransomware::setRatingObfuscare(double ratingObfuscare) {
    rating_obfuscare = ratingObfuscare;
}
//--------------------------------------------------------------------------------------------------------------------------------
//Pentru fiecare computer din firmă se reține un id unic, incrementat automat, o listă de
//malware (poate conține un malware sau mai multe) și ratingul final ce este calculat drept
//suma ratingului impactului fiecărui malware
class Computer{
private:
    static int id;
    int cod;
    double rating_final;
    vector <Malware*> virusi;

public:
    int getCod() const;
    void setCod(int cod);

    double getRatingFinal() const;
    void setRatingFinal(double ratingFinal);

    const vector<Malware *> &getVirusi() const;
    void setVirusi(const vector<Malware *> &virusi);

    Computer();
    Computer(const Computer& c);
    Computer& operator=(const Computer& c);
    ~Computer();
    Computer(vector < Malware*> virus);

    void addVirus(Malware *m);
    friend istream& operator>>(istream& is, Computer& c);
    friend ostream & operator<<(ostream& os, Computer& c);

};
istream& operator>>(istream& is, Computer& c){
    int nr;
    while(true){
        try{

            cout << "Numar virusuri:\n";
            is >> nr;
            is.get();
            if(nr < 0)
                throw string("Nr invalid!");
            else
                break;

        }
        catch (string s){
            cout << s << '\n';
        }
    }
    for(int i = 0;i < nr; ++i){
        string tip;
        Malware *p = nullptr;
        while(true){
            try{
                cout << "Introduceti tipul virsurului - root sau key sau ker sau ran \n";
                getline(is, tip);
                if(tip == "root"){
                    p = new Rootkit;
                    break;;
                }
                else if(tip == "key"){
                    p = new Keylogger;
                    break;
                }else if(tip == "ker"){
                    p = new KernelKeylogger;
                    break;
                }
                else if(tip == "ran"){
                    p = new Ransomware;
                    break;
                }

                else throw string("Tip invalid!");
            }
            catch(string s){
                cout << s << '\n';
            }
        }
        is >> *p;
        c.rating_final += p->calculeaza();
        c.virusi.push_back(p);
    }
    return is;

}
ostream & operator<<(ostream& os, Computer& c){
    os << "Cod: " << c.cod << '\n';
    os << "Rating final: " << c.rating_final << '\n';
    os << "Virusi:\n";
    for(int i = 0;i < c.virusi.size(); ++i)
        cout << *c.virusi[i] << '\n';
    return os;
}
Computer::Computer(vector<Malware *> virus) {
    ++id;
    cod = id;
    for(int i = 0;i< virusi.size(); ++i)
        delete virusi[i];
    virusi.clear();
    for(int i = 0;i < virus.size(); ++i) {
        addVirus(virus[i]);
        rating_final += virus[i]->calculeaza();
    }
}
void Computer::addVirus(Malware *m) {
    if(Ransomware *d = dynamic_cast<Ransomware*>(m))
        virusi.push_back(new Ransomware(*d));
    else if(Rootkit *d = dynamic_cast<Rootkit*>(m))
        virusi.push_back(new Rootkit(*d));
    else if(Keylogger *d = dynamic_cast<Keylogger*>(m))
        virusi.push_back(new Keylogger(*d));
    else if(KernelKeylogger *d = dynamic_cast<KernelKeylogger*>(m))
        virusi.push_back(new KernelKeylogger(*d));
}
int Computer::id = 0;
Computer::Computer() : virusi(){
    ++id;
    cod  = id;
    rating_final = 0;
}
Computer::Computer(const Computer &c) {
    cod = c.cod;
    rating_final = c.rating_final;
    for(int i = 0;i< virusi.size(); ++i)
        delete virusi[i];
    virusi.clear();
    for(int i = 0;i < c.virusi.size(); ++i)
        addVirus(c.virusi[i]);
}
Computer & Computer::operator=(const Computer &c) {
    cod = c.cod;
    rating_final = c.rating_final;
    for(int i = 0;i< virusi.size(); ++i)
        delete virusi[i];
    virusi.clear();
    for(int i = 0;i < c.virusi.size(); ++i)
        addVirus(c.virusi[i]);
    return *this;
}
Computer::~Computer() {
    --id;
    cod = 0;
    rating_final = 0;
    for(int i = 0;i < virusi.size();++i)
        delete virusi[i];
    virusi.clear();
}

int Computer::getCod() const {
    return cod;
}

void Computer::setCod(int cod) {
    Computer::cod = cod;
}

double Computer::getRatingFinal() const {
    return rating_final;
}

void Computer::setRatingFinal(double ratingFinal) {
    rating_final = ratingFinal;
}

const vector<Malware *> &Computer::getVirusi() const {
    return virusi;
}

void Computer::setVirusi(const vector<Malware *> &virusi) {
    Computer::virusi = virusi;
}

//----------------------------------------------------------Meniu Interactiv------------------------------------------

class MeniuInteractiv{
private:
    vector < Computer*> calculatoare;

    static MeniuInteractiv* instanta;
    MeniuInteractiv() = default;
    MeniuInteractiv(const MeniuInteractiv& m) = default;
    MeniuInteractiv(MeniuInteractiv& m) = default;
    MeniuInteractiv& operator=(const MeniuInteractiv& m) = default;
    MeniuInteractiv& operator=(MeniuInteractiv& ob) = default;

public:
    static MeniuInteractiv* getInstanta(){
        if(instanta == nullptr)
            instanta = new MeniuInteractiv();
        return instanta;
    }
    static void deleteInstanta(){
        if(instanta != nullptr)
            delete instanta;
        instanta = nullptr;
    }
    ~MeniuInteractiv(){
        for(int i = 0;i < calculatoare.size(); ++i)
            delete calculatoare[i];
        calculatoare.clear();
    }

    void demo();
    void adaugaCalculator();
    void afisCalculatoare();
    void afisCalculatoareRating();
    void afisPrimeleK();
    void afisProcent();

};
void MeniuInteractiv::afisProcent() {
    double p;
    int nr = 0;
    for(int i = 0;i < calculatoare.size();++i)
        if(calculatoare[i]->getRatingFinal() != 0)
            ++nr;
        if(calculatoare.size()) {
            p = 100.0 * ((double) nr) / ((double) calculatoare.size());
            cout << "Procent: " << p << '\n';
        }
        else
            cout << "Nu exista calculatoare\n";
}
void MeniuInteractiv::afisCalculatoareRating() {
    for(int i = 0;i < calculatoare.size(); ++i)
        for(int j = i+1;j < calculatoare.size(); ++j)
            if(calculatoare[i]->getRatingFinal() > calculatoare[j]->getRatingFinal())
                swap(calculatoare[i],calculatoare[j]);

    for(int i = 0;i < calculatoare.size(); ++i)
        cout << *calculatoare[i] << '\n';
    cout << '\n';
}
void MeniuInteractiv::afisPrimeleK() {
    int k;
    while(true){
        cout << "K este:\n";
        cin >> k;
        cin.get();
        if(k <= 0 )
            throw string("Nr invalid!");
        else
            break;;
    }
    for(int i = 0;i < calculatoare.size(); ++i)
        for(int j = i+1;j < calculatoare.size(); ++j)
            if(calculatoare[i]->getRatingFinal() > calculatoare[j]->getRatingFinal())
                swap(calculatoare[i],calculatoare[j]);
    for(int i = 0 ;i < k && i < calculatoare.size(); ++i)
        cout << *calculatoare[i] << '\n';
    cout << '\n';


}
void MeniuInteractiv::adaugaCalculator() {
    Computer *c = new Computer;
    cout << "Calculator:\n";
    cin >> *c;
    calculatoare.push_back(c);
}
void MeniuInteractiv::afisCalculatoare() {
    for(int i = 0;i < calculatoare.size(); ++i)
        cout << *calculatoare[i] << '\n';
    cout << '\n';
}

void MeniuInteractiv::demo() {
    cout << "demo\n";
}
MeniuInteractiv* MeniuInteractiv::instanta = nullptr;

int main() {

    int optiune;
    MeniuInteractiv* m = m->getInstanta();
    while(true){
        cout << "0.Demo\n";
        cout << "1.Adauga Calculator\n";
        cout << "2.Afis Calculatoare\n";
        cout << "3.Afis Calculatoare dupa Rating\n";
        cout << "4.Afis primele k calculatoare\n";
        cout << "5.Afis procent de calculatoare infectate\n";
        cout << "6.Inchide\n";

        try{
            cin >> optiune;
            cin.get();
            if(optiune < 0 || optiune > 11)
                throw string("Optiune gresita!");
            else{ if(optiune == 0) m->demo();
                if (optiune == 1) m->adaugaCalculator();
                else if (optiune == 2) m->afisCalculatoare();
                else if (optiune == 3) m->afisCalculatoareRating();
                else if (optiune == 4) m->afisPrimeleK();
                else if (optiune == 5)  m->afisProcent();
                else if (optiune == 6) break;

            }
        }
        catch (string s){
            cout << s << '\n';
        }


    }
    m->deleteInstanta();

    return 0;
}