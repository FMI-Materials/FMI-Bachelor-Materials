//
// Created by Lenovo on 5/16/2020.
//

#ifndef DIAMANT_DREPTUNGHI_H
#define DIAMANT_DREPTUNGHI_H
#include<iostream>
#include "punct.h"
#include "patrat.h"
using namespace std;
class dreptunghi: virtual public patrat
{int valid;
protected:
    float latura2;
public:
    dreptunghi() {}

    dreptunghi(const punct &stangaJos, float latura, float latura2) : patrat(stangaJos, latura), latura2(latura2) {}
    dreptunghi( const dreptunghi & ob)
    {
        latura2=ob.latura2;
        stanga_jos=ob.stanga_jos;
        latura=ob.latura;

    }
     ~dreptunghi() {

    }
    dreptunghi & operator =(const dreptunghi & ob)
    {
        latura2=ob.latura2;
        stanga_jos=ob.stanga_jos;
        latura=ob.latura;

        return *this;
    }
    float arie()
    {
        cout<<"arie dreptunghi:";
        return latura*latura2;
    }
    void citesc(istream &os);
    void afisez(ostream &os);

    //friend ostream &operator<<(ostream &os, const dreptunghi &dreptunghi);
    //friend istream &operator>>(istream &os,  dreptunghi &dreptunghi);

};
void dreptunghi:: citesc(istream &os)
{
    cout<<"dreptunghi: "<<endl;
    cout<< " latura2: ";
    os>> latura2;
    cout<< "stanga_jos: " ;
    os>> stanga_jos ;
    cout<< " latura: ";
    os>> latura;
}
void dreptunghi::  afisez(ostream &os)
{
    cout<<"~~~~~~~~~~~~~~~~~"<<endl;
    os<<"dreptunghi: "<<endl;
    os << " latura2: " << latura2<<endl;
    os << "stanga_jos: " << stanga_jos << " latura: " << latura<<endl;
}



#endif //DIAMANT_DREPTUNGHI_H
