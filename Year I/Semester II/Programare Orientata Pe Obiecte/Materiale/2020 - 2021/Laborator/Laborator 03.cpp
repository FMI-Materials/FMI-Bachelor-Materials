#include <iostream>
#include <string.h>

using namespace std;
class Persoana;

class nrCompelx{
int partReal;
int parteImaginara;
public:
    nrCompelx(){this->parteImaginara=0; this->partReal=0;}
    nrCompelx(int real, int imaginar){
        this->partReal=real;
        this->parteImaginara=imaginar;

    }
    nrCompelx(const nrCompelx& p){

    this->partReal=p.partReal;
     this->parteImaginara=p.parteImaginara;
     }
    nrCompelx& operator=(const nrCompelx& p){
        if(this!=&p){
            this->partReal=p.partReal;
            this->parteImaginara=p.parteImaginara;
                }

    return *this;
    }

    friend nrCompelx operator+(const nrCompelx& a, const nrCompelx& b  ){

        nrCompelx aux;
        aux.partReal=a.partReal+b.partReal;
        aux.parteImaginara=a.parteImaginara+b.parteImaginara;

        return aux;
    }

    friend istream& operator>>(istream& in, nrCompelx& nr){
        cout<<"\nParte reala: "; in>>nr.partReal;
        cout<<"\nParte imaginara: "; in>>nr.parteImaginara;

        return in;

    }
    friend ostream& operator<<(ostream& out, const nrCompelx& nr){

        out<<nr.partReal<<" + "<<nr.parteImaginara<<"i";
        return out;

    }

    int getReal(){return this->partReal;}
    int getImaginar(){return this->parteImaginara;}

    void setReal(int real){this->partReal=real;}
    void setImagianr(int imaginar){this->parteImaginara=imaginar;}


};

class Produs{
float pret;
int tva;
public:
   friend class Persoana; // niciodata
};

class Persoana
{
private:
    char* nume;  //pointeri  char nume[100]
    int varsta;
    const int iDPersoana; // nu exista setter
    bool angajat;

    float* cheltuieliInUltimeleNLuni; // la fel si pentru int*, long* etc Persoane*
    int luni;

    string* cumparaturiInUltimaLuna;
    int nrArticoleCumparate;

    char initialaTata;

protected:
    string prenume;


public:

    static int contorId;

    Persoana();
    Persoana(int luni);
    /*Persoana(int vasrta):iDPersoana(contorId++);*/
    Persoana(char* nume, string prenume);
    Persoana(char* nume,string prenume, int varsta, bool angajat, float* cheltuieliInUltimeleNLuni, int luni, int nrArticoleCumparate, string* cumparaturiInUltimaLuna,char initialaTata);
    Persoana(const Persoana& per);
    Persoana& operator=(const Persoana& per);
    friend ostream& operator<<(ostream& out, const Persoana& per);
    friend istream& operator>>(istream&,Persoana&);

    float* getCheltuieliInUltimeleNLuni();
    int getLuni(); // la fel si pt char, long, float
    char* getNume();

    void setCheltuieliInUltimeleNLuni( float* chel, int n); // string* int*...
    void setPrenume(string a);
    void setNume(char* nume); // la fel pt toate cu *

    const Persoana& operator++(); // pre incrementare
    const Persoana operator++(int);  //post incrementare

    void afisare();
    void citire();

    friend void afisare2(const Persoana&);
    friend void citire2(Persoana&);
    friend float totalChel(Persoana p);//NICIODATA. Putem sa folosim friend doar pentru <<,>> +/-*
    float calculeazaPretProdus(Produs p);

    ~Persoana();




};


const Persoana Persoana::operator++(int){ // Post incrementare
        Persoana aux(*this);
        this->varsta++;
        return aux;
}
const Persoana& Persoana::operator++(){  //Pre incrementare

        this->varsta++;
        return *this;

}

istream& operator>>(istream& in, Persoana& per){

    cout<<"\nNume: ";
    char aux[100];
    in>>aux;

    if(per.nume!=NULL)
        delete[] per.nume;
    per.nume=new char[strlen(aux)+1];
    strcpy(per.nume,aux);

    cout<<"\nPrenume: "; in>>per.prenume;
    cout<<"\nVartsa: ";in>>per.varsta;
    cout<<"\nInitiala tata: "; in>>per.initialaTata;
    cout<<"\nAngajat [1-DA | 0-NU]:"; in>>per.angajat;

    cout<<"\nPe cate luni contorizam? "; in>>per.luni;
    if(per.cheltuieliInUltimeleNLuni!=NULL)
        delete[] per.cheltuieliInUltimeleNLuni;
    per.cheltuieliInUltimeleNLuni=new float[per.luni];
    cout<<"\nValori: ";
    for(int i=0; i<per.luni;i++)
        in>>per.cheltuieliInUltimeleNLuni[i];
    cout<<"\nCate produse ati cumparat in ultima luna? "; in>>per.nrArticoleCumparate;
    if(per.cumparaturiInUltimaLuna!=NULL)
        delete[] per.cumparaturiInUltimaLuna;
    per.cumparaturiInUltimaLuna=new string[per.nrArticoleCumparate];
    cout<<"\nProduse: ";
    for(int i=0; i<per.nrArticoleCumparate;i++)
        in>>per.cumparaturiInUltimaLuna[i];

    return in;


}

ostream& operator<<(ostream& out, const Persoana& per){

    out<<"\nID: "<<per.iDPersoana;
    out<<"\nNume: "<<per.nume;
    out<<"\nPrenume: "<<per.prenume;
    out<<"\nVarsta: "<<per.varsta;
    out<<"\nInitiala tata: "<<per.initialaTata;
    out<<"\nAngajat: ";
    if(per.angajat) out<<"da"; else out<<"nu";
    out<<"\nIn ultimele "<<per.luni<<" luni a cumparat produse in valoare de: ";
    for(int i=0; i<per.luni; i++)
        out<<per.cheltuieliInUltimeleNLuni[i]<<", ";
    out<<"\nUltimele produse cumparate: ";
    for(int i=0; i<per.nrArticoleCumparate;i++)
        out<<per.cumparaturiInUltimaLuna[i]<<", ";

    return out;



}

void citire2(Persoana& per){

    cout<<"\nNume: ";
    char aux[100];
    cin>>aux;

    if(per.nume!=NULL)
        delete[] per.nume;
    per.nume=new char[strlen(aux)+1];
    strcpy(per.nume,aux);

    cout<<"\nPrenume: "; cin>>per.prenume;
    cout<<"\nVartsa: ";cin>>per.varsta;
    cout<<"\nInitiala tata: "; cin>>per.initialaTata;
    cout<<"\nAngajat [1-DA | 0-NU]:"; cin>>per.angajat;

    cout<<"\nPe cate luni contorizam? "; cin>>per.luni;
    if(per.cheltuieliInUltimeleNLuni!=NULL)
        delete[] per.cheltuieliInUltimeleNLuni;
    per.cheltuieliInUltimeleNLuni=new float[per.luni];
    cout<<"\nValori: ";
    for(int i=0; i<per.luni;i++)
        cin>>per.cheltuieliInUltimeleNLuni[i];
    cout<<"\nCate produse ati cumparat in ultima luna? "; cin>>per.nrArticoleCumparate;
    if(per.cumparaturiInUltimaLuna!=NULL)
        delete[] per.cumparaturiInUltimaLuna;
    per.cumparaturiInUltimaLuna=new string[per.nrArticoleCumparate];
    cout<<"\nProduse: ";
    for(int i=0; i<per.nrArticoleCumparate;i++)
        cin>>per.cumparaturiInUltimaLuna[i];



}
void afisare2(const Persoana& per){

    cout<<"\nID: "<<per.iDPersoana;
    cout<<"\nNume: "<<per.nume;
    cout<<"\nPrenume: "<<per.prenume;
    cout<<"\nVarsta: "<<per.varsta;
    cout<<"\nInitiala tata: "<<per.initialaTata;
    cout<<"\nAngajat: ";
    if(per.angajat) cout<<"da"; else cout<<"nu";
    cout<<"\nIn ultimele "<<per.luni<<" luni a cumparat produse in valoare de: ";
    for(int i=0; i<per.luni; i++)
        cout<<per.cheltuieliInUltimeleNLuni[i]<<", ";
    cout<<"\nUltimele produse cumparate: ";
    for(int i=0; i<per.nrArticoleCumparate;i++)
        cout<<per.cumparaturiInUltimaLuna[i]<<", ";



}
void Persoana::citire(){

    cout<<"\nNume: ";
    char aux[100];
    cin>>aux;

    if(this->nume!=NULL)
        delete[] this->nume;
    this->nume=new char[strlen(aux)+1];
    strcpy(this->nume,aux);

    cout<<"\nPrenume: "; cin>>this->prenume;
    cout<<"\nVartsa: ";cin>>this->varsta;
    cout<<"\nInitiala tata: "; cin>>this->initialaTata;
    cout<<"\nAngajat [1-DA | 0-NU]:"; cin>>this->angajat;

    cout<<"\nPe cate luni contorizam? "; cin>>this->luni;
    if(this->cheltuieliInUltimeleNLuni!=NULL)
        delete[] this->cheltuieliInUltimeleNLuni;
    this->cheltuieliInUltimeleNLuni=new float[this->luni];
    cout<<"\nValori: ";
    for(int i=0; i<this->luni;i++)
        cin>>this->cheltuieliInUltimeleNLuni[i];
    cout<<"\nCate produse ati cumparat in ultima luna? "; cin>>this->nrArticoleCumparate;
    if(this->cumparaturiInUltimaLuna!=NULL)
        delete[] this->cumparaturiInUltimaLuna;
    this->cumparaturiInUltimaLuna=new string[this->nrArticoleCumparate];
    cout<<"\nProduse: ";
    for(int i=0; i<this->nrArticoleCumparate;i++)
        cin>>this->cumparaturiInUltimaLuna[i];

}

void Persoana::afisare(){

    cout<<"\nID: "<<this->iDPersoana;
    cout<<"\nNume: "<<this->nume;
    cout<<"\nPrenume: "<<this->prenume;
    cout<<"\nVarsta: "<<this->varsta;
    cout<<"\nInitiala tata: "<<this->initialaTata;
    cout<<"\nAngajat: ";
    if(this->angajat) cout<<"da"; else cout<<"nu";
    cout<<"\nIn ultimele "<<this->luni<<" luni a cumparat produse in valoare de: ";
    for(int i=0; i<this->luni; i++)
        cout<<this->cheltuieliInUltimeleNLuni[i]<<", ";
    cout<<"\nUltimele produse cumparate: ";
    for(int i=0; i<this->nrArticoleCumparate;i++)
        cout<<this->cumparaturiInUltimaLuna[i]<<", ";


}

float Persoana::calculeazaPretProdus(Produs p){

    return p.pret*p.tva/100+p.pret;

}

int Persoana::contorId=1000;
Persoana::Persoana():iDPersoana(contorId++)
{

    this->nume=new char[strlen("Anonim")+1];
    strcpy(this->nume,"Anonim");
    this->varsta=0;
    this->angajat=false;
    this->cheltuieliInUltimeleNLuni=NULL;
    this->luni=0;
    this->cumparaturiInUltimaLuna=NULL;
    this->nrArticoleCumparate=0;
    this->initialaTata='_';
    this->prenume="Anonim";


}

Persoana::Persoana(char* nume, string prenume):iDPersoana(contorId++)
{

    this->nume=new char[strlen(nume)+1];
    strcpy(this->nume,nume);

    this->prenume=prenume;

    this->cheltuieliInUltimeleNLuni=NULL;
    this->luni=0;
    this->cumparaturiInUltimaLuna=NULL;
    this->nrArticoleCumparate=0;


}

Persoana::Persoana(int luni):iDPersoana(contorId++)
{

    this->luni=luni;
    this->nume=NULL;
    this->cheltuieliInUltimeleNLuni=NULL;
    this->luni=0;
    this->cumparaturiInUltimaLuna=NULL;
    this->nrArticoleCumparate=0;


}
/*

    Persoana::Persoana(int vasrta):iDPersoana(contorId++){

        this->varsta=vasrta;
        this->nume=NULL;
        this->cheltuieliInUltimeleNLuni=NULL;
        this->luni=0;
        this->cumparaturiInUltimaLuna=NULL;
        this->nrArticoleCumparate=0;


    }
*/


Persoana::Persoana(char* nume,string prenume, int varsta, bool angajat, float* cheltuieliInUltimeleNLuni, int luni, int nrArticoleCumparate, string* cumparaturiInUltimaLuna,char initialaTata):iDPersoana(contorId++)
{
    this->nume=new char[strlen(nume)+1];
    strcpy(this->nume,nume);

    this->prenume=prenume;
    this->varsta=varsta;
    this->angajat=angajat;
    this->luni=luni;

    this->cheltuieliInUltimeleNLuni=new float[luni];
    for(int i=0; i<this->luni; i++)
        this->cheltuieliInUltimeleNLuni[i]=cheltuieliInUltimeleNLuni[i];

    this->nrArticoleCumparate=nrArticoleCumparate;

    this->cumparaturiInUltimaLuna=new string [this->nrArticoleCumparate];
    for(int i=0; i<this->nrArticoleCumparate; i++)
        this->cumparaturiInUltimaLuna[i]=cumparaturiInUltimaLuna[i];

    this->initialaTata=initialaTata;



}

Persoana::Persoana(const Persoana& per):iDPersoana(per.iDPersoana)
{

    this->nume=new char[strlen(per.nume)+1];
    strcpy(this->nume,per.nume);

    this->prenume=per.prenume;
    this->varsta=per.varsta;
    this->angajat=per.angajat;
    this->luni=per.luni;

    this->cheltuieliInUltimeleNLuni=new float[per.luni];
    for(int i=0; i<this->luni; i++)
        this->cheltuieliInUltimeleNLuni[i]=per.cheltuieliInUltimeleNLuni[i];

    this->nrArticoleCumparate=per.nrArticoleCumparate;

    this->cumparaturiInUltimaLuna=new string [this->nrArticoleCumparate];
    for(int i=0; i<this->nrArticoleCumparate; i++)
        this->cumparaturiInUltimaLuna[i]=per.cumparaturiInUltimaLuna[i];

    this->initialaTata=per.initialaTata;

}

Persoana& Persoana::operator=(const Persoana& per)
{

    if(this!=&per)
    {

        if(this->nume!=NULL)
            delete[] this->nume;
        if(this->cheltuieliInUltimeleNLuni!=NULL)
            delete[] this->cheltuieliInUltimeleNLuni;
        if(this->cumparaturiInUltimaLuna!=NULL)
            delete[] this->cumparaturiInUltimaLuna;

        this->nume=new char[strlen(per.nume)+1];
        strcpy(this->nume,per.nume);

        this->prenume=per.prenume;
        this->varsta=per.varsta;
        this->angajat=per.angajat;
        this->luni=per.luni;

        this->cheltuieliInUltimeleNLuni=new float[per.luni];
        for(int i=0; i<this->luni; i++)
            this->cheltuieliInUltimeleNLuni[i]=per.cheltuieliInUltimeleNLuni[i];

        this->nrArticoleCumparate=per.nrArticoleCumparate;

        this->cumparaturiInUltimaLuna=new string [this->nrArticoleCumparate];
        for(int i=0; i<this->nrArticoleCumparate; i++)
            this->cumparaturiInUltimaLuna[i]=per.cumparaturiInUltimaLuna[i];

        this->initialaTata=per.initialaTata;



    }

    return *this;


}


float* Persoana::getCheltuieliInUltimeleNLuni()
{
    return this->cheltuieliInUltimeleNLuni;

}
void Persoana::setCheltuieliInUltimeleNLuni( float* chel, int n) // string* int*...
{
    this->luni=n;
    if(this->cheltuieliInUltimeleNLuni!=NULL)
        delete[] cheltuieliInUltimeleNLuni;
    this->cheltuieliInUltimeleNLuni=new float[n];
    for(int i=0; i<n; i++)
        this->cheltuieliInUltimeleNLuni[i]=chel[i];

}

void Persoana::setPrenume(string a)
{

    this->prenume=a;

}

int Persoana::getLuni() // la fel si pt char, long, float
{
    return luni;

}

char* Persoana::getNume()
{

    return this->nume;

}

void Persoana::setNume(char* nume) // la fel pt toate cu *
{

    if(this->nume!=NULL)
        delete[] this->nume;

    this->nume=new char[strlen(nume)+1];
    strcpy(this->nume,nume);

}



Persoana::~Persoana()
{

    if(this->nume!=NULL)
        delete[] this->nume;
    if(this->cheltuieliInUltimeleNLuni!=NULL)
        delete[] this->cheltuieliInUltimeleNLuni;
    if(this->cumparaturiInUltimaLuna!=NULL)
        delete[] this->cumparaturiInUltimaLuna;

}

float totalChel(Persoana p){

    float s=0;
    for(int i=0;i<p.luni;i++)
        s=s+p.cheltuieliInUltimeleNLuni[i];
    return s;


}




int main()
{
/*
    //cd
    Persoana a;

    // constr cu toti param;
    char nume[]= {"Szmeteanca"};
    char nume2[]= {"Szmeteanca2"};
    float chel[]= {3.4,5.6,10};
    float chel2[]= {3.4,5.6,10,1000};
    string prod[]= {"Mere", "Pere","Banane"};

    Persoana p1(nume,"Eduard",23,true,chel,3,3,prod,'B');
    Persoana P5(nume,"Gabriel");

    //cc
    Persoana p2(p1), p3=p1;

    //operator =
    Persoana p4;
    p4=p1;
    // get_se;
    cout<<p1.getNume();
    p1.setNume("SZMETEANCA2");
    cout<<p1.getNume();

    cout<<"\n";
    for(int i=0; i<p1.getLuni(); i++)
        cout<<*(p1.getCheltuieliInUltimeleNLuni()+i)<<" ";
    p1.setCheltuieliInUltimeleNLuni(chel2,4);
    cout<<"\n";
    for(int i=0; i<p1.getLuni(); i++)
        cout<<*(p1.getCheltuieliInUltimeleNLuni()+i)<<" ";
cout<<"\n------------------------------------------------\n";
cout<<totalChel(p1);
cout<<endl;
p1.afisare();
//p1.citire();
//p1.afisare();
//afisare2(p1);
//citire2(p1);
//afisare2(p1);
cout<<++p1;
cout<<p1++;
cout<<p1;
*/

nrCompelx a;
cin>>a; cout<<a;
nrCompelx b(a),c;
c=a;

nrCompelx r=a+b+b;


cout<<endl<<b<<endl<<c;
cout<<endl<<r;




    return 0;
}
