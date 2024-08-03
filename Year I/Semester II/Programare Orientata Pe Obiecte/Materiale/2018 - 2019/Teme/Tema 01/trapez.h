//
// Created by Lenovo on 5/16/2020.
//
#include<iostream>
#include "punct.h"
#include "patrat.h"
#include "dreptunghi.h"
#include "romb.h"
#include "paralelogram.h"
using namespace std;
#ifndef DIAMANT_TRAPEZ_H
#define DIAMANT_TRAPEZ_H
class trapez : public paralelogram
{
    float baza2;
    int valid;
public:
    trapez() {}

    trapez(const punct &stangaJos, float latura, const punct &coltOpus, const punct &stangaJos1, float latura1,
           float latura2, float baza2) : paralelogram(stangaJos, latura, coltOpus, stangaJos1, latura1, latura2),
                                         baza2(baza2) {}
    trapez (const trapez & ob)
    {
        baza2=ob.baza2;
        latura2=ob.latura2;
        stanga_jos=ob.stanga_jos;
        latura=ob.latura;
        colt_opus=ob.colt_opus;

    }

    ~trapez() {

    }
    trapez & operator =(const trapez & ob)
    {
        baza2=ob.baza2;
        latura2=ob.latura2;
        stanga_jos=ob.stanga_jos;
        latura=ob.latura;
        colt_opus=ob.colt_opus;
        return * this;
    }
    float arie ()
    {
        float b,B;
        cout<<"arie trapez:";
        if (latura<latura2)
            B=latura2;
        else
            B=latura;
        cout<<"imi e lene sa calculez :)";
        return 1.1;

    }
    void citesc(istream &os);
    void afisez(ostream &os);

   // friend ostream &operator<<(ostream &os, const trapez &trapez);
    //friend istream &operator<<(istream &os,  trapez &trapez);

};
void trapez:: citesc(istream &os)
{
    cout<<"trapez:"<<endl;
    os>>baza2;
    cout<< " colt_opus: ";
    os>>colt_opus;
    cout<< "stanga_jos: " ;
    os>> stanga_jos ;
    cout<< " latura: ";
    os>> latura;
    cout<< " latura2: ";
}
void trapez:: afisez(ostream &os)
{
    cout<<"~~~~~~~~~~~~~~~~~"<<endl;
    cout<<"trapez: "<<endl;
    os<<"baza2: "<<baza2;
    os<< " colt_opus: " << colt_opus<<endl;
    os << "stanga_jos: " << stanga_jos<<endl << " latura: " << latura<<endl;
    os << " latura2: " << latura2<<endl;
}



#endif //DIAMANT_TRAPEZ_H
