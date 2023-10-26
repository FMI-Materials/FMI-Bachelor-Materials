#include "../include/reggram.h"
#include "../include/dfa.h"

#include <iostream>
#include <vector>
#include <string>
#include <set>

#define LAMBDA '~'

using namespace std;

NFA REGGRAM::get_nfa() {
    NFA nfa;
    map<string, int> rename;
    for(auto& g: grammar){
        bool is_start_state = false;
        if(g.first==start_state) is_start_state = true;
        rename[g.first] = nfa.push_state(new State(false, is_start_state));
    }
    auto* final_state = new State(true, false);
    nfa.push_state(final_state);
    int idx = 0;
    for(const auto& g: grammar){
        for(const auto& s: g.second){
            State* conn = final_state;
            if(!s.second.empty())
                conn = nfa[rename[s.second]];
            nfa[idx]->next.emplace_back(conn, s.first);
        }
        idx++;
    }
    return nfa;
}

void REGGRAM::remove_lambdas(){
    /// Copy all lambda free productions and remember those that contain lambda
    set<string> contain_lambda;
    bool start_state_contains_lambda = false;
    map<string, vector<pair<string, string>>> lambda_free_grammar;
    for(const auto& symbol: this->grammar){
        vector<pair<string, string>> conn;
        for(const auto& n: symbol.second)
            if(!n.first.empty() && n.first[0]==LAMBDA){
                contain_lambda.insert(symbol.first);
                if(this->start_state==symbol.first) start_state_contains_lambda = true;
            }
            else
                conn.push_back(n);
        lambda_free_grammar[symbol.first] = conn;
    }
    /// if N->~ is in G, copy every rule in which N appears on the right hand side both with and without N
    for(const auto& cl: contain_lambda){
        for(auto& symbol: lambda_free_grammar){
            for(const auto& n: symbol.second)
                if(n.second==cl){
                    bool contains_already = false;
                    for(const auto &n1: symbol.second)
                        if(n1.first==n.first && n1.second.empty()){
                            contains_already = true; break;
                        }
                    if(!contains_already)
                    symbol.second.emplace_back(n.first, "");
                }
        }
    }
    /// Since S was a production in the original grammar, add S1 -> ~
    if(start_state_contains_lambda){
        for(auto &n: lambda_free_grammar[start_state])
            lambda_free_grammar[start_state+"1"].emplace_back(n);
        lambda_free_grammar[start_state+"1"].emplace_back(string(1, LAMBDA), "");
        start_state+="1";
    }
    /// Copy the generated grammar and free memory
    this->grammar = lambda_free_grammar;
    contain_lambda.clear();
    lambda_free_grammar.clear();
}

std::istream& operator>>(std::istream& in, REGGRAM& _reggram){
    int n;
    in>>n;
    while(n--){
        string a, b;
        in>>a>>b;
        if(_reggram.start_state.empty()) _reggram.start_state = a;
        string conn;
        if(b.size()>1) conn= b.substr(1);
        _reggram.grammar[a].emplace_back(b.substr(0,1), conn);
    }
    return in;
}

std::ostream& operator<<(std::ostream& out, const REGGRAM& _reggram){
    for(const auto& g: _reggram.grammar){
        out<<g.first<<' ';
        for(int i=0;i<g.second.size();i++){
            if(i>0) out<<" | ";
            out<<g.second[i].first<<g.second[i].second;
        }
        out<<'\n';
    }
    out<<'\n';
    return out;
}

