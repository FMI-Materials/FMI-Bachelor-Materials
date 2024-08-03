#include <iostream>
#include <fstream>

#include "include/nfa.h"
#include "include/dfa.h"
#include "include/reggram.h"
#include "include/regex.h"

using namespace std;

void show_model(ostream& out){
    out<<"<------ Model: ----------------------->\n\n";
    out<<"(States) (Connections) (Number of final states)\n(Start state)\n(Final states)\n";
    out<<"(State from) (State to) (Cost)\n...\n...\n";
    out<<"(State from) (State to) (Cost)\n";
}

void lambda_nfa_dfa(ostream& out){
    out<<"\n<------ Lambda nfa to dfa: ----------->\n\n";
    NFA nfa;
    ifstream fin("data/nfa.in");
    fin>>nfa;
    out<<"NFA: \n";
    out<<nfa;
    nfa.remove_lambdas();
    nfa.convert_to_dfa();
    DFA dfa = *(DFA*)&nfa;
    out<<dfa;
    out<<dfa.get_regex();
    fin.close();
    /*DFA dfa = *(DFA*)&nfa;
    dfa.minimize();
    out<<"DFA: \n";
    out<<dfa;
    fin.close();*/
}

void dfa_regex(ostream& out){
    out<<"<------ Dfa to regex: ---------------->\n\n";
    DFA dfa;
    ifstream fin("data/dfa.in");
    fin>>dfa;
    //dfa.minimize();
    out<<"Minimized DFA: \n";
    out<<dfa;
    out<<"Regex: \n";
    out<<dfa.get_regex();
    fin.close();
}

void regular_grammar_dfa(ostream& out){
    out<<"\n<------ Regular grammar to dfa: ------>\n\n";
    REGGRAM reggram;
    ifstream fin("data/reggram.in");
    fin>>reggram;
    out<<"Grammar: \n";
    out<<reggram;
    reggram.remove_lambdas();
    out<<"Epsilon free grammar: \n";
    out<<reggram;
    NFA nfa = reggram.get_nfa();
    nfa.remove_lambdas();
    out<<"NFA: \n";
    out<<nfa;
    out<<"Regex: \n";
    out<<nfa.get_regex()<<'\n';
    nfa.convert_to_dfa();
    DFA dfa = *(DFA*)&nfa;
    dfa.minimize();
    out<<"DFA: \n";
    out<<dfa;
    out<<"Final Regex: \n";
    out<<dfa.get_regex();
    fin.close();
}
int main() {
    
    ofstream fout("data/output.txt");
    
    //show_model(fout);

    //lambda_nfa_dfa(fout);
    //dfa_regex(fout);
    //regular_grammar_dfa(fout);

    NFA nfa;
    ifstream fin("data/nfa.in");
    fin>>nfa;
    nfa.convert_to_dfa();
    cout<<nfa.get_regex();
    fin.close();

    return 0;
}
