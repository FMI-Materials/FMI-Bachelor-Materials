#include <iostream>
#include <set>
#include <vector>

using namespace std;
int n,m;
set <int> S;
vector<int> muchii[1001];
vector<int> grade;
void citire(){
    cin >> n >> m;
    for(int i = 0; i <= n; ++i)
        grade.push_back(0);
    for(int i = 0; i < m; ++i){
        int x,y;
        cin >> x >> y;
        muchii[x].push_back(y);
        grade[y]++;
    }
}
void sortareTopologica(){
    for(int i = 1;i <=n; ++i)
        if(grade[i] == 0)
            S.insert(i);

    while(!S.empty()){
        int nod = *(S.begin());
        S.erase(nod);
        cout << nod << " ";
        for(auto j: muchii[nod])
        {
            grade[j]--;
            if(grade[j] == 0)
                S.insert(j);
        }
    }
}
int main() {
    citire();
    sortareTopologica();
    return 0;
}
