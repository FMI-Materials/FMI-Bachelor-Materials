#include <iostream>
#include <stdlib.h>
#include <list>
using namespace std;

/**
Referinta -> Bibliografie -> Articol
                          -> Carte
          -> Webografie
*/

list<string> defaultList(){
    list<string> temp;
    temp.push_back("***");
    return temp;
}

class Referinte{

public:
    virtual ~Referinte(){};
    virtual void citire(istream &in) = 0;
    virtual void afisare(ostream &out) = 0;
    friend istream& operator >> (istream&, Referinte&);
    friend ostream& operator << (ostream&, Referinte&);
};
istream& operator>> (istream& in, Referinte& x){
    x.citire(in);
    return in;
}
ostream& operator<< (ostream& out, Referinte& x){
    x.afisare(out);
    return out;
}

class Bibliografie : public Referinte {
protected:
    list <string> autori;
    string titlu;
    int anPublicare;
public:
    Bibliografie (list<string>,string,int);
    ~Bibliografie(){};
    void citire (istream& in);
    void afisare (ostream &out);
    int get_anPublicare(){return anPublicare;}
    string get_titlu() {return titlu;}
    friend istream& operator >> (istream&, Bibliografie&);
    friend ostream& operator << (ostream&, Bibliografie&);
};

Bibliografie::Bibliografie(list<string> a=defaultList(),string t="", int an=0){
	list<string>::iterator i;
	for (i = a.begin(); i != a.end(); ++i) {
		autori.push_back(*i);
	}
	if (*autori.begin() == "***")
        autori.pop_front();
	titlu=t;
	anPublicare = an;
}
void Bibliografie::citire(istream& in){
    string autor;
    int nr;
    cout<<"Dati numarul autorilor: ";
    in>>nr;
    in.get();
    for (int i=0;i<nr;i++){
        cout<<"Dati numele autorului "<<i<<": ";
        getline(in,autor);
        autori.push_back(autor);
    }
    cout<<"Dati titlul: ";
    getline(in,titlu);
    cout<<"Dati anul publicarii: ";
    in>>anPublicare;
}
void Bibliografie::afisare(ostream& out){
    list<string>::iterator i;
	for (i = autori.begin(); i != autori.end(); ++i) {
        out<<(*i)<<", ";
	}
	out<<titlu<<", ";
	out<<anPublicare;
}
istream& operator>> (istream& in, Bibliografie& x){
    x.citire(in);
    return in;
}
ostream& operator<< (ostream& out, Bibliografie& x){
    x.afisare(out);
    return out;
}

class Articol : public Bibliografie {
private:
    string numeRevista;
    string nrRevista;
    string paginiRevista;
public:
    Articol(list<string>,string,int,string,string,string);
    ~Articol(){};
    void citire(istream&);
    void afisare(ostream&);
    friend istream& operator >> (istream&, Articol&);
    friend ostream& operator << (ostream&, Articol&);
};
Articol::Articol(list<string> a=defaultList(),string t="", int an=0, string numeR = "", string nrRev = "", string pag=""):Bibliografie(a,t,an){
    numeRevista = numeR;
    nrRevista = nrRev;
    paginiRevista = pag;
}
void Articol::citire(istream& in){
    Bibliografie::citire(in);
    in.get();
    cout<<"Dati numele revistei: ";
    getline(in,numeRevista);
    cout<<"Dati numarul revistei: ";
    in>>nrRevista;
    in.get();
    cout<<"Introduceti paginile sau intervalul de pagini: ";
    getline(in,paginiRevista);
}
void Articol::afisare(ostream& out){
    out<<"Articol: \n";
    Bibliografie::afisare(out);
    out<<", "<<numeRevista<<", ";
    out<<nrRevista<<", ";
    out<<paginiRevista<<".\n";
}
istream& operator>> (istream& in, Articol& x){
    x.citire(in);
    return in;
}
ostream& operator<< (ostream& out, Articol& x){
    x.afisare(out);
    return out;
}

class Carte : public Bibliografie{
private:
    string numeEditura;
    string orasEditura;
public:
    Carte(list<string>,string,int,string,string);
    ~Carte(){}
    void citire(istream& in);
    void afisare(ostream& out);
    friend istream& operator >> (istream&, Carte&);
    friend ostream& operator << (ostream&, Carte&);
};
Carte::Carte(list<string> a=defaultList(),string t="", int an=0, string numeEditura = "", string oras = ""):Bibliografie(a,t,an){
    this->numeEditura = numeEditura;
    orasEditura = oras;
}
void Carte::citire(istream& in){
    Bibliografie::citire(in);
    in.get();
    cout<<"Dati numele editurii: ";
    getline(in,numeEditura);
    cout<<"Dati orasul editurii: ";
    getline(in,orasEditura);
}
void Carte::afisare(ostream& out){
    out<<"Carte: \n";
    Bibliografie::afisare(out);
    out<<", "<<numeEditura<<", ";
    out<<orasEditura<<".\n";
}
istream& operator>> (istream& in, Carte& x){
    x.citire(in);
    return in;
}
ostream& operator<< (ostream& out, Carte& x){
    x.afisare(out);
    return out;
}

class Webografie : public Referinte{
private:
    string numeProprietar;
    string titlu;
    string url;
public:
    Webografie (string, string, string);
    ~Webografie(){}
    void citire(istream& in);
    void afisare(ostream& out);
    string get_proprietar(){return numeProprietar;}
    string get_titlu() {return titlu;}
    friend istream& operator >> (istream&, Webografie&);
    friend ostream& operator << (ostream&, Webografie&);
};
Webografie::Webografie(string nume = "", string titlu = "", string url = ""){
    this->numeProprietar = nume;
    this->titlu = titlu;
    this->url=url;
}
void Webografie::citire(istream& in){
    cout<<"Dati numele proprietarului: ";
    in.get();
    getline(in,numeProprietar);
    cout<<"Dati titlul: ";
    getline(in,titlu);
    cout<<"Dati url: ";
    getline(in,url);
}
void Webografie::afisare(ostream& out){
    out<<"Web: \n";
    out<<numeProprietar<<", "<<titlu<<", "<<url<<".\n";
}
istream& operator>> (istream& in, Webografie& x){
    x.citire(in);
    return in;
}
ostream& operator<< (ostream& out, Webografie& x){
    x.afisare(out);
    return out;
}
void tip(Referinte *&p, int &i) {
    string s;
    cout<<"\n";
    cout<<"Introduceti tipul referintei "<<i+1<<": ";
    cin>>s;
    try
    {
        if(s=="articol")
        {
                p=new Articol;
                cin>>*p;
                i++;
        }
        else
            if(s=="carte")
            {
                p=new Carte;
                cin>>*p;
                i++;
            }
            else
                if(s=="link")
                {
                    p=new Webografie;
                    cin>>*p;
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
        cout<<"Nu ati introdus un tip valid. Incercati articol, carte sau link.\n ";
    }
}

void menu_output()
{
    cout<<"\nReferinte\n";
    cout<<"\n\t\tMENIU:";
    cout<<"\n===========================================\n";
    cout<<"\n";
    cout<<"1. Citeste referintele";
    cout<<"\n";
    cout<<"2. Afiseaza referintele";
    cout<<"\n";
    cout<<"3. Cauta dupa an";
    cout<<"\n";
    cout<<"4. Cauta dupa titlu";
    cout<<"\n";
    cout<<"5. Cauta dupa proprietar";
    cout<<"\n";
    cout<<"0. Iesire.";
    cout<<"\n";
}

void menu()
{
    int option;
    option=0;
    int n=0;
    Referinte **v;
    do
    {
        menu_output();
        cout<<"\nIntroduceti numarul actiunii: ";
        cin>>option;
        if (option==1)
        {
            cout<<"Introduceti numarul de obiecte citite: ";
            cin>>n;
            v=new Referinte*[n];
            if (n>0)
            {
                for(int i=0;i<n;)
                    tip(v[i],i);
            }
            else
                cout<<"Numarul introdus trebuie sa fie pozitiv.\n";
        }
        if (option==2)
        {
            for(int i=0;i<n;i++)
            {
                cout<<"\n"<<*v[i];
                cout<<"--------------------------\n";
            }
        }
        if (option==3)
        {
            if (n>0){
                int anCautat;
                cout<<"Dati anul cautat: ";
                cin>>anCautat;
                for(int i=0;i<n;i++)
                {
                    ///incerc cast catre articol
                    Articol *p1=dynamic_cast<Articol*>(v[i]);
                    ///incerc cast catre carte
                    Carte *p2=dynamic_cast<Carte*>(v[i]);

                    if (p1)
                        if (p1->get_anPublicare() == anCautat)
                            cout<<*v[i]<<"\n";
                    if (p2)
                        if (p2->get_anPublicare() == anCautat)
                            cout<<*v[i]<<"\n";

                }
            }
            else{
                cout<<"Nu s-au citit referinte. Reveniti la actiunea 1.\n";
            }
        }
        if (option==4)
        {
            if (n>0){
                string titluCautat;
                cout<<"Dati titlul cautat: ";
                cin>>titluCautat;
                for(int i=0;i<n;i++)
                {
                    ///incerc cast catre articol
                    Articol *p1=dynamic_cast<Articol*>(v[i]);
                    ///incerc cast catre carte
                    Carte *p2=dynamic_cast<Carte*>(v[i]);
                    ///incerc cast catre link
                    Webografie *p3=dynamic_cast<Webografie*>(v[i]);
                    if (p1){
                        size_t gasit = p1->get_titlu().find(titluCautat);
                        if (gasit != string::npos){///npos maximum value for size_t
                             cout<<*v[i]<<"\n";
                        }
                    }
                    if (p2){
                        size_t gasit = p2->get_titlu().find(titluCautat);
                        if (gasit != string::npos){
                             cout<<*v[i]<<"\n";
                        }
                    }
                    if (p3){
                        size_t gasit = p3->get_titlu().find(titluCautat);
                        if (gasit != string::npos){
                             cout<<*v[i]<<"\n";
                        }
                    }
                }
            }
            else{
                cout<<"Nu s-au citit referinte. Reveniti la actiunea 1.\n";
            }
        }
        if (option==5)
        {
            if (n>0){
                string proprietarCautat;
                cout<<"Dati proprietarul cautat: ";
                cin>>proprietarCautat;
                for(int i=0;i<n;i++)
                {

                    ///incerc cast catre link
                    Webografie *p1=dynamic_cast<Webografie*>(v[i]);
                    if (p1){
                        size_t gasit = p1->get_proprietar().find(proprietarCautat);
                        if (gasit != string::npos){
                             cout<<*v[i]<<"\n";
                        }
                    }
                }
            }
            else{
                cout<<"Nu s-au citit referinte. Reveniti la actiunea 1.\n";
            }
        }
        if (option==0)
        {
            cout<<"\nEXIT\n\n";
        }
        if (option<0||option>5)
        {
            cout<<"\nSelectie invalida\n";
        }
        cout<<"\n";
        system("pause"); ///Pauza - Press any key to continue...
        system("cls");   ///Sterge continutul curent al consolei
    }
    while(option!=0);
}
int main()
{
    menu();

    return 0;
}
