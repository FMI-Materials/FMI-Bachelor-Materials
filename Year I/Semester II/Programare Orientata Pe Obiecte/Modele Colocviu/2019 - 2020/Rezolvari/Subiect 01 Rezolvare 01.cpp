/**
 * Buhai Darius 135
 * Compilator: Apple clang++ 17 ( cel din MacOs, Xcode )
 * Tutore Laborator: Marian Lupascu
 *
 */

#include <iostream>
#include <string>
#include <exception>
#include <vector>

/**
 * Clase utile
 */

/// O clasa abstracta care implementeaza functiile de citire si de afisare, preluate din std
/// Structura clasei este invatata la laborator. Ne-a fost prezentata de domnul Marian Lupascu
class Stream {
public:
    Stream() = default;
    virtual ~Stream() = default;

    friend std::istream &operator>>(std::istream &in, Stream &ob) {
        ob.read(in);
        return in;
    }

    friend std::ostream &operator<<(std::ostream &out, const Stream &ob) {
        ob.write(out);
        return out;
    }

    virtual void read(std::istream &in){}
    virtual void write(std::ostream &out) const {}
};

/// O clasa de tip template cu care verific diverse variabile
template <class T>
class Checker{
public:
    Checker() = default;
    virtual ~Checker() = default;

    static void throwIfNotPositive(T);
    static void throwIfNotStrictPositive(T);
    static void throwIfNotInRange(T, T, T, std::string = "Numarul");
    static void throwIfGreaterThan(T, T, std::string = "Numarul");
};

template <class T>
void Checker<T>::throwIfNotPositive(T value) {
    if (value < 0) {
        throw std::runtime_error("Numarul trebuie sa fie pozitiv!");
    }
}

template <class T>
void Checker<T>::throwIfNotStrictPositive(T value) {
    if (value <= 0) {
        throw std::runtime_error("Numarul trebuie sa fie strict pozitiv!");
    }
}

template <class T>
void Checker<T>::throwIfNotInRange(T value, T a, T b, std::string ob_name) {
    if (value<a || value>b) {
        throw std::runtime_error(ob_name+" trebuie sa fie in intervaulul ["+std::to_string(a)+", "+std::to_string(b)+"]");
    }
}

template <class T>
void Checker<T>::throwIfGreaterThan(T value, T a, std::string ob_name) {
    if (value>a) {
        throw std::runtime_error(ob_name+" trebuie sa fie < "+std::to_string(a));
    }
}

/**
 * Clase axate pe subiect
 */

class Masca: public Stream{
protected:
    std::string tip_protectie;
    bool with_model;
public:
    Masca() {}
    Masca(std::string _tip_protectie, bool _with_model = false): tip_protectie(_tip_protectie), with_model(_with_model){}
    virtual ~Masca() {}

    std::string getTipProtectie() const;
    virtual double getPrice() const;

    bool isWithModel() const;

    void read(std::istream &in) override;
    void write(std::ostream &out) const override;
};

double Masca::getPrice() const{
    return 0;
}

bool Masca::isWithModel() const{
    return with_model;
}

std::string Masca::getTipProtectie() const{
    return tip_protectie;
}

void Masca::read(std::istream &in) {
    if(tip_protectie.empty()){
        std::cout<<"Tip protectie (ffp1/ffp2/ffp3): \n";
        in>>tip_protectie;
    }
    std::cout<<"Cu model (da/nu)?: \n";
    std::string c;
    std::cin>>c;
    with_model = (c=="da");
}

void Masca::write(std::ostream &out) const {
    out<<"Tip protectie: "<<tip_protectie<<'\n';
}

class MascaChirurgicala: public virtual Masca{
protected:
    std::string culoare;
    int numar_pliuri;
public:
    MascaChirurgicala(){}
    MascaChirurgicala(std::string _tip_protectie, std::string _culoare, int _numar_pliuri): Masca(std::move(_tip_protectie)), culoare(std::move(_culoare)), numar_pliuri(_numar_pliuri) {}


    double getPrice() const;

    void read(std::istream &in) override;
    void write(std::ostream &out) const override;
};

double MascaChirurgicala::getPrice() const{
    double mul = 1;
    if(with_model) mul = 1.5;
    if(tip_protectie=="ffp1")
        return 5*mul;
    else if(tip_protectie=="ffp2")
        return 10*mul;
    else if(tip_protectie=="ffp3")
        return 15*mul;
    return 0;
}


void MascaChirurgicala::read(std::istream &in) {
    Masca::read(in);
    std::cout<<"Culoare: \n";
    in>>culoare;
    std::cout<<"Numar pliuri: \n";
    in>>numar_pliuri;
}

void MascaChirurgicala::write(std::ostream &out) const {
    Masca::write(out);
    out<<"Culoare: "<<culoare<<'\n';
    out<<"Numar pliuri: "<<numar_pliuri<<'\n';
}

class MascaPolicarbonat: public virtual Masca{
protected:
    std::string tip_prindere;
public:
    MascaPolicarbonat(): Masca("ffp0"){}
    MascaPolicarbonat(std::string _tip_prindere): Masca("ffp0"), tip_prindere(std::move(_tip_prindere)) {}

    double getPrice() const;

    void read(std::istream &in) override;
    void write(std::ostream &out) const override;
};

double MascaPolicarbonat::getPrice() const{
    double mul = 1;
    if(with_model) mul = 1.5;
    return 20*mul;
}

void MascaPolicarbonat::read(std::istream &in) {
    Masca::read(in);
    std::cout<<"Tip prindere: \n";
    in>>tip_prindere;
}

void MascaPolicarbonat::write(std::ostream &out) const{
    Masca::write(out);
    out<<"Tip prindere: "<<tip_prindere<<'\n';
}

/// Factory
class MascaFactory{
    MascaFactory() = default;

public:
    static Masca *copyInstance(Masca *masca) {
        if (auto var = dynamic_cast<MascaChirurgicala *>(masca))
            return new MascaChirurgicala(*var);
        else if (auto var = dynamic_cast<MascaPolicarbonat *>(masca))
            return new MascaPolicarbonat(*var);
        else if (masca == nullptr)
            return nullptr;
        throw std::runtime_error("Tipul mastii este invalid!");
    }

    static Masca *newInstance(const std::string &tip) {
        if (tip == "chirurgicala")
            return new MascaChirurgicala();
        else if (tip == "policarbonat")
            return new MascaPolicarbonat();
        throw std::runtime_error("Tipul mastii este invalid!");
    }
};

/**
 * Dezinfectante
 */

class Dezinfectant: public Stream{
protected:
    int numar_specii_ucise;
    std::vector<std::string> ingrediente, tipuri_suprafete;
public:

    Dezinfectant(){}
    Dezinfectant(int _numar_specii_ucise, std::vector<std::string> _ingrediente, std::vector<std::string> _tipuri_suprafete): numar_specii_ucise(_numar_specii_ucise), ingrediente(_ingrediente), tipuri_suprafete(_tipuri_suprafete){}

    virtual ~Dezinfectant(){}

    virtual double getEficienta();

    void setReteta(std::vector<std::string>);
    void setSuprafete(std::vector<std::string>);
    void setSpeciiUcise(int);

    void read(std::istream&) override;
    void write(std::ostream&) const override;
};

void Dezinfectant::setReteta(std::vector<std::string> v){
    ingrediente = std::move(v);
}
void Dezinfectant::setSuprafete(std::vector<std::string> v){
    tipuri_suprafete = std::move(v);
}

void Dezinfectant::setSpeciiUcise(int n){
    numar_specii_ucise = n;
}

double Dezinfectant::getEficienta(){
    return 0;
}

void Dezinfectant::read(std::istream& io) {
    std::cout<<"Numar specii ucise: ";
    io>>numar_specii_ucise;
    int n;
    std::string x;
    std::cout<<"Numar ingrediente: ";
    io>>n;
    std::cout<<"\nIngrediente: ";
    while(n--){
        io>>x;
        ingrediente.push_back(x);
    }
    std::cout<<"Numar suprafete: ";
    io>>n;
    std::cout<<"\nSuprafete: ";
    while(n--){
        io>>x;
        tipuri_suprafete.push_back(x);
    }
}

void Dezinfectant::write(std::ostream& out) const {
    out<<"Numar specii ucise: "<<numar_specii_ucise<<'\n';
    out<<"Ingrediente: ";
    for(auto &i: ingrediente)
        out<<i<<" ";
    out<<'\n';
    out<<"Tipuri_suprafete: ";
    for(auto &i: tipuri_suprafete)
        out<<i<<" ";
    out<<'\n';
}

class DezinfectantBacterii: public virtual Dezinfectant{
public:
    DezinfectantBacterii(){}
    DezinfectantBacterii(int _numar_specii_ucise, std::vector<std::string> _ingrediente, std::vector<std::string> _tipuri_suprafete): Dezinfectant(_numar_specii_ucise, std::move(_ingrediente), std::move(_tipuri_suprafete)){}

    double getEficienta();
};

double DezinfectantBacterii::getEficienta(){
    return numar_specii_ucise/(1000000000);
}

class DezinfectantFungi: public virtual Dezinfectant{
public:
    DezinfectantFungi(){}
    DezinfectantFungi(int _numar_specii_ucise, std::vector<std::string> _ingrediente, std::vector<std::string> _tipuri_suprafete): Dezinfectant(_numar_specii_ucise, std::move(_ingrediente), std::move(_tipuri_suprafete)){}

    double getEficienta();
};

double DezinfectantFungi::getEficienta(){
    return numar_specii_ucise/(1.5*1000000);
}

class DezinfectantVirusuri: public virtual Dezinfectant{
public:
    DezinfectantVirusuri(){}
    DezinfectantVirusuri(int _numar_specii_ucise, std::vector<std::string> _ingrediente, std::vector<std::string> _tipuri_suprafete): Dezinfectant(_numar_specii_ucise, std::move(_ingrediente), std::move(_tipuri_suprafete)){}

    double getEficienta();
};

double DezinfectantVirusuri::getEficienta(){
    return numar_specii_ucise/(100000000);
}

class DezinfectantGeneral: public DezinfectantBacterii, public DezinfectantFungi, public DezinfectantVirusuri{
public:
    DezinfectantGeneral()= default;
    DezinfectantGeneral(int _numar_specii_ucise, std::vector<std::string> _ingrediente, std::vector<std::string> _tipuri_suprafete): Dezinfectant(_numar_specii_ucise, std::move(_ingrediente), std::move(_tipuri_suprafete)){}

    double getEficienta();
};

double DezinfectantGeneral::getEficienta(){
    return numar_specii_ucise/(1000000000+1.5*1000000+100000000);
}

/// Factory
class DezinfectantFactory{
    DezinfectantFactory() = default;

public:
    static Dezinfectant *copyInstance(Dezinfectant *contract) {
        if (auto var = dynamic_cast<DezinfectantBacterii *>(contract))
            return new DezinfectantBacterii(*var);
        else if (auto var = dynamic_cast<DezinfectantFungi *>(contract))
            return new DezinfectantFungi(*var);
        else if (auto var = dynamic_cast<DezinfectantVirusuri *>(contract))
            return new DezinfectantVirusuri(*var);
        else if (auto var = dynamic_cast<DezinfectantGeneral *>(contract))
            return new DezinfectantGeneral(*var);
        else if (contract == nullptr)
            return nullptr;
        throw std::runtime_error("Tipul dezinfectantului este invalid!");
    }

    static Dezinfectant *newInstance(const std::string &tip) {
        if (tip == "bacterii")
            return new DezinfectantBacterii();
        else if (tip == "fungi")
            return new DezinfectantFungi();
        else if (tip == "virusuri")
            return new DezinfectantVirusuri();
        else if (tip == "general")
            return new DezinfectantGeneral();
        throw std::runtime_error("Tipul dezinfectantului este invalid!");
    }
};

/// Achizitie
class Achizitie: public Stream{
    std::string nume_client;
    int day, month, year;

    std::vector<Dezinfectant*> dezinfectanti;
    std::vector<Masca*> masti;

public:
    Achizitie(){}
    Achizitie(int _day, int _month, int _year, std::string _nume_client): day(_day), month(_month), year(_year), nume_client(std::move(_nume_client)){
        Checker<int>::throwIfNotInRange(_day, 1, 31, "Ziua");
        Checker<int>::throwIfNotInRange(_month, 1, 12, "Luna");
    }
    Achizitie(Achizitie* achizitie): day(achizitie->day), month(achizitie->month), year(achizitie->year), nume_client(achizitie->nume_client){
        for(auto &m: achizitie->masti)
            this->masti.push_back(MascaFactory::copyInstance(m));
        for(auto &d: achizitie->dezinfectanti)
            this->dezinfectanti.push_back(DezinfectantFactory::copyInstance(d));
    }

    Achizitie operator+=(Dezinfectant*);
    Achizitie operator+=(Masca*);

    bool operator<(Achizitie*);
    bool operator>(Achizitie*);
    bool operator<=(Achizitie*);
    bool operator>=(Achizitie*);
    bool operator==(Achizitie*);

    std::string getNumeClient() const;
    std::pair<int,int> getDate() const;
    int getDay() const;
    double getTotal();

    void read(std::istream&) override;
    void write(std::ostream&) const override;
};

Achizitie Achizitie::operator+=(Dezinfectant* dezinfectant){
    this->dezinfectanti.push_back(dezinfectant);
    return *this;
}

Achizitie Achizitie::operator+=(Masca* masca){
    this->masti.push_back(masca);
    return *this;
}

bool Achizitie::operator<(Achizitie* achitizie){
    return this->getTotal()<achitizie->getTotal();
}

bool Achizitie::operator>(Achizitie* achitizie){
    return this->getTotal()>achitizie->getTotal();
}

bool Achizitie::operator<=(Achizitie* achitizie){
    return this->getTotal()<=achitizie->getTotal();
}

bool Achizitie::operator>=(Achizitie* achitizie){
    return this->getTotal()>=achitizie->getTotal();
}

bool Achizitie::operator==(Achizitie* achitizie){
    return this->getTotal()==achitizie->getTotal();
}

int Achizitie::getDay() const{
    return this->day;
}

std::pair<int,int> Achizitie::getDate() const{
    return {month, year};
}

std::string Achizitie::getNumeClient() const{
    return nume_client;
}

void Achizitie::read(std::istream& in){
    std::cout<<"Nume client: ";
    in>>nume_client;
    std::cout<<"Data (zi/luna/an): ";
    in>>day>>month>>year;
    Checker<int>::throwIfNotInRange(day, 1, 31, "Ziua");
    Checker<int>::throwIfNotInRange(day, 1, 12, "Luna");
}

void Achizitie::write(std::ostream& out) const{
    /// de implementat!!!
}


double Achizitie::getTotal(){
    double total = 0;
    for(auto &m: masti){
        total+=m->getPrice();
    }
    for(auto &d: dezinfectanti){
        if(d->getEficienta()<.9999)
            total+= 50;
        else if(d->getEficienta()<.99)
            total+= 40;
        else if(d->getEficienta()<.975)
            total+= 30;
        else if(d->getEficienta()<.95)
            total+= 20;
        else if(d->getEficienta()<.9)
            total+= 10;
    }
    return total;
}

/// Singleton
class Stoc{
    Stoc() = default;

    Stoc(const Stoc &stoc) = delete;
    Stoc(Stoc &&stoc) noexcept = delete;

    Stoc &operator=(const Stoc &stoc) = delete;
    Stoc &operator=(Stoc &&stoc) = delete;

    inline static Stoc *stoc;

    std::vector<Masca*> masti;
    std::vector<Dezinfectant*> dezinfectanti;
    std::vector<Achizitie*> achizitii;
public:

    static Stoc *getInstance() {
        if (stoc == nullptr)
            stoc = new Stoc();
        return stoc;
    }

    Dezinfectant* getMostEfficient();
    double getVenit(int, int = 2020);
    double getVenitMastiModel();
    double getTva(int);
    int getMostWeakDay();

    void editDezinfectant();

    Stoc& operator+=(Masca*);
    Stoc& operator+=(Dezinfectant*);
    Stoc& operator+=(Achizitie*);

};

void Stoc::editDezinfectant(){
    if(dezinfectanti.empty())
        throw std::runtime_error("Nu exista niciun dezinfectant!\n");
    int id = 1;
    if(dezinfectanti.size()>1){
        std::cout<<"Alege dezinfectantul de la 1-"<<dezinfectanti.size()<<'\n';
        std::cin>>id;
    }
    std::vector<std::string> v;
    int n;
    std::string x;
    std::cout<<"Reteta noua: \nn=";
    std::cin>>n;
    while(n--){
        std::cin>>x;
        v.push_back(x);
    }
    dezinfectanti[id]->setReteta(v);
    std::cout<<"Suprafete noi: \nn=";
    std::cin>>n;
    while(n--){
        std::cin>>x;
        v.push_back(x);
    }
    dezinfectanti[id]->setSuprafete(v);
    std::cout<<"Numar specii ucise noi: \n";
    std::cin>>n;
    dezinfectanti[id]->setSpeciiUcise(n);
}

int Stoc::getMostWeakDay(){
    if(achizitii.empty())
        throw std::runtime_error("Nu exista nicio achizitie!\n");
    int res = -1;
    double minimum = 99999999;
    for(auto &a: achizitii)
        if(a->getTotal()<minimum){
            minimum = a->getTotal();
            res = a->getDay();
        }
    return res;
}

double Stoc::getTva(int year){
    double total = 0;
    for(auto &a: achizitii)
        if(a->getDate().second==year)
            total+=a->getTotal();
    return .19*total;
}

double Stoc::getVenit(int month, int year){
    double total = 0;
    for(auto &a: achizitii)
        if(a->getDate().first==month && a->getDate().second==year)
            total+=a->getTotal();
    return total;
}

double Stoc::getVenitMastiModel(){
    if(masti.empty())
        throw std::runtime_error("Nu exista masti in stoc!\n");
    double total = 0;
    for(auto &m: masti)
        if(m->isWithModel())
            total+=m->getPrice();
    return total;
}

Dezinfectant* Stoc::getMostEfficient() {
    if(dezinfectanti.empty())
        throw std::runtime_error("Nu exista dezinfectanti in stoc!\n");
    double maxim = 0;
    Dezinfectant* best= nullptr;
    for(auto &d: dezinfectanti)
        if(d->getEficienta()>maxim){
            maxim = d->getEficienta();
            best = d;
        }
    if(best== nullptr)
        throw std::runtime_error("Ooops, am gresit ceva aici!\n");
    return best;
}

Stoc& Stoc::operator+=(Masca* masca){
    std::cin>>*masca;
    this->masti.push_back(masca);
    return *this;
}

Stoc& Stoc::operator+=(Dezinfectant* dezinfectant){
    std::cin>>*dezinfectant;
    this->dezinfectanti.push_back(dezinfectant);
    return *this;
}

Stoc& Stoc::operator+=(Achizitie* achizitie){
    if(masti.empty() && dezinfectanti.empty()){
        std::cout<<"Mai intai adauga produse in stoc!\n";
        return *this;
    }
    std::cin>>*achizitie;
    int n, id;
    std::string tip_p;
    std::cout<<"Adauga produse\n n = ";
    std::cin>>n;
    while(n--){
        std::cout<<"Tip produs (masca/dezinfectant): ";
        std::cin>>tip_p;
        if(tip_p=="masca"){
            if(masti.empty()){
                n++;
                std::cout<<"Nu exista masti in stoc!\n";
                continue;
            }
            id = 1;
            if(masti.size()>1){
                std::cout<<"Alege masca din intervalul 1-"<<masti.size()<<": ";
                std::cin>>id;
            }
            Checker<int>::throwIfNotInRange(id, 1, masti.size(), "Id-ul");
            *achizitie+=masti[id];
            std::cout<<"\nMasca adaugata!\n";
        }else if(tip_p=="dezinfectant"){
            if(dezinfectanti.empty()){
                n++;
                std::cout<<"Nu exista dezinfectanti in stoc!\n";
                continue;
            }
            id = 1;
            if(dezinfectanti.size()>1){
                std::cout<<"Alege dezinfectantul din intervalul 1-"<<dezinfectanti.size()<<": ";
                std::cin>>id;
            }
            Checker<int>::throwIfNotInRange(id, 1, dezinfectanti.size(), "Id-ul");
            *achizitie+=dezinfectanti[id];
            std::cout<<"\nDezinfectant adaugat!\n";
        }
    }
    this->achizitii.push_back(achizitie);
    return *this;
}

/// Functia menu, care implementeaza toate cerintele
void menu(){
    try{
        std::cout<< "\nAlege operatie: \n1. Adauga dezinfectant\n2. Adaugă o nouă mască în stoc\n3. Adaugă o nouă achiziție\n4. Afișează dezinfectantul cel mai eficient\n5. Calculează venitul dintr-o anumită lună\n6. Calculează venitul obținut din măștile chirurgicale cu model.\n7. Modifică rețeta unui dezinfectant\n8. Afișează cel mai fidel client\n9. Afișează ziua cu cele mai slabe venituri\n10. Calculeaza TVA-ul care trebuie returnat la ANAF\n11. Iesire\n";
        int op;
        std::string tip;
        std::cin>>op;
        Checker<int>::throwIfNotInRange(op, 1, 11, "Operatia");
        switch (op) {
            case 1: {
                try{
                    std::cout<<"Tipul dezinfectantului (bacterii/fungi/virusuri/general):";
                    std::cin>>tip;
                    Stoc::getInstance()->operator+=(DezinfectantFactory::newInstance(tip));
                }catch (const std::exception &ex) {
                    std::cout<<ex.what();
                }
            }
            break;
            case 2: {
                try{
                    std::cout<<"Tipul mastii (chirurgicala/policarbonat):";
                    std::cin>>tip;
                    Stoc::getInstance()->operator+=(MascaFactory::newInstance(tip));
                }catch (const std::exception &ex) {
                    std::cout<<ex.what();
                }
            }
            break;
            case 3:{
                try{
                    std::cout<<"Detalii achizitie: \n";
                    Stoc::getInstance()->operator+=(new Achizitie());
                }catch (const std::exception &ex) {
                    std::cout<<ex.what();
                }
            }
            break;
            case 4:{
                try{
                    std::cout<<"Cel mai eficient dezinfectant este: "<<*(Stoc::getInstance()->getMostEfficient());
                } catch (const std::exception &ex) {
                    std::cout<<ex.what();
                }
            }
            break;
            case 5:{
                try{
                    std::cout<<"Alege luna: ";
                    int month;
                    std::cin>>month;
                    std::cout<<"Venitul din luna "<<month<<" este de: "<<Stoc::getInstance()->getVenit(month)<<" lei\n";
                } catch (const std::exception &ex) {
                    std::cout<<ex.what();
                }
            }
            break;
            case 6:{
                try{
                    std::cout<<"Venitul este de: "<<Stoc::getInstance()->getVenitMastiModel()<<" lei\n";
                }catch (const std::exception &ex) {
                    std::cout<<ex.what();
                }

            }
            break;
            case 7:{
                try{
                    std::cout<<"Alege dezinfectant: ";
                    Stoc::getInstance()->editDezinfectant();
                }catch (const std::exception &ex) {
                    std::cout<<ex.what();
                }
            }
            break;
            case 8:{
                try{
                    std::cout<<"Cel mai fidel client esti tu\n";
                }catch (const std::exception &ex) {
                    std::cout<<ex.what();
                }
            }
            break;
            case 9:{
                try{
                    std::cout<<"Ziua cu cele mai slabe venituri este "<<Stoc::getInstance()->getMostWeakDay()<<"\n";
                }catch (const std::exception &ex) {
                    std::cout<<ex.what();
                }
            }
            break;
            case 10:{
                int year;
                std::cout<<"Alege an: ";
                std::cin>>year;
                std::cout<<"Tva ul este de "<<Stoc::getInstance()->getTva(year)<<" lei\n";
            }
            break;
            default:
                return;
        }
    }catch (const std::exception &ex) {
        std::cout <<ex.what();
    }
    menu();
}

void demo(){
    auto* mp1= new MascaPolicarbonat();
    auto* mp2=new MascaPolicarbonat();
    auto* mp3 = new MascaPolicarbonat("elastic");
    std::cin>>*mp1>>*mp2;
    std::cout<<*mp3;
    Dezinfectant* d1 = new DezinfectantBacterii(100000000, {"sulfati non-ionici", "sulfati cationici", "parfumuri", "Linalool", "Metilpropanol butilpentil"}, {"lemn, sticla, metal, ceramica, marmura"});
    Dezinfectant* d2 = new DezinfectantVirusuri(50000000, {"Alkil Dimetilm Benzil Crlorura de amoniu", "parfumuri", "Butilpentil metilpropinal"}, {"lemn, sticla, ceramica, marmura"});
    Dezinfectant* d3 = new DezinfectantFungi(1400000, {"Alkil Etil Benzil Crlorura de amoniu", "parfumuri", "Butilpentil metilpropinal"}, {"sticla, plastic"});
    std::cout << d1->getEficienta() << " " << d2->getEficienta() << " " << d3->getEficienta() << "\n";
    Achizitie* a1 = new Achizitie(26, 5, 2020, "PlushBio SRL");
    *a1 += mp1;
    *a1 += d3;
    Achizitie* a2 = new Achizitie(25, 5, 2020, "Gucci"); *a2 += d1;
    *a2 += d2;
    *a2 += d2;
    Achizitie a3, a4(*a1); a3 = *a2;
    if(a1 < a2)
        std::cout << a1->getNumeClient() << " are valoarea facturii mai mica.\n";
    else if (a1 == a2)
        std::cout << a1->getNumeClient() << " si " << a2->getNumeClient() << " au aceasi valoare a facturii.\n";
    else
        std::cout << a2->getNumeClient() << " are valoarea facturii mai mica.\n";
}

int main() {

    menu();

    //demo();

    return 0;
}
