//
// Created by Lenovo on 5/16/2020.
//

#ifndef DIAMANT_ROMB_H
#define DIAMANT_ROMB_H
#include<iostream>
#include "punct.h"
#include "patrat.h"
#include <cmath>
using namespace std;
class romb: virtual public patrat
{
    int valid;
protected:
    punct colt_opus;

public:
    romb() {}

    romb(const punct &stangaJos, float latura, const punct &coltOpus) : patrat(stangaJos, latura),
                                                                        colt_opus(coltOpus) {}
     romb(const romb & ob)
     {
        colt_opus=ob.colt_opus;
         stanga_jos=ob.stanga_jos;
         latura=ob.latura;
     }

     ~romb() {

    }
    romb & operator =(const romb & ob)
    {
        colt_opus=ob.colt_opus;
        stanga_jos=ob.stanga_jos;
        latura=ob.latura;
        return *this;
    }
    float arie()
    {
        float D,d;
        cout<<"arie romb:";
        D=abs(colt_opus.getX()-stanga_jos.getX());
        d=stanga_jos.getX()+latura;
        return (D+d)/2;

    }
     void citesc(istream &os);
     void afisez(ostream &os);

    //friend ostream &operator<<(ostream &os, const romb &romb);
   // friend istream &operator>>(istream &os, romb &romb);

};
void romb ::citesc(istream &os)
{
    cout<<"romb: "<<endl;
    cout<< " colt_opus: ";
    os>>colt_opus;
    cout<< "stanga_jos: " ;
    os>> stanga_jos ;
    cout<< " latura: ";
    os>> latura;
}
void romb:: afisez(ostream &os)
{
    cout<<"~~~~~~~~~~~~~~~~~"<<endl;
    os<<"romb: "<<endl;
    os<< " colt_opus: " << colt_opus<<endl;
    os << "stanga_jos: " << stanga_jos<<endl << " latura: " << latura<<endl;
}



#endif //DIAMANT_ROMB_H
