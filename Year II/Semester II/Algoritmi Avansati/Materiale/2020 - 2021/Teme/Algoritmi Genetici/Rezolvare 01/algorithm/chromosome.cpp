#include "chromosome.h"
#include <iostream>
#include <utility>
#include <vector>
#include <random>
#include <string>

int Chromosome::get_length(){
    if(l != 0)
        return l;
    set_length();
    return l;
}

void Chromosome::set_length(){
    LD ld = log2((domain.b - domain.a)*pow(10, p));
    l = (int) round(abs(ld));
}

LD Chromosome::get_value() const{
    LD y = ((domain.b - domain.a) / (pow(2, l) - 1));
    LD res = 0;
    for(int i=genes.size()-1;i>=0;--i){
        if(genes[i])
            res+=y;
        y*=2;
    }
    return  res + domain.a;
}

void Chromosome::set_genome(std::vector<bool> g){
    this->genes = std::move(g);
}

void Chromosome::generate_random(){
    genes.clear();
    for(int i=0;i<l;++i)
        genes.push_back(random() % 2);
}

std::string Chromosome::get_string_genome(){
    std::string result;
    for(auto g: genes)
        result += g ? "1" : "0";
    return result;
}

const std::vector<bool> &Chromosome::get_genome() const {
    return genes;
}

LD Chromosome::get_selection_probability() const {
    return ps;
}

void Chromosome::set_selection_probability(LD ps) {
    this->ps = ps;
}
