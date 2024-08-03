#include <iostream>
#include <string>
#include <map>
#include "dfa.h"

#ifndef TEMA2_REGRAM_H
#define TEMA2_REGRAM_H

class REGGRAM{
    std::map<std::string, std::vector<std::pair<std::string, std::string>>> grammar;
    std::string start_state;
public:
    NFA get_nfa();
    void remove_lambdas();

    friend std::istream& operator>>(std::istream&, REGGRAM&);
    friend std::ostream& operator<<(std::ostream&, const REGGRAM&);
};

#endif //TEMA2_REGRAM_H
