#include <iostream>
#include <vector>
#include <string>

using namespace std;
class Formular{
private:
    string nume;
    string seria;
    string numar;
    bool pasaport;
    double media_bac;
    bool facultate2;
    double media_absolvire;
    string optiune;
    double nota_mate;
public:
    const string &getNume() const;
    void setNume(const string &nume);

    const string &getSeria() const;
    void setSeria(const string &seria);

    const string &getNumar() const;
    void setNumar(const string &numar);

    bool isPasaport() const;
    void setPasaport(bool pasaport);

    double getMediaBac() const;
    void setMediaBac(double mediaBac);

    bool isFacultate2() const;
    void setFacultate2(bool facultate2);

    double getMediaAbsolvire() const;
    void setMediaAbsolvire(double mediaAbsolvire);

    const string &getOptiune() const;
    void setOptiune(const string &optiune);

    double getNotaMate() const;
    void setNotaMate(double notaMate);

    Formular();
    Formular(const Formular& formular);
    Formular& operator=(const Formular& formular);
    ~Formular();
    Formular(const string &nume,bool pasaport, const string &seria, const string &numar, double mediaBac) ;
    Formular(const string &nume,bool pasaport, const string &seria, const string &numar, double mediaBac, bool facultate2,
             double notaMate);

    Formular(const string &nume,bool pasaport, const string &seria, const string &numar, double mediaBac, bool facultate2,
             double mediaAdmitere, const string &optiune, double notaMate);

    Formular(const string &nume,bool pasaport, const string &seria, const string &numar, double mediaBac, const string &optiune,
             double notaMate);

    friend istream& operator>>(istream& is, Formular& formular);
    friend ostream& operator<<(ostream& os, Formular& formular);

};
istream& operator>>(istream& is, Formular& formular){
    cout << "Nume:\n";
    getline(is,formular.nume);
    cout << "Pasaport: 1- da sau 0 - nu\n";
    is >> formular.pasaport;
    is.get();
    cout << "Seria:\n";
    getline(is, formular.seria);
    cout << "Numar:\n";
    getline(is, formular.numar);
    cout << "Media de bac:\n";
    is >> formular.media_bac;
    is.get();
    cout << "A doua facultate? 1 - da sau 0 - nu\n";
    is >> formular.facultate2;
    is.get();
    if(formular.facultate2){
        cout << "Media absolvire:\n";
        is >> formular.media_absolvire;
        is.get();
    }
    else
        formular.media_absolvire = 0;
    cout << "Optiune:  ID sau IF:\n";
    getline(is, formular.optiune);
    if(formular.optiune == "ID" && !formular.facultate2){
        cout << "Nota mate:\n";
        is >> formular.nota_mate;
        is.get();
    }
    return is;
}
ostream& operator<<(ostream& os, Formular& formular){
    os << "Nume: " << formular.nume << '\n';
    os << "Pasaport: " << formular.pasaport << '\n';
    os << "Seria: " << formular.seria << '\n';
    os << "Numar: " << formular.numar << '\n';
    os << "Media de bac: " << formular.media_bac << '\n';
    os << "A doua facultate: " << formular.facultate2 << '\n';
    if(formular.facultate2){
        os << "Medie absolvire: " <<  formular.media_absolvire << '\n';
    }
    if(formular.optiune == "ID" && !formular.facultate2)
        os << "Nota mate: " << formular.nota_mate << '\n';
    return os;
}

Formular::Formular() {
    nume = seria = numar = "";
    media_bac = media_absolvire = 0;
    facultate2 = false;
}
Formular::Formular(const Formular &formular) {
    nume = formular.nume;
    seria = formular.seria;
    numar = formular.numar;
    media_bac = formular.media_bac;
    facultate2 = formular.facultate2;
    media_absolvire = formular.media_absolvire;
}
Formular & Formular::operator=(const Formular &formular) {
    nume = formular.nume;
    seria = formular.seria;
    numar = formular.numar;
    media_bac = formular.media_bac;
    facultate2 = formular.facultate2;
    media_absolvire = formular.media_absolvire;
    return *this;
}
Formular::~Formular() {
    nume.clear();
    seria.clear();
    numar.clear();
    media_bac = media_absolvire = 0;
    facultate2 = false;
}

Formular::Formular(const string &nume, bool pasaport,const string &seria, const string &numar, double mediaBac) : nume(nume),
                                                                                                    seria(seria),
                                                                                                    numar(numar),
                                                                                                    media_bac(
                                                                                                            mediaBac),pasaport(pasaport) {}

Formular::Formular(const string &nume,bool pasaport, const string &seria, const string &numar, double mediaBac, bool facultate2,
                   double notaMate) : nume(nume), seria(seria), numar(numar), media_bac(mediaBac),
                                      facultate2(facultate2), media_absolvire(notaMate),pasaport(pasaport) {}

Formular::Formular(const string &nume,bool pasaport,const string &seria, const string &numar, double mediaBac, bool facultate2,
                   double mediaAdmitere, const string &optiune, double notaMate) : nume(nume), seria(seria),
                                                                                   numar(numar), media_bac(mediaBac),
                                                                                   facultate2(facultate2),
                                                                                   media_absolvire(mediaAdmitere),
                                                                                   optiune(optiune),
                                                                                   nota_mate(notaMate),pasaport(pasaport) {}

Formular::Formular(const string &nume, bool pasaport,const string &seria, const string &numar, double mediaBac, const string &optiune,
                   double notaMate) : nume(nume), seria(seria), numar(numar), media_bac(mediaBac), optiune(optiune),
                                      nota_mate(notaMate),pasaport(pasaport) {}

const string &Formular::getNume() const {
    return nume;
}

void Formular::setNume(const string &nume) {
    Formular::nume = nume;
}

const string &Formular::getSeria() const {
    return seria;
}

void Formular::setSeria(const string &seria) {
    Formular::seria = seria;
}

const string &Formular::getNumar() const {
    return numar;
}

void Formular::setNumar(const string &numar) {
    Formular::numar = numar;
}

bool Formular::isPasaport() const {
    return pasaport;
}

void Formular::setPasaport(bool pasaport) {
    Formular::pasaport = pasaport;
}

double Formular::getMediaBac() const {
    return media_bac;
}

void Formular::setMediaBac(double mediaBac) {
    media_bac = mediaBac;
}

bool Formular::isFacultate2() const {
    return facultate2;
}

void Formular::setFacultate2(bool facultate2) {
    Formular::facultate2 = facultate2;
}

double Formular::getMediaAbsolvire() const {
    return media_absolvire;
}

void Formular::setMediaAbsolvire(double mediaAbsolvire) {
    media_absolvire = mediaAbsolvire;
}

const string &Formular::getOptiune() const {
    return optiune;
}

void Formular::setOptiune(const string &optiune) {
    Formular::optiune = optiune;
}

double Formular::getNotaMate() const {
    return nota_mate;
}

void Formular::setNotaMate(double notaMate) {
    nota_mate = notaMate;
}

//-----------------------------------------------------------------------------------------------


class Dosar{
private:
    Formular formular;
    static int id;
    int numar_dosar;
    string cod_legitimatie;
    double nota_concurs;
    double media_admitere;

public:
    const Formular &getFormular() const;
    void setFormular(const Formular &formular);

    static int getId();
    static void setId(int id);

    int getNumarDosar() const;
    void setNumarDosar(int numarDosar);

    const string &getCodLegitimatie() const;
    void setCodLegitimatie(const string &codLegitimatie);

    double getNotaConcurs() const;
    void setNotaConcurs(double notaConcurs);

    double getMediaAdmitere() const;
    void setMediaAdmitere(double mediaAdmitere);

    Dosar();
    Dosar(const Dosar& dosar);
    Dosar& operator=(const Dosar& dosar);
    Dosar(const Formular &formular, double notaConcurs);
    ~Dosar();


    void calculeazaMedie();
    void calculeazaCodLegitimatie();

    friend istream& operator>>(istream& is, Dosar& dosar);
    friend ostream& operator<<(ostream& os, Dosar& dosar);

};
istream& operator>>(istream& is, Dosar& dosar){
    cout << "Formular:\n";
    is >> dosar.formular;
    dosar.calculeazaCodLegitimatie();
    if(dosar.formular.isFacultate2() == false) {
        if (dosar.formular.getOptiune() == "IF") {
            cout << "Nota1:\n";
            double nota1, nota2;
            is >> nota1;
            is.get();
            cout << "Nota2:\n";
            is >> nota2;
            is.get();
            double med = (nota1 + nota2) / 2.0;
            dosar.nota_concurs = med;
        }
    }
    else{
        cout << "Nota proba orala:\n";
        is >> dosar.nota_concurs;
        is.get();
    }
    dosar.calculeazaMedie();
    return is;

}
ostream& operator<<(ostream& os, Dosar& dosar) {
    os << "Formular:\n";
    os << dosar.formular << '\n';
    os  << "Cod Legitimatie: " << dosar.cod_legitimatie << '\n';
    os << "Nota concurs: " << dosar.nota_concurs << '\n';
    os << "Medie admitere: " << dosar.media_admitere << '\n';
    return os;
}

Dosar::Dosar() {
    ++id;
    numar_dosar = id;
    cod_legitimatie = "";
    nota_concurs = 0;
    media_admitere = 0;
    calculeazaCodLegitimatie();
}
Dosar::Dosar(const Dosar &dosar) {
    numar_dosar = dosar.numar_dosar;
    formular = dosar.formular;
    cod_legitimatie = dosar.cod_legitimatie;
    nota_concurs = dosar.nota_concurs;
    media_admitere = dosar.media_admitere;
}
Dosar & Dosar::operator=(const Dosar &dosar) {
    numar_dosar = dosar.numar_dosar;
    formular = dosar.formular;
    cod_legitimatie = dosar.cod_legitimatie;
    nota_concurs = dosar.nota_concurs;
    media_admitere = dosar.media_admitere;
    return *this;
}
Dosar::~Dosar() {
    --id;
    numar_dosar = 0;
    cod_legitimatie = "";
    nota_concurs = 0;
    media_admitere = 0;
}
void Dosar::calculeazaCodLegitimatie() {
    if(formular.getOptiune() == "IF")
        if(formular.isFacultate2() == false)
            cod_legitimatie = to_string(numar_dosar);
        else
            cod_legitimatie = "IF2_" + to_string(numar_dosar);
    else if(formular.isFacultate2() == false)
        cod_legitimatie = "ID_" + to_string(numar_dosar);
    else
        cod_legitimatie = "ID2_" + to_string(numar_dosar);

}
void Dosar::calculeazaMedie(){
    if (formular.isFacultate2() == false)
        if(formular.getOptiune() == "IF")
                media_admitere = 0.8 * nota_concurs + 0.2 * formular.getMediaBac();
        else media_admitere = 0.6 * nota_concurs + 0.4 *  formular.getNotaMate();
    else
        media_admitere = 0.6 * nota_concurs + 0.4 *  formular.getMediaAbsolvire();
}
Dosar::Dosar(const Formular &formular, double notaConcurs) : formular(formular), nota_concurs(notaConcurs) {}

const Formular &Dosar::getFormular() const {
    return formular;
}

void Dosar::setFormular(const Formular &formular) {
    Dosar::formular = formular;
}

int Dosar::getId() {
    return id;
}

void Dosar::setId(int id) {
    Dosar::id = id;
}

int Dosar::getNumarDosar() const {
    return numar_dosar;
}

void Dosar::setNumarDosar(int numarDosar) {
    numar_dosar = numarDosar;
}

const string &Dosar::getCodLegitimatie() const {
    return cod_legitimatie;
}

void Dosar::setCodLegitimatie(const string &codLegitimatie) {
    cod_legitimatie = codLegitimatie;
}

double Dosar::getNotaConcurs() const {
    return nota_concurs;
}

void Dosar::setNotaConcurs(double notaConcurs) {
    nota_concurs = notaConcurs;
}

double Dosar::getMediaAdmitere() const {
    return media_admitere;
}

void Dosar::setMediaAdmitere(double mediaAdmitere) {
    media_admitere = mediaAdmitere;
}
int Dosar::id = 0;

//-------------------------------------------------------------------------------------------------------------------------------
class Manager{
private:
    vector<Dosar*> dosare;
    int nrLocuriIF;
    int nrLocuriID;
    int nrLocuriTaxaIF;
    int nrLocuriTaxaID;


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
        for(int i = 0; i < dosare.size(); ++i)
            delete dosare[i];
        dosare.clear();
    }

    void demo();
    void setNrLocuri();
    void adaugaCandidat();
    void afisListe();
    void afisAdmisi();
    void afisAdmisiPasaport();

};
void Manager::setNrLocuri() {
    cout << "Nr locuri buget IF:\n";
    cin >> nrLocuriIF;
    cin.get();
    cout << "Nr locuri buget ID:\n";
    cin >> nrLocuriID;
    cin.get();
    cout << "Procent locuri taxa:\n";
    int p;
    cin >> p;
    cin.get();
    nrLocuriTaxaIF = (double)p/100.0 * nrLocuriIF;
    nrLocuriTaxaID = (double)p/100.0 * nrLocuriID;
}
void Manager::adaugaCandidat() {
    Dosar  *d = new Dosar;
    cin >> *d;
    dosare.push_back(d);
}
void Manager::afisListe() {
    cout << "Nr dosaree: " << dosare.size() << '\n';
    cout << "Dosare:\n";
    for(int i = 0;i < dosare.size(); ++i)
        cout << *dosare[i] << '\n';

}
void Manager::afisAdmisi() {
    for(int i = 0;i < dosare.size(); ++i)
        for(int j = i+1; j < dosare.size(); ++j)
            if(dosare[i]->getMediaAdmitere() < dosare[j]->getMediaAdmitere())
                swap(dosare[i],dosare[j]);
    int nr = 0;
    cout << "IF - buget:\n";
    for(int i = 0;i < dosare.size(); ++i)
        if(nr <= nrLocuriIF  &&   dosare[i]->getFormular().getOptiune() == "IF"  && dosare[i]->getFormular().isFacultate2() == false && dosare[i]->getMediaAdmitere()>=5){
            ++nr;
            cout << *dosare[i] << '\n';
        }
        else if(nr > nrLocuriIF)
            break;
    nr = 0;
    cout << "IF - taxa:\n";
    for(int i = 0;i < dosare.size(); ++i)
        if(nr <= nrLocuriTaxaIF  &&   dosare[i]->getFormular().getOptiune() == "IF"  && dosare[i]->getFormular().isFacultate2() == true && dosare[i]->getMediaAdmitere()>=5){
            ++nr;
            cout << *dosare[i] << '\n';
        }
        else if(nr > nrLocuriTaxaIF)
            break;
    nr = 0;
    cout << "ID - buget:\n";

    for(int i = 0;i < dosare.size(); ++i)
        if(nr <= nrLocuriID  &&   dosare[i]->getFormular().getOptiune() == "ID"  && dosare[i]->getFormular().isFacultate2() == false && dosare[i]->getMediaAdmitere()>=5){
            ++nr;
            cout << *dosare[i] << '\n';
        }
        else if(nr > nrLocuriID)
            break;
    nr = 0;
    cout << "ID - taxa:\n";
    for(int i = 0;i < dosare.size(); ++i)
        if(nr <= nrLocuriTaxaID  &&   dosare[i]->getFormular().getOptiune() == "ID"  && dosare[i]->getFormular().isFacultate2() == true && dosare[i]->getMediaAdmitere()>=5){
            ++nr;
            cout << *dosare[i] << '\n';
        }
        else if(nr > nrLocuriTaxaID)
            break;
}
void Manager::afisAdmisiPasaport() {
    for(int i = 0;i < dosare.size(); ++i)
        for(int j = i+1; j < dosare.size(); ++j)
            if(dosare[i]->getMediaAdmitere() < dosare[j]->getMediaAdmitere())
                swap(dosare[i],dosare[j]);
    int nr = 0;
    cout << "IF - buget:\n";
    for(int i = 0;i < dosare.size(); ++i)
        if(nr <= nrLocuriIF  &&   dosare[i]->getFormular().getOptiune() == "IF"  && dosare[i]->getFormular().isFacultate2() == false && dosare[i]->getMediaAdmitere()>=5 && dosare[i]->getFormular().isPasaport() == true){
            ++nr;
            cout << *dosare[i] << '\n';
        }
        else if(nr > nrLocuriIF)
            break;
    nr = 0;
    cout << "IF - taxa:\n";
    for(int i = 0;i < dosare.size(); ++i)
        if(nr <= nrLocuriTaxaIF  &&   dosare[i]->getFormular().getOptiune() == "IF"  && dosare[i]->getFormular().isFacultate2() == true && dosare[i]->getMediaAdmitere()>=5  && dosare[i]->getFormular().isPasaport() == true){
            ++nr;
            cout << *dosare[i] << '\n';
        }
        else if(nr > nrLocuriTaxaIF)
            break;
    nr = 0;
    cout << "ID - buget:\n";

    for(int i = 0;i < dosare.size(); ++i)
        if(nr <= nrLocuriID  &&   dosare[i]->getFormular().getOptiune() == "ID"  && dosare[i]->getFormular().isFacultate2() == false && dosare[i]->getMediaAdmitere()>=5  && dosare[i]->getFormular().isPasaport() == true){
            ++nr;
            cout << *dosare[i] << '\n';
        }
        else if(nr > nrLocuriID)
            break;
    nr = 0;
    cout << "ID - taxa:\n";
    for(int i = 0;i < dosare.size(); ++i)
        if(nr <= nrLocuriTaxaID  &&   dosare[i]->getFormular().getOptiune() == "ID"  && dosare[i]->getFormular().isFacultate2() == true && dosare[i]->getMediaAdmitere()>=5  && dosare[i]->getFormular().isPasaport() == true){
            ++nr;
            cout << *dosare[i] << '\n';
        }
        else if(nr > nrLocuriTaxaID)
            break;
}
void Manager::demo() {
}
Manager* Manager::instanta = nullptr;

int main() {
    int optiune;
    Manager* m = m->getInstanta();
    while(1){
        cout << "0.Demo\n";
        cout << "1.setNrLocuri\n";
        cout << "2.adaugaCandidat\n";
        cout << "3.afisListe\n";
        cout << "4.afisAdmisi\n";
        cout << "5.afisAdmisiPasaport\n";
        cout << "6.inchide\n";

        try{
            cin >> optiune;
            cin.get();
            if(optiune < 0 || optiune > 11)
                throw string("Optiune gresita!");
            else{ if(optiune == 0) m->demo();
                if (optiune == 1) m->setNrLocuri();
                else if (optiune == 2) m->adaugaCandidat();
                else if (optiune == 3) m->afisListe();
                else if (optiune == 4) m->afisAdmisi();
                else if (optiune == 5) m->afisAdmisiPasaport();
                else if(optiune == 6) break;

            }
        }
        catch (string s){
            cout << s << '\n';
        }


    }
    m->deleteInstanta();

    return 0;
}