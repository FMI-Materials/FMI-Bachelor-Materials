#include <vector>
#include <iostream>
#include <string>

#ifndef TEMA2_STATE_H
#define TEMA2_STATE_H

struct State{
    std::vector<std::pair<State*, std::string>> next;
    bool final_state, start_state;
    int id;

    State(int id = -1, bool _final_state = false, bool _start_state = false): id(id), final_state(_final_state), start_state(_start_state){}
    State(bool _final_state, bool _start_state): id(-1), final_state(_final_state), start_state(_start_state){}
};

#endif //TEMA2_STATE_H
