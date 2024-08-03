//
// Created by Lenovo on 5/16/2020.
//

#ifndef DIAMANT_PUNCT_H
#define DIAMANT_PUNCT_H
#include<iostream>
using namespace std;
class punct
{
    float x;
    float y;
public:
    punct() {}

    punct(float x, float y) : x(x), y(y) {}
    punct (const punct &ob)
    {
        x=ob.x;
        y=ob.y;
    }

     ~punct() {

    }
    punct & operator =(const punct & ob)
    {
        x=ob.x;
        y=ob.y;
        return *this;
    }
    void arie(const punct & ob)
    {
        cout<<"Nu se poate calcula aria punctului"<<endl;
    }

    float getX() const;

    friend ostream &operator<<(ostream &os, const punct &punct) ;
    friend istream &operator>>(istream &os, punct &punct) ;

};
 ostream &operator<<(ostream &os, const punct &punct) {
     os<<"punct: "<<endl;
    os << "x: " << punct.x << " y: " << punct.y<<endl;
    return os;
}
istream &operator>>(istream &os,  punct &punct)
{
     cout<<"punctul este :"<<endl;
    cout<< "x: ";
    os>> punct.x ;
    cout<< " y: ";
    os>> punct.y;
    return os;
}

float punct::getX() const {
    return x;
}

#endif //DIAMANT_PUNCT_H
