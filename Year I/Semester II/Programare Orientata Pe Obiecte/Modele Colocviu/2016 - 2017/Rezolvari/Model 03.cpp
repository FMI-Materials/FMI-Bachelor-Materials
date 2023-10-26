#include <iostream>
#include <vector>
using namespace std;
class Participant{
private:
    string nume;
    string cnp;
    int varsta;
    string tip;
    int nrCredite;
public:
    const string &getNume() const;
    void setNume(const string &nume);

    const string &getCnp() const;
    void setCnp(const string &cnp);

    void setVarsta(int varsta);
    const int getVarsta();

    const string &getTip() const;
    void setTip(const string &tip);

    int getNrCredite() const;
    void setNrCredite(int nrCredite);

    Participant();
    Participant(const Participant& participant);
    Participant(const string &nume, const string &cnp, const string &tip);
    Participant& operator=(const Participant& participant);
    ~Participant();

    friend istream& operator>>(istream& is, Participant& participant);
    friend ostream& operator<<(ostream& os, Participant& participant);

};
istream& operator>>(istream& is, Participant& participant){
    cout << "Introduceti numele:\n";
    getline(is, participant.nume);
    cout << "Introduceti cnp:\n";
    getline(is,participant.cnp);
    cout << "Introduceti tip:\n";
    getline(is,participant.tip);
    return is;
}
ostream& operator<<(ostream& os, Participant& participant){
    os << "Nume: " << participant.nume << '\n';
    os << "CNP: " << participant.cnp << '\n';
    if(participant.tip == "prof")
        os << "Nr Credite: " << participant.nrCredite << '\n';
    return os;
}
const int Participant::getVarsta() {
    return varsta;
}
Participant::~Participant() {
    nume = cnp = tip = "";
    varsta = nrCredite = 0;

}
Participant & Participant::operator=(const Participant &participant) {
    nume = participant.nume;
    cnp = participant.cnp;
    tip = participant.tip;
    nrCredite = participant.nrCredite;
}
Participant::Participant() {
    nume = "";
    cnp = "";
    nrCredite = 0;
    tip = "";
}
Participant::Participant(const Participant &participant) {
    nume = participant.nume;
    cnp = participant.cnp;
    tip = participant.tip;
    nrCredite = participant.nrCredite;
}

Participant::Participant(const string &nume, const string &cnp, const string &tip) : nume(nume), cnp(cnp), tip(tip) {}

const string &Participant::getNume() const {
    return nume;
}

void Participant::setNume(const string &nume) {
    Participant::nume = nume;
}

const string &Participant::getCnp() const {
    return cnp;
}

void Participant::setCnp(const string &cnp) {
    Participant::cnp = cnp;
}

void Participant::setVarsta(int varsta) {
    Participant::varsta = varsta;
}

const string &Participant::getTip() const {
    return tip;
}

void Participant::setTip(const string &tip) {
    Participant::tip = tip;
}

int Participant::getNrCredite() const {
    return nrCredite;
}

void Participant::setNrCredite(int nrCredite) {
    Participant::nrCredite = nrCredite;
}

class Activitate{
protected:
    string denumire;
    int zi, luna, an;
    vector<pair<int, Participant>> participanti;
public:
    const string &getDenumire() const;
    void setDenumire(const string &denumire);

    int getZi() const;
    void setZi(int zi);

    int getLuna() const;
    void setLuna(int luna);

    int getAn() const;
    void setAn(int an);

    const vector<pair<int, Participant>> &getParticipanti() const;
    void setParticipanti(const vector<pair<int, Participant>> &participanti);

    Activitate();
    Activitate(const Activitate& activitate);
    Activitate(const string &denumire, int zi, int luna, int an, const vector<pair<int, Participant>> &participanti);
    Activitate& operator=(Activitate& activitate);
    virtual ~Activitate();

    friend istream& operator>>(istream& is, Activitate& activitate){
        return activitate.readActivitate(is);
    }
    friend ostream& operator<<(ostream& os,Activitate& activitate){
        return activitate.printActivitate(os);
    }
    virtual istream& readActivitate(istream& is) = 0;
    virtual ostream& printActivitate(ostream& os) = 0;
};
Activitate::Activitate(const Activitate &activitate): denumire(activitate.denumire), zi(activitate.zi), luna(activitate.luna),
an(activitate.an), participanti(activitate.participanti) {

}
Activitate & Activitate::operator=(Activitate &activitate) {
    denumire = activitate.denumire;
    zi = activitate.zi;
    luna = activitate.luna;
    an = activitate.an;
    participanti = activitate.participanti;
    return *this;
}
const string &Activitate::getDenumire() const {
    return denumire;
}

void Activitate::setDenumire(const string &denumire) {
    Activitate::denumire = denumire;
}

int Activitate::getZi() const {
    return zi;
}

void Activitate::setZi(int zi) {
    Activitate::zi = zi;
}

int Activitate::getLuna() const {
    return luna;
}

void Activitate::setLuna(int luna) {
    Activitate::luna = luna;
}

int Activitate::getAn() const {
    return an;
}

void Activitate::setAn(int an) {
    Activitate::an = an;
}

const vector<pair<int, Participant>> &Activitate::getParticipanti() const {
    return participanti;
}

void Activitate::setParticipanti(const vector<pair<int, Participant>> &participanti) {
    Activitate::participanti = participanti;
}

Activitate::Activitate(const string &denumire, int zi, int luna, int an,
                       const vector<pair<int, Participant>> &participanti) : denumire(denumire), zi(zi), luna(luna),
                                                                             an(an), participanti(participanti) {}

Activitate::Activitate() {
    denumire = "";
    zi = luna = an = 0;
}

Activitate::~Activitate() {
    participanti.clear();
    denumire = "";
    zi = luna = an = 0;
}

class Curs:public  Activitate{
private:
    int credite;
public:
    Curs():Activitate(),credite(0){}
    Curs(const string &denumire, int zi, int luna, int an, const vector<pair<int, Participant>> &participanti,
         int credite);
    Curs(const Curs& curs);
    Curs& operator=(Curs& curs);
    ~Curs(){
        credite = 0;
    }

    int getCredite() const;
    void setCredite(int credite);

    istream& readActivitate(istream& is);
    ostream& printActivitate(ostream& os);
};
Curs::Curs(const Curs &curs) : Activitate(curs.denumire, curs.zi, curs.luna, curs.an, curs.participanti), credite(curs.credite) {

}
istream & Curs::readActivitate(istream &is) {
    cout << "Introduceti denumire:\n";
    getline(is, denumire);
    cout << "Introduceti data:\n";
    cout << "Introduceti an:\n";
    bool bisect = 0;
    int zile[]={0,31,28,31,30,31,30,31,31,30,31,30,31};
    is >> an;
    is.get();
    if ((an % 4 == 0 && an % 100!=0) || an%400 == 0 )
        bisect = 1;
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
    cout << "Introduceti nr de participanti\n";
    int nr;
    is >> nr;
    is.get();
    cout << "Introduceti participanti\n";
    for(int i = 0; i < nr; ++i){
        is >> participanti[i].second;
        if(participanti[i].second.getTip() == "prof")
            participanti[i].first = 0;
        else{
            cout << "Introduceti punctaj\n";
            is >> participanti[i].first;
            is.get();
        }
    }
    cout << "Introduceti nr de credite:\n";
    is >> credite;
    is.get();
    for(int i = 0; i < nr; ++i){
        if(participanti[i].second.getTip() == "prof")
            participanti[i].second.setNrCredite(participanti[i].second.getNrCredite()+credite);
    }
    return is;
}
ostream & Curs::printActivitate(ostream &os) {
    os << "Denumire: " << denumire << '\n';
    os << "Data: " << zi << '/' << luna << '/' << an << '\n';
    os << "Participanti\n";
    for(int i = 0; i < participanti.size(); ++i) {
        os << participanti[i].second << " ";
        if(participanti[i].second.getTip() != "prof")
            os << "Punctaj: " << participanti[i].first;
        os << '\n';
    }
    os << "Credite: " << credite << '\n';
    return os;

}
Curs & Curs::operator=(Curs &curs) {
    denumire = curs.denumire;
    zi = curs.zi;
    luna = curs.luna;
    an = curs.an;
    participanti = curs.participanti;
    credite = curs.credite;
    return *this;
}
Curs::Curs(const string &denumire, int zi, int luna, int an, const vector<pair<int, Participant>> &participanti,
           int credite) : Activitate(denumire, zi, luna, an, participanti), credite(credite) {}

int Curs::getCredite() const {
    return credite;
}

void Curs::setCredite(int credite) {
    Curs::credite = credite;
}
class Concurs: public Activitate{
private:
    bool online;
    vector <Participant> castigatori;
    string site;
public:
    bool isOnline() const;
    void setOnline(bool online);

    const vector<Participant> &getCastigatori() const;
    void setCastigatori(const vector<Participant> &castigatori);

    const string &getSite() const;
    void setSite(const string &site);

    Concurs();
    Concurs(const Concurs& concurs);
    Concurs(const string &denumire, int zi, int luna, int an, const vector<pair<int, Participant>> &participanti,
            bool online, const vector<Participant> &castigatori, const string &site);
    Concurs& operator=(Concurs& concurs);
    ~Concurs();

    istream& readActivitate(istream& is);
    ostream& printActivitate(ostream& os);
};
istream & Concurs::readActivitate(istream &is) {
    cout << "Introduceti denumire:\n";
    getline(is, denumire);
    cout << "Introduceti data:\n";
    cout << "Introduceti data:\n";
    cout << "Introduceti an:\n";
    bool bisect = 0;
    int zile[]={0,31,28,31,30,31,30,31,31,30,31,30,31};
    is >> an;
    is.get();
    if ((an % 4 == 0 && an % 100!=0) || an%400 == 0 )
        bisect = 1;
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
    cout << "Introduceti nr de participanti\n";
    int nr;
    is >> nr;
    is.get();
    cout << "Introduceti participanti\n";
    for(int i = 0; i < nr; ++i){
        is >> participanti[i].second;
        if(participanti[i].second.getTip() == "prof")
            participanti[i].first = 0;
        else{
            cout << "Introduceti punctaj\n";
            is >> participanti[i].first;
            is.get();
        }
    }
    cout << "1 - online, 0- offline\n";
    is >> online;
    is.get();
    if(online == 1) {
        cout << "Introduceti site\n";
        getline(is, site);
    }
    for(int i = 0;i < participanti.size();++i)
        for(int j = i+1 ;j < participanti.size(); ++j)
            if(participanti[i].first < participanti[j].first)
                swap(participanti[i],participanti[j]);
    int nrpct = 1;
    castigatori.push_back(participanti[0].second);
    for(int i=1; i < participanti.size() && nrpct <=4; ++i)
        if(participanti[i].first == participanti[i-1].first)
            castigatori.push_back(participanti[i].second);
        else{
            ++nrpct;
            castigatori.push_back(participanti[i].second);
        }
    return is;
}
ostream & Concurs::printActivitate(ostream &os) {
    os << "Denumire: " << denumire << '\n';
    os << "Data: " << zi << '/' << luna << '/' << an << '\n';
    os << "Participanti\n";
    for(int i = 0; i < participanti.size(); ++i) {
        os << participanti[i].second << " ";
        if(participanti[i].second.getTip() != "prof")
            os << "Punctaj: " << participanti[i].first;
        os << '\n';
    }
    if(online)
        os << "Site: " << site << '\n';
    for(int i = 0; i < castigatori.size(); ++i)
        os << castigatori[i] << '\n';

    return os;

}
Concurs::~Concurs() {
    online = false;
    castigatori.clear();
    site = "";
}
Concurs & Concurs::operator=(Concurs &concurs) {
    denumire = concurs.denumire;
    zi = concurs.zi;
    luna = concurs.luna;
    an = concurs.an;
    participanti = concurs.participanti;
    online = concurs.online;
    castigatori = concurs.castigatori;
    site = concurs.site;
    return *this;
}
Concurs::Concurs(const Concurs &concurs) {
    denumire = concurs.denumire;
    zi = concurs.zi;
    luna = concurs.luna;
    an = concurs.an;
    participanti = concurs.participanti;
    online = concurs.online;
    castigatori = concurs.castigatori;
    site = concurs.site;

}
Concurs::Concurs():Activitate(),online(0), site("") {}

Concurs::Concurs(const string &denumire, int zi, int luna, int an, const vector<pair<int, Participant>> &participanti,
                 bool online, const vector<Participant> &castigatori, const string &site) : Activitate(denumire, zi,
                                                                                                       luna, an,
                                                                                                       participanti),
                                                                                            online(online),
                                                                                            castigatori(castigatori),
                                                                                            site(site) {}

bool Concurs::isOnline() const {
    return online;
}

void Concurs::setOnline(bool online) {
    Concurs::online = online;
}

const vector<Participant> &Concurs::getCastigatori() const {
    return castigatori;
}

void Concurs::setCastigatori(const vector<Participant> &castigatori) {
    Concurs::castigatori = castigatori;
}

const string &Concurs::getSite() const {
    return site;
}

void Concurs::setSite(const string &site) {
    Concurs::site = site;
}

class Manager{
private:
    vector <Activitate*> activitati;

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
        for(int i = 0;i < activitati.size();++i)
            delete activitati[i];
        activitati.clear();
    }
    void deleteInstanta(){
        if(instanta!= nullptr)
            delete instanta;
        instanta = nullptr;
    }

    void adaugaParticipanti(int index);
    void alfabeticParticipanti();
    void activitatiData(int zi, int luna,int an);
    void afisPremianti();


};
void Manager::adaugaParticipanti(int index) {
    cout << "Introduceti nr de participanti\n";
    int nr;
    cin >> nr;
    cin.get();

    vector<pair<int, Participant>> vect = activitati[index]->getParticipanti();
    for(int i = 0;i < nr;++i){
        Participant p;
        cin >> p;
        int pct;
        if(p.getTip() == "prof")
            pct  = 0;
        else{
            cout << "Introduceti punctaj\n";
            cin >> pct;
            cin.get();
        }
        vect.push_back(make_pair(pct,p));
    }
    activitati[index]->setParticipanti(vect);
    vect.clear();
}
void Manager::alfabeticParticipanti() {
    for(int i = 0;i < activitati.size(); ++i){
        vector<pair<int, Participant>> vect = activitati[i]->getParticipanti();
        for(int j = 0;j < vect.size(); ++i)
            for(int k = j+1; k< vect.size();++k)
                if(vect[j].second.getNume() > vect[k].second.getNume())
                    swap(vect[j],vect[k]);

        cout << "Activitatea " << i << '\n';
        for(int j = 0;j < vect.size(); ++i)
            cout << vect[j].second << '\n';
        cout << '\n';
        vect.clear();
    }
}
void Manager::activitatiData(int zi, int luna, int an) {
    vector<Participant> vect;
    for(int i = 0;i < activitati.size(); ++i)
        if(activitati[i]->getZi() == zi && activitati[i]->getLuna() == luna && activitati[i]->getAn() == an){
            vector <pair<int, Participant>> v = activitati[i]->getParticipanti();
            for(int j = 0;j < v.size(); ++j)
                vect.push_back(v[j].second);
        }
    for(int i = 0;i <vect.size(); ++i)
        for(int j = i+1; j< vect.size(); ++j)
            if(vect[i].getNume() > vect[j].getNume())
                swap(vect[i],vect[j]);

    for(int i = 0;i <vect.size(); ++i)
        cout << vect[i] << '\n';


}
void Manager::afisPremianti() {
    cout << "de facut\n";
}
Manager* Manager::instanta = nullptr;

int main() {
    int optiune;
    Manager* m = m->getInstanta();
    while(1){
        cout << "0.adauga participanti\n";
        cout << "1.Alfabetic particip\n";
        cout << "2.Participantii dintr-o data\n";
        cout << "3.Afis premianti\n";
        cout << "4.inchide\n";
        try{
            cin >> optiune;
            cin.get();
            if(optiune < 0 || optiune > 11)
                throw string("Optiune gresita!");
            else{ if(optiune == 0) {
                cout << "Introduceti indecul activitatii:\n";
                int index;
                cin >> index;
                cin.get();
                m->adaugaParticipanti(index);
            }
                if (optiune == 1) m->alfabeticParticipanti();
                else if (optiune == 2) {
                    cout << "Introduceti data:\n";
                    cout << "Introduceti an:\n";
                    bool bisect = 0;
                    int zi, luna, an;
                    int zile[]={0,31,28,31,30,31,30,31,31,30,31,30,31};
                    cin >> an;
                    cin.get();
                    if ((an % 4 == 0 && an % 100!=0) || an%400 == 0 )
                        bisect = 1;
                    cout << "Introduceti luna:\n";
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

                    cout << "Introduceti ziua\n";

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
                    m->activitatiData(zi,luna,an);
                }
                else if (optiune == 3) m->afisPremianti();
                else  break;

            }
        }
        catch (string s){
            cout << s << '\n';
        }


    }
    return 0;
}

