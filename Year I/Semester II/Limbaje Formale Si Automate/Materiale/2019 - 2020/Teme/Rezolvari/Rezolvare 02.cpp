#include <iostream>
#include <cstdio>
#include <vector>
#include <unordered_set>
#include <set>

#define MAXN 1201

bool viz[MAXN][MAXN];

using namespace std;

struct node{
    vector<pair<node *, char>> next;
    bool final_state;
    int id;
    node(int id, int is_final_state){
        this->id = id;
        this->final_state = is_final_state;
    }
};

vector<node *> g;
int s, m, fs;

bool check_dfa(string input, node *cg = g[0]){
    if(input.size()==0 && cg->final_state)
        return true;
    for(auto x: cg->next)
        if(x.second==input[0])
            return check_dfa(input.substr(1), x.first);
    return false;
}

bool check_nfa(string input){
    int k = 0;
    vector<node*> states, new_states;
    states.push_back(g[1]);
    bool end_state;
    for(char l : input){
        k++;
        end_state = false;
        new_states.clear();
        for(auto state : states)
            for(auto next_state: state->next){
                if(next_state.second==l && !viz[next_state.first->id][k]){
                    viz[next_state.first->id][k] = 1;
                    new_states.push_back(next_state.first);
                    if(next_state.first->final_state)
                        end_state = true;
                }
            }
        states = new_states;
    }
    return end_state;
}

void read_data(){
    g.clear();
    cin>>s>>fs;
    for(int i=0;i<s;i++)
        g.push_back(new node(i, false));
    for(int i=0;i<fs;i++){
        int x;
        cin>>x;
        g[x]->final_state = true;
    }
    cin>>m;
    while(m){
        int a, b;
        char acc;
        cin>>a>>b>>acc;
        g[a]->next.push_back({g[b], acc});
        m--;
    }
}

void write_smallest_words(){
    cout<<'\n';
    vector<pair<string, node*>> states, new_states;
    unordered_set<string> words;
    states.push_back({"", g[0]});
    int words_found = 0;
    while(words_found<100){
        new_states.resize(0);
        for(auto state : states) {
            for (auto next_state: state.second->next) {
                new_states.push_back({state.first+next_state.second, next_state.first});
                if (next_state.first->final_state)
                    if(words.find(state.first+next_state.second) == words.end()){
                        words.insert(state.first+next_state.second);
                        cout<<state.first+next_state.second<<'\n';
                        words_found++;
                    }
            }
        }
        states = new_states;
    }
}

void generate_exception(){
    cout<<3004<<'\n'<<1<<'\n'<<3003<<'\n';
    cout<<2000+1000*1000*2+2<<'\n';
    for(int i=1;i<=1000;++i)
        cout<<0<<' '<<i<<" a"<<'\n';
    for(int i = 1; i <= 1000; ++i)
        for(int j = 1001; j <= 2000; ++j)
            cout<<i<<' '<<j<<" b"<<'\n';
    for(int i = 1001; i <= 2000; ++i)
        for(int j = 2001; j <= 3000; ++j)
            cout<<i<<' '<<j<<" c"<<'\n';
    for(int i = 2001; i <= 3000; ++i)
        cout<<i<<' '<<3001<<" d"<<'\n';
    cout<<3000<<' '<<3002<<" d"<<'\n';
    cout<<3002<<' '<<3003<<" e"<<'\n';
}

void test_dfa(){
    cout<<"\nTesting dfa: \n";
    freopen("dfa.in", "r", stdin);
    read_data();
    cout<<"aba: "<<check_dfa("aba")<<'\n';
    cout<<"abb: "<<check_dfa("abb")<<'\n';
}

void test_nfa(){
    cout<<"\nTesting nfa: \n";
    freopen("nfa.in", "r", stdin);
    read_data();
    cout<<"abcde: "<<check_nfa("abcde")<<'\n';
    cout<<"abcdeee: "<<check_nfa("abcdeee")<<'\n';
}

void test_smallest(){
    write_smallest_words();
}

int main() {
    test_dfa();
    test_nfa();
    test_smallest();
    return 0;
}
