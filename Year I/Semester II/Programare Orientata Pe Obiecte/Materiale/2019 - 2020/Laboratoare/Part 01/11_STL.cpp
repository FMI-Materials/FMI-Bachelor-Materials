#include <iostream>
#include <list>
using namespace std;

class Avocat{
    string nume;
    int pretOra;
    int nrProcese;
public:
    Avocat(string, int, int);
    int get_nrProcese() const{
        return nrProcese;
    }
    int get_pretOra() {
    return pretOra;
    }
    void afisare(ostream &out);
    friend ostream& operator<<(ostream& out, Avocat&);
    bool operator<(Avocat &z){
        return pretOra<z.get_pretOra();
    }

};
Avocat::Avocat(string n="", int pret=0, int nrP=0){
    nume=n;
    pretOra=pret;
    nrProcese=nrP;
}
void Avocat::afisare(ostream &out){
    out<<"Nume avocat: "<<nume<<"\n";
    out<<"Pretul perceput pe ora: "<<pretOra<<"\n";
    out<<"Numarul total de procese: "<<nrProcese<<"\n";
}
ostream& operator<<(ostream& out, Avocat& f)
{
    f.afisare(out);
    return out;
}
bool compare(const Avocat& f, const Avocat& s){
    return f.get_nrProcese()<s.get_nrProcese();
}
int main()
{
    Avocat a1("Avocatul Poporului", 1, 3);
    Avocat a2("Cerbu", 3, 5);
    Avocat a3("Barbu", 2, 2);

    list <Avocat> barou; ///folosesc list din STL
	barou.push_back(a1); ///folosesc push_back din STL pentru a adauga in lista un avocat
	barou.push_back(a2);
	barou.push_back(a3);

	list<Avocat>::iterator i; ///Creez un iterator
	cout << "---------------------------------------------------------------\n";
	for (i = barou.begin(); i != barou.end(); ++i) { ///De la inceputul listei pana la final, parcurg si afisez continutul iteratorului
		cout << (*i);
	}

	barou.sort(); ///Sortez folosind supraincarcarea operatorului < care se bazeaza pe pret

	cout << "---------------------------------------------------------------\n";

	for (i = barou.begin(); i != barou.end(); ++i) { ///Afisez dupa sortare
		cout << (*i);
	}

	barou.sort(compare); ///Sortez folosind supraincarcarea metoda de comparare ce foloseste get_nrProcese const care se bazeaza pe nr procese

	cout << "---------------------------------------------------------------\n";

	for (i = barou.begin(); i != barou.end(); ++i) { ///Afisez dupa sortare
		cout << (*i);
	}
    return 0;
}
