#include "../include/nfa.h"
#include "../include/regex.h"
#include "../include/state.h"

#include <iostream>
#include <utility>
#include <vector>
#include <queue>
#include <set>
#include <map>

#define LAMBDA '~'

using namespace std;

NFA::NFA(const std::vector<State *>& _states){
    map<int, State*> relation;
    for(auto const &state: states){
        auto new_state = new State(state->id, state->final_state, state->start_state);
        this->push_state(new_state);
        relation[new_state->id] = new_state;
    }
    for(auto const &state: states)
        for(auto const &n: state->next)
            this->states[state->id]->next.emplace_back(relation[n.first->id],n.second);
}

NFA::NFA(NFA const &_old){
    map<int, State*> relation;
    for(auto const &state: _old.states){
        auto new_state = new State(state->id, state->final_state, state->start_state);
        this->push_state(new_state);
        relation[new_state->id] = new_state;
    }
    for(auto const &state: _old.states)
        for(auto const &n: state->next)
            this->states[state->id]->next.emplace_back(relation[n.first->id],n.second);
}

int NFA::push_state(State * state) {
    if(state->id==-1) state->id = states.size();
    states.push_back(state);
    return state->id;
}

State* NFA::operator[](int id){
    if(states.size()>id && states[id]->id==id) return states[id];
    for(auto &state: states)
        if(state->id==id)
            return state;
    return nullptr;
}

void NFA::remove_lambda(State *v1, State *v2, int id){
    /**
     * step 1 - remove lambda
     * step 2 - duplicate moves that starts from v2
     * step 3 - set initial current_states
     * step 4 - set final current_states
     */
    for(int j=id;j<v1->next.size()-1;j++)
        v1->next[j] = v1->next[j+1];
    v1->next.pop_back();
    for(const auto& m: v2->next)
        v1->next.push_back(m);
    if(v1->start_state) v2->start_state = true;
    if(v2->final_state) v1->final_state = true;

}

void NFA::remove_lambdas(){
    /// Algoritmul de pe GeekForGeeks, ceva mai ok nu stiu sa fac
    int id;
    bool found_lambda;
    do{
        found_lambda = false;
        for(auto state: states){
            id = 0;
            for(auto c : state->next){
                if(c.second == string(1,LAMBDA)){
                    found_lambda = true;
                    remove_lambda(state, c.first, id);
                    break;
                }
                id++;
            }
            if(found_lambda) break;
        }
    }while(found_lambda);
}

void NFA::convert_to_dfa(){
    map<set<int>, map<string, set<int>>> current_states;
    queue<set<int>> to_add;
    map<string, set<int>> to;
    int start_state_id;
    /** First, add only the start current_states */
    for(State* x: states)
        if(x->start_state){
            start_state_id = x->id;
            for(const auto& s: x->next)
                to[s.second].insert(s.first->id);
            current_states[{x->id}] = to;
            for(const auto& t: to)
                if(current_states.find(t.second)==current_states.end())
                    to_add.push(t.second);
            break;
        }
    /** While there is a change in the current_states, group them */
    while(!to_add.empty()){
        set<int> current = to_add.front();
        to_add.pop();
        if(current_states.find(current)==current_states.end()){
            to.clear();
            for(int id: current){
                for(const auto& s: states[id]->next)
                    to[s.second].insert(s.first->id);
            }
            current_states[current] = to;
            for(const auto& t: to){
                to_add.push(t.second);
            }
        }
    }
    /** Merge all current_states and add them in the final graph */
    map<set<int>, State*> new_nodes;
    bool is_final_state, is_start_state;
    int id = 0;
    for(const auto& state: current_states){
        is_final_state = is_start_state = false;
        for(auto i: state.first)
            if(states[i]->final_state) is_final_state = true;
        if(state.first.size()==1 && state.first.find(start_state_id)!=state.first.end())
            is_start_state = true;
        new_nodes[state.first] = new State(id, is_final_state, is_start_state);
        id++;
    }
    states.clear();
    for(const auto& new_node: new_nodes){
        for(const auto& t: current_states[new_node.first])
            new_node.second->next.emplace_back(new_nodes[t.second], t.first);
        states.push_back(new_node.second);
    }
}

std::vector<State *> NFA::get_states(){
    return this->states;
}

vector<State*> NFA::get_states(bool final_state, bool start_state){
    vector<State*> new_states;
    for(auto s:states)
        if(s->start_state==start_state || s->final_state==final_state)
            new_states.push_back(s);
    return new_states;
}

void NFA::strip_lambdas(){
    auto strip_char = [](std::string& str, const char ch) {
        string new_string;
        for(auto c: str)
            if(c!=ch)
                new_string.push_back(c);
        str = new_string;
    };
    for(auto &state: states)
        for(auto &n: state->next)
            strip_char(n.second, LAMBDA);
}

void NFA::remove_regex_state(State* state){
    /// Find all connections ( in and out )
    vector<pair<State*, string>> out;
    out = state->next;
    auto in = get_all_inputs(state);
    /// Remove from states vector
    remove_from_states(state);
    /// Connect loops
    string loop;
    for(auto const & input: in)
        if(input.first==state){
            if(!loop.empty()) loop+="+";
            loop += input.second.second;
        }
    if(loop.size()>1) loop = "("+loop+")";
    if(!loop.empty()) loop += "*";
    /// Connect all inputs to the outputs
    for(auto &input: in)
        for(auto const& output: out){
            if(output.first!=state)
                input.first->next.emplace_back(output.first, input.second.second+loop+output.second);
        }
    /// Merge states that are the same
    for(auto &input: in){
        map<State*, vector<pair<State*, string>>> connections;
        for(auto &x: input.first->next)
            connections[x.first].push_back(x);
        if(connections.size()!=input.first->next.size()){
            input.first->next.clear();
            for(const auto& con: connections){
                string cost;
                for(const auto& a: con.second){
                    if(!cost.empty()) cost+="+";
                    cost+=a.second;
                }
                input.first->next.emplace_back(con.first, cost);
            }
        }
    }
    /// Free space
    delete state;
}

void NFA::remove_from_states(State* state){
    bool found_state = false;
    for(int i=0;i<states.size();i++){
        if(!found_state && states[i]==state)
            found_state = true;
        if(found_state)
            states[i] = states[i+1];
    }
    states.pop_back();
}

vector<pair<State*, pair<State*, string>>> NFA::get_all_inputs(State* state){
    vector<pair<State*, pair<State*, string>>> in;
    for(auto &i : states){
        vector<pair<State*, string>> new_next;
        for(auto &n: i->next)
            if(n.first == state)
                in.emplace_back(i, n);
            else
                new_next.emplace_back(n);
        i->next.clear();
        i->next = new_next;
    }
    return in;
}

void NFA::convert_to_regex(){
    /// Step 1 - add new start state, with lambda connection
    states.push_back(nullptr);
    for(int i = static_cast<int>(states.size()-1);i>0;i--){
        states[i] = states[i-1];
        states[i]->id++;
    }
    int start_state =0;
    for(auto const&state: states)
        if(state->start_state){
            start_state = state->id;
            break;
        }
    states[0] = new State(0, false, true);
    states[start_state]->start_state = false;
    states[0]->next.emplace_back(states[start_state], string(1, LAMBDA));
    /// Step 2 - add new final state and connect old final states
    states.push_back(new State(states.size(), true, false));
    for(int i=1;i<states.size()-1;i++)
        if(states[i]->final_state){
            states[i]->final_state = false;
            states[i]->next.emplace_back(states.back(), string(1, LAMBDA));
        }
    /// Step 3, remove all states, one by one
    do{
        remove_regex_state(states[1]);
    }while(states.size()>2);
    /// Clear lambdas
    strip_lambdas();
}

REGEX NFA::get_regex() {
    NFA copy_of_nfa = NFA(*this);
    copy_of_nfa.convert_to_regex();
    string _syntax;
    if(!copy_of_nfa.states.empty() && !copy_of_nfa.states[0]->next.empty())
        _syntax = copy_of_nfa.states[0]->next[0].second;
    REGEX reg = REGEX(_syntax);
    reg.minimize();
    return reg;
}

std::istream& operator>>(std::istream& in, NFA &nfa){
    int s, fs, m, ss;
    nfa.states.clear();
    in>>s>>m>>fs;
    in>>ss;
    for(int i=0;i<s;i++) nfa.states.push_back(new State(i));
    nfa.states[ss]->start_state = true;
    while(fs--){
        int x;
        in>>x;
        nfa.states[x]->final_state = true;
    }
    while(m--){
        int a, b;
        string acc;
        in>>a>>b>>acc;
        nfa.states[a]->next.emplace_back(nfa.states[b], acc);
    }
    return in;
}

ostream & operator<<(std::ostream& out, const NFA & nfa) {
    int cnt_final = 0, cnt_next = 0;
    for(auto state: nfa.states)
        if(state->final_state)
            cnt_final++;
    for(auto state: nfa.states)
        for(auto n: state->next)
            cnt_next++;
    out<<nfa.states.size()<<' '<<cnt_next<<' '<<cnt_final<<'\n';
    for(auto state: nfa.states)
        if(state->start_state){
            out<<state->id<<' ';
            break;
        }
    out<<'\n';
    for(auto state: nfa.states)
        if(state->final_state)
            out<<state->id<<' ';
    out<<'\n';
    for(auto state: nfa.states)
        for(const auto& n: state->next)
            out<<state->id<<' '<<n.first->id<<' '<<n.second<<'\n';
    out<<'\n';
    return out;
}