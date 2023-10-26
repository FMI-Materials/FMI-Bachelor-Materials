#include <iostream>
#include <string.h>

using namespace std;
class Persoana{
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
    Persoana(char* nume, string prenume):iDPersoana(contorId++){

        this->nume=new char[strlen(nume)+1];
        strcpy(this->nume,nume);

        this->prenume=prenume;

        this->cheltuieliInUltimeleNLuni=NULL;
        this->luni=0;
        this->cumparaturiInUltimaLuna=NULL;
        this->nrArticoleCumparate=0;


    }

    Persoana(int luni):iDPersoana(contorId++){

        this->luni=luni;
        this->nume=NULL;
        this->cheltuieliInUltimeleNLuni=NULL;
        this->luni=0;
        this->cumparaturiInUltimaLuna=NULL;
        this->nrArticoleCumparate=0;


    }
/*

    Persoana(int vasrta):iDPersoana(contorId++){

        this->varsta=vasrta;
        this->nume=NULL;
        this->cheltuieliInUltimeleNLuni=NULL;
        this->luni=0;
        this->cumparaturiInUltimaLuna=NULL;
        this->nrArticoleCumparate=0;


    }
*/


    Persoana(char* nume,string prenume, int varsta, bool angajat, float* cheltuieliInUltimeleNLuni, int luni, int nrArticoleCumparate, string* cumparaturiInUltimaLuna,char initialaTata):iDPersoana(contorId++)
    {
        this->nume=new char[strlen(nume)+1];
        strcpy(this->nume,nume);

        this->prenume=prenume;
        this->varsta=varsta;
        this->angajat=angajat;
        this->luni=luni;

        this->cheltuieliInUltimeleNLuni=new float[luni];
        for(int i=0; i<this->luni;i++)
            this->cheltuieliInUltimeleNLuni[i]=cheltuieliInUltimeleNLuni[i];

        this->nrArticoleCumparate=nrArticoleCumparate;

        this->cumparaturiInUltimaLuna=new string [this->nrArticoleCumparate];
        for(int i=0; i<this->nrArticoleCumparate; i++)
            this->cumparaturiInUltimaLuna[i]=cumparaturiInUltimaLuna[i];

        this->initialaTata=initialaTata;



    }

    Persoana(const Persoana& per):iDPersoana(per.iDPersoana){

        this->nume=new char[strlen(per.nume)+1];
        strcpy(this->nume,per.nume);

        this->prenume=per.prenume;
        this->varsta=per.varsta;
        this->angajat=per.angajat;
        this->luni=per.luni;

        this->cheltuieliInUltimeleNLuni=new float[per.luni];
        for(int i=0; i<this->luni;i++)
            this->cheltuieliInUltimeleNLuni[i]=per.cheltuieliInUltimeleNLuni[i];

        this->nrArticoleCumparate=per.nrArticoleCumparate;

        this->cumparaturiInUltimaLuna=new string [this->nrArticoleCumparate];
        for(int i=0; i<this->nrArticoleCumparate; i++)
            this->cumparaturiInUltimaLuna[i]=per.cumparaturiInUltimaLuna[i];

        this->initialaTata=per.initialaTata;

    }

    Persoana& operator=(const Persoana& per){

        if(this!=&per){

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
            for(int i=0; i<this->luni;i++)
                this->cheltuieliInUltimeleNLuni[i]=per.cheltuieliInUltimeleNLuni[i];

            this->nrArticoleCumparate=per.nrArticoleCumparate;

            this->cumparaturiInUltimaLuna=new string [this->nrArticoleCumparate];
            for(int i=0; i<this->nrArticoleCumparate; i++)
                this->cumparaturiInUltimaLuna[i]=per.cumparaturiInUltimaLuna[i];

            this->initialaTata=per.initialaTata;



        }

        return *this;


    }


    float* getCheltuieliInUltimeleNLuni()
    {
        return this->cheltuieliInUltimeleNLuni;

    }
    void setCheltuieliInUltimeleNLuni( float* chel, int n) // string* int*...
    {
        this->luni=n;
        if(this->cheltuieliInUltimeleNLuni!=NULL)
            delete[] cheltuieliInUltimeleNLuni;
        this->cheltuieliInUltimeleNLuni=new float[n];
        for(int i=0; i<n; i++)
            this->cheltuieliInUltimeleNLuni[i]=chel[i];

    }

    void setPrenume(string a){

        this->prenume=a;

    }

    int getLuni() // la fel si pt char, long, float
    {
        return luni;

    }

    char* getNume()
    {

        return this->nume;

    }

    void setNume(char* nume) // la fel pt toate cu *
    {

        if(this->nume!=NULL)
            delete[] this->nume;

        this->nume=new char[strlen(nume)+1];
        strcpy(this->nume,nume);

    }



    ~Persoana(){

        if(this->nume!=NULL)
            delete[] this->nume;
        if(this->cheltuieliInUltimeleNLuni!=NULL)
            delete[] this->cheltuieliInUltimeleNLuni;
        if(this->cumparaturiInUltimaLuna!=NULL)
            delete[] this->cumparaturiInUltimaLuna;

    }




};
int Persoana::contorId=1000;
Persoana::Persoana():iDPersoana(contorId++){

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


int main()
{

    //cd
    Persoana a;

    // constr cu toti param;
    char nume[]={"Szmeteanca"};
    char nume2[]={"Szmeteanca2"};
    float chel[]={3.4,5.6,10};
    float chel2[]={3.4,5.6,10,1000};
    string prod[]={"Mere", "Pere","Banane"};

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
    for(int i=0; i<p1.getLuni();i++)
        cout<<*(p1.getCheltuieliInUltimeleNLuni()+i)<<" ";
    p1.setCheltuieliInUltimeleNLuni(chel2,4);
        cout<<"\n";
    for(int i=0; i<p1.getLuni();i++)
        cout<<*(p1.getCheltuieliInUltimeleNLuni()+i)<<" ";




    return 0;
}
