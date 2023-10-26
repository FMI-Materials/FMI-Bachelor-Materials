//
// Created by Lenovo on 5/26/2020.
//

#ifndef COLOCVIU_POLICARBONAT_H
#define COLOCVIU_POLICARBONAT_H
#include <iostream>
#include <string>
#include<cmath>
#include <vector>
#include<map>
#include "chirurgicala.h"
using namespace std;
class policarbonat: public masca
{
    string prindere;
public:
    policarbonat() {}
    policarbonat(const policarbonat &ob)
    {
        protectie=ob.protectie;
        culoare=ob.culoare;
        pliuri=ob.pliuri;
        logo=ob.logo;
        pret=ob.pret;
        prindere=ob.prindere;
    }

    ~policarbonat() {}

    policarbonat & operator =(const policarbonat &ob){
        protectie = ob.protectie;
        culoare = ob.culoare;
        pliuri = ob.pliuri;
        logo = ob.logo;
        pret = ob.pret;
        prindere = ob.prindere;
        return *this;
    }
    void citesc(istream &os);
    void afisez(ostream &os);
};
void policarbonat:: citesc(istream &os)
{
    cout<<"-------masca policarbonat: \n";
    tip=2;
    masca::citesc(os);
    protectie="ffp0";
    pret=20;
    cout<<"prindere: ";
    getline(os,prindere);
}
void policarbonat::afisez(ostream &os)
{
    os<<"-------masca policarbonat: \n";
    masca::afisez(os);
    os<<"prindere: ";
    os<<prindere<<endl;

}

#endif //COLOCVIU_POLICARBONAT_H
