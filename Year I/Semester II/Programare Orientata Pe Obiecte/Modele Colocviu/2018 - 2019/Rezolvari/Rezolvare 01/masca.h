//
// Created by Lenovo on 5/26/2020.
//

#ifndef COLOCVIU_MASCA_H
#define COLOCVIU_MASCA_H
#include <iostream>
#include <string>
#include<cmath>
#include <vector>
#include<map>
using namespace std;
class masca
{
protected:
    string protectie;
    string culoare;
    int pliuri;
    string logo;
    int tip;//1-daca e chirurgicala 2-policarbonat
    double pret;//in functie de protectie
public:
    masca() {}
    masca(const masca &ob)
    {
        protectie=ob.protectie;
        culoare=ob.culoare;
        pliuri=ob.pliuri;
        logo=ob.logo;
        pret=ob.pret;
    }

    virtual ~masca() {}
   masca & operator =(const masca &ob)
    {
        protectie=ob.protectie;
        culoare=ob.culoare;
        pliuri=ob.pliuri;
        logo=ob.logo;
        pret=ob.pret;
        return *this;
    }

    double getPret() const {
        return pret;
    }

    virtual void citesc(istream &os);
    virtual void afisez(ostream &os);

    friend ostream& operator <<(ostream &os, masca &ob);
    friend istream& operator >>(istream &os, masca &ob);


};
void masca:: citesc(istream &os)
{
    if(tip==1)//masca chirurgicala
    {
        cout << "protectie(ffp1/ffp2/ffp3): ";
        getline(os, protectie);
    }
    cout<<"culoare: ";
    getline(os, culoare);
    cout<<"nr pliuri: ";
    os>>pliuri;
    string rasp;
    if(tip==1) //logo-ul este pt masca chirurgicala
    {
        cout << "doriti si logo?(da/nu)\n ";
        os.get();
        getline(os, rasp);
        if (rasp == "da") {
            getline(os, logo);
        } else
            logo = "nu";
    }
    //calcul pret
    if(protectie=="ffp1")
        pret=5;
    else
    if(protectie=="ffp2")
        pret=10;
    else
    if(protectie=="ffp3")
        pret=15;
}
void masca:: afisez(ostream &os)
{

    os<<"protectie: ";
    os<<protectie;
    os<<endl;
    os<<"culoare: ";
    os<<culoare;
    os<<endl;
    cout<<"nr pliuri: ";
    os<<pliuri;
    os<<endl;
    if(tip==1) {
        os << "logo: ";
        os << logo;
        os << endl;
    }
    os<<"pret: ";
    os<<pret<<" lei";
    os<<endl;
}
ostream& operator << (ostream& os, masca& ob)
{
    ob.afisez(os);
    return os;
}
istream& operator >>(istream& os, masca& ob)
{
    ob.citesc(os);
    return os;
}


#endif //COLOCVIU_MASCA_H
