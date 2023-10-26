#include <iostream>

using namespace std;

class Persoana{
protected:

string nume;
string prenume;

public:
    Persoana(){


        nume="Anonim";
        prenume="Anonim";

    }
    Persoana(string nume,string prenume){
        cout<<"cosntructor Persona:\n";

        this->nume=nume;
        this->prenume=prenume;


    }
    friend ostream& operator<< (ostream& out, const Persoana& p){

        out<<"Nume: "<<p.nume<<" Prenume: "<<p.prenume;
        return out;

    }

   void Afisare()
    {
        cout<< "Nume: "<<nume<<" Prenume: "<<prenume;
        }
    friend  istream& operator >>(istream& in, Persoana& p){

        cout<<"Numele: ";
        in>>p.nume;
        cout<<"Prenumele ";
        in>>p.prenume;
        return in;
    }

    ~Persoana(){

        cout<<"\n Destructor Peroana\n";
    }
};

class Student: public virtual Persoana{
protected:

    string facultate;
public:

    Student():Persoana(){

        facultate="Anonim";

    }

    void Afisare(){

        Persoana::Afisare();
        cout<<" facultatea: "<<facultate;

    }
    Student(string nume, string prenume, string facultate):Persoana(nume,prenume){
    cout<<"cosntructor Student:\n";

        this->facultate=facultate;

    }

        friend ostream& operator<< (ostream& out, const Student& p){

        out<<(Persoana&)p;
        out<<" Faculatea: "<<p.facultate;
        return out;

    }

    friend  istream& operator >>(istream& in, Student& p){

        in>>(Persoana&)p;
        cout<<"Faculatea: ";
        in>>p.facultate;

        return in;
    }


    ~Student(){

        cout<<"\n Destructor Student\n";
    }
};

class Angajat: public virtual Persoana{
protected:
    string functie;
    public:

    Angajat():Persoana(){

        functie="Anonim";

    }

        void Afisare(){

        Persoana::Afisare();
        cout<<" functie: "<<functie;

    }

    Angajat(string nume, string prenume, string functie):Persoana(nume,prenume){

    cout<<"cosntructor Angajat:\n";

        this->functie=functie;

    }

        friend ostream& operator<< (ostream& out, const Angajat& p){

        out<<(Persoana&)p;
        out<<" Functia: "<<p.functie;
        return out;

    }

    friend  istream& operator >>(istream& in, Angajat& p){

        in>>(Persoana&)p;
        cout<<"Functia: ";
        in>>p.functie;

        return in;
    }

    ~Angajat(){

        cout<<"\n Destructor Angajat\n";
    }

};

class StudentAngajat:public virtual Student,
                     public virtual Angajat{
protected:
    int salariul;
    public:
    StudentAngajat():Angajat(),Student(),Persoana(){

        salariul=0;

    }
    StudentAngajat(string nume,string prenume, string facultatea,string functie,int salariul):Angajat(nume,prenume,functie),Student(nume,prenume,facultatea),Persoana(nume,prenume){

        cout<<"cosntructor StudeAngajat:\n";

        this->salariul=salariul;


    }

    void Afisare(){

        Persoana::Afisare();
        cout<<" Facultate "<<facultate;
        cout<<" Functie "<<functie;
        cout<<" salariul "<<salariul;

    }


    ~StudentAngajat(){

        cout<<"\n Destructor StudentAngajat\n";
    }

};


int main()
{


  StudentAngajat a("ion","marcel","fmi","prof",1000);
    a.Afisare();
    cout<<endl;

    return 0;
}
