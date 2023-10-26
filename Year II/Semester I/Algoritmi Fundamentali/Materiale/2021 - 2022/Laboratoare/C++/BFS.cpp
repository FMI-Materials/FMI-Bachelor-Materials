#include <iostream>
#include <vector>
#include <algorithm>
#include <queue>
using namespace std;
int nrNoduri, nrMuchii, nodStart;
vector<int> vizitat;
vector<int> tata;
vector<int> muchii[1001];
void citire(){
    cin >> nrNoduri >> nrMuchii;
    for(int i = 0; i < nrNoduri; ++i){
        vizitat.push_back(0);
        tata.push_back(-1);
    }
    for(int i = 0; i < nrMuchii; ++i){
        int a,b;
        cin >> a >> b;
        muchii[a].push_back(b);
        muchii[b].push_back(a);
    }
    for(int i = 1;i < nrNoduri; ++i)
        sort(muchii[i].begin(),muchii[i].end());
}
void BFS(int start){
    queue <int> coada;
    vizitat[start] = 1;
    coada.push(start);
    while (!coada.empty()){
        int k = coada.front();
        coada.pop();
        for(int i = 0;i < muchii[k].size(); ++i)
            if(vizitat[muchii[k][i]] == 0){
                vizitat[muchii[k][i]] = vizitat[k] + 1;
                tata[muchii[k][i]] = k;
                coada.push(muchii[k][i]);
            }
        cout << k << ' ';
    }
}
int main() {
    citire();
    for(int i = 1; i <= nrNoduri; ++i)
        if( vizitat[i] == 0)
            BFS(i);
    return 0;
}
