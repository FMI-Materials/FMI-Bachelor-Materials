//
// Created by Lenovo on 5/16/2020.
//

#ifndef DIAMANT_PATRAT_H
#define DIAMANT_PATRAT_H
#include<iostream>
#include "punct.h"
using namespace std;
class patrat
{
    int valid;
protected:
    punct stanga_jos;
    float latura;

public:
    patrat() {}

    patrat(const punct &stangaJos, float latura) : stanga_jos(stangaJos), latura(latura) {}
    patrat(const patrat & ob)
    {
        stanga_jos=ob.stanga_jos;
        latura=ob.latura;

    }
     virtual ~patrat() {

    }

    patrat & operator =(const patrat & ob)
    {
        stanga_jos=ob.stanga_jos;
        latura=ob.latura;
        return *this;
    }
    virtual float arie()
    {
        cout<<"arie patrat:";
        return latura*latura;
    }

    virtual void citesc(istream &os);
    virtual void afisez(ostream &os);

     friend ostream &operator<<(ostream &os, patrat &patrat);
     friend istream &operator>>(istream &os, patrat &patrat) ;

};
void patrat:: citesc(istream &os)
{
    cout<<"patrat:"<<endl;
    cout<< "stanga_jos: " ;
    os>> stanga_jos ;
    cout<< " latura: ";
    os>> latura;
}
void patrat:: afisez(ostream &os) {
    cout<<"~~~~~~~~~~~~~~~~~"<<endl;
    os<<"patrat:"<<endl;
    os << "stanga_jos: " << stanga_jos << " latura: " << latura<<endl;

}
ostream  &  operator<<(ostream &os, patrat &patrat)
{
    patrat.afisez(os);
    return os;
}

istream & operator>>(istream &os, patrat &patrat)
{
    patrat.citesc(os);
    return os;
}



#endif //DIAMANT_PATRAT_H
