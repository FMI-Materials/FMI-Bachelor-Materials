//
// Created by Lenovo on 5/26/2020.
//

#ifndef COLOCVIU_FUNGI_H
#define COLOCVIU_FUNGI_H
#include <iostream>
#include <string>
#include<cmath>
#include <vector>
#include<map>
#include "dezinfectanti.h"
using namespace std;
class fungi: public dezinfectanti
{
private:
    const long double total=100000000;
    double eficienta;//calculata automat
    double pret;//calculat automat


public:
    fungi(){}

    fungi(const fungi & ob)
    {
        specii=ob.specii;
        ingrediente=ob.ingrediente;
        suprafata=ob.suprafata;
        eficienta=ob.eficienta;
        pret=ob.pret;
    }
    ~fungi(){}
    double getPret() const {
        return pret;
    }
    double getEficienta() const {
        return eficienta;
    }
    fungi & operator =(const fungi & ob)
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
void fungi::citesc(istream &os)
{
    cout<<"--dezinfectant fungi: \n";
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
void  fungi:: afisez(ostream &os)
{
    os<<"--dezinfectant fungi: \n";
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
#endif //COLOCVIU_FUNGI_H
