#include <iostream>
#include <vector>

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
}
void DFS(int x){
    vizitat[x] = 1;
    //cout << x << " ";
    for(int i = 0;i < muchii[x].size(); ++i) {
        int z = muchii[x][i];
        if (vizitat[z] == 0) {
            tata[z] = x;
            DFS(z);
        } else if (z != tata[x]) {
            int y = x;
            while (y != z) {
                cout << y << " ";
                y = tata[y];
            }
            cout << z << " " << x;
            //exit(0);
        }
    }

}
int main(){
    citire();
    for(int i = 1;i <= nrNoduri; ++i)
        if(vizitat[i] == 0)
            DFS(i);
}