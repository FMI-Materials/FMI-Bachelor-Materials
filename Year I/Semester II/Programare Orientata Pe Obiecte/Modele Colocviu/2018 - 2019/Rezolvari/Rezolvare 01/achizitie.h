//
// Created by Lenovo on 5/26/2020.
//

#ifndef COLOCVIU_ACHIZITIE_H
#define COLOCVIU_ACHIZITIE_H
#include <iostream>
#include <string>
#include<cmath>
#include <vector>
#include<map>
#include "chirurgicala.h"
#include "policarbonat.h"
#include "dezinfectanti.h"
#include "bacterii.h"
#include "virusuri.h"
#include "fungi.h"
#include "masca.h"

using namespace std;
class achizitie
{
    string data;
    string client;
    vector<dezinfectanti*> d;
   vector<masca *>m;

    double pret_total;//calculat automat
public:
    achizitie(){}
    achizitie( achizitie & ob)
    {
        data=ob.data;
        client=ob.client;
        for (vector<dezinfectanti*>::iterator it = ob.d.begin(); it != ob.d.end(); it++)
            d.push_back(*it);

        for (vector<masca*>::iterator it = ob.m.begin(); it != ob.m.end(); it++)
            m.push_back(*it);

        pret_total=ob.pret_total;

    }
    ~achizitie(){}
    achizitie & operator=( achizitie & ob)
    {
        data=ob.data;
        client=ob.client;
        for (vector<dezinfectanti*>::iterator it = ob.d.begin(); it != ob.d.end(); it++)
            d.push_back(*it);

        for (vector<masca*>::iterator it = ob.m.begin(); it != ob.m.end(); it++)
            m.push_back(*it);
        pret_total=ob.pret_total;
        return *this;
    }

    friend ostream &operator<<(ostream &os,  achizitie &ob);
    friend istream &operator>>(istream &os,  achizitie &ob);
};

ostream &operator<<(ostream &os, achizitie &ob)
{
    os<<"----achizitie:\n";
    os << "data: " << ob.data <<endl;
    os<< " client: " << ob.client<<endl;
    int i;
    os<<"dezinfectantii achizitionati: \n";
    for (vector<dezinfectanti*>::iterator it = ob.d.begin(); it != ob.d.end(); it++)
        os<<**it;

    os<<"mastile achizitionate: \n";

    for (vector<masca*>::iterator it = ob.m.begin(); it != ob.m.end(); it++)
        os<<**it;
  os<< " achzitie in valoare de: "<< ob.pret_total<<" lei"<<endl;
    return os;
}
istream &operator>>(istream &os,  achizitie &ob)
{
    cout<<"---dati o achizitie: \n";
    cout<<"data: ";
    getline(os,ob.data);
    cout<<"numele dvs: ";
    getline(os, ob.client);
    int i, dim1, dim2;
    cout<<"cati dezinfectanti vreti sa cumparati: ";
    os>>dim1;
    cout<<"introduceti dezinfectantii: \n";
    ob.pret_total=0;
    for(i=0;i<dim1;i++)
    {
        cout<<"dezinfectantul nr "<<i<<": ";
        cout<<"ce tip de dezinfectant doriti?: (1-bacterii/2-virusuri/3-fungi): ";
        int optiune;
        os>>optiune;
        os.get();
        dezinfectanti *p;
        if(optiune==1)
        {
            p=new bacterii;
            os>>(*p);
            bacterii *b= dynamic_cast<bacterii*>(p);
            ob.pret_total+=(*b).getPret();//calculez si pret total


        } else
            if(optiune==2)
            {
                p=new virusuri;
                os>>(*p);
                virusuri *b= dynamic_cast<virusuri*>(p);
                ob.pret_total+=(*b).getPret();
            }
            else
                if(optiune==3)
                {
                    p=new fungi;
                    os>>(*p);
                    fungi *b= dynamic_cast<fungi*>(p);
                    ob.pret_total+=(*b).getPret();
                }

       ob.d.push_back(p);

    }
    cout<<"cate masti vreti sa cumparati: ";
    os>>dim2;
    cout<<"introduceti mastile: \n";
    for(i=0;i<dim2;i++)
    {
        cout<<"masca nr "<<i<<": ";
        cout<<"ce tip de masca doriti?: (1-masca chirurgicala/2-masca policarbonat: ";
        int optiune;
        os>>optiune;
        os.get();
        masca *p;
        if(optiune==2)
        {
            p=new policarbonat;
            os>>(*p);
            policarbonat *b= dynamic_cast<policarbonat*>(p);
            ob.pret_total+=(*b).getPret();
        }
        else

        {
            p=new chirurgicala;
            os>>(*p);
            ob.pret_total+=(*p).getPret();
        }
       ob.m.push_back(p);

    }

    return os;


}
#endif //COLOCVIU_ACHIZITIE_H
