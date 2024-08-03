//
// Created by Darius Buhai on 3/11/20.
//

#ifndef LAB4_VECTOR_H
#define LAB4_VECTOR_H

class Vector{
    static unsigned nr_inst;
    vector<int*> v;
public:
    Vector()=default;
    Vector(vector<int> x);
    Vector(const Vector &other);

    void afisare();

    friend ostream& operator<<(ostream& std, const Vector &d);
    friend istream& operator>>(istream& std, Vector &d);

    Vector operator+(int nr);

    friend Vector operator+(int nr, const Vector &a);
    Vector operator+(Vector a);

    Vector& operator++();
    Vector& operator++(int);

    int& operator[](int p);

    Vector& operator=(const Vector& rhs);
};


#endif //LAB4_VECTOR_H
