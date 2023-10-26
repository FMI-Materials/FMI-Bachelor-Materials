#include <iostream>
#include <string.h>
using namespace std;
class Persoana
{
private:
    string nume;
    char* prenume;
    int varsta;
public:
    string getNume()
    {
        return nume;
    }
    Persoana()
    {

        this->nume="Anonim";
        this->prenume=new char[strlen("Anonim")+1];
        strcpy(this->prenume,"Anonim");
        this->varsta=0;
        cout<<"\nConstructor Persoana\n";
    }

    Persoana(string nume, char* prenume, int varsta)
    {

        this->nume=nume;
        this->prenume=new char[strlen(prenume)+1];
        strcpy(this->prenume, prenume);
        this->varsta=varsta;

    }
    Persoana(const Persoana& p)
    {


        this->nume=p.nume;
        this->varsta=p.varsta;

        this->prenume=new char[strlen(p.prenume)+1];
        strcpy(this->prenume,p.prenume);



    }



    Persoana& operator=(const Persoana& p)
    {

        if(this!=&p)
        {

            this->nume=p.nume;

            if(this->prenume!=NULL)
                delete[] this->prenume;

            this->prenume=new char[strlen(p.prenume)+1];
            strcpy(this->prenume, p.prenume);
            this->varsta=p.varsta;


        }
        return *this;

    }

    friend ostream& operator<<(ostream& out, const Persoana& p)
    {
        out<<p.nume<<" "<<p.prenume<<" "<<p.varsta;
        return out;

    }

    friend istream& operator>>(istream& in, Persoana& p)
    {

        cout<<"Numele este: ";
        in>>p.nume;
        cout<<"Prenumele este: ";
        char buffer[100];
        in>>buffer;

        if(p.prenume!=NULL)
            delete[] p.prenume;
        p.prenume=new char[strlen(buffer)+1];
        strcpy(p.prenume, buffer);

        cout<<"Varsta este ";
        in>>p.varsta;

        return in;
    }

    ~Persoana()
    {

        if(this->prenume!=NULL)
            delete[] this->prenume;

        cout<<"\nDestructor Persoana\n";

    }

};
class Student:public Persoana
{
private:
    string facultate;
public:

    Student():Persoana()
    {

        this->facultate=facultate;
        cout<<"\nConstructor Student\n";

    }
    Student(string nume, char* prenume, int varsta, string facultate):Persoana(nume,prenume,varsta)
    {


        this->facultate=facultate;


    }

    Student(const Student& s):Persoana(s)
    {

        this->facultate=s.facultate;


    }

    Student& operator=(const Student& s)
    {


        if(this!=&s)
        {
            // sterge memoria la this unde este cazul;
            Persoana::operator=(s);
            this->facultate=s.facultate;


        }
        return *this;

    }

    friend ostream& operator<<(ostream& out, const Student& s)
    {
        out<<(Persoana&)s;
        out<<" "<<s.facultate;
        return out;

    }

    friend istream& operator>>(istream& in, Student& s)
    {
        in>>(Persoana&)s;
        cout<<"\nFacultate: ";
        in>>s.facultate;


        return in;
    }



    ~Student()
    {

        cout<<"\nDestructor Student\n";

    }
};




int main()
{
    char prenume[]= {"Edi"};

    Student s;
    cin>>s;
    cout<<s;


    return 0;
}
