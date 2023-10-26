//
// Created by Lenovo on 5/26/2020.
//

#ifndef COLOCVIU_CHIRURGICALA_H
#define COLOCVIU_CHIRURGICALA_H
#include <iostream>
#include <string>
#include<cmath>
#include <vector>
#include<map>
#include "masca.h"
using namespace std;
class chirurgicala:public masca
{


public:
    chirurgicala() {}
    chirurgicala(const chirurgicala &ob)
    {
        protectie=ob.protectie;
        culoare=ob.culoare;
        pliuri=ob.pliuri;
        logo=ob.logo;
        pret=ob.pret;
    }

    virtual ~chirurgicala() {}
    chirurgicala& operator =(const chirurgicala &ob)
    {
        protectie=ob.protectie;
        culoare=ob.culoare;
        pliuri=ob.pliuri;
        logo=ob.logo;
        pret=ob.pret;
        return *this;
    }

    double getPret() const;
    string get_logo() const
    {
        return logo;
    }

    virtual void citesc(istream &os);
    virtual void afisez(ostream &os);

    friend ostream& operator <<(ostream &os, chirurgicala &ob);
    friend istream& operator >>(istream &os, chirurgicala &ob);


};
 void chirurgicala:: citesc(istream &os)
 {
    cout<<"------masca chirurgicala\n";
    tip=1;
    masca:: citesc(os);
 }
 void chirurgicala:: afisez(ostream &os)
 {
     os<<"------masca chirurgicala\n";
     masca:: afisez(os);
 }
ostream& operator << (ostream& os, chirurgicala& ob)
{
    ob.afisez(os);
    return os;
}
istream& operator >>(istream& os, chirurgicala& ob)
{
    ob.citesc(os);
    return os;
}

double chirurgicala::getPret() const {
    return pret;
}

#endif //COLOCVIU_CHIRURGICALA_H
