#include <iostream>
#include <vector>
#include <memory>
#include <stdexcept>
#include <algorithm>
#include <string.h>

class EroareAplicatie:public std::runtime_error{
public:
    explicit EroareAplicatie(const std::string &arg): std::runtime_error(arg){
        std::cout<<"const. eroare\n";
    }
};

class ErrorOption:public EroareAplicatie{
public:
    explicit ErrorOption(const std::string &arg): EroareAplicatie(arg){}
};

class ErrorStatie:public EroareAplicatie{
public:
    explicit ErrorStatie(const std::string &arg): EroareAplicatie(arg){}
};

class Adresa{
    std::string strada;
    int numar;
    int sector;
public:
    Adresa(const std::string &strada, int numar, int sector) : strada(strada), numar(numar), sector(sector) {}
    friend std::ostream &operator<<(std::ostream &os, const Adresa &andresa) {
        os << "strada: " << andresa.strada << " numar: " << andresa.numar << " sector: " << andresa.sector;
        return os;
    }

    bool operator==(const std::string& arg) const {
        std::string aux = strada +" "+std::to_string(numar)+" "+ std::to_string(sector);
        return  aux == arg;
    }

    bool operator!=(const std::string &rhs) const {
        return !(*this == rhs);
    }
};

class Statie{
protected:
    Adresa adresa;
    std::string numestatie;
    const int id;
    static int contor;
    std::string cod;
    std::vector<int> id_autobuze;
public:
    Statie(const Adresa &adresa, const std::string& numestatie_, std::vector<int> id_autobuze_) :
        adresa(adresa), numestatie(numestatie_), id(contor++), id_autobuze(id_autobuze_){}
    virtual void afisare(std::ostream &os) const{
        auto& statie = *this;
        os << "Statia nr."<<statie.id<<std::endl;
        os<<"adresa: " << statie.adresa << " id: " << statie.id << " cod: " << statie.cod<<std::endl;
        os<<"Autobuze:";
        for(auto& i: id_autobuze) os<<i<<" ";
        os<<std::endl;
    }
    friend std::ostream &operator<<(std::ostream &os, const Statie &statie){
        statie.afisare(os);
        return os;
    }
    virtual void setCod() = 0;

    const Adresa &getAdresa() const {
        return adresa;
    }

    const std::string &getCod() const {
        return cod;
    }

    const std::string &getNumestatie() const {
        return numestatie;
    }

    const std::vector<int> &getIdAutobuze() const {
        return id_autobuze;
    }

    const int getId() const;
    virtual std::shared_ptr<Statie> clone() const = 0;
    virtual ~Statie() = 0;
};

int Statie::contor = 1;

const int Statie::getId() const {
    return id;
}

class StatieUrbana:public Statie{
    bool legitimatie;
public:
    StatieUrbana(const Adresa &adresa, const std::string& nume_, std::vector<int> id_autobuze_, bool legitimatie) : Statie(adresa, nume_, id_autobuze_), legitimatie(legitimatie) {}
    void afisare(std::ostream &os) const override{
        Statie::afisare(os);
        os<<"Achizitie legitimatie: "<<legitimatie<<std::endl;
    }
    void setCod(){
        cod = "SU-" + std::to_string(id);
    }
    std::shared_ptr<Statie> clone()const override {
        std::cout<<"CLONE STATIEURB\n";
        return std::make_shared<StatieUrbana>(*this);
    }
    ~StatieUrbana() override{}
};

class StatieExtraurbana:public Statie{
public:
    StatieExtraurbana(const Adresa &adresa, const std::string& nume_, std::vector<int> id_autobuze_) : Statie(adresa, nume_, id_autobuze_) {}
    void afisare(std::ostream &os) const override{
        Statie::afisare(os);
    }
    void setCod(){
        cod = "SE-" + std::to_string(id);
    }
    std::shared_ptr<Statie> clone()const override {
        std::cout<<"CLONE STATIEEXT\n";
        return std::make_shared<StatieExtraurbana>(*this);
    }
    ~StatieExtraurbana()override{}
};

class PunctInformare{
    std::vector<std::shared_ptr<Statie>> statii;
    int linii[100][100];
public:
    void setLinii(const std::vector<std::shared_ptr<Statie>> &statii_){
        for(auto& statie:statii_){
            for(auto& statie2: statii_ ){
                for(auto& nr_autobuz: statie->getIdAutobuze()){
                    if(std::find(statie2->getIdAutobuze().begin(), statie2->getIdAutobuze().end(), nr_autobuz) != statie2->getIdAutobuze().end()){
                        linii[statie->getId()][statie2->getId()] = 1;
                    }
                }
            }
        }
    }

    PunctInformare(const std::vector<std::shared_ptr<Statie>> &statii_) : statii(statii_){
        setLinii(statii_);
    }

    void addStatie(const std::shared_ptr<Statie> statie_){
        try {
            for(auto& i:statii){
                if(i->getNumestatie() == statie_->getNumestatie())
                    throw(ErrorStatie("Error! Statie existenta!"));
            }
            statii.push_back(statie_);
            setLinii(statii);
            std::cout << "Adaugarea unei statii s-a realizat cu succes!";
        }catch(std::exception& err){
            std::cout << err.what() << "\n";
        }
    }
    void detaliiStatie(const std::string& arg, int caz){
        try {
            int ok = 0;
            switch (caz) {
                case 1:
                    for(auto& i:statii) {
                        if (i->getNumestatie() == arg) {
                            ok = 1;
                            std::cout << *i;
                            break;
                        }
                    }
                    if(!ok)
                        throw(ErrorStatie{"Error! Nu exista statia cu numele: " + arg+"\n"});
                    break;
                case 2:
                    for(auto& i:statii){
                        if(i->getCod() == arg) {
                            ok = 1;
                            std::cout << *i;
                            break;
                        }
                    }
                    if(!ok)
                        throw(ErrorStatie{"Error! Nu exista statia cu codul: " + arg+"\n"});
                    break;
                case 3:
                    for(auto& i:statii){
                        if(i->getAdresa() == arg) {
                            std::cout << *i;
                            ok = 1;
                            break;
                        }
                    }
                    if(!ok)
                        throw(ErrorStatie{"Error! Nu exista statia cu adresa: " + arg+"\n"});
                    break;
                default:
                    throw(ErrorOption("Error! Cant find option!"));
            }

        }
        catch(std::exception& err){
            std::cout << err.what() << "\n";
        }
    }
    float pretCalatorie(const std::string& nume1, const std::string& nume2){
        try{
            int count = 0, id1 = -1, id2 = -1;
            std::shared_ptr<Statie> saux1, saux2;
            for(auto& i:statii){
                if(i->getNumestatie() == nume1){
                    count++;
                    id1 = i->getId();
                    saux1 = i->clone();
                }
                if(i->getNumestatie() == nume2){
                    count++;
                    id2 = i->getId();
                    saux2 = i->clone();
                }
            }
            if(count == 2) {
                std::cout << "Statiile exista\n";
                if(linii[id1][id2]) {
                    std::cout << "Statiile sunt legate\n";
                    if(saux1->getCod().find("U")){
                        if(saux2->getCod().find("U")) {
                            return 2;
                        }else return 1.3*2;
                    }
                    if(saux1->getCod().find("E")){
                        if(saux2->getCod().find("E")) {
                            return 1.2*2;
                        }else return 1.3*2;
                    }
                }
                else {
                    std::cout << "Statiile nu sunt legate\n";
                    if(saux1->getCod().find("U")){
                        if(saux2->getCod().find("U")) {
                            return 2*1.15;
                        }else return 1.4*2;
                    }
                    if(saux1->getCod().find("E")){
                        if(saux2->getCod().find("E")) {
                            return 1.25*2;
                        }else return 1.4*2;
                    }
                }
                throw(EroareAplicatie("Error! 403\n"));
            }
            else
                throw(ErrorStatie{"Error! Statiile nu exista!\n"});
        }catch(std::exception& err){
            std::cout<<err.what()<<"\n";
        }
    }
    void afisareTraseu(int n){
        for(int i = 1; i <= n; i++){
            for(int j = 1; j <= n; j++){
                std::cout<<linii[i][j];
            }
            std::cout<<std::endl;
        }
    }
};

int main() {
    std::shared_ptr<Statie> s1 = std::make_shared<StatieUrbana>(Adresa{"Iuliu Maniu", 22, 6}, "Gorjului", std::vector<int>{1, 16}, false);
    s1->setCod();
    std::shared_ptr<Statie> s2 = std::make_shared<StatieExtraurbana>(Adresa{"Berceni", 1, 4}, "Berceni", std::vector<int>{1, 3});
    s2->setCod();
    PunctInformare manager{std::vector<std::shared_ptr<Statie>>{s1, s2}};
    std::cout<<*s1<<std::endl<<*s2;
    std::cout<<"TEST ADAUGARE STATIE\n";
    std::shared_ptr<Statie> saux = std::make_shared<StatieUrbana>(Adresa{"Iuliu Maniu", 18, 6}, "Lujerului", std::vector<int>{3, 7}, true);
    manager.addStatie(saux);
    std::cout<<"TEST DETALII STATIE\n";
    manager.detaliiStatie("Iuliu Maniu 22 6", 3);
    std::cout<<"TEST PRET CALATORIE\n";
    ///manager.afisareTraseu(5);
    std::cout<<"Pret calatorie: "<<manager.pretCalatorie("Gorjului", "Berceni");
    return 0;
}
