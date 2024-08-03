#include <iostream>
#include <list>
#include <stdlib.h>
using namespace std;

class Avocat{
protected:
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
    virtual void afisare(ostream &out);
    virtual void citire(istream &in);
    friend ostream& operator<<(ostream& out, Avocat&);
    friend istream& operator>>(istream& in, Avocat&);
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
void Avocat::citire(istream& in){
    cout<<"Dati numele: ";
    in>>nume;
    cout<<"Dati pretul pe ora: ";
    in>>pretOra;
    cout<<"Dati numar procese: ";
    in>>nrProcese;
}
istream& operator>>(istream& in, Avocat& f){
    f.citire(in);
    return in;
}
ostream& operator<<(ostream& out, Avocat& f)
{
    f.afisare(out);
    return out;
}
class AvocatDerivat:public Avocat{
    int test;
public:
    AvocatDerivat(string n="",int pret=0,int nrP=0,int x=0):Avocat(n,pret,nrP){
        test=x;
    }
    void afisare(ostream &out);
    void citire(istream &in);
    friend ostream& operator<<(ostream& out, AvocatDerivat&);
    friend istream& operator>>(istream& in, AvocatDerivat&);
};
void AvocatDerivat::afisare(ostream &out){
    Avocat::afisare(out);
    out<<"Test: ";
    out<<test;
}
void AvocatDerivat::citire(istream& in){
    Avocat::citire(in);
    cout<<"Dati test: ";
    in>>test;
}
istream& operator>>(istream& in, AvocatDerivat& f){
    f.citire(in);
    return in;
}
ostream& operator<<(ostream& out, AvocatDerivat& f)
{
    f.afisare(out);
    return out;
}
bool compare(const Avocat& f, const Avocat& s){
    return f.get_nrProcese()<s.get_nrProcese();
}


void tip(Avocat *&p, int &i, list<Avocat*> &l) {
    string s;
    cout<<"\n";
    cout<<"Introduceti tipul avocatului "<<i+1<<": ";
    cin>>s;
    try
    {
        if(s=="avocat")
        {
                p=new Avocat;
                cin>>*p;
                l.push_back(*&p);
                i++;
        }
        else
            if(s=="avocatDerivat")
            {
                p=new AvocatDerivat;
                cin>>*p;
                l.push_back(*&p);
                i++;
            }
            else
                throw 10;
    }
    catch (bad_alloc var)
    {
        cout << "Allocation Failure\n";
        exit(EXIT_FAILURE);
    }
    catch(int j)
    {
        cout<<"Nu ati introdus un post valid. Incercati avocat sau avocatDerivat.\n ";
    }
}

int main()
{
    list <Avocat *> barou; ///folosesc list din STL
	Avocat **v;
	int n;
	cout<<"Dati nr de obiecte:";
	cin>>n;
	v=new Avocat*[n];
	for(int i=0;i<n;)
        tip(v[i],i,barou);
    cout<<"\nAfisam:\n";

	list<Avocat*>::iterator i; ///Creez un iterator
	cout << "---------------------------------------------------------------\n";
	for (i = barou.begin(); i != barou.end(); ++i) { ///De la inceputul listei pana la final, parcurg si afisez continutul iteratorului
		cout << (**i);
	}

    return 0;
}
