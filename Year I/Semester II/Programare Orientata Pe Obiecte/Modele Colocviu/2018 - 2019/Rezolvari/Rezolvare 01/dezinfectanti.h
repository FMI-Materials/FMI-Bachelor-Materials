//
// Created by Lenovo on 5/26/2020.
//

#ifndef COLOCVIU_DEZINFECTANTI_H
#define COLOCVIU_DEZINFECTANTI_H
#include <iostream>
#include <string>
#include<cmath>
#include <vector>
#include<map>
using namespace std;
class dezinfectanti
{
protected:

    int specii;
    string ingrediente;
    string suprafata;
public:
    dezinfectanti(){}

    dezinfectanti(const dezinfectanti & ob)
    {
        specii=ob.specii;
        ingrediente=ob.ingrediente;
        suprafata=ob.suprafata;
    }
    virtual ~dezinfectanti(){}

    dezinfectanti & operator =(const dezinfectanti & ob)
    {
        specii=ob.specii;
        ingrediente=ob.ingrediente;
        suprafata=ob.suprafata;
        return *this;
    }

    virtual void citesc(istream &os)=0;
    virtual void afisez(ostream &os)=0;
    void reteta(string nou)
    {
        ingrediente=nou;
    }
    friend ostream& operator <<(ostream &os, dezinfectanti &ob);
    friend istream& operator >>(istream &os, dezinfectanti &ob);
};
ostream& operator << (ostream& os, dezinfectanti& ob)
{
    ob.afisez(os);
    return os;
}
istream& operator >>(istream& os, dezinfectanti& ob)
{
    ob.citesc(os);
    return os;
}

#endif //COLOCVIU_DEZINFECTANTI_H
