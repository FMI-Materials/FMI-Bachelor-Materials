#include <iostream>
#include <string.h>

using namespace std;
class Produs
{
private:
    string nume;
    float pret;
public:

    Produs& operator=(const Produs& p)
    {
        if(this != &p)
        {
            this -> nume = p.nume;
            this -> pret = p.pret;
        }

        return *this;
    }
    Produs(const Produs& p)
    {
        this -> nume = p.nume;
        this -> pret = p.pret;
    }


    Produs()
    {
        this -> nume = "Anonim";
        this -> pret = 0;
    }
    Produs(string nume,float pret)
    {
        this -> nume = nume;
        this -> pret = pret;
    }

// ob+int
    Produs operator+(int x){

        Produs aux(*this);
        aux.pret=aux.pret+x;

        return aux;

    }
    Produs operator+=(int x){

        this->pret+=x;
        return *this;
    }
    /* ob+int
        friend Produs operator+( Produs p,int x){

        p.pret=p.pret+x;
        return p;


    }

    */
    // int +ob
    friend Produs operator+(int x, Produs p){

        p.pret=p.pret+x;
        return p;


    }

    // ob+ob
    Produs operator+( const Produs& p){

        Produs aux;
        aux.nume=this->nume+", "+p.nume;
        aux.pret=this->pret+p.pret;

        return aux;


    }
    /*

        friend Produs operator+ (Produs p1, Produs p2){

            p1.nume=p1.nume+", "+p2.nume;
            p1.pret=p1.pret+p2.pret;

            return p1;
        }

    */

    bool operator==(const Produs& per){

        if(this->nume==per.nume && this->pret==per.pret)
            return true;
        return false;

    }

    bool operator!=(const Produs& per){

        if(this->nume!=per.nume)
            return true;
        return false;

    }
    bool operator<(const Produs& per){

        if(this->pret<per.pret)
            return true;
        return false;

    }
    bool operator>=(const Produs& per){

        if(this->pret>=per.pret)
            return true;
        return false;

    }


    friend istream& operator>>(istream& in,Produs& p);
    friend ostream& operator<<(ostream& out, const Produs& p);

    explicit operator int(){
    // (int)p1
        return (int)this->pret;

    }

     operator int() const {
    // p1
        return (int)this->pret;

    }

    operator string() const {
    // p1
        return to_string(this->pret);

    }

   explicit operator string()  {
    // p1
        return this->nume;

    }

    ~Produs()
    {

    }


};

istream& operator>>(istream& in,Produs& p)
{
    cout<<"\nNume produs: ";
    in>>p.nume;
    cout<<"\nPretul produsului: ";
    in>>p.pret;

    return in;
}
ostream& operator<<(ostream& out,const Produs& p)
{
    out<<"\nNume Produs: "<<p.nume;
    out<<"\nPret Produs: "<<p.pret;

    return out;
}


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

    Produs* produse;
    int nrProduse;
protected:
    string prenume;
public:
    static int contorId;


    Persoana();
    Persoana(char* nume);
    Persoana(char* nume, string prenume);
    Persoana(char* nume, string prenume, int varsta, bool angajat, float* cheltuieliInUltimeleNLuni, int luni, int nrArticoleCumparate,
             string* cumparaturiInUltimaLuna,char initialaTata, int nrProduse, Produs* produse);
    Persoana(const Persoana& per);
    Persoana& operator=(const Persoana& per);
    friend ostream& operator<<(ostream& out, const Persoana& p); // operator afisare
    friend istream& operator>>(istream& in, Persoana& p); //operator citire

    int getLuni();
    char* getNume();
    void setNume(char* nume);
    void setCheltuieliInUltimeleNLuni( float* chel, int n);
    float* getCheltuieliInUltimeleNLuni();

    const Persoana& operator++();  // pre-incremenatre
    const Persoana operator++(int); //post-incrementare



    friend float sumaChel(Persoana p); // nu folosizti functii friend, aveti voie doar pentru <<,>> si op +/-/*/:

    Persoana operator+(const Produs& p){

        Persoana aux(*this);
        Produs *listaAux;
        listaAux=new Produs[aux.nrProduse];
        for(int i=0; i<aux.nrProduse;i++)
            listaAux[i]=aux.produse[i];

        if(aux.produse!=NULL)
            delete[] aux.produse;

        aux.nrProduse++;

        aux.produse=new Produs[aux.nrProduse];
        for(int i=0; i<aux.nrProduse-1;i++)
            aux.produse[i]=listaAux[i];

        aux.produse[aux.nrProduse-1]=p;

        return aux;

    }


      friend  Persoana operator+(const Produs& p, const Persoana& per1){

        Persoana aux(per1);
        Produs *listaAux;
        listaAux=new Produs[aux.nrProduse];
        for(int i=0; i<aux.nrProduse;i++)
            listaAux[i]=aux.produse[i];

        if(aux.produse!=NULL)
            delete[] aux.produse;

        aux.nrProduse++;

        aux.produse=new Produs[aux.nrProduse];
        for(int i=0; i<aux.nrProduse-1;i++)
            aux.produse[i]=listaAux[i];

        aux.produse[aux.nrProduse-1]=p;

        return aux;

    }

    void stergeProduse(const Produs& prod)
    {

        int k=0;
        Produs* listaProd;
        listaProd=new Produs[this->nrProduse];
        for(int i=0; i<this->nrProduse; i++)
        {

            listaProd[i]=this->produse[i];
            if(this->produse[i]==prod)
                k++;
        }
            if(this->produse!=NULL)
                delete[] this->produse;


            this->produse=new Produs[this->nrProduse-k];
            int i=0;
            int o=0;
            while(i<this->nrProduse)
            {
                if(listaProd[i]==prod)
                    i++;
                else
                {
                    this->produse[o]=listaProd[i];
                    o++;
                    i++;

                }

            }
            this->nrProduse=this->nrProduse-k;


    }

    Produs operator[](int index){

        if(index>=0 && index<this->nrProduse)
                return this->produse[index];
        else
        {
            cout<<"index gresit";
            exit(0);

        }

    }

    void afisare();
    void citire();

    ~Persoana();

};


//Pre-incremenatre
const Persoana& Persoana::operator++()
{

    this->varsta++;
    return *this;
}
//Post-incrementare
const Persoana Persoana::operator++(int)
{

    Persoana aux(*this);
    this->varsta++;

    return aux;

}

istream& operator>>(istream& in, Persoana& p)
{

    cout<<"\nNume: ";
    char aux[100];
    in>>aux;

    if(p.nume!=NULL)
        delete[] p.nume;
    p.nume=new char[strlen(aux)+1];
    strcpy(p.nume,aux);


    cout<<"\nPrenume: ";
    in>>p.prenume;
    cout<<"\nVarsts: ";
    in>>p.varsta;
    cout<<"\nAngajat [1-true/0-false]: ";
    in>>p.angajat;
    cout<<"\nInitiala tata: ";
    in>>p.initialaTata;

    cout<<"\nPe cate luni contorizam? ";
    in>>p.luni;
    cout<<"\nValori: ";

    if(p.cheltuieliInUltimeleNLuni!=NULL)
        delete[] p.cheltuieliInUltimeleNLuni;
    p.cheltuieliInUltimeleNLuni=new float[p.luni];
    for(int i=0; i<p.luni; i++)
        in>>p.cheltuieliInUltimeleNLuni[i];

    cout<<"\nCate produse ati cumparat in ultima luna: ";
    in>>p.nrArticoleCumparate;

    if(p.cumparaturiInUltimaLuna!=NULL)
        delete[] p.cumparaturiInUltimaLuna;
    p.cumparaturiInUltimaLuna=new string[p.nrArticoleCumparate];
    cout<<"\nProduse: ";
    for(int i=0; i<p.nrArticoleCumparate; i++)
        in>>p.cumparaturiInUltimaLuna[i];

    cout<<"\nNumarul de produse: ";
    in>>p.nrProduse;

    if(p.produse!=NULL)
        delete[] p.produse;
    p.produse=new Produs[p.nrProduse];
    cout<<"\nProdusele sunt: ";
    for(int i=0; i<p.nrProduse;i++)
        in>>p.produse[i];
    return in;

}

ostream& operator<<(ostream& out, const Persoana& p)
{


    out<<"\nId persoana: "<<p.iDPersoana;
    out<<"\nNume: "<<p.nume;
    out<<"\nPrenume: "<<p.prenume;
    out<<"\nVarsta: "<<p.varsta;
    out<<"\nInitiala tata: "<<p.initialaTata;
    out<<"\nAngajat: ";
    if(p.angajat) out<<"da";
    else out<<"nu";
    out<<"\nIn ultimele "<<p.luni<<" luni a cumparat produse in valoare de: ";
    for(int i=0; i<p.luni; i++)
        out<<p.cheltuieliInUltimeleNLuni[i]<<", ";
    out<<"\nIn ultima luna a cumparat produsele: ";
    for(int i=0; i<p.nrArticoleCumparate; i++)
        out<<p.cumparaturiInUltimaLuna[i]<<", ";

    out<<"\nProdduse cumparate sunt: ";
    for(int i=0; i<p.nrProduse;i++)
            out<<p.produse[i];
    return out;

}

void Persoana::citire()
{

    cout<<"\nNume: ";
    char aux[100];
    cin>>aux;

    if(this->nume!=NULL)
        delete[] this->nume;
    this->nume=new char[strlen(aux)+1];
    strcpy(this->nume,aux);


    cout<<"\nPrenume: ";
    cin>>this->prenume;
    cout<<"\nVarsts: ";
    cin>>this->varsta;
    cout<<"\nAngajat [1-true/0-false]: ";
    cin>>this->angajat;
    cout<<"\nInitiala tata: ";
    cin>>this->initialaTata;

    cout<<"\nPe cate luni contorizam? ";
    cin>>this->luni;
    cout<<"\nValori: ";

    if(this->cheltuieliInUltimeleNLuni!=NULL)
        delete[] this->cheltuieliInUltimeleNLuni;
    this->cheltuieliInUltimeleNLuni=new float[this->luni];
    for(int i=0; i<this->luni; i++)
        cin>>this->cheltuieliInUltimeleNLuni[i];

    cout<<"\nCate produse ati cumparat in ultima luna: ";
    cin>>this->nrArticoleCumparate;

    if(this->cumparaturiInUltimaLuna!=NULL)
        delete[] this->cumparaturiInUltimaLuna;
    this->cumparaturiInUltimaLuna=new string[this->nrArticoleCumparate];
    cout<<"\nProduse: ";
    for(int i=0; i<this->nrArticoleCumparate; i++)
        cin>>this->cumparaturiInUltimaLuna[i];

}

void Persoana::afisare()
{


    cout<<"\nId persoana: "<<this->iDPersoana;
    cout<<"\nNume: "<<this->nume;
    cout<<"\nPrenume: "<<this->prenume;
    cout<<"\nVarsta: "<<this->varsta;
    cout<<"\nInitiala tata: "<<this->initialaTata;
    cout<<"\nAngajat: ";
    if(this->angajat) cout<<"da";
    else cout<<"nu";
    cout<<"\nIn ultimele "<<this->luni<<" luni a cumparat produse in valoare de: ";
    for(int i=0; i<this->luni; i++)
        cout<<this->cheltuieliInUltimeleNLuni[i]<<", ";
    cout<<"\nIn ultima luna a cumparat produsele: ";
    for(int i=0; i<this->nrArticoleCumparate; i++)
        cout<<this->cumparaturiInUltimaLuna[i]<<", ";



}



int Persoana::contorId=1000;

float* Persoana::getCheltuieliInUltimeleNLuni()
{
    return this->cheltuieliInUltimeleNLuni;

}
void Persoana::setCheltuieliInUltimeleNLuni( float* chel, int n)
{
    this->luni=n;
    if(this->cheltuieliInUltimeleNLuni!=NULL)
        delete[] cheltuieliInUltimeleNLuni;
    this->cheltuieliInUltimeleNLuni=new float[n];
    for(int i=0; i<n; i++)
        this->cheltuieliInUltimeleNLuni[i]=chel[i];

}
int Persoana::getLuni()
{
    return luni;

}

char* Persoana::getNume()
{

    return this->nume;

}

void Persoana::setNume(char* nume)
{

    if(this->nume!=NULL)
        delete[] this->nume;
    this->nume=new char[strlen(nume)+1];
    strcpy(this->nume,nume);

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

        if(this->produse!=NULL)
            delete[] produse;

        this->nume=new char[strlen(per.nume)+1];

        strcpy( this->nume, per.nume);

        this->varsta=per.varsta;
        this->angajat=per.angajat;
        this->prenume=per.prenume;
        this->initialaTata=per.initialaTata;
        this->luni=per.luni;
        this->nrArticoleCumparate=per.nrArticoleCumparate;

        this->cheltuieliInUltimeleNLuni=new float[per.luni];
        for(int i=0; i<per.luni; i++)
            this->cheltuieliInUltimeleNLuni[i]=per.cheltuieliInUltimeleNLuni[i];

        this->cumparaturiInUltimaLuna=new string[per.nrArticoleCumparate];
        for(int i=0; i<per.nrArticoleCumparate; i++)
            this->cumparaturiInUltimaLuna[i]=per.cumparaturiInUltimaLuna[i];

        this->nrProduse=per.nrProduse;
        this->produse=new Produs[per.nrProduse];
        for(int i=0; i<per.nrProduse; i++)
            this->produse[i]=per.produse[i];


    }

    return *this;

}


Persoana::Persoana(const Persoana& per):iDPersoana(per.iDPersoana)
{

    this->nume=new char[strlen(per.nume)+1];
    strcpy( this->nume, per.nume);


    this->varsta=per.varsta;
    this->angajat=per.angajat;
    this->prenume=per.prenume;
    this->initialaTata=per.initialaTata;
    this->luni=per.luni;
    this->nrArticoleCumparate=per.nrArticoleCumparate;

    this->cheltuieliInUltimeleNLuni=new float[per.luni];
    for(int i=0; i<per.luni; i++)
        this->cheltuieliInUltimeleNLuni[i]=per.cheltuieliInUltimeleNLuni[i];

    this->cumparaturiInUltimaLuna=new string[per.nrArticoleCumparate];
    for(int i=0; i<per.nrArticoleCumparate; i++)
        this->cumparaturiInUltimaLuna[i]=per.cumparaturiInUltimaLuna[i];

    this->nrProduse=per.nrProduse;
    this->produse=new Produs[per.nrProduse];
    for(int i=0; i<per.nrProduse; i++)
        this->produse[i]=per.produse[i];



}

Persoana::Persoana(char* nume, string prenume, int varsta, bool angajat, float* cheltuieliInUltimeleNLuni, int luni, int nrArticoleCumparate,
                   string* cumparaturiInUltimaLuna,char initialaTata, int nrProduse, Produs* produse):iDPersoana(contorId++)
{

    this->nume=new char[strlen(nume)+1];
    strcpy( this->nume, nume);

    this->varsta=varsta;
    this->angajat=angajat;
    this->prenume=prenume;
    this->initialaTata=initialaTata;
    this->luni=luni;
    this->nrArticoleCumparate=nrArticoleCumparate;

    this->cheltuieliInUltimeleNLuni=new float[luni];
    for(int i=0; i<luni; i++)
        this->cheltuieliInUltimeleNLuni[i]=cheltuieliInUltimeleNLuni[i];

    this->cumparaturiInUltimaLuna=new string[nrArticoleCumparate];
    for(int i=0; i<nrArticoleCumparate; i++)
        this->cumparaturiInUltimaLuna[i]=cumparaturiInUltimaLuna[i];

    this->nrProduse=nrProduse;
    this->produse=new Produs[nrProduse];
    for(int i=0; i<nrProduse; i++)
        this->produse[i]=produse[i];

}



Persoana::Persoana(char* nume):iDPersoana(contorId++)
{

    this->nume=new char[strlen(nume)+1];
    strcpy( this->nume, nume);
    this->produse=NULL;
}

Persoana::Persoana(char* nume, string prenume):iDPersoana(contorId++)
{

    this->nume=new char[strlen(nume)+1];
    strcpy( this->nume, nume);
    this->prenume=prenume;
    this->produse=NULL;


}


Persoana::Persoana():iDPersoana(contorId++)
{

    this->produse=NULL;
    this->nrProduse=0;
    nume=new char[strlen("Anonim")+1];
    strcpy( this->nume,"Anonim");

    this->varsta=0;
    this->angajat=false;
    this->cheltuieliInUltimeleNLuni=NULL;// nullptr
    this->luni=0;
    this->cumparaturiInUltimaLuna=NULL;
    this->nrArticoleCumparate=0;
    this->initialaTata='q';
    this->prenume="Anonim";
}


Persoana::~Persoana()
{

    if(this->nume!=NULL)
        delete[] this->nume;

    if(this->cheltuieliInUltimeleNLuni!=NULL)
        delete[] this->cheltuieliInUltimeleNLuni;

    if(this->cumparaturiInUltimaLuna!=NULL)
        delete[] this->cumparaturiInUltimaLuna;

    if(this->produse!=NULL)
        delete[] this->produse;
}

float sumaChel(Persoana p)
{

    float s=0;
    for(int i=0; i<p.luni; i++)
        s=s+p.cheltuieliInUltimeleNLuni[i];
    return s;

}

int main()
{
  Produs p1("cola",10.3), p2("Lapte",3);
  Persoana per1;
    per1=p2+per1+p1+p2;


    cout<<endl<<per1;
    per1.stergeProduse(p2);
    cout<<endl<<per1;
    cout<<endl;
    cout<<per1[0];
    int a=p1;
    string b=p1;
    cout<<endl<<(int)p1;
    cout<<endl<<(string)p1;

}







