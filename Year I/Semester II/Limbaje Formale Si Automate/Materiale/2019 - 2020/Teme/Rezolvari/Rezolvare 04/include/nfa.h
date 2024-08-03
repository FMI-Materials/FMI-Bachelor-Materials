#include "state.h"
#include "regex.h"

#include <vector>
#include <iostream>

#ifndef TEMA2_NFA_H
#define TEMA2_NFA_H

class NFA{
private:
    static void remove_lambda(State*, State*, int);

    std::vector<std::pair<State*, std::pair<State*, std::string>>> get_all_inputs(State* state);
    void remove_from_states(State* state);
    void remove_regex_state(State* state);
    void strip_lambdas();
    void convert_to_regex();
protected:
    std::vector<State*> states;
public:
    NFA(const std::vector<State *>&);
    NFA(NFA const &);
    NFA() = default;

    std::vector<State*> get_states();
    std::vector<State*> get_states(bool, bool);
    State* operator[](int id);
    int push_state(State*);

    void remove_lambdas();

    void convert_to_dfa();

    REGEX get_regex();

    friend std::istream& operator>>(std::istream&, NFA&);
    friend std::ostream& operator<<(std::ostream&, const NFA&);
};

#endif //TEMA2_NFA_H
