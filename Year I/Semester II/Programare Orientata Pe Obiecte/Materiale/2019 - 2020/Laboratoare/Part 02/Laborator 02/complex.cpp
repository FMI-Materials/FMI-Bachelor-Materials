//
// Created by Darius Buhai on 2/28/20.
//

#include <iostream>
#include <string>
#include "complex.h"

Complex::Complex(): r(0), i(0){std::cout<<"C";}
extern Complex::Complex(int r, int i): r(r), i(i){std::cout<<"C";}
/// Copy constructor-ul se apeleaza direct cand trimit un obiect intr-o functie
Complex::Complex(const Complex& other): r(other.r), i(other.i){std::cout<<"C";}


void Complex::afisare() const {
    std::cout<<this->r<<(i>=0 ? "+" : "")<<this->i<<"i\n";
}
std::string Complex::to_String() const {
    return std::to_string(r)+(i>=0 ? "+" : "")+std::to_string(i)+"i\n";
}