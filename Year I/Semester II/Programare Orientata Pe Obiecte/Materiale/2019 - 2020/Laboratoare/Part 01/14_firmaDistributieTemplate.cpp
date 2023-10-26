#include <iostream>
#include <stdlib.h>
#include <string.h>
using namespace std;

class film
{
protected:
    string nume_film;
    string tip;
    double durata;
public:
    film (string, string, double);
    film (film&);
    virtual ~film();

    virtual void citire (istream &in);
    virtual void afisare(ostream &out);


    film& operator=(film &p);
    friend istream& operator>>(istream&, film&);
    friend ostream& operator<<(ostream&, film&);
    friend class persoane;
};
film::film (string num="", string gen="", double minute=0)
{
    nume_film=num;
    tip=gen;
    try
    {
        if (minute<0)
            throw minute;
    }
    catch (double x)
    {
        cout<<"Eroare in constructor, minutele nu pot fi negative.\n";
        exit(EXIT_FAILURE);
    }
    durata=minute;
}
void film::citire(istream &in)
{
    string x;
    cout<<"Denumire film:";
    in>>x;
    nume_film=x;
    cout<<"Genul filmului:";
    in>>x;
    tip=x;
    cout<<"Durata filmului:";
    string p;
    in>>p;
    double d;
    char *q=new char [p.length()+1];
    strcpy(q,p.c_str());
    d=atof(q);
    try
    {
        if (d<0)
            throw 1;
    }
    catch (int x)
    {
        cout<<"Eroare in setarea duratei, minutele nu pot fi negative.\n";
        exit(EXIT_FAILURE);
    }
    durata=d;
}
void film::afisare(ostream &out)
{
    out<<"Denumire film: "<<nume_film<<"\n";
    out<<"Genul filmului: "<<tip<<"\n";
    out<<"Durata filmului: "<<durata<<"\n";
}
film::film (film &p)
{
    nume_film=p.nume_film;
    tip=p.tip;
    durata=p.durata;
}
film::~film()
{

}
film& film :: operator= (film &x)
{
    if (this!=&x)
    {
        nume_film=x.nume_film;
        tip=x.tip;
        durata=x.durata;
    }
    return *this;
}
istream& operator>>(istream& in,film& f)
{
    f.citire(in);
    return in;
}

ostream& operator<<(ostream& out, film& f)
{
    f.afisare(out);
    return out;
}
///------------------------------------------------------

class persoane
{
protected:
    string cnp;
    string nume_persoana;
    film *filme;
    int nr;
public:
    persoane (string, string, film*,int);
    persoane (persoane&);
    virtual ~persoane();

    int get_numar(){return nr;}
    virtual void citire(istream &in);
    virtual void afisare(ostream &out);
    persoane& operator=(persoane &p);
    friend istream& operator>>(istream&, persoane&);
    friend ostream& operator<<(ostream&, persoane&);

    friend ifstream& operator>>(ifstream&, persoane&);

};

persoane::persoane (string c="",string numep="",film *f=NULL,int nr=0)
{
    try
    {
        for (unsigned int i=0;i<c.length();i++)
            if (c[i]<'0'||c[i]>'9')
                throw 1;
    }
    catch(int i)
    {
        cout<<"Eroare constructor, CNP-ul persoanei poate contine doar cifre.\n";
        exit(EXIT_FAILURE);
    }
    cnp=c;
    nume_persoana=numep;
    filme=new film[nr];
    for(int i=0;i<nr;i++)
        filme[i]=f[i];

}
persoane::persoane(persoane &p)
{
    cnp=p.cnp;
    nume_persoana=p.nume_persoana;
    nr=p.nr;
    filme=new film[nr];
    for(int i=0;i<nr;i++)
        filme[i]=p.filme[i];

}
persoane::~persoane()
{

}
void persoane::citire(istream &in)
{
    string x;
    cout<<"CNP:";
    in>>x;
    cnp=x;
    cout<<"Nume:";
    in>>x;
    nume_persoana=x;
    cout<<"Numarul de filme: ";
    in>>nr;
    filme=new film[nr];
    for(int i=0;i<nr;i++)
        in>>filme[i];
}
void persoane::afisare(ostream &out)
{
    out<<"CNP: "<<cnp<<"\n";
    out<<"Nume: "<<nume_persoana<<"\n";
    out<<"Cele "<<nr<<" filme sunt: "<<"\n";
    int i;
    for(i=0;i<nr-1;i++)
        out<<filme[i]<<"\n";
    if (nr!=0)
        out<<filme[i];
}
persoane& persoane :: operator= (persoane &x)
{
    if (this!=&x)
    {
        cnp=x.cnp;
        nume_persoana=x.nume_persoana;
        nr=x.nr;
        filme=new film[nr];
        for(int i=0;i<nr;i++)
            filme[i]=x.filme[i];
    }
    return *this;
}
istream& operator>>(istream& in,persoane& p)
{
    p.citire(in);
    return in;
}

ostream& operator<<(ostream& out, persoane& p)
{
    p.afisare(out);
    return out;
}
///-------------------------------------------------
class personal:public persoane
{
protected:
    double* procent_incasari;
public:
    personal(string, string, film*,int, double*);
    personal(personal&);
    ~personal();

    void citire(istream &in);
    void afisare(ostream &out);

    personal& operator=(personal &p);
    friend istream& operator>>(istream&, personal&);
    friend ostream& operator<<(ostream&, personal&);

    friend ifstream& operator>>(ifstream&, personal&);
};
personal::personal(string c="",string numep="",film* f=NULL,int n=0,double procent[]=0):persoane(c,numep,f,n)
{
    if (f)
    {
    procent_incasari=new double[nr];
    for (int i=0;i<nr;i++)
        procent_incasari[i]=procent[i];

    }
}
personal::personal(personal &p):persoane(p)
{
   procent_incasari=new double[p.nr];
    for (int i=0;i<p.nr;i++)
        procent_incasari[i]=p.procent_incasari[i];
}
personal::~personal()
{

}
void personal::citire(istream &in)
{
    persoane::citire(in);
    procent_incasari=new double[nr];
    for (int i=0;i<nr;i++)
    {
        cout<<"Introduceti procentul castigat "<<i+1<<": ";
        string p1;
        in>>p1;
        double d;
        char *q=new char [p1.length()+1];
        strcpy(q,p1.c_str());
        d=atof(q);
        try
        {
            if (d<0||d>100)
                throw 1;
        }
        catch (int i)
        {
            cout<<"Eroare la setarea procentului din incasari. Valoarea procentului trebuie sa fie intre 0% si 100%.\n";
            exit(EXIT_FAILURE);
        }
        procent_incasari[i]=d;
    }
}
void personal::afisare(ostream &out)
{
    persoane::afisare(out);
    int i;
    for (i=0;i<nr-1;i++)
        out<<"Procent incasari "<<i+1<<": "<<procent_incasari[i]<<"\n";
    if (nr!=0)
    out<<"Procent incasari "<<i+1<<": "<<procent_incasari[i]<<"\n";
}
personal& personal :: operator=(personal &x)
{
    if(this!=&x)
    {
        persoane::operator=(x);
        for (int i=0;i<x.nr;i++)
            procent_incasari[i]=x.procent_incasari[i];
    }
    return *this;
}
istream& operator>>(istream& in,personal& p)
{
    p.citire(in);
    return in;
}

ostream& operator<<(ostream& out, personal& p)
{
    p.afisare(out);
    return out;
}

///-------------------------------------------------
class regizor:public personal
{
    double* suma_fixa;
public:
    regizor(string, string, film*,int, double*, double*);
    regizor(regizor&);
    ~regizor();

    void citire(istream &in);
    void afisare(ostream &out);

    regizor& operator=(regizor &p);
    friend istream& operator>>(istream&, regizor&);
    friend ostream& operator<<(ostream&, regizor&);
};
regizor::regizor(string c="",string numep="",film* f=NULL,int n=0,double procent[]=0,double suma[]=0):personal(c,numep,f,n,procent)
{
    if (f)
    {
    suma_fixa=new double[nr];
    for (int i=0;i<nr;i++)
        suma_fixa[i]=suma[i];
    }
}
regizor::regizor(regizor &p):personal(p)
{
    suma_fixa=new double[p.nr];
    for (int i=0;i<p.nr;i++)
        suma_fixa[i]=p.suma_fixa[i];
}
regizor::~regizor()
{

}
void regizor::citire(istream &in)
{
    personal::citire(in);
    suma_fixa=new double[nr];
    for (int i=0;i<nr;i++)
    {
        cout<<"Introduceti suma fixa castigata "<<i+1<<": ";
        string p1;
        in>>p1;
        double d;
        char *q=new char [p1.length()+1];
        strcpy(q,p1.c_str());
        d=atof(q);
        suma_fixa[i]=d;
    }
}
void regizor::afisare(ostream &out)
{
    personal::afisare(out);
    int i;
    for (i=0;i<nr-1;i++)
        out<<"Suma fixa "<<i+1<<": "<<suma_fixa[i]<<"\n";
    if (nr!=0)
    out<<"Suma fixa "<<i+1<<": "<<suma_fixa[i]<<"\n";
}
regizor& regizor :: operator=(regizor &x)
{
    if(this!=&x)
    {
        personal::operator=(x);
        for (int i=0;i<x.nr;i++)
            suma_fixa[i]=x.suma_fixa[i];
    }
    return *this;
}

istream& operator>>(istream& in,regizor& p)
{
    p.citire(in);
    return in;
}

ostream& operator<<(ostream& out, regizor& p)
{
    p.afisare(out);
    return out;
}
///-------------------------------------------------
class actor:public personal
{
    bool* principal;
public:
    actor(string, string, film*,int, double*,bool*);
    actor(actor&);
    ~actor();

    bool get_principal(int i){return principal[i];}
    void citire(istream &in);
    void afisare(ostream &out);

    actor& operator=(actor &p);
    friend istream& operator>>(istream&, actor&);
    friend ostream& operator<<(ostream&, actor&);
};
actor::actor(string c="",string numep="",film* f=NULL,int n=0,double procent[]=0,bool princ[]=0):personal(c,numep,f,n,procent)
{
    if (f)
    {
    principal=new bool[nr];
    for (int i=0;i<nr;i++)
        principal[i]=princ[i];
    for (int i=0;i<nr;i++)
        if (principal[i]==1)
            procent_incasari[i]=procent_incasari[i]+10;
    }
}
actor::actor(actor &p):personal(p)
{
    principal=new bool[p.nr];
    for (int i=0;i<p.nr;i++)
        principal[i]=p.principal[i];
}
actor::~actor()
{

}
void actor::citire(istream &in)
{
    personal::citire(in);
    principal=new bool[nr];
    for (int i=0;i<nr;i++)
    {
        cout<<"Actor principal pentru filmul "<<i+1<<": ";
        bool d;
        in>>d;
        principal[i]=d;
        if (d!=0)
            procent_incasari[i]+=10;
    }
}
void actor::afisare(ostream &out)
{
    personal::afisare(out);
    int i;
    for (i=0;i<nr-1;i++)
        out<<"Personaj principal pentru filmul "<<i+1<<": "<<principal[i]<<"\n";
    if (nr!=0)
    out<<"Personaj principal pentru filmul "<<i+1<<": "<<principal[i];
    out<<"\n";
}
actor& actor :: operator=(actor &x)
{
    if(this!=&x)
    {
        personal::operator=(x);
        for (int i=0;i<x.nr;i++)
            principal[i]=x.principal[i];
    }
    return *this;
}

istream& operator>>(istream& in,actor& p)
{
    p.citire(in);
    return in;
}

ostream& operator<<(ostream& out, actor& p)
{
    p.afisare(out);
    return out;
}

///-------------------------------------------------
class tehnic:public personal
{
    string* specializare;
public:
    tehnic(string, string, film*,int, double*,string*);
    tehnic(tehnic&);
    ~tehnic();

    void citire(istream &in);
    void afisare(ostream &out);

    tehnic& operator=(tehnic &p);
    friend istream& operator>>(istream&, tehnic&);
    friend ostream& operator<<(ostream&, tehnic&);
};
tehnic::tehnic(string c="",string numep="",film* f=NULL,int n=0,double procent[]=0,string spec[]=0):personal(c,numep,f,n,procent)
{
    if (f)
    {
    specializare=new string[nr];
    for (int i=0;i<nr;i++)
        specializare[i]=spec[i];
    }
}
tehnic::tehnic(tehnic &p):personal(p)
{
    specializare=new string[nr];
    for (int i=0;i<p.nr;i++)
        specializare[i]=p.specializare[i];
}
tehnic::~tehnic()
{

}
void tehnic::citire(istream &in)
{
    personal::citire(in);
    specializare=new string[nr];
    for (int i=0;i<nr;i++)
    {
        cout<<"Specializare pentru filmul "<<i+1<<": ";
        string d;
        in>>d;
        specializare[i]=d;
    }
}
void tehnic::afisare(ostream &out)
{
    personal::afisare(out);
    int i;
    for (i=0;i<nr-1;i++)
        out<<"Specializare pentru filmul "<<i+1<<": "<<specializare[i]<<"\n";
    if (nr!=0)
        out<<"Specializare pentru filmul "<<i+1<<": "<<specializare[i];
    out<<"\n";
}
tehnic& tehnic :: operator=(tehnic &x)
{
    if(this!=&x)
    {
        personal::operator=(x);
        for (int i=0;i<x.nr;i++)
            specializare[i]=x.specializare[i];
    }
    return *this;
}

istream& operator>>(istream& in,tehnic& p)
{
    p.citire(in);
    return in;
}

ostream& operator<<(ostream& out, tehnic& p)
{
    p.afisare(out);
    return out;
}
/**
film
persoane -> personal -> actor
                     -> regizor
                     -> rehnic
*/

template <class t> class FirmaDistributie
{
    t *v;
    int nr;
public:
    FirmaDistributie(t *p=NULL, int n=0)
    {
        nr=n;
        if (n!=0){
            v=new t[n];
            for(int i=0;i<n;i++)
            {
                v[i]=p[i];
            }
        }
    }
    FirmaDistributie(FirmaDistributie &a)
    {
        nr=a.nr;
        v=new t[nr];
        for(int i=0;i<nr;i++)
        {
            v[i]=a.v[i];
        }
    }
    ~FirmaDistributie()
    {
        delete [] v;
    }

    int get_nr();
    t get_v(int i) {return v[i];}
    friend istream& operator >>(istream &in, FirmaDistributie <t> &g)
    {
        cout<<"Introduceti numarul de persoane implicate: ";
        in>>g.nr;
        g.v=new t[g.nr];
        cout<<"Introduceti obiectele: \n";
        for(int i=0;i<g.nr;i++){
           in>>g.v[i];
           cout<<"\n";
        }
        return in;
    }
    friend ostream& operator <<(ostream &out, FirmaDistributie<t> &g)
    {
        out<<"In firma de distributie se gasesc urmatoarele "<<g.nr<<" persoane implicate:"<<"\n";
        for(int i=0;i<g.nr;i++)
            out<<g.v[i]<<"\n";
        return out;
    }
};

template <class t> int FirmaDistributie<t>::get_nr(){
    return nr;
}

template <> class FirmaDistributie <actor>
{
    actor* v;
    int nr;
    int nr_actori_principali;
public:
    FirmaDistributie(actor *p=NULL, int n=0)
    {
        nr_actori_principali=0;
        nr=n;
        v=new actor[n];
        for(int i=0;i<n;i++)
        {
            v[i]=p[i];
            for (int j=0;j<v[i].get_numar();j++)
                if (v[i].get_principal(j)==1)
                    {nr_actori_principali+=1;
                    break;}
        }
    }
    FirmaDistributie(FirmaDistributie &a)
    {
        nr=a.nr;
        nr_actori_principali=0;
        v=new actor[nr];
        for(int i=0;i<nr;i++)
        {
            v[i]=a.v[i];
            for (int j=0;j<v[i].get_numar();j++)
                if (v[i].get_principal(j)==1)
                    nr_actori_principali+=1;
        }
    }
    ~FirmaDistributie()
    {
        delete [] v;
    }

    int get_nr() {return nr;}
    actor get_v(int i) {return v[i];}
    friend istream& operator >>(istream &in, FirmaDistributie <actor> &g)
    {
        cout<<"Introduceti numarul de actori implicati: ";
        in>>g.nr;
        g.v=new actor[g.nr];
        cout<<"Introduceti obiectele\n";
        for(int i=0;i<g.nr;i++)
        {
            in>>g.v[i];
            for (int j=0;j<g.v[i].get_numar();j++)
                if (g.v[i].get_principal(j)==1)
                    {g.nr_actori_principali+=1;
                    break;}
           cout<<"\n";
        }
        return in;
    }
    friend ostream& operator <<(ostream &out, FirmaDistributie<actor> &g)
    {
        out<<"In firma de distributie sunt "<<g.nr<<" actori implicati.\n";
        for(int i=0;i<g.nr;i++)
            out<<g.v[i]<<"\n";
        out<<"Dintre acestia, "<<g.nr_actori_principali<<" sunt actori principali.\n";
        return out;
    }
};


void tip(personal *&p, int &i) {
    string s;
    cout<<"\n";
    cout<<"Introduceti postul personalului "<<i+1<<": ";
    cin>>s;
    try
    {
        if(s=="regizor")
        {
                p=new regizor;
                cin>>*p;
                i++;
        }
        else
            if(s=="actor")
            {
                p=new actor;
                cin>>*p;
                i++;
            }
            else
                if(s=="tehnic")
                {
                    p=new tehnic;
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
        cout<<"Nu ati introdus un post valid. Incercati regizor, actor sau tehnic.\n ";
    }
}
void menu_output()
{
    cout<<"\nPRODUCTIE CINEMATOGRAFICA\n";
    cout<<"\n\t\tMENIU:";
    cout<<"\n===========================================\n";
    cout<<"\n";
    cout<<"1. Citeste informatii despre persoanele implicate. --- UPCAST & LATE-BINDING";
    cout<<"\n";
    cout<<"2. Firma de distributie --- TEMPLATE (regizor).";
    cout<<"\n";
    cout<<"3. Firma de distributie --- TEMPLATE (tehnic).";
    cout<<"\n";
    cout<<"4. Firma de distributie --- TEMPLATE (actor-SPECIALIZARE).";
    cout<<"\n";
    cout<<"5. Contorizare personal --- DYNAMIC_CAST (DOWNCAST).";
    cout<<"\n";
    cout<<"0. Iesire.";
    cout<<"\n";
}
void menu()
{
    int option;///optiunea aleasa din meniu
    option=0;
    int n=0;
    personal **v;
    do
    {
        menu_output();
        cout<<"\nIntroduceti numarul actiunii: ";
        cin>>option;
        if (option==1)
        {
            cout<<"Introduceti numarul de obiecte citite: ";
            cin>>n;
            v=new personal*[n];
            if (n>0)
            {
                for(int i=0;i<n;)
                    tip(v[i],i);
                cout<<"\nAfisam personalul citit anterior:\n";
                for(int i=0;i<n;i++)
                   {
                        cout<<"\n"<<*v[i];
                        cout<<"--------------------------\n";
                   }
            }
            else
                cout<<"Numarul introdus trebuie sa fie pozitiv.\n";
        }
        if (option==2)
        {
            FirmaDistributie <regizor> x;
            cin>>x;
            cout<<x;
        }
        if (option==3)
        {
            FirmaDistributie <tehnic> x;
            cin>>x;
            cout<<x;
        }
        if (option==4)
        {
            FirmaDistributie <actor> x;
            cin>>x;
            cout<<x;
        }
        if (option==5)
        {
            int N_reg,N_act,N_teh;
            N_reg=N_act=N_teh=0;
            if (n>0){
            for(int i=0;i<n;i++)
            {
                ///incerc cast catre regizor
                regizor *p1=dynamic_cast<regizor*>(v[i]);
                ///incerc cast catre actor
                actor *p2=dynamic_cast<actor*>(v[i]);
                ///incerc cast catre tehnic
                tehnic *p3=dynamic_cast<tehnic*>(v[i]);
                ///daca sunt nenuli atunci incrementez corespunzator
                if (p1)
                    N_reg++;
                if (p2)
                    N_act++;
                if (p3)
                    N_teh++;
            }
            cout<<"Numarul de regizori: "<<N_reg<<"\n";
            cout<<"Numarul de actori: "<<N_act<<"\n";
            cout<<"Numarul de personal tehnic: "<<N_teh<<"\n";}
            else{
                cout<<"Nu s-au citit persoane. Reveniti la actiunea 1.\n";
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
