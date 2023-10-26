//
// Created by Lenovo on 5/26/2020.
//

#ifndef COLOCVIU_BACTERII_H
#define COLOCVIU_BACTERII_H
#include <iostream>
#include <string>
#include<cmath>
#include <vector>
#include<map>
#include "dezinfectanti.h"
using namespace std;
class bacterii: public dezinfectanti
{
private:
    const long double total=10000000000;
    double eficienta;//calculata automat
    double pret;//calculat automat


public:
    bacterii(){}

    bacterii(const bacterii & ob)
    {
        specii=ob.specii;
        ingrediente=ob.ingrediente;
        suprafata=ob.suprafata;
        eficienta=ob.eficienta;
        pret=ob.pret;
    }
    ~bacterii(){}

    double getPret() const {
        return pret;
    }

    bacterii & operator =(const bacterii & ob)
    {
        specii=ob.specii;
        ingrediente=ob.ingrediente;
        suprafata=ob.suprafata;
        eficienta=ob.eficienta;
        pret=ob.pret;
        return *this;
    }

    double getEficienta() const {
        return eficienta;
    }

    void citesc(istream &os);
    void afisez(ostream &os);

};
void bacterii::citesc(istream &os)
{
    cout<<"--dezinfectant bacterii: \n";
    cout<<"nr specii:";
    os>>specii;
    cout<<"ingrediente: ";
    os.get();
    getline(os,ingrediente);
    cout<<"suprafata: ";
    getline(os, suprafata);
   //calcul eficienta
    eficienta=specii/total;
    if(eficienta<0.9)
        pret=10;
    else
        if(eficienta<0.95)
            pret=20;
        else
            if(eficienta<0.975)
                pret=30;
            else
                if(eficienta<0.99)
                    pret=40;
                else
                        pret=50;
}
void  bacterii:: afisez(ostream &os)
{
    os<<"--dezinfectant bacterii: \n";
    os<<"nr specii:";
    os<<specii;
    os<<endl;
    os<<"ingrediente: ";
    os<<ingrediente;
    os<<endl;
    os<<"suprafata: ";
    os<<suprafata;
    os<<endl;
    os<<"eficienta: ";
    os<<eficienta;
    os<<endl;
    os<<"pret: ";
    os<<pret<<" lei";
    os<<endl;
}

#endif //COLOCVIU_BACTERII_H
