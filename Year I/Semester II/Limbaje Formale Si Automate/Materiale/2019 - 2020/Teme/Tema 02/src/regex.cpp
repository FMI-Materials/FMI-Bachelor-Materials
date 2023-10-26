#include <iostream>
#include <string>
#include <vector>
#include <set>

#include "../include/regex.h";

using namespace std;

REGEX::REGEX(std::string _syntax): syntax(_syntax){}

string REGEX::minimize_string(string _syntax){
    set<string> options;
    string last_option;
    auto next_p = [](string in){
        int m = 1;
        for(int i=0;i<in.size();i++){
            if(in[i]=='(') m++;
            if(in[i]==')') m--;
            if(m==0) return i;
        }
        return -1;
    };
    for(int i=0;i<_syntax.size();i++){
        if(_syntax[i]=='+'){
            options.insert(last_option);
            last_option.clear();
        }
        else if(_syntax[i]=='('){
            int np = next_p(_syntax.substr(i+1));
            if(np!=-1){
                last_option+='('+minimize_string(_syntax.substr(i+1, np))+')';
                i += np+1;
            }
        }else
            last_option+=_syntax[i];
    }
    if(!last_option.empty()) options.insert(last_option);
    string final;
    for(const auto& o: options){
        if(!final.empty()) final+="+";
        final+=o;
    }
    return final;
}

void REGEX::minimize() {
    this->syntax = this->minimize_string(this->syntax);
}


std::istream& operator>>(std::istream& in, REGEX &reggex){
    in>>reggex.syntax;
    return in;
}

ostream & operator<<(std::ostream& out, const REGEX & reggex) {
    out<<reggex.syntax<<'\n';
    return out;
}