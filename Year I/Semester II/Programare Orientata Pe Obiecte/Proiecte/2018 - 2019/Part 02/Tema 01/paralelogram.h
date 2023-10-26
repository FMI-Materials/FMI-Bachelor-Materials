//
// Created by Lenovo on 5/16/2020.
//

#ifndef DIAMANT_PARALELOGRAM_H
#define DIAMANT_PARALELOGRAM_H
#include<iostream>
#include "punct.h"
#include "patrat.h"
#include "dreptunghi.h"
#include "romb.h"
using namespace std;
class paralelogram: public romb, public dreptunghi{
    int valid;
public:
    paralelogram() {}

    paralelogram(const punct &stangaJos, float latura, const punct &coltOpus, const punct &stangaJos1, float latura1,
                 float latura2) : romb(stangaJos, latura, coltOpus), dreptunghi(stangaJos1, latura1, latura2) {}
    paralelogram (const paralelogram & ob)
    {
        latura2=ob.latura2;
        stanga_jos=ob.stanga_jos;
        latura=ob.latura;
        colt_opus=ob.colt_opus;
    }

     ~paralelogram() {

    }
    paralelogram & operator =(const paralelogram & ob)
    {
        latura2=ob.latura2;
        stanga_jos=ob.stanga_jos;
        latura=ob.latura;
        colt_opus=ob.colt_opus;
        return *this;
    }
    float arie()
    {
        cout<<"arie paralel:";
        float D;
        D=abs(colt_opus.getX()-stanga_jos.getX());
        if (latura*latura+latura2*latura2==D*D)
            return dreptunghi:: arie();
        else
            return romb:: arie();
    }
    void citesc(istream &os);
    void afisez(ostream &os);

    //friend ostream &operator<<(ostream &os, const paralelogram &paralelogram);
    //friend istream &operator>>(istream &os,  paralelogram &paralelogram);


};
void paralelogram:: citesc(istream &os)
{
    cout<<"paralelogram: "<<endl;
    cout<< " colt_opus: ";
    os>>colt_opus;
    cout<< "stanga_jos: " ;
    os>> stanga_jos ;
    cout<< " latura: ";
    os>> latura;
    cout<< " latura2: ";
}
void paralelogram:: afisez(ostream &os)
{
    cout<<"~~~~~~~~~~~~~~~~~"<<endl;
    os<<"paralelogram: "<<endl;
    os<< " colt_opus: " << colt_opus<<endl;
    os << "stanga_jos: " << stanga_jos<<endl << " latura: " << latura<<endl;
    os << " latura2: " << latura2<<endl;

}



#endif //DIAMANT_PARALELOGRAM_H
