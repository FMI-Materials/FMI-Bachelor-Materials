//
// Created by Lenovo on 5/26/2020.
//

#ifndef COLOCVIU_VIRUSURI_H
#define COLOCVIU_VIRUSURI_H
#include <iostream>
#include <string>
#include<cmath>
#include <vector>
#include<map>
#include "dezinfectanti.h"
using namespace std;
class virusuri: public dezinfectanti
{
private:
    const long double total=1500000;
    double eficienta;//calculata automat
    double pret;//calculat automat


public:
    virusuri(){}

    virusuri(const virusuri & ob)
    {
        specii=ob.specii;
        ingrediente=ob.ingrediente;
        suprafata=ob.suprafata;
        eficienta=ob.eficienta;
        pret=ob.pret;
    }
    ~virusuri(){}
    double getPret() const {
        return pret;
    }
    double getEficienta() const {
        return eficienta;
    }

    virusuri & operator =(const virusuri & ob)
    {
        specii=ob.specii;
        ingrediente=ob.ingrediente;
        suprafata=ob.suprafata;
        eficienta=ob.eficienta;
        pret=ob.pret;
        return *this;
    }
    void citesc(istream &os);
    void afisez(ostream &os);

};
void virusuri::citesc(istream &os)
{
    cout<<"--dezinfectant virusuri: \n";
    cout<<"nr specii:";
    os>>specii;
    cout<<"ingrediente: ";
    os.get();
    getline(os,ingrediente);
    cout<<"suprafata: ";
    getline(os, suprafata);

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
    if(eficienta<0.9999)
        pret=50;
}
void  virusuri:: afisez(ostream &os)
{
    os<<"--dezinfectant virusuri: \n";
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

#endif //COLOCVIU_VIRUSURI_H
