#include "nfa.h"

#include <iostream>
#include <vector>
#include <string>

#ifndef TEMA2_DFA_H
#define TEMA2_DFA_H

class DFA: public NFA{
private:
    void remove_inaccessible();
public:
    void minimize();
};

#endif //TEMA2_DFA_H
