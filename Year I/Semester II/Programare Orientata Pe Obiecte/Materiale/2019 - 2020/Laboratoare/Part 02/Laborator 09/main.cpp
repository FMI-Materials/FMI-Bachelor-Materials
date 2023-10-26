#include <iostream>
#include <cmath>
#include <string>
#include <vector>
#include <set>

using namespace std;

class Masina
{
protected:
    int an, viteza;
    string nume;
    float greutate;

public:
    Masina(int _an = 0, int _viteza = 0, string _nume = "", float _greutate = 0) : an(_an), viteza(_viteza), nume(_nume), greutate(_greutate) {};
    virtual float get_Autonomie() = 0;
    virtual ~Masina() {}
};

class ElectricCar : virtual public Masina
{
protected:
    int BatteryCapacity;

public:
    ElectricCar(int _an = 0, int _viteza = 0, string _nume = "", float _greutate = 0, int _batteryCapacity = 0) : Masina(_an, _viteza, _nume, _greutate), BatteryCapacity(_batteryCapacity) {};
    float get_Autonomie()
    {
        return static_cast<float>(BatteryCapacity) / (greutate * greutate);
    }
    friend ostream& operator<<(ostream& out, const ElectricCar& e);
    friend istream& operator>>(istream& in, ElectricCar& e);
    ~ElectricCar() {}
};

istream& operator>>(istream& in, ElectricCar& e)
{
    string _nume;
    int _batteryCapacity;
    int _an;
    int _greutate;
    in >> _nume >> _batteryCapacity >> _an >> _greutate;
    e.nume = _nume;
    e.BatteryCapacity = _batteryCapacity;
    e.an = _an;
    e.greutate = _greutate;
    return in;
}
ostream& operator<<(ostream& out, const ElectricCar& e)
{
    out << e.an << ' ' << e.BatteryCapacity << ' ' << e.nume << ' ' << e.greutate << '\n';
    return out;
}

class MasinaCombustibil : virtual public Masina
{
protected:
    int capacitate_rezervor;
    string tip_combustibil;

public:
    MasinaCombustibil(int _an = 0, int _viteza = 0, string _nume = "", float _greutate = 0, int _capacitate_rezervor = 0, string _tip_combustibil = "") : Masina(_an, _viteza, _nume, _greutate), capacitate_rezervor(_capacitate_rezervor), tip_combustibil(_tip_combustibil) {};
    float get_Autonomie()
    {
        return static_cast<float>(capacitate_rezervor) / (greutate * greutate);
    }
    ~MasinaCombustibil() {}
};

class MasinaHibrid : public ElectricCar, public MasinaCombustibil
{

public:
    MasinaHibrid(int _an = 0, int _viteza = 0, string _nume = "", float _greutate = 0, int BatteryCapacity = 0, int _capacitate_rezervor = 0, string _tip_combustibil = "Benzina") : MasinaCombustibil(_an, _viteza, _nume, _greutate, _capacitate_rezervor),
                                                                                                                                                                                     Masina(_an, _viteza, _nume, _greutate), ElectricCar(_an, _viteza, _nume, _greutate, BatteryCapacity) {};
    float get_Autonomie()
    {
        return ElectricCar::get_Autonomie() + MasinaCombustibil::get_Autonomie();
    }
    ~MasinaHibrid() {}
};

class Tranzactie
{
    string nume_cumparator, data;
    vector<Masina*> achizitii;

public:
    Tranzactie(string nume_cumparator = "", string data = "") : nume_cumparator(nume_cumparator), data(data) {}
    ~Tranzactie()
    {
        /*
        for (auto achizitie : achizitii)
            delete& achizitie;
        achizitii.clear();*/
    }
    Tranzactie(const Tranzactie& other)
    {
        nume_cumparator = other.nume_cumparator;
        data = other.data;
        for (auto& it : other.achizitii) achizitii.push_back(it);
    }
    void setAchizitii(vector <Masina*> masini)
    {
        for (auto achizitie : achizitii)
            delete& achizitie;
        achizitii.clear();
        for (auto& masina : masini) achizitii.push_back(masina);
    }
    Tranzactie& operator =(const Tranzactie& other)
    {
        if (this == &other) return *this;
        nume_cumparator = other.nume_cumparator;
        data = other.data;
        for (auto achizitie : achizitii)
            delete& achizitie;
        achizitii.clear();
        for (auto& it : other.achizitii) achizitii.push_back(it);
    }

    inline vector<Masina*> get_Achizitii() const { return achizitii; }
};

class Manager
{
private:
    vector<Tranzactie> tranzactii;
    set<ElectricCar> masiniElectrice;
    set<MasinaCombustibil> masiniCombustibil;
    set<MasinaHibrid> masiniHibrid;
    Manager()
    {
    }
    static Manager* pInstanta;

public:
    static Manager* get_Instance()
    {
        if (!pInstanta)
        {
            pInstanta = new Manager();
        }
        return pInstanta;
    }
    Manager(Manager const&) = delete;
    Manager& operator=(const Manager&) = delete;
    void add_Tranzactie(Tranzactie foo)
    {
        tranzactii.push_back(foo);

        /*
        vector<Masina*> achizitii = foo.get_Achizitii();

        for (auto& achizitie : achizitii)
        {

            if (MasinaHibrid* hibrid = dynamic_cast<MasinaHibrid*>(achizitie))
            {
                masiniHibrid.insert(MasinaHibrid(*hibrid));
            }
            else if (ElectricCar* electrica = dynamic_cast<ElectricCar*>(achizitie))
            {
                masiniElectrice.insert(ElectricCar(*electrica));
            }
            else if (MasinaCombustibil* combustibil = dynamic_cast<MasinaCombustibil*>(achizitie))
            {
                masiniCombustibil.insert(MasinaCombustibil(*combustibil));
            }
        }
        */
    }

    //inline set<ElectricCar> get_MasiniElectrice() const { return masiniElectrice; }
};

Manager* Manager::pInstanta = nullptr;

int main()
{
    ElectricCar electricCar;
    cin >> electricCar;
    cout << electricCar;

    vector<Masina*> masini;
    masini.push_back(new ElectricCar());
    masini.push_back(new ElectricCar(electricCar));
    Tranzactie t("Ana", "2020-05-09");
    t.setAchizitii(masini);

    Manager* manager = Manager::get_Instance();
    manager->add_Tranzactie(t);

    cout << electricCar.get_Autonomie();

    /*
    set<ElectricCar> electrice = manager->get_MasiniElectrice();
    for (auto& electric : electrice)
        cout << electric << endl;
        */
}
