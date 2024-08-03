#include <iostream>
#include <vector>

using namespace std;

#include "vector.h"

unsigned Vector::nr_inst = 0;

Vector::Vector(vector<int> x){
    for(auto i : x)
        v.emplace_back(new int(i));
    nr_inst++;
}

void Vector::afisare(){
    for(auto &e: v) /// Referinta pentru a nu copia adresa la fiecare iteratie
        cout<<*e<<' ';
    cout<<'\n';
}

ostream& operator<<(ostream& std, const Vector &d){
    for(auto &e: d.v)
        std<<*e<<' ';
    return std;
}

istream& operator>>(istream& std, Vector &d){
    int x, size;
    for(auto e: d.v)
        delete e;
    d.v.clear();
    std>>size;
    for(int i=0;i<size;++i){
        std>>x;
        d.v.emplace_back(new int(x));
    }
    return std;
}

Vector Vector::operator+(int nr){
    for(auto e: this->v)
        (*e)+=nr;
    return *this;
}
Vector Vector::operator+(Vector a){
    //for(auto e: this->v)
    //   (*e)+=nr;
    return *this;
}

Vector operator+(int nr, const Vector &a){
    Vector d(a);
    for(auto e: d.v)
        (*e)+=nr;
    return d;
}

Vector& Vector::operator++(int nr){
    Vector d(*this);
    operator++();
    return d;
}

Vector& Vector::operator++(){
    *this = *this + 1;
    return *this;
}

Vector::Vector(const Vector &other){
    for(auto e: other.v)
        v.emplace_back(new int(*e));
    nr_inst++;
}

int& Vector::operator[](int p){
    return *(this->v[p]);
}


Vector& Vector::operator=(const Vector& rhs){
    if(this!=&rhs){
        for(auto e: this->v)
            delete e;
        this->v.clear();
        for(auto &e: rhs.v)
            this->v.emplace_back(new int(*e));
    }
    return *this;
}

